#include "SoundManager.h"
#include <algorithm>
#include <iostream>

namespace zombie {
namespace audio {

SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::getInstance() {
 if (!instance) {
 instance = new SoundManager();
 }
 return instance;
}

SoundManager::SoundManager()
 : mediaPath("../media/")
 , masterVolume(1.0f)
 , musicVolume(1.0f)
 , soundVolume(1.0f)
 , currentMusic(nullptr)
 , initialized(false)
{
}

SoundManager::~SoundManager() {
 shutdown();
}

bool SoundManager::init(int frequency, int channels) {
 if (initialized) {
 return true;
 }
 
 // Initialize SDL_mixer
 if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, 2048) < 0) {
 std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
 return false;
 }
 
 // Allocate mixing channels for sound effects
 Mix_AllocateChannels(16);
 
 initialized = true;
 std::cout << "SoundManager initialized: " << frequency << "Hz, " << channels << " channels" << std::endl;

 // Apply any preconfigured volumes after initialization
 applyVolumes();
 
 return true;
}

void SoundManager::shutdown() {
 if (!initialized) {
 return;
 }
 
 stopMusic();
 unloadAll();
 
 Mix_CloseAudio();
 initialized = false;
}

bool SoundManager::loadMusic(const std::string& name, const std::string& path) {
 if (!initialized) {
 std::cerr << "SoundManager not initialized" << std::endl;
 return false;
 }
 
 // Check if already loaded
 auto it = musicCache.find(name);
 if (it != musicCache.end()) {
 return true;
 }
 
 std::string fullPath = mediaPath + path;
 Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
 
 if (!music) {
 std::cerr << "Failed to load music: " << fullPath << " - " << Mix_GetError() << std::endl;
 return false;
 }
 
 musicCache[name] = music;
 std::cout << "Loaded music: " << name << std::endl;
 
 return true;
}

void SoundManager::playMusic(const std::string& name, int loops) {
 if (!initialized) return;
 
 auto it = musicCache.find(name);
 if (it == musicCache.end()) {
 std::cerr << "Music not found: " << name << std::endl;
 return;
 }
 
 if (currentMusic) {
 Mix_HaltMusic();
 }
 
 currentMusic = it->second;
 currentMusicName = name;
 
 if (Mix_PlayMusic(currentMusic, loops) < 0) {
 std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
 }
}

void SoundManager::pauseMusic() {
 if (initialized && Mix_PlayingMusic()) {
 Mix_PauseMusic();
 }
}

void SoundManager::resumeMusic() {
 if (initialized && Mix_PausedMusic()) {
 Mix_ResumeMusic();
 }
}

void SoundManager::stopMusic() {
 if (initialized) {
 Mix_HaltMusic();
 currentMusic = nullptr;
 currentMusicName.clear();
 }
}

void SoundManager::setMusicVolume(float volume) {
 musicVolume = std::clamp(volume, 0.0f, 1.0f);
 applyVolumes();
}

bool SoundManager::isMusicPlaying() const {
 return initialized && Mix_PlayingMusic();
}

bool SoundManager::loadSound(const std::string& name, const std::string& path) {
 if (!initialized) {
 std::cerr << "SoundManager not initialized" << std::endl;
 return false;
 }
 
 // Check if already loaded
 auto it = soundCache.find(name);
 if (it != soundCache.end()) {
 return true;
 }
 
 std::string fullPath = mediaPath + path;
 Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
 
 if (!sound) {
 std::cerr << "Failed to load sound: " << fullPath << " - " << Mix_GetError() << std::endl;
 return false;
 }
 
 soundCache[name] = sound;
 std::cout << "Loaded sound: " << name << std::endl;
 
 return true;
}

void SoundManager::playSound(const std::string& name, int loops) {
 if (!initialized) return;
 
 auto it = soundCache.find(name);
 if (it == soundCache.end()) {
 std::cerr << "Sound not found: " << name << std::endl;
 return;
 }
 
 // Play on first available channel (-1)
 if (Mix_PlayChannel(-1, it->second, loops) < 0) {
 std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
 }
}

void SoundManager::setSoundVolume(float volume) {
 soundVolume = std::clamp(volume, 0.0f, 1.0f);
 applyVolumes();
}

void SoundManager::setMasterVolume(float volume) {
 masterVolume = std::clamp(volume, 0.0f, 1.0f);
 applyVolumes();
}

void SoundManager::unloadMusic(const std::string& name) {
 auto it = musicCache.find(name);
 if (it != musicCache.end()) {
 if (it->second == currentMusic) {
 stopMusic();
 }
 Mix_FreeMusic(it->second);
 musicCache.erase(it);
 }
}

void SoundManager::unloadSound(const std::string& name) {
 auto it = soundCache.find(name);
 if (it != soundCache.end()) {
 Mix_FreeChunk(it->second);
 soundCache.erase(it);
 }
}

void SoundManager::applyVolumes() {
 if (!initialized) {
 return;
 }

 const int musicMix = static_cast<int>(masterVolume * musicVolume * MIX_MAX_VOLUME);
 const int soundMix = static_cast<int>(masterVolume * soundVolume * MIX_MAX_VOLUME);

 Mix_VolumeMusic(musicMix);
 Mix_Volume(-1, soundMix);
}

void SoundManager::unloadAll() {
 // Unload all music
 for (auto& pair : musicCache) {
 Mix_FreeMusic(pair.second);
 }
 musicCache.clear();
 currentMusic = nullptr;
 currentMusicName.clear();
 
 // Unload all sounds
 for (auto& pair : soundCache) {
 Mix_FreeChunk(pair.second);
 }
 soundCache.clear();
}

} // namespace audio
} // namespace zombie
