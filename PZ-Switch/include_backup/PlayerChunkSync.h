#pragma once
#include <memory>

class IsoCell;
class ChunkManager;
class IsoChunk;

/**
 * PlayerChunkSync - Synchronizes player position with chunk loading
 * 
 * Responsibilities:
 * - Track player's current chunk
 * - Request chunk loading/unloading based on player movement
 * - Handle smooth chunk transitions
 * - Support Z-level changes
 * - Detect and resolve chunk boundary crossings
 */
class PlayerChunkSync {
public:
    struct Config {
        int loadDistance;       // Chunks to load around player
        int unloadDistance;     // Chunks to unload beyond this
        float transitionSpeed;  // Smooth transition speed
        bool enableDebug;
        
        Config() : loadDistance(3), unloadDistance(5),
                  transitionSpeed(0.15f), enableDebug(false) {}
    };

    explicit PlayerChunkSync(IsoCell* cell, void* player, ChunkManager* manager,
                            const Config& config = Config());
    ~PlayerChunkSync();

    // Called each frame
    void update(float deltaTime);

    // Get current player chunk
    int getPlayerChunkX() const { return playerChunkX; }
    int getPlayerChunkY() const { return playerChunkY; }
    int getPlayerChunkZ() const { return playerChunkZ; }

    // Get smooth camera follow position
    struct Vec2 { float x = 0.0f, y = 0.0f; };
    Vec2 getCameraPosition() const { return cameraPos; }

    // Chunk boundary crossing
    bool isPlayerChunkBoundary() const { return nearChunkBoundary; }
    int getBoundaryDirection() const { return boundaryDirection; }

    // Z-level transition
    bool isPlayerZTransition() const { return inZTransition; }
    float getZTransitionProgress() const { return zTransitionProgress; }

    // Configuration
    void setConfig(const Config& cfg) { config = cfg; }
    const Config& getConfig() const { return config; }

    // Statistics
    struct Stats {
        int chunksLoaded = 0;
        int chunksUnloaded = 0;
        int boundarysCrossed = 0;
        int zLevelChanges = 0;
    };
    const Stats& getStats() const { return stats; }

private:
    IsoCell* cell;
    void* player;  // IsoPlayer* - use void* to avoid circular includes
    ChunkManager* chunkManager;
    Config config;
    Stats stats;

    // Current state
    int playerChunkX = 0;
    int playerChunkY = 0;
    int playerChunkZ = 0;
    
    Vec2 cameraPos;
    Vec2 targetCameraPos;

    // Chunk boundary detection
    bool nearChunkBoundary = false;
    int boundaryDirection = 0;  // Bitmask: 1=N, 2=E, 4=S, 8=W
    float boundaryDistance = 0.0f;

    // Z-level transition
    bool inZTransition = false;
    float zTransitionProgress = 0.0f;
    int targetZ = 0;

    // Helper methods
    void updateChunkPosition();
    void updateChunkLoading();
    void updateCameraPosition(float deltaTime);
    void updateBoundaryDetection();
    void updateZTransition(float deltaTime);
    void requestChunksAround(int cx, int cy);
};
