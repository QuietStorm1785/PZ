#include "ObjectPool.h"
#include "Entity.h"
#include <iostream>

namespace zombie {
namespace memory {

// EntityPool implementation
class EntityPool::Impl {
public:
    ObjectPool<zombie::entities::Entity> pool;
    
    explicit Impl(size_t initialSize, size_t maxSize)
        : pool(initialSize, maxSize)
    {
        // Set custom reset function
        pool.setResetFunction([](zombie::entities::Entity* entity) {
            // Reset entity to default state
            entity->setPosition(0.0f, 0.0f);
            entity->setVelocity(0.0f, 0.0f);
            entity->setHealth(100.0f);
            entity->setActive(false);
            entity->setVisible(false);
        });
    }
};

EntityPool::EntityPool(size_t initialSize, size_t maxSize)
    : pImpl(std::make_unique<Impl>(initialSize, maxSize))
{
}

EntityPool::~EntityPool() = default;

zombie::entities::Entity* EntityPool::acquire() {
    auto* entity = pImpl->pool.acquire();
    entity->setActive(true);
    entity->setVisible(true);
    return entity;
}

void EntityPool::release(zombie::entities::Entity* entity) {
    if (entity) {
        entity->setActive(false);
        entity->setVisible(false);
        pImpl->pool.release(entity);
    }
}

size_t EntityPool::getPoolSize() const {
    return pImpl->pool.getPoolSize();
}

size_t EntityPool::getActiveCount() const {
    return pImpl->pool.getActiveCount();
}

size_t EntityPool::getTotalCreated() const {
    return pImpl->pool.getTotalCreated();
}

size_t EntityPool::getTotalAcquired() const {
    return pImpl->pool.getTotalAcquired();
}

size_t EntityPool::getTotalReleased() const {
    return pImpl->pool.getTotalReleased();
}

float EntityPool::getHitRate() const {
    return pImpl->pool.getHitRate();
}

void EntityPool::clear() {
    pImpl->pool.clear();
}

} // namespace memory
} // namespace zombie
