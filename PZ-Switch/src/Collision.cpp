#include "Collision.h"
#include <cmath>
#include <algorithm>

namespace zombie {
namespace physics {

// CollisionSystem implementation

CollisionSystem::CollisionSystem() {
}

CollisionSystem::~CollisionSystem() {
}

bool CollisionSystem::checkAABB(const AABB& a, const AABB& b) {
 return (a.left() < b.right() &&
 a.right() > b.left() &&
 a.top() < b.bottom() &&
 a.bottom() > b.top());
}

bool CollisionSystem::checkAABB(const AABB& a, const AABB& b, CollisionInfo& info) {
 if (!checkAABB(a, b)) {
 info.collided = false;
 return false;
 }
 
 info.collided = true;
 
 // Calculate overlap on each axis
 float overlapX = std::min(a.right(), b.right()) - std::max(a.left(), b.left());
 float overlapY = std::min(a.bottom(), b.bottom()) - std::max(a.top(), b.top());
 
 // Find the axis of least penetration
 if (overlapX < overlapY) {
 info.penetrationX = overlapX;
 info.penetrationY = 0;
 info.normalX = (a.centerX() < b.centerX()) ? -1.0f : 1.0f;
 info.normalY = 0;
 } else {
 info.penetrationX = 0;
 info.penetrationY = overlapY;
 info.normalX = 0;
 info.normalY = (a.centerY() < b.centerY()) ? -1.0f : 1.0f;
 }
 
 return true;
}

bool CollisionSystem::checkEntityCollision(entities::Entity* a, entities::Entity* b) {
 if (!a || !b) return false;
 
 float ax, ay, aw, ah;
 float bx, by, bw, bh;
 
 a->getBounds(ax, ay, aw, ah);
 b->getBounds(bx, by, bw, bh);
 
 AABB boxA(ax, ay, aw, ah);
 AABB boxB(bx, by, bw, bh);
 
 return checkAABB(boxA, boxB);
}

bool CollisionSystem::checkEntityCollision(entities::Entity* a, entities::Entity* b, CollisionInfo& info) {
 if (!a || !b) {
 info.collided = false;
 return false;
 }
 
 float ax, ay, aw, ah;
 float bx, by, bw, bh;
 
 a->getBounds(ax, ay, aw, ah);
 b->getBounds(bx, by, bw, bh);
 
 AABB boxA(ax, ay, aw, ah);
 AABB boxB(bx, by, bw, bh);
 
 return checkAABB(boxA, boxB, info);
}

bool CollisionSystem::pointInAABB(float px, float py, const AABB& box) {
 return (px >= box.left() && px <= box.right() &&
 py >= box.top() && py <= box.bottom());
}

bool CollisionSystem::checkCircleCollision(float x1, float y1, float r1,
 float x2, float y2, float r2) {
 float dx = x2 - x1;
 float dy = y2 - y1;
 float distSq = dx * dx + dy * dy;
 float radiusSum = r1 + r2;
 
 return distSq < (radiusSum * radiusSum);
}

bool CollisionSystem::checkTileCollision(entities::Entity* entity,
 world::TileMap* tileMap,
 int layer) {
 if (!entity || !tileMap) return false;
 
 float ex, ey, ew, eh;
 entity->getBounds(ex, ey, ew, eh);
 
 int tileSize = tileMap->getTileSize();
 
 // Get tile coordinates for the entity's bounds
 int startX = static_cast<int>(ex / tileSize);
 int startY = static_cast<int>(ey / tileSize);
 int endX = static_cast<int>((ex + ew) / tileSize);
 int endY = static_cast<int>((ey + eh) / tileSize);
 
 // Check tiles in the entity's area
 for (int y = startY; y <= endY; y++) {
 for (int x = startX; x <= endX; x++) {
 int tileId = tileMap->getTile(x, y, layer);
 
 // If tile exists (not -1), there's a collision
 if (tileId >= 0) {
 return true;
 }
 }
 }
 
 return false;
}

void CollisionSystem::resolveCollision(entities::Entity* entity, const CollisionInfo& info) {
 if (!entity || !info.collided) return;
 
 // Move entity out of collision
 float newX = entity->getX() + info.normalX * info.penetrationX;
 float newY = entity->getY() + info.normalY * info.penetrationY;
 
 entity->setPosition(newX, newY);
 
 // Optionally cancel velocity in the collision direction
 float vx = entity->getVelocityX();
 float vy = entity->getVelocityY();
 
 if (info.normalX != 0) vx = 0;
 if (info.normalY != 0) vy = 0;
 
 entity->setVelocity(vx, vy);
}

void CollisionSystem::checkEntityCollisions(std::vector<entities::Entity*>& entities) {
 for (size_t i = 0; i < entities.size(); i++) {
 for (size_t j = i + 1; j < entities.size(); j++) {
 CollisionInfo info;
 if (checkEntityCollision(entities[i], entities[j], info)) {
 // Handle collision - could trigger events here
 // For now, just resolve for the first entity
 resolveCollision(entities[i], info);
 }
 }
 }
}

// CollisionGrid implementation

CollisionGrid::CollisionGrid(int cellSize)
 : cellSize(cellSize)
{
}

CollisionGrid::~CollisionGrid() {
}

void CollisionGrid::clear() {
 grid.clear();
}

void CollisionGrid::addEntity(entities::Entity* entity) {
 if (!entity) return;
 
 int cellX, cellY;
 getCellCoords(entity->getX(), entity->getY(), cellX, cellY);
 
 int key = getCellKey(cellX, cellY);
 grid[key].push_back(entity);
}

std::vector<entities::Entity*> CollisionGrid::queryNear(float x, float y, float radius) {
 std::vector<entities::Entity*> result;
 
 int cellX, cellY;
 getCellCoords(x, y, cellX, cellY);
 
 int cellRadius = static_cast<int>(radius / cellSize) + 1;
 
 // Check surrounding cells
 for (int dy = -cellRadius; dy <= cellRadius; dy++) {
 for (int dx = -cellRadius; dx <= cellRadius; dx++) {
 int key = getCellKey(cellX + dx, cellY + dy);
 auto it = grid.find(key);
 
 if (it != grid.end()) {
 for (auto* entity : it->second) {
 // Check actual distance
 float ex = entity->getX();
 float ey = entity->getY();
 float distSq = (ex - x) * (ex - x) + (ey - y) * (ey - y);
 
 if (distSq <= radius * radius) {
 result.push_back(entity);
 }
 }
 }
 }
 }
 
 return result;
}

std::vector<entities::Entity*> CollisionGrid::queryBox(const AABB& box) {
 std::vector<entities::Entity*> result;
 
 int startCellX, startCellY, endCellX, endCellY;
 getCellCoords(box.left(), box.top(), startCellX, startCellY);
 getCellCoords(box.right(), box.bottom(), endCellX, endCellY);
 
 for (int cy = startCellY; cy <= endCellY; cy++) {
 for (int cx = startCellX; cx <= endCellX; cx++) {
 int key = getCellKey(cx, cy);
 auto it = grid.find(key);
 
 if (it != grid.end()) {
 for (auto* entity : it->second) {
 result.push_back(entity);
 }
 }
 }
 }
 
 return result;
}

int CollisionGrid::getCellKey(int cellX, int cellY) const {
 // Simple hash function for 2D coordinates
 return cellX + cellY * 10000;
}

void CollisionGrid::getCellCoords(float x, float y, int& cellX, int& cellY) const {
 cellX = static_cast<int>(std::floor(x / cellSize));
 cellY = static_cast<int>(std::floor(y / cellSize));
}

} // namespace physics
} // namespace zombie
