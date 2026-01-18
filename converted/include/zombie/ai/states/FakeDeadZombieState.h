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
#include "zombie/core/Core.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FakeDeadZombieState : public State {
public:
 static const FakeDeadZombieState _instance = new FakeDeadZombieState();

 static FakeDeadZombieState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setVisibleToNPCs(false);
 owner.setCollidable(false);
 ((IsoZombie)owner).setFakeDead(true);
 owner.setOnFloor(true);
 }

 void execute(IsoGameCharacter owner) {
 if (owner.isDead()) {
 if (GameClient.bClient && owner instanceof IsoZombie) {
 GameClient.sendZombieDeath((IsoZombie)owner);
 }

 if (!GameClient.bClient) {
 new IsoDeadBody();
 }
 } else if (Core.bLastStand) {
 ((IsoZombie)owner).setFakeDead(false);
 }
 }

 void exit(IsoGameCharacter owner) {
 ((IsoZombie)owner).setFakeDead(false);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
