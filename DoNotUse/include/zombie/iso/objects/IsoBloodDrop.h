#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoPhysicsObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoBloodDrop : public IsoPhysicsObject {
public:
    float tintb = 1.0F;
    float tintg = 1.0F;
    float tintr = 1.0F;
    float time = 0.0F;
    float sx = 0.0F;
    float sy = 0.0F;
    float lsx = 0.0F;
    float lsy = 0.0F;
    static Vector2 temp = std::make_shared<Vector2>();

    public IsoBloodDrop(IsoCell var1) {
      super(var1);
   }

    bool Serialize() {
    return false;
   }

    std::string getObjectName() {
      return "ZombieGiblets";
   }

    void collideGround() {
    float var1 = this.x - (int)this.x;
    float var2 = this.y - (int)this.y;
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare((int)this.x, (int)this.y, (int)this.z);
      if (var3 != nullptr) {
    IsoObject var4 = var3.getFloor();
         var4.addChild(this);
         this.setCollidable(false);
         IsoWorld.instance.CurrentCell.getRemoveList().push_back(this);
      }
   }

    void collideWall() {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare((int)this.x, (int)this.y, (int)this.z);
      if (var1 != nullptr) {
    IsoObject var2 = nullptr;
         if (this.isCollidedN()) {
            var2 = var1.getWall(true);
         } else if (this.isCollidedS()) {
            var1 = IsoWorld.instance.CurrentCell.getGridSquare((int)this.x, (int)this.y + 1, (int)this.z);
            if (var1 != nullptr) {
               var2 = var1.getWall(true);
            }
         } else if (this.isCollidedW()) {
            var2 = var1.getWall(false);
         } else if (this.isCollidedE()) {
            var1 = IsoWorld.instance.CurrentCell.getGridSquare((int)this.x + 1, (int)this.y, (int)this.z);
            if (var1 != nullptr) {
               var2 = var1.getWall(false);
            }
         }

         if (var2 != nullptr) {
            var2.addChild(this);
            this.setCollidable(false);
            IsoWorld.instance.CurrentCell.getRemoveList().push_back(this);
         }
      }
   }

    void update() {
      super.update();
      this.time = this.time + GameTime.instance.getMultipliedSecondsSinceLastUpdate();
      if (this.velX == 0.0F && this.velY == 0.0F && this.getZ() == (int)this.getZ()) {
         this.setCollidable(false);
         IsoWorld.instance.CurrentCell.getRemoveList().push_back(this);
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      this.setTargetAlpha(0.3F);
      this.sprite.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY, var4, true);
   }

    public IsoBloodDrop(IsoCell var1, float var2, float var3, float var4, float var5, float var6) {
      super(var1);
      this.velX = var5 * 2.0F;
      this.velY = var6 * 2.0F;
      this.terminalVelocity = -0.1F;
      this.velZ = this.velZ + (Rand.Next(10000) / 10000.0F - 0.5F) * 0.05F;
    float var7 = Rand.Next(9000) / 10000.0F;
      var7 += 0.1F;
      this.velX *= var7;
      this.velY *= var7;
      this.velZ += var7 * 0.05F;
      if (Rand.Next(7) == 0) {
         this.velX *= 2.0F;
         this.velY *= 2.0F;
      }

      this.velX *= 0.8F;
      this.velY *= 0.8F;
      temp.x = this.velX;
      temp.y = this.velY;
      temp.rotate((Rand.Next(1000) / 1000.0F - 0.5F) * 0.07F);
      if (Rand.Next(3) == 0) {
         temp.rotate((Rand.Next(1000) / 1000.0F - 0.5F) * 0.1F);
      }

      if (Rand.Next(5) == 0) {
         temp.rotate((Rand.Next(1000) / 1000.0F - 0.5F) * 0.2F);
      }

      if (Rand.Next(8) == 0) {
         temp.rotate((Rand.Next(1000) / 1000.0F - 0.5F) * 0.3F);
      }

      if (Rand.Next(10) == 0) {
         temp.rotate((Rand.Next(1000) / 1000.0F - 0.5F) * 0.4F);
      }

      this.velX = temp.x;
      this.velY = temp.y;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.nx = var2;
      this.ny = var3;
      this.setAlpha(0.5F);
      this.def = IsoSpriteInstance.get(this.sprite);
      this.def.alpha = 0.4F;
      this.sprite.def.alpha = 0.4F;
      this.offsetX = -26.0F;
      this.offsetY = -242.0F;
      this.offsetX += 8.0F;
      this.offsetY += 9.0F;
      this.sprite.LoadFramesNoDirPageSimple("BloodSplat");
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
