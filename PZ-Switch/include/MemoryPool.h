#pragma once

/**
 * Memory Pool Allocator for Java-Converted Objects
 * 
 * High-performance pooled allocator for frequently-allocated objects
 * to reduce heap fragmentation and GC pressure
 */

#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <cstdint>
#include <cstring>
#include <algorithm>

namespace jni {

/**
 * Fixed-size memory pool allocator
 * Useful for objects of uniform size
 */
template<size_t ObjectSize, size_t PoolSize = 1024>
class FixedMemoryPool {
private:
    struct Block {
        uint8_t data[ObjectSize];
        bool in_use;
    };
    
    std::vector<Block> m_blocks;
    std::queue<size_t> m_free_indices;
    mutable std::mutex m_mutex;
    size_t m_peak_usage;
    size_t m_current_usage;
    
public:
    FixedMemoryPool() : m_peak_usage(0), m_current_usage(0) {
        m_blocks.resize(PoolSize);
        for (size_t i = 0; i < PoolSize; ++i) {
            m_blocks[i].in_use = false;
            m_free_indices.push(i);
        }
    }
    
    /**
     * Allocate a block from the pool
     * Returns nullptr if pool is exhausted
     */
    void* allocate() {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        if (m_free_indices.empty()) {
            return nullptr; // Pool exhausted
        }
        
        size_t index = m_free_indices.front();
        m_free_indices.pop();
        
        m_blocks[index].in_use = true;
        m_current_usage++;
        m_peak_usage = std::max(m_peak_usage, m_current_usage);
        
        return m_blocks[index].data;
    }
    
    /**
     * Return a block to the pool
     */
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        std::lock_guard<std::mutex> lock(m_mutex);
        
        // Find the block
        uint8_t* ptr_data = static_cast<uint8_t*>(ptr);
        for (size_t i = 0; i < m_blocks.size(); ++i) {
            if (m_blocks[i].data == ptr_data) {
                m_blocks[i].in_use = false;
                m_free_indices.push(i);
                m_current_usage--;
                return;
            }
        }
    }
    
    /**
     * Get pool statistics
     */
    struct Stats {
        size_t pool_size;
        size_t available;
        size_t in_use;
        size_t peak_usage;
    };
    
    Stats getStats() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return {
            PoolSize,
            m_free_indices.size(),
            m_current_usage,
            m_peak_usage
        };
    }
    
    /**
     * Reset pool statistics
     */
    void resetStats() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_peak_usage = m_current_usage;
    }
};

/**
 * Generic object pool for small object allocations
 * Pre-allocates chunks and manages free list
 */
template<typename T>
class ObjectPool {
private:
    struct ObjectNode {
        T object;
        ObjectNode* next;
    };
    
    std::unique_ptr<ObjectNode[]> m_pool;
    ObjectNode* m_free_list;
    mutable std::mutex m_mutex;
    size_t m_pool_size;
    size_t m_allocated_count;
    
public:
    explicit ObjectPool(size_t size = 256) 
        : m_pool_size(size), m_allocated_count(0) {
        
        m_pool = std::make_unique<ObjectNode[]>(size);
        
        // Link free list
        m_free_list = &m_pool[0];
        for (size_t i = 0; i < size - 1; ++i) {
            m_pool[i].next = &m_pool[i + 1];
        }
        m_pool[size - 1].next = nullptr;
    }
    
    /**
     * Allocate an object from pool
     */
    template<typename... Args>
    std::shared_ptr<T> allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        if (!m_free_list) {
            // Pool exhausted, fall back to heap allocation
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
        
        ObjectNode* node = m_free_list;
        m_free_list = node->next;
        m_allocated_count++;
        
        // Construct object in-place
        new (&node->object) T(std::forward<Args>(args)...);
        
        return std::shared_ptr<T>(
            &node->object,
            [this, node](T*) {
                // Custom deleter that returns to pool
                node->object.~T();
                std::lock_guard<std::mutex> pool_lock(m_mutex);
                node->next = m_free_list;
                m_free_list = node;
                m_allocated_count--;
            }
        );
    }
    
    /**
     * Get pool statistics
     */
    struct Stats {
        size_t pool_size;
        size_t available;
        size_t in_use;
    };
    
    Stats getStats() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        size_t available = 0;
        ObjectNode* node = m_free_list;
        while (node) {
            available++;
            node = node->next;
        }
        return {
            m_pool_size,
            available,
            m_allocated_count
        };
    }
};

/**
 * Arena allocator for temporary/frame-based allocations
 * All allocations are freed when arena is cleared
 */
class ArenaAllocator {
private:
    static constexpr size_t CHUNK_SIZE = 65536; // 64KB chunks
    
    struct Chunk {
        std::unique_ptr<uint8_t[]> data;
        size_t used;
    };
    
    std::vector<Chunk> m_chunks;
    mutable std::mutex m_mutex;
    
public:
    ArenaAllocator() {
        m_chunks.emplace_back();
        m_chunks[0].data = std::make_unique<uint8_t[]>(CHUNK_SIZE);
        m_chunks[0].used = 0;
    }
    
    /**
     * Allocate memory from arena
     * Alignment is important for some types
     */
    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        Chunk& current = m_chunks.back();
        
        // Align current position
        size_t space = CHUNK_SIZE - current.used;
        uint8_t* ptr = current.data.get() + current.used;
        if (std::align(alignment, size, (void*&)ptr, space)) {
            size_t offset = ptr - current.data.get();
            current.used = offset + size;
            return ptr;
        }
        
        // Need new chunk
        m_chunks.emplace_back();
        m_chunks.back().data = std::make_unique<uint8_t[]>(CHUNK_SIZE);
        m_chunks.back().used = size;
        return m_chunks.back().data.get();
    }
    
    /**
     * Clear all allocations (they're reused in next frame)
     */
    void clear() {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& chunk : m_chunks) {
            chunk.used = 0;
        }
    }
    
    /**
     * Reset arena (new frame)
     */
    void reset() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_chunks.clear();
        m_chunks.emplace_back();
        m_chunks[0].data = std::make_unique<uint8_t[]>(CHUNK_SIZE);
        m_chunks[0].used = 0;
    }
    
    /**
     * Get memory usage statistics
     */
    struct Stats {
        size_t chunks;
        size_t total_capacity;
        size_t used;
    };
    
    Stats getStats() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        Stats stats = {m_chunks.size(), m_chunks.size() * CHUNK_SIZE, 0};
        for (const auto& chunk : m_chunks) {
            stats.used += chunk.used;
        }
        return stats;
    }
};

/**
 * Global memory pool instances for converted Java objects
 */
namespace pools {
    // Pre-allocated pools for common object sizes
    extern FixedMemoryPool<64, 2048> small_objects;    // 64 bytes, 2K objects
    extern FixedMemoryPool<256, 1024> medium_objects;   // 256 bytes, 1K objects
    extern FixedMemoryPool<1024, 256> large_objects;    // 1KB, 256 objects
    
    // Arena for frame-temporary allocations
    extern ArenaAllocator frame_arena;
    
    /**
     * Print memory pool statistics
     */
    void printStats();
    
    /**
     * Reset frame-based allocations
     */
    void resetFrame();
}

} // namespace jni

/**
 * Custom deleter for pooled allocations
 */
namespace std {
    template<size_t Size, size_t PoolSize>
    struct default_delete<jni::FixedMemoryPool<Size, PoolSize>> {
        void operator()(jni::FixedMemoryPool<Size, PoolSize>* ptr) const noexcept {
            delete ptr;
        }
    };
}
