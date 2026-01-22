#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL12.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/opengl/GL20.h"
#include "zombie/core/SpriteRenderer/RingBuffer.h"
#include "zombie/core/Styles/AdditiveStyle.h"
#include "zombie/core/Styles/LightingStyle.h"
#include "zombie/core/Styles/Style.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoGridSquare/CircleStencilShader.h"
#include "zombie/iso/IsoGridSquare/NoCircleStencilShader.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <filesystem>

namespace zombie {
namespace core {


class SpriteRenderer {
public:
    Texture texture0;
    Texture texture1;
    uint8_t useAttribArray;
    Style style;
    int start;
    int length;
    ShortBuffer indices;
    int startIndex;
    int endIndex;
   const std::vector<TextureDraw> ops;

   private SpriteRenderer$RingBuffer$StateRun(RingBuffer var1) {
      this.this$0 = var1;
      this.useAttribArray = -1;
      this.ops = std::make_unique<std::vector<>>();
   }

    std::string toString() {
    std::string var1 = System.lineSeparator();
      return this.getClass().getSimpleName()
         + "{ "
         + var1
         + "  ops:"
         + PZArrayUtil.arrayToString(this.ops, "{", "}", ", ")
         + var1
         + "  texture0:"
         + this.texture0
         + var1
         + "  texture1:"
         + this.texture1
         + var1
         + "  useAttribArray:"
         + this.useAttribArray
         + var1
         + "  style:"
         + this.style
         + var1
         + "  start:"
         + this.start
         + var1
         + "  length:"
         + this.length
         + var1
         + "  indices:"
         + this.indices
         + var1
         + "  startIndex:"
         + this.startIndex
         + var1
         + "  endIndex:"
         + this.endIndex
         + var1
         + "}";
   }

    void render() {
      if (this.style != nullptr) {
    int var1 = this.ops.size();
         if (var1 > 0) {
            for (int var8 = 0; var8 < var1; var8++) {
               this.ops.get(var8).run();
            }

            this.ops.clear();
         } else {
            if (this.style != this.this$0.lastRenderedStyle) {
               if (this.this$0.lastRenderedStyle != nullptr
                  && (
                     !RingBuffer.IGNORE_STYLES
                        || this.this$0.lastRenderedStyle != AdditiveStyle.instance
                           && this.this$0.lastRenderedStyle != TransparentStyle.instance
                           && this.this$0.lastRenderedStyle != LightingStyle.instance
                  )) {
                  this.this$0.lastRenderedStyle.resetState();
               }

               if (this.style != nullptr
                  && (
                     !RingBuffer.IGNORE_STYLES
                        || this.style != AdditiveStyle.instance && this.style != TransparentStyle.instance && this.style != LightingStyle.instance
                  )) {
                  this.style.setupState();
               }

               this.this$0.lastRenderedStyle = this.style;
            }

            if (this.this$0.lastRenderedTexture0 != nullptr && this.this$0.lastRenderedTexture0.getID() != Texture.lastTextureID) {
               this.this$0.restoreBoundTextures = true;
            }

            if (this.this$0.restoreBoundTextures) {
               Texture.lastTextureID = 0;
               GL11.glBindTexture(3553, 0);
               if (this.texture0 == nullptr) {
                  GL11.glDisable(3553);
               }

               this.this$0.lastRenderedTexture0 = nullptr;
               this.this$0.lastRenderedTexture1 = nullptr;
               this.this$0.restoreBoundTextures = false;
            }

            if (this.texture0 != this.this$0.lastRenderedTexture0) {
               if (this.texture0 != nullptr) {
                  if (this.this$0.lastRenderedTexture0 == nullptr) {
                     GL11.glEnable(3553);
                  }

                  this.texture0.bind();
               } else {
                  GL11.glDisable(3553);
                  Texture.lastTextureID = 0;
                  GL11.glBindTexture(3553, 0);
               }

               this.this$0.lastRenderedTexture0 = this.texture0;
            }

            if (DebugOptions.instance.Checks.BoundTextures.getValue()) {
               this.this$0.debugBoundTexture(this.this$0.lastRenderedTexture0, 33984);
            }

            if (this.texture1 != this.this$0.lastRenderedTexture1) {
               GL13.glActiveTexture(33985);
               GL13.glClientActiveTexture(33985);
               if (this.texture1 != nullptr) {
                  GL11.glBindTexture(3553, this.texture1.getID());
               } else {
                  GL11.glDisable(3553);
               }

               GL13.glActiveTexture(33984);
               GL13.glClientActiveTexture(33984);
               this.this$0.lastRenderedTexture1 = this.texture1;
            }

            if (this.useAttribArray != this.this$0.lastUseAttribArray) {
               if (this.useAttribArray != -1) {
                  if (this.useAttribArray == 1) {
    int var2 = CircleStencilShader.instance.a_wallShadeColor;
                     if (var2 != -1) {
                        GL20.glEnableVertexAttribArray(var2);
                     }
                  }

                  if (this.useAttribArray == 2) {
    int var3 = NoCircleStencilShader.instance.a_wallShadeColor;
                     if (var3 != -1) {
                        GL20.glEnableVertexAttribArray(var3);
                     }
                  }
               } else {
                  if (this.this$0.lastUseAttribArray == 1) {
    int var4 = CircleStencilShader.instance.a_wallShadeColor;
                     if (var4 != -1) {
                        GL20.glDisableVertexAttribArray(var4);
                     }
                  }

                  if (this.this$0.lastUseAttribArray == 2) {
    int var5 = NoCircleStencilShader.instance.a_wallShadeColor;
                     if (var5 != -1) {
                        GL20.glDisableVertexAttribArray(var5);
                     }
                  }
               }

               this.this$0.lastUseAttribArray = this.useAttribArray;
            }

            if (this.length != 0) {
               if (this.length == -1) {
                  this.this$0.restoreVBOs = true;
               } else {
                  if (this.this$0.restoreVBOs) {
                     this.this$0.restoreVBOs = false;
                     this.this$0.vbo[this.this$0.sequence].bind();
                     this.this$0.ibo[this.this$0.sequence].bind();
                     GL11.glVertexPointer(2, 5126, 32, 0L);
                     GL11.glTexCoordPointer(2, 5126, 32, 8L);
                     GL11.glColorPointer(4, 5121, 32, 28L);
                     GL13.glActiveTexture(33985);
                     GL13.glClientActiveTexture(33985);
                     GL11.glTexCoordPointer(2, 5126, 32, 16L);
                     GL11.glEnableClientState(32888);
    int var6 = CircleStencilShader.instance.a_wallShadeColor;
                     if (var6 != -1) {
                        GL20.glVertexAttribPointer(var6, 4, 5121, true, 32, 24L);
                     }

                     var6 = NoCircleStencilShader.instance.a_wallShadeColor;
                     if (var6 != -1) {
                        GL20.glVertexAttribPointer(var6, 4, 5121, true, 32, 24L);
                     }

                     GL13.glActiveTexture(33984);
                     GL13.glClientActiveTexture(33984);
                  }

                  if (!$assertionsDisabled && GL11.glGetInteger(34964) != this.this$0.vbo[this.this$0.sequence].getID()) {
                     throw std::make_unique<AssertionError>();
                  } else {
                     if (this.useAttribArray == 1) {
                        this.this$0.vbo[this.this$0.sequence].enableVertexAttribArray(CircleStencilShader.instance.a_wallShadeColor);
                        if (!$assertionsDisabled && GL20.glGetVertexAttribi(CircleStencilShader.instance.a_wallShadeColor, 34975) == 0) {
                           throw std::make_unique<AssertionError>();
                        }
                     } else if (this.useAttribArray == 2) {
                        this.this$0.vbo[this.this$0.sequence].enableVertexAttribArray(NoCircleStencilShader.instance.a_wallShadeColor);
                     } else {
                        this.this$0.vbo[this.this$0.sequence].disableVertexAttribArray();
                     }

                     if (this.style.getRenderSprite()) {
                        GL12.glDrawRangeElements(4, this.start, this.start + this.length, this.endIndex - this.startIndex, 5123, this.startIndex * 2L);
                     } else {
                        this.style.render(this.start, this.startIndex);
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace core
} // namespace zombie
