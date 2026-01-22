#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ZombiePopulationManager.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieSittingState : public State {
public:
    static const ZombieSittingState _instance = std::make_shared<ZombieSittingState>();

    static ZombieSittingState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      if (GameClient.bClient && var1.getCurrentSquare() != nullptr) {
         ZombiePopulationManager.instance.sitAgainstWall(var2, var2.getCurrentSquare());
      }
   }

    void exit(IsoGameCharacter var1) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
