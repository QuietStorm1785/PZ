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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FakeDeadAttackState : public State {
public:
 static const FakeDeadAttackState _instance = new FakeDeadAttackState();

 static FakeDeadAttackState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 zombie0.DirectionFromVector(zombie0.vectorToTarget);
 zombie0.setFakeDead(false);
 owner.setVisibleToNPCs(true);
 owner.setCollidable(true);
 std::string string = "MaleZombieAttack";
 if (owner.isFemale()) {
 string = "FemaleZombieAttack";
 }

 owner.getEmitter().playSound(string);
 if (zombie0.target instanceof IsoPlayer && !((IsoPlayer)zombie0.target).getCharacterTraits().Desensitized.isSet()) {
 IsoPlayer player = (IsoPlayer)zombie0.target;
 Stats stats = player.getStats();
 stats.Panic = stats.Panic + player.getBodyDamage().getPanicIncreaseValue() * 3.0F;
 }
 }

 void execute(IsoGameCharacter owner) {
 }

 void exit(IsoGameCharacter owner) {
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 IsoZombie zombie0 = (IsoZombie)owner;
 if (event.m_EventName.equalsIgnoreCase("AttackCollisionCheck")
 && owner.isAlive()
 && zombie0.isTargetInCone(1.5F, 0.9F)
 && zombie0.target instanceof IsoGameCharacter character
 && (character.getVehicle() == nullptr || character.getVehicle().couldCrawlerAttackPassenger(character)) {
 character.getBodyDamage().AddRandomDamageFromZombie((IsoZombie)owner, nullptr);
 }

 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 zombie0.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
 zombie0.setCrawler(true);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
