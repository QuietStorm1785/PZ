#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerKnockedDown : public State {
public:
 static const PlayerKnockedDown _instance = new PlayerKnockedDown();

 static PlayerKnockedDown instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setIgnoreMovement(true);
 ((IsoPlayer)owner).setBlockMovement(true);
 owner.setHitReaction("");
 }

 void execute(IsoGameCharacter owner) {
 if (owner.isDead()) {
 if (!GameServer.bServer && !GameClient.bClient) {
 owner.Kill(nullptr);
 }
 } else {
 owner.setReanimateTimer(owner.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("FallOnFront")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("FallOnBack")) {
 owner.setFallOnFront(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("setSitOnGround")) {
 owner.setSitOnGround(Boolean.parseBoolean(event.m_ParameterValue);
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setIgnoreMovement(false);
 ((IsoPlayer)owner).setBlockMovement(false);
 ((IsoPlayer)owner).setKnockedDown(false);
 owner.setOnFloor(true);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
