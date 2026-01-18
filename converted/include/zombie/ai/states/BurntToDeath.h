#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TutorialManager.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BurntToDeath : public State {
public:
 static const BurntToDeath _instance = new BurntToDeath();

 static BurntToDeath instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 if (owner instanceof IsoSurvivor) {
 owner.getDescriptor().bDead = true;
 }

 if (!(owner instanceof IsoZombie) {
 owner.PlayAnimUnlooped("Die");
 } else {
 owner.PlayAnimUnlooped("ZombieDeath");
 }

 owner.def.AnimFrameIncrease = 0.25F;
 owner.setStateMachineLocked(true);
 std::string string = owner.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
 owner.getEmitter().playVocals(string);
 if (GameServer.bServer && owner instanceof IsoZombie) {
 GameServer.sendZombieSound(IsoZombie.ZombieSound.Burned, (IsoZombie)owner);
 }
 }

 void execute(IsoGameCharacter owner) {
 if ((int)owner.def.Frame == owner.sprite.CurrentAnim.Frames.size() - 1) {
 if (owner == TutorialManager.instance.wife) {
 owner.dir = IsoDirections.S;
 }

 owner.RemoveAttachedAnims();
 if (GameClient.bClient && owner instanceof IsoZombie) {
 GameClient.sendZombieDeath((IsoZombie)owner);
 }

 if (!GameClient.bClient) {
 new IsoDeadBody();
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
