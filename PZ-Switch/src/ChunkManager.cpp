#include "ChunkManager.h"
#include "IsoCell.h"
#include "IsoChunk.h"
#include <cmath>
#include <algorithm>
#include <iostream>

ChunkManager::ChunkManager(IsoCell* cell, const Config& config)
    : cell(cell), config(config), updateAccumulator(0.0f) {
}

ChunkManager::~ChunkManager() {
    unloadAll();
}

ChunkManager::UpdateResult ChunkManager::update(float deltaTime, int playerChunkX, int playerChunkY, int playerZ) {
    UpdateResult result;
    result.totalLoaded = loadedChunks.size();

    updateAccumulator += deltaTime;
    if (updateAccumulator < config.updateInterval) {
        return result;  // Not time to update yet
    }
    updateAccumulator = 0.0f;

    // Get chunks to load and unload
    auto toLoad = getChunksToLoad(playerChunkX, playerChunkY, playerZ);
    auto toUnload = getChunksToUnload(playerChunkX, playerChunkY, playerZ);

    // Load nearby chunks (prioritize by distance)
    for (const auto& req : toLoad) {
        if ((int)loadedChunks.size() >= config.maxLoadedChunks) {
            break;  // Stop loading if at capacity
        }
        loadChunk(req.chunkX, req.chunkY, req.z);
        result.loaded++;
    }

    // Unload far chunks
    for (const auto& req : toUnload) {
        unloadChunk(req.chunkX, req.chunkY, req.z);
        result.unloaded++;
    }

    result.totalLoaded = loadedChunks.size();
    return result;
}

void ChunkManager::loadChunk(int chunkX, int chunkY, int z) {
    uint32_t key = getChunkKey(chunkX, chunkY, z);
    
    // Already loaded?
    if (loadedChunks.find(key) != loadedChunks.end()) {
        return;
    }

    // Load via cell (cell manages actual storage)
    cell->loadChunk(chunkX, chunkY, z);
    
    // Track in our manager
    IsoChunk* chunk = cell->getChunk(chunkX, chunkY, z);
    if (chunk) {
        loadedChunks[key] = chunk;
    }
}

void ChunkManager::unloadChunk(int chunkX, int chunkY, int z) {
    uint32_t key = getChunkKey(chunkX, chunkY, z);
    
    auto it = loadedChunks.find(key);
    if (it == loadedChunks.end()) {
        return;  // Not tracked
    }

    // Unload via cell
    cell->unloadChunk(chunkX, chunkY, z);
    
    // Remove from tracking
    loadedChunks.erase(it);
}

void ChunkManager::unloadAll() {
    auto keys = loadedChunks;
    for (const auto& kv : keys) {
        uint32_t key = kv.first;
        int chunkX = (key >> 16) & 0xFFFF;
        int chunkY = (key >> 8) & 0xFF;
        int z = key & 0xFF;
        unloadChunk(chunkX, chunkY, z);
    }
    loadedChunks.clear();
}

bool ChunkManager::isChunkLoaded(int chunkX, int chunkY, int z) const {
    uint32_t key = getChunkKey(chunkX, chunkY, z);
    return loadedChunks.find(key) != loadedChunks.end();
}

int ChunkManager::getTotalLoadedChunks() const {
    return loadedChunks.size();
}

float ChunkManager::getChunkDistance(int x1, int y1, int x2, int y2) const {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<ChunkManager::ChunkLoadRequest> ChunkManager::getChunksToLoad(int centerX, int centerY, int z) {
    std::vector<ChunkLoadRequest> requests;
    
    // Scan radius around player
    int loadDist = config.loadDistance;
    for (int dx = -loadDist; dx <= loadDist; dx++) {
        for (int dy = -loadDist; dy <= loadDist; dy++) {
            int chunkX = centerX + dx;
            int chunkY = centerY + dy;
            
            if (!isChunkLoaded(chunkX, chunkY, z)) {
                float dist = getChunkDistance(chunkX, chunkY, centerX, centerY);
                requests.push_back({chunkX, chunkY, z, dist});
            }
        }
    }
    
    // Sort by distance (nearest first)
    std::sort(requests.begin(), requests.end());
    
    return requests;
}

std::vector<ChunkManager::ChunkLoadRequest> ChunkManager::getChunksToUnload(int centerX, int centerY, int z) {
    std::vector<ChunkLoadRequest> requests;
    
    int unloadDist = config.unloadDistance;
    
    // Check all loaded chunks
    for (const auto& kv : loadedChunks) {
        uint32_t key = kv.first;
        int chunkZ = key & 0xFF;
        
        // Only check same level
        if (chunkZ != z) continue;
        
        int chunkX = (key >> 16) & 0xFFFF;
        int chunkY = (key >> 8) & 0xFF;
        
        float dist = getChunkDistance(chunkX, chunkY, centerX, centerY);
        
        // Beyond unload distance?
        if (dist > unloadDist) {
            requests.push_back({chunkX, chunkY, z, dist});
        }
    }
    
    // Sort by distance (farthest first)
    std::sort(requests.begin(), requests.end(), 
        [](const ChunkLoadRequest& a, const ChunkLoadRequest& b) {
            return a.distance > b.distance;
        });
    
    return requests;
}

ChunkManager::Stats ChunkManager::getStatistics() const {
    Stats stats;
    stats.totalLoaded = loadedChunks.size();
    
    // Estimate memory: ~32KB per chunk (32x32 grid with objects)
    stats.memoryEstimateMB = (stats.totalLoaded * 32) / 1024;
    
    // For now, just return approximation
    stats.averageDistance = config.loadDistance;
    
    stats.chunksQueuedForLoad = 0;  // No queue in sync implementation
    
    return stats;
}

// ChunkPreloader implementation
ChunkPreloader::ChunkPreloader(ChunkManager* manager)
    : manager(manager) {
}

ChunkPreloader::~ChunkPreloader() {
    loadQueue.clear();
}

void ChunkPreloader::preloadChunk(int chunkX, int chunkY, int z) {
    loadQueue.push_back(std::make_tuple(chunkX, chunkY, z));
}

bool ChunkPreloader::hasPendingLoads() const {
    return !loadQueue.empty();
}

bool ChunkPreloader::processOneLoad() {
    if (loadQueue.empty()) return false;
    
    auto [chunkX, chunkY, z] = loadQueue.front();
    loadQueue.erase(loadQueue.begin());
    
    manager->loadChunk(chunkX, chunkY, z);
    return true;
}
