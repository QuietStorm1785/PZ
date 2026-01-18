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
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerActionsState : public State {
public:
 static const PlayerActionsState _instance = new PlayerActionsState();

 static PlayerActionsState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 InventoryItem item0 = owner.getPrimaryHandItem();
 InventoryItem item1 = owner.getSecondaryHandItem();
 if (!(item0 instanceof HandWeapon) && !(item1 instanceof HandWeapon) {
 owner.setHideWeaponModel(true);
 }

 std::string string = owner.getVariableString("PerformingAction");
 if (GameClient.bClient
 && owner instanceof IsoPlayer
 && owner.isLocal()
 && !owner.getCharacterActions().empty()
 && owner.getNetworkCharacterAI().getAction() == nullptr) {
 owner.getNetworkCharacterAI().setAction(owner.getCharacterActions().get(0);
 GameClient.sendAction(owner.getNetworkCharacterAI().getAction(), true);
 owner.getNetworkCharacterAI().setPerformingAction(string);
 }
 }

 void execute(IsoGameCharacter owner) {
 if (GameClient.bClient && owner instanceof IsoPlayer && owner.isLocal()) {
 std::string string = owner.getVariableString("PerformingAction");
 if (!owner.getCharacterActions().empty()
 && (
 owner.getNetworkCharacterAI().getAction() != owner.getCharacterActions().get(0)
 || string != nullptr && !string == owner.getNetworkCharacterAI().getPerformingAction())
 )) {
 GameClient.sendAction(owner.getNetworkCharacterAI().getAction(), false);
 owner.getNetworkCharacterAI().setAction(owner.getCharacterActions().get(0);
 GameClient.sendAction(owner.getNetworkCharacterAI().getAction(), true);
 owner.getNetworkCharacterAI().setPerformingAction(string);
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setHideWeaponModel(false);
 if (GameClient.bClient && owner instanceof IsoPlayer && owner.isLocal() && owner.getNetworkCharacterAI().getAction() != nullptr) {
 GameClient.sendAction(owner.getNetworkCharacterAI().getAction(), false);
 owner.getNetworkCharacterAI().setAction(nullptr);
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (GameClient.bClient
 && event != nullptr
 && owner instanceof IsoPlayer
 && owner.getNetworkCharacterAI().getAction() != nullptr
 && !owner.isLocal()
 && "changeWeaponSprite".equalsIgnoreCase(event.m_EventName)
 && !StringUtils.isNullOrEmpty(event.m_ParameterValue) {
 if ("original" == event.m_ParameterValue) {
 owner.getNetworkCharacterAI().setOverride(false, nullptr, nullptr);
 } else {
 owner.getNetworkCharacterAI().setOverride(true, event.m_ParameterValue, nullptr);
 }
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
