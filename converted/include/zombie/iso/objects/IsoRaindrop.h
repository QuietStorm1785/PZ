#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoRaindrop : public IsoObject {
public:
 int AnimSpriteIndex;
 float GravMod;
 int Life;
 float SplashY;
 float OffsetY;
 float Vel_Y;

 bool Serialize() {
 return false;
 }

 public IsoRaindrop(IsoCell cell, IsoGridSquare gridSquare, bool CanSee) {
 if (CanSee) {
 if (gridSquare != nullptr) {
 if (!gridSquare.getProperties().Is(IsoFlagType.HasRaindrop) {
 this->Life = 0;
 this->square = gridSquare;
 int int0 = 1 * Core.TileScale;
 int int1 = 64 * Core.TileScale;
 float float0 = Rand.Next(0.1F, 0.9F);
 float float1 = Rand.Next(0.1F, 0.9F);
 short short0 = (short)(IsoUtils.XToScreen(float0, float1, 0.0F, 0) - int0 / 2);
 short short1 = (short)(IsoUtils.YToScreen(float0, float1, 0.0F, 0) - int1);
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 this->OffsetY = RainManager.RaindropStartDistance;
 this->SplashY = short1;
 this->AttachAnim("Rain", "00", 1, 0.0F, -short0, -short1, true, 0, false, 0.7F, RainManager.RaindropTintMod);
 if (this->AttachedAnimSprite != nullptr) {
 this->AnimSpriteIndex = this->AttachedAnimSprite.size() - 1;
 } else {
 this->AnimSpriteIndex = 0;
 }

 this->AttachedAnimSprite.get(this->AnimSpriteIndex).setScale(Core.TileScale, Core.TileScale);
 gridSquare.getProperties().Set(IsoFlagType.HasRaindrop);
 this->Vel_Y = 0.0F;
 float float2 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
 this->GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * float2);
 RainManager.AddRaindrop(this);
 }
 }
 }
 }

 bool HasTooltip() {
 return false;
 }

 std::string getObjectName() {
 return "RainDrops";
 }

 bool TestCollide(IsoMovingObject obj, IsoGridSquare PassedObjectSquare) {
 return this->square == PassedObjectSquare;
 }

 public IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 return IsoObject.VisionResult.NoEffect;
 }

 void ChangeTintMod(ColorInfo NewTintMod) {
 }

 void update() {
 this->sx = this->sy = 0.0F;
 this->Life++;

 for (int int0 = 0; int0 < this->AttachedAnimSprite.size(); int0++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int0);
 spriteInstance.update();
 spriteInstance.Frame = spriteInstance.Frame + spriteInstance.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
 IsoSprite sprite = spriteInstance.parentSprite;
 if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() && sprite.Loop && spriteInstance.Looped) {
 spriteInstance.Frame = 0.0F;
 }
 }

 this->Vel_Y = this->Vel_Y + this->GravMod * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
 this->OffsetY = this->OffsetY + this->Vel_Y;
 if (this->AttachedAnimSprite != nullptr && this->AttachedAnimSprite.size() > this->AnimSpriteIndex && this->AnimSpriteIndex >= 0) {
 this->AttachedAnimSprite.get(this->AnimSpriteIndex).parentSprite.soffY = (short)(this->SplashY + (int)this->OffsetY);
 }

 if (this->OffsetY < 0.0F) {
 this->OffsetY = RainManager.RaindropStartDistance;
 this->Vel_Y = 0.0F;
 float float0 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
 this->GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * float0);
 }

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
 this->setAlphaAndTarget(int1, 0.55F);
 } else {
 this->setAlphaAndTarget(int1, 1.0F);
 }
 }
 }

 void Reset(IsoGridSquare square, bool boolean0) {
 if (boolean0) {
 if (square != nullptr) {
 if (!square.getProperties().Is(IsoFlagType.HasRaindrop) {
 this->Life = 0;
 this->square = square;
 this->OffsetY = RainManager.RaindropStartDistance;
 if (this->AttachedAnimSprite != nullptr) {
 this->AnimSpriteIndex = this->AttachedAnimSprite.size() - 1;
 } else {
 this->AnimSpriteIndex = 0;
 }

 square.getProperties().Set(IsoFlagType.HasRaindrop);
 this->Vel_Y = 0.0F;
 float float0 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
 this->GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * float0);
 RainManager.AddRaindrop(this);
 }
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
