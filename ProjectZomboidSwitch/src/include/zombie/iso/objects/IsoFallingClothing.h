#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoPhysicsObject.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoFallingClothing : public IsoPhysicsObject {
public:
    InventoryItem clothing = nullptr;
    int dropTimer = 0;
    bool addWorldItem = true;

    std::string getObjectName() {
      return "FallingClothing";
   }

    public IsoFallingClothing(IsoCell var1) {
      super(var1);
   }

    public IsoFallingClothing(IsoCell var1, float var2, float var3, float var4, float var5, float var6, InventoryItem var7) {
      super(var1);
      this.clothing = var7;
      this.dropTimer = 60;
      this.velX = var5;
      this.velY = var6;
    float var8 = Rand.Next(4000) / 10000.0F;
    float var9 = Rand.Next(4000) / 10000.0F;
      var8 -= 0.2F;
      var9 -= 0.2F;
      this.velX += var8;
      this.velY += var9;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.nx = var2;
      this.ny = var3;
      this.offsetX = 0.0F;
      this.offsetY = 0.0F;
      this.terminalVelocity = -0.02F;
    Texture var10 = this.sprite.LoadFrameExplicit(var7.getTex().getName());
      if (var10 != nullptr) {
         this.sprite.Animate = false;
    int var11 = Core.TileScale;
         this.sprite.def.scaleAspect(var10.getWidthOrig(), var10.getHeightOrig(), 16 * var11, 16 * var11);
      }

      this.speedMod = 4.5F;
   }

    void collideGround() {
      this.drop();
   }

    void collideWall() {
      this.drop();
   }

    void update() {
      super.update();
      this.dropTimer--;
      if (this.dropTimer <= 0) {
         this.drop();
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    float var8 = (60 - this.dropTimer) / 60.0F * 360.0F;
      if (!WorldItemModelDrawer.renderMain(this.clothing, this.getCurrentSquare(), this.getX(), this.getY(), this.getZ(), var8)) {
         super.render(var1, var2, var3, var4, var5, var6, var7);
      }
   }

    void drop() {
    IsoGridSquare var1 = this.getCurrentSquare();
      if (var1 != nullptr && this.clothing != nullptr) {
         if (this.addWorldItem) {
    float var2 = var1.getApparentZ(this.getX() % 1.0F, this.getY() % 1.0F);
            var1.AddWorldInventoryItem(this.clothing, this.getX() % 1.0F, this.getY() % 1.0F, var2 - var1.getZ());
         }

         this.clothing = nullptr;
         this.setDestroyed(true);
         var1.getMovingObjects().remove(this);
         this.getCell().Remove(this);
         LuaEventManager.triggerEvent("OnContainerUpdate", var1);
      }
   }

    void Trigger() {
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
