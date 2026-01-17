#include "IsoPlayer.h"
#include "InputManager.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "InventoryManager.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>

namespace zombie {
namespace characters {

// ===== IsoGameCharacter Implementation =====

IsoGameCharacter::IsoGameCharacter()
    : Entity()
    , targetX(0)
    , targetY(0)
    , moving(false)
    , running(false)
    , facingDirection(4) // South
    , moveSpeed(100.0f)
    , stamina(100.0f)
    , maxStamina(100.0f)
    , hunger(0.0f)
    , thirst(0.0f)
    , fatigue(0.0f)
    , attackDelay(1.0f)
    , nextAttackTime(0.0f)
{
    setSize(32, 32);
    setMaxHealth(100.0f);
    setHealth(100.0f);}

IsoGameCharacter::~IsoGameCharacter() {
}

void IsoGameCharacter::update(float deltaTime) {
    Entity::update(deltaTime);
    
    // Update stats
    if (moving) {
        stamina -= deltaTime * (running ? 5.0f : 2.0f);
        stamina = std::max(0.0f, stamina);
        
        if (stamina <= 0.0f) {
            running = false;
        }
    } else {
        stamina += deltaTime * 3.0f;
        stamina = std::min(maxStamina, stamina);
    }
    
    // Hunger and thirst slowly increase
    hunger += deltaTime * 0.01f;
    thirst += deltaTime * 0.02f;
    
    updateAnimation(deltaTime);
}

void IsoGameCharacter::render(SDL_Renderer* renderer) {
    Entity::render(renderer);
}

void IsoGameCharacter::updateMovement(float deltaTime) {
    if (!moving) return;
    
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance < 5.0f) {
        moving = false;
        velocityX = 0;
        velocityY = 0;
        return;
    }
    
    // Normalize direction
    float dirX = dx / distance;
    float dirY = dy / distance;
    
    // Apply movement speed
    float speed = running ? 150.0f : 100.0f;
    velocityX = dirX * speed;
    velocityY = dirY * speed;
}

void IsoGameCharacter::setTargetPosition(float tx, float ty) {
    targetX = tx;
    targetY = ty;
    moving = true;
}

void IsoGameCharacter::hit(float damage, IsoGameCharacter* attacker) {
    health -= damage;
    
    if (health <= 0.0f) {
        health = 0.0f;
        die();
    }
}

void IsoGameCharacter::die() {
    setActive(false);
    setVisible(false);
    std::cout << "Character died!" << std::endl;
}

void IsoGameCharacter::addItem(const std::string& itemType) {
    inventory.push_back(itemType);
}

void IsoGameCharacter::removeItem(const std::string& itemType) {
    auto it = std::find(inventory.begin(), inventory.end(), itemType);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

bool IsoGameCharacter::hasItem(const std::string& itemType) const {
    return std::find(inventory.begin(), inventory.end(), itemType) != inventory.end();
}

void IsoGameCharacter::updateAnimation(float deltaTime) {
    // TODO: Update sprite based on movement direction and state
}

void IsoGameCharacter::selectSprite() {
    // TODO: Select appropriate sprite based on facing direction
}

// ===== IsoPlayer Implementation =====

IsoPlayer::IsoPlayer()
    : IsoGameCharacter()
    , playerNum(0)
    , forename("Player")
    , surname("One")
    , xp(0.0f)
    , level(1)
    , pressingForward(false)
    , pressingBack(false)
    , pressingLeft(false)
    , pressingRight(false)
    , interactRange(64.0f)
    , world(nullptr)
    , currentSquare(nullptr)
    , currentZ(0)
    , inventory(nullptr)
{
    setMaxHealth(100.0f);
    setHealth(100.0f);
    setMoveSpeed(150.0f);
    
    // Create inventory
    inventory = new InventoryManager(this);
}

IsoPlayer::~IsoPlayer() {
    delete inventory;
    inventory = nullptr;
}

void IsoPlayer::update(float deltaTime) {
    // Predictive collision against world grid before applying movement
    if (world) {
        float nextX = getX() + getVelocityX() * deltaTime;
        float nextY = getY() + getVelocityY() * deltaTime;

        if (!canMoveTo(nextX, nextY)) {
            setVelocity(0.0f, 0.0f);
        }
    }

    IsoGameCharacter::update(deltaTime);

    if (world) {
        updateCurrentSquare();
    }

    updatePlayerStats(deltaTime);
    
    // Update animation controller
    if (animController) {
        // Update animation state based on movement
        if (!isAlive()) {
            animController->setState(zombie::characters::AnimationController::State::DEATH);
        } else if (isMoving()) {
            if (isRunning()) {
                animController->setState(zombie::characters::AnimationController::State::RUN);
            } else {
                animController->setState(zombie::characters::AnimationController::State::WALK);
            }
            
            // Update direction based on velocity
            auto dir = zombie::characters::AnimationHelpers::velocityToDirection(velocityX, velocityY);
            animController->setDirection(dir);
        } else {
            animController->setState(zombie::characters::AnimationController::State::IDLE);
        }
        
        animController->update(deltaTime);
    }
}

void IsoPlayer::render(SDL_Renderer* renderer) {
    IsoGameCharacter::render(renderer);
}

void IsoPlayer::handleInput(input::InputManager* inputMgr) {
    if (!isAlive()) return;
    
    processMovementInput(inputMgr);
    processActionInput(inputMgr);
}

void IsoPlayer::processMovementInput(input::InputManager* inputMgr) {
    float moveX = 0.0f;
    float moveY = 0.0f;
    
    // WASD movement
    if (inputMgr->isKeyDown(SDL_SCANCODE_W)) moveY -= 1.0f;
    if (inputMgr->isKeyDown(SDL_SCANCODE_S)) moveY += 1.0f;
    if (inputMgr->isKeyDown(SDL_SCANCODE_A)) moveX -= 1.0f;
    if (inputMgr->isKeyDown(SDL_SCANCODE_D)) moveX += 1.0f;
    
    // Gamepad support
    if (inputMgr->hasGamepad()) {
        float axisX = inputMgr->getAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
        float axisY = inputMgr->getAxisValue(SDL_CONTROLLER_AXIS_LEFTY);
        
        // Apply deadzone
        const float deadzone = 0.15f;
        if (std::abs(axisX) > deadzone) moveX += axisX;
        if (std::abs(axisY) > deadzone) moveY += axisY;
    }
    
    // Running (Shift or B button on Switch)
    running = inputMgr->isKeyDown(SDL_SCANCODE_LSHIFT) || 
              inputMgr->isGamepadButtonDown(SDL_CONTROLLER_BUTTON_B);
    
    // Normalize diagonal movement
    if (moveX != 0.0f && moveY != 0.0f) {
        float length = std::sqrt(moveX * moveX + moveY * moveY);
        moveX /= length;
        moveY /= length;
    }
    
    // Apply movement
    float speed = getMoveSpeed();
    if (running && stamina > 10.0f) {
        speed *= 1.5f;
    }
    
    setVelocity(moveX * speed, moveY * speed);
    moving = (moveX != 0.0f || moveY != 0.0f);
    
    // Update facing direction
    if (moving) {
        if (std::abs(moveX) > std::abs(moveY)) {
            facingDirection = moveX > 0 ? 2 : 6; // E or W
        } else {
            facingDirection = moveY > 0 ? 4 : 0; // S or N
        }
    }
}

void IsoPlayer::processActionInput(input::InputManager* inputMgr) {
    // Interact (E key or A button on Switch)
    if (inputMgr->isKeyPressed(SDL_SCANCODE_E) ||
        inputMgr->isGamepadButtonPressed(SDL_CONTROLLER_BUTTON_A)) {
        interact();
    }
    
    // Attack (Space or X button on Switch)
    if (inputMgr->isKeyPressed(SDL_SCANCODE_SPACE) ||
        inputMgr->isGamepadButtonPressed(SDL_CONTROLLER_BUTTON_X)) {
        attackNearestZombie();
    }
    
    // Use item (F key or Y button on Switch)
    if (inputMgr->isKeyPressed(SDL_SCANCODE_F) ||
        inputMgr->isGamepadButtonPressed(SDL_CONTROLLER_BUTTON_Y)) {
        // TODO: Open quick use menu
    }
}

void IsoPlayer::updatePlayerStats(float deltaTime) {
    // Health regeneration when well-fed and rested
    if (hunger < 30.0f && thirst < 30.0f && health < maxHealth) {
        health += deltaTime * 0.5f;
        health = std::min(maxHealth, health);
    }
    
    // Damage from extreme hunger/thirst
    if (hunger > 90.0f || thirst > 90.0f) {
        health -= deltaTime * 1.0f;
    }
    
    // Clamp stats
    hunger = std::clamp(hunger, 0.0f, 100.0f);
    thirst = std::clamp(thirst, 0.0f, 100.0f);
}

void IsoPlayer::interact() {
    IsoGridSquare* square = currentSquare;
    if (!square && world) {
        square = world->getGridSquare(static_cast<int>(std::floor(getX())),
                                      static_cast<int>(std::floor(getY())),
                                      currentZ);
    }

    if (!square) {
        std::cout << forename << " " << surname << " interacts with nothing." << std::endl;
        return;
    }

    const auto& objs = square->getObjects();
    if (objs.empty()) {
        std::cout << forename << " " << surname << " finds no interactable objects here." << std::endl;
        return;
    }

    std::cout << forename << " " << surname << " interacts with " << objs.size() << " object(s)." << std::endl;
    for (auto* obj : objs) {
        if (obj) {
            obj->onInteract(this);
        }
    }
}

void IsoPlayer::useItem(const std::string& itemType) {
    if (hasItem(itemType)) {
        std::cout << "Using item: " << itemType << std::endl;
        // TODO: Implement item usage logic
    }
}

void IsoPlayer::attackNearestZombie() {
    std::cout << forename << " " << surname << " attacks!" << std::endl;
    // TODO: Find nearest zombie and attack
}

void IsoPlayer::setWorld(IsoCell* cell, int zLevel) {
    if (world == cell && currentZ == zLevel) return;

    detachFromWorld();
    world = cell;
    currentZ = zLevel;

    if (!world) return;

    // Add player to the current square for tracking
    updateCurrentSquare();
}

void IsoPlayer::detachFromWorld() {
    if (currentSquare) {
        try {
            auto self = shared_from_this();
            currentSquare->removeCharacter(self);
        } catch (const std::bad_weak_ptr&) {
            // Player not managed by shared_ptr; ignore removal attempt
        }
        currentSquare = nullptr;
    }
    world = nullptr;
}

bool IsoPlayer::canMoveTo(float newX, float newY) const {
    if (!world) return true;

    int tx = static_cast<int>(std::floor(newX));
    int ty = static_cast<int>(std::floor(newY));
    const IsoGridSquare* target = world->getGridSquare(tx, ty, currentZ);

    // If chunk/square missing, treat as blocked to avoid falling out of world
    if (!target) {
        return false;
    }

    return target->isFree(true);
}

void IsoPlayer::updateCurrentSquare() {
    if (!world) return;

    int tx = static_cast<int>(std::floor(getX()));
    int ty = static_cast<int>(std::floor(getY()));
    IsoGridSquare* nextSquare = world->getGridSquare(tx, ty, currentZ);

    if (nextSquare == currentSquare) return;

    try {
        auto self = shared_from_this();

        if (currentSquare) {
            currentSquare->removeCharacter(self);
        }

        if (nextSquare) {
            nextSquare->addCharacter(self);
        }

        currentSquare = nextSquare;
    } catch (const std::bad_weak_ptr&) {
        // setWorld may be called on a non-managed instance; skip occupancy tracking
        currentSquare = nextSquare;
    }
}

} // namespace characters
} // namespace zombie
