#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/PerformanceSettings.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class IsoPhysicsObject : public IsoMovingObject {
public:
    float speedMod = 1.0F;
    float velX = 0.0F;
    float velY = 0.0F;
    float velZ = 0.0F;
    float terminalVelocity = -0.05F;

    public IsoPhysicsObject(IsoCell var1) {
      super(var1);
      this.solid = false;
      this.shootable = false;
   }

    void collideGround() {
   }

    void collideWall() {
   }

    void update() {
    IsoGridSquare var1 = this.getCurrentSquare();
      super.update();
      if (this.isCollidedThisFrame()) {
         if (this.isCollidedN() || this.isCollidedS()) {
            this.velY = -this.velY;
            this.velY *= 0.5F;
            this.collideWall();
         }

         if (this.isCollidedE() || this.isCollidedW()) {
            this.velX = -this.velX;
            this.velX *= 0.5F;
            this.collideWall();
         }
      }

    int var2 = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
    float var3 = 30.0F / var2;
    float var4 = 0.1F * this.speedMod * var3;
      var4 = 1.0F - var4;
      this.velX *= var4;
      this.velY *= var4;
      this.velZ -= 0.005F * var3;
      if (this.velZ < this.terminalVelocity) {
         this.velZ = this.terminalVelocity;
      }

      this.setNx(this.getNx() + this.velX * this.speedMod * 0.3F * var3);
      this.setNy(this.getNy() + this.velY * this.speedMod * 0.3F * var3);
    float var5 = this.getZ();
      this.setZ(this.getZ() + this.velZ * 0.4F * var3);
      if (this.getZ() < 0.0F) {
         this.setZ(0.0F);
         this.velZ = -this.velZ * 0.5F;
         this.collideGround();
      }

      if (this.getCurrentSquare() != nullptr
         && (int)this.getZ() < (int)var5
         && (var1 != nullptr && var1.TreatAsSolidFloor() || this.getCurrentSquare().TreatAsSolidFloor())) {
         this.setZ((int)var5);
         this.velZ = -this.velZ * 0.5F;
         this.collideGround();
      }

      if (Math.abs(this.velX) < 1.0E-4F) {
         this.velX = 0.0F;
      }

      if (Math.abs(this.velY) < 1.0E-4F) {
         this.velY = 0.0F;
      }

      if (this.velX + this.velY == 0.0F) {
         this.sprite.Animate = false;
      }

      this.sx = this.sy = 0.0F;
   }

    float getGlobalMovementMod(bool var1) {
      return 1.0F;
   }
}
} // namespace iso
} // namespace zombie
