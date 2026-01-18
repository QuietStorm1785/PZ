#pragma once
#include "Collision.h"
#include <vector>
#include <memory>

class IsoGridSquare;
class IsoChunk;
class IsoCell;

/**
 * CollisionGrid - Spatial grid for efficient collision queries
 * Maps world coordinates to collision data
 */
class CollisionGrid {
public:
    explicit CollisionGrid(int gridSize = 32);  // 32x32 tiles per grid cell
    ~CollisionGrid();

    // Register collision bounds for entity
    void registerCollision(float x, float y, int z, float width, float height,
                          bool solid = true, void* entityPtr = nullptr);
    
    // Unregister collision
    void unregisterCollision(float x, float y, int z, void* entityPtr = nullptr);

    // Query collisions at position
    struct CollisionResult {
        bool blocked = false;
        bool solid = false;
        void* entityPtr = nullptr;
        float x, y, z;
        float width, height;
    };

    CollisionResult queryAt(float x, float y, int z);
    std::vector<CollisionResult> queryRadius(float x, float y, int z, float radius);
    std::vector<CollisionResult> queryBox(float x, float y, int z, float width, float height);

    // Clear all collisions
    void clear();

    // Statistics
    int getRegisteredCount() const { return registeredCount; }
    int getGridCellCount() const { return gridWidth * gridHeight; }

private:
    int gridSize;
    int gridWidth, gridHeight;
    int registeredCount = 0;

    // Grid cell containing collision data
    struct GridCell {
        std::vector<CollisionResult> collisions;
    };

    // 3D grid: [z][gridX][gridY]
    std::vector<std::vector<std::vector<GridCell>>> grid;

    // Helper: Get grid coordinates
    int getGridX(float worldX) const { return (int)(worldX / gridSize); }
    int getGridY(float worldY) const { return (int)(worldY / gridSize); }
    bool isValidGridPos(int gx, int gy, int z) const;
};

/**
 * WorldCollisionSystem - Manages collisions between world and entities
 */
class WorldCollisionSystem {
public:
    explicit WorldCollisionSystem(IsoCell* cell);
    ~WorldCollisionSystem();

    // Initialize collision grid from chunk data
    void buildCollisionGrid(int z);

    // Test if position is walkable
    bool isWalkable(float x, float y, int z);
    bool isWalkable(float x, float y, int z, float width, float height);

    // Move entity, handling collisions
    struct MoveResult {
        float actualX, actualY;  // Where entity ended up
        bool collided = false;
        std::vector<void*> hitEntities;  // Entities we collided with
    };

    MoveResult moveEntity(float fromX, float fromY, float toX, float toY, int z,
                         float width, float height, void* entityPtr = nullptr);

    // Register/unregister dynamic entity
    void registerEntity(float x, float y, int z, float width, float height,
                       bool solid, void* entityPtr);
    void unregisterEntity(void* entityPtr);

    // Update entity position
    void updateEntityPosition(void* entityPtr, float newX, float newY, int z);

    // Access collision grid
    const CollisionGrid& getGrid() const { return grid; }

private:
    IsoCell* cell;
    CollisionGrid grid;

    // Helper: Build collision from tile
    void addTileCollisions(IsoGridSquare* square);

    // Check line of sight with collision
    bool hasLineOfSight(float x1, float y1, float x2, float y2, int z);
};
