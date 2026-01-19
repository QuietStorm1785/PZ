#pragma once

#include <memory>
#include <string_view>
#include "LRUCache.h"

namespace zombie {
namespace iso {

// Forward declarations
class IsoTexture;
using IsoTexturePtr = std::shared_ptr<IsoTexture>;

// ============================================================================
// ISOMETRIC TEXTURE CACHE
// ============================================================================

class IsometricTextureCache {
public:
    explicit IsometricTextureCache(size_t max_cache_size = 128 * 1024 * 1024)
        : cache_(max_cache_size) {}

    // Load or get cached texture
    IsoTexturePtr get_or_load_texture(std::string_view path) noexcept {
        auto creator = [](const std::string& p) -> IsoTexturePtr {
            // Load texture from disk
            return load_texture_from_path(p);
        };

        return cache_.get_or_create(std::string(path), 0);  // Size handled internally
    }

    // Preload textures
    void preload_textures(const std::vector<std::string>& paths) noexcept {
        for (const auto& path : paths) {
            get_or_load_texture(path);
        }
    }

    // Get cache statistics
    jni::caching::CacheStatistics get_stats() const noexcept {
        return cache_.get_statistics();
    }

    // Clear cache
    void clear() noexcept {
        cache_.clear();
    }

    // Print cache report
    void print_report() const noexcept {
        cache_.print_report("IsometricTextureCache");
    }

private:
    static IsoTexturePtr load_texture_from_path(const std::string& path) noexcept {
        // Actual texture loading implementation
        return std::make_shared<IsoTexture>();  // Stub
    }

    jni::caching::LRUCache<std::string, IsoTexture> cache_;
};

// ============================================================================
// SPRITE ANIMATION FRAME CACHE
// ============================================================================

class SpriteFrameCache {
public:
    explicit SpriteFrameCache(size_t max_cache_size = 64 * 1024 * 1024)
        : cache_(max_cache_size) {}

    // Get animation frame
    std::shared_ptr<class SpriteFrame> get_frame(std::string_view animation_id,
                                                 uint32_t frame_index) noexcept {
        std::string key = std::string(animation_id) + "_" + std::to_string(frame_index);
        return cache_.get(key);
    }

    // Cache frame
    void cache_frame(std::string_view animation_id,
                    uint32_t frame_index,
                    std::shared_ptr<class SpriteFrame> frame,
                    size_t size_bytes) noexcept {
        std::string key = std::string(animation_id) + "_" + std::to_string(frame_index);
        cache_.put(key, frame, size_bytes);
    }

    // Preload animation
    void preload_animation(std::string_view animation_id,
                          uint32_t frame_count) noexcept {
        for (uint32_t i = 0; i < frame_count; ++i) {
            std::string key = std::string(animation_id) + "_" + std::to_string(i);
            // Load frame
        }
    }

    // Get statistics
    jni::caching::CacheStatistics get_stats() const noexcept {
        return cache_.get_statistics();
    }

    // Clear cache
    void clear() noexcept {
        cache_.clear();
    }

    void print_report() const noexcept {
        cache_.print_report("SpriteFrameCache");
    }

private:
    jni::caching::LRUCache<std::string, class SpriteFrame> cache_;
};

}  // namespace iso
}  // namespace zombie

#endif  // ISOMETRIC_TEXTURE_CACHE_H
