#pragma once

#include <memory>
#include <string_view>
#include "AudioBatching.h"
#include "zombie/ISoundSystem.h"

namespace zombie {
namespace audio {

// ============================================================================
// OPTIMIZED SOUND MANAGER WITH BATCHING
// ============================================================================

class OptimizedSoundManager {
public:
    explicit OptimizedSoundManager(uint32_t batch_size = 256)
        : batch_system_(batch_size),
          spatial_audio_(batch_system_) {}

    // Play sound at position
    void play_sound(std::string_view sound_path,
                   float x, float y, float z,
                   float volume = 1.0f,
                   float range = 100.0f,
                   uint32_t source_id = 0) noexcept {
        // Calculate spatial audio parameters
        float attenuated_volume = spatial_audio_.calculate_volume_attenuation(
            x, y, z, range) * volume;
        float pan = spatial_audio_.calculate_pan(x, y);

        // Queue batched command
        batch_system_.play_sound(sound_path, x, y, z, attenuated_volume, range, source_id);
    }

    // Stop sound
    void stop_sound(uint32_t sound_id) noexcept {
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

    // Update listener position (usually player)
    void update_listener_position(float x, float y, float z) noexcept {
        spatial_audio_.set_listener_position(x, y, z);
    }

    // Process all queued commands
    void process_batch() noexcept {
        batch_system_.process_all_batches(
            [this](const jni::audio::AudioBatch& batch) {
                for (const auto& cmd : batch.get_commands()) {
                    execute_audio_command(cmd);
                }
            });
    }

    // Flush immediately
    void flush() noexcept {
        batch_system_.flush_batch();
        process_batch();
    }

    // Get statistics
    struct Statistics {
        jni::audio::AudioBatchingSystem::Statistics batch_stats;
        uint64_t total_processed = 0;
    };

    Statistics get_statistics() const noexcept {
        return {batch_system_.get_statistics(), total_processed_};
    }

    // Print report
    void print_report() const noexcept {
        batch_system_.print_report("OptimizedSoundManager");
    }

private:
    void execute_audio_command(const jni::audio::AudioCommand& cmd) noexcept {
        switch (cmd.type) {
            case jni::audio::AudioCommandType::PLAY_SOUND:
                // Call underlying sound system
                // actual_sound_system_->play(cmd.sound_path, cmd.x, cmd.y, cmd.z, cmd.volume);
                break;

            case jni::audio::AudioCommandType::STOP_SOUND:
                // actual_sound_system_->stop(cmd.sound_id);
                break;

            case jni::audio::AudioCommandType::SET_VOLUME:
                // actual_sound_system_->set_volume(cmd.sound_id, cmd.volume);
                break;

            case jni::audio::AudioCommandType::SET_PITCH:
                // actual_sound_system_->set_pitch(cmd.sound_id, cmd.pitch);
                break;

            case jni::audio::AudioCommandType::UPDATE_LISTENER:
                // Update audio listener position
                break;

            default:
                break;
        }
        total_processed_++;
    }

    jni::audio::AudioBatchingSystem batch_system_;
    jni::audio::SpatialAudioManager spatial_audio_;
    uint64_t total_processed_ = 0;
};

// ============================================================================
// AMBIENT SOUND BATCHER
// ============================================================================

class AmbientSoundBatcher {
public:
    explicit AmbientSoundBatcher(uint32_t batch_size = 128)
        : batch_system_(batch_size) {}

    // Queue ambient sound
    void queue_ambient_sound(std::string_view sound_path,
                            float x, float y, float z,
                            float volume = 0.5f,
                            float range = 50.0f) noexcept {
        batch_system_.play_sound(sound_path, x, y, z, volume, range);
    }

    // Process all ambient sounds
    void process() noexcept {
        batch_system_.flush_batch();

        auto batch = batch_system_.get_next_batch();
        while (batch) {
            // Process batch of ambient sounds
            batch = batch_system_.get_next_batch();
        }
    }

    // Get statistics
    jni::audio::AudioBatchingSystem::Statistics get_statistics() const noexcept {
        return batch_system_.get_statistics();
    }

    void print_report() const noexcept {
        batch_system_.print_report("AmbientSoundBatcher");
    }

private:
    jni::audio::AudioBatchingSystem batch_system_;
};

}  // namespace audio
}  // namespace zombie

#endif  // OPTIMIZED_SOUND_MANAGER_H
