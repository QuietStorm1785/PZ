#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>

class IsoGridSquare;

/**
 * Pathfinding Priority Levels
 * Used to prioritize urgent pathfinding requests over background tasks
 */
enum class PathPriority : int {
    BACKGROUND_MIN = 0,      // Lowest priority background tasks
    BACKGROUND_LOW = 1,      // Background zombie pathfinding (far)
    BACKGROUND_MED = 2,      // Background zombie pathfinding (medium)
    NPC_LOW = 3,             // NPC behavior (not urgent)
    NPC_MEDIUM = 4,          // NPC behavior (medium urgency)
    NPC_NORMAL = 5,          // NPC behavior (default)
    NPC_HIGH = 6,            // NPC behavior (important)
    NPC_URGENT = 7,          // NPC behavior (very urgent)
    THREAT_NEAR = 8,         // Nearby threats (close zombies)
    THREAT_IMMEDIATE = 9,    // Immediate threats (very close)
    THREAT_CRITICAL = 10     // Critical threats (player/ally in danger)
};

/**
 * PathNode - Represents a single node in pathfinding grid
 */
struct PathNode {
    int x, y, z;
    float gCost;  // Cost from start
    float hCost;  // Heuristic cost to goal
    float fCost;  // gCost + hCost
    PathNode* parent;

    PathNode(int x, int y, int z) : x(x), y(y), z(z), gCost(0), hCost(0), fCost(0), parent(nullptr) {}
};

/**
 * PathRequest - Async pathfinding request
 */
struct PathRequest {
    int id;
    float startX, startY, startZ;
    float endX, endY, endZ;
    float maxDistance;
    std::vector<std::pair<int, int>> result;
    bool completed;
    bool success;
    int priority;  // 0 = lowest, higher = more important

    // Default constructor
    PathRequest() : id(0), startX(0), startY(0), startZ(0), endX(0), endY(0), endZ(0),
                   maxDistance(1000.0f), result(), completed(false), success(false), priority(5) {}

    PathRequest(int id, float sx, float sy, float sz, float ex, float ey, float ez, float maxDist = 1000.0f, int prio = 5)
        : id(id), startX(sx), startY(sy), startZ(sz), endX(ex), endY(ey), endZ(ez),
          maxDistance(maxDist), result(), completed(false), success(false), priority(prio) {}
};

/**
 * PathfindingThreadPool - Multi-threaded A* pathfinding
 * 
 * Manages a pool of worker threads for asynchronous pathfinding requests.
 * Prevents main game thread blocking during complex pathfinding.
 * 
 * Example:
 *   PathfindingThreadPool::getInstance()->requestPath(startX, startY, startZ, endX, endY, endZ);
 *   auto result = PathfindingThreadPool::getInstance()->getResult(requestId);
 */
class PathfindingThreadPool {
public:
    static const int DEFAULT_THREAD_COUNT = 4;
    static const int REQUEST_QUEUE_SIZE = 128;

    /**
     * Get singleton instance
     */
    static PathfindingThreadPool* getInstance();

    /**
     * Get optimal thread count based on system hardware
     * @return Recommended number of threads (DEFAULT_THREAD_COUNT if detection fails)
     */
    static int getOptimalThreadCount();

    /**
     * Calculate pathfinding priority based on distance to target
     * @param distance - Distance to target in tiles
     * @param isPlayerTarget - True if target is player (higher priority)
     * @return Priority level (0-10)
     */
    static int calculatePriorityByDistance(float distance, bool isPlayerTarget = false);

    /**
     * Initialize thread pool with specified number of workers
     * @param threadCount - Number of worker threads (0 = auto-detect)
     */
    bool initialize(int threadCount = 0);

    /**
     * Shutdown thread pool gracefully
     */
    void shutdown();

    /**
     * Request async pathfinding
     * @param startX, startY, startZ - Starting position
     * @param endX, endY, endZ - Target position
     * @param maxDistance - Maximum path search distance
     * @param priority - Request priority (0-10, higher = sooner)
     * @return Request ID for later retrieval
     */
    int requestPath(float startX, float startY, float startZ,
                   float endX, float endY, float endZ,
                   float maxDistance = 1000.0f, int priority = 5);

    /**
     * Get result of completed pathfinding request
     * @param requestId - ID from requestPath()
     * @return Path as vector of (x,y) coordinates, empty if not ready
     */
    std::vector<std::pair<int, int>> getResult(int requestId);

    /**
     * Check if request is complete
     * @param requestId - ID from requestPath()
     * @return true if result is ready
     */
    bool isPathReady(int requestId);

    /**
     * Cancel pending request
     */
    void cancelRequest(int requestId);

    /**
     * Get queue statistics
     */
    int getPendingRequestCount() const;
    int getCompletedRequestCount() const;

    /**
     * Clear old completed requests (memory management)
     * @param maxAge - Maximum age in seconds before cleanup (default: 10s)
     */
    void clearOldRequests(float maxAge = 10.0f);

    /**
     * Get queue health metrics
     * @return true if queue is healthy, false if bottlenecked
     */
    bool isQueueHealthy() const;

    /**
     * Get average queue wait time estimate
     */
    float getAverageWaitTime() const;

private:
    PathfindingThreadPool();
    ~PathfindingThreadPool();

    /**
     * Worker thread function
     */
    void workerThread();

    /**
     * Compute path using A* algorithm
     */
    bool computePath(const PathRequest& request, std::vector<std::pair<int, int>>& outPath);

    /**
     * A* heuristic (Manhattan distance)
     */
    static float heuristic(int x1, int y1, int x2, int y2);

    /**
     * Get terrain cost for movement
     */
    static float getTerrainCost(IsoGridSquare* square);

    /**
     * Check if square is walkable
     */
    static bool isWalkable(IsoGridSquare* square);

    /**
     * PathNode object pool for memory reuse
     */
    struct Node {
        int x, y;
        float gCost, hCost, fCost;
        Node* parent;
        Node() : x(0), y(0), gCost(0), hCost(0), fCost(0), parent(nullptr) {}
    };

    Node* allocateNode();
    void releaseNode(Node* node);
    void clearNodePool();

    std::vector<std::thread> workers;
    std::queue<PathRequest> requestQueue;
    std::unordered_map<int, PathRequest> completedRequests;
    std::unordered_map<int, std::chrono::steady_clock::time_point> requestTimestamps;
    mutable std::mutex queueMutex;
    mutable std::mutex resultMutex;
    mutable std::mutex poolMutex;
    bool running;
    int nextRequestId;
    int completedCount;

    // Object pool for PathNode reuse
    std::vector<Node*> nodePool;
    std::vector<Node*> activeNodes;

    // Queue monitoring
    static constexpr int MAX_HEALTHY_QUEUE_SIZE = 50;
    static constexpr float WARNING_WAIT_TIME = 2.0f;  // seconds

    static PathfindingThreadPool* instance;
};

/**
 * AsyncPathfinder - Wrapper for easy async pathfinding
 * 
 * Higher-level API for pathfinding requests with callback support.
 */
class AsyncPathfinder {
public:
    using PathCallback = std::function<void(int, const std::vector<std::pair<int, int>>&)>;

    /**
     * Request path with callback
     * @param startX, startY, startZ - Start position
     * @param endX, endY, endZ - End position
     * @param callback - Called when path is ready
     * @param priority - Request priority
     * @return Request ID
     */
    static int requestPathWithCallback(float startX, float startY, float startZ,
                                       float endX, float endY, float endZ,
                                       const PathCallback& callback,
                                       int priority = 5);

    /**
     * Update callbacks for completed requests
     * (Call this periodically from main thread)
     */
    static void updateCallbacks();

    /**
     * Cancel request with callback
     */
    static void cancelRequest(int requestId);

private:
    static std::unordered_map<int, PathCallback> callbacks;
    static std::mutex callbackMutex;
};
