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
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace ai {
namespace states {


class CrawlingZombieTurnState : public State {
public:
    static const CrawlingZombieTurnState _instance = std::make_shared<CrawlingZombieTurnState>();
    static const Vector2 tempVector2_1 = std::make_shared<Vector2>();
    static const Vector2 tempVector2_2 = std::make_shared<Vector2>();

    static CrawlingZombieTurnState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      ((IsoZombie)var1).AllowRepathDelay = 0.0F;
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("TurnSome")) {
    Vector2 var3 = tempVector2_1.set(var1.dir.ToVector());
         Vector2 var4 = "left".equalsIgnoreCase(var2.m_ParameterValue)
            ? IsoDirections.fromIndex(var1.dir.index() + 1).ToVector()
            : IsoDirections.fromIndex(var1.dir.index() - 1).ToVector();
    Vector2 var5 = PZMath.lerp(tempVector2_2, var3, var4, var2.m_TimePc);
         var1.setForwardDirection(var5);
      } else {
         if (var2.m_EventName.equalsIgnoreCase("TurnComplete")) {
            if ("left".equalsIgnoreCase(var2.m_ParameterValue)) {
               var1.dir = IsoDirections.fromIndex(var1.dir.index() + 1);
            } else {
               var1.dir = IsoDirections.fromIndex(var1.dir.index() - 1);
            }

            var1.getVectorFromDirection(var1.getForwardDirection());
         }
      }
   }

    static bool calculateDir(IsoGameCharacter var0, IsoDirections var1) {
      return var1.index() > var0.dir.index() ? var1.index() - var0.dir.index() <= 4 : var1.index() - var0.dir.index() < -4;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
