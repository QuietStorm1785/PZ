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

namespace zombie {
namespace ai {
namespace states {


class ZombieFaceTargetState : public State {
public:
    static const ZombieFaceTargetState _instance = std::make_shared<ZombieFaceTargetState>();

    static ZombieFaceTargetState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      if (var2.getTarget() != nullptr) {
         var2.faceThisObject(var2.getTarget());
      }
   }

    void exit(IsoGameCharacter var1) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
