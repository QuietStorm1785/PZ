#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/states/PlayerFallDownState.h"
#include "zombie/ai/states/PlayerKnockedDown.h"
#include "zombie/ai/states/PlayerOnGroundState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace characters {


class HitReactionNetworkAI {
public:
    static const float G = 2.0F;
    static const float DURATION = 600.0F;
    const Vector2 startPosition = std::make_shared<Vector2>();
    const Vector2 finalPosition = std::make_shared<Vector2>();
    uint8_t finalPositionZ = 0;
    const Vector2 startDirection = std::make_shared<Vector2>();
    const Vector2 finalDirection = std::make_shared<Vector2>();
    float startAngle;
    float finalAngle;
    const IsoGameCharacter character;
    long startTime;

    public HitReactionNetworkAI(IsoGameCharacter var1) {
      this.character = var1;
      this.startTime = 0L;
   }

    bool isSetup() {
      return this.finalPosition.x != 0.0F && this.finalPosition.y != 0.0F;
   }

    bool isStarted() {
      return this.startTime > 0L;
   }

    void start() {
      if (this.isSetup() && !this.isStarted()) {
         this.startTime = GameTime.getServerTimeMills();
         if (this.startPosition.x != this.character.x || this.startPosition.y != this.character.y) {
            DebugLog.Multiplayer.warn("HitReaction start shifted");
         }

         DebugLog.Damage
            .trace("id=%d: %s / %s => %s", this.character.getOnlineID(), this.getActualDescription(), this.getStartDescription(), this.getFinalDescription());
      }
   }

    void finish() {
      if (this.startTime != 0L) {
         DebugLog.Damage
            .trace("id=%d: %s / %s => %s", this.character.getOnlineID(), this.getActualDescription(), this.getStartDescription(), this.getFinalDescription());
      }

      this.startTime = 0L;
      this.setup(0.0F, 0.0F, (byte)0, 0.0F);
   }

    void setup(float var1, float var2, uint8_t var3, float var4) {
      this.startPosition.set(this.character.x, this.character.y);
      this.finalPosition.set(var1, var2);
      this.finalPositionZ = var3;
      this.startDirection.set(this.character.getForwardDirection());
      this.startAngle = this.character.getAnimAngleRadians();
    Vector2 var5 = std::make_shared<Vector2>().set(this.finalPosition.x - this.startPosition.x, this.finalPosition.y - this.startPosition.y);
      if (var4 == nullptr) {
         var5.normalize();
         var4 = var5.dot(this.character.getForwardDirection());
         PZMath.lerp(this.finalDirection, var5, this.character.getForwardDirection(), Math.abs(var4));
         IsoMovingObject.getVectorFromDirection(this.finalDirection, IsoDirections.fromAngle(this.finalDirection));
      } else {
         this.finalDirection.setLengthAndDirection(var4, 1.0F);
      }

      this.finalAngle = var4;
      if (this.isSetup()) {
         DebugLog.Damage
            .trace("id=%d: %s / %s => %s", this.character.getOnlineID(), this.getActualDescription(), this.getStartDescription(), this.getFinalDescription());
      }
   }

    void moveInternal(float var1, float var2, float var3, float var4) {
      this.character.nx = var1;
      this.character.ny = var2;
      this.character.setDir(IsoDirections.fromAngle(var3, var4));
      this.character.setForwardDirection(var3, var4);
      this.character.getAnimationPlayer().SetForceDir(this.character.getForwardDirection());
   }

    void moveFinal() {
      this.moveInternal(this.finalPosition.x, this.finalPosition.y, this.finalDirection.x, this.finalDirection.y);
      this.character.lx = this.character.nx = this.character.x = this.finalPosition.x;
      this.character.ly = this.character.ny = this.character.y = this.finalPosition.y;
      this.character.setCurrent(IsoWorld.instance.CurrentCell.getGridSquare((int)this.finalPosition.x, (int)this.finalPosition.y, this.character.z));
      DebugLog.Damage
         .trace("id=%d: %s / %s => %s", this.character.getOnlineID(), this.getActualDescription(), this.getStartDescription(), this.getFinalDescription());
   }

    void move() {
      if (this.finalPositionZ != (byte)this.character.z) {
         DebugLog.Damage
            .trace("HitReaction interrupt id=%d: z-final:%d z-current=%d", this.character.getOnlineID(), this.finalPositionZ, (byte)this.character.z);
         this.finish();
      } else {
    float var1 = Math.min(1.0F, Math.max(0.0F, (float)(GameTime.getServerTimeMills() - this.startTime) / 600.0F));
         if (this.startPosition.x == this.finalPosition.x && this.startPosition.y == this.finalPosition.y) {
            var1 = 1.0F;
         }

         if (var1 < 1.0F) {
            var1 = (PZMath.gain(var1 * 0.5F + 0.5F, 2.0F) - 0.5F) * 2.0F;
            this.moveInternal(
               PZMath.lerp(this.startPosition.x, this.finalPosition.x, var1),
               PZMath.lerp(this.startPosition.y, this.finalPosition.y, var1),
               PZMath.lerp(this.startDirection.x, this.finalDirection.x, var1),
               PZMath.lerp(this.startDirection.y, this.finalDirection.y, var1)
            );
         } else {
            this.moveFinal();
            this.finish();
         }
      }
   }

    bool isDoSkipMovement() {
      if (this.dynamic_cast<IsoZombie*>(character) != nullptr) {
         return this.character.isCurrentState(ZombieFallDownState.instance()) || this.character.isCurrentState(ZombieOnGroundState.instance());
      } else {
         return !(this.dynamic_cast<IsoPlayer*>(character) != nullptr)
            ? false
            : this.character.isCurrentState(PlayerFallDownState.instance())
               || this.character.isCurrentState(PlayerKnockedDown.instance())
               || this.character.isCurrentState(PlayerOnGroundState.instance());
      }
   }

    std::string getStartDescription() {
      return std::string.format(
         "start=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
         this.startPosition.x,
         this.startPosition.y,
         this.startDirection.x,
         this.startDirection.y,
         this.startAngle
      );
   }

    std::string getFinalDescription() {
      return std::string.format(
         "final=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
         this.finalPosition.x,
         this.finalPosition.y,
         this.finalDirection.x,
         this.finalDirection.y,
         this.finalAngle
      );
   }

    std::string getActualDescription() {
      return std::string.format(
         "actual=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
         this.character.x,
         this.character.y,
         this.character.getForwardDirection().getX(),
         this.character.getForwardDirection().getY(),
         this.character.getAnimAngleRadians()
      );
   }

    std::string getDescription() {
      return std::string.format(
         "start=%d | (x=%f,y=%f;a=%f;l=%f)",
         this.startTime,
         this.finalPosition.x,
         this.finalPosition.y,
         this.finalAngle,
         IsoUtils.DistanceTo(this.startPosition.x, this.startPosition.y, this.finalPosition.x, this.finalPosition.y)
      );
   }

    static void CalcHitReactionWeapon(IsoGameCharacter var0, IsoGameCharacter var1, HandWeapon var2) {
    HitReactionNetworkAI var3 = var1.getHitReactionNetworkAI();
      if (var1.isOnFloor()) {
         var3.setup(var1.x, var1.y, (byte)var1.z, var1.getAnimAngleRadians());
      } else {
    Vector2 var4 = std::make_shared<Vector2>();
    float var5 = var1.calcHitDir(var0, var2, var4);
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            var4.x = (var4.x + var1.x + ((IsoPlayer)var1).networkAI.targetX) * 0.5F;
            var4.y = (var4.y + var1.y + ((IsoPlayer)var1).networkAI.targetY) * 0.5F;
         } else {
            var4.x = var4.x + var1.x;
            var4.y = var4.y + var1.y;
         }

         var4.x = PZMath.roundFromEdges(var4.x);
         var4.y = PZMath.roundFromEdges(var4.y);
         if (PolygonalMap2.instance.lineClearCollide(var1.x, var1.y, var4.x, var4.y, (int)var1.z, nullptr, false, true)) {
            var4.x = var1.x;
            var4.y = var1.y;
         }

         var3.setup(var4.x, var4.y, (byte)var1.z, var5);
      }

      if (var3.isSetup()) {
         var3.start();
      }
   }

    static void CalcHitReactionVehicle(IsoGameCharacter var0, BaseVehicle var1) {
    HitReactionNetworkAI var2 = var0.getHitReactionNetworkAI();
      if (!var2.isStarted()) {
         if (var0.isOnFloor()) {
            var2.setup(var0.x, var0.y, (byte)var0.z, var0.getAnimAngleRadians());
         } else {
    Vector2 var3 = std::make_shared<Vector2>();
            var0.calcHitDir(var3);
            if (dynamic_cast<IsoPlayer*>(var0) != nullptr) {
               var3.x = (var3.x + var0.x + ((IsoPlayer)var0).networkAI.targetX) * 0.5F;
               var3.y = (var3.y + var0.y + ((IsoPlayer)var0).networkAI.targetY) * 0.5F;
            } else {
               var3.x = var3.x + var0.x;
               var3.y = var3.y + var0.y;
            }

            var3.x = PZMath.roundFromEdges(var3.x);
            var3.y = PZMath.roundFromEdges(var3.y);
            if (PolygonalMap2.instance.lineClearCollide(var0.x, var0.y, var3.x, var3.y, (int)var0.z, var1, false, true)) {
               var3.x = var0.x;
               var3.y = var0.y;
            }

            var2.setup(var3.x, var3.y, (byte)var0.z, nullptr);
         }
      }

      if (var2.isSetup()) {
         var2.start();
      }
   }

    void process(float var1, float var2, float var3, float var4) {
      this.setup(var1, var2, (byte)var3, var4);
      this.start();
      if (GameServer.bServer) {
         this.moveFinal();
         this.finish();
      }
   }
}
} // namespace characters
} // namespace zombie
