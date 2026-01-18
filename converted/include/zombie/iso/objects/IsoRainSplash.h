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


class IsoRainSplash : public IsoObject {
public:
 int Age;

 bool Serialize() {
 return false;
 }

 public IsoRainSplash(IsoCell cell, IsoGridSquare gridSquare) {
 if (gridSquare != nullptr) {
 if (!gridSquare.getProperties().Is(IsoFlagType.HasRainSplashes) {
 this->Age = 0;
 this->square = gridSquare;
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 int int0 = 1 + Rand.Next(2);
 uint8_t byte0 = 16;
 uint8_t byte1 = 8;

 for (int int1 = 0; int1 < int0; int1++) {
 float float0 = Rand.Next(0.1F, 0.9F);
 float float1 = Rand.Next(0.1F, 0.9F);
 short short0 = (short)(IsoUtils.XToScreen(float0, float1, 0.0F, 0) - byte0 / 2);
 short short1 = (short)(IsoUtils.YToScreen(float0, float1, 0.0F, 0) - byte1 / 2);
 this->AttachAnim(
 "RainSplash", "00", 4, RainManager.RainSplashAnimDelay, -short0, -short1, true, 0, false, 0.7F, RainManager.RainSplashTintMod
 );
 this->AttachedAnimSprite.get(int1).Frame = (short)Rand.Next(4);
 this->AttachedAnimSprite.get(int1).setScale(Core.TileScale, Core.TileScale);
 }

 gridSquare.getProperties().Set(IsoFlagType.HasRainSplashes);
 RainManager.AddRainSplash(this);
 }
 }
 }

 std::string getObjectName() {
 return "RainSplashes";
 }

 bool HasTooltip() {
 return false;
 }

 bool TestCollide(IsoMovingObject obj, IsoGridSquare PassedObjectSquare) {
 return this->square == PassedObjectSquare;
 }

 public IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 return IsoObject.VisionResult.NoEffect;
 }

 void ChangeTintMod(ColorInfo NewTintMod) {
 if (this->AttachedAnimSprite != nullptr) {
 int int0 = 0;

 while (int0 < this->AttachedAnimSprite.size()) {
 int0++;
 }
 }
 }

 void update() {
 this->sx = this->sy = 0.0F;
 this->Age++;

 for (int int0 = 0; int0 < this->AttachedAnimSprite.size(); int0++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int0);
 IsoSprite sprite = spriteInstance.parentSprite;
 spriteInstance.update();
 spriteInstance.Frame = spriteInstance.Frame + spriteInstance.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
 if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() && sprite.Loop && spriteInstance.Looped) {
 spriteInstance.Frame = 0.0F;
 }
 }

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
 this->setAlphaAndTarget(int1, 0.25F);
 } else {
 this->setAlphaAndTarget(int1, 0.6F);
 }
 }
 }

 void Reset(IsoGridSquare square) {
 if (square != nullptr) {
 if (!square.getProperties().Is(IsoFlagType.HasRainSplashes) {
 this->Age = 0;
 this->square = square;
 int int0 = 1 + Rand.Next(2);
 if (this->AttachedAnimSprite != nullptr) {
 int int1 = 0;

 while (int1 < this->AttachedAnimSprite.size()) {
 int1++;
 }
 }

 square.getProperties().Set(IsoFlagType.HasRainSplashes);
 RainManager.AddRainSplash(this);
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
