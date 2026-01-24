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
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerHitReactionState : public State {
public:
    static const PlayerHitReactionState _instance = std::make_shared<PlayerHitReactionState>();

    static PlayerHitReactionState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      if (!var1.getCharacterActions().empty()) {
         ((BaseAction)var1.getCharacterActions().get(0)).forceStop();
      }

      var1.setIsAiming(false);
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      var1.setHitReaction("");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var1.getAttackedBy() != nullptr && var1.getAttackedBy() instanceof IsoZombie) {
         if (var2.m_EventName.equalsIgnoreCase("PushAwayZombie")) {
            var1.getAttackedBy().setHitForce(0.03F);
            ((IsoZombie)var1.getAttackedBy()).setPlayerAttackPosition(nullptr);
            ((IsoZombie)var1.getAttackedBy()).setStaggerBack(true);
         }

         if (var2.m_EventName.equalsIgnoreCase("Defend")) {
            var1.getAttackedBy().setHitReaction("BiteDefended");
            if (GameClient.bClient) {
               GameClient.sendHitCharacter(var1.getAttackedBy(), var1, nullptr, 0.0F, false, 1.0F, false, false, false);
            }
         }

         if (var2.m_EventName.equalsIgnoreCase("DeathSound")) {
            if (var1.isPlayingDeathSound()) {
               return;
            }

            var1.setPlayingDeathSound(true);
    std::string var3 = "Male";
            if (var1.isFemale()) {
               var3 = "Female";
            }

            var3 = var3 + "BeingEatenDeath";
            var1.playSound(var3);
         }

         if (var2.m_EventName.equalsIgnoreCase("Death")) {
            var1.setOnFloor(true);
            if (!GameServer.bServer) {
               var1.Kill(var1.getAttackedBy());
            }
         }
      } else {
         DebugLog.log("PlayerHitReactionState.animEvent (" + var2.m_EventName + ") zombie is nullptr");
      }
   }
}
public:
    static PlayerHitReactionState& instance();
    void enter(IsoGameCharacter* character) override;
    void execute(IsoGameCharacter* character) override;
    void exit(IsoGameCharacter* character) override;
    void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
private:
    PlayerHitReactionState() = default;
