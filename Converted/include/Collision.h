#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <vector>

namespace zombie {
namespace physics {

/**
 * AABB - Axis-Aligned Bounding Box
 */
struct AABB {
    float x, y, width, height;
    
    AABB() : x(0), y(0), width(0), height(0) {}
    AABB(float x, float y, float w, float h) : x(x), y(y), width(w), height(h) {}
    
    float left() const { return x; }
    float right() const { return x + width; }
    float top() const { return y; }
    float bottom() const { return y + height; }
    
    float centerX() const { return x + width * 0.5f; }
    float centerY() const { return y + height * 0.5f; }
};

/**
 * CollisionInfo - Information about a collision
 */
struct CollisionInfo {
    bool collided;
    float penetrationX;
    float penetrationY;
    float normalX;
    float normalY;
    
    CollisionInfo() 
        : collided(false)
        , penetrationX(0)
        , penetrationY(0)
        , normalX(0)
        , normalY(0) {}
};

/**
 * CollisionSystem - Handles collision detection and resolution
 */
class CollisionSystem {
public:
    CollisionSystem();
    ~CollisionSystem();
    
    // AABB collision detection
    static bool checkAABB(const AABB& a, const AABB& b);
    static bool checkAABB(const AABB& a, const AABB& b, CollisionInfo& info);
    
    // Entity collision
    static bool checkEntityCollision(entities::Entity* a, entities::Entity* b);
    static bool checkEntityCollision(entities::Entity* a, entities::Entity* b, CollisionInfo& info);
    
    // Point tests
    static bool pointInAABB(float px, float py, const AABB& box);
    
    // Circle collision (for simpler checks)
    static bool checkCircleCollision(float x1, float y1, float r1,
                                    float x2, float y2, float r2);
    
    // Tile collision
    static bool checkTileCollision(entities::Entity* entity,
                                   world::TileMap* tileMap,
                                   int layer = 0);
    
    // Resolve collision by moving entity
    static void resolveCollision(entities::Entity* entity, const CollisionInfo& info);
    
    // Check multiple entities
    static void checkEntityCollisions(std::vector<entities::Entity*>& entities);
};

/**
 * CollisionGrid - Spatial partitioning for efficient collision detection
 */
class CollisionGrid {
public:
    CollisionGrid(int cellSize = 64);
    ~CollisionGrid();
    
    void clear();
    void addEntity(entities::Entity* entity);
    
    // Query entities near a point or box
    std::vector<entities::Entity*> queryNear(float x, float y, float radius);
    std::vector<entities::Entity*> queryBox(const AABB& box);
    
private:
    int cellSize;
    std::unordered_map<int, std::vector<entities::Entity*>> grid;
    
    int getCellKey(int cellX, int cellY) const;
    void getCellCoords(float x, float y, int& cellX, int& cellY) const;
};

} // namespace physics
} // namespace zombie
