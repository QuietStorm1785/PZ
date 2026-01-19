#include "IsoPlayer.h"
#include "InputManager.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoZombie.h"
#include "InventoryManager.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>
#include <limits>

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
 (void)deltaTime;
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
 (void)attacker;
 health -= damage;
 
 if (health <= 0.0f) {
 health = 0.0f;
 die();
 }
}

void IsoGameCharacter::die() {
 setActive(false);
 setVisible(false);
 std::cout << "Character died!" << '\n';
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
 (void)deltaTime;
 
 // Update facing direction based on velocity
 if (moving) {
 if (std::abs(velocityX) > std::abs(velocityY)) {
 // Horizontal movement dominant
 facingDirection = (velocityX > 0) ? 6 : 2; // East : West
 } else {
 // Vertical movement dominant
 facingDirection = (velocityY > 0) ? 4 : 0; // South : North
 }
 }
 
 // Animation frame updates would go here
 // - Increment animation frame counter
 // - Switch to appropriate animation based on state (idle, walk, run, attack)
}

void IsoGameCharacter::selectSprite() {
 // Select sprite texture/frame based on facing direction
 // Directions: 0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
 
 // Would set the current sprite texture here
 // For example:
 // - sprite->setTexture(characterSheet)
 // - sprite->setTextureRect(getFrameForDirection(facingDirection))
 // 
 // This requires the sprite atlas/sheet system to be fully integrated
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
 
 // Apply configurable deadzone
 const float deadzone = inputMgr->getControllerDeadzone();
 if (std::abs(axisX) > deadzone) moveX += axisX;
 if (std::abs(axisY) > deadzone) moveY += axisY;
 }
 
 // Running (Shift or sprint binding on controller)
 running = inputMgr->isKeyDown(SDL_SCANCODE_LSHIFT) || 
 inputMgr->isActionDown("sprint");
 
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
 
 // Update facing direction from movement or right stick aiming
 if (inputMgr->hasGamepad()) {
 float lookX = inputMgr->getAxisValue(SDL_CONTROLLER_AXIS_RIGHTX);
 float lookY = inputMgr->getAxisValue(SDL_CONTROLLER_AXIS_RIGHTY);
 const float deadzone = inputMgr->getControllerDeadzone();
 if (std::abs(lookX) > deadzone || std::abs(lookY) > deadzone) {
 // Use right stick to aim/facing
 if (std::abs(lookX) > std::abs(lookY)) {
 facingDirection = lookX > 0 ? 2 : 6; // E or W
 } else {
 facingDirection = lookY > 0 ? 4 : 0; // S or N
 }
 } else if (moving) {
 if (std::abs(moveX) > std::abs(moveY)) {
 facingDirection = moveX > 0 ? 2 : 6; // E or W
 } else {
 facingDirection = moveY > 0 ? 4 : 0; // S or N
 }
 }
 } else if (moving) {
 if (std::abs(moveX) > std::abs(moveY)) {
 facingDirection = moveX > 0 ? 2 : 6; // E or W
 } else {
 facingDirection = moveY > 0 ? 4 : 0; // S or N
 }
 }
}

void IsoPlayer::processActionInput(input::InputManager* inputMgr) {
 // Interact (E key or A on Switch)
 if (inputMgr->isKeyPressed(SDL_SCANCODE_E) ||
 inputMgr->isActionPressed("interact")) {
 interact();
 }

 // Shove/aim (LT on Switch by default)
 if (inputMgr->isActionPressed("aim") || inputMgr->isActionPressed("shove")) {
 // Placeholder shove implementation; real logic would push nearby zombie back
 attackNearestZombie();
 }

 // Attack (Space or configured binding -> RT on Switch)
 if (inputMgr->isKeyPressed(SDL_SCANCODE_SPACE) ||
 inputMgr->isActionPressed("fire")) {
 attackNearestZombie();
 }
 
 // Use item / inventory (F or Y on Switch)
 if (inputMgr->isKeyPressed(SDL_SCANCODE_F) ||
 inputMgr->isActionPressed("inventory")) {
 // TODO: Open quick use menu or inventory radial
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
 std::cout << forename << " " << surname << " interacts with nothing." << '\n';
 return;
 }

 const auto& objs = square->getObjects();
 if (objs.empty()) {
 std::cout << forename << " " << surname << " finds no interactable objects here." << '\n';
 return;
 }

 std::cout << forename << " " << surname << " interacts with " << objs.size() << " object(s)." << '\n';
 for (auto* obj : objs) {
 if (obj) {
 obj->onInteract(this);
 }
 }
}

void IsoPlayer::useItem(const std::string& itemType) {
 if (!hasItem(itemType)) {
 std::cout << "Don't have item: " << itemType << '\n';
 return;
 }
 
 std::cout << "Using item: " << itemType << '\n';
 
 // Basic item usage logic
 if (itemType == "FirstAidKit" || itemType == "Bandage") {
 // Heal player
 float healAmount = (itemType == "FirstAidKit") ? 30.0f : 15.0f;
 setHealth(std::min(getMaxHealth(), getHealth() + healAmount));
 removeItem(itemType);
 std::cout << forename << " heals for " << healAmount << " HP" << '\n';
 }
 else if (itemType == "Food" || itemType == "CannedFood") {
 // Reduce hunger
 hunger -= 20.0f;
 hunger = std::max(0.0f, hunger);
 removeItem(itemType);
 std::cout << forename << " eats and reduces hunger" << '\n';
 }
 else if (itemType == "Water" || itemType == "WaterBottle") {
 // Reduce thirst
 thirst -= 25.0f;
 thirst = std::max(0.0f, thirst);
 removeItem(itemType);
 std::cout << forename << " drinks and reduces thirst" << '\n';
 }
 else {
 std::cout << "Don't know how to use: " << itemType << '\n';
 }
}

void IsoPlayer::attackNearestZombie() {
 std::cout << forename << " " << surname << " attacks!" << '\n';
 
 if (!world) return;
 
 const auto& zombies = world->getZombies();
 if (zombies.empty()) {
 std::cout << "No zombies nearby" << '\n';
 return;
 }
 
 // Find nearest zombie within attack range
 IsoZombiePtr nearestZombie = nullptr;
 float nearestDist = interactRange; // Use interact range as max attack range
 
 for (const auto& zombie : zombies) {
 if (!zombie || !zombie->isAlive()) continue;
 
 float dx = zombie->getX() - getX();
 float dy = zombie->getY() - getY();
 float dist = std::sqrt(dx*dx + dy*dy);
 
 if (dist < nearestDist) {
 nearestDist = dist;
 nearestZombie = zombie;
 }
 }
 
 if (nearestZombie) {
 // Deal damage based on weapon (for now, unarmed damage)
 float damage = 10.0f; // Base unarmed damage
 
 nearestZombie->takeDamage(damage);
 std::cout << forename << " hits zombie for " << damage << " damage!" << '\n';
 
 // TODO: Play attack animation
 // TODO: Play attack sound
 } else {
 std::cout << "No zombie in range" << '\n';
 }
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
