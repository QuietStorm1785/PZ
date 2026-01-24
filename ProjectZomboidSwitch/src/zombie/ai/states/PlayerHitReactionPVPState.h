#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerHitReactionPVPState : public State {
public:
    static PlayerHitReactionPVPState& instance();
    void enter(IsoGameCharacter* character) override;
    void execute(IsoGameCharacter* character) override;
    void exit(IsoGameCharacter* character) override;
    void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
private:
    PlayerHitReactionPVPState() = default;
};


PlayerHitReactionPVPState& PlayerHitReactionPVPState::instance() {
    static PlayerHitReactionPVPState _instance;
    return _instance;
}

void PlayerHitReactionPVPState::enter(IsoGameCharacter* var1) {
      if (!var1->getCharacterActions().empty()) {
         ((BaseAction)var1->getCharacterActions().get(0)).forceStop();
      }

      var1->setSitOnGround(false);
   }

void PlayerHitReactionPVPState::execute(IsoGameCharacter* var1) {
   }

void PlayerHitReactionPVPState::exit(IsoGameCharacter* var1) {
      var1->setIgnoreMovement(false);
      var1->setHitReaction("");
      var1->setVariable("hitpvp", false);
   }

void PlayerHitReactionPVPState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
      if (var2->m_EventName.equalsIgnoreCase("PushAwayZombie")) {
         var1->getAttackedBy()->setHitForce(0.03F);
         if (var1->getAttackedBy() instanceof IsoZombie) {
            ((IsoZombie)var1->getAttackedBy())->setPlayerAttackPosition(nullptr);
            ((IsoZombie)var1->getAttackedBy())->setStaggerBack(true);
         }
      }

      if (var2->m_EventName.equalsIgnoreCase("Defend")) {
         var1->getAttackedBy()->setHitReaction("BiteDefended");
      }

      if (var2->m_EventName.equalsIgnoreCase("DeathSound")) {
         if (var1->isPlayingDeathSound()) {
            return;
         }

         var1->setPlayingDeathSound(true);
    std::string var3 = "Male";
         if (var1->isFemale()) {
            var3 = "Female";
         }

         var3 = var3 + "BeingEatenDeath";
         var1->playSound(var3);
      }

      if (var2->m_EventName.equalsIgnoreCase("Death")) {
         var1->setOnFloor(true);
         if (!GameServer.bServer) {
            var1->Kill(var1->getAttackedBy());
         }
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
