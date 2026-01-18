#pragma once
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

class IsoBall : public IsoPhysicsObject {
public:
 HandWeapon weapon = nullptr;
 IsoGameCharacter character = nullptr;
 int lastCheckX = 0;
 int lastCheckY = 0;

 std::string getObjectName() { return "MolotovCocktail"; }

public
 IsoBall(IsoCell cell) { super(cell); }

public
 IsoBall(IsoCell cell, float float4, float float5, float float6, float float0,
 float float1, HandWeapon weaponx, IsoGameCharacter characterx) {
 super(cell);
 this->weapon = weaponx;
 this->character = characterx;
 this->velX = float0;
 this->velY = float1;
 float float2 = Rand.Next(4000) / 10000.0F;
 float float3 = Rand.Next(4000) / 10000.0F;
 float2 -= 0.2F;
 float3 -= 0.2F;
 this->velX += float2;
 this->velY += float3;
 this->x = float4;
 this->y = float5;
 this->z = float6;
 this->nx = float4;
 this->ny = float5;
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 this->terminalVelocity = -0.02F;
 Texture texture = this->sprite.LoadFrameExplicit(weaponx.getTex().getName());
 if (texture != nullptr) {
 this->sprite.Animate = false;
 int int0 = Core.TileScale;
 this->sprite.def.scaleAspect(texture.getWidthOrig(),
 texture.getHeightOrig(), 16 * int0,
 16 * int0);
 }

 this->speedMod = 0.6F;
 }

 void collideGround() { this->Fall(); }

 void collideWall() { this->Fall(); }

 void update() { super.update(); }

 void render(float float0, float float1, float float2, ColorInfo colorInfo,
 bool boolean0, bool boolean1, Shader shader) {
 super.render(float0, float1, float2, colorInfo, boolean0, boolean1, shader);
 if (Core.bDebug) {
 }
 }

 void Fall() {
 this->getCurrentSquare().getMovingObjects().remove(this);
 this->getCell().Remove(this);
 if (!GameClient.bClient) {
 WorldSoundManager.instance.addSound(this, (int)this->x, (int)this->y, 0,
 600, 600);
 }

 if (this->character instanceof IsoPlayer) {
 if (((IsoPlayer)this->character).isLocalPlayer()) {
 this->square.AddWorldInventoryItem(this->weapon, Rand.Next(0.2F, 0.8F),
 Rand.Next(0.2F, 0.8F), 0.0F, true);
 }
 } else {
 DebugLog.General.error("IsoBall: character isn't instance of IsoPlayer");
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
