#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

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
    bool loadMusic(const std::string& name, const std::string& path);
    void playMusic(const std::string& name, int loops = -1); // -1 = infinite loop
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void setMusicVolume(float volume); // 0.0 to 1.0
    bool isMusicPlaying() const;
    
    // Sound effects
    bool loadSound(const std::string& name, const std::string& path);
    void playSound(const std::string& name, int loops = 0);
    void setSoundVolume(float volume); // 0.0 to 1.0
    
    // Master volume
    void setMasterVolume(float volume);
    float getMasterVolume() const { return masterVolume; }
    
    // Cleanup
    void unloadMusic(const std::string& name);
    void unloadSound(const std::string& name);
    void unloadAll();
    
    // Set media path
    void setMediaPath(const std::string& path) { mediaPath = path; }
    std::string getMediaPath() const { return mediaPath; }
    
private:
    static SoundManager* instance;
    
    std::string mediaPath;
    float masterVolume;
    
    // Music
    std::unordered_map<std::string, Mix_Music*> musicCache;
    Mix_Music* currentMusic;
    std::string currentMusicName;
    
    // Sound effects
    std::unordered_map<std::string, Mix_Chunk*> soundCache;
    
    bool initialized;
};

} // namespace audio
} // namespace zombie
