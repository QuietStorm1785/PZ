#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
