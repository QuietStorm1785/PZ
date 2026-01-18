#pragma once
#include "Sprite.h"
#include "SpriteAnimation.h"
#include <string>
#include <memory>

namespace zombie {
namespace entities {

/**
 * Entity - Base class for all game entities
 */
class Entity {
public:
 Entity();
 virtual ~Entity();
 
 // Lifecycle
 virtual void update(float deltaTime);
 virtual void render(SDL_Renderer* renderer);
 
 // Position and movement
 void setPosition(float x, float y);
 float getX() const { return x; }
 float getY() const { return y; }
 
 void setVelocity(float vx, float vy);
 float getVelocityX() const { return velocityX; }
 float getVelocityY() const { return velocityY; }
 
 // Collision bounds
 void setSize(float w, float h);
 float getWidth() const { return width; }
 float getHeight() const { return height; }
 
 // Get bounding box
 void getBounds(float& outX, float& outY, float& outW, float& outH) const;
 
 // Entity properties
 void setActive(bool active) { this->active = active; }
 bool isActive() const { return active; }
 
 void setVisible(bool visible) { this->visible = visible; }
 bool isVisible() const { return visible; }
 
 void setHealth(float hp) { health = hp; }
 float getHealth() const { return health; }
 
 void setMaxHealth(float maxHp) { maxHealth = maxHp; }
 float getMaxHealth() const { return maxHealth; }
 
 bool isAlive() const { return health > 0; }
 
 // Entity type identification
 virtual std::string getType() const { return "Entity"; }
 
protected:
 // Transform
 float x, y;
 float velocityX, velocityY;
 float width, height;
 
 // State
 bool active;
 bool visible;
 float health;
 float maxHealth;
 
 // Rendering (optional - can be overridden)
 graphics::Sprite* sprite;
 graphics::AnimatedSprite* animSprite;
};

// Smart pointer types for entities
using EntityPtr = std::shared_ptr<Entity>;
using EntityWeakPtr = std::weak_ptr<Entity>;

/**
 * EntityManager - Manages all entities in the game
 */
class EntityManager {
public:
 EntityManager();
 ~EntityManager();
 
 // Add/remove entities
 void addEntity(EntityPtr entity);
 void removeEntity(EntityPtr entity);
 void clear();
 
 // Update all entities
 void updateAll(float deltaTime);
 void renderAll(SDL_Renderer* renderer);
 
 // Query entities
 int getEntityCount() const;
 EntityPtr getEntity(int index);
 
 // Cleanup dead entities
 void removeDeadEntities();
 
private:
 std::vector<EntityPtr> entities;
};

} // namespace entities
} // namespace zombie
