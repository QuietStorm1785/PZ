#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/permission/DefaultStatePermissions.h"
#include "zombie/ai/permission/IStatePermissions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/MoveDeltaModifiers.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {


class State {
public:
    void enter(IsoGameCharacter var1) {
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }

    bool isAttacking(IsoGameCharacter var1) {
    return false;
   }

    bool isMoving(IsoGameCharacter var1) {
    return false;
   }

    bool isDoingActionThatCanBeCancelled() {
    return false;
   }

    void getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
   }

    bool isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    return false;
   }

      std::string getName();
      IStatePermissions* getStatePermissions();
}
} // namespace ai
} // namespace zombie
