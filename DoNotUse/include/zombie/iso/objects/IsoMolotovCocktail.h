#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoPhysicsObject.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoMolotovCocktail : public IsoPhysicsObject {
public:
    HandWeapon weapon = nullptr;
    IsoGameCharacter character = nullptr;
    int timer = 0;
    int explodeTimer = 0;

    std::string getObjectName() {
      return "MolotovCocktail";
   }

    public IsoMolotovCocktail(IsoCell var1) {
      super(var1);
   }

    public IsoMolotovCocktail(IsoCell var1, float var2, float var3, float var4, float var5, float var6, HandWeapon var7, IsoGameCharacter var8) {
      super(var1);
      this.weapon = var7;
      this.character = var8;
      this.explodeTimer = var7.getTriggerExplosionTimer();
      this.velX = var5;
      this.velY = var6;
    float var9 = Rand.Next(4000) / 10000.0F;
    float var10 = Rand.Next(4000) / 10000.0F;
      var9 -= 0.2F;
      var10 -= 0.2F;
      this.velX += var9;
      this.velY += var10;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.nx = var2;
      this.ny = var3;
      this.offsetX = 0.0F;
      this.offsetY = 0.0F;
      this.terminalVelocity = -0.02F;
    Texture var11 = this.sprite.LoadFrameExplicit(var7.getTex().getName());
      if (var11 != nullptr) {
         this.sprite.Animate = false;
    int var12 = Core.TileScale;
         this.sprite.def.scaleAspect(var11.getWidthOrig(), var11.getHeightOrig(), 16 * var12, 16 * var12);
      }

      this.speedMod = 0.6F;
   }

    void collideCharacter() {
      if (this.explodeTimer == 0) {
         this.Explode();
      }
   }

    void collideGround() {
      if (this.explodeTimer == 0) {
         this.Explode();
      }
   }

    void collideWall() {
      if (this.explodeTimer == 0) {
         this.Explode();
      }
   }

    void update() {
      super.update();
      if (this.isCollidedThisFrame() && this.explodeTimer == 0) {
         this.Explode();
      }

      if (this.explodeTimer > 0) {
         this.timer++;
         if (this.timer >= this.explodeTimer) {
            this.Explode();
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      super.render(var1, var2, var3, var4, var5, var6, var7);
      if (Core.bDebug) {
      }
   }

    void Explode() {
      this.setDestroyed(true);
      this.getCurrentSquare().getMovingObjects().remove(this);
      this.getCell().Remove(this);
      if (GameClient.bClient) {
         if (!(this.dynamic_cast<IsoPlayer*>(character) != nullptr) || !((IsoPlayer)this.character).isLocalPlayer()) {
            return;
         }

         this.square.syncIsoTrap(this.weapon);
      }

      if (this.weapon.isInstantExplosion()) {
    IsoTrap var1 = std::make_shared<IsoTrap>(this.weapon, this.getCurrentSquare().getCell(), this.getCurrentSquare());
         this.getCurrentSquare().AddTileObject(var1);
         var1.triggerExplosion(false);
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
