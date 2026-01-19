#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <memory>
#include <functional>
#include <cstdint>
#include <string_view>
#include "JNIBridge.h"

namespace jni {
namespace audio {

// ============================================================================
// AUDIO COMMAND TYPES
// ============================================================================

enum class AudioCommandType : uint8_t {
    PLAY_SOUND,
    STOP_SOUND,
    SET_VOLUME,
    SET_PITCH,
    LOOP_SOUND,
    SPATIAL_AUDIO,
    UPDATE_LISTENER,
};

// ============================================================================
// AUDIO COMMAND
// ============================================================================

struct AudioCommand {
    AudioCommandType type;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float volume = 1.0f;
    float pitch = 1.0f;
    float range = 100.0f;
    uint32_t sound_id = 0;
    uint32_t source_id = 0;
    bool loop = false;
    std::string sound_path;

    AudioCommand(AudioCommandType cmd_type)
        : type(cmd_type) {}
};

// ============================================================================
// AUDIO BATCH
// ============================================================================

class AudioBatch {
public:
    AudioBatch() = default;

    void add_command(const AudioCommand& cmd) noexcept {
        commands_.push_back(cmd);
    }

    void clear() noexcept {
        commands_.clear();
    }

    const std::vector<AudioCommand>& get_commands() const noexcept {
        return commands_;
    }

    size_t size() const noexcept {
        return commands_.size();
    }

    bool empty() const noexcept {
        return commands_.empty();
    }

private:
    std::vector<AudioCommand> commands_;
};

// ============================================================================
// AUDIO BATCHING SYSTEM
// ============================================================================

class AudioBatchingSystem {
public:
    explicit AudioBatchingSystem(uint32_t batch_size_hint = 256)
        : batch_size_hint_(batch_size_hint) {
        current_batch_ = std::make_unique<AudioBatch>();
    }

    ~AudioBatchingSystem() = default;

    // Add a command to current batch
    void add_sound_command(const AudioCommand& cmd) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        current_batch_->add_command(cmd);
        stats_.queued_commands++;

        // Auto-flush if batch is full
        if (current_batch_->size() >= batch_size_hint_) {
            flush_batch();
        }
    }

    // Play sound (convenience method)
    void play_sound(std::string_view sound_path,
                   float x, float y, float z,
                   float volume = 1.0f,
                   float range = 100.0f,
                   uint32_t source_id = 0) noexcept {
        AudioCommand cmd(AudioCommandType::PLAY_SOUND);
        cmd.sound_path = sound_path;
        cmd.x = x;
        cmd.y = y;
        cmd.z = z;
        cmd.volume = volume;
        cmd.range = range;
        cmd.source_id = source_id;
        add_sound_command(cmd);
    }

    // Stop sound
    void stop_sound(uint32_t sound_id) noexcept {
        AudioCommand cmd(AudioCommandType::STOP_SOUND);
        cmd.sound_id = sound_id;
        add_sound_command(cmd);
    }

    // Set volume
    void set_volume(uint32_t sound_id, float volume) noexcept {
        AudioCommand cmd(AudioCommandType::SET_VOLUME);
        cmd.sound_id = sound_id;
        cmd.volume = volume;
        add_sound_command(cmd);
    }

    // Set pitch
    void set_pitch(uint32_t sound_id, float pitch) noexcept {
        AudioCommand cmd(AudioCommandType::SET_PITCH);
        cmd.sound_id = sound_id;
        cmd.pitch = pitch;
        add_sound_command(cmd);
    }

    // Update listener position (for spatial audio)
    void update_listener(float x, float y, float z) noexcept {
        AudioCommand cmd(AudioCommandType::UPDATE_LISTENER);
        cmd.x = x;
        cmd.y = y;
        cmd.z = z;
        add_sound_command(cmd);
    }

    // Flush current batch to queue
    void flush_batch() noexcept {
        if (!current_batch_->empty()) {
            pending_batches_.push(std::move(current_batch_));
            current_batch_ = std::make_unique<AudioBatch>();
            stats_.batches_queued++;
        }
    }

    // Get next batch for processing
    std::unique_ptr<AudioBatch> get_next_batch() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pending_batches_.empty()) {
            return nullptr;
        }
        auto batch = std::move(pending_batches_.front());
        pending_batches_.pop();
        stats_.batches_processed++;
        return batch;
    }

    // Process all pending batches (for immediate playback)
    void process_all_batches(
        std::function<void(const AudioBatch&)> processor) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        // Process pending batches
        while (!pending_batches_.empty()) {
            processor(*pending_batches_.front());
            pending_batches_.pop();
            stats_.batches_processed++;
        }

        // Process current batch
        if (!current_batch_->empty()) {
            processor(*current_batch_);
            current_batch_->clear();
        }
    }

    // Get statistics
    struct Statistics {
        uint64_t queued_commands = 0;
        uint64_t batches_queued = 0;
        uint64_t batches_processed = 0;

        float avg_batch_size() const noexcept {
            if (batches_processed == 0) return 0.0f;
            return static_cast<float>(queued_commands) / batches_processed;
        }
    };

    Statistics get_statistics() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return stats_;
    }

    // Reset statistics
    void reset_statistics() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        stats_ = Statistics{};
    }

    // Get number of pending batches
    size_t get_pending_batch_count() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return pending_batches_.size();
    }

    // Print report
    void print_report(std::string_view system_name) const noexcept {
        auto stats = get_statistics();
        printf("\n=== Audio Batching System: %s ===\n", system_name.data());
        printf("  Total Commands Queued: %llu\n", stats.queued_commands);
        printf("  Total Batches: %llu\n", stats.batches_processed);
        printf("  Avg Batch Size: %.1f commands\n", stats.avg_batch_size());
        printf("  Pending Batches: %zu\n", get_pending_batch_count());
        printf("=================================\n\n");
    }

private:
    uint32_t batch_size_hint_;
    std::unique_ptr<AudioBatch> current_batch_;
    std::queue<std::unique_ptr<AudioBatch>> pending_batches_;
    mutable std::mutex mutex_;
    mutable Statistics stats_;
};

// ============================================================================
// SPATIAL AUDIO MANAGER
// ============================================================================

class SpatialAudioManager {
public:
    struct ListenerPosition {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    explicit SpatialAudioManager(AudioBatchingSystem& batch_system)
        : batch_system_(batch_system) {}

    // Update listener position
    void set_listener_position(float x, float y, float z) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        listener_.x = x;
        listener_.y = y;
        listener_.z = z;
        batch_system_.update_listener(x, y, z);
    }

    // Calculate distance-based volume attenuation
    float calculate_volume_attenuation(float source_x,
                                       float source_y,
                                       float source_z,
                                       float range) const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        
        float dx = source_x - listener_.x;
        float dy = source_y - listener_.y;
        float dz = source_z - listener_.z;
        float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

        if (distance > range) {
            return 0.0f;
        }
        if (distance == 0.0f) {
            return 1.0f;
        }

        // Linear attenuation
        return 1.0f - (distance / range);
    }

    // Calculate panning for stereo
    float calculate_pan(float source_x, float source_y) const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        
        float dx = source_x - listener_.x;
        // Pan range: -1.0 (left) to 1.0 (right)
        // Clamp to range
        return std::max(-1.0f, std::min(1.0f, dx / 100.0f));
    }

    // Get current listener position
    ListenerPosition get_listener_position() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return listener_;
    }

private:
    AudioBatchingSystem& batch_system_;
    ListenerPosition listener_;
    mutable std::mutex mutex_;
};

}  // namespace audio
}  // namespace jni

#endif  // AUDIO_BATCHING_H
