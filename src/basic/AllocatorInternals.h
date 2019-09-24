#ifndef __GOTO_FRONTEND_BASIC_ALLOCATOR_INTERNAL_H__
#define __GOTO_FRONTEND_BASIC_ALLOCATOR_INTERNAL_H__

#include <cstdint>
#include <atomic>

namespace Goto
{
class MemoryChunk
{
    void* pageSignature = nullptr;

    volatile bool     pageIsFull     = false;
    volatile uint32_t pageAllocIndex = 0;
    volatile uint32_t pageAllocCount = 0;

    ~MemoryChunk() = delete;

public:
    void* allocate(size_t size);
    void  deallocate();

    void Free();

    bool IsFreeable();
    void Initialize();

    // This will be used that object is really allocated from MemoryChunk.
    bool CheckSignature() const;

    static MemoryChunk* FindOriginal(void* pObj);
};

size_t       InternalPageSize();
MemoryChunk* InternalAllocateChunk();
void         InternalFreeChunk(MemoryChunk* chunk);
} // namespace Sniper
#endif