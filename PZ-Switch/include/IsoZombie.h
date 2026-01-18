#pragma once
#include <memory>
#include "Pathfinding.h"
#include <glm/glm.hpp>

// Forward declarations
namespace zombie {
namespace characters {
 class IsoPlayer;
}
}

class IsoGridSquare;

// Use shorter alias and smart pointer types
using IsoPlayer = zombie::characters::IsoPlayer;
using IsoPlayerPtr = std::shared_ptr<IsoPlayer>;
using IsoPlayerWeakPtr = std::weak_ptr<IsoPlayer>;

/**
 * IsoZombie - AI-controlled zombie character
 * Simplified standalone zombie class with basic AI
 */
class IsoZombie {
public:
 IsoZombie();
 virtual ~IsoZombie();

 // Position
 float getX() const { return x; }
 float getY() const { return y; }
 float getZ() const { return z; }
 void setX(float nx) { x = nx; }
 void setY(float ny) { y = ny; }
 void setZ(float nz) { z = nz; }

 // Health
 float getHealth() const { return health; }
 void setHealth(float h) { health = h; }
 bool isAlive() const { return health > 0.0f; }
 void takeDamage(float damage);

 // Update
 void update(float deltaTime);

 // AI States
 enum class ZombieState {
 IDLE,
 WANDER,
 CHASE,
 ATTACK
 };

 ZombieState getState() const { return state; }
 void setState(ZombieState s) { state = s; }

 // Target tracking
 IsoPlayerPtr getTarget() const;
 void setTarget(IsoPlayerPtr t);

 // AI behavior
 void updateAI(float deltaTime);
 void findNearestPlayer();
 bool canSeePlayer(IsoPlayerPtr player);
 void chaseTarget(float deltaTime);
 void attackTarget();
 void wander(float deltaTime);

 // World binding
 void setWorld(class IsoCell* cell);

 // Properties
 float getSightRange() const { return sightRange; }
 float getAttackRange() const { return attackRange; }
 float getAttackDamage() const { return attackDamage; }
 float getMoveSpeed() const { return moveSpeed; }
 void setMoveSpeed(float speed) { moveSpeed = speed; }
 int getFacingDirection() const { return facingDirection; }

private:
 // Position and physics
 float x, y, z;
 float health;
 float moveSpeed;
 int facingDirection; // 0=N, 1=E, 2=S, 3=W
 
 // AI state
 ZombieState state;
 IsoPlayerWeakPtr target; // Non-owning reference to avoid circular dependency
 
 // AI properties
 float sightRange;
 float attackRange;
 float attackDamage;
 float attackCooldown;
 float timeSinceLastAttack;
 
 // Wander behavior
 float wanderTimer;
 float wanderX, wanderY;
 
 // Pathfinding
 std::shared_ptr<zombie::pathfinding::AStarPathfinder> pathfinder;
 std::vector<zombie::pathfinding::Vec3> currentPath;
 int pathIndex;
 float pathUpdateTimer;
 static constexpr float PATH_UPDATE_INTERVAL = 0.5f; // Update path every 0.5 seconds
 
 // Async pathfinding
 int asyncPathRequestId;
 bool waitingForPath;

 // Non-owning reference to the world grid
 class IsoCell* world;
 uint32_t walkabilityListenerId = 0;
};
