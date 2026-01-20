#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoPhysicsObject.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoBall : public IsoPhysicsObject {
public:
    HandWeapon weapon = nullptr;
    IsoGameCharacter character = nullptr;
    int lastCheckX = 0;
    int lastCheckY = 0;

    std::string getObjectName() {
      return "MolotovCocktail";
   }

    public IsoBall(IsoCell var1) {
      super(var1);
   }

    public IsoBall(IsoCell var1, float var2, float var3, float var4, float var5, float var6, HandWeapon var7, IsoGameCharacter var8) {
      super(var1);
      this.weapon = var7;
      this.character = var8;
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

    void collideGround() {
      this.Fall();
   }

    void collideWall() {
      this.Fall();
   }

    void update() {
      super.update();
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      super.render(var1, var2, var3, var4, var5, var6, var7);
      if (Core.bDebug) {
      }
   }

    void Fall() {
      this.getCurrentSquare().getMovingObjects().remove(this);
      this.getCell().Remove(this);
      if (!GameClient.bClient) {
         WorldSoundManager.instance.addSound(this, (int)this.x, (int)this.y, 0, 600, 600);
      }

      if (this.dynamic_cast<IsoPlayer*>(character) != nullptr) {
         if (((IsoPlayer)this.character).isLocalPlayer()) {
            this.square.AddWorldInventoryItem(this.weapon, Rand.Next(0.2F, 0.8F), Rand.Next(0.2F, 0.8F), 0.0F, true);
         }
      } else {
         DebugLog.General.error("IsoBall: character isn't instance of IsoPlayer");
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
