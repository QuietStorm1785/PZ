#pragma once
#include <vector>
#include <unordered_map>
#include <cstdint>

// Forward declarations
class IsoObject;
class IsoGridSquare;
class IsoCell;

namespace zombie { namespace characters { class IsoPlayer; } }

/**
 * VisibilityChecker - Line-of-sight and visibility queries
 * 
 * Provides raycasting and visibility checks for NPC vision and rendering occlusion.
 * Uses Bresenham line algorithm to check grid squares along a ray.
 * 
 * Performance: O(distance) per query, results can be cached
 * 
 * Example:
 *   VisibilityChecker vis;
 *   if (vis.canSee(x1, y1, x2, y2, z)) {
 *       // Direct line of sight
 *   }
 */
class VisibilityChecker {
public:
    VisibilityChecker();
    ~VisibilityChecker();

    /**
     * Check if target is visible from observer position
     * Uses raycasting with terrain occlusion
     * @param x1, y1 - Observer position
     * @param x2, y2 - Target position
     * @param z - Height level
     * @return true if there's line-of-sight
     */
    bool canSee(float x1, float y1, float x2, float y2, int z);

    /**
     * Check if observer can see a specific object
     * @param observer - Observer entity
     * @param object - Target object
     * @param maxDistance - Maximum visibility range
     * @return true if object is visible
     */
    bool canSeeObject(zombie::characters::IsoPlayer* observer, IsoObject* object, float maxDistance = 500.0f);

    /**
     * Get all visible objects from a position
     * @param x, y, z - Observer position
     * @param radius - Search radius
     * @param maxObjects - Max results to return
     * @return Vector of visible objects
     */
    std::vector<IsoObject*> getVisibleObjects(float x, float y, int z, float radius, int maxObjects = 100);

    /**
     * Bresenham line tracing for ray casting
     * @return Vector of grid positions along the ray
     */
    std::vector<std::pair<int, int>> traceRay(float x1, float y1, float x2, float y2);

    /**
     * Check if grid square blocks vision
     * @param square - Grid square to check
     * @return true if square is solid/opaque
     */
    bool isOccluding(IsoGridSquare* square);

    /**
     * Clear visibility cache (call after world changes)
     */
    void clearCache();

    /**
     * Get cache hit rate (for profiling)
     */
    int getCacheHitRate() const;

    /**
     * Set world reference for square queries
     */
    void setWorld(IsoCell* cell) { world = cell; }

private:
    // Caches line-of-sight results: hash(x1,y1,x2,y2,z) -> result
    std::unordered_map<uint64_t, bool> visibilityCache;
    
    // Cache statistics
    int cacheHits;
    int cacheMisses;

    // World reference for square queries
    IsoCell* world;

    uint64_t hashQuery(float x1, float y1, float x2, float y2, int z);
};

/**
 * FogOfWarSystem - Persistent visibility tracking
 * 
 * Tracks explored areas and maintains fog of war state per tile.
 * Can be used for visibility culling and explored area highlighting.
 */
class FogOfWarSystem {
public:
    enum class FogState {
        UNEXPLORED = 0,  // Never seen
        EXPLORED = 1,    // Seen before but not visible now
        VISIBLE = 2      // Currently visible
    };

    FogOfWarSystem(int width, int height, int depth);
    ~FogOfWarSystem();

    /**
     * Update visibility from observer position
     * @param observerX, observerY, observerZ - Observer location
     * @param visionRadius - How far observer can see
     */
    void updateVisibility(float observerX, float observerY, int observerZ, float visionRadius);

    /**
     * Get current fog state for tile
     */
    FogState getFogState(int x, int y, int z) const;

    /**
     * Set fog state directly
     */
    void setFogState(int x, int y, int z, FogState state);

    /**
     * Set explored state for tile (persistent)
     */
    void setExplored(int x, int y, int z);

    /**
     * Clear fog of war for a specific Z level
     */
    void clearFog(int z);

    /**
     * Get percentage of world explored
     */
    float getExploredPercentage() const;

private:
    int gridWidth, gridHeight, gridDepth;
    // 3D grid storage: fogGrid[x][y][z]
    std::vector<std::vector<std::vector<FogState>>> fogGrid;
    std::vector<bool> exploredMap;

    int getIndex(int x, int y, int z) const {
        return x + y * gridWidth + z * gridWidth * gridHeight;
    }
};
