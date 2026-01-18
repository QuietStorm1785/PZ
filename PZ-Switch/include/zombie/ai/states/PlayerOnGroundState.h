#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
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

class PlayerOnGroundState : public State {
public:
 static const PlayerOnGroundState _instance = new PlayerOnGroundState();

 static PlayerOnGroundState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 owner.setIgnoreMovement(true);
 ((IsoPlayer)owner).setBlockMovement(true);
 owner.setVariable("bAnimEnd", false);
 }

 void execute(IsoGameCharacter owner) {
 if (!GameServer.bServer && owner.isDead()) {
 owner.die();
 } else {
 owner.setReanimateTimer(owner.getReanimateTimer() -
 GameTime.getInstance().getMultiplier() / 1.6F);
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setIgnoreMovement(false);
 ((IsoPlayer)owner).setBlockMovement(false);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
