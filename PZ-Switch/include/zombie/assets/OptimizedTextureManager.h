#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <SDL2/SDL.h>
#include "LRUCache.h"
#include "HotPathProfiler.h"

namespace zombie {
namespace assets {

// ============================================================================
// OPTIMIZED TEXTURE MANAGER WITH LRU CACHING
// ============================================================================

/**
 * Enhancement wrapper for TextureManager that adds LRU caching
 * for improved texture lookup performance and memory management.
 */
class OptimizedTextureManager {
public:
    // Configuration
    static constexpr size_t DEFAULT_CACHE_SIZE = 128 * 1024 * 1024;  // 128 MB
    static constexpr size_t MOBILE_CACHE_SIZE = 64 * 1024 * 1024;    // 64 MB (Switch)
    static constexpr size_t DESKTOP_CACHE_SIZE = 256 * 1024 * 1024;  // 256 MB (PC)

    explicit OptimizedTextureManager(size_t cache_size = DEFAULT_CACHE_SIZE);
    ~OptimizedTextureManager() = default;

    // Initialize texture cache
    void initialize(SDL_Renderer* renderer) noexcept;
    void shutdown() noexcept;

    // Get or load texture (automatic caching)
    SDL_Texture* get_texture(std::string_view path) noexcept {
        PROFILE_SCOPE("TextureLookup");
        return cache_.get(std::string(path)).get();
    }

    // Preload texture immediately
    void preload_texture(std::string_view path) noexcept {
        PROFILE_SCOPE("TexturePreload");
        get_texture(path);
    }

    // Preload multiple textures
    void preload_textures(const std::vector<std::string>& paths) noexcept {
        PROFILE_SCOPE("TexturePreloadBatch");
        for (const auto& path : paths) {
            preload_texture(path);
        }
    }

    // Get cache statistics
    void print_cache_status() const noexcept {
        auto stats = cache_.get_statistics();
        printf("\nTexture Cache Status:\n");
        printf("  Items: %u\n", stats.num_items);
        printf("  Memory: %.2f MB / %.2f MB\n",
               stats.current_size_bytes / 1024.0f / 1024.0f,
               stats.max_size_bytes / 1024.0f / 1024.0f);
        printf("  Hit Rate: %.1f%% (%llu hits, %llu misses)\n",
               stats.hit_rate(), stats.hits, stats.misses);
        printf("  Evictions: %llu\n", stats.evictions);
    }

    // Check if texture is cached
    bool is_cached(std::string_view path) const noexcept {
        return cache_.contains(std::string(path));
    }

    // Get cache hit rate
    double get_hit_rate() const noexcept {
        return cache_.get_statistics().hit_rate();
    }

    // Get cache memory usage
    size_t get_cache_memory_usage() const noexcept {
        return cache_.get_size_bytes();
    }

    // Get cache item count
    uint32_t get_cache_item_count() const noexcept {
        return cache_.get_item_count();
    }

    // Clear entire cache
    void clear_cache() noexcept {
        PROFILE_SCOPE("CacheClear");
        cache_.clear();
    }

    // Reset statistics
    void reset_cache_statistics() noexcept {
        cache_.reset_statistics();
    }

    // Get cache capacity
    size_t get_cache_capacity() const noexcept {
        return cache_.get_statistics().max_size_bytes;
    }

    // Set custom eviction callback
    void set_eviction_callback(
        std::function<void(const std::string&, SDL_Texture*)> callback) noexcept {
        eviction_callback_ = callback;
    }

private:
    SDL_Renderer* renderer_ = nullptr;
    jni::caching::LRUCache<std::string, SDL_Texture> cache_;
    std::function<void(const std::string&, SDL_Texture*)> eviction_callback_;

    // Load texture from disk
    std::shared_ptr<SDL_Texture> load_texture_from_disk(const std::string& path) noexcept;

    // Calculate texture size in bytes
    size_t calculate_texture_size(SDL_Texture* texture) const noexcept;
};

// ============================================================================
// SPRITE ANIMATION FRAME CACHE
// ============================================================================

class SpriteFrameCache {
public:
    static constexpr size_t DEFAULT_FRAME_CACHE_SIZE = 64 * 1024 * 1024;  // 64 MB

    explicit SpriteFrameCache(size_t cache_size = DEFAULT_FRAME_CACHE_SIZE);
    ~SpriteFrameCache() = default;

    // Get animation frame
    SDL_Texture* get_frame(std::string_view animation_id,
                          uint32_t frame_index) noexcept {
        PROFILE_SCOPE("FrameLookup");
        std::string key = std::string(animation_id) + "_" + std::to_string(frame_index);
        auto cached = frame_cache_.get(key);
        return cached ? cached.get() : nullptr;
    }

    // Cache animation frame
    void cache_frame(std::string_view animation_id,
                    uint32_t frame_index,
                    std::shared_ptr<SDL_Texture> frame,
                    size_t size_bytes) noexcept {
        PROFILE_SCOPE("FrameCache");
        std::string key = std::string(animation_id) + "_" + std::to_string(frame_index);
        frame_cache_.put(key, frame, size_bytes);
    }

    // Preload all frames of an animation
    void preload_animation(std::string_view animation_id,
                          uint32_t frame_count) noexcept {
        PROFILE_SCOPE("AnimationPreload");
        for (uint32_t i = 0; i < frame_count; ++i) {
            // Load frame - actual implementation depends on frame source
        }
    }

    // Get statistics
    void print_cache_status() const noexcept {
        auto stats = frame_cache_.get_statistics();
        printf("\nSprite Frame Cache Status:\n");
        printf("  Items: %u\n", stats.num_items);
        printf("  Memory: %.2f MB / %.2f MB\n",
               stats.current_size_bytes / 1024.0f / 1024.0f,
               stats.max_size_bytes / 1024.0f / 1024.0f);
        printf("  Hit Rate: %.1f%%\n", stats.hit_rate());
    }

    // Clear cache
    void clear() noexcept {
        frame_cache_.clear();
    }

private:
    jni::caching::LRUCache<std::string, SDL_Texture> frame_cache_;
};

}  // namespace assets
}  // namespace zombie
