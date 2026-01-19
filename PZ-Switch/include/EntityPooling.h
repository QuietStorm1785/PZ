#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <chrono>
#include <cassert>

namespace jni {
namespace pooling {

// ============================================================================
// ENTITY POOL STATISTICS
// ============================================================================

struct PoolStatistics {
    uint32_t total_allocated = 0;
    uint32_t currently_in_use = 0;
    uint32_t available_in_pool = 0;
    uint32_t allocations_since_reset = 0;
    uint32_t deallocations_since_reset = 0;
    std::chrono::milliseconds total_allocation_time{0};
};

// ============================================================================
// CONTIGUOUS ENTITY POOL (FOR CACHE EFFICIENCY)
// ============================================================================

template <typename T>
class ContiguousEntityPool {
public:
    explicit ContiguousEntityPool(uint32_t capacity, std::string_view pool_name = "")
        : capacity_(capacity), pool_name_(pool_name) {
        // Pre-allocate all entities in contiguous memory
        entities_.reserve(capacity);
        
        // Create all entities upfront
        for (uint32_t i = 0; i < capacity; ++i) {
            entities_.emplace_back(std::make_unique<T>());
            available_indices_.push(i);
        }
    }

    ~ContiguousEntityPool() = default;

    // Allocate an entity from the pool
    T* allocate() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        if (available_indices_.empty()) {
            return nullptr;  // Pool exhausted
        }

        uint32_t idx = available_indices_.front();
        available_indices_.pop();

        in_use_count_++;
        stats_.allocations_since_reset++;

        return entities_[idx].get();
    }

    // Release an entity back to the pool
    void release(T* entity) noexcept {
        if (!entity) return;

        std::lock_guard<std::mutex> lock(mutex_);

        // Find the entity in our pool
        for (uint32_t i = 0; i < capacity_; ++i) {
            if (entities_[i].get() == entity) {
                available_indices_.push(i);
                in_use_count_--;
                stats_.deallocations_since_reset++;
                return;
            }
        }
    }

    // Get current statistics
    PoolStatistics get_statistics() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        PoolStatistics stat = stats_;
        stat.total_allocated = capacity_;
        stat.currently_in_use = in_use_count_;
        stat.available_in_pool = available_indices_.size();
        return stat;
    }

    // Clear statistics counters
    void reset_statistics() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        stats_.allocations_since_reset = 0;
        stats_.deallocations_since_reset = 0;
        stats_.total_allocation_time = std::chrono::milliseconds{0};
    }

    // Get utilization percentage
    float get_utilization() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        if (capacity_ == 0) return 0.0f;
        return (static_cast<float>(in_use_count_) / capacity_) * 100.0f;
    }

    // Check if entity is owned by this pool
    bool contains(T* entity) const noexcept {
        if (!entity) return false;
        std::lock_guard<std::mutex> lock(mutex_);
        for (uint32_t i = 0; i < capacity_; ++i) {
            if (entities_[i].get() == entity) {
                return true;
            }
        }
        return false;
    }

    // Get pool capacity
    uint32_t capacity() const noexcept { return capacity_; }

    // Get pool name
    std::string_view name() const noexcept { return pool_name_; }

private:
    uint32_t capacity_;
    std::string pool_name_;
    std::vector<std::unique_ptr<T>> entities_;
    std::queue<uint32_t> available_indices_;
    uint32_t in_use_count_ = 0;
    mutable std::mutex mutex_;
    PoolStatistics stats_;
};

// ============================================================================
// SMART POOL POINTER (RAII FOR AUTOMATIC RELEASE)
// ============================================================================

template <typename T>
class PooledEntity {
public:
    PooledEntity(T* entity, ContiguousEntityPool<T>* pool)
        : entity_(entity), pool_(pool) {}

    ~PooledEntity() noexcept {
        if (entity_ && pool_) {
            pool_->release(entity_);
        }
    }

    // Move semantics
    PooledEntity(PooledEntity&& other) noexcept
        : entity_(other.entity_), pool_(other.pool_) {
        other.entity_ = nullptr;
        other.pool_ = nullptr;
    }

    PooledEntity& operator=(PooledEntity&& other) noexcept {
        if (this != &other) {
            if (entity_ && pool_) {
                pool_->release(entity_);
            }
            entity_ = other.entity_;
            pool_ = other.pool_;
            other.entity_ = nullptr;
            other.pool_ = nullptr;
        }
        return *this;
    }

    // Delete copy operations
    PooledEntity(const PooledEntity&) = delete;
    PooledEntity& operator=(const PooledEntity&) = delete;

    // Access operators
    T* operator->() noexcept { return entity_; }
    const T* operator->() const noexcept { return entity_; }

    T& operator*() noexcept { return *entity_; }
    const T& operator*() const noexcept { return *entity_; }

    T* get() noexcept { return entity_; }
    const T* get() const noexcept { return entity_; }

    explicit operator bool() const noexcept { return entity_ != nullptr; }

private:
    T* entity_;
    ContiguousEntityPool<T>* pool_;
};

// ============================================================================
// MULTI-TIER POOL MANAGER (DIFFERENT SIZES FOR DIFFERENT ENTITY TYPES)
// ============================================================================

template <typename T>
class MultiTierPoolManager {
public:
    struct Tier {
        uint32_t size;
        std::unique_ptr<ContiguousEntityPool<T>> pool;
    };

    explicit MultiTierPoolManager(std::string_view manager_name = "")
        : manager_name_(manager_name) {}

    // Add a pool tier
    void add_tier(uint32_t size, std::string_view tier_name) {
        tiers_.emplace_back(Tier{
            size,
            std::make_unique<ContiguousEntityPool<T>>(
                size, tier_name)
        });
    }

    // Allocate from any available tier
    T* allocate() noexcept {
        for (auto& tier : tiers_) {
            if (auto* entity = tier.pool->allocate()) {
                return entity;
            }
        }
        return nullptr;  // All pools exhausted
    }

    // Release entity back to pool
    void release(T* entity) noexcept {
        for (auto& tier : tiers_) {
            if (tier.pool->contains(entity)) {
                tier.pool->release(entity);
                return;
            }
        }
    }

    // Get total statistics across all tiers
    std::vector<PoolStatistics> get_all_statistics() const noexcept {
        std::vector<PoolStatistics> stats;
        for (const auto& tier : tiers_) {
            stats.push_back(tier.pool->get_statistics());
        }
        return stats;
    }

    // Print pool report
    void print_report() const noexcept {
        printf("\n=== Entity Pool Report: %s ===\n", manager_name_.data());
        
        uint32_t total_capacity = 0;
        uint32_t total_in_use = 0;

        for (size_t i = 0; i < tiers_.size(); ++i) {
            auto stats = tiers_[i].pool->get_statistics();
            total_capacity += stats.total_allocated;
            total_in_use += stats.currently_in_use;

            printf("  Tier %zu (%s):\n", i, tiers_[i].pool->name().data());
            printf("    Capacity: %u\n", stats.total_allocated);
            printf("    In Use: %u (%.1f%%)\n", 
                   stats.currently_in_use,
                   tiers_[i].pool->get_utilization());
            printf("    Available: %u\n", stats.available_in_pool);
            printf("    Allocations: %u\n", stats.allocations_since_reset);
            printf("    Deallocations: %u\n", stats.deallocations_since_reset);
        }

        printf("  Total Capacity: %u\n", total_capacity);
        printf("  Total In Use: %u (%.1f%%)\n", 
               total_in_use,
               total_capacity > 0 ? (static_cast<float>(total_in_use) / total_capacity) * 100.0f : 0.0f);
        printf("============================\n\n");
    }

private:
    std::string manager_name_;
    std::vector<Tier> tiers_;
};

// ============================================================================
// POOL MONITOR (FOR DETECTING POOL EXHAUSTION AND WARNINGS)
// ============================================================================

template <typename T>
class PoolMonitor {
public:
    explicit PoolMonitor(ContiguousEntityPool<T>* pool,
                        float warning_threshold = 0.8f,
                        float critical_threshold = 0.95f)
        : pool_(pool),
          warning_threshold_(warning_threshold),
          critical_threshold_(critical_threshold) {}

    // Check pool health and return status
    enum class PoolHealth {
        HEALTHY,
        WARNING,
        CRITICAL,
        EXHAUSTED
    };

    PoolHealth check_health() const noexcept {
        float utilization = pool_->get_utilization();

        if (utilization >= 100.0f) {
            return PoolHealth::EXHAUSTED;
        } else if (utilization >= critical_threshold_ * 100.0f) {
            return PoolHealth::CRITICAL;
        } else if (utilization >= warning_threshold_ * 100.0f) {
            return PoolHealth::WARNING;
        }
        return PoolHealth::HEALTHY;
    }

    // Get health status string
    std::string_view get_status_string() const noexcept {
        switch (check_health()) {
            case PoolHealth::HEALTHY:
                return "HEALTHY";
            case PoolHealth::WARNING:
                return "WARNING";
            case PoolHealth::CRITICAL:
                return "CRITICAL";
            case PoolHealth::EXHAUSTED:
                return "EXHAUSTED";
        }
        return "UNKNOWN";
    }

    // Get current utilization
    float get_utilization() const noexcept {
        return pool_->get_utilization();
    }

private:
    ContiguousEntityPool<T>* pool_;
    float warning_threshold_;
    float critical_threshold_;
};

}  // namespace pooling
}  // namespace jni

#endif  // ENTITY_POOLING_H
