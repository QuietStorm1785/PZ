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
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerActionsState : public State {
public:
    static const PlayerActionsState _instance = std::make_shared<PlayerActionsState>();

    static PlayerActionsState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    InventoryItem var2 = var1.getPrimaryHandItem();
    InventoryItem var3 = var1.getSecondaryHandItem();
      if (!(dynamic_cast<HandWeapon*>(var2) != nullptr) && !(dynamic_cast<HandWeapon*>(var3) != nullptr)) {
         var1.setHideWeaponModel(true);
      }

    std::string var4 = var1.getVariableString("PerformingAction");
      if (GameClient.bClient
         && dynamic_cast<IsoPlayer*>(var1) != nullptr
         && var1.isLocal()
         && !var1.getCharacterActions().empty()
         && var1.getNetworkCharacterAI().getAction() == nullptr) {
         var1.getNetworkCharacterAI().setAction((BaseAction)var1.getCharacterActions().get(0));
         GameClient.sendAction(var1.getNetworkCharacterAI().getAction(), true);
         var1.getNetworkCharacterAI().setPerformingAction(var4);
      }
   }

    void execute(IsoGameCharacter var1) {
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.isLocal()) {
    std::string var2 = var1.getVariableString("PerformingAction");
         if (!var1.getCharacterActions().empty()
            && (
               var1.getNetworkCharacterAI().getAction() != var1.getCharacterActions().get(0)
                  || var2 != nullptr && !var2 == var1.getNetworkCharacterAI().getPerformingAction())
            )) {
            GameClient.sendAction(var1.getNetworkCharacterAI().getAction(), false);
            var1.getNetworkCharacterAI().setAction((BaseAction)var1.getCharacterActions().get(0));
            GameClient.sendAction(var1.getNetworkCharacterAI().getAction(), true);
            var1.getNetworkCharacterAI().setPerformingAction(var2);
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setHideWeaponModel(false);
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.isLocal() && var1.getNetworkCharacterAI().getAction() != nullptr) {
         GameClient.sendAction(var1.getNetworkCharacterAI().getAction(), false);
         var1.getNetworkCharacterAI().setAction(nullptr);
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (GameClient.bClient
         && var2 != nullptr
         && dynamic_cast<IsoPlayer*>(var1) != nullptr
         && var1.getNetworkCharacterAI().getAction() != nullptr
         && !var1.isLocal()
         && "changeWeaponSprite".equalsIgnoreCase(var2.m_EventName)
         && !StringUtils.isNullOrEmpty(var2.m_ParameterValue)) {
         if ("original" == var2.m_ParameterValue)) {
            var1.getNetworkCharacterAI().setOverride(false, nullptr, nullptr);
         } else {
            var1.getNetworkCharacterAI().setOverride(true, var2.m_ParameterValue, nullptr);
         }
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
