#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include "AudioBatching.h"
#include "HotPathProfiler.h"

namespace zombie {
namespace audio {

// ============================================================================
// OPTIMIZED SOUND MANAGER WITH AUDIO BATCHING
// ============================================================================

/**
 * Enhancement wrapper for SoundManager that adds audio command batching
 * and spatial audio processing for improved performance.
 */
class OptimizedSoundManager {
public:
    // Configuration
    static constexpr uint32_t DEFAULT_BATCH_SIZE = 256;
    static constexpr uint32_t MOBILE_BATCH_SIZE = 128;  // Switch - lower latency
    static constexpr uint32_t DESKTOP_BATCH_SIZE = 512; // PC - higher throughput

    explicit OptimizedSoundManager(uint32_t batch_size = DEFAULT_BATCH_SIZE);
    ~OptimizedSoundManager() = default;

    // Initialize sound system
    void initialize() noexcept;
    void shutdown() noexcept;

    // ========================================================================
    // SOUND PLAYBACK (BATCHED)
    // ========================================================================

    // Play sound at position (automatically batched)
    void play_sound(std::string_view sound_file,
                   float x, float y, float z,
                   float volume = 1.0f,
                   float range = 100.0f) noexcept {
        PROFILE_SCOPE("PlaySound");
        batch_system_.play_sound(sound_file, x, y, z, volume, range);
    }

    // Play sound without spatial positioning
    void play_sound_2d(std::string_view sound_file,
                      float volume = 1.0f) noexcept {
        PROFILE_SCOPE("PlaySound2D");
        batch_system_.play_sound(sound_file, 0, 0, 0, volume, 0);
    }

    // Stop sound
    void stop_sound(uint32_t sound_id) noexcept {
        PROFILE_SCOPE("StopSound");
        batch_system_.stop_sound(sound_id);
    }

    // Set volume
    void set_volume(uint32_t sound_id, float volume) noexcept {
        batch_system_.set_volume(sound_id, volume);
    }

    // Set pitch
    void set_pitch(uint32_t sound_id, float pitch) noexcept {
        batch_system_.set_pitch(sound_id, pitch);
    }

    // ========================================================================
    // SPATIAL AUDIO
    // ========================================================================

    // Update listener position (player camera)
    void update_listener_position(float x, float y, float z) noexcept {
        PROFILE_SCOPE("UpdateListener");
        spatial_audio_.set_listener_position(x, y, z);
    }

    // Calculate volume attenuation based on distance
    float calculate_attenuation(float source_x, float source_y, float source_z,
                               float range) const noexcept {
        return spatial_audio_.calculate_volume_attenuation(
            source_x, source_y, source_z, range);
    }

    // Calculate stereo panning
    float calculate_pan(float source_x, float source_y) const noexcept {
        return spatial_audio_.calculate_pan(source_x, source_y);
    }

    // Get listener position
    jni::audio::SpatialAudioManager::ListenerPosition get_listener_position() const noexcept {
        return spatial_audio_.get_listener_position();
    }

    // ========================================================================
    // BATCHING & PROCESSING
    // ========================================================================

    // Flush current batch manually
    void flush_batch() noexcept {
        PROFILE_SCOPE("FlushBatch");
        batch_system_.flush_batch();
    }

    // Process all pending batches
    void process_batches(
        std::function<void(const jni::audio::AudioBatch&)> processor) noexcept {
        PROFILE_SCOPE("ProcessBatches");
        batch_system_.process_all_batches(processor);
    }

    // Auto-process (call from game loop)
    void update(float delta_time) noexcept {
        PROFILE_SCOPE("AudioUpdate");
        flush_batch();  // Flush any pending commands
        
        // Process batches
        process_batches([this](const jni::audio::AudioBatch& batch) {
            execute_batch(batch);
        });
    }

    // ========================================================================
    // STATISTICS & MONITORING
    // ========================================================================

    // Get batch system statistics
    jni::audio::AudioBatchingSystem::Statistics get_statistics() const noexcept {
        return batch_system_.get_statistics();
    }

    // Print audio system status
    void print_status() const noexcept {
        auto stats = get_statistics();
        printf("\nAudio System Status:\n");
        printf("  Total Commands: %llu\n", stats.queued_commands);
        printf("  Batches: %llu\n", stats.batches_processed);
        printf("  Avg Batch Size: %.1f commands\n", stats.avg_batch_size());
        printf("  Pending Batches: %zu\n", batch_system_.get_pending_batch_count());
    }

    // Reset statistics
    void reset_statistics() noexcept {
        batch_system_.reset_statistics();
    }

    // Get pending batch count
    size_t get_pending_batch_count() const noexcept {
        return batch_system_.get_pending_batch_count();
    }

    // Get batch system
    jni::audio::AudioBatchingSystem& get_batch_system() noexcept {
        return batch_system_;
    }

    const jni::audio::AudioBatchingSystem& get_batch_system() const noexcept {
        return batch_system_;
    }

private:
    jni::audio::AudioBatchingSystem batch_system_;
    jni::audio::SpatialAudioManager spatial_audio_;

    // Execute a batch of audio commands
    void execute_batch(const jni::audio::AudioBatch& batch) noexcept;
};

// ============================================================================
// AMBIENT SOUND MANAGER (OPTIMIZED)
// ============================================================================

class OptimizedAmbientSoundManager {
public:
    explicit OptimizedAmbientSoundManager(uint32_t batch_size = 128);
    ~OptimizedAmbientSoundManager() = default;

    // Queue ambient sound
    void queue_ambient_sound(std::string_view sound_file,
                            float x, float y, float z,
                            float volume = 0.5f,
                            float range = 50.0f) noexcept {
        PROFILE_SCOPE("QueueAmbient");
        batch_system_.play_sound(sound_file, x, y, z, volume, range);
    }

    // Process all ambient sounds
    void update() noexcept {
        PROFILE_SCOPE("AmbientUpdate");
        batch_system_.flush_batch();
        
        auto batch = batch_system_.get_next_batch();
        while (batch) {
            execute_batch(*batch);
            batch = batch_system_.get_next_batch();
        }
    }

    // Get statistics
    jni::audio::AudioBatchingSystem::Statistics get_statistics() const noexcept {
        return batch_system_.get_statistics();
    }

    // Print status
    void print_status() const noexcept {
        auto stats = get_statistics();
        printf("\nAmbient Sound System Status:\n");
        printf("  Total Commands: %llu\n", stats.queued_commands);
        printf("  Batches: %llu\n", stats.batches_processed);
        printf("  Avg Batch Size: %.1f\n", stats.avg_batch_size());
    }

    // Reset statistics
    void reset_statistics() noexcept {
        batch_system_.reset_statistics();
    }

private:
    jni::audio::AudioBatchingSystem batch_system_;

    void execute_batch(const jni::audio::AudioBatch& batch) noexcept;
};

}  // namespace audio
}  // namespace zombie
