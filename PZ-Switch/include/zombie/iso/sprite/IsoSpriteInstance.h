#pragma once
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoSpriteInstance {
public:
public
 static ObjectPool<IsoSpriteInstance> pool =
 new ObjectPool<>(IsoSpriteInstance::new);
 static const AtomicBoolean lock = new AtomicBoolean(false);
 IsoSprite parentSprite;
 float tintb = 1.0F;
 float tintg = 1.0F;
 float tintr = 1.0F;
 float Frame = 0.0F;
 float alpha = 1.0F;
 float targetAlpha = 1.0F;
 bool bCopyTargetAlpha = true;
 bool bMultiplyObjectAlpha = false;
 bool Flip;
 float offZ = 0.0F;
 float offX = 0.0F;
 float offY = 0.0F;
 float AnimFrameIncrease = 1.0F;
 static float multiplier = 1.0F;
 bool Looped = true;
 bool Finished = false;
 bool NextFrame;
 float scaleX = 1.0F;
 float scaleY = 1.0F;

 static IsoSpriteInstance get(IsoSprite spr) {
 while (!lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 IsoSpriteInstance spriteInstance = pool.alloc();
 lock.set(false);
 spriteInstance.parentSprite = spr;
 spriteInstance.reset();
 return spriteInstance;
 }

 void reset() {
 this->tintb = 1.0F;
 this->tintg = 1.0F;
 this->tintr = 1.0F;
 this->Frame = 0.0F;
 this->alpha = 1.0F;
 this->targetAlpha = 1.0F;
 this->bCopyTargetAlpha = true;
 this->bMultiplyObjectAlpha = false;
 this->Flip = false;
 this->offZ = 0.0F;
 this->offX = 0.0F;
 this->offY = 0.0F;
 this->AnimFrameIncrease = 1.0F;
 multiplier = 1.0F;
 this->Looped = true;
 this->Finished = false;
 this->NextFrame = false;
 this->scaleX = 1.0F;
 this->scaleY = 1.0F;
 }

public
 IsoSpriteInstance() {}

 void setFrameSpeedPerFrame(float perSecond) {
 this->AnimFrameIncrease = perSecond * multiplier;
 }

 int getID() { return this->parentSprite.ID; }

 std::string getName() { return this->parentSprite.getName(); }

 IsoSprite getParentSprite() { return this->parentSprite; }

public
 IsoSpriteInstance(IsoSprite spr) { this->parentSprite = spr; }

 float getTintR() { return this->tintr; }

 float getTintG() { return this->tintg; }

 float getTintB() { return this->tintb; }

 float getAlpha() { return this->alpha; }

 float getTargetAlpha() noexcept{ return this->targetAlpha; }

 bool isCopyTargetAlpha() noexcept{ return this->bCopyTargetAlpha; }

 bool isMultiplyObjectAlpha() { return this->bMultiplyObjectAlpha; }

 void render(IsoObject obj, float x, float y, float z, IsoDirections dir,
 float offsetX, float offsetY, ColorInfo info2) {
 this->parentSprite.render(this, obj, x, y, z, dir, offsetX, offsetY, info2,
 true);
 }

 void SetAlpha(float f) {
 this->alpha = f;
 this->bCopyTargetAlpha = false;
 }

 void SetTargetAlpha(float _targetAlpha) {
 this->targetAlpha = _targetAlpha;
 this->bCopyTargetAlpha = false;
 }

 void update() {}

 void renderprep(IsoObject object) {
 if (object != nullptr && this->bCopyTargetAlpha) {
 this->targetAlpha =
 object.getTargetAlpha(IsoCamera.frameState.playerIndex);
 this->alpha = object.getAlpha(IsoCamera.frameState.playerIndex);
 } else if (!this->bMultiplyObjectAlpha) {
 if (this->alpha < this->targetAlpha) {
 this->alpha = this->alpha + IsoSprite.alphaStep;
 if (this->alpha > this->targetAlpha) {
 this->alpha = this->targetAlpha;
 }
 } else if (this->alpha > this->targetAlpha) {
 this->alpha = this->alpha - IsoSprite.alphaStep;
 if (this->alpha < this->targetAlpha) {
 this->alpha = this->targetAlpha;
 }
 }

 if (this->alpha < 0.0F) {
 this->alpha = 0.0F;
 }

 if (this->alpha > 1.0F) {
 this->alpha = 1.0F;
 }
 }
 }

 float getFrame() { return this->Frame; }

 bool isFinished() { return this->Finished; }

 void Dispose() {}

 void RenderGhostTileColor(int x, int y, int z, float r, float g, float b,
 float a) {
 if (this->parentSprite != nullptr) {
 IsoSpriteInstance spriteInstance = get(this->parentSprite);
 spriteInstance.Frame = this->Frame;
 spriteInstance.tintr = r;
 spriteInstance.tintg = g;
 spriteInstance.tintb = b;
 spriteInstance.alpha = spriteInstance.targetAlpha = a;
 IsoGridSquare.getDefColorInfo().r = IsoGridSquare.getDefColorInfo().g =
 IsoGridSquare.getDefColorInfo().b =
 IsoGridSquare.getDefColorInfo().a = 1.0F;
 this->parentSprite.render(spriteInstance, nullptr, x, y, z,
 IsoDirections.N, 0.0F, -144.0F,
 IsoGridSquare.getDefColorInfo(), true);
 }
 }

 void setScale(float _scaleX, float _scaleY) {
 this->scaleX = _scaleX;
 this->scaleY = _scaleY;
 }

 float getScaleX() { return this->scaleX; }

 float getScaleY() { return this->scaleY; }

 void scaleAspect(float texW, float texH, float width, float height) {
 if (texW > 0.0F && texH > 0.0F && width > 0.0F && height > 0.0F) {
 float float0 = height * texW / texH;
 float float1 = width * texH / texW;
 bool boolean0 = float0 <= width;
 if (boolean0) {
 width = float0;
 } else {
 height = float1;
 }

 this->scaleX = width / texW;
 this->scaleY = height / texH;
 }
 }

 static void add(IsoSpriteInstance isoSpriteInstance) {
 isoSpriteInstance.reset();

 while (!lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 pool.release(isoSpriteInstance);
 lock.set(false);
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
