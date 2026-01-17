#include "Entity.h"
#include <algorithm>

namespace zombie {
namespace entities {

// Entity implementation

Entity::Entity()
    : x(0.0f)
    , y(0.0f)
    , velocityX(0.0f)
    , velocityY(0.0f)
    , width(32.0f)
    , height(32.0f)
    , active(true)
    , visible(true)
    , health(100.0f)
    , maxHealth(100.0f)
    , sprite(nullptr)
    , animSprite(nullptr)
{
}

Entity::~Entity() {
    if (sprite) {
        delete sprite;
        sprite = nullptr;
    }
    if (animSprite) {
        delete animSprite;
        animSprite = nullptr;
    }
}

void Entity::update(float deltaTime) {
    if (!active) return;
    
    // Apply velocity
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
    
    // Update animated sprite
    if (animSprite) {
        animSprite->update(deltaTime);
        animSprite->setPosition(x, y);
    } else if (sprite) {
        sprite->setPosition(x, y);
    }
}

void Entity::render(SDL_Renderer* renderer) {
    if (!visible) return;
    
    // Render sprite
    if (animSprite) {
        animSprite->render(renderer);
    } else if (sprite) {
        sprite->render(renderer);
    }
}

void Entity::setPosition(float px, float py) {
    x = px;
    y = py;
    
    if (animSprite) {
        animSprite->setPosition(x, y);
    } else if (sprite) {
        sprite->setPosition(x, y);
    }
}

void Entity::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}

void Entity::setSize(float w, float h) {
    width = w;
    height = h;
}

void Entity::getBounds(float& outX, float& outY, float& outW, float& outH) const {
    outX = x;
    outY = y;
    outW = width;
    outH = height;
}

// EntityManager implementation

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
    clear();
}

void EntityManager::addEntity(EntityPtr entity) {
    if (entity) {
        entities.push_back(entity);
    }
}

void EntityManager::removeEntity(EntityPtr entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);  // shared_ptr handles deletion
    }
}

void EntityManager::clear() {
    entities.clear();  // shared_ptr handles deletion automatically
}

void EntityManager::updateAll(float deltaTime) {
    for (auto& entity : entities) {
        if (entity && entity->isActive()) {
            entity->update(deltaTime);
        }
    }
}

void EntityManager::renderAll(SDL_Renderer* renderer) {
    for (auto& entity : entities) {
        if (entity && entity->isVisible()) {
            entity->render(renderer);
        }
    }
}

int EntityManager::getEntityCount() const {
    return static_cast<int>(entities.size());
}

EntityPtr EntityManager::getEntity(int index) {
    if (index >= 0 && index < static_cast<int>(entities.size())) {
        return entities[index];
    }
    return nullptr;
}

void EntityManager::removeDeadEntities() {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const EntityPtr& entity) {
                return !entity->isAlive();  // shared_ptr deletion is automatic
            }),
        entities.end()
    );
}

} // namespace entities
} // namespace zombie
