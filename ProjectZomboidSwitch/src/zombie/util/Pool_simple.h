#pragma once
#include <vector>
#include <memory>
#include <functional>

namespace zombie {
namespace util {

// Simple object pool for reducing allocations
template<typename T>
class Pool {
private:
    std::vector<std::unique_ptr<T>> available;
    std::function<std::unique_ptr<T>()> factory;
    size_t maxSize;
    size_t allocated;

public:
    Pool(std::function<std::unique_ptr<T>()> factoryFunc, size_t max = 1000)
        : factory(factoryFunc), maxSize(max), allocated(0) {}
    
    // Acquire object from pool
    std::unique_ptr<T> acquire() {
        if (!available.empty()) {
            auto obj = std::move(available.back());
            available.pop_back();
            return obj;
        }
        
        // Create new if under limit
        if (allocated < maxSize) {
            allocated++;
            return factory();
        }
        
        // Force create if over limit
        return factory();
    }
    
    // Return object to pool
    void release(std::unique_ptr<T> obj) {
        if (obj && available.size() < maxSize) {
            available.push_back(std::move(obj));
        }
    }
    
    // Clear pool
    void clear() {
        available.clear();
        allocated = 0;
    }
    
    // Get pool stats
    size_t getAvailableCount() const { return available.size(); }
    size_t getAllocatedCount() const { return allocated; }
    size_t getMaxSize() const { return maxSize; }
};

// Pooled object base class
class IPooledObject {
public:
    virtual ~IPooledObject() = default;
    virtual void onAcquired() {}
    virtual void onReleased() {}
};

} // namespace util
} // namespace zombie
