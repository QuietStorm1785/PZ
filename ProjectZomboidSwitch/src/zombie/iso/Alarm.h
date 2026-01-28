#pragma once
#include <cstdint>
#include "zombie/audio/OpenALSoundEmitter.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {

class Alarm {
public:
    static int64_t inst;
    static OpenALSoundEventDescription event;
    bool finished = false;
    int x;
    int y;
    float volume = 0.0f;
    float occlusion = 0.0f;
    float endGameTime = 0.0f;

    Alarm(int x, int y);
    void update();
    void updateSound();
};

} // namespace iso
} // namespace zombie
