#include "IsoZombie.h"
#include "IsoPlayer.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "PathfindingThreadPool.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

IsoZombie::IsoZombie()
 : x(0.0f), y(0.0f), z(0.0f)
 , health(100.0f)
 , moveSpeed(50.0f)
 , facingDirection(2) // South
 , state(ZombieState::IDLE)
 , target() // Default-constructed weak_ptr (empty)
 , sightRange(10.0f)
 , attackRange(1.5f)
 , attackDamage(5.0f)
 , attackCooldown(1.0f)
 , timeSinceLastAttack(0.0f)
 , wanderTimer(0.0f)
 , wanderX(0.0f)
 , wanderY(0.0f)
 , pathIndex(0)
 , pathUpdateTimer(PATH_UPDATE_INTERVAL)
 , asyncPathRequestId(-1)
 , waitingForPath(false)
 , world(nullptr) {
 // Pathfinding will be initialized when world is set
}

// Target tracking with smart pointers
IsoPlayerPtr IsoZombie::getTarget() const {
 return target.lock(); // Return shared_ptr or nullptr if expired
}

void IsoZombie::setTarget(IsoPlayerPtr t) {
 target = t; // Store as weak_ptr
}

IsoZombie::~IsoZombie() {
 // Unregister walkability listener if still registered
 if (world && walkabilityListenerId != 0) {
 world->removeWalkabilityListener(walkabilityListenerId);
 walkabilityListenerId = 0;
 }
}

void IsoZombie::update(float deltaTime) {
 if (!isAlive()) return;
 
 // Update AI
 updateAI(deltaTime);
 
 // Update attack cooldown
 timeSinceLastAttack += deltaTime;
}

void IsoZombie::updateAI(float deltaTime) {
 switch (state) {
 case ZombieState::IDLE: {
 findNearestPlayer();
 auto targetPtr = getTarget();
 if (targetPtr && canSeePlayer(targetPtr)) {
 setState(ZombieState::CHASE);
 } else {
 // Randomly start wandering
 wanderTimer -= deltaTime;
 if (wanderTimer <= 0.0f) {
 setState(ZombieState::WANDER);
 wanderTimer = 3.0f + (rand() % 5); // 3-8 seconds
 }
 }
 break;
 }
 
 case ZombieState::WANDER: {
 wander(deltaTime);
 
 // Check for players while wandering
 findNearestPlayer();
 auto targetPtr2 = getTarget();
 if (targetPtr2 && canSeePlayer(targetPtr2)) {
 setState(ZombieState::CHASE);
 }
 
 // Return to idle after wander timer expires
 wanderTimer -= deltaTime;
 if (wanderTimer <= 0.0f) {
 setState(ZombieState::IDLE);
 wanderTimer = 2.0f + (rand() % 3); // 2-5 seconds idle
 }
 break;
 }
 
 case ZombieState::CHASE: {
 auto targetPtr3 = getTarget();
 if (!targetPtr3 || !canSeePlayer(targetPtr3)) {
 setState(ZombieState::IDLE);
 setTarget(nullptr);
 } else {
 chaseTarget(deltaTime);
 
 // Check if in attack range
 float dx = x - targetPtr3->getX();
 float dy = y - targetPtr3->getY();
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist <= attackRange) {
 setState(ZombieState::ATTACK);
 }
 }
 break;
 }
 
 case ZombieState::ATTACK: {
 auto targetPtr4 = getTarget();
 if (!targetPtr4) {
 setState(ZombieState::IDLE);
 } else {
 float dx = x - targetPtr4->getX();
 float dy = y - targetPtr4->getY();
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist > attackRange) {
 setState(ZombieState::CHASE);
 } else {
 attackTarget();
 }
 }
 break;
 }
 }
}

void IsoZombie::findNearestPlayer() {
 if (!world) return;
 
 // Get all players from the world
 const auto& players = world->getPlayers();
 if (players.empty()) return;
 
 // Find closest player
 IsoPlayerPtr nearestPlayer = nullptr;
 float nearestDist = std::numeric_limits<float>::max();
 
 for (const auto& player : players) {
 if (!player || !player->isAlive()) continue;
 
 float dx = x - player->getX();
 float dy = y - player->getY();
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist < nearestDist && dist <= sightRange) {
 nearestDist = dist;
 nearestPlayer = player;
 }
 }
 
 if (nearestPlayer) {
 setTarget(nearestPlayer);
 }
}

bool IsoZombie::canSeePlayer(IsoPlayerPtr player) {
 if (!player) return false;
 
 float dx = x - player->getX();
 float dy = y - player->getY();
 float dist = std::sqrt(dx*dx + dy*dy);
 
 return dist <= sightRange;
}

void IsoZombie::chaseTarget(float deltaTime) {
 auto targetPtr = getTarget();
 if (!targetPtr) return;
 
 // Check if we have a pending async path request
 if (waitingForPath && asyncPathRequestId != -1) {
 auto threadPool = PathfindingThreadPool::getInstance();
 if (threadPool->isPathReady(asyncPathRequestId)) {
 // Path is ready, retrieve it
 auto result = threadPool->getResult(asyncPathRequestId);
 if (!result.empty()) {
 // Convert to our path format
 currentPath.clear();
 for (const auto& point : result) {
 currentPath.push_back(zombie::pathfinding::Vec3(point.first, point.second, 0));
 }
 pathIndex = 0;
 }
 waitingForPath = false;
 asyncPathRequestId = -1;
 }
 }
 
 // Update pathfinding timer
 pathUpdateTimer -= deltaTime;
 
 // Request new path if timer expired and not waiting
 if (pathUpdateTimer <= 0.0f && !waitingForPath) {
 int startX = static_cast<int>(x);
 int startY = static_cast<int>(y);
 int startZ = static_cast<int>(z);
 
 int goalX = static_cast<int>(targetPtr->getX());
 int goalY = static_cast<int>(targetPtr->getY());
 int goalZ = 0; // Z-coordinate defaults to 0 (ground level)
 
 // Calculate distance for priority determination
 float distance = std::sqrt((goalX - startX) * (goalX - startX) + 
 (goalY - startY) * (goalY - startY));
 
 // Check if target is a player (higher priority)
 bool isPlayerTarget = (targetPtr->getType() == "player");
 
 // Calculate priority based on distance and target type
 // Uses intelligent scaling:
 // 0-5 tiles: Priority 8-10 (immediate threat)
 // 5-15 tiles: Priority 6-8 (nearby threat)
 // 15-30 tiles: Priority 4-6 (medium distance)
 // 30-50 tiles: Priority 2-4 (far)
 // 50+ tiles: Priority 0-2 (background)
 int priority = PathfindingThreadPool::calculatePriorityByDistance(distance, isPlayerTarget);
 
 auto threadPool = PathfindingThreadPool::getInstance();
 asyncPathRequestId = threadPool->requestPath(
 startX, startY, startZ,
 goalX, goalY, goalZ,
 100.0f, // Max distance
 priority
 );
 
 waitingForPath = true;
 pathUpdateTimer = PATH_UPDATE_INTERVAL;
 }
 
 // Follow the calculated path
 if (!currentPath.empty() && pathIndex < static_cast<int>(currentPath.size())) {
 const zombie::pathfinding::Vec3& waypoint = currentPath[pathIndex];
 
 // Move towards current waypoint
 float dx = waypoint.x - x;
 float dy = waypoint.y - y;
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist < 0.5f) {
 // Close enough to waypoint, move to next
 pathIndex++;
 } else if (dist > 0.1f) {
 // Normalize and move
 dx /= dist;
 dy /= dist;
 
 float speed = moveSpeed * deltaTime;
 x += dx * speed;
 y += dy * speed;
 
 // Update facing direction
 if (std::abs(dx) > std::abs(dy)) {
 facingDirection = (dx > 0) ? 1 : 3; // East or West
 } else {
 facingDirection = (dy > 0) ? 2 : 0; // South or North
 }
 }
 } else {
 // No path or reached end, use direct approach as fallback
 float dx = targetPtr->getX() - x;
 float dy = targetPtr->getY() - y;
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist > 0.1f) {
 // Normalize direction
 dx /= dist;
 dy /= dist;
 
 // Move at zombie speed
 float speed = moveSpeed * deltaTime;
 x += dx * speed;
 y += dy * speed;
 
 // Update facing direction
 if (std::abs(dx) > std::abs(dy)) {
 facingDirection = (dx > 0) ? 1 : 3; // East or West
 } else {
 facingDirection = (dy > 0) ? 2 : 0; // South or North
 }
 }
 }
}

void IsoZombie::attackTarget() {
 auto targetPtr = getTarget();
 if (!targetPtr) return;
 
 // Can only attack if cooldown expired
 if (timeSinceLastAttack >= attackCooldown) {
 targetPtr->setHealth(targetPtr->getHealth() - attackDamage);
 timeSinceLastAttack = 0.0f;
 }
}

void IsoZombie::wander(float deltaTime) {
 // Pick a random direction if we don't have one
 if (wanderX == 0.0f && wanderY == 0.0f) {
 float angle = (rand() % 360) * 3.14159f / 180.0f;
 wanderX = std::cos(angle);
 wanderY = std::sin(angle);
 }
 
 // Move slowly in wander direction
 float speed = getMoveSpeed() * 0.3f * deltaTime; // 30% speed when wandering
 x += wanderX * speed;
 y += wanderY * speed;
 
 // Randomly change direction occasionally
 if (rand() % 100 < 5) { // 5% chance per frame
 wanderX = 0.0f;
 wanderY = 0.0f;
 }
}

void IsoZombie::setWorld(IsoCell* cell) {
 world = cell;
 if (!world) return;

 // Initialize A* pathfinder sized to the world with multi-Z depth
 int w = world->getWidth();
 int h = world->getHeight();
 int d = IsoCell::MAX_HEIGHT;
 pathfinder = std::make_shared<zombie::pathfinding::AStarPathfinder>(w, h, d);

 // Neighbor provider uses IsoGridSquare neighbor pointers for fast traversal
 pathfinder->setNeighborProvider([this](int lx, int ly, int lz, std::vector<zombie::pathfinding::Vec3>& out) {
 if (!world) return;
 IsoGridSquare* sq = world->getGridSquare(lx, ly, lz);
 if (!sq || sq->isBlocked()) return;

 auto tryAdd = [&](IsoGridSquare* n) {
 if (n && !n->isBlocked()) {
 out.emplace_back(static_cast<float>(n->getX()), static_cast<float>(n->getY()), static_cast<float>(n->getZ()));
 }
 };

 tryAdd(sq->getN());
 tryAdd(sq->getS());
 tryAdd(sq->getE());
 tryAdd(sq->getW());
 tryAdd(sq->getNE());
 tryAdd(sq->getNW());
 tryAdd(sq->getSE());
 tryAdd(sq->getSW());
 });

 // Cache up to 256 recent paths; dynamic obstacles will invalidate via walkability listener
 pathfinder->setCacheSize(256);

 // Sync walkability from currently loaded chunks across all Z levels
 for (int zz = 0; zz < d; ++zz) {
 world->forEachLoadedSquare(zz, [&](const IsoGridSquare* sq) {
 int sx = sq->getX();
 int sy = sq->getY();
 int sz = sq->getZ();
 bool walkable = !sq->isBlocked();
 pathfinder->setWalkable(sx, sy, sz, walkable);
 });
 }

 // Subscribe to future walkability changes; capture weak_ptr to avoid keeping pathfinder alive
 std::weak_ptr<zombie::pathfinding::AStarPathfinder> pfWeak = pathfinder;
 walkabilityListenerId = world->addWalkabilityListener(
 [pfWeak](int lx, int ly, int lz, bool walkable) {
 if (auto pf = pfWeak.lock()) {
 pf->setWalkable(lx, ly, lz, walkable);
 }
 }
 );
}

void IsoZombie::takeDamage(float damage) {
 if (damage <= 0.0f) return;
 
 health -= damage;
 
 if (health <= 0.0f) {
 health = 0.0f;
 std::cout << "Zombie died!" << std::endl;
 // TODO: Play death animation
 // TODO: Spawn loot
 }
}
