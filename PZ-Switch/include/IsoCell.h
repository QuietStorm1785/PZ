#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "SpatialGrid.h"

class IsoGridSquare;
class IsoChunk;
namespace zombie { namespace characters { class IsoPlayer; } }
class IsoZombie;

// Use shorter alias and smart pointer types
using IsoPlayer = zombie::characters::IsoPlayer;
using IsoPlayerPtr = std::shared_ptr<IsoPlayer>;
using IsoZombiePtr = std::shared_ptr<IsoZombie>;

/**
 * IsoCell - Main world manager, handles chunks and grid squares
 * Represents the entire playable world divided into chunks
 */
class IsoCell {
public:
    using WalkabilityListenerId = uint32_t;
    static const int MAX_HEIGHT = 8;  // Max Z levels

    IsoCell(int width, int height);
    ~IsoCell();

    // Grid square access
    IsoGridSquare* getGridSquare(int x, int y, int z);
    const IsoGridSquare* getGridSquare(int x, int y, int z) const;

    // World dimensions
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Chunk management
    IsoChunk* getChunk(int chunkX, int chunkY, int z);
    void loadChunk(int chunkX, int chunkY, int z);
    void unloadChunk(int chunkX, int chunkY, int z);
    void unloadAllChunks();
    int getLoadedChunkCount() const { return chunks.size(); }
    
    // Convert world coordinates to chunk coordinates
    static int worldToChunkCoord(int worldCoord) { return worldCoord / 32; }
    static int worldToLocalCoord(int worldCoord) { return worldCoord % 32; }

    // Character management
    void addCharacter(IsoPlayerPtr player);
    void removeCharacter(IsoPlayerPtr player);
    const std::vector<IsoPlayerPtr>& getPlayers() const { return players; }

    // Zombie management
    void addZombie(IsoZombiePtr zombie);
    void removeZombie(IsoZombiePtr zombie);
    const std::vector<IsoZombiePtr>& getZombies() const { return zombies; }

    // Update
    void update();

    // Lightweight iteration over loaded content (no chunk loading)
    void forEachLoadedChunk(int z, const std::function<void(const IsoChunk*)>& fn) const;
    void forEachLoadedSquare(int z, const std::function<void(const IsoGridSquare*)>& fn) const;

    // Walkability change notifications (observer pattern)
    WalkabilityListenerId addWalkabilityListener(const std::function<void(int x, int y, int z, bool walkable)>& cb);
    void removeWalkabilityListener(WalkabilityListenerId id);
    void notifyWalkabilityChanged(int x, int y, int z, bool walkable);

    // Runtime object management
    IsoObject* spawnObject(const std::string& type, int x, int y, int z, bool solid = false);
    void despawnObject(IsoObject* obj);

    // Spatial queries
    std::vector<IsoObject*> queryObjectsNear(float x, float y, float z, float radius);
    std::vector<IsoPlayer*> queryEntitiesNear(float x, float y, float z, float radius);

private:
    int width, height;

    // Chunk storage - key is (chunkX << 16) | (chunkY << 8) | z
    std::unordered_map<uint32_t, std::unique_ptr<IsoChunk>> chunks;

    // Spatial grids for fast queries (one per world level)
    std::unordered_map<int, std::unique_ptr<SpatialGrid>> objectGrids;      // Z -> grid
    std::unordered_map<int, std::unique_ptr<EntitySpatialGrid>> entityGrids; // Z -> grid

    // All characters and zombies in the world (shared ownership)
    std::vector<IsoPlayerPtr> players;
    std::vector<IsoZombiePtr> zombies;

    // Helper to generate chunk key
    uint32_t getChunkKey(int chunkX, int chunkY, int z) const;
    
    // Ensure chunk exists
    void ensureChunkExists(int chunkX, int chunkY, int z);

    // Walkability listeners
    std::unordered_map<WalkabilityListenerId, std::function<void(int,int,int,bool)>> walkabilityListeners;
    WalkabilityListenerId nextWalkabilityListenerId = 1;

    // Helper to get or create spatial grid for a level
    SpatialGrid* getOrCreateObjectGrid(int z);
    EntitySpatialGrid* getOrCreateEntityGrid(int z);
};
