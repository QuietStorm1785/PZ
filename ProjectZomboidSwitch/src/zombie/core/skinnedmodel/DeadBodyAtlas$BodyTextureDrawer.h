#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/AtlasEntry.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    BodyTexture bodyTexture;
    float x;
    float y;
    float r;
    float g;
    float b;
    float a;

   private DeadBodyAtlas$BodyTextureDrawer() {
   }

   DeadBodyAtlas$BodyTextureDrawer init(BodyTexture var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      this.bodyTexture = var1;
      this.x = var2;
      this.y = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.a = var7;
    return this;
   }

    void render() {
    AtlasEntry var1 = this.bodyTexture.entry;
      if (var1.ready && var1.tex.isReady()) {
    int var2 = (int)(this.x - var1.w / 2.0F - var1.offsetX);
    int var3 = (int)(this.y - var1.h / 2.0F - var1.offsetY);
    int var4 = var1.w;
    int var5 = var1.h;
         var1.tex.bind();
         GL11.glBegin(7);
         GL11.glColor4f(this.r, this.g, this.b, this.a);
         GL11.glTexCoord2f(var1.tex.xStart, var1.tex.yStart);
         GL11.glVertex2i(var2, var3);
         GL11.glTexCoord2f(var1.tex.xEnd, var1.tex.yStart);
         GL11.glVertex2i(var2 + var4, var3);
         GL11.glTexCoord2f(var1.tex.xEnd, var1.tex.yEnd);
         GL11.glVertex2i(var2 + var4, var3 + var5);
         GL11.glTexCoord2f(var1.tex.xStart, var1.tex.yEnd);
         GL11.glVertex2i(var2, var3 + var5);
         GL11.glEnd();
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
   }

    void postRender() {
      this.bodyTexture = nullptr;
      DeadBodyAtlas.instance.bodyTextureDrawerPool.release(this);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
