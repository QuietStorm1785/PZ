#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerHitReactionState : public State {
public:
 static const PlayerHitReactionState _instance = new PlayerHitReactionState();

 static PlayerHitReactionState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 owner.setIgnoreMovement(true);
 if (!owner.getCharacterActions().empty()) {
 owner.getCharacterActions().get(0).forceStop();
 }

 owner.setIsAiming(false);
 }

 void execute(IsoGameCharacter owner) {}

 void exit(IsoGameCharacter owner) {
 owner.setIgnoreMovement(false);
 owner.setHitReaction("");
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (owner.getAttackedBy() != nullptr && owner.getAttackedBy() instanceof
 IsoZombie) {
 if (event.m_EventName.equalsIgnoreCase("PushAwayZombie")) {
 owner.getAttackedBy().setHitForce(0.03F);
 ((IsoZombie)owner.getAttackedBy()).setPlayerAttackPosition(nullptr);
 ((IsoZombie)owner.getAttackedBy()).setStaggerBack(true);
 }

 if (event.m_EventName.equalsIgnoreCase("Defend")) {
 owner.getAttackedBy().setHitReaction("BiteDefended");
 if (GameClient.bClient) {
 GameClient.sendHitCharacter(owner.getAttackedBy(), owner, nullptr,
 0.0F, false, 1.0F, false, false, false);
 }
 }

 if (event.m_EventName.equalsIgnoreCase("DeathSound")) {
 if (owner.isPlayingDeathSound()) {
 return;
 }

 owner.setPlayingDeathSound(true);
 std::string string = "Male";
 if (owner.isFemale()) {
 string = "Female";
 }

 string = string + "BeingEatenDeath";
 owner.playSound(string);
 }

 if (event.m_EventName.equalsIgnoreCase("Death")) {
 owner.setOnFloor(true);
 if (!GameServer.bServer) {
 owner.Kill(owner.getAttackedBy());
 }
 }
 } else {
 DebugLog.log("PlayerHitReactionState.animEvent (" + event.m_EventName +
 ") zombie is nullptr");
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
