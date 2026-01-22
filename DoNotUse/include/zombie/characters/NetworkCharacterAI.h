#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/NetworkCharacterAI/1.h"
#include "zombie/characters/NetworkCharacterAI/SpeedChecker.h"
#include "zombie/characters/NetworkTeleport/NetworkTeleportDebug.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/DeadCharacterPacket.h"
#include "zombie/network/packets/hit/VehicleHitPacket.h"
#include <algorithm>

namespace zombie {
namespace characters {


class NetworkCharacterAI {
public:
    static const short VEHICLE_HIT_DELAY_MS = 500;
    const SpeedChecker speedChecker = std::make_shared<SpeedChecker>();
    PredictionTypes predictionType;
    DeadCharacterPacket deadBody;
    VehicleHitPacket vehicleHit;
    float timestamp;
    BaseAction action;
    std::string performingAction;
    long noCollisionTime;
    bool wasLocal;
    const HitReactionNetworkAI hitReaction;
    const IsoGameCharacter character;
    NetworkTeleportDebug teleportDebug;
   public const std::unordered_map<int, std::string> debugData = std::make_shared<1>(this);

    public NetworkCharacterAI(IsoGameCharacter var1) {
      this.character = var1;
      this.deadBody = nullptr;
      this.wasLocal = false;
      this.vehicleHit = nullptr;
      this.noCollisionTime = 0L;
      this.hitReaction = std::make_shared<HitReactionNetworkAI>(var1);
      this.predictionType = PredictionTypes.None;
      this.clearTeleportDebug();
      this.speedChecker.reset();
   }

    void reset() {
      this.deadBody = nullptr;
      this.wasLocal = false;
      this.vehicleHit = nullptr;
      this.noCollisionTime = 0L;
      this.hitReaction.finish();
      this.predictionType = PredictionTypes.None;
      this.clearTeleportDebug();
      this.speedChecker.reset();
   }

    void setLocal(bool var1) {
      this.wasLocal = var1;
   }

    bool wasLocal() {
      return this.wasLocal;
   }

    NetworkTeleportDebug getTeleportDebug() {
      return this.teleportDebug;
   }

    void clearTeleportDebug() {
      this.teleportDebug = nullptr;
      this.debugData.clear();
   }

    void setTeleportDebug(NetworkTeleportDebug var1) {
      this.teleportDebug = var1;
      this.debugData.entrySet().stream().sorted(Entry.comparingByKey(Comparator.naturalOrder())).forEach(var0 -> {
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "==> " + var0.getValue());
         }
      });
      if (Core.bDebug) {
         DebugLog.log(
            DebugType.Multiplayer,
            std::string.format(
               "NetworkTeleport %s id=%d distance=%.3f prediction=%s",
               this.character.getClass().getSimpleName(),
               this.character.getOnlineID(),
               var1.getDistance(),
               this.predictionType
            )
         );
      }
   }

    void addTeleportData(int var1, const std::string& var2) {
      this.debugData.put(var1, var2);
   }

    void processDeadBody() {
      if (this.isSetDeadBody() && !this.hitReaction.isSetup() && !this.hitReaction.isStarted()) {
         this.deadBody.process();
         this.setDeadBody(nullptr);
      }
   }

    void setDeadBody(DeadCharacterPacket var1) {
      this.deadBody = var1;
      DebugLog.Death.trace(var1 == nullptr ? "processed" : "postpone");
   }

    bool isSetDeadBody() {
      return this.deadBody != nullptr && this.deadBody.isConsistent();
   }

    void setPerformingAction(const std::string& var1) {
      this.performingAction = var1;
   }

    std::string getPerformingAction() {
      return this.performingAction;
   }

    void setAction(BaseAction var1) {
      this.action = var1;
   }

    BaseAction getAction() {
      return this.action;
   }

    void startAction() {
      if (this.action != nullptr) {
         this.action.start();
      }
   }

    void stopAction() {
      if (this.action != nullptr) {
         this.setOverride(false, nullptr, nullptr);
         this.action.stop();
      }
   }

    void setOverride(bool var1, const std::string& var2, const std::string& var3) {
      if (this.action != nullptr) {
         this.action.chr.forceNullOverride = var1;
         this.action.chr.overridePrimaryHandModel = var2;
         this.action.chr.overrideSecondaryHandModel = var3;
         this.action.chr.resetModelNextFrame();
      }
   }

    void processVehicleHit() {
      this.vehicleHit.tryProcessInternal();
      this.setVehicleHit(nullptr);
   }

    void setVehicleHit(VehicleHitPacket var1) {
      this.vehicleHit = var1;
      this.timestamp = (float)TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime());
      DebugLog.Damage.noise(var1 == nullptr ? "processed" : "postpone");
   }

    bool isSetVehicleHit() {
      return this.vehicleHit != nullptr && this.vehicleHit.isConsistent();
   }

    void resetVehicleHitTimeout() {
      this.timestamp = (float)(TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()) - 500L);
      if (this.vehicleHit == nullptr) {
         DebugLog.Damage.noise("VehicleHit is not set");
      }
   }

    bool isVehicleHitTimeout() {
    bool var1 = (float)TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()) - this.timestamp >= 500.0F;
      if (var1) {
         DebugLog.Damage.noise("VehicleHit timeout");
      }

    return var1;
   }

    void updateHitVehicle() {
      if (this.isSetVehicleHit() && this.isVehicleHitTimeout()) {
         this.processVehicleHit();
      }
   }

    bool isCollisionEnabled() {
      return this.noCollisionTime == 0L;
   }

    bool isNoCollisionTimeout() {
    bool var1 = GameTime.getServerTimeMills() > this.noCollisionTime;
      if (var1) {
         this.setNoCollision(0L);
      }

    return var1;
   }

    void setNoCollision(long var1) {
      if (var1 == 0L) {
         this.noCollisionTime = 0L;
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "SetNoCollision: disabled");
         }
      } else {
         this.noCollisionTime = GameTime.getServerTimeMills() + var1;
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "SetNoCollision: enabled for " + var1 + " ms");
         }
      }
   }

    bool checkPosition(UdpConnection var1, IsoGameCharacter var2, float var3, float var4) {
      if (GameServer.bServer && var2.isAlive()) {
         this.speedChecker.set(var3, var4, var2.isSeatedInVehicle());
    bool var5 = PacketValidator.checkSpeed(var1, this.speedChecker, var2.getClass().getSimpleName() + SpeedChecker.class.getSimpleName());
         if (32 == var1.accessLevel) {
            var5 = true;
         }

    return var5;
      } else {
    return true;
      }
   }

    void resetSpeedLimiter() {
      this.speedChecker.reset();
   }
}
} // namespace characters
} // namespace zombie
