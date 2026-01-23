#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/GameSoundClip.h"

namespace zombie {


class GameSounds {
public:
    virtual ~GameSounds() = default;
    bool play(GameSoundClip var1);

    bool isPlaying();

    bool update();

    void stop();
}
} // namespace zombie
