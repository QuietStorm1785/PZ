#include "PathfindingThreadPool.h"
#include "IsoGridSquare.h"
#include <queue>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include <unordered_set>

PathfindingThreadPool* PathfindingThreadPool::instance = nullptr;

PathfindingThreadPool* PathfindingThreadPool::getInstance() {
 if (!instance) {
 instance = new PathfindingThreadPool();
 }
 return instance;
}

PathfindingThreadPool::PathfindingThreadPool()
 : running(false), nextRequestId(0), completedCount(0) {}

PathfindingThreadPool::~PathfindingThreadPool() {
 shutdown();
}

int PathfindingThreadPool::getOptimalThreadCount() {
 // Get hardware concurrency (CPU cores)
 unsigned int hwCores = std::thread::hardware_concurrency();
 
 if (hwCores == 0) {
 // Detection failed, use default
 return DEFAULT_THREAD_COUNT;
 }
 
 // Use half the cores for pathfinding (leave rest for game logic)
 // Min 2 threads, max 8 threads
 int optimalThreads = std::max(2, std::min(8, static_cast<int>(hwCores) / 2));
 
 return optimalThreads;
}

int PathfindingThreadPool::calculatePriorityByDistance(float distance, bool isPlayerTarget) {
 // Distance thresholds (in tiles)
 const float CRITICAL_RANGE = 5.0f; // Immediate threat
 const float NEAR_RANGE = 15.0f; // Nearby threat
 const float MEDIUM_RANGE = 30.0f; // Medium distance
 const float FAR_RANGE = 50.0f; // Far distance
 
 int basePriority;
 
 if (distance < CRITICAL_RANGE) {
 // Critical range: 8-10
 basePriority = static_cast<int>(PathPriority::THREAT_NEAR) + 
 static_cast<int>((CRITICAL_RANGE - distance) / CRITICAL_RANGE * 2.0f);
 } else if (distance < NEAR_RANGE) {
 // Near range: 6-8
 basePriority = static_cast<int>(PathPriority::NPC_HIGH) + 
 static_cast<int>((NEAR_RANGE - distance) / (NEAR_RANGE - CRITICAL_RANGE) * 2.0f);
 } else if (distance < MEDIUM_RANGE) {
 // Medium range: 4-6
 basePriority = static_cast<int>(PathPriority::NPC_MEDIUM) + 
 static_cast<int>((MEDIUM_RANGE - distance) / (MEDIUM_RANGE - NEAR_RANGE) * 2.0f);
 } else if (distance < FAR_RANGE) {
 // Far range: 2-4
 basePriority = static_cast<int>(PathPriority::BACKGROUND_MED) + 
 static_cast<int>((FAR_RANGE - distance) / (FAR_RANGE - MEDIUM_RANGE) * 2.0f);
 } else {
 // Very far: 0-2
 basePriority = static_cast<int>(PathPriority::BACKGROUND_MIN);
 }
 
 // Boost priority if target is player
 if (isPlayerTarget) {
 basePriority = std::min(10, basePriority + 2);
 }
 
 // Clamp to valid range [0-10]
 return std::max(0, std::min(10, basePriority));
}

bool PathfindingThreadPool::initialize(int threadCount) {
 if (running) return false;
 
 // Auto-detect if threadCount is 0
 if (threadCount <= 0) {
 threadCount = getOptimalThreadCount();
 }
 
 running = true;
 for (int i = 0; i < threadCount; i++) {
 workers.emplace_back(&PathfindingThreadPool::workerThread, this);
 }
 
 return true;
}

void PathfindingThreadPool::shutdown() {
 running = false;
 for (auto& worker : workers) {
 if (worker.joinable()) {
 worker.join();
 }
 }
 workers.clear();
 clearNodePool();
}

PathfindingThreadPool::Node* PathfindingThreadPool::allocateNode() {
 std::lock_guard<std::mutex> lock(poolMutex);
 
 Node* node;
 if (!nodePool.empty()) {
 // Reuse from pool
 node = nodePool.back();
 nodePool.pop_back();
 // Reset node
 node->x = node->y = 0;
 node->gCost = node->hCost = node->fCost = 0.0f;
 node->parent = nullptr;
 } else {
 // Allocate new node
 node = new Node();
 }
 
 activeNodes.push_back(node);
 return node;
}

void PathfindingThreadPool::releaseNode(Node* node) {
 if (!node) return;
 
 std::lock_guard<std::mutex> lock(poolMutex);
 
 // Remove from active list
 auto it = std::find(activeNodes.begin(), activeNodes.end(), node);
 if (it != activeNodes.end()) {
 activeNodes.erase(it);
 }
 
 // Return to pool (limit pool size to prevent unbounded growth)
 if (nodePool.size() < 10000) { // Max 10k cached nodes
 nodePool.push_back(node);
 } else {
 delete node;
 }
}

void PathfindingThreadPool::clearNodePool() {
 std::lock_guard<std::mutex> lock(poolMutex);
 
 // Delete all pooled nodes
 for (auto* node : nodePool) {
 delete node;
 }
 nodePool.clear();
 
 // Delete all active nodes (should be empty after path completion)
 for (auto* node : activeNodes) {
 delete node;
 }
 activeNodes.clear();
}

int PathfindingThreadPool::requestPath(float startX, float startY, float startZ,
 float endX, float endY, float endZ,
 float maxDistance, int priority) {
 int requestId = nextRequestId++;
 
 PathRequest request(requestId, startX, startY, startZ, endX, endY, endZ, maxDistance, priority);
 
 {
 std::lock_guard<std::mutex> lock(queueMutex);
 requestQueue.push(request);
 requestTimestamps[requestId] = std::chrono::steady_clock::now();
 }
 
 return requestId;
}

void PathfindingThreadPool::clearOldRequests(float maxAge) {
 std::lock_guard<std::mutex> lock(resultMutex);
 
 auto now = std::chrono::steady_clock::now();
 std::vector<int> toRemove;
 
 for (const auto& pair : requestTimestamps) {
 auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - pair.second).count();
 if (elapsed > maxAge) {
 toRemove.push_back(pair.first);
 }
 }
 
 for (int id : toRemove) {
 completedRequests.erase(id);
 requestTimestamps.erase(id);
 }
}

bool PathfindingThreadPool::isQueueHealthy() const {
 std::lock_guard<std::mutex> lock(queueMutex);
 return requestQueue.size() < MAX_HEALTHY_QUEUE_SIZE;
}

float PathfindingThreadPool::getAverageWaitTime() const {
 std::lock_guard<std::mutex> lock(resultMutex);
 
 if (completedRequests.empty()) {
 return 0.0f;
 }
 
 auto now = std::chrono::steady_clock::now();
 float totalWaitTime = 0.0f;
 int count = 0;
 
 for (const auto& pair : completedRequests) {
 auto it = requestTimestamps.find(pair.first);
 if (it != requestTimestamps.end()) {
 auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second).count();
 totalWaitTime += elapsed / 1000.0f; // Convert to seconds
 count++;
 }
 }
 
 return count > 0 ? totalWaitTime / count : 0.0f;
}

std::vector<std::pair<int, int>> PathfindingThreadPool::getResult(int requestId) {
 std::lock_guard<std::mutex> lock(resultMutex);
 
 auto it = completedRequests.find(requestId);
 if (it != completedRequests.end()) {
 return it->second.result;
 }
 
 return std::vector<std::pair<int, int>>();
}

bool PathfindingThreadPool::isPathReady(int requestId) {
 std::lock_guard<std::mutex> lock(resultMutex);
 return completedRequests.find(requestId) != completedRequests.end();
}

void PathfindingThreadPool::cancelRequest(int requestId) {
 std::lock_guard<std::mutex> lock(resultMutex);
 completedRequests.erase(requestId);
}

int PathfindingThreadPool::getPendingRequestCount() const {
 std::lock_guard<std::mutex> lock(queueMutex);
 return requestQueue.size();
}

int PathfindingThreadPool::getCompletedRequestCount() const {
 std::lock_guard<std::mutex> lock(resultMutex);
 return completedRequests.size();
}

void PathfindingThreadPool::workerThread() {
 while (running) {
 PathRequest request;
 bool hasRequest = false;
 
 {
 std::lock_guard<std::mutex> lock(queueMutex);
 if (!requestQueue.empty()) {
 request = requestQueue.front();
 requestQueue.pop();
 hasRequest = true;
 }
 }
 
 if (!hasRequest) {
 std::this_thread::sleep_for(std::chrono::milliseconds(10));
 continue;
 }
 
 // Compute path
 std::vector<std::pair<int, int>> path;
 bool success = computePath(request, path);
 
 // Store result
 {
 std::lock_guard<std::mutex> lock(resultMutex);
 request.result = path;
 request.success = success;
 request.completed = true;
 completedRequests[request.id] = request;
 completedCount++;
 }
 }
}

bool PathfindingThreadPool::computePath(const PathRequest& request, std::vector<std::pair<int, int>>& outPath) {
 int startX = static_cast<int>(request.startX);
 int startY = static_cast<int>(request.startY);
 int endX = static_cast<int>(request.endX);
 int endY = static_cast<int>(request.endY);
 
 // Distance check
 float dx = endX - startX;
 float dy = endY - startY;
 float distance = std::sqrt(dx * dx + dy * dy);
 
 if (distance > request.maxDistance) {
 return false;
 }
 
 // A* algorithm implementation
 struct Node {
 int x, y;
 float gCost; // Cost from start
 float hCost; // Heuristic cost to goal
 float fCost; // gCost + hCost
 Node* parent;
 
 Node(int x, int y) : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(nullptr) {}
 };
 
 auto compare = [](Node* a, Node* b) {
 return a->fCost > b->fCost; // Min-heap based on fCost
 };
 
 std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
 std::unordered_map<int, Node*> allNodes; // key = x + y * 10000
 std::unordered_set<int> closedSet;
 
 // Helper to get node key
 auto getKey = [](int x, int y) { return x + y * 10000; };
 
 // Create start node
 Node* startNode = new Node(startX, startY);
 startNode->gCost = 0;
 startNode->hCost = heuristic(startX, startY, endX, endY);
 startNode->fCost = startNode->hCost;
 
 openSet.push(startNode);
 allNodes[getKey(startX, startY)] = startNode;
 
 bool pathFound = false;
 Node* goalNode = nullptr;
 
 // 8-directional neighbors (cardinal + diagonal)
 const int dirX[] = {0, 1, 0, -1, 1, 1, -1, -1};
 const int dirY[] = {-1, 0, 1, 0, -1, 1, 1, -1};
 const float moveCost[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.414f, 1.414f, 1.414f, 1.414f};
 
 // A* main loop
 while (!openSet.empty() && !pathFound) {
 Node* current = openSet.top();
 openSet.pop();
 
 int currentKey = getKey(current->x, current->y);
 
 // Skip if already processed
 if (closedSet.find(currentKey) != closedSet.end()) {
 continue;
 }
 
 closedSet.insert(currentKey);
 
 // Check if we reached the goal
 if (current->x == endX && current->y == endY) {
 pathFound = true;
 goalNode = current;
 break;
 }
 
 // Explore neighbors
 for (int i = 0; i < 8; i++) {
 int nx = current->x + dirX[i];
 int ny = current->y + dirY[i];
 int neighborKey = getKey(nx, ny);
 
 // Skip if already in closed set
 if (closedSet.find(neighborKey) != closedSet.end()) {
 continue;
 }
 
 // Check walkability (simplified - in real implementation would query IsoCell)
 // For now, assume all squares are walkable
 // TODO: Add IsoCell reference and check isWalkable()
 
 float newGCost = current->gCost + moveCost[i];
 
 // Check if this neighbor is already in open set
 Node* neighbor = nullptr;
 auto it = allNodes.find(neighborKey);
 if (it != allNodes.end()) {
 neighbor = it->second;
 // If we found a better path to this node, update it
 if (newGCost < neighbor->gCost) {
 neighbor->gCost = newGCost;
 neighbor->fCost = neighbor->gCost + neighbor->hCost;
 neighbor->parent = current;
 }
 } else {
 // Create new neighbor node
 neighbor = new Node(nx, ny);
 neighbor->gCost = newGCost;
 neighbor->hCost = heuristic(nx, ny, endX, endY);
 neighbor->fCost = neighbor->gCost + neighbor->hCost;
 neighbor->parent = current;
 
 allNodes[neighborKey] = neighbor;
 openSet.push(neighbor);
 }
 }
 }
 
 // Reconstruct path if found
 if (pathFound && goalNode) {
 Node* current = goalNode;
 while (current != nullptr) {
 outPath.push_back({current->x, current->y});
 current = current->parent;
 }
 std::reverse(outPath.begin(), outPath.end());
 }
 
 // Cleanup allocated nodes
 for (auto& pair : allNodes) {
 delete pair.second;
 }
 
 return pathFound;
}

float PathfindingThreadPool::heuristic(int x1, int y1, int x2, int y2) {
 // Manhattan distance heuristic
 return static_cast<float>(std::abs(x2 - x1) + std::abs(y2 - y1));
}

float PathfindingThreadPool::getTerrainCost(IsoGridSquare* square) {
 if (!square) return 1000.0f; // Impassable
 
 // TODO: Get terrain cost from square
 // Different terrain types have different movement costs
 
 return 1.0f; // Default cost
}

bool PathfindingThreadPool::isWalkable(IsoGridSquare* square) {
 if (!square) return false;
 
 // TODO: Check if square is walkable
 // Check for blocking objects, terrain type, etc.
 
 return true; // Default walkable
}

// AsyncPathfinder Implementation
std::unordered_map<int, AsyncPathfinder::PathCallback> AsyncPathfinder::callbacks;
std::mutex AsyncPathfinder::callbackMutex;

int AsyncPathfinder::requestPathWithCallback(float startX, float startY, float startZ,
 float endX, float endY, float endZ,
 const PathCallback& callback,
 int priority) {
 auto threadPool = PathfindingThreadPool::getInstance();
 int requestId = threadPool->requestPath(startX, startY, startZ, endX, endY, endZ, 1000.0f, priority);
 
 {
 std::lock_guard<std::mutex> lock(callbackMutex);
 callbacks[requestId] = callback;
 }
 
 return requestId;
}

void AsyncPathfinder::updateCallbacks() {
 auto threadPool = PathfindingThreadPool::getInstance();
 
 std::lock_guard<std::mutex> lock(callbackMutex);
 
 auto it = callbacks.begin();
 while (it != callbacks.end()) {
 int requestId = it->first;
 const auto& callback = it->second;
 
 if (threadPool->isPathReady(requestId)) {
 auto result = threadPool->getResult(requestId);
 callback(requestId, result);
 it = callbacks.erase(it);
 } else {
 ++it;
 }
 }
}

void AsyncPathfinder::cancelRequest(int requestId) {
 auto threadPool = PathfindingThreadPool::getInstance();
 threadPool->cancelRequest(requestId);
 
 std::lock_guard<std::mutex> lock(callbackMutex);
 callbacks.erase(requestId);
}
