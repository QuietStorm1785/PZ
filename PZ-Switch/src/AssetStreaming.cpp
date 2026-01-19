#include "AssetStreaming.h"
#include "Core.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

namespace zombie {
namespace assets {

// AssetStreamingSystem Implementation
AssetStreamingSystem::AssetStreamingSystem(const Config& cfg)
 : config(cfg)
 , currentMemoryUsage(0)
 , totalRequests(0)
 , cacheHits(0)
 , cacheMisses(0)
 , globalTime(0.0f)
{
 std::cout << "AssetStreamingSystem initialized" << '\n';
 std::cout << " Max memory: " << (config.maxMemoryBytes / (1024*1024)) << " MB" << '\n';
 std::cout << " Max cached assets: " << config.maxCachedAssets << '\n';
}

AssetStreamingSystem::~AssetStreamingSystem() {
 clear();
}

AssetHandle<SDL_Texture> AssetStreamingSystem::requestTexture(const std::string& path) {
 std::lock_guard<std::mutex> lock(cacheMutex);
 
 totalRequests++;
 
 // Check if already cached
 auto it = cachedTextures.find(path);
 if (it != cachedTextures.end()) {
 cacheHits++;
 it->second.lastAccessTime = globalTime;
 it->second.unloadTimer = 0.0f;
 return AssetHandle<SDL_Texture>(it->second.texture, &it->second.refCount, false);
 }
 
 cacheMisses++;
 
 // Load immediately (async loading would go here)
 SDL_Texture* texture = loadTextureImmediate(path);
 
 if (!texture) {
 return AssetHandle<SDL_Texture>();
 }
 
 // Add to cache
 CachedTexture cached;
 cached.texture = texture;
 cached.path = path;
 cached.memorySize = estimateTextureMemory(texture);
 cached.refCount = 0;
 cached.lastAccessTime = globalTime;
 cached.unloadTimer = 0.0f;
 
 currentMemoryUsage += cached.memorySize;
 cachedTextures[path] = cached;
 
 // Check if we need to evict
 if (currentMemoryUsage > config.maxMemoryBytes) {
 evictLRU();
 }
 
 auto& stored = cachedTextures[path];
 return AssetHandle<SDL_Texture>(stored.texture, &stored.refCount, false);
}

void AssetStreamingSystem::preloadTexture(const std::string& path) {
 if (config.asyncLoading) {
 loadQueue.push(path);
 } else {
 requestTexture(path);
 }
}

bool AssetStreamingSystem::isLoaded(const std::string& path) const {
 auto it = cachedTextures.find(path);
 return it != cachedTextures.end();
}

void AssetStreamingSystem::unload(const std::string& path) {
 std::lock_guard<std::mutex> lock(cacheMutex);
 
 auto it = cachedTextures.find(path);
 if (it != cachedTextures.end()) {
 if (it->second.texture) {
 SDL_DestroyTexture(it->second.texture);
 }
 currentMemoryUsage -= it->second.memorySize;
 cachedTextures.erase(it);
 }
}

void AssetStreamingSystem::unloadUnused() {
 std::lock_guard<std::mutex> lock(cacheMutex);
 
 std::vector<std::string> toUnload;
 
 for (auto& kv : cachedTextures) {
 if (kv.second.refCount == 0 && kv.second.unloadTimer >= config.unloadDelay) {
 toUnload.push_back(kv.first);
 }
 }
 
 for (const auto& path : toUnload) {
 auto it = cachedTextures.find(path);
 if (it != cachedTextures.end()) {
 if (it->second.texture) {
 SDL_DestroyTexture(it->second.texture);
 }
 currentMemoryUsage -= it->second.memorySize;
 cachedTextures.erase(it);
 }
 }
 
 if (!toUnload.empty()) {
 std::cout << "Unloaded " << toUnload.size() << " unused assets" << '\n';
 }
}

void AssetStreamingSystem::update(float deltaTime) {
 std::lock_guard<std::mutex> lock(cacheMutex);
 
 globalTime += deltaTime;
 
 // Update unload timers
 if (config.autoUnload) {
 for (auto& kv : cachedTextures) {
 if (kv.second.refCount == 0) {
 kv.second.unloadTimer += deltaTime;
 }
 }
 }
 
 // Process load queue (if async)
 if (config.asyncLoading && !loadQueue.empty()) {
 // Load one asset per frame to spread load
 std::string path = loadQueue.front();
 loadQueue.pop();
 
 if (!isLoaded(path)) {
 requestTexture(path);
 }
 }
}

void AssetStreamingSystem::setMemoryBudget(size_t bytes) {
 config.maxMemoryBytes = bytes;
 
 // Evict if over budget
 while (currentMemoryUsage > config.maxMemoryBytes) {
 evictLRU();
 }
}

void AssetStreamingSystem::clear() {
 std::lock_guard<std::mutex> lock(cacheMutex);
 
 for (auto& kv : cachedTextures) {
 if (kv.second.texture) {
 SDL_DestroyTexture(kv.second.texture);
 }
 }
 
 cachedTextures.clear();
 currentMemoryUsage = 0;
}

SDL_Texture* AssetStreamingSystem::loadTextureImmediate(const std::string& path) {
 auto* core = core::Core::getInstance();
 if (!core) return nullptr;
 
 SDL_Renderer* renderer = core->getRenderer();
 if (!renderer) return nullptr;
 
 SDL_Surface* surface = IMG_Load(path.c_str());
 if (!surface) {
 std::cerr << "Failed to load image: " << path << " - " << IMG_GetError() << '\n';
 return nullptr;
 }
 
 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
 SDL_FreeSurface(surface);
 
 if (!texture) {
 std::cerr << "Failed to create texture: " << path << " - " << SDL_GetError() << '\n';
 return nullptr;
 }
 
 return texture;
}

void AssetStreamingSystem::evictLRU() {
 // Find least recently used asset with refCount == 0
 std::string lruPath;
 float oldestTime = globalTime;
 
 for (const auto& kv : cachedTextures) {
 if (kv.second.refCount == 0 && kv.second.lastAccessTime < oldestTime) {
 oldestTime = kv.second.lastAccessTime;
 lruPath = kv.first;
 }
 }
 
 if (!lruPath.empty()) {
 std::cout << "Evicting LRU asset: " << lruPath << '\n';
 unload(lruPath);
 }
}

size_t AssetStreamingSystem::estimateTextureMemory(SDL_Texture* texture) {
 if (!texture) return 0;
 
 int w, h;
 SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
 
 // Estimate: width * height * 4 bytes (RGBA)
 return w * h * 4;
}

// StreamingTextureManager Implementation
StreamingTextureManager* StreamingTextureManager::instance = nullptr;

StreamingTextureManager::StreamingTextureManager() {
 AssetStreamingSystem::Config config;
 config.maxMemoryBytes = 64 * 1024 * 1024; // 64MB for textures
 config.maxCachedAssets = 500;
 config.autoUnload = true;
 config.unloadDelay = 10.0f; // Unload after 10 seconds of no use
 
 streamingSystem = std::make_unique<AssetStreamingSystem>(config);
}

StreamingTextureManager::~StreamingTextureManager() {
 streamingSystem.reset();
}

StreamingTextureManager* StreamingTextureManager::getInstance() {
 if (!instance) {
 instance = new StreamingTextureManager();
 }
 return instance;
}

SDL_Texture* StreamingTextureManager::getTexture(const std::string& path) {
 auto handle = streamingSystem->requestTexture(path);
 return handle.get();
}

void StreamingTextureManager::preloadTexture(const std::string& path) {
 streamingSystem->preloadTexture(path);
}

void StreamingTextureManager::update(float deltaTime) {
 streamingSystem->update(deltaTime);
 
 // Periodic cleanup
 static float cleanupTimer = 0.0f;
 cleanupTimer += deltaTime;
 if (cleanupTimer >= 5.0f) {
 streamingSystem->unloadUnused();
 cleanupTimer = 0.0f;
 }
}

size_t StreamingTextureManager::getMemoryUsage() const {
 return streamingSystem->getCurrentMemoryUsage();
}

float StreamingTextureManager::getCacheHitRate() const {
 return streamingSystem->getCacheHitRate();
}

void StreamingTextureManager::printStats() const {
 std::cout << "\n=== Asset Streaming Statistics ===" << '\n';
 std::cout << "Memory Usage: " << (streamingSystem->getCurrentMemoryUsage() / (1024*1024)) 
 << " / " << (streamingSystem->getMaxMemoryUsage() / (1024*1024)) << " MB" << '\n';
 std::cout << "Cached Assets: " << streamingSystem->getCachedAssetCount() << '\n';
 std::cout << "Cache Hit Rate: " << streamingSystem->getCacheHitRate() << "%" << '\n';
 std::cout << "Total Requests: " << streamingSystem->getTotalRequests() << '\n';
 std::cout << "Cache Hits: " << streamingSystem->getCacheHits() << '\n';
 std::cout << "Cache Misses: " << streamingSystem->getCacheMisses() << '\n';
 std::cout << "==================================\n" << '\n';
}

} // namespace assets
} // namespace zombie
