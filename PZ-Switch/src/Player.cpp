#include "Player.h"
#include <cmath>
#include <iostream>

namespace zombie {
namespace entities {

// Player implementation

Player::Player()
 : Entity()
 , moveSpeed(200.0f)
 , movingLeft(false)
 , movingRight(false)
 , movingUp(false)
 , movingDown(false)
{
 setSize(32, 48); // Typical character size
 setHealth(100);
 setMaxHealth(100);
}

Player::~Player() {
}

void Player::update(float deltaTime) {
 updateMovement(deltaTime);
 Entity::update(deltaTime);
}

void Player::render(SDL_Renderer* renderer) {
 Entity::render(renderer);
}

void Player::moveLeft() {
 movingLeft = true;
}

void Player::moveRight() {
 movingRight = true;
}

void Player::moveUp() {
 movingUp = true;
}

void Player::moveDown() {
 movingDown = true;
}

void Player::stopMoving() {
 movingLeft = false;
 movingRight = false;
 movingUp = false;
 movingDown = false;
 setVelocity(0, 0);
}

void Player::attack() {
 // Simple melee attack - damage entities within range
 // This would be expanded with weapon handling, animations, etc.
 std::cout << "Player attacks!" << '\n';
 
 // Attack range of 50 pixels
 const float attackRange = 50.0f;
 const float attackDamage = 10.0f;
 
 // TODO: Query spatial grid for nearby zombies
 // For now, this is a placeholder that would connect to the entity system
}

void Player::interact() {
 // Interact with nearby objects (doors, containers, items)
 std::cout << "Player interacts!" << '\n';
 
 const float interactRange = 64.0f;
 
 // TODO: Query world for interactive objects within range
 // - Check for doors to open/close
 // - Check for containers to loot
 // - Check for items to pick up
 // For now, this is a placeholder
}

void Player::updateMovement(float deltaTime) {
 (void)deltaTime;
 float vx = 0.0f;
 float vy = 0.0f;
 
 if (movingLeft) vx -= moveSpeed;
 if (movingRight) vx += moveSpeed;
 if (movingUp) vy -= moveSpeed;
 if (movingDown) vy += moveSpeed;
 
 // Normalize diagonal movement
 if (vx != 0.0f && vy != 0.0f) {
 float length = std::sqrt(vx * vx + vy * vy);
 vx = (vx / length) * moveSpeed;
 vy = (vy / length) * moveSpeed;
 }
 
 setVelocity(vx, vy);
}

// Zombie implementation

Zombie::Zombie()
 : Entity()
 , moveSpeed(100.0f)
 , aggroRange(200.0f)
 , hasTargetPos(false)
 , targetX(0.0f)
 , targetY(0.0f)
{
 setSize(32, 48);
 setHealth(50);
 setMaxHealth(50);
}

Zombie::~Zombie() {
}

void Zombie::update(float deltaTime) {
 updateAI(deltaTime);
 Entity::update(deltaTime);
}

void Zombie::render(SDL_Renderer* renderer) {
 Entity::render(renderer);
}

void Zombie::setTarget(float tx, float ty) {
 targetX = tx;
 targetY = ty;
 hasTargetPos = true;
}

void Zombie::clearTarget() {
 hasTargetPos = false;
 setVelocity(0, 0);
}

void Zombie::updateAI(float deltaTime) {
 if (!hasTargetPos) {
 setVelocity(0, 0);
 return;
 }
 
 moveTowardsTarget(deltaTime);
}

void Zombie::moveTowardsTarget(float deltaTime) {
 (void)deltaTime;
 float dx = targetX - x;
 float dy = targetY - y;
 float distance = std::sqrt(dx * dx + dy * dy);
 
 // Stop if close enough
 if (distance < 10.0f) {
 setVelocity(0, 0);
 return;
 }
 
 // Normalize and apply speed
 float vx = (dx / distance) * moveSpeed;
 float vy = (dy / distance) * moveSpeed;
 
 setVelocity(vx, vy);
}

} // namespace entities
} // namespace zombie
