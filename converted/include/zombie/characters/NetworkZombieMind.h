#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables.h"
#include "zombie/network/packets/ZombiePacket.h"
#include "zombie/vehicles/PathFindBehavior2.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NetworkZombieMind {
public:
 const IsoZombie zombie;
 uint8_t pfbType = 0;
 float pfbTargetX;
 float pfbTargetY;
 float pfbTargetZ;
 bool pfbIsCanceled = false;
 bool shouldRestorePFBTarget = false;
 IsoPlayer pfbTargetCharacter = nullptr;

 public NetworkZombieMind(IsoZombie _zombie) {
 this->zombie = _zombie;
 }

 void set(ZombiePacket packet) {
 PathFindBehavior2 pathFindBehavior2 = this->zombie.getPathFindBehavior2();
 if (pathFindBehavior2.getIsCancelled()
 || pathFindBehavior2.isGoalNone()
 || pathFindBehavior2.bStopping
 || this->zombie.realState == nullptr
 || NetworkVariables.ZombieState.Idle == this->zombie.realState) {
 packet.pfbType = 0;
 } else if (pathFindBehavior2.isGoalCharacter()) {
 IsoGameCharacter character = pathFindBehavior2.getTargetChar();
 if (character instanceof IsoPlayer) {
 packet.pfbType = 1;
 packet.pfbTarget = character.getOnlineID();
 } else {
 packet.pfbType = 0;
 DebugLog.Multiplayer.error("NetworkZombieMind: goal character is not set");
 }
 } else if (pathFindBehavior2.isGoalLocation()) {
 packet.pfbType = 2;
 packet.pfbTargetX = pathFindBehavior2.getTargetX();
 packet.pfbTargetY = pathFindBehavior2.getTargetY();
 packet.pfbTargetZ = (byte)pathFindBehavior2.getTargetZ();
 } else if (pathFindBehavior2.isGoalSound()) {
 packet.pfbType = 3;
 packet.pfbTargetX = pathFindBehavior2.getTargetX();
 packet.pfbTargetY = pathFindBehavior2.getTargetY();
 packet.pfbTargetZ = (byte)pathFindBehavior2.getTargetZ();
 }
 }

 void parse(ZombiePacket packet) {
 this->pfbIsCanceled = packet.pfbType == 0;
 if (!this->pfbIsCanceled) {
 this->pfbType = packet.pfbType;
 if (this->pfbType == 1) {
 if (GameServer.bServer) {
 this->pfbTargetCharacter = GameServer.IDToPlayerMap.get(packet.pfbTarget);
 } else if (GameClient.bClient) {
 this->pfbTargetCharacter = GameClient.IDToPlayerMap.get(packet.pfbTarget);
 }
 } else if (this->pfbType > 1) {
 this->pfbTargetX = packet.pfbTargetX;
 this->pfbTargetY = packet.pfbTargetY;
 this->pfbTargetZ = packet.pfbTargetZ;
 }
 }
 }

 void restorePFBTarget() {
 this->shouldRestorePFBTarget = true;
 }

 void zombieIdleUpdate() {
 if (this->shouldRestorePFBTarget) {
 this->doRestorePFBTarget();
 this->shouldRestorePFBTarget = false;
 }
 }

 void doRestorePFBTarget() {
 if (!this->pfbIsCanceled) {
 if (this->pfbType == 1 && this->pfbTargetCharacter != nullptr) {
 this->zombie.pathToCharacter(this->pfbTargetCharacter);
 this->zombie.spotted(this->pfbTargetCharacter, true);
 } else if (this->pfbType == 2) {
 this->zombie.pathToLocationF(this->pfbTargetX, this->pfbTargetY, this->pfbTargetZ);
 } else if (this->pfbType == 3) {
 this->zombie.pathToSound((int)this->pfbTargetX, (int)this->pfbTargetY, (int)this->pfbTargetZ);
 this->zombie.alerted = false;
 this->zombie.setLastHeardSound((int)this->pfbTargetX, (int)this->pfbTargetY, (int)this->pfbTargetZ);
 this->zombie.AllowRepathDelay = 120.0F;
 this->zombie.timeSinceRespondToSound = 0.0F;
 }
 }
 }
}
} // namespace characters
} // namespace zombie
