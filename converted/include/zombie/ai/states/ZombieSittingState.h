#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ZombiePopulationManager.h"
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

class ZombieSittingState : public State {
public:
  static const ZombieSittingState _instance = new ZombieSittingState();

  static ZombieSittingState instance() { return _instance; }

  void enter(IsoGameCharacter owner) {}

  void execute(IsoGameCharacter owner) {
    IsoZombie zombie0 = (IsoZombie)owner;
    if (GameClient.bClient && owner.getCurrentSquare() != nullptr) {
      ZombiePopulationManager.instance.sitAgainstWall(
          zombie0, zombie0.getCurrentSquare());
    }
  }

  void exit(IsoGameCharacter owner) {}
}
} // namespace states
} // namespace ai
} // namespace zombie
