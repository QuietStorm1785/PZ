#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <cmath>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <functional>
#include <list>
#include "Terrain.h"

namespace zombie {
namespace pathfinding {

struct Vec3 {
 float x, y, z;
 Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
 
 bool operator==(const Vec3& other) const {
 return x == other.x && y == other.y && z == other.z;
 }
};

struct PathNode {
 int x, y, z;
 float g, h, f; // g=cost from start, h=heuristic, f=g+h
 PathNode* parent;
 
 PathNode(int px, int py, int pz) : x(px), y(py), z(pz), g(0), h(0), f(0), parent(nullptr) {}
 
 bool operator<(const PathNode& other) const {
 return f > other.f; // For priority queue (min-heap)
 }
 
 int getHash() const {
 return x + y * 300 + z * 90000; // Assuming max 300x300x100
 }
};

struct PathResult {
 std::vector<Vec3> waypoints;
 bool found;
 float length;
 int nodeCount;
 float searchTime;
 
 PathResult() : found(false), length(0.0f), nodeCount(0), searchTime(0.0f) {}
};

class AStarPathfinder {
public:
 AStarPathfinder(int mapWidth, int mapHeight, int mapDepth);
 ~AStarPathfinder();
 
 PathResult findPath(Vec3 start, Vec3 goal);
 PathResult findPath(int startX, int startY, int startZ, int goalX, int goalY, int goalZ);
 
 void setWalkable(int x, int y, int z, bool walkable);
 bool isWalkable(int x, int y, int z) const;

 // Provide custom neighbor expansion (e.g., IsoGridSquare neighbor pointers)
 using NeighborProvider = std::function<void(int,int,int,std::vector<Vec3>&)>;
 void setNeighborProvider(NeighborProvider provider) { neighborProvider = std::move(provider); }
 void clearNeighborProvider() { neighborProvider = nullptr; }

 // Path cache control
 void setCacheSize(size_t entries) { maxCacheEntries = entries; trimCache(); }
 void clearCache() { cache.clear(); lruOrder.clear(); }
 
 // Configure pathfinding behavior
 void setMaxIterations(int max) { maxIterations = max; }
 void setDiagonalMovement(bool allow) { allowDiagonal = allow; }
 
 // Heuristic distance (Manhattan or Euclidean)
 float heuristic(Vec3 from, Vec3 to) const;
 
private:
 int width, height, depth;
 std::vector<bool> walkableMap;
 int maxIterations;
 bool allowDiagonal;

 // Path cache keyed by start/goal and invalidated by generation bumps
 struct CacheKey {
 int sx, sy, sz, gx, gy, gz;
 bool operator==(const CacheKey& other) const {
 return sx == other.sx && sy == other.sy && sz == other.sz &&
 gx == other.gx && gy == other.gy && gz == other.gz;
 }
 };

 struct CacheKeyHash {
 size_t operator()(const CacheKey& k) const {
 // Mix coordinates into a hash; small world sizes keep collisions low
 size_t h1 = std::hash<int>()(k.sx * 73856093 ^ k.sy * 19349663 ^ k.sz * 83492791);
 size_t h2 = std::hash<int>()(k.gx * 1645333507 ^ k.gy * 2654435761 ^ k.gz * 889523);
 return h1 ^ (h2 << 1);
 }
 };

 struct CacheEntry {
 PathResult result;
 uint64_t generation;
 std::list<CacheKey>::iterator lruIt;
 };

 std::unordered_map<CacheKey, CacheEntry, CacheKeyHash> cache;
 std::list<CacheKey> lruOrder;
 size_t maxCacheEntries = 128;
 uint64_t generation = 1; // Bumped on walkability change
 NeighborProvider neighborProvider;
 
 float getDistance(Vec3 a, Vec3 b) const;
 float getMoveCost(int x1, int y1, int z1, int x2, int y2, int z2) const;
 std::vector<Vec3> reconstructPath(PathNode* endNode);
 std::vector<Vec3> gatherNeighbors(PathNode* node);
 bool isValid(int x, int y, int z) const;
 void cleanupNodes(std::vector<PathNode*>& nodes);
 void bumpGeneration();
 bool tryGetCached(const CacheKey& key, PathResult& out) const;
 void storeCache(const CacheKey& key, const PathResult& result);
 void touchCache(CacheEntry& entry);
 void trimCache();
};

} // namespace pathfinding
} // namespace zombie
