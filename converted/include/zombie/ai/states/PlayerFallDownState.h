#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerFallDownState : public State {
public:
  static const PlayerFallDownState _instance = new PlayerFallDownState();

  static PlayerFallDownState instance() { return _instance; }

  void enter(IsoGameCharacter owner) {
    owner.setIgnoreMovement(true);
    owner.clearVariable("bKnockedDown");
    if (owner.isDead() && !GameServer.bServer && !GameClient.bClient) {
      owner.Kill(nullptr);
    }
  }

  void execute(IsoGameCharacter owner) {}

  void exit(IsoGameCharacter owner) {
    owner.setIgnoreMovement(false);
    owner.setOnFloor(true);
  }

  void animEvent(IsoGameCharacter owner, AnimEvent event) {
    if (GameClient.bClient &&
        event.m_EventName.equalsIgnoreCase("FallOnFront")) {
      owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue));
    }
  }
}
} // namespace states
} // namespace ai
} // namespace zombie
