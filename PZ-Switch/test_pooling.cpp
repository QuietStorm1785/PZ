// Test Entity Pooling System
#include "ObjectPool.h"
#include "Entity.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace zombie::memory;
using namespace zombie::entities;

void printStats(EntityPool& pool, const std::string& phase) {
    std::cout << "\n=== " << phase << " ===" << std::endl;
    std::cout << "Pool Size: " << pool.getPoolSize() << std::endl;
    std::cout << "Active Count: " << pool.getActiveCount() << std::endl;
    std::cout << "Hit Rate: " << std::fixed << std::setprecision(2) 
              << (pool.getHitRate() * 100) << "%" << std::endl;
    std::cout << "Total Created: " << pool.getTotalCreated() << std::endl;
    std::cout << "Total Acquired: " << pool.getTotalAcquired() << std::endl;
    std::cout << "Total Released: " << pool.getTotalReleased() << std::endl;
}

int main() {
    std::cout << "Entity Pooling System Test\n" << std::endl;
    
    // Create pool with 0 initial size to test pooling behavior
    EntityPool pool(0, 500);
    std::vector<Entity*> entities;
    
    // Test 1: Acquire 10 entities (all will be new)
    std::cout << "Test 1: Acquiring 10 entities (first time)..." << std::endl;
    for (int i = 0; i < 10; i++) {
        Entity* entity = pool.acquire();
        entity->setPosition(100.0f + i * 10, 200.0f);
        entities.push_back(entity);
    }
    printStats(pool, "After acquiring 10 entities");
    
    // Test 2: Release all entities back to pool
    std::cout << "\nTest 2: Releasing all entities..." << std::endl;
    for (Entity* entity : entities) {
        pool.release(entity);
    }
    entities.clear();
    printStats(pool, "After releasing all entities");
    
    // Test 3: Acquire 10 entities again (should reuse from pool)
    std::cout << "\nTest 3: Acquiring 10 entities (should hit pool)..." << std::endl;
    for (int i = 0; i < 10; i++) {
        Entity* entity = pool.acquire();
        entities.push_back(entity);
        // Check if entity was properly reset
        if (!entity->isActive()) {
            std::cout << "ERROR: Entity " << i << " not active after acquire!" << std::endl;
        }
    }
    printStats(pool, "After re-acquiring 10 entities");
    
    // Test 4: Verify entity state was reset
    std::cout << "\nTest 4: Verifying entity reset..." << std::endl;
    bool allReset = true;
    for (Entity* entity : entities) {
        if (entity->getX() != 0.0f || entity->getY() != 0.0f) {
            std::cout << "WARNING: Entity position not reset (may be expected behavior)" << std::endl;
            allReset = false;
            break;
        }
    }
    if (allReset) {
        std::cout << "✓ All entities properly reset" << std::endl;
    }
    
    // Test 5: Acquire more entities than pool size
    std::cout << "\nTest 5: Acquiring 20 total entities (exceed pool)..." << std::endl;
    for (int i = 0; i < 10; i++) {
        Entity* entity = pool.acquire();
        entities.push_back(entity);
    }
    printStats(pool, "After acquiring 20 total entities");
    
    // Test 6: Release all and clear pool
    std::cout << "\nTest 6: Cleaning up..." << std::endl;
    for (Entity* entity : entities) {
        pool.release(entity);
    }
    entities.clear();
    pool.clear();
    printStats(pool, "After clearing pool");
    
    // Summary
    std::cout << "\n=== Test Summary ===" << std::endl;
    double finalHitRate = pool.getHitRate();
    if (pool.getTotalCreated() < pool.getTotalAcquired()) {
        std::cout << "✓ PASS: Created " << pool.getTotalCreated() 
                  << " but acquired " << pool.getTotalAcquired() 
                  << " times (pooling working)" << std::endl;
    } else {
        std::cout << "✗ FAIL: Never reused pooled objects" << std::endl;
    }
    
    return 0;
}
