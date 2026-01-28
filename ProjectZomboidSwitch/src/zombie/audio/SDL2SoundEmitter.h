#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace audio {

class SDL2SoundEmitter {
public:
    SDL2SoundEmitter();
    ~SDL2SoundEmitter();

    int64_t playSound(const std::string& name);
    int stopSound(int64_t id);
    void stopAll();
    void setVolume(int64_t id, float volume);
    void setPitch(int64_t id, float pitch);
    void setPos(float x, float y, float z);
    void setVolumeAll(float volume);

private:
    struct SoundInstance {
        Mix_Chunk* chunk = nullptr;
        int channel = -1;
    };
    std::unordered_map<int64_t, SoundInstance> sounds_;
    int64_t nextId_ = 1;
};

} // namespace audio
