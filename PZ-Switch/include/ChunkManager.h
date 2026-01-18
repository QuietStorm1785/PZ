#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>

class IsoChunk;
class IsoCell;
class IsoGridSquare;

/**
 * ChunkManager - Handles dynamic chunk loading/unloading around player
 * 
 * Features:
 * - Load chunks in view distance around player
 * - Unload chunks outside range
 * - Prioritize nearby chunks
 * - Z-level support
 * - Performance optimized (only load what's visible)
 */
class ChunkManager {
public:
 // Configuration
 struct Config {
 int loadDistance; // Chunks around player to load
 int unloadDistance; // Chunks beyond this are unloaded
 int maxLoadedChunks; // Cap on total loaded chunks
 float updateInterval; // How often to update chunk loading (seconds)
 
 Config()
 : loadDistance(3)
 , unloadDistance(5)
 , maxLoadedChunks(100)
 , updateInterval(1.0f) {}
 };

 explicit ChunkManager(IsoCell* cell, const Config& config = Config());
 ~ChunkManager();

 // Update - call once per frame
 // Returns number of chunks loaded/unloaded this frame
 struct UpdateResult {
 int loaded = 0;
 int unloaded = 0;
 int totalLoaded = 0;
 };
 UpdateResult update(float deltaTime, int playerChunkX, int playerChunkY, int playerZ);

 // Manual control
 void loadChunk(int chunkX, int chunkY, int z);
 void unloadChunk(int chunkX, int chunkY, int z);
 void unloadAll();

 // Query
 bool isChunkLoaded(int chunkX, int chunkY, int z) const;
 int getTotalLoadedChunks() const;
 
 // Statistics
 struct Stats {
 int totalLoaded;
 int memoryEstimateMB;
 float averageDistance;
 int chunksQueuedForLoad;
 };
 Stats getStatistics() const;

 // Configuration
 void setConfig(const Config& config) { this->config = config; }
 const Config& getConfig() const { return config; }

private:
 IsoCell* cell;
 Config config;
 float updateAccumulator = 0.0f;

 // Track loaded chunks for statistics
 std::unordered_map<uint32_t, IsoChunk*> loadedChunks;

 // Helper to generate chunk key
 uint32_t getChunkKey(int chunkX, int chunkY, int z) const {
 return ((uint32_t)chunkX << 16) | ((uint32_t)chunkY << 8) | (uint32_t)z;
 }

 // Chunk loading priority
 struct ChunkLoadRequest {
 int chunkX, chunkY, z;
 float distance;
 
 bool operator<(const ChunkLoadRequest& other) const {
 return distance < other.distance; // Min-heap (nearest first)
 }
 };

 // Get chunks to load around a position
 std::vector<ChunkLoadRequest> getChunksToLoad(int centerX, int centerY, int z);
 
 // Get chunks to unload (far from center)
 std::vector<ChunkLoadRequest> getChunksToUnload(int centerX, int centerY, int z);

 // Calculate distance between chunks
 float getChunkDistance(int x1, int y1, int x2, int y2) const;
};

/**
 * ChunkPreloader - Load chunks in background (for future async implementation)
 */
class ChunkPreloader {
public:
 explicit ChunkPreloader(ChunkManager* manager);
 ~ChunkPreloader();

 // Queue chunk for loading (currently synchronous, ready for async)
 void preloadChunk(int chunkX, int chunkY, int z);
 
 // Check if queue has pending loads
 bool hasPendingLoads() const;
 
 // Process one load (call in background or after frame)
 bool processOneLoad();

private:
 ChunkManager* manager;
 std::vector<std::tuple<int, int, int>> loadQueue;
};
