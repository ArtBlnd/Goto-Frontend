#ifndef __SNIPER_ENGINE_COMMON_ALLOCATOR_H__
#define __SNIPER_ENGINE_COMMON_ALLOCATOR_H__

#include <Basic/AllocatorInternals.h>

#include <shared_mutex>
#include <atomic>
#include <thread>
#include <vector>

namespace Goto
{
    // This is cuncurrent allocator that can allocate memory fast.
    // Concurrent Allocator
    //      Memory Usage : NORMAL
    //      Speed        : FAST
    //      Concurrency  : YES
    template <class Ty, size_t Pages = 4>
    class ConcurrentAllocator
    {
        using ChunkStorage = std::pair<MemoryChunk*, std::mutex>;

        const size_t ObjectSize = sizeof(Ty);
        const size_t ObjectPerPage = (InternalPageSize() / sizeof(Ty)) - 1;

        std::shared_mutex               caChunksMutex;
        std::array<ChunkStorage, Pages> caChunks;

        Ty* AllocateWith(MemoryChunk*& chunk)
        {
            void* pObj = chunk->allocate(sizeof(Ty));

            if (pObj != nullptr)
            {
                return (Ty*)pObj;
            }

            chunk = InternalAllocateChunk();
            return AllocateWith(chunk);
        }

    public:
        ConcurrentAllocator()
        {
            std::unique_lock<std::shared_mutex> lock(caChunksMutex);

            for (auto& [chunk, mutex] : caChunks)
            {
                chunk = InternalAllocateChunk();
            }
        }

        // allocate memory and construct it.
        template <class... ArgsTy>
        Ty* Allocate(ArgsTy... args)
        {
            std::shared_lock<std::shared_mutex> lock(caChunksMutex);

            while (true)
            {
                for (auto& [chunk, mutex] : caChunks)
                {
                    if (mutex.try_lock())
                    {
                        Ty* newObj = AllocateWith(chunk);
                        mutex.unlock();

                        if (!std::is_pod<Ty>::value)
                        {
                            return new(newObj) Ty(args...);
                        }

                        return newObj;
                    }
                }
            }

            // Unreachable.
            return nullptr;
        }

        template <class TyDist>
        void Deallocate(TyDist* ptr)
        {
            if (!std::is_pod<Ty>::value)
            {
                ptr->~TyDist();
            }
            
            MemoryChunk* chunk = MemoryChunk::FindOriginal(ptr);
            chunk->deallocate();

            if (chunk->IsFreeable())
            {
                chunk->Free();
            }
        }
    };

    // NOTE THAT THIS IS NOT THREAD SAFE
    // This is allocator that does not freed before distructing allocator itself.
    // Fast Allocator
    //      Memory Usage : VERY HIGH
    //      Speed        : BLAZING FAST
    //      Concurrency  : NO
    template <class Ty>
    class FastAllocator
    {
        const size_t ChunkSize = sizeof(Ty);

        std::vector<MemoryChunk*> faAllocatedChunks;
        MemoryChunk*              faChunk = nullptr;

        void ReplaceChunk()
        {
            faAllocatedChunks.push_back(faChunk);
            faChunk = InternalAllocateChunk();
        }

        Ty* AllocateImpl()
        {
            return (Ty*)faChunk->allocate(ChunkSize);
        }

        static void DeallocateChunks(std::vector<MemoryChunk*> chunks)
        {
            for (MemoryChunk* chunk : chunks)
            {
                chunk->Free();
            }
        }

    public:
        FastAllocator()
        {
            faChunk = InternalAllocateChunk();
        }

        ~FastAllocator()
        {
            std::thread deallocThread = std::thread(DeallocateChunks, std::move(faAllocatedChunks));
            deallocThread.detach();

            faChunk->Free();
        }

        template <class... ArgsTy>
        Ty* Allocate(ArgsTy... args)
        {
            Ty* newObject = AllocateImpl();

            if (newObject == nullptr)
            {
                ReplaceChunk();
                return Allocate(args...);
            }

            if (!std::is_pod<Ty>::value)
            {
                return new(newObject) Ty(args...);
            }

            return newObject;
        }

        template <class TyDist>
        void Deallocate(TyDist* ptr)
        {
            // Nothing to do with it.
        }
    };


    // This is cuncurrent allocator that can allocate memory fast.
    // Relaxed Allocator
    //      Memory Usage : NORMAL
    //      Speed        : FAST
    //      Concurrency  : YES
    template <size_t Pages>
    class RelaxedAllocator
    {
        using ChunkStorage = std::pair<MemoryChunk*, std::mutex>;
        
        std::shared_mutex               caChunksMutex;
        std::array<ChunkStorage, Pages> caChunks;

        template <class RetTy>
        RetTy* AllocateWith(MemoryChunk*& chunk)
        {
            void* pObj = chunk->allocate(sizeof(RetTy));

            if (pObj != nullptr)
            {
                return (RetTy*)pObj;
            }

            chunk = InternalAllocateChunk();
            return AllocateWith(chunk);
        }

    public:
        RelaxedAllocator()
        {
            std::unique_lock<std::shared_mutex> lock(caChunksMutex);

            for (auto& [chunk, mutex] : caChunks)
            {
                chunk = InternalAllocateChunk();
            }
        }

        // allocate memory and construct it.
        template <class Ty, class... ArgsTy>
        Ty* Allocate(ArgsTy... args)
        {
            std::shared_lock<std::shared_mutex> lock(caChunksMutex);

            while (true)
            {
                for (auto& [chunk, mutex] : caChunks)
                {
                    if (mutex.try_lock())
                    {
                        Ty* newObj = AllocateWith<Ty>(chunk);
                        mutex.unlock();

                        if (!std::is_pod<Ty>::value)
                        {
                            return new(newObj) Ty(args...);
                        }

                        return newObj;
                    }
                }
            }

            // Unreachable.
            return nullptr;
        }

        template <class Ty>
        void Deallocate(Ty* ptr)
        {
            if (!std::is_pod<Ty>::value)
            {
                ptr->~Ty();
            }
            
            MemoryChunk* chunk = MemoryChunk::FindOriginal(ptr);
            chunk->deallocate();

            if (chunk->IsFreeable())
            {
                chunk->Free();
            }
        }
    };
}

#endif