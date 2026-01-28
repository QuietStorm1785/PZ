#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALSoundEmitter.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include <glm/vec2.hpp>
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


enum class HelicopterState {
    Arriving,
    Hovering,
    Searching,
    Leaving
};

class Helicopter {
public:
    static constexpr float MAX_BOTHER_SECONDS = 60.0F;
    static constexpr float MAX_UNSEEN_SECONDS = 15.0F;
    static constexpr int RADIUS_HOVER = 50;
    static constexpr int RADIUS_SEARCH = 100;

    HelicopterState state;
    std::shared_ptr<IsoGameCharacter> target;
    float timeSinceChopperSawPlayer = 0.0f;
    float hoverTime = 0.0f;
    float searchTime = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float targetX = 0.0f;
    float targetY = 0.0f;
    glm::vec2 move{0.0f, 0.0f};
    bool bActive = false;
    static long inst;
    static OpenALSoundEventDescription event;
    bool bSoundStarted = false;
    float volume = 0.0f;
    float occlusion = 0.0f;

    void pickRandomTarget();
    void setTarget(std::shared_ptr<IsoGameCharacter> target);
    void changeState(HelicopterState newState);
    void update();
    void updateSound();
    bool isTargetVisible() const;
    void deactivate();
    bool isActive() const;
    void clientSync(float x, float y, bool active);
};
} // namespace iso
} // namespace zombie
