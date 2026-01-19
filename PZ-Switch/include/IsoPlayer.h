#pragma once
#include "Entity.h"
#include "InputManager.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "AnimationController.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <glm/glm.hpp>

class IsoCell;
class IsoGridSquare;
class InventoryManager;

namespace zombie {
namespace characters {

// Forward declarations
class BodyDamage;
class Moodles;
class Stats;
class Inventory;

/**
 * IsoGameCharacter - Base class for all characters (players, zombies, survivors)
 */
class IsoGameCharacter : public entities::Entity {
public:
 IsoGameCharacter();
 virtual ~IsoGameCharacter();
 
 // Lifecycle
 void update(float deltaTime) override;
 void render(SDL_Renderer* renderer) override;
 
 // Movement
 virtual void updateMovement(float deltaTime);
 void setTargetPosition(float x, float y);
 bool isMoving() const { return moving; }
 
 void setMoveSpeed(float speed) { moveSpeed = speed; }
 float getMoveSpeed() const { return moveSpeed; }
 
 // Combat
 virtual void hit(float damage, IsoGameCharacter* attacker);
 virtual void die();
 bool isDead() const { return health <= 0.0f; }
 
 // Character state
 void setFacing(int direction) { facingDirection = direction; }
 int getFacing() const { return facingDirection; }
 
 void setRunning(bool run) { running = run; }
 bool isRunning() const { return running; }
 
 // Stats
 float getStamina() const { return stamina; }
 void setStamina(float value) { stamina = value; }
 
 float getHunger() const { return hunger; }
 void setHunger(float value) { hunger = value; }
 
 float getThirst() const { return thirst; }
 void setThirst(float value) { thirst = value; }
 
 // Inventory
 void addItem(std::string_view itemType);
 void removeItem(std::string_view itemType);
 bool hasItem(std::string_view itemType) const;
 
 std::string getType() const override { return "IsoGameCharacter"; }
 
protected:
 // Movement
 float targetX, targetY;
 bool moving;
 bool running;
 int facingDirection; // 0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
 float moveSpeed;
 
 // Stats
 float stamina;
 float maxStamina;
 float hunger;
 float thirst;
 float fatigue;
 
 // Combat
 float attackDelay;
 float nextAttackTime;
 
 // Simple inventory (for now)
 std::vector<std::string> inventory;
 
 // Rendering
 void updateAnimation(float deltaTime);
 void selectSprite();
};

/**
 * IsoPlayer - Player character controlled by user input
 */
class IsoPlayer : public IsoGameCharacter, public std::enable_shared_from_this<IsoPlayer> {
public:
 IsoPlayer();
 virtual ~IsoPlayer();
 
 void update(float deltaTime) override;
 void render(SDL_Renderer* renderer) override;
 
 // Input handling
 void handleInput(input::InputManager* inputMgr);
 
 // Player actions
 void interact();
 void useItem(std::string_view itemType);
 void attackNearestZombie();

 // World binding
 void setWorld(IsoCell* cell, int zLevel = 0);
 void detachFromWorld();
 IsoGridSquare* getCurrentSquare() const { return currentSquare; }
 int getCurrentZ() const { return currentZ; }
 
 // Player state
 void setPlayerNum(int num) { playerNum = num; }
 int getPlayerNum() const { return playerNum; }
 
 void setSurname(std::string_view name) { surname = name; }
 std::string getSurname() const { return surname; }
 
 void setForename(std::string_view name) { forename = name; }
 std::string getForename() const { return forename; }
 
 // Experience and skills
 void addXP(float amount) { xp += amount; }
 float getXP() const { return xp; }
 
 // Inventory
 InventoryManager* getInventory() { return inventory; }
 const InventoryManager* getInventory() const { return inventory; }
 
 // Sprite access
 zombie::graphics::AnimatedSprite* getSprite() { return sprite.get(); }
 void setSprite(std::shared_ptr<zombie::graphics::AnimatedSprite> spr) { 
 sprite = spr;
 if (sprite && !animController) {
 animController = std::make_unique<zombie::characters::AnimationController>(sprite.get());
 }
 }
 
 // Animation controller access
 zombie::characters::AnimationController* getAnimationController() { return animController.get(); }
 
 std::string getType() const override { return "IsoPlayer"; }
 
private:
 int playerNum;
 std::string forename;
 std::string surname;
 
 // Player stats
 float xp;
 int level;
 
 // Input state
 bool pressingForward;
 bool pressingBack;
 bool pressingLeft;
 bool pressingRight;
 
 // Actions
 float interactRange;

 // World tracking
 IsoCell* world;
 IsoGridSquare* currentSquare;
 int currentZ;
 
 // Inventory system
 InventoryManager* inventory;
 
 // Sprite for rendering
 std::shared_ptr<zombie::graphics::AnimatedSprite> sprite;
 
 // Animation controller
 std::unique_ptr<zombie::characters::AnimationController> animController;
 
 // Helper methods
 void processMovementInput(input::InputManager* inputMgr);
 void processActionInput(input::InputManager* inputMgr);
 void updatePlayerStats(float deltaTime);
 bool canMoveTo(float newX, float newY) const;
 void updateCurrentSquare();
};

} // namespace characters
} // namespace zombie
