#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <mutex>
#include <unordered_map>

// Forward declarations
namespace zombie { namespace entities { class Entity; } }

namespace zombie {
namespace memory {

/**
 * ObjectPool - Generic object pool for performance optimization
 * 
 * Reduces allocation overhead by reusing objects instead of
 * constantly creating and destroying them.
 * 
 * Template Parameters:
 * T - Type of object to pool
 * 
 * Example:
 * ObjectPool<Bullet> bulletPool(100);
 * Bullet* bullet = bulletPool.acquire();
 * // ... use bullet ...
 * bulletPool.release(bullet);
 */
template<typename T>
class ObjectPool {
public:
 /**
 * Constructor
 * @param initialSize - Number of objects to pre-allocate
 * @param maxSize - Maximum pool size (0 = unlimited)
 */
 explicit ObjectPool(size_t initialSize = 10, size_t maxSize = 1000)
 : maxPoolSize(maxSize)
 , totalCreated(0)
 , totalAcquired(0)
 , totalReleased(0)
 {
 pool.reserve(initialSize);
 for (size_t i = 0; i < initialSize; i++) {
 pool.push_back(std::make_unique<T>());
 }
 totalCreated = initialSize;
 }

 /**
 * Acquire object from pool
 * Creates new object if pool is empty
 * @return Pointer to object (caller must call release() when done)
 */
 T* acquire() {
 std::lock_guard<std::mutex> lock(poolMutex);
 
 totalAcquired++;
 
 if (pool.empty()) {
 // Pool exhausted, create new object
 totalCreated++;
 auto obj = std::make_unique<T>();
 T* ptr = obj.get();
 activeObjects[ptr] = std::move(obj);
 return ptr;
 }
 
 // Reuse from pool
 auto obj = std::move(pool.back());
 pool.pop_back();
 
 T* ptr = obj.get();
 activeObjects[ptr] = std::move(obj);
 
 return ptr;
 }

 /**
 * Release object back to pool
 * @param obj - Object to return (must have been acquired from this pool)
 */
 void release(T* obj) {
 if (!obj) return;
 
 std::lock_guard<std::mutex> lock(poolMutex);
 
 totalReleased++;
 
 auto it = activeObjects.find(obj);
 if (it == activeObjects.end()) {
 // Object not from this pool, ignore
 return;
 }
 
 // Reset object to default state
 resetObject(obj);
 
 // Return to pool if not at max capacity
 if (maxPoolSize == 0 || pool.size() < maxPoolSize) {
 pool.push_back(std::move(it->second));
 }
 // Otherwise just delete (unique_ptr will handle it)
 
 activeObjects.erase(it);
 }

 /**
 * Get pool statistics
 */
 size_t getPoolSize() const { return pool.size(); }
 size_t getActiveCount() const { return activeObjects.size(); }
 size_t getTotalCreated() const { return totalCreated; }
 size_t getTotalAcquired() const { return totalAcquired; }
 size_t getTotalReleased() const { return totalReleased; }
 
 /**
 * Get hit rate (percentage of acquires that reused pooled objects)
 */
 float getHitRate() const {
 if (totalAcquired == 0) return 0.0f;
 // Hits = requests served from pool (not newly created)
 // If totalCreated >= totalAcquired, we've never reused anything
 if (totalCreated >= totalAcquired) return 0.0f;
 size_t hits = totalAcquired - totalCreated;
 return 100.0f * (float)hits / (float)totalAcquired;
 }

 /**
 * Clear pool (deletes all unused objects)
 */
 void clear() {
 std::lock_guard<std::mutex> lock(poolMutex);
 pool.clear();
 }

 /**
 * Set custom reset function
 * Called when object is returned to pool
 */
 void setResetFunction(std::function<void(T*)> resetFn) {
 customReset = resetFn;
 }

private:
 std::vector<std::unique_ptr<T>> pool;
 std::unordered_map<T*, std::unique_ptr<T>> activeObjects;
 std::mutex poolMutex;
 size_t maxPoolSize;
 size_t totalCreated;
 size_t totalAcquired;
 size_t totalReleased;
 std::function<void(T*)> customReset;

 void resetObject(T* obj) {
 if (customReset) {
 customReset(obj);
 }
 // Otherwise object keeps its state
 // (derived classes can override reset() method)
 }
};

/**
 * EntityPool - Specialized pool for game entities
 * 
 * Manages Entity objects with automatic reset on release.
 */
class EntityPool {
public:
 explicit EntityPool(size_t initialSize = 50, size_t maxSize = 500);
 ~EntityPool();

 /**
 * Acquire entity from pool
 * @return Entity ready for use
 */
 zombie::entities::Entity* acquire();

 /**
 * Release entity back to pool
 * Resets entity state automatically
 */
 void release(zombie::entities::Entity* entity);

 /**
 * Get pool statistics
 */
 size_t getPoolSize() const;
 size_t getActiveCount() const;
 size_t getTotalCreated() const;
 size_t getTotalAcquired() const;
 size_t getTotalReleased() const;
 float getHitRate() const;

 /**
 * Clear pool
 */
 void clear();

private:
 class Impl;
 std::unique_ptr<Impl> pImpl;
};

} // namespace memory
} // namespace zombie
