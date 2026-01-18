#include "Pathfinding.h"
#include <cmath>
#include <algorithm>
#include <chrono>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace zombie {
namespace pathfinding {

// Custom comparator for PathNode in priority queue (lower f-score first)
struct PathNodeCompare {
    bool operator()(PathNode* a, PathNode* b) const {
        return a->f > b->f; // min-heap
    }
};

AStarPathfinder::AStarPathfinder(int mapWidth, int mapHeight, int mapDepth)
    : width(mapWidth)
    , height(mapHeight)
    , depth(mapDepth)
    , maxIterations(10000)
    , allowDiagonal(true) {
    walkableMap.resize(width * height * depth, true);
}

AStarPathfinder::~AStarPathfinder() {
}

PathResult AStarPathfinder::findPath(Vec3 start, Vec3 goal) {
    return findPath((int)start.x, (int)start.y, (int)start.z,
                    (int)goal.x, (int)goal.y, (int)goal.z);
}

PathResult AStarPathfinder::findPath(int startX, int startY, int startZ, int goalX, int goalY, int goalZ) {
    auto startTime = std::chrono::high_resolution_clock::now();
    PathResult result;

    CacheKey cacheKey{startX, startY, startZ, goalX, goalY, goalZ};
    if (tryGetCached(cacheKey, result)) {
        result.searchTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - startTime).count();
        return result;
    }
    
    // Validate start and goal
    if (!isValid(startX, startY, startZ) || !isValid(goalX, goalY, goalZ)) {
        result.found = false;
        result.nodeCount = 0;
        result.searchTime = 0.0f;
        return result;
    }
    
    // If start equals goal
    if (startX == goalX && startY == goalY && startZ == goalZ) {
        result.waypoints.push_back(Vec3(startX, startY, startZ));
        result.found = true;
        result.length = 0.0f;
        result.nodeCount = 1;
        result.searchTime = 0.0f;
        return result;
    }
    
    // Create node lookup
    std::unordered_map<int, PathNode*> nodeMap;
    std::vector<PathNode*> allNodes;

    auto getNode = [&](int x, int y, int z) -> PathNode* {
        int hash = x + y * width + z * width * height;
        auto it = nodeMap.find(hash);
        if (it != nodeMap.end()) {
            return it->second;
        }
        PathNode* node = new PathNode(x, y, z);
        node->g = -1.0f; // mark as unvisited
        nodeMap[hash] = node;
        allNodes.push_back(node);
        return node;
    };
    
    // Initialize open and closed sets
    std::priority_queue<PathNode*, std::vector<PathNode*>, PathNodeCompare> openSet;
    std::unordered_set<int> closedSet;
    
    // Create start node
    PathNode* startNode = getNode(startX, startY, startZ);
    startNode->g = 0.0f;
    startNode->h = heuristic(Vec3(startX, startY, startZ), Vec3(goalX, goalY, goalZ));
    startNode->f = startNode->g + startNode->h;
    
    openSet.push(startNode);
    
    PathNode* goalNode = nullptr;
    int iterations = 0;
    
    while (!openSet.empty() && iterations < maxIterations) {
        iterations++;
        
        // Get node with lowest f score
        PathNode* current = openSet.top();
        openSet.pop();
        
        // Skip if already processed
        int currentHash = current->x + current->y * width + current->z * width * height;
        if (closedSet.find(currentHash) != closedSet.end()) {
            continue;
        }
        
        // Goal reached
        if (current->x == goalX && current->y == goalY && current->z == goalZ) {
            goalNode = current;
            break;
        }
        
        // Add to closed set
        closedSet.insert(currentHash);
        
        // Explore neighbors (coordinates only)
        std::vector<Vec3> neighbors = gatherNeighbors(current);

        for (const auto& n : neighbors) {
            int nx = static_cast<int>(n.x);
            int ny = static_cast<int>(n.y);
            int nz = static_cast<int>(n.z);
            int neighborHash = nx + ny * width + nz * width * height;

            if (closedSet.find(neighborHash) != closedSet.end()) {
                continue; // Already evaluated
            }

            float tentativeG = current->g + getMoveCost(current->x, current->y, current->z, nx, ny, nz);

            // Get or create neighbor in map
            PathNode* mapNeighbor = getNode(nx, ny, nz);

            if (mapNeighbor->g < 0 || tentativeG < mapNeighbor->g) {
                // New or better path
                mapNeighbor->parent = current;
                mapNeighbor->g = tentativeG;
                mapNeighbor->h = heuristic(Vec3(mapNeighbor->x, mapNeighbor->y, mapNeighbor->z),
                                          Vec3(goalX, goalY, goalZ));
                mapNeighbor->f = mapNeighbor->g + mapNeighbor->h;
                openSet.push(mapNeighbor);
            }
        }
    }
    
    // Reconstruct path if goal found
    if (goalNode) {
        result.waypoints = reconstructPath(goalNode);
        result.found = true;
        
        // Calculate path length
        result.length = 0.0f;
        for (size_t i = 1; i < result.waypoints.size(); ++i) {
            result.length += getDistance(result.waypoints[i-1], result.waypoints[i]);
        }
    } else {
        result.found = false;
    }
    
    result.nodeCount = iterations;
    
    // Cleanup all allocated nodes
    for (auto node : allNodes) {
        delete node;
    }
    allNodes.clear();
    nodeMap.clear();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    result.searchTime = std::chrono::duration<float>(endTime - startTime).count();

    storeCache(cacheKey, result);
    
    return result;
}

void AStarPathfinder::setWalkable(int x, int y, int z, bool walkable) {
    if (isValid(x, y, z)) {
        walkableMap[x + y * width + z * width * height] = walkable;
        bumpGeneration();
    }
}

bool AStarPathfinder::isWalkable(int x, int y, int z) const {
    if (isValid(x, y, z)) {
        return walkableMap[x + y * width + z * width * height];
    }
    return false;
}

float AStarPathfinder::heuristic(Vec3 from, Vec3 to) const {
    // Euclidean distance heuristic (admissible for A*)
    float dx = from.x - to.x;
    float dy = from.y - to.y;
    float dz = from.z - to.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float AStarPathfinder::getDistance(Vec3 a, Vec3 b) const {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float AStarPathfinder::getMoveCost(int x1, int y1, int z1, int x2, int y2, int z2) const {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int dz = std::abs(z2 - z1);

    int steps = dx + dy + dz;
    if (steps == 0) return 0.0f;

    // Base cost: diagonal in 2D costs sqrt(2); vertical adds linear cost
    float baseCost = 1.0f;
    if (allowDiagonal && dx == 1 && dy == 1 && dz == 0) {
        baseCost = 1.41421356f;
    } else {
        baseCost = 1.0f * steps;
    }

    // Apply terrain cost multiplier from destination square
    float terrainMult = 1.0f; // default
    TerrainType destTerrain = TerrainType::GRASS; // default
    
    // Note: terrain costs can be retrieved from IsoGridSquare if available in world context
    // For now, we use a default multiplier. In integrated version, query actual terrain:
    // IsoGridSquare* sq = world->getGridSquare(x2, y2, z2);
    // if (sq) terrainMult = getTerrainCost(sq->getTerrain());
    
    return baseCost * terrainMult;
}

std::vector<Vec3> AStarPathfinder::reconstructPath(PathNode* endNode) {
    std::vector<Vec3> path;
    PathNode* current = endNode;
    
    while (current) {
        path.insert(path.begin(), Vec3(current->x, current->y, current->z));
        current = current->parent;
    }
    
    return path;
}

std::vector<Vec3> AStarPathfinder::gatherNeighbors(PathNode* node) {
    std::vector<Vec3> neighbors;

    if (neighborProvider) {
        neighborProvider(node->x, node->y, node->z, neighbors);
        return neighbors;
    }

    // Default: 2D 8-way (plus vertical if depth >1)
    static const int dirs2D[8][2] = {
        {-1,  0}, {1,  0}, {0, -1}, {0, 1},
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
    };

    for (int i = 0; i < 8; ++i) {
        int nx = node->x + dirs2D[i][0];
        int ny = node->y + dirs2D[i][1];
        int nz = node->z;

        if (!allowDiagonal && i >= 4) continue; // skip diagonals when disabled

        if (isValid(nx, ny, nz) && isWalkable(nx, ny, nz)) {
            neighbors.emplace_back(static_cast<float>(nx), static_cast<float>(ny), static_cast<float>(nz));
        }
    }

    // Vertical movement (stairs/levels) if depth > 1
    if (depth > 1) {
        const int zDirs[2] = {-1, 1};
        for (int dz : zDirs) {
            int nz = node->z + dz;
            if (isValid(node->x, node->y, nz) && isWalkable(node->x, node->y, nz)) {
                neighbors.emplace_back(static_cast<float>(node->x), static_cast<float>(node->y), static_cast<float>(nz));
            }
        }
    }

    return neighbors;
}

bool AStarPathfinder::isValid(int x, int y, int z) const {
    return x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth;
}

void AStarPathfinder::cleanupNodes(std::vector<PathNode*>& nodes) {
    for (auto node : nodes) {
        if (node) {
            delete node;
        }
    }
    nodes.clear();
}

void AStarPathfinder::bumpGeneration() {
    generation++;
    clearCache();
}

bool AStarPathfinder::tryGetCached(const CacheKey& key, PathResult& out) const {
    auto it = cache.find(key);
    if (it == cache.end()) return false;
    const CacheEntry& entry = it->second;
    if (entry.generation != generation) return false;
    out = entry.result;
    return true;
}

void AStarPathfinder::storeCache(const CacheKey& key, const PathResult& result) {
    // Evict if needed
    trimCache();

    auto it = cache.find(key);
    if (it != cache.end()) {
        it->second.result = result;
        it->second.generation = generation;
        touchCache(it->second);
        return;
    }

    lruOrder.push_front(key);
    CacheEntry entry{result, generation, lruOrder.begin()};
    cache[key] = entry;
    trimCache();
}

void AStarPathfinder::touchCache(CacheEntry& entry) {
    lruOrder.splice(lruOrder.begin(), lruOrder, entry.lruIt);
    entry.lruIt = lruOrder.begin();
}

void AStarPathfinder::trimCache() {
    while (cache.size() > maxCacheEntries && !lruOrder.empty()) {
        CacheKey oldest = lruOrder.back();
        lruOrder.pop_back();
        cache.erase(oldest);
    }
}

} // namespace pathfinding
} // namespace zombie
