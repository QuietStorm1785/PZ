#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Stats.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class FakeDeadAttackState : public State {
public:
    static const FakeDeadAttackState _instance = std::make_shared<FakeDeadAttackState>();

    static FakeDeadAttackState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.DirectionFromVector(var2.vectorToTarget);
      var2.setFakeDead(false);
      var1.setVisibleToNPCs(true);
      var1.setCollidable(true);
    std::string var3 = "MaleZombieAttack";
      if (var1.isFemale()) {
         var3 = "FemaleZombieAttack";
      }

      var1.getEmitter().playSound(var3);
      if (var2.dynamic_cast<IsoPlayer*>(target) != nullptr && !((IsoPlayer)var2.target).getCharacterTraits().Desensitized.isSet()) {
    IsoPlayer var4 = (IsoPlayer)var2.target;
    Stats var10000 = var4.getStats();
         var10000.Panic = var10000.Panic + var4.getBodyDamage().getPanicIncreaseValue() * 3.0F;
      }
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    IsoZombie var3 = (IsoZombie)var1;
      if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck")
         && var1.isAlive()
         && var3.isTargetInCone(1.5F, 0.9F)
         && var3.dynamic_cast<IsoGameCharacter*>(target) != nullptr var4
         && (var4.getVehicle() == nullptr || var4.getVehicle().couldCrawlerAttackPassenger(var4))) {
         var4.getBodyDamage().AddRandomDamageFromZombie((IsoZombie)var1, nullptr);
      }

      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var3.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
         var3.setCrawler(true);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
