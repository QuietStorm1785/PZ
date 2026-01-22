#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {


class IsoSpriteInstance {
public:
   public static const ObjectPool<IsoSpriteInstance> pool = std::make_shared<ObjectPool>(IsoSpriteInstance::new);
    static const AtomicBoolean lock = std::make_shared<AtomicBoolean>(false);
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

    static IsoSpriteInstance get(IsoSprite var0) {
      while (!lock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

    IsoSpriteInstance var1 = (IsoSpriteInstance)pool.alloc();
      lock.set(false);
      var1.parentSprite = var0;
      var1.reset();
    return var1;
   }

    void reset() {
      this.tintb = 1.0F;
      this.tintg = 1.0F;
      this.tintr = 1.0F;
      this.Frame = 0.0F;
      this.alpha = 1.0F;
      this.targetAlpha = 1.0F;
      this.bCopyTargetAlpha = true;
      this.bMultiplyObjectAlpha = false;
      this.Flip = false;
      this.offZ = 0.0F;
      this.offX = 0.0F;
      this.offY = 0.0F;
      this.AnimFrameIncrease = 1.0F;
      multiplier = 1.0F;
      this.Looped = true;
      this.Finished = false;
      this.NextFrame = false;
      this.scaleX = 1.0F;
      this.scaleY = 1.0F;
   }

    public IsoSpriteInstance() {
   }

    void setFrameSpeedPerFrame(float var1) {
      this.AnimFrameIncrease = var1 * multiplier;
   }

    int getID() {
      return this.parentSprite.ID;
   }

    std::string getName() {
      return this.parentSprite.getName();
   }

    IsoSprite getParentSprite() {
      return this.parentSprite;
   }

    public IsoSpriteInstance(IsoSprite var1) {
      this.parentSprite = var1;
   }

    float getTintR() {
      return this.tintr;
   }

    float getTintG() {
      return this.tintg;
   }

    float getTintB() {
      return this.tintb;
   }

    float getAlpha() {
      return this.alpha;
   }

    float getTargetAlpha() {
      return this.targetAlpha;
   }

    bool isCopyTargetAlpha() {
      return this.bCopyTargetAlpha;
   }

    bool isMultiplyObjectAlpha() {
      return this.bMultiplyObjectAlpha;
   }

    void render(IsoObject var1, float var2, float var3, float var4, IsoDirections var5, float var6, float var7, ColorInfo var8) {
      this.parentSprite.render(this, var1, var2, var3, var4, var5, var6, var7, var8, true);
   }

    void SetAlpha(float var1) {
      this.alpha = var1;
      this.bCopyTargetAlpha = false;
   }

    void SetTargetAlpha(float var1) {
      this.targetAlpha = var1;
      this.bCopyTargetAlpha = false;
   }

    void update() {
   }

    void renderprep(IsoObject var1) {
      if (var1 != nullptr && this.bCopyTargetAlpha) {
         this.targetAlpha = var1.getTargetAlpha(IsoCamera.frameState.playerIndex);
         this.alpha = var1.getAlpha(IsoCamera.frameState.playerIndex);
      } else if (!this.bMultiplyObjectAlpha) {
         if (this.alpha < this.targetAlpha) {
            this.alpha = this.alpha + IsoSprite.alphaStep;
            if (this.alpha > this.targetAlpha) {
               this.alpha = this.targetAlpha;
            }
         } else if (this.alpha > this.targetAlpha) {
            this.alpha = this.alpha - IsoSprite.alphaStep;
            if (this.alpha < this.targetAlpha) {
               this.alpha = this.targetAlpha;
            }
         }

         if (this.alpha < 0.0F) {
            this.alpha = 0.0F;
         }

         if (this.alpha > 1.0F) {
            this.alpha = 1.0F;
         }
      }
   }

    float getFrame() {
      return this.Frame;
   }

    bool isFinished() {
      return this.Finished;
   }

    void Dispose() {
   }

    void RenderGhostTileColor(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      if (this.parentSprite != nullptr) {
    IsoSpriteInstance var8 = get(this.parentSprite);
         var8.Frame = this.Frame;
         var8.tintr = var4;
         var8.tintg = var5;
         var8.tintb = var6;
         var8.alpha = var8.targetAlpha = var7;
         IsoGridSquare.getDefColorInfo().r = IsoGridSquare.getDefColorInfo().g = IsoGridSquare.getDefColorInfo().b = IsoGridSquare.getDefColorInfo().a = 1.0F;
         this.parentSprite.render(var8, nullptr, var1, var2, var3, IsoDirections.N, 0.0F, -144.0F, IsoGridSquare.getDefColorInfo(), true);
      }
   }

    void setScale(float var1, float var2) {
      this.scaleX = var1;
      this.scaleY = var2;
   }

    float getScaleX() {
      return this.scaleX;
   }

    float getScaleY() {
      return this.scaleY;
   }

    void scaleAspect(float var1, float var2, float var3, float var4) {
      if (var1 > 0.0F && var2 > 0.0F && var3 > 0.0F && var4 > 0.0F) {
    float var5 = var4 * var1 / var2;
    float var6 = var3 * var2 / var1;
    bool var7 = var5 <= var3;
         if (var7) {
            var3 = var5;
         } else {
            var4 = var6;
         }

         this.scaleX = var3 / var1;
         this.scaleY = var4 / var2;
      }
   }

    static void add(IsoSpriteInstance var0) {
      var0.reset();

      while (!lock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      pool.release(var0);
      lock.set(false);
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
