#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "zombie/audio/OptimizedAudioSystem.h"

namespace zombie {
namespace audio {

/**
 * SoundManager - Audio playback system using SDL_mixer
 */
class SoundManager {
public:
 static SoundManager* getInstance();
 
 SoundManager();
 ~SoundManager();
 
 // Initialize audio system
 bool init(int frequency = 44100, int channels = 2);
 void shutdown();
 
 // Audio batching and spatial audio (Day 3 Optimization)
 void initialize_audio_batching(uint32_t batch_size = 256) noexcept {
     if (!audio_system) {
         audio_system = std::make_unique<OptimizedSoundManager>(batch_size);
         audio_system->initialize();
     }
 }
 
 void play_spatial_sound(std::string_view sound_name, float x, float y, float z,
                        float volume = 1.0f, float range = 100.0f) noexcept {
     if (audio_system) {
         audio_system->play_sound(sound_name, x, y, z, volume, range);
     }
 }
 
 void update_listener_position(float x, float y, float z) noexcept {
     if (audio_system) {
         audio_system->update_listener_position(x, y, z);
     }
 }
 
 void process_audio_batches() noexcept {
     if (audio_system) {
         audio_system->process_batches();
     }
 }
 
 void print_audio_system_status() const noexcept {
     if (audio_system) {
         audio_system->print_statistics();
     }
 }
 
 // Music playback
 bool loadMusic(std::string_view name, std::string_view path);
 void playMusic(std::string_view name, int loops = -1); // -1 = infinite loop
 void pauseMusic();
 void resumeMusic();
 void stopMusic();
 void setMusicVolume(float volume); // 0.0 to 1.0
 bool isMusicPlaying() const;
 
 // Sound effects
 bool loadSound(std::string_view name, std::string_view path);
 void playSound(std::string_view name, int loops = 0);
 void setSoundVolume(float volume); // 0.0 to 1.0
 
 // Master volume
 void setMasterVolume(float volume);
 float getMasterVolume() const { return masterVolume; }
 
 // Cleanup
 void unloadMusic(std::string_view name);
 void unloadSound(std::string_view name);
 void unloadAll();
 
 // Set media path
 void setMediaPath(std::string_view path) { mediaPath = path; }
 std::string getMediaPath() const { return mediaPath; }
 
private:
 static SoundManager* instance;
 
 std::string mediaPath;
 float masterVolume;
 float musicVolume;
 float soundVolume;
 std::unique_ptr<OptimizedSoundManager> audio_system;
 
 // Music
 std::unordered_map<std::string, Mix_Music*> musicCache;
 Mix_Music* currentMusic;
 std::string currentMusicName;
 
 // Sound effects
 std::unordered_map<std::string, Mix_Chunk*> soundCache;
 
 bool initialized;

 void applyVolumes();
};

} // namespace audio
} // namespace zombie
