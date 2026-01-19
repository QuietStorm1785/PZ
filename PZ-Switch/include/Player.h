#pragma once
#include "Entity.h"

namespace zombie {
namespace entities {

/**
 * Player - Player character entity
 */
class Player : public Entity {
public:
 Player();
 virtual ~Player();
 
 void update(float deltaTime) override;
 void render(SDL_Renderer* renderer) override;
 
 // Movement
 void moveLeft();
 void moveRight();
 void moveUp();
 void moveDown();
 void stopMoving();
 
 // Actions
 void attack();
 void interact();
 
 // Properties
 float getMoveSpeed() const { return moveSpeed; }
 void setMoveSpeed(float speed) { moveSpeed = speed; }
 
 std::string getType() const override { return "Player"; }
 
private:
 float moveSpeed;
 bool movingLeft, movingRight, movingUp, movingDown;
 
 void updateMovement(float deltaTime);
};

/**
 * Zombie - Basic zombie enemy
 */
class Zombie : public Entity {
public:
 Zombie();
 virtual ~Zombie();
 
 void update(float deltaTime) override;
 void render(SDL_Renderer* renderer) override;
 
 // AI
 void setTarget(float targetX, float targetY);
 void clearTarget();
 bool hasTarget() const noexcept { return hasTargetPos; }
 
 // Properties
 float getMoveSpeed() const { return moveSpeed; }
 void setMoveSpeed(float speed) { moveSpeed = speed; }
 
 float getAggroRange() const { return aggroRange; }
 void setAggroRange(float range) { aggroRange = range; }
 
 std::string getType() const override { return "Zombie"; }
 
private:
 float moveSpeed;
 float aggroRange;
 
 bool hasTargetPos;
 float targetX, targetY;
 
 void updateAI(float deltaTime);
 void moveTowardsTarget(float deltaTime);
};

} // namespace entities
} // namespace zombie
