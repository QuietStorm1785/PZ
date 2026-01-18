#include "VisibilitySystem.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoPlayer.h"
#include "IsoCell.h"
#include "Terrain.h"
#include <cmath>
#include <algorithm>

// VisibilityChecker Implementation
VisibilityChecker::VisibilityChecker() : cacheHits(0), cacheMisses(0), world(nullptr) {}

VisibilityChecker::~VisibilityChecker() {
 clearCache();
}

bool VisibilityChecker::canSee(float x1, float y1, float x2, float y2, int z) {
 // Create cache key
 int key = static_cast<int>(x1) * 73856093 ^ static_cast<int>(y1) * 19349663 ^ 
 static_cast<int>(x2) * 83492791 ^ static_cast<int>(y2) * 12982917 ^ z * 7919;
 
 auto it = visibilityCache.find(key);
 if (it != visibilityCache.end()) {
 cacheHits++;
 return it->second;
 }
 
 cacheMisses++;
 
 // Perform raycasting
 auto rayPoints = traceRay(x1, y1, x2, y2);
 
 bool blocked = false;
 for (const auto& point : rayPoints) {
 // Skip start point
 if (point.first == static_cast<int>(x1) && point.second == static_cast<int>(y1)) {
 continue;
 }
 
 // Get grid square at this point
 if (world) {
 IsoGridSquare* square = world->getGridSquare(point.first, point.second, z);
 if (isOccluding(square)) {
 blocked = true;
 break;
 }
 }
 }
 
 bool result = !blocked; // Can see if no obstruction found
 visibilityCache[key] = result;
 return result;
}

bool VisibilityChecker::canSeeObject(zombie::characters::IsoPlayer* observer, IsoObject* object, float maxDistance) {
 if (!observer || !object) return false;
 
 // Get observer position
 float observerX = observer->getX();
 float observerY = observer->getY();
 int observerZ = observer->getCurrentZ();
 
 float dx = object->getX() - observerX;
 float dy = object->getY() - observerY;
 float distance = std::sqrt(dx * dx + dy * dy);
 
 if (distance > maxDistance) return false;
 
 // Check line of sight from observer to object
 return canSee(observerX, observerY, object->getX(), object->getY(), observerZ);
}

std::vector<IsoObject*> VisibilityChecker::getVisibleObjects(float x, float y, int z, float radius, int maxObjects) {
 std::vector<IsoObject*> visible;
 
 if (!world) return visible;
 
 // Query the world for objects within radius
 // This would typically use a spatial partitioning structure for efficiency
 // For now, we'll iterate through loaded chunks near the position
 
 int centerChunkX = static_cast<int>(x) / 10; // Assuming 10x10 chunks
 int centerChunkY = static_cast<int>(y) / 10;
 int chunkRadius = static_cast<int>(radius / 10) + 1;
 
 // Scan nearby chunks
 for (int cy = centerChunkY - chunkRadius; cy <= centerChunkY + chunkRadius; cy++) {
 for (int cx = centerChunkX - chunkRadius; cx <= centerChunkX + chunkRadius; cx++) {
 // Get grid squares in this chunk and check for objects
 for (int ly = 0; ly < 10; ly++) {
 for (int lx = 0; lx < 10; lx++) {
 int worldX = cx * 10 + lx;
 int worldY = cy * 10 + ly;
 
 const IsoGridSquare* square = world->getGridSquare(worldX, worldY, z);
 if (!square) continue;
 
 // Check objects in this square
 // TODO: Need to add getObjects() method to IsoGridSquare
 // For now, this is a framework that would be completed when
 // IsoGridSquare has a proper object collection
 
 if (static_cast<int>(visible.size()) >= maxObjects) {
 return visible;
 }
 }
 }
 }
 }
 
 return visible;
}

std::vector<std::pair<int, int>> VisibilityChecker::traceRay(float x1, float y1, float x2, float y2) {
 std::vector<std::pair<int, int>> points;
 
 // Bresenham's line algorithm
 int x0 = static_cast<int>(x1);
 int y0 = static_cast<int>(y1);
 int x3 = static_cast<int>(x2);
 int y3 = static_cast<int>(y2);
 
 int dx = std::abs(x3 - x0);
 int dy = std::abs(y3 - y0);
 int sx = (x0 < x3) ? 1 : -1;
 int sy = (y0 < y3) ? 1 : -1;
 int err = dx - dy;
 
 int x = x0, y = y0;
 
 while (true) {
 points.push_back({x, y});
 
 if (x == x3 && y == y3) break;
 
 int e2 = 2 * err;
 if (e2 > -dy) {
 err -= dy;
 x += sx;
 }
 if (e2 < dx) {
 err += dx;
 y += sy;
 }
 }
 
 return points;
}

bool VisibilityChecker::isOccluding(IsoGridSquare* square) {
 if (!square) return false;
 
 // Check if square itself blocks vision (walls, solid terrain)
 if (!square->isFree()) {
 return true; // Square is blocked
 }
 
 // Check for solid objects that block vision
 const auto& objects = square->getObjects();
 for (IsoObject* obj : objects) {
 if (obj && obj->isSolid()) {
 // Solid objects (walls, large furniture) block vision
 return true;
 }
 }
 
 // Note: Terrain types don't block vision in this system.
 // Vision blocking is handled by solid objects and square walkability.
 
 return false; // Square does not block vision
}

void VisibilityChecker::clearCache() {
 visibilityCache.clear();
 cacheHits = 0;
 cacheMisses = 0;
}

int VisibilityChecker::getCacheHitRate() const {
 int total = cacheHits + cacheMisses;
 if (total == 0) return 0;
 return (cacheHits * 100) / total;
}

// FogOfWarSystem Implementation
FogOfWarSystem::FogOfWarSystem(int gridWidth, int gridHeight, int gridDepth)
 : gridWidth(gridWidth), gridHeight(gridHeight), gridDepth(gridDepth) {
 
 // Initialize fog of war grid
 fogGrid.resize(gridWidth);
 for (int x = 0; x < gridWidth; x++) {
 fogGrid[x].resize(gridHeight);
 for (int y = 0; y < gridHeight; y++) {
 fogGrid[x][y].resize(gridDepth);
 for (int z = 0; z < gridDepth; z++) {
 fogGrid[x][y][z] = FogState::UNEXPLORED;
 }
 }
 }
}

FogOfWarSystem::~FogOfWarSystem() {
 fogGrid.clear();
}

void FogOfWarSystem::updateVisibility(float observerX, float observerY, int observerZ, float visionRadius) {
 int obsX = static_cast<int>(observerX);
 int obsY = static_cast<int>(observerY);
 
 // Mark all cells within vision radius
 for (int x = -static_cast<int>(visionRadius); x <= static_cast<int>(visionRadius); x++) {
 for (int y = -static_cast<int>(visionRadius); y <= static_cast<int>(visionRadius); y++) {
 int gridX = obsX + x;
 int gridY = obsY + y;
 
 if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
 float dx = static_cast<float>(x);
 float dy = static_cast<float>(y);
 float distance = std::sqrt(dx * dx + dy * dy);
 
 if (distance <= visionRadius) {
 // Check line of sight
 VisibilityChecker checker;
 if (checker.canSee(observerX, observerY, gridX, gridY, observerZ)) {
 setFogState(gridX, gridY, observerZ, FogState::VISIBLE);
 setExplored(gridX, gridY, observerZ);
 }
 }
 }
 }
 }
 
 // Mark previously visible cells as explored (but not visible)
 for (int x = 0; x < gridWidth; x++) {
 for (int y = 0; y < gridHeight; y++) {
 if (fogGrid[x][y][observerZ] == FogState::VISIBLE) {
 float dx = static_cast<float>(x - obsX);
 float dy = static_cast<float>(y - obsY);
 float distance = std::sqrt(dx * dx + dy * dy);
 
 if (distance > visionRadius) {
 setFogState(x, y, observerZ, FogState::EXPLORED);
 }
 }
 }
 }
}

FogOfWarSystem::FogState FogOfWarSystem::getFogState(int x, int y, int z) const {
 if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight && z >= 0 && z < gridDepth) {
 return fogGrid[x][y][z];
 }
 return FogState::UNEXPLORED;
}

void FogOfWarSystem::setFogState(int x, int y, int z, FogState state) {
 if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight && z >= 0 && z < gridDepth) {
 fogGrid[x][y][z] = state;
 }
}

void FogOfWarSystem::setExplored(int x, int y, int z) {
 FogState current = getFogState(x, y, z);
 if (current == FogState::UNEXPLORED) {
 setFogState(x, y, z, FogState::EXPLORED);
 }
}

float FogOfWarSystem::getExploredPercentage() const {
 int explored = 0;
 int total = gridWidth * gridHeight * gridDepth;
 
 for (int x = 0; x < gridWidth; x++) {
 for (int y = 0; y < gridHeight; y++) {
 for (int z = 0; z < gridDepth; z++) {
 if (fogGrid[x][y][z] != FogState::UNEXPLORED) {
 explored++;
 }
 }
 }
 }
 
 return (total > 0) ? (100.0f * explored / total) : 0.0f;
}
