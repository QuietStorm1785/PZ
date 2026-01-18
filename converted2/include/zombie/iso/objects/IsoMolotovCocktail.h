#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoMolotovCocktail : public IsoPhysicsObject {
public:
  HandWeapon weapon = null;
  IsoGameCharacter character = null;
  int timer = 0;
  int explodeTimer = 0;

  std::string getObjectName() { return "MolotovCocktail"; }

public
  IsoMolotovCocktail(IsoCell cell) { super(cell); }

public
  IsoMolotovCocktail(IsoCell cell, float x, float y, float z, float xvel,
                     float yvel, HandWeapon _weapon,
                     IsoGameCharacter _character) {
    super(cell);
    this.weapon = _weapon;
    this.character = _character;
    this.explodeTimer = _weapon.getTriggerExplosionTimer();
    this.velX = xvel;
    this.velY = yvel;
    float float0 = Rand.Next(4000) / 10000.0F;
    float float1 = Rand.Next(4000) / 10000.0F;
    float0 -= 0.2F;
    float1 -= 0.2F;
    this.velX += float0;
    this.velY += float1;
    this.x = x;
    this.y = y;
    this.z = z;
    this.nx = x;
    this.ny = y;
    this.offsetX = 0.0F;
    this.offsetY = 0.0F;
    this.terminalVelocity = -0.02F;
    Texture texture = this.sprite.LoadFrameExplicit(_weapon.getTex().getName());
    if (texture != nullptr) {
      this.sprite.Animate = false;
      int int0 = Core.TileScale;
      this.sprite.def.scaleAspect(texture.getWidthOrig(),
                                  texture.getHeightOrig(), 16 * int0,
                                  16 * int0);
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

  void render(float x, float y, float z, ColorInfo info, bool bDoAttached,
              bool bWallLightingPass, Shader shader) {
    super.render(x, y, z, info, bDoAttached, bWallLightingPass, shader);
    if (Core.bDebug) {
    }
  }

  void Explode() {
    this.setDestroyed(true);
    this.getCurrentSquare().getMovingObjects().remove(this);
    this.getCell().Remove(this);
    if (GameClient.bClient) {
      if (!(this.character instanceof IsoPlayer) ||
          !((IsoPlayer)this.character).isLocalPlayer()) {
        return;
      }

      this.square.syncIsoTrap(this.weapon);
    }

    if (this.weapon.isInstantExplosion()) {
      IsoTrap trap = new IsoTrap(this.weapon, this.getCurrentSquare().getCell(),
                                 this.getCurrentSquare());
      this.getCurrentSquare().AddTileObject(trap);
      trap.triggerExplosion(false);
    }
  }
}
} // namespace objects
} // namespace iso
} // namespace zombie
