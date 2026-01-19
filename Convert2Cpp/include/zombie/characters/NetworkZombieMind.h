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
#include "zombie/network/NetworkVariables/ZombieState.h"
#include "zombie/network/packets/ZombiePacket.h"
#include "zombie/vehicles/PathFindBehavior2.h"

namespace zombie {
namespace characters {


class NetworkZombieMind {
public:
    const IsoZombie zombie;
    uint8_t pfbType = 0;
    float pfbTargetX;
    float pfbTargetY;
    float pfbTargetZ;
    bool pfbIsCanceled = false;
    bool shouldRestorePFBTarget = false;
    IsoPlayer pfbTargetCharacter = null;

    public NetworkZombieMind(IsoZombie var1) {
      this.zombie = var1;
   }

    void set(ZombiePacket var1) {
    PathFindBehavior2 var2 = this.zombie.getPathFindBehavior2();
      if (var2.getIsCancelled() || var2.isGoalNone() || var2.bStopping || this.zombie.realState == nullptr || ZombieState.Idle == this.zombie.realState)) {
         var1.pfbType = 0;
      } else if (var2.isGoalCharacter()) {
    IsoGameCharacter var3 = var2.getTargetChar();
         if (var3 instanceof IsoPlayer) {
            var1.pfbType = 1;
            var1.pfbTarget = var3.getOnlineID();
         } else {
            var1.pfbType = 0;
            DebugLog.Multiplayer.error("NetworkZombieMind: goal character is not set");
         }
      } else if (var2.isGoalLocation()) {
         var1.pfbType = 2;
         var1.pfbTargetX = var2.getTargetX();
         var1.pfbTargetY = var2.getTargetY();
         var1.pfbTargetZ = (byte)var2.getTargetZ();
      } else if (var2.isGoalSound()) {
         var1.pfbType = 3;
         var1.pfbTargetX = var2.getTargetX();
         var1.pfbTargetY = var2.getTargetY();
         var1.pfbTargetZ = (byte)var2.getTargetZ();
      }
   }

    void parse(ZombiePacket var1) {
      this.pfbIsCanceled = var1.pfbType == 0;
      if (!this.pfbIsCanceled) {
         this.pfbType = var1.pfbType;
         if (this.pfbType == 1) {
            if (GameServer.bServer) {
               this.pfbTargetCharacter = static_cast<IsoPlayer>(GameServer).IDToPlayerMap.get(var1.pfbTarget);
            } else if (GameClient.bClient) {
               this.pfbTargetCharacter = static_cast<IsoPlayer>(GameClient).IDToPlayerMap.get(var1.pfbTarget);
            }
         } else if (this.pfbType > 1) {
            this.pfbTargetX = var1.pfbTargetX;
            this.pfbTargetY = var1.pfbTargetY;
            this.pfbTargetZ = var1.pfbTargetZ;
         }
      }
   }

    void restorePFBTarget() {
      this.shouldRestorePFBTarget = true;
   }

    void zombieIdleUpdate() {
      if (this.shouldRestorePFBTarget) {
         this.doRestorePFBTarget();
         this.shouldRestorePFBTarget = false;
      }
   }

    void doRestorePFBTarget() {
      if (!this.pfbIsCanceled) {
         if (this.pfbType == 1 && this.pfbTargetCharacter != nullptr) {
            this.zombie.pathToCharacter(this.pfbTargetCharacter);
            this.zombie.spotted(this.pfbTargetCharacter, true);
         } else if (this.pfbType == 2) {
            this.zombie.pathToLocationF(this.pfbTargetX, this.pfbTargetY, this.pfbTargetZ);
         } else if (this.pfbType == 3) {
            this.zombie.pathToSound((int)this.pfbTargetX, (int)this.pfbTargetY, (int)this.pfbTargetZ);
            this.zombie.alerted = false;
            this.zombie.setLastHeardSound((int)this.pfbTargetX, (int)this.pfbTargetY, (int)this.pfbTargetZ);
            this.zombie.AllowRepathDelay = 120.0F;
            this.zombie.timeSinceRespondToSound = 0.0F;
         }
      }
   }
}
} // namespace characters
} // namespace zombie
