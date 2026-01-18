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
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerHitReactionPVPState : public State {
public:
 static const PlayerHitReactionPVPState _instance = new PlayerHitReactionPVPState();

 static PlayerHitReactionPVPState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 if (!owner.getCharacterActions().empty()) {
 owner.getCharacterActions().get(0).forceStop();
 }

 owner.setSitOnGround(false);
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 owner.setIgnoreMovement(false);
 owner.setHitReaction("");
 owner.setVariable("hitpvp", false);
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("PushAwayZombie")) {
 owner.getAttackedBy().setHitForce(0.03F);
 if (owner.getAttackedBy() instanceof IsoZombie) {
 ((IsoZombie)owner.getAttackedBy()).setPlayerAttackPosition(nullptr);
 ((IsoZombie)owner.getAttackedBy()).setStaggerBack(true);
 }
 }

 if (event.m_EventName.equalsIgnoreCase("Defend")) {
 owner.getAttackedBy().setHitReaction("BiteDefended");
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
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
