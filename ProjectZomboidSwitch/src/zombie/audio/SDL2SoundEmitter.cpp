#include "zombie/audio/SDL2SoundEmitter.h"
#include <iostream>

namespace audio {

SDL2SoundEmitter::SDL2SoundEmitter() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

SDL2SoundEmitter::~SDL2SoundEmitter() {
    stopAll();
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

int64_t SDL2SoundEmitter::playSound(const std::string& name) {
    Mix_Chunk* chunk = Mix_LoadWAV(name.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound: " << name << " Error: " << Mix_GetError() << std::endl;
        return -1;
    }
    int channel = Mix_PlayChannel(-1, chunk, 0);
    if (channel == -1) {
        std::cerr << "Failed to play sound: " << name << " Error: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(chunk);
        return -1;
    }
    int64_t id = nextId_++;
    sounds_[id] = {chunk, channel};
    return id;
}

int SDL2SoundEmitter::stopSound(int64_t id) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        Mix_HaltChannel(it->second.channel);
        Mix_FreeChunk(it->second.chunk);
        sounds_.erase(it);
        return 0;
    }
    return -1;
}

void SDL2SoundEmitter::stopAll() {
    for (auto& [id, inst] : sounds_) {
        Mix_HaltChannel(inst.channel);
        Mix_FreeChunk(inst.chunk);
    }
    sounds_.clear();
}

void SDL2SoundEmitter::setVolume(int64_t id, float volume) {
    auto it = sounds_.find(id);
    if (it != sounds_.end()) {
        Mix_Volume(it->second.channel, static_cast<int>(volume * MIX_MAX_VOLUME));
    }
}

void SDL2SoundEmitter::setPitch(int64_t, float) {
    // SDL2_mixer does not support pitch natively
}

void SDL2SoundEmitter::setPos(float, float, float) {
    // Positioning not implemented in this stub
}

void SDL2SoundEmitter::setVolumeAll(float volume) {
    for (auto& [id, inst] : sounds_) {
        Mix_Volume(inst.channel, static_cast<int>(volume * MIX_MAX_VOLUME));
    }
}

} // namespace audio
