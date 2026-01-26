#pragma once
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/javafmod.h"
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
    static FMOD_STUDIO_EVENT_DESCRIPTION* event;
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
