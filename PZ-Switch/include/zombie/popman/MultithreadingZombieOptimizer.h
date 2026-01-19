/**
 * @file MultithreadingZombieOptimizer.h
 * @brief Zombie-specific parallelization utilities
 * 
 * Provides high-level API for parallel zombie operations:
 * - Parallel AI updates for all zombies
 * - Parallel collision detection using spatial hashing
 * - Parallel position/velocity updates
 * - Thread pool coordination
 * 
 * Performance Target: +10-20% FPS via parallelization
 * Integration: Works with MultithreadingFramework.h and ZombiePopulationManager
 * 
 * @date January 19, 2026
 * @author PZ Optimization Team
 */

#pragma once

#include "MultithreadingFramework.h"
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <cmath>

namespace zombie {
namespace popman {
namespace threading_optimizer {

// ============================================================================
// SPATIAL HASHING FOR COLLISION DETECTION
// ============================================================================

/**
 * @struct SpatialHashGrid
 * @brief 3D spatial hash grid for fast collision detection
 * 
 * Divides 3D space into uniform cells for O(1) proximity queries.
 * Used to parallelize collision detection across grid cells.
 */
struct SpatialHashGrid {
    static constexpr float CELL_SIZE = 5.0f;  // 5-unit cells
    
    struct GridCell {
        std::vector<size_t> zombie_indices;
        std::vector<std::pair<float, float>> collision_pairs;  // (dist_sq, zombie_index)
    };
    
    std::unordered_map<int64_t, GridCell> cells;
    
    /**
     * @brief Compute 3D spatial hash key for position
     * @param x, y, z World coordinates
     * @return Hash key for grid cell
     */
    static int64_t compute_hash(float x, float y, float z) noexcept {
        int32_t gx = static_cast<int32_t>(x / CELL_SIZE);
        int32_t gy = static_cast<int32_t>(y / CELL_SIZE);
        int32_t gz = static_cast<int32_t>(z / CELL_SIZE);
        
        // Cantor pairing function for 3D
        int64_t key = static_cast<int64_t>(gx);
        key = (key << 21) | (static_cast<int64_t>(gy) & 0x1FFFFF);
        key = (key << 21) | (static_cast<int64_t>(gz) & 0x1FFFFF);
        return key;
    }
    
    /**
     * @brief Clear all cells
     */
    void clear() {
        cells.clear();
    }
    
    /**
     * @brief Insert zombie at position
     */
    void insert(size_t zombie_idx, float x, float y, float z) {
        int64_t key = compute_hash(x, y, z);
        cells[key].zombie_indices.push_back(zombie_idx);
    }
    
    /**
     * @brief Get zombies in cell at position
     */
    const std::vector<size_t>* get_cell(float x, float y, float z) const {
        int64_t key = compute_hash(x, y, z);
        auto it = cells.find(key);
        return (it != cells.end()) ? &it->second.zombie_indices : nullptr;
    }
};

// ============================================================================
// MULTITHREADING ZOMBIE OPTIMIZER
// ============================================================================

/**
 * @class MultithreadingZombieOptimizer
 * @brief High-level API for parallel zombie processing
 * 
 * Coordinates multithreading across zombie population operations.
 * Provides thread pool integration and load balancing.
 */
class MultithreadingZombieOptimizer {
public:
    /**
     * @brief Initialize multithreading optimizer
     * @param thread_pool Reference to global thread pool
     */
    static void initialize(::threading::ThreadPool& thread_pool) noexcept {
        thread_pool_ = &thread_pool;
        is_initialized_ = true;
        processor_.reset(new ::threading::ParallelEntityProcessor(thread_pool));
    }
    
    /**
     * @brief Check if multithreading is enabled
     */
    static bool is_enabled() noexcept {
        return is_initialized_;
    }
    
    /**
     * @brief Get number of worker threads
     */
    static size_t get_worker_count() noexcept {
        return thread_pool_ ? thread_pool_->num_workers() : 0;
    }
    
    // ========================================================================
    // PARALLEL AI UPDATES
    // ========================================================================
    
    /**
     * @brief Update zombie AI state for all zombies in parallel
     * 
     * Distributes zombie AI update work across thread pool.
     * Each thread processes a batch of zombies to reduce contention.
     * 
     * @param zombie_count Total number of zombies to update
     * @param update_func Function: f(size_t zombie_index) - updates one zombie
     * @param batch_size Zombies per task (default 32)
     * @return Time elapsed in milliseconds
     */
    static double parallel_update_ai(
        size_t zombie_count,
        std::function<void(size_t)> update_func,
        size_t batch_size = 32) noexcept {
        
        if (!is_initialized_ || zombie_count == 0) return 0.0;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        
        processor_->process_batch(zombie_count, update_func, batch_size);
        processor_->wait();
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time);
        return duration.count() / 1000.0;  // Convert to milliseconds
    }
    
    // ========================================================================
    // PARALLEL POSITION UPDATES
    // ========================================================================
    
    /**
     * @brief Update zombie positions in parallel
     * 
     * Applies velocity to positions: pos += vel * dt
     * Uses thread pool for batch-based parallelization.
     * 
     * @param positions Array of (x, y, z) positions
     * @param velocities Array of (vx, vy, vz) velocities
     * @param dt Time step
     * @param zombie_count Number of zombies
     * @return Time elapsed in milliseconds
     */
    static double parallel_update_positions(
        float* positions,
        const float* velocities,
        float dt,
        size_t zombie_count) noexcept {
        
        if (!is_initialized_ || zombie_count == 0) return 0.0;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        
        // Batch size: 64 zombies per task
        size_t batch_size = 64;
        size_t num_batches = (zombie_count + batch_size - 1) / batch_size;
        
        for (size_t batch = 0; batch < num_batches; ++batch) {
            size_t start = batch * batch_size;
            size_t end = std::min(start + batch_size, zombie_count);
            
            thread_pool_->submit([positions, velocities, dt, start, end]() {
                for (size_t i = start; i < end; ++i) {
                    size_t pos_idx = i * 3;
                    size_t vel_idx = i * 3;
                    
                    // pos[i] += vel[i] * dt
                    positions[pos_idx + 0] += velocities[vel_idx + 0] * dt;
                    positions[pos_idx + 1] += velocities[vel_idx + 1] * dt;
                    positions[pos_idx + 2] += velocities[vel_idx + 2] * dt;
                }
            }, 60);  // Medium priority
        }
        
        thread_pool_->wait_all();
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time);
        return duration.count() / 1000.0;
    }
    
    // ========================================================================
    // PARALLEL COLLISION DETECTION
    // ========================================================================
    
    /**
     * @brief Perform parallel collision detection using spatial hashing
     * 
     * Divides space into grid cells and tests collisions within cells.
     * Massively parallel - each cell processed independently.
     * 
     * @param positions Zombie positions (x, y, z per zombie)
     * @param zombie_count Number of zombies
     * @param collision_func Function: f(size_t idx1, size_t idx2, float dist_sq)
     * @param collision_radius Collision detection radius
     * @return Time elapsed in milliseconds
     */
    static double parallel_collision_detection(
        const float* positions,
        size_t zombie_count,
        std::function<void(size_t, size_t, float)> collision_func,
        float collision_radius = 2.0f) noexcept {
        
        if (!is_initialized_ || zombie_count == 0) return 0.0;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        
        // Build spatial hash grid
        SpatialHashGrid grid;
        for (size_t i = 0; i < zombie_count; ++i) {
            size_t pos_idx = i * 3;
            grid.insert(i, positions[pos_idx + 0], 
                       positions[pos_idx + 1], positions[pos_idx + 2]);
        }
        
        float collision_radius_sq = collision_radius * collision_radius;
        
        // Process each grid cell in parallel
        for (const auto& [key, cell] : grid.cells) {
            thread_pool_->submit([&cell, positions, collision_radius_sq, 
                                 &collision_func]() {
                // Test all pairs within this cell
                for (size_t i = 0; i < cell.zombie_indices.size(); ++i) {
                    size_t idx1 = cell.zombie_indices[i];
                    size_t pos_idx1 = idx1 * 3;
                    
                    for (size_t j = i + 1; j < cell.zombie_indices.size(); ++j) {
                        size_t idx2 = cell.zombie_indices[j];
                        size_t pos_idx2 = idx2 * 3;
                        
                        // Distance squared between idx1 and idx2
                        float dx = positions[pos_idx1 + 0] - 
                                   positions[pos_idx2 + 0];
                        float dy = positions[pos_idx1 + 1] - 
                                   positions[pos_idx2 + 1];
                        float dz = positions[pos_idx1 + 2] - 
                                   positions[pos_idx2 + 2];
                        
                        float dist_sq = dx*dx + dy*dy + dz*dz;
                        
                        if (dist_sq < collision_radius_sq) {
                            collision_func(idx1, idx2, dist_sq);
                        }
                    }
                }
            }, 70);  // Higher priority for collision detection
        }
        
        thread_pool_->wait_all();
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time);
        return duration.count() / 1000.0;
    }
    
    // ========================================================================
    // PARALLEL PATHFINDING
    // ========================================================================
    
    /**
     * @brief Process pathfinding requests in parallel
     * 
     * Distributes pathfinding computation across threads.
     * 
     * @param pathfind_count Number of pathfinding requests
     * @param pathfind_func Function: f(size_t request_index) - compute one path
     * @param batch_size Requests per task
     * @return Time elapsed in milliseconds
     */
    static double parallel_pathfinding(
        size_t pathfind_count,
        std::function<void(size_t)> pathfind_func,
        size_t batch_size = 16) noexcept {
        
        if (!is_initialized_ || pathfind_count == 0) return 0.0;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        
        processor_->process_batch(pathfind_count, pathfind_func, batch_size);
        processor_->wait();
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time);
        return duration.count() / 1000.0;
    }
    
    // ========================================================================
    // UTILITY FUNCTIONS
    // ========================================================================
    
    /**
     * @brief Get pending task count
     */
    static size_t get_pending_tasks() noexcept {
        return thread_pool_ ? thread_pool_->pending_tasks() : 0;
    }
    
    /**
     * @brief Get active task count
     */
    static size_t get_active_tasks() noexcept {
        return thread_pool_ ? thread_pool_->active_tasks() : 0;
    }
    
    /**
     * @brief Wait for all pending tasks
     */
    static void wait_all() noexcept {
        if (thread_pool_) {
            thread_pool_->wait_all();
        }
    }
    
    /**
     * @brief Get thread pool utilization (0.0 to 1.0)
     */
    static double get_utilization() noexcept {
        if (!thread_pool_) return 0.0;
        
        size_t total_capacity = thread_pool_->num_workers();
        if (total_capacity == 0) return 0.0;
        
        size_t active = thread_pool_->active_tasks();
        return static_cast<double>(active) / static_cast<double>(total_capacity);
    }
    
    /**
     * @brief Get configuration info for logging
     */
    static void log_config() noexcept {
        if (!is_initialized_) {
            printf("MultithreadingZombieOptimizer: NOT INITIALIZED\n");
            return;
        }
        
        printf("MultithreadingZombieOptimizer Configuration:\n");
        printf("  Worker threads: %zu\n", get_worker_count());
        printf("  Spatial grid cell size: %.1f units\n", 
               SpatialHashGrid::CELL_SIZE);
        printf("  Status: ACTIVE\n");
    }

private:
    static ::threading::ThreadPool* thread_pool_;
    static std::unique_ptr<::threading::ParallelEntityProcessor> processor_;
    static bool is_initialized_;
};

// Static member initialization (defined in implementation file)
inline ::threading::ThreadPool* MultithreadingZombieOptimizer::thread_pool_ = nullptr;
inline std::unique_ptr<::threading::ParallelEntityProcessor> 
    MultithreadingZombieOptimizer::processor_ = nullptr;
inline bool MultithreadingZombieOptimizer::is_initialized_ = false;

}  // namespace threading_optimizer
}  // namespace popman
}  // namespace zombie

#endif  // MULTITHREADING_ZOMBIE_OPTIMIZER_H
