#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <SDL2/SDL.h>

namespace zombie {
namespace assets {

/**
 * AssetHandle - Smart handle for streamed assets
 * 
 * Automatically loads/unloads assets based on usage.
 */
template<typename T>
class AssetHandle {
public:
 AssetHandle() : asset(nullptr), refCount(nullptr), ownsRef(true) {}
 
 explicit AssetHandle(T* ptr, int* sharedRef = nullptr, bool ownsSharedRef = true)
 : asset(ptr)
 , refCount(sharedRef ? sharedRef : (ptr ? new int(0) : nullptr))
 , ownsRef(sharedRef ? ownsSharedRef : true) {
 if (refCount) {
 (*refCount)++;
 }
 }
 
 AssetHandle(const AssetHandle& other)
 : asset(other.asset), refCount(other.refCount), ownsRef(other.ownsRef)
 {
 if (refCount) {
 (*refCount)++;
 }
 }

 AssetHandle(AssetHandle&& other) noexcept
 : asset(other.asset), refCount(other.refCount), ownsRef(other.ownsRef) {
 other.asset = nullptr;
 other.refCount = nullptr;
 other.ownsRef = true;
 }
 
 ~AssetHandle() {
 release();
 }
 
 AssetHandle& operator=(const AssetHandle& other) {
 if (this != &other) {
 release();
 asset = other.asset;
 refCount = other.refCount;
 ownsRef = other.ownsRef;
 if (refCount) {
 (*refCount)++;
 }
 }
 return *this;
 }

 AssetHandle& operator=(AssetHandle&& other) noexcept {
 if (this != &other) {
 release();
 asset = other.asset;
 refCount = other.refCount;
 ownsRef = other.ownsRef;
 other.asset = nullptr;
 other.refCount = nullptr;
 other.ownsRef = true;
 }
 return *this;
 }
 
 T* get() const { return asset; }
 T* operator->() const { return asset; }
 T& operator*() const { return *asset; }
 
 bool isValid() const { return asset != nullptr; }
 int getRefCount() const { return refCount ? *refCount : 0; }
 
private:
 T* asset;
 int* refCount;
 bool ownsRef;
 
 void release() {
 if (refCount && --(*refCount) == 0) {
 if (ownsRef) {
 delete refCount;
 }
 // Asset deletion handled by streaming system
 }
 asset = nullptr;
 refCount = nullptr;
 ownsRef = true;
 }
};

/**
 * AssetStreamingSystem - On-demand asset loading
 * 
 * Loads assets when needed, unloads when not used.
 * Reduces memory footprint and startup time.
 * 
 * Features:
 * - Async loading (background thread)
 * - Reference counting
 * - LRU cache eviction
 * - Memory budget management
 */
class AssetStreamingSystem {
public:
 struct Config {
 size_t maxMemoryBytes;
 size_t maxCachedAssets;
 bool asyncLoading;
 bool autoUnload;
 float unloadDelay;
 
 Config()
 : maxMemoryBytes(128 * 1024 * 1024)
 , maxCachedAssets(1000)
 , asyncLoading(true)
 , autoUnload(true)
 , unloadDelay(5.0f)
 {}
 };

 explicit AssetStreamingSystem(const Config& config = Config());
 ~AssetStreamingSystem();

 /**
 * Request texture (loads if not cached)
 * @param path - Path to texture file
 * @return Handle to texture (may be nullptr if loading)
 */
 AssetHandle<SDL_Texture> requestTexture(const std::string& path);

 /**
 * Preload texture (async)
 * @param path - Path to texture file
 */
 void preloadTexture(const std::string& path);

 /**
 * Check if asset is loaded
 */
 bool isLoaded(const std::string& path) const;

 /**
 * Unload specific asset
 */
 void unload(const std::string& path);

 /**
 * Unload all unused assets
 */
 void unloadUnused();

 /**
 * Update streaming system (call each frame)
 * @param deltaTime - Time since last update
 */
 void update(float deltaTime);

 /**
 * Get memory usage statistics
 */
 size_t getCurrentMemoryUsage() const { return currentMemoryUsage; }
 size_t getMaxMemoryUsage() const { return config.maxMemoryBytes; }
 size_t getCachedAssetCount() const { return cachedTextures.size(); }
 
 /**
 * Get cache statistics
 */
 size_t getTotalRequests() const { return totalRequests; }
 size_t getCacheHits() const { return cacheHits; }
 size_t getCacheMisses() const { return cacheMisses; }
 float getCacheHitRate() const {
 return totalRequests > 0 ? (100.0f * cacheHits / totalRequests) : 0.0f;
 }

 /**
 * Set memory budget
 */
 void setMemoryBudget(size_t bytes);

 /**
 * Clear all cached assets
 */
 void clear();

private:
 struct CachedTexture {
 SDL_Texture* texture;
 std::string path;
 size_t memorySize;
 int refCount;
 float lastAccessTime;
 float unloadTimer;
 
 CachedTexture()
 : texture(nullptr)
 , memorySize(0)
 , refCount(0)
 , lastAccessTime(0.0f)
 , unloadTimer(0.0f)
 {}
 };

 Config config;
 std::unordered_map<std::string, CachedTexture> cachedTextures;
 std::queue<std::string> loadQueue;
 std::mutex cacheMutex;
 
 size_t currentMemoryUsage;
 size_t totalRequests;
 size_t cacheHits;
 size_t cacheMisses;
 float globalTime;

 SDL_Texture* loadTextureImmediate(const std::string& path);
 void evictLRU();
 size_t estimateTextureMemory(SDL_Texture* texture);
};

/**
 * StreamingTextureManager - Wrapper for TextureManager with streaming
 * 
 * Drop-in replacement for TextureManager with automatic streaming.
 */
class StreamingTextureManager {
public:
 static StreamingTextureManager* getInstance();

 /**
 * Get texture (loads on-demand)
 */
 SDL_Texture* getTexture(const std::string& path);

 /**
 * Preload texture
 */
 void preloadTexture(const std::string& path);

 /**
 * Update streaming (call each frame)
 */
 void update(float deltaTime);

 /**
 * Get statistics
 */
 size_t getMemoryUsage() const;
 float getCacheHitRate() const;
 void printStats() const;

private:
 StreamingTextureManager();
 ~StreamingTextureManager();

 static StreamingTextureManager* instance;
 std::unique_ptr<AssetStreamingSystem> streamingSystem;
};

} // namespace assets
} // namespace zombie
