#include <Basic/AllocatorInternals.h>
#include <Basic/Debug.h>

#include <mutex>
#include <vector>
#include <thread>
#include <exception>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/mman.h>
#endif

namespace Goto
{

#ifdef _WIN32
size_t __pageSize = 0;

size_t __getPageSize()
{
    if (__pageSize != 0)
    {
        return __pageSize;
    }

    SYSTEM_INFO info;
    GetSystemInfo(&info);

    __pageSize = info.dwAllocationGranularity;

    return __getPageSize();
}

void* __allocatePage()
{
    size_t pageSize = __getPageSize();
    return VirtualAlloc(nullptr, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void __freePage(void* pPage)
{
    VirtualFree(pPage, 0, MEM_RELEASE);
}
#else
size_t __pageSize = 4096 * 16;

size_t __getPageSize()
{
    return __pageSize;
}

void* __allocatePage()
{
    // Windows platform has allocation granularity that linux does not
    // We have to create large page and cut it to make it aligned.
}

void __freePage(void* pPage) {}
#endif
// count of flying MemoryChunk objects
std::atomic<size_t> __pageUsing = 0;

MemoryChunk* InternalAllocateChunk()
{
    MemoryChunk* newChunk = (MemoryChunk*)__allocatePage();
    newChunk->Initialize();

#ifdef SNIPER_PLATFORM_IOS
    const size_t __pageMaxAlloc = (1024 * 1024 * 12) / __getPageSize();

    if (__pageUsing > __pageMaxAlloc)
    {
        while (__pageUsing < __pageMaxAlloc - std::thread::hardware_concurrency * 2)
        {
            std::this_thread::yield();
        }
    }
#endif

    __pageUsing++;
    return newChunk;
}

void InternalFreeChunk(MemoryChunk* chunk)
{
    __freePage(chunk);
    __pageUsing--;
    return;
}

size_t InternalPageSize()
{
    return __getPageSize() - sizeof(MemoryChunk);
}

template <class TyA, class TyB>
constexpr void* OffsetOf(TyA base, TyB offs)
{
    return (void*)((size_t)(base) + (size_t)(offs));
}

// ==================================================
// class MemoryChunk implements
// ==================================================

void* MemoryChunk::allocate(size_t size)
{
    void* pChunk = OffsetOf(this, sizeof(MemoryChunk) + pageAllocIndex);

    if (pageAllocIndex + size + sizeof(MemoryChunk) > __getPageSize())
    {
        pageIsFull = true;
        return nullptr;
    }

    pageAllocCount++;
    pageAllocIndex += (uint32_t)size;

    return pChunk;
}

void MemoryChunk::deallocate()
{
    --pageAllocCount;
}

void MemoryChunk::Free()
{
    debug_assert(CheckSignature(), "Unknown memory chunk!");
    InternalFreeChunk(this);
}

bool MemoryChunk::IsFreeable()
{
    return pageAllocCount == 0 && pageIsFull;
}

void MemoryChunk::Initialize()
{
    size_t thisPtr = (size_t)this;
    std::memcpy(this, &thisPtr, sizeof(size_t));
}

bool MemoryChunk::CheckSignature() const
{
    return pageSignature == this;
}

MemoryChunk* MemoryChunk::FindOriginal(void* pObj)
{
    size_t       offset = (size_t)(pObj) % __getPageSize();
    MemoryChunk* chunk  = (MemoryChunk*)((size_t)pObj - offset);

    // We need to check that calculated MemoryChunk is valid
    // If the signature of MemoryChunk is not same to its pointer
    // Its not a page object that allocated from __allocatePage()
    if (chunk->CheckSignature())
    {
        return chunk;
    }

    // Seems its not valid object. we got a wrong way.
    return nullptr;
}
} // namespace Sniper