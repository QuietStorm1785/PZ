#include "Player.h"
#include <cmath>

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
    // TODO: Implement attack logic
}

void Player::interact() {
    // TODO: Implement interact logic
}

void Player::updateMovement(float deltaTime) {
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
