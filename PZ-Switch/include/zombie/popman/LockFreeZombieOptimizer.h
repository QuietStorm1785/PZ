/**
 * @file LockFreeZombieOptimizer.h
 * @brief Lock-free data structures for zombie-specific scenarios
 * 
 * Eliminates mutex contention in high-traffic subsystems:
 * - Audio command queue (lock-free MPMC queue)
 * - Entity pool free list (lock-free stack)
 * - Collision event queue (lock-free ring buffer)
 * 
 * Performance Target: +5-10% FPS via reduced lock contention
 * Integration: Works with LockFreeStructures.h and ZombiePopulationManager
 * 
 * @date January 19, 2026
 * @author PZ Optimization Team
 */

#pragma once

#include "LockFreeStructures.h"
#include <functional>
#include <vector>
#include <memory>

namespace zombie {
namespace popman {
namespace lockfree_optimizer {

// ============================================================================
// AUDIO COMMAND BUFFER (Lock-Free Queue)
// ============================================================================

/**
 * @struct AudioCommand
 * @brief Audio operation to be queued lock-free
 */
struct AudioCommand {
    enum class CommandType {
        PLAY_SOUND = 0,
        STOP_SOUND = 1,
        SET_VOLUME = 2,
        SET_PITCH = 3,
        SET_POSITION = 4,
    };
    
    CommandType type;
    uint32_t sound_id;
    float volume;
    float pitch;
    float x, y, z;
    float max_distance;
};

// ============================================================================
// COLLISION EVENT BUFFER (Lock-Free Ring Buffer)
// ============================================================================

/**
 * @struct CollisionEvent
 * @brief Collision detection event
 */
struct CollisionEvent {
    uint32_t zombie_a;
    uint32_t zombie_b;
    float distance_squared;
    float timestamp;
};

// ============================================================================
// ENTITY POOL BUFFER (Lock-Free Stack)
// ============================================================================

/**
 * @struct PooledEntityHandle
 * @brief Handle to a reusable entity in the pool
 */
struct PooledEntityHandle {
    uint32_t entity_id;
    uint32_t generation;  // For ABA problem detection
};

// ============================================================================
// LOCK-FREE ZOMBIE OPTIMIZER
// ============================================================================

/**
 * @class LockFreeZombieOptimizer
 * @brief Provides lock-free queuing for zombie operations
 * 
 * Coordinates access to high-contention resources without locks.
 * Allows multiple threads to safely queue operations without blocking.
 */
class LockFreeZombieOptimizer {
public:
    /**
     * @brief Initialize lock-free structures
     */
    static void initialize() noexcept {
        audio_command_queue_ = std::make_unique<AudioCommandQueue>();
        collision_event_queue_ = std::make_unique<CollisionEventQueue>();
        entity_pool_stack_ = std::make_unique<EntityPoolStack>();
        is_initialized_ = true;
    }
    
    /**
     * @brief Check if lock-free optimizer is initialized
     */
    static bool is_enabled() noexcept {
        return is_initialized_;
    }
    
    // ========================================================================
    // LOCK-FREE AUDIO COMMAND QUEUE
    // ========================================================================
    
    /**
     * @brief Enqueue an audio command lock-free
     * 
     * Multiple threads can safely call this without blocking.
     * Command will be processed asynchronously by audio thread.
     * 
     * @param cmd Audio command to queue
     * @return true if queued successfully, false if queue full
     */
    static bool enqueue_audio_command(const AudioCommand& cmd) noexcept {
        if (!is_initialized_) return false;
        return audio_command_queue_->try_enqueue(cmd);
    }
    
    /**
     * @brief Try to dequeue an audio command
     * 
     * Non-blocking: returns immediately if no command available.
     * 
     * @param cmd [out] Dequeued command
     * @return true if command available, false if queue empty
     */
    static bool dequeue_audio_command(AudioCommand& cmd) noexcept {
        if (!is_initialized_) return false;
        return audio_command_queue_->try_dequeue(cmd);
    }
    
    /**
     * @brief Get pending audio command count
     * @note Count is approximate due to concurrent access
     */
    static size_t audio_command_count() noexcept {
        if (!is_initialized_) return 0;
        return audio_command_queue_->size();
    }
    
    /**
     * @brief Process all queued audio commands
     * 
     * Drains the queue and calls handler for each command.
     * 
     * @param handler Function: f(const AudioCommand& cmd)
     * @return Number of commands processed
     */
    static size_t process_audio_commands(
        std::function<void(const AudioCommand&)> handler) noexcept {
        
        if (!is_initialized_) return 0;
        
        AudioCommand cmd;
        size_t count = 0;
        
        while (audio_command_queue_->try_dequeue(cmd)) {
            try {
                handler(cmd);
            } catch (...) {
                // Silently ignore handler exceptions
            }
            count++;
        }
        
        return count;
    }
    
    // ========================================================================
    // LOCK-FREE COLLISION EVENT QUEUE
    // ========================================================================
    
    /**
     * @brief Enqueue a collision event lock-free
     * 
     * Multiple collision detection threads can write to this
     * queue without contention.
     * 
     * @param evt Collision event
     * @return true if queued, false if queue full
     */
    static bool enqueue_collision_event(const CollisionEvent& evt) noexcept {
        if (!is_initialized_) return false;
        return collision_event_queue_->try_enqueue(evt);
    }
    
    /**
     * @brief Try to dequeue a collision event
     * @param evt [out] Collision event
     * @return true if event available, false if queue empty
     */
    static bool dequeue_collision_event(CollisionEvent& evt) noexcept {
        if (!is_initialized_) return false;
        return collision_event_queue_->try_dequeue(evt);
    }
    
    /**
     * @brief Get pending collision event count
     * @note Count is approximate
     */
    static size_t collision_event_count() noexcept {
        if (!is_initialized_) return 0;
        return collision_event_queue_->size();
    }
    
    /**
     * @brief Process all queued collision events
     * 
     * @param handler Function: f(const CollisionEvent& evt)
     * @return Number of events processed
     */
    static size_t process_collision_events(
        std::function<void(const CollisionEvent&)> handler) noexcept {
        
        if (!is_initialized_) return 0;
        
        CollisionEvent evt;
        size_t count = 0;
        
        while (collision_event_queue_->try_dequeue(evt)) {
            try {
                handler(evt);
            } catch (...) {
                // Silently ignore handler exceptions
            }
            count++;
        }
        
        return count;
    }
    
    // ========================================================================
    // LOCK-FREE ENTITY POOL STACK
    // ========================================================================
    
    /**
     * @brief Allocate an entity from the pool (lock-free)
     * 
     * @return Entity handle, or invalid if pool empty
     */
    static PooledEntityHandle allocate_entity() noexcept {
        if (!is_initialized_) return PooledEntityHandle{0, 0};
        
        PooledEntityHandle handle;
        if (entity_pool_stack_->try_pop(handle)) {
            return handle;
        }
        
        return PooledEntityHandle{0, 0};
    }
    
    /**
     * @brief Return an entity to the pool (lock-free)
     * 
     * @param handle Entity handle to return
     */
    static void deallocate_entity(const PooledEntityHandle& handle) noexcept {
        if (!is_initialized_) return;
        
        PooledEntityHandle updated = handle;
        updated.generation++;  // Bump generation for ABA handling
        entity_pool_stack_->push(updated);
    }
    
    /**
     * @brief Pre-allocate entity pool
     * 
     * @param count Number of entities to pre-allocate
     */
    static void preallocate_entities(uint32_t count) noexcept {
        if (!is_initialized_) return;
        
        for (uint32_t i = 0; i < count; ++i) {
            entity_pool_stack_->push(PooledEntityHandle{i, 0});
        }
    }
    
    // ========================================================================
    // STATISTICS
    // ========================================================================
    
    /**
     * @brief Get current queue depths for monitoring
     */
    struct QueueStats {
        size_t audio_commands;
        size_t collision_events;
        bool audio_queue_full;
        bool collision_queue_full;
    };
    
    /**
     * @brief Get queue statistics
     */
    static QueueStats get_queue_stats() noexcept {
        if (!is_initialized_) {
            return QueueStats{0, 0, false, false};
        }
        
        return QueueStats{
            audio_command_queue_->size(),
            collision_event_queue_->size(),
            audio_command_queue_->full(),
            collision_event_queue_->full()
        };
    }
    
    /**
     * @brief Log configuration
     */
    static void log_config() noexcept {
        if (!is_initialized_) {
            printf("LockFreeZombieOptimizer: NOT INITIALIZED\n");
            return;
        }
        
        printf("LockFreeZombieOptimizer Configuration:\n");
        printf("  Audio command queue capacity: 65536\n");
        printf("  Collision event queue capacity: 32768\n");
        printf("  Entity pool capacity: 16384\n");
        printf("  Status: ACTIVE\n");
    }

private:
    // Type aliases for queues
    using AudioCommandQueue = ::lockfree::LockFreeQueue<AudioCommand, 65536>;
    using CollisionEventQueue = ::lockfree::LockFreeQueue<CollisionEvent, 32768>;
    using EntityPoolStack = ::lockfree::LockFreeStack<PooledEntityHandle, 16384>;
    
    // Singleton queue instances
    static std::unique_ptr<AudioCommandQueue> audio_command_queue_;
    static std::unique_ptr<CollisionEventQueue> collision_event_queue_;
    static std::unique_ptr<EntityPoolStack> entity_pool_stack_;
    static bool is_initialized_;
};

// Static member initialization (defined in implementation file)
inline std::unique_ptr<LockFreeZombieOptimizer::AudioCommandQueue>
    LockFreeZombieOptimizer::audio_command_queue_ = nullptr;
inline std::unique_ptr<LockFreeZombieOptimizer::CollisionEventQueue>
    LockFreeZombieOptimizer::collision_event_queue_ = nullptr;
inline std::unique_ptr<LockFreeZombieOptimizer::EntityPoolStack>
    LockFreeZombieOptimizer::entity_pool_stack_ = nullptr;
inline bool LockFreeZombieOptimizer::is_initialized_ = false;

}  // namespace lockfree_optimizer
}  // namespace popman
}  // namespace zombie

#endif  // LOCK_FREE_ZOMBIE_OPTIMIZER_H
