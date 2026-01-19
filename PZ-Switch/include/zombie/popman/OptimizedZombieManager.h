#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include "EntityPooling.h"
#include "HotPathProfiler.h"

namespace zombie {

// Forward declaration
class IsoZombie;

namespace popman {

// ============================================================================
// OPTIMIZED ZOMBIE POPULATION MANAGER WITH ENTITY POOLING
// ============================================================================

/**
 * Enhancement wrapper for ZombiePopulationManager that adds entity pooling
 * for improved performance when spawning/despawning zombies.
 */
class OptimizedZombieManager {
public:
    explicit OptimizedZombieManager(uint32_t pool_capacity = 4096);
    ~OptimizedZombieManager() = default;

    // Initialize zombie pools
    void initialize_pools() noexcept;

    // Allocate zombie from pool
    IsoZombie* allocate_zombie() noexcept {
        PROFILE_SCOPE("ZombieAllocate");
        return zombie_pool_->allocate();
    }

    // Release zombie back to pool
    void release_zombie(IsoZombie* zombie) noexcept {
        if (zombie && zombie_pool_) {
            PROFILE_SCOPE("ZombieRelease");
            zombie_pool_->release(zombie);
        }
    }

    // Get pool statistics
    void print_pool_status() const noexcept {
        if (zombie_pool_) {
            auto stats = zombie_pool_->get_statistics();
            printf("\nZombie Pool Status:\n");
            printf("  Capacity: %u\n", stats.total_allocated);
            printf("  In Use: %u (%.1f%%)\n", 
                   stats.currently_in_use,
                   zombie_pool_->get_utilization());
            printf("  Available: %u\n", stats.available_in_pool);
            printf("  Allocations: %u\n", stats.allocations_since_reset);
            printf("  Deallocations: %u\n", stats.deallocations_since_reset);
        }
    }

    // Check pool health
    void check_pool_health() const noexcept {
        if (!zombie_pool_) return;
        
        float utilization = zombie_pool_->get_utilization();
        if (utilization > 90.0f) {
            printf("WARNING: Zombie pool at %.1f%% capacity\n", utilization);
        }
    }

    // Get pool capacity
    uint32_t get_pool_capacity() const noexcept {
        return zombie_pool_ ? zombie_pool_->capacity() : 0;
    }

    // Get current pool utilization
    float get_pool_utilization() const noexcept {
        return zombie_pool_ ? zombie_pool_->get_utilization() : 0.0f;
    }

    // Reset statistics
    void reset_pool_statistics() noexcept {
        if (zombie_pool_) {
            zombie_pool_->reset_statistics();
        }
    }

private:
    std::unique_ptr<jni::pooling::ContiguousEntityPool<IsoZombie>> zombie_pool_;
};

}  // namespace popman
}  // namespace zombie
