#pragma once

#include <memory>
#include <unordered_map>
#include <deque>
#include <mutex>
#include <functional>
#include <cstddef>
#include <string_view>
#include "JNIBridge.h"

namespace jni {
namespace caching {

// ============================================================================
// LRU CACHE ENTRY
// ============================================================================

template <typename ValueT>
struct CacheEntry {
    std::string key;
    std::shared_ptr<ValueT> value;
    size_t size_bytes = 0;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point last_accessed;

    CacheEntry(std::string_view k, std::shared_ptr<ValueT> v, size_t sz)
        : key(k), value(v), size_bytes(sz) {
        created_at = std::chrono::system_clock::now();
        last_accessed = created_at;
    }
};

// ============================================================================
// LRU CACHE STATISTICS
// ============================================================================

struct CacheStatistics {
    uint64_t hits = 0;
    uint64_t misses = 0;
    uint64_t evictions = 0;
    size_t current_size_bytes = 0;
    size_t max_size_bytes = 0;
    uint32_t num_items = 0;

    float hit_rate() const noexcept {
        uint64_t total = hits + misses;
        return total > 0 ? (static_cast<float>(hits) / total) * 100.0f : 0.0f;
    }
};

// ============================================================================
// THREAD-SAFE LRU CACHE
// ============================================================================

template <typename KeyT, typename ValueT>
class LRUCache {
public:
    using CreateFn = std::function<std::shared_ptr<ValueT>(const KeyT&)>;
    using EvictFn = std::function<void(const KeyT&, const ValueT&)>;

    explicit LRUCache(size_t max_size_bytes,
                      CreateFn creator = nullptr,
                      EvictFn evictor = nullptr)
        : max_size_bytes_(max_size_bytes),
          creator_(creator),
          evictor_(evictor) {}

    ~LRUCache() = default;

    // Get or create an item
    std::shared_ptr<ValueT> get_or_create(const KeyT& key,
                                          size_t size_bytes) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        // Check if already cached
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            stats_.hits++;
            it->second->last_accessed = std::chrono::system_clock::now();
            lru_order_.erase(it->second->order_it);
            lru_order_.push_back(key);
            it->second->order_it = std::prev(lru_order_.end());
            return it->second->value;
        }

        // Cache miss
        stats_.misses++;

        // Create new item
        std::shared_ptr<ValueT> value;
        if (creator_) {
            value = creator_(key);
        } else {
            value = std::make_shared<ValueT>();
        }

        // Evict old items if necessary
        while (current_size_bytes_ + size_bytes > max_size_bytes_ && !cache_.empty()) {
            evict_oldest();
        }

        // Insert new item
        lru_order_.push_back(key);
        auto entry = std::make_shared<CacheEntry<ValueT>>(
            std::string_view(reinterpret_cast<const char*>(&key), sizeof(KeyT)),
            value,
            size_bytes);
        entry->order_it = std::prev(lru_order_.end());
        cache_[key] = entry;

        current_size_bytes_ += size_bytes;

        return value;
    }

    // Get cached item without creating
    std::shared_ptr<ValueT> get(const KeyT& key) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = cache_.find(key);
        if (it != cache_.end()) {
            stats_.hits++;
            it->second->last_accessed = std::chrono::system_clock::now();
            
            // Update LRU order
            lru_order_.erase(it->second->order_it);
            lru_order_.push_back(key);
            it->second->order_it = std::prev(lru_order_.end());
            
            return it->second->value;
        }

        stats_.misses++;
        return nullptr;
    }

    // Put item in cache
    void put(const KeyT& key, std::shared_ptr<ValueT> value, size_t size_bytes) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        // Remove existing entry if present
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            current_size_bytes_ -= it->second->size_bytes;
            lru_order_.erase(it->second->order_it);
            cache_.erase(it);
        }

        // Evict if necessary
        while (current_size_bytes_ + size_bytes > max_size_bytes_ && !cache_.empty()) {
            evict_oldest();
        }

        // Insert new entry
        lru_order_.push_back(key);
        auto entry = std::make_shared<CacheEntry<ValueT>>(
            std::string_view(reinterpret_cast<const char*>(&key), sizeof(KeyT)),
            value,
            size_bytes);
        entry->order_it = std::prev(lru_order_.end());
        cache_[key] = entry;

        current_size_bytes_ += size_bytes;
    }

    // Remove specific item
    void remove(const KeyT& key) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = cache_.find(key);
        if (it != cache_.end()) {
            current_size_bytes_ -= it->second->size_bytes;
            lru_order_.erase(it->second->order_it);
            cache_.erase(it);
        }
    }

    // Check if key exists
    bool contains(const KeyT& key) const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return cache_.find(key) != cache_.end();
    }

    // Clear cache
    void clear() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        cache_.clear();
        lru_order_.clear();
        current_size_bytes_ = 0;
        stats_.evictions = 0;
    }

    // Get statistics
    CacheStatistics get_statistics() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        CacheStatistics stat = stats_;
        stat.current_size_bytes = current_size_bytes_;
        stat.max_size_bytes = max_size_bytes_;
        stat.num_items = cache_.size();
        return stat;
    }

    // Reset statistics
    void reset_statistics() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        stats_.hits = 0;
        stats_.misses = 0;
        stats_.evictions = 0;
    }

    // Get size in bytes
    size_t get_size_bytes() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return current_size_bytes_;
    }

    // Get item count
    uint32_t get_item_count() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return cache_.size();
    }

    // Print cache report
    void print_report(std::string_view cache_name) const noexcept {
        auto stats = get_statistics();
        printf("\n=== LRU Cache Report: %s ===\n", cache_name.data());
        printf("  Items: %u\n", stats.num_items);
        printf("  Size: %.2f MB / %.2f MB\n",
               stats.current_size_bytes / 1024.0f / 1024.0f,
               stats.max_size_bytes / 1024.0f / 1024.0f);
        printf("  Hit Rate: %.1f%% (%llu hits, %llu misses)\n",
               stats.hit_rate(), stats.hits, stats.misses);
        printf("  Evictions: %llu\n", stats.evictions);
        printf("============================\n\n");
    }

private:
    void evict_oldest() noexcept {
        if (lru_order_.empty()) return;

        const KeyT& oldest_key = lru_order_.front();
        auto it = cache_.find(oldest_key);
        if (it != cache_.end()) {
            if (evictor_ && it->second->value) {
                evictor_(oldest_key, *it->second->value);
            }
            current_size_bytes_ -= it->second->size_bytes;
            cache_.erase(it);
            stats_.evictions++;
        }
        lru_order_.pop_front();
    }

    size_t max_size_bytes_;
    size_t current_size_bytes_ = 0;
    CreateFn creator_;
    EvictFn evictor_;

    std::unordered_map<KeyT, std::shared_ptr<CacheEntry<ValueT>>> cache_;
    std::deque<KeyT> lru_order_;
    mutable std::mutex mutex_;
    mutable CacheStatistics stats_;
};

// ============================================================================
// TEXTURE CACHE SPECIALIZATION
// ============================================================================

class ITexture {
public:
    virtual ~ITexture() = default;
    virtual size_t get_size_bytes() const noexcept = 0;
};

using TextureLRUCache = LRUCache<std::string, ITexture>;

}  // namespace caching
}  // namespace jni

#endif  // LRU_CACHE_H
