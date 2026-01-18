#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerAimState : public State {
public:
 static const PlayerAimState _instance = new PlayerAimState();

 static PlayerAimState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 if (!"strafe" == owner.getPreviousActionContextStateName())) {
 InventoryItem item = owner.getPrimaryHandItem();
 if (item != nullptr && item.getBringToBearSound() != nullptr) {
 owner.getEmitter().playSoundImpl(item.getBringToBearSound(), nullptr);
 }
 }
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
