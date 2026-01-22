#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/SpriteRenderer/WallShaderTexRender.h"
#include "zombie/core/Styles/AbstractStyle.h"
#include "zombie/core/Styles/Style.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureDraw/Type.h"
#include "zombie/core/textures/TextureFBO.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace sprite {


class GenericSpriteRenderState {
public:
    const int index;
   public TextureDraw[] sprite = new TextureDraw[2048];
   public Style[] style = new Style[2048];
    int numSprites;
    TextureFBO fbo;
    bool bRendered;
    bool m_isRendering;
   public const std::vector<TextureDraw> postRender = std::make_unique<std::vector<>>();
    AbstractStyle defaultStyle = TransparentStyle.instance;
    bool bCursorVisible = true;
    static const uint8_t UVCA_NONE = -1;
    static const uint8_t UVCA_CIRCLE = 1;
    static const uint8_t UVCA_NOCIRCLE = 2;
    uint8_t useVertColorsArray = -1;
    int texture2_color0;
    int texture2_color1;
    int texture2_color2;
    int texture2_color3;
    WallShaderTexRender wallShaderTexRender;
    Texture texture1_cutaway;
    int texture1_cutaway_x;
    int texture1_cutaway_y;
    int texture1_cutaway_w;
    int texture1_cutaway_h;

    protected GenericSpriteRenderState(int var1) {
      this.index = var1;

      for (int var2 = 0; var2 < this.sprite.length; var2++) {
         this.sprite[var2] = std::make_unique<TextureDraw>();
      }
   }

    void onRendered() {
      this.m_isRendering = false;
      this.bRendered = true;
   }

    void onRenderAcquired() {
      this.m_isRendering = true;
   }

    bool isRendering() {
      return this.m_isRendering;
   }

    void onReady() {
      this.bRendered = false;
   }

    bool isReady() {
      return !this.bRendered;
   }

    bool isRendered() {
      return this.bRendered;
   }

    void CheckSpriteSlots() {
      if (this.numSprites == this.sprite.length) {
         TextureDraw[] var1 = this.sprite;
         this.sprite = new TextureDraw[this.numSprites * 3 / 2 + 1];

         for (int var2 = this.numSprites; var2 < this.sprite.length; var2++) {
            this.sprite[var2] = std::make_unique<TextureDraw>();
         }

         System.arraycopy(var1, 0, this.sprite, 0, this.numSprites);
         Style[] var3 = this.style;
         this.style = new Style[this.numSprites * 3 / 2 + 1];
         System.arraycopy(var3, 0, this.style, 0, this.numSprites);
      }
   }

    static void clearSprites(List<TextureDraw> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         ((TextureDraw)var0.get(var1)).postRender();
      }

      var0.clear();
   }

    void clear() {
      clearSprites(this.postRender);
      this.numSprites = 0;
   }

    void glDepthMask(bool var1) {
      this.CheckSpriteSlots();
      TextureDraw.glDepthMask(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

   public void renderflipped(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10
   ) {
      this.render(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
      this.sprite[this.numSprites - 1].flipped = true;
   }

    void drawSkyBox(Shader var1, int var2, int var3, int var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.drawSkyBox(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void drawWater(Shader var1, int var2, int var3, bool var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      var1.startMainThread(this.sprite[this.numSprites], var2);
      TextureDraw.drawWater(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void drawPuddles(Shader var1, int var2, int var3, int var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.drawPuddles(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void drawParticles(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.drawParticles(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void glDisable(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glDisable(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void glEnable(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glEnable(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glStencilMask(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glStencilMask(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glClear(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glClear(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glClearColor(int var1, int var2, int var3, int var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glClearColor(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glStencilFunc(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glStencilFunc(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glStencilOp(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glStencilOp(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glColorMask(int var1, int var2, int var3, int var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glColorMask(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glAlphaFunc(int var1, float var2) {
      if (SpriteRenderer.GL_BLENDFUNC_ENABLED) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         TextureDraw.glAlphaFunc(this.sprite[this.numSprites], var1, var2);
         this.style[this.numSprites] = TransparentStyle.instance;
         this.numSprites++;
      }
   }

    void glBlendFunc(int var1, int var2) {
      if (SpriteRenderer.GL_BLENDFUNC_ENABLED) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         TextureDraw.glBlendFunc(this.sprite[this.numSprites], var1, var2);
         this.style[this.numSprites] = TransparentStyle.instance;
         this.numSprites++;
      }
   }

    void glBlendFuncSeparate(int var1, int var2, int var3, int var4) {
      if (SpriteRenderer.GL_BLENDFUNC_ENABLED) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         TextureDraw.glBlendFuncSeparate(this.sprite[this.numSprites], var1, var2, var3, var4);
         this.style[this.numSprites] = TransparentStyle.instance;
         this.numSprites++;
      }
   }

    void glBlendEquation(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glBlendEquation(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

   public void render(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      float var18,
      float var19,
      float var20,
      float var21,
      Consumer<TextureDraw> var22
   ) {
      this.render(
         var1,
         var2,
         var4,
         var6,
         var8,
         var10,
         var12,
         var14,
         var16,
         var18,
         var19,
         var20,
         var21,
         var18,
         var19,
         var20,
         var21,
         var18,
         var19,
         var20,
         var21,
         var18,
         var19,
         var20,
         var21,
         var22
      );
   }

   public void render(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      float var18,
      float var19,
      float var20,
      float var21,
      float var22,
      float var23,
      float var24,
      float var25,
      float var26,
      float var27,
      float var28,
      float var29,
      float var30,
      float var31,
      float var32,
      float var33,
      Consumer<TextureDraw> var34
   ) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].reset();
      TextureDraw.Create(
         this.sprite[this.numSprites],
         var1,
         (float)var2,
         (float)var4,
         (float)var6,
         (float)var8,
         (float)var10,
         (float)var12,
         (float)var14,
         (float)var16,
         var18,
         var19,
         var20,
         var21,
         var22,
         var23,
         var24,
         var25,
         var26,
         var27,
         var28,
         var29,
         var30,
         var31,
         var32,
         var33,
         var34
      );
      if (this.useVertColorsArray != -1) {
    TextureDraw var35 = this.sprite[this.numSprites];
         var35.useAttribArray = this.useVertColorsArray;
         var35.tex1_col0 = this.texture2_color0;
         var35.tex1_col1 = this.texture2_color1;
         var35.tex1_col2 = this.texture2_color2;
         var35.tex1_col3 = this.texture2_color3;
      }

      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void setUseVertColorsArray(uint8_t var1, int var2, int var3, int var4, int var5) {
      this.useVertColorsArray = var1;
      this.texture2_color0 = var2;
      this.texture2_color1 = var3;
      this.texture2_color2 = var4;
      this.texture2_color3 = var5;
   }

    void clearUseVertColorsArray() {
      this.useVertColorsArray = -1;
   }

   public void renderdebug(
      Texture var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19,
      float var20,
      float var21,
      float var22,
      float var23,
      float var24,
      float var25,
      Consumer<TextureDraw> var26
   ) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].reset();
      TextureDraw.Create(
         this.sprite[this.numSprites],
         var1,
         var2,
         var3,
         var4,
         var5,
         var6,
         var7,
         var8,
         var9,
         var10,
         var11,
         var12,
         var13,
         var14,
         var15,
         var16,
         var17,
         var18,
         var19,
         var20,
         var21,
         var22,
         var23,
         var24,
         var25,
         var26
      );
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void renderline(Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].reset();
      if (var2 <= var4 && var3 <= var5) {
         TextureDraw.Create(
            this.sprite[this.numSprites],
            var1,
            var2 + var10,
            var3 - var10,
            var4 + var10,
            var5 - var10,
            var4 - var10,
            var5 + var10,
            var2 - var10,
            var3 + var10,
            var6,
            var7,
            var8,
            var9
         );
      } else if (var2 >= var4 && var3 >= var5) {
         TextureDraw.Create(
            this.sprite[this.numSprites],
            var1,
            var2 + var10,
            var3 - var10,
            var2 - var10,
            var3 + var10,
            var4 - var10,
            var5 + var10,
            var4 + var10,
            var5 - var10,
            var6,
            var7,
            var8,
            var9
         );
      } else if (var2 >= var4 && var3 <= var5) {
         TextureDraw.Create(
            this.sprite[this.numSprites],
            var1,
            var4 - var10,
            var5 - var10,
            var2 - var10,
            var3 - var10,
            var2 + var10,
            var3 + var10,
            var4 + var10,
            var5 + var10,
            var6,
            var7,
            var8,
            var9
         );
      } else if (var2 <= var4 && var3 >= var5) {
         TextureDraw.Create(
            this.sprite[this.numSprites],
            var1,
            var2 - var10,
            var3 - var10,
            var2 + var10,
            var3 + var10,
            var4 + var10,
            var5 + var10,
            var4 - var10,
            var5 - var10,
            var6,
            var7,
            var8,
            var9
         );
      }

      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void renderline(Texture var1, int var2, int var3, int var4, int var5, float var6, float var7, float var8, float var9) {
      this.renderline(var1, var2, var3, var4, var5, var6, var7, var8, var9, 1);
   }

   public void render(
      Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10, int var11, int var12, int var13
   ) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].reset();
      TextureDraw.Create(this.sprite[this.numSprites], var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void render(Texture var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, Consumer<TextureDraw> var10) {
      if (var1 == nullptr || var1.isReady()) {
         if (var9 != 0.0F) {
            if (this.numSprites == this.sprite.length) {
               this.CheckSpriteSlots();
            }

            this.sprite[this.numSprites].reset();
    int var12 = Color.colorToABGR(var6, var7, var8, var9);
    float var15 = var2 + var4;
    float var16 = var3 + var5;
    TextureDraw var11;
            if (this.wallShaderTexRender == nullptr) {
               var11 = TextureDraw.Create(
                  this.sprite[this.numSprites], var1, var2, var3, var15, var3, var15, var16, var2, var16, var12, var12, var12, var12, var10
               );
            } else {
               var11 = TextureDraw.Create(
                  this.sprite[this.numSprites], var1, this.wallShaderTexRender, var2, var3, var15 - var2, var16 - var3, var6, var7, var8, var9, var10
               );
            }

            if (this.useVertColorsArray != -1) {
               var11.useAttribArray = this.useVertColorsArray;
               var11.tex1_col0 = this.texture2_color0;
               var11.tex1_col1 = this.texture2_color1;
               var11.tex1_col2 = this.texture2_color2;
               var11.tex1_col3 = this.texture2_color3;
            }

            if (this.texture1_cutaway != nullptr) {
               var11.tex1 = this.texture1_cutaway;
    float var17 = this.texture1_cutaway.xEnd - this.texture1_cutaway.xStart;
    float var18 = this.texture1_cutaway.yEnd - this.texture1_cutaway.yStart;
    float var19 = (float)this.texture1_cutaway_x / this.texture1_cutaway.getWidth();
    float var20 = (float)(this.texture1_cutaway_x + this.texture1_cutaway_w) / this.texture1_cutaway.getWidth();
    float var21 = (float)this.texture1_cutaway_y / this.texture1_cutaway.getHeight();
    float var22 = (float)(this.texture1_cutaway_y + this.texture1_cutaway_h) / this.texture1_cutaway.getHeight();
               var11.tex1_u0 = var11.tex1_u3 = this.texture1_cutaway.xStart + var19 * var17;
               var11.tex1_v0 = var11.tex1_v1 = this.texture1_cutaway.yStart + var21 * var18;
               var11.tex1_u1 = var11.tex1_u2 = this.texture1_cutaway.xStart + var20 * var17;
               var11.tex1_v2 = var11.tex1_v3 = this.texture1_cutaway.yStart + var22 * var18;
            }

            this.style[this.numSprites] = this.defaultStyle;
            this.numSprites++;
         }
      }
   }

    void renderRect(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
      if (var8 != 0.0F) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         this.sprite[this.numSprites].reset();
         TextureDraw.Create(this.sprite[this.numSprites], nullptr, var1, var2, var3, var4, var5, var6, var7, var8, nullptr);
         this.style[this.numSprites] = this.defaultStyle;
         this.numSprites++;
      }
   }

   public void renderPoly(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].reset();
      TextureDraw.Create(this.sprite[this.numSprites], nullptr, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

   public void renderPoly(
      Texture var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13
   ) {
      if (var1 == nullptr || var1.isReady()) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         this.sprite[this.numSprites].reset();
         TextureDraw.Create(this.sprite[this.numSprites], var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
         if (var1 != nullptr) {
    float var14 = var1.getXEnd();
    float var15 = var1.getXStart();
    float var16 = var1.getYEnd();
    float var17 = var1.getYStart();
    TextureDraw var18 = this.sprite[this.numSprites];
            var18.u0 = var15;
            var18.u1 = var14;
            var18.u2 = var14;
            var18.u3 = var15;
            var18.v0 = var17;
            var18.v1 = var17;
            var18.v2 = var16;
            var18.v3 = var16;
         }

         this.style[this.numSprites] = this.defaultStyle;
         this.numSprites++;
      }
   }

   public void renderPoly(
      Texture var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      float var18,
      float var19,
      float var20,
      float var21
   ) {
      if (var1 == nullptr || var1.isReady()) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         this.sprite[this.numSprites].reset();
         TextureDraw.Create(this.sprite[this.numSprites], var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
         if (var1 != nullptr) {
    TextureDraw var22 = this.sprite[this.numSprites];
            var22.u0 = var14;
            var22.u1 = var16;
            var22.u2 = var18;
            var22.u3 = var20;
            var22.v0 = var15;
            var22.v1 = var17;
            var22.v2 = var19;
            var22.v3 = var21;
         }

         this.style[this.numSprites] = this.defaultStyle;
         this.numSprites++;
      }
   }

   public void render(
      Texture var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      float var13,
      float var14,
      float var15,
      float var16,
      float var17,
      Consumer<TextureDraw> var18
   ) {
      if (var9 != 0.0F) {
         if (this.numSprites == this.sprite.length) {
            this.CheckSpriteSlots();
         }

         this.sprite[this.numSprites].reset();
         TextureDraw.Create(
            this.sprite[this.numSprites], var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18
         );
         this.style[this.numSprites] = this.defaultStyle;
         this.numSprites++;
      }
   }

    void glBuffer(int var1, int var2) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glBuffer(this.sprite[this.numSprites], var1, var2);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glDoStartFrame(int var1, int var2, float var3, int var4) {
      this.glDoStartFrame(var1, var2, var3, var4, false);
   }

    void glDoStartFrame(int var1, int var2, float var3, int var4, bool var5) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glDoStartFrame(this.sprite[this.numSprites], var1, var2, var3, var4, var5);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glDoStartFrameFx(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glDoStartFrameFx(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glIgnoreStyles(bool var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glIgnoreStyles(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glDoEndFrame() {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glDoEndFrame(this.sprite[this.numSprites]);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glDoEndFrameFx(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glDoEndFrameFx(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void doCoreIntParam(int var1, float var2) {
      this.CheckSpriteSlots();
      TextureDraw.doCoreIntParam(this.sprite[this.numSprites], var1, var2);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glTexParameteri(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glTexParameteri(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void setCutawayTexture(Texture var1, int var2, int var3, int var4, int var5) {
      this.texture1_cutaway = var1;
      this.texture1_cutaway_x = var2;
      this.texture1_cutaway_y = var3;
      this.texture1_cutaway_w = var4;
      this.texture1_cutaway_h = var5;
   }

    void clearCutawayTexture() {
      this.texture1_cutaway = nullptr;
   }

    void setExtraWallShaderParams(WallShaderTexRender var1) {
      this.wallShaderTexRender = var1;
   }

    void ShaderUpdate1i(int var1, int var2, int var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.ShaderUpdate1i(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void ShaderUpdate1f(int var1, int var2, float var3) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.ShaderUpdate1f(this.sprite[this.numSprites], var1, var2, var3);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void ShaderUpdate2f(int var1, int var2, float var3, float var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.ShaderUpdate2f(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void ShaderUpdate3f(int var1, int var2, float var3, float var4, float var5) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.ShaderUpdate3f(this.sprite[this.numSprites], var1, var2, var3, var4, var5);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void ShaderUpdate4f(int var1, int var2, float var3, float var4, float var5, float var6) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.ShaderUpdate4f(this.sprite[this.numSprites], var1, var2, var3, var4, var5, var6);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glLoadIdentity() {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glLoadIdentity(this.sprite[this.numSprites]);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glGenerateMipMaps(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glGenerateMipMaps(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void glBind(int var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glBind(this.sprite[this.numSprites], var1);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void glViewport(int var1, int var2, int var3, int var4) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.glViewport(this.sprite[this.numSprites], var1, var2, var3, var4);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
   }

    void drawModel(ModelSlot var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.drawModel(this.sprite[this.numSprites], var1);

      assert this.sprite[this.numSprites].drawer != nullptr;

    std::vector var2 = this.postRender;
      var2.push_back(this.sprite[this.numSprites]);
      this.style[this.numSprites] = this.defaultStyle;
      this.numSprites++;
      var1.renderRefCount++;
   }

    void drawGeneric(GenericDrawer var1) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      this.sprite[this.numSprites].type = Type.DrawModel;
      this.sprite[this.numSprites].drawer = var1;
      this.style[this.numSprites] = this.defaultStyle;
    std::vector var2 = this.postRender;
      var2.push_back(this.sprite[this.numSprites]);
      this.numSprites++;
   }

    void StartShader(int var1, int var2) {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.StartShader(this.sprite[this.numSprites], var1);
      if (var1 != 0 && Shader.ShaderMap.containsKey(var1)) {
         ((Shader)Shader.ShaderMap.get(var1)).startMainThread(this.sprite[this.numSprites], var2);
    std::vector var3 = this.postRender;
         var3.push_back(this.sprite[this.numSprites]);
      }

      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }

    void EndShader() {
      if (this.numSprites == this.sprite.length) {
         this.CheckSpriteSlots();
      }

      TextureDraw.StartShader(this.sprite[this.numSprites], 0);
      this.style[this.numSprites] = TransparentStyle.instance;
      this.numSprites++;
   }
}
} // namespace sprite
} // namespace core
} // namespace zombie
