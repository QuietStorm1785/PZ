#include "WorldCollisionSystem.h"
#include "IsoCell.h"
#include "IsoChunk.h"
#include "IsoGridSquare.h"
#include <cmath>
#include <algorithm>

// ===== CollisionGrid =====

CollisionGrid::CollisionGrid(int gridSize)
 : gridSize(gridSize), gridWidth(1000), gridHeight(1000) {
 // Initialize 3D grid (8 Z-levels, large X/Y grid)
 grid.resize(8);
 for (int z = 0; z < 8; z++) {
 grid[z].resize(gridWidth);
 for (int x = 0; x < gridWidth; x++) {
 grid[z][x].resize(gridHeight);
 }
 }
}

CollisionGrid::~CollisionGrid() = default;

bool CollisionGrid::isValidGridPos(int gx, int gy, int z) const {
 return gx >= 0 && gx < gridWidth && gy >= 0 && gy < gridHeight && z >= 0 && z < 8;
}

void CollisionGrid::registerCollision(float x, float y, int z, float width, float height,
 bool solid, void* entityPtr) {
 if (z < 0 || z >= 8) return;

 int gridX = getGridX(x);
 int gridY = getGridY(y);
 
 if (!isValidGridPos(gridX, gridY, z)) return;

 CollisionResult result;
 result.blocked = solid;
 result.solid = solid;
 result.entityPtr = entityPtr;
 result.x = x;
 result.y = y;
 result.z = z;
 result.width = width;
 result.height = height;

 grid[z][gridX][gridY].collisions.push_back(result);
 registeredCount++;
}

void CollisionGrid::unregisterCollision(float x, float y, int z, void* entityPtr) {
 if (z < 0 || z >= 8) return;

 int gridX = getGridX(x);
 int gridY = getGridY(y);
 
 if (!isValidGridPos(gridX, gridY, z)) return;

 auto& collisions = grid[z][gridX][gridY].collisions;
 collisions.erase(
 std::remove_if(collisions.begin(), collisions.end(),
 [entityPtr](const CollisionResult& r) {
 return r.entityPtr == entityPtr;
 }),
 collisions.end()
 );
}

void CollisionGrid::clear() {
 for (int z = 0; z < 8; z++) {
 for (int x = 0; x < gridWidth; x++) {
 for (int y = 0; y < gridHeight; y++) {
 grid[z][x][y].collisions.clear();
 }
 }
 }
 registeredCount = 0;
}

CollisionGrid::CollisionResult CollisionGrid::queryAt(float x, float y, int z) {
 if (z < 0 || z >= 8) {
 return CollisionResult();
 }

 int gridX = getGridX(x);
 int gridY = getGridY(y);
 
 if (!isValidGridPos(gridX, gridY, z)) {
 return CollisionResult();
 }

 // Check if any collision at this grid cell blocks the position
 auto& collisions = grid[z][gridX][gridY].collisions;
 for (const auto& collision : collisions) {
 // Check AABB overlap
 if (x >= collision.x && x < collision.x + collision.width &&
 y >= collision.y && y < collision.y + collision.height) {
 return collision;
 }
 }

 CollisionResult empty;
 return empty;
}

std::vector<CollisionGrid::CollisionResult> CollisionGrid::queryRadius(
 float x, float y, int z, float radius) {
 std::vector<CollisionResult> results;
 
 if (z < 0 || z >= 8) return results;

 // Calculate grid bounds
 int minGx = getGridX(x - radius);
 int maxGx = getGridX(x + radius);
 int minGy = getGridY(y - radius);
 int maxGy = getGridY(y + radius);

 // Query all grid cells in radius
 for (int gx = minGx; gx <= maxGx; gx++) {
 for (int gy = minGy; gy <= maxGy; gy++) {
 if (!isValidGridPos(gx, gy, z)) continue;

 auto& collisions = grid[z][gx][gy].collisions;
 for (const auto& collision : collisions) {
 // Check distance
 float dx = collision.x - x;
 float dy = collision.y - y;
 float dist = std::sqrt(dx * dx + dy * dy);
 if (dist <= radius) {
 results.push_back(collision);
 }
 }
 }
 }

 return results;
}

std::vector<CollisionGrid::CollisionResult> CollisionGrid::queryBox(
 float x, float y, int z, float width, float height) {
 std::vector<CollisionResult> results;
 
 if (z < 0 || z >= 8) return results;

 // Calculate grid bounds
 int minGx = getGridX(x);
 int maxGx = getGridX(x + width);
 int minGy = getGridY(y);
 int maxGy = getGridY(y + height);

 // Query all grid cells that overlap box
 for (int gx = minGx; gx <= maxGx; gx++) {
 for (int gy = minGy; gy <= maxGy; gy++) {
 if (!isValidGridPos(gx, gy, z)) continue;

 auto& collisions = grid[z][gx][gy].collisions;
 for (const auto& collision : collisions) {
 // Check AABB overlap
 if (!(x + width < collision.x || x > collision.x + collision.width ||
 y + height < collision.y || y > collision.y + collision.height)) {
 results.push_back(collision);
 }
 }
 }
 }

 return results;
}

// ===== WorldCollisionSystem =====

WorldCollisionSystem::WorldCollisionSystem(IsoCell* cell)
 : cell(cell), grid(32) {
}

WorldCollisionSystem::~WorldCollisionSystem() = default;

void WorldCollisionSystem::buildCollisionGrid(int z) {
 if (!cell) return;

 // Clear existing collisions for this Z-level
 // (Would need Z-level aware clear in CollisionGrid)

 // Iterate all loaded chunks at this Z-level
 cell->forEachLoadedChunk(z, [&](const IsoChunk* chunk) {
 // For each tile in chunk
 for (int x = 0; x < 32; x++) {
 for (int y = 0; y < 32; y++) {
 IsoGridSquare* square = const_cast<IsoChunk*>(chunk)->getGridSquare(x, y);
 if (square) {
 addTileCollisions(square);
 }
 }
 }
 });
}

void WorldCollisionSystem::addTileCollisions(IsoGridSquare* square) {
 if (!square || !square->isSolid()) return;

 // Register collision for solid tiles
 grid.registerCollision(
 (float)square->getX(), (float)square->getY(), square->getZ(),
 1.0f, 1.0f, // 1x1 tile size
 true,
 (void*)square
 );
}

bool WorldCollisionSystem::isWalkable(float x, float y, int z) {
 auto result = grid.queryAt(x, y, z);
 return !result.blocked;
}

bool WorldCollisionSystem::isWalkable(float x, float y, int z, float width, float height) {
 auto results = grid.queryBox(x, y, z, width, height);
 
 for (const auto& result : results) {
 if (result.blocked) {
 return false;
 }
 }
 
 return true;
}

WorldCollisionSystem::MoveResult WorldCollisionSystem::moveEntity(
 float fromX, float fromY, float toX, float toY, int z,
 float width, float height, void* entityPtr) {
 
 MoveResult result;
 result.actualX = toX;
 result.actualY = toY;

 // Check if destination is walkable
 if (isWalkable(toX, toY, z, width, height)) {
 // No collision, move freely
 result.collided = false;
 } else {
 // Collision detected, slide along obstacles
 result.collided = true;
 
 // Try X-axis only
 if (isWalkable(toX, fromY, z, width, height)) {
 result.actualY = fromY;
 }
 // Try Y-axis only
 else if (isWalkable(fromX, toY, z, width, height)) {
 result.actualX = fromX;
 }
 // Both blocked, stay in place
 else {
 result.actualX = fromX;
 result.actualY = fromY;
 }
 }

 // Collect hit entities
 auto hits = grid.queryBox(result.actualX, result.actualY, z, width, height);
 for (const auto& hit : hits) {
 if (hit.entityPtr && hit.entityPtr != entityPtr) {
 result.hitEntities.push_back(hit.entityPtr);
 }
 }

 return result;
}

void WorldCollisionSystem::registerEntity(float x, float y, int z, float width, float height,
 bool solid, void* entityPtr) {
 grid.registerCollision(x, y, z, width, height, solid, entityPtr);
}

void WorldCollisionSystem::unregisterEntity(void* entityPtr) {
 (void)entityPtr;
 // Would need entity tracking to unregister properly
 // For now, relies on buildCollisionGrid being called to refresh
}

void WorldCollisionSystem::updateEntityPosition(void* entityPtr, float newX, float newY, int z) {
 // Unregister at old position, register at new
 // This is simplified - full implementation would track entity positions
 unregisterEntity(entityPtr);
 registerEntity(newX, newY, z, 0.5f, 0.5f, false, entityPtr);
}

bool WorldCollisionSystem::hasLineOfSight(float x1, float y1, float x2, float y2, int z) {
 // Bresenham line algorithm to check line of sight
 // Returns true if line is clear (no solid obstacles)
 
 int dx = (int)std::abs(x2 - x1);
 int dy = (int)std::abs(y2 - y1);
 int sx = (x1 < x2) ? 1 : -1;
 int sy = (y1 < y2) ? 1 : -1;
 int err = dx - dy;

 float curX = x1;
 float curY = y1;

 while (true) {
 // Check collision at current position
 if (!isWalkable(curX, curY, z)) {
 return false;
 }

 if ((int)curX == (int)x2 && (int)curY == (int)y2) {
 break;
 }

 int e2 = 2 * err;
 if (e2 > -dy) {
 err -= dy;
 curX += sx;
 }
 if (e2 < dx) {
 err += dx;
 curY += sy;
 }
 }

 return true;
}
