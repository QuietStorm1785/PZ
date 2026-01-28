#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/Mouse.h"

namespace zombie {
namespace ui {


class UIElement {
   // ImGui-based rendering entry point
   virtual void ImGuiRender();
public:
    static const Color tempcol = std::make_shared<Color>(0, 0, 0, 0);
   static const std::vector<UIElement> toAdd = new std::vector<>(0);
    static Texture white;
    static int StencilLevel = 0;
    bool capture = false;
    bool IgnoreLossControl = false;
    std::string clickedValue = nullptr;
   public const std::vector<UIElement> Controls = std::make_unique<std::vector<>>();
    bool defaultDraw = true;
    bool followGameWorld = false;
    int renderThisPlayerOnly = -1;
    float height = 256.0F;
    UIElement Parent = nullptr;
    bool visible = true;
    float width = 256.0F;
    double x = 0.0;
    double y = 0.0;
    KahluaTable table;
    bool alwaysBack;
    bool bScrollChildren = false;
    bool bScrollWithParent = true;
    bool bRenderClippedChildren = true;
    bool anchorTop = true;
    bool anchorLeft = true;
    bool anchorRight = false;
    bool anchorBottom = false;
    int playerContext = -1;
    bool alwaysOnTop = false;
    int maxDrawHeight = -1;
    double yScroll = 0.0;
    double xScroll = 0.0;
    int scrollHeight = 0;
    double lastheight = -1.0;
    double lastwidth = -1.0;
    bool bResizeDirty = false;
    bool enabled = true;
   private const std::vector<UIElement> toTop = new std::vector<>(0);
    bool bConsumeMouseEvents = true;
    long leftDownTime = 0L;
    bool clicked;
    double clickX;
    double clickY;
    std::string uiname = "";
    bool bWantKeyEvents = false;
    bool bForceCursorVisible = false;

    public UIElement() {
   }

    public UIElement(KahluaTable var1) {
      this.table = var1;
   }

    double getMaxDrawHeight() {
      return BoxedStaticValues.toDouble(this.maxDrawHeight);
   }

    void setMaxDrawHeight(double var1) {
      this.maxDrawHeight = (int)var1;
   }

    void clearMaxDrawHeight() {
      this.maxDrawHeight = -1;
   }

    double getXScroll() {
      return this.xScroll;
   }

    void setXScroll(double var1) {
      this.xScroll = var1;
   }

    double getYScroll() {
      return this.yScroll;
   }

    void setYScroll(double var1) {
      this.yScroll = var1;
   }

    void setAlwaysOnTop(bool var1) {
      this.alwaysOnTop = var1;
   }

    void backMost() {
      this.alwaysBack = true;
   }

    void AddChild(UIElement var1) {
      this.getControls().push_back(var1);
      var1.setParent(this);
   }

    void RemoveChild(UIElement var1) {
      this.getControls().remove(var1);
      var1.setParent(nullptr);
   }

    double getScrollHeight() {
      return BoxedStaticValues.toDouble(this.scrollHeight);
   }

    void setScrollHeight(double var1) {
      this.scrollHeight = (int)var1;
   }

    bool isConsumeMouseEvents() {
      return this.bConsumeMouseEvents;
   }

    void setConsumeMouseEvents(bool var1) {
      this.bConsumeMouseEvents = var1;
   }

    void ClearChildren() {
      this.getControls().clear();
   }

    void ButtonClicked(const std::string& var1) {
      this.setClickedValue(var1);
   }

    void DrawText(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13, double var15) {
      TextManager.instance
         .DrawString(var1, var3 + this.getAbsoluteX() + this.xScroll, var5 + this.getAbsoluteY() + this.yScroll, (float)var7, var2, var9, var11, var13, var15);
   }

    void DrawText(const std::string& var1, double var2, double var4, double var6, double var8, double var10, double var12) {
      TextManager.instance.DrawString(var2 + this.getAbsoluteX() + this.xScroll, var4 + this.getAbsoluteY() + this.yScroll, var1, var6, var8, var10, var12);
   }

    void DrawText(const std::string& var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      TextManager.instance.DrawString(var2 + this.getAbsoluteX() + this.xScroll, var4 + this.getAbsoluteY() + this.yScroll, var1, var10, var12, var14, var16);
   }

    void DrawText(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (var2 != nullptr) {
    int var15 = (int)(var5 + this.getAbsoluteY() + this.yScroll);
         if (var15 + 100 >= 0 && var15 <= 4096) {
            TextManager.instance
               .DrawString(var1, var3 + this.getAbsoluteX() + this.xScroll, var5 + this.getAbsoluteY() + this.yScroll, var2, var7, var9, var11, var13);
         }
      }
   }

    void DrawTextUntrimmed(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (var2 != nullptr) {
         TextManager.instance
            .DrawStringUntrimmed(var1, var3 + this.getAbsoluteX() + this.xScroll, var5 + this.getAbsoluteY() + this.yScroll, var2, var7, var9, var11, var13);
      }
   }

    void DrawTextCentre(const std::string& var1, double var2, double var4, double var6, double var8, double var10, double var12) {
      TextManager.instance
         .DrawStringCentre(var2 + this.getAbsoluteX() + this.xScroll, var4 + this.getAbsoluteY() + this.yScroll, var1, var6, var8, var10, var12);
   }

    void DrawTextCentre(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      TextManager.instance
         .DrawStringCentre(var1, var3 + this.getAbsoluteX() + this.xScroll, var5 + this.getAbsoluteY() + this.yScroll, var2, var7, var9, var11, var13);
   }

    void DrawTextRight(const std::string& var1, double var2, double var4, double var6, double var8, double var10, double var12) {
      TextManager.instance
         .DrawStringRight(var2 + this.getAbsoluteX() + this.xScroll, var4 + this.getAbsoluteY() + this.yScroll, var1, var6, var8, var10, var12);
   }

    void DrawTextRight(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      TextManager.instance
         .DrawStringRight(var1, var3 + this.getAbsoluteX() + this.xScroll, var5 + this.getAbsoluteY() + this.yScroll, var2, var7, var9, var11, var13);
   }

    void DrawTextureAngle(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14) {
      if (this.isVisible()) {
    float var16 = var1.getWidth() / 2;
    float var17 = var1.getHeight() / 2;
    double var18 = Math.toRadians(180.0 + var6);
    double var20 = Math.cos(var18) * var16;
    double var22 = Math.sin(var18) * var16;
    double var24 = Math.cos(var18) * var17;
    double var26 = Math.sin(var18) * var17;
    double var28 = var20 - var26;
    double var30 = var24 + var22;
    double var32 = -var20 - var26;
    double var34 = var24 - var22;
    double var36 = -var20 + var26;
    double var38 = -var24 - var22;
    double var40 = var20 + var26;
    double var42 = -var24 + var22;
         var28 += this.getAbsoluteX() + var2;
         var30 += this.getAbsoluteY() + var4;
         var32 += this.getAbsoluteX() + var2;
         var34 += this.getAbsoluteY() + var4;
         var36 += this.getAbsoluteX() + var2;
         var38 += this.getAbsoluteY() + var4;
         var40 += this.getAbsoluteX() + var2;
         var42 += this.getAbsoluteY() + var4;
         SpriteRenderer.instance
            .render(
               var1,
               var28,
               var30,
               var32,
               var34,
               var36,
               var38,
               var40,
               var42,
               (float)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               (float)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               (float)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               (float)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               nullptr
            );
      }
   }

    void DrawTextureAngle(Texture var1, double var2, double var4, double var6) {
      this.DrawTextureAngle(var1, var2, var4, var6, 1.0, 1.0, 1.0, 1.0);
   }

   public void DrawTexture(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      double var18,
      double var20,
      double var22,
      double var24
   ) {
      SpriteRenderer.instance
         .render(
            var1,
            var2,
            var4,
            var6,
            var8,
            var10,
            var12,
            var14,
            var16,
            (float)var18,
            (float)var20,
            (float)var22,
            (float)var24,
            (float)var18,
            (float)var20,
            (float)var22,
            (float)var24,
            (float)var18,
            (float)var20,
            (float)var22,
            (float)var24,
            (float)var18,
            (float)var20,
            (float)var22,
            (float)var24,
            nullptr
         );
   }

    void DrawTexture(Texture var1, double var2, double var4, double var6) {
      if (this.isVisible()) {
    double var8 = var2 + this.getAbsoluteX();
    double var10 = var4 + this.getAbsoluteY();
         var8 += var1.offsetX;
         var10 += var1.offsetY;
    int var12 = (int)(var10 + this.yScroll);
         if (var12 + var1.getHeight() >= 0 && var12 <= 4096) {
            SpriteRenderer.instance
               .renderi(var1, (int)(var8 + this.xScroll), (int)(var10 + this.yScroll), var1.getWidth(), var1.getHeight(), 1.0F, 1.0F, 1.0F, (float)var6, nullptr);
         }
      }
   }

    void DrawTextureCol(Texture var1, double var2, double var4, Color var6) {
      if (this.isVisible()) {
    double var7 = var2 + this.getAbsoluteX();
    double var9 = var4 + this.getAbsoluteY();
    int var11 = 0;
    int var12 = 0;
         if (var1 != nullptr) {
            var7 += var1.offsetX;
            var9 += var1.offsetY;
            var11 = var1.getWidth();
            var12 = var1.getHeight();
         }

    int var13 = (int)(var9 + this.yScroll);
         if (var13 + var12 >= 0 && var13 <= 4096) {
            SpriteRenderer.instance.renderi(var1, (int)(var7 + this.xScroll), (int)(var9 + this.yScroll), var11, var12, var6.r, var6.g, var6.b, var6.a, nullptr);
         }
      }
   }

    void DrawTextureScaled(Texture var1, double var2, double var4, double var6, double var8, double var10) {
      if (this.isVisible()) {
    double var12 = var2 + this.getAbsoluteX();
    double var14 = var4 + this.getAbsoluteY();
         SpriteRenderer.instance
            .renderi(var1, (int)(var12 + this.xScroll), (int)(var14 + this.yScroll), (int)var6, (int)var8, 1.0F, 1.0F, 1.0F, (float)var10, nullptr);
      }
   }

    void DrawTextureScaledUniform(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14) {
      if (this.isVisible() && var1 != nullptr) {
    double var16 = var2 + this.getAbsoluteX();
    double var18 = var4 + this.getAbsoluteY();
         var16 += var1.offsetX * var6;
         var18 += var1.offsetY * var6;
         SpriteRenderer.instance
            .renderi(
               var1,
               (int)(var16 + this.xScroll),
               (int)(var18 + this.yScroll),
               (int)(var1.getWidth() * var6),
               (int)(var1.getHeight() * var6),
               (float)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               nullptr
            );
      }
   }

    void DrawTextureScaledAspect(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (this.isVisible() && var1 != nullptr) {
    double var18 = var2 + this.getAbsoluteX();
    double var20 = var4 + this.getAbsoluteY();
         if (var1.getWidth() > 0 && var1.getHeight() > 0 && var6 > 0.0 && var8 > 0.0) {
    double var22 = Math.min(var6 / var1.getWidthOrig(), var8 / var1.getHeightOrig());
    double var24 = var6;
    double var26 = var8;
            var6 = var1.getWidth() * var22;
            var8 = var1.getHeight() * var22;
            var18 -= (var6 - var24) / 2.0;
            var20 -= (var8 - var26) / 2.0;
         }

         SpriteRenderer.instance
            .renderi(
               var1,
               (int)(var18 + this.xScroll),
               (int)(var20 + this.yScroll),
               (int)var6,
               (int)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               (float)var16,
               nullptr
            );
      }
   }

   public void DrawTextureScaledAspect2(
      Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16
   ) {
      if (this.isVisible() && var1 != nullptr) {
    double var18 = var2 + this.getAbsoluteX();
    double var20 = var4 + this.getAbsoluteY();
         if (var1.getWidth() > 0 && var1.getHeight() > 0 && var6 > 0.0 && var8 > 0.0) {
    double var22 = Math.min(var6 / var1.getWidth(), var8 / var1.getHeight());
    double var24 = var6;
    double var26 = var8;
            var6 = var1.getWidth() * var22;
            var8 = var1.getHeight() * var22;
            var18 -= (var6 - var24) / 2.0;
            var20 -= (var8 - var26) / 2.0;
         }

         SpriteRenderer.instance
            .render(
               var1,
               (int)(var18 + this.xScroll),
               (int)(var20 + this.yScroll),
               (int)var6,
               (int)var8,
               (float)var10,
               (float)var12,
               (float)var14,
               (float)var16,
               nullptr
            );
      }
   }

    void DrawTextureScaledCol(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (var1 != nullptr) {
    bool var18 = false;
      }

      if (this.isVisible()) {
    double var23 = var2 + this.getAbsoluteX();
    double var20 = var4 + this.getAbsoluteY();
    int var22 = (int)(var20 + this.yScroll);
         if (!(var22 + var8 < 0.0) && var22 <= 4096) {
            SpriteRenderer.instance
               .renderi(
                  var1,
                  (int)(var23 + this.xScroll),
                  (int)(var20 + this.yScroll),
                  (int)var6,
                  (int)var8,
                  (float)var10,
                  (float)var12,
                  (float)var14,
                  (float)var16,
                  nullptr
               );
         }
      }
   }

    void DrawTextureScaledCol(Texture var1, double var2, double var4, double var6, double var8, Color var10) {
      if (var1 != nullptr) {
    bool var11 = false;
      }

      if (this.isVisible()) {
    double var15 = var2 + this.getAbsoluteX();
    double var13 = var4 + this.getAbsoluteY();
         SpriteRenderer.instance
            .render(var1, (int)(var15 + this.xScroll), (int)(var13 + this.yScroll), (int)var6, (int)var8, var10.r, var10.g, var10.b, var10.a, nullptr);
      }
   }

    void DrawTextureScaledColor(Texture var1, double var2, double var3, double var4, double var5, double var6, double var7, double var8, double var9) {
      this.DrawTextureScaledCol(var1, var2, var3, var4, var5, var6, var7, var8, var9);
   }

    void DrawTextureColor(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12) {
      tempcol.r = (float)var6;
      tempcol.g = (float)var8;
      tempcol.b = (float)var10;
      tempcol.a = (float)var12;
      this.DrawTextureCol(var1, var2, var4, tempcol);
   }

   public void DrawSubTextureRGBA(
      Texture var1,
      double var2,
      double var4,
      double var6,
      double var8,
      double var10,
      double var12,
      double var14,
      double var16,
      double var18,
      double var20,
      double var22,
      double var24
   ) {
      if (var1 != nullptr && this.isVisible() && !(var6 <= 0.0) && !(var8 <= 0.0) && !(var14 <= 0.0) && !(var16 <= 0.0)) {
    double var26 = var10 + this.getAbsoluteX() + this.xScroll;
    double var28 = var12 + this.getAbsoluteY() + this.yScroll;
         var26 += var1.offsetX;
         var28 += var1.offsetY;
         if (!(var28 + var16 < 0.0) && !(var28 > 4096.0)) {
    float var30 = PZMath.clamp((float)var2, 0.0F, var1.getWidth());
    float var31 = PZMath.clamp((float)var4, 0.0F, var1.getHeight());
    float var32 = PZMath.clamp((float)(var30 + var6), 0.0F, var1.getWidth()) - var30;
    float var33 = PZMath.clamp((float)(var31 + var8), 0.0F, var1.getHeight()) - var31;
    float var34 = var30 / var1.getWidth();
    float var35 = var31 / var1.getHeight();
    float var36 = (var30 + var32) / var1.getWidth();
    float var37 = (var31 + var33) / var1.getHeight();
    float var38 = var1.getXEnd() - var1.getXStart();
    float var39 = var1.getYEnd() - var1.getYStart();
            var34 = var1.getXStart() + var34 * var38;
            var36 = var1.getXStart() + var36 * var38;
            var35 = var1.getYStart() + var35 * var39;
            var37 = var1.getYStart() + var37 * var39;
            SpriteRenderer.instance
               .render(
                  var1,
                  (float)var26,
                  (float)var28,
                  (float)var14,
                  (float)var16,
                  (float)var18,
                  (float)var20,
                  (float)var22,
                  (float)var24,
                  var34,
                  var35,
                  var36,
                  var35,
                  var36,
                  var37,
                  var34,
                  var37
               );
         }
      }
   }

    void DrawTextureTiled(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (var1 != nullptr && this.isVisible() && !(var6 <= 0.0) && !(var8 <= 0.0)) {
         for (double var18 = var4; var18 < var4 + var8; var18 += var1.getHeight()) {
            for (double var20 = var2; var20 < var2 + var6; var20 += var1.getWidth()) {
    double var22 = var1.getWidth();
    double var24 = var1.getHeight();
               if (var20 + var22 > var2 + var6) {
                  var22 = var2 + var6 - var20;
               }

               if (var18 + var1.getHeight() > var4 + var8) {
                  var24 = var4 + var8 - var18;
               }

               this.DrawSubTextureRGBA(var1, 0.0, 0.0, var22, var24, var20, var18, var22, var24, var10, var12, var14, var16);
            }
         }
      }
   }

    void DrawTextureTiledX(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (var1 != nullptr && this.isVisible() && !(var6 <= 0.0) && !(var8 <= 0.0)) {
         for (double var18 = var2; var18 < var2 + var6; var18 += var1.getWidth()) {
    double var20 = var1.getWidth();
    double var22 = var1.getHeight();
            if (var18 + var20 > var2 + var6) {
               var20 = var2 + var6 - var18;
            }

            this.DrawSubTextureRGBA(var1, 0.0, 0.0, var20, var22, var18, var4, var20, var22, var10, var12, var14, var16);
         }
      }
   }

    void DrawTextureTiledY(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (var1 != nullptr && this.isVisible() && !(var6 <= 0.0) && !(var8 <= 0.0)) {
         for (double var18 = var4; var18 < var4 + var8; var18 += var1.getHeight()) {
    double var20 = var1.getWidth();
    double var22 = var1.getHeight();
            if (var18 + var1.getHeight() > var4 + var8) {
               var22 = var4 + var8 - var18;
            }

            this.DrawSubTextureRGBA(var1, 0.0, 0.0, var20, var22, var2, var18, var20, var22, var10, var12, var14, var16);
         }
      }
   }

    void DrawTextureIgnoreOffset(Texture var1, double var2, double var4, int var6, int var7, Color var8) {
      if (this.isVisible()) {
    double var9 = var2 + this.getAbsoluteX();
    double var11 = var4 + this.getAbsoluteY();
         SpriteRenderer.instance.render(var1, (int)(var9 + this.xScroll), (int)(var11 + this.yScroll), var6, var7, var8.r, var8.g, var8.b, var8.a, nullptr);
      }
   }

    void DrawTexture_FlippedX(Texture var1, double var2, double var4, int var6, int var7, Color var8) {
      if (this.isVisible()) {
    double var9 = var2 + this.getAbsoluteX();
    double var11 = var4 + this.getAbsoluteY();
         SpriteRenderer.instance
            .renderflipped(var1, (float)(var9 + this.xScroll), (float)(var11 + this.yScroll), var6, var7, var8.r, var8.g, var8.b, var8.a, nullptr);
      }
   }

    void DrawTexture_FlippedXIgnoreOffset(Texture var1, double var2, double var4, int var6, int var7, Color var8) {
      if (this.isVisible()) {
    double var9 = var2 + this.getAbsoluteX();
    double var11 = var4 + this.getAbsoluteY();
         SpriteRenderer.instance
            .renderflipped(var1, (float)(var9 + this.xScroll), (float)(var11 + this.yScroll), var6, var7, var8.r, var8.g, var8.b, var8.a, nullptr);
      }
   }

   public void DrawUVSliceTexture(
      Texture var1, double var2, double var4, double var6, double var8, Color var10, double var11, double var13, double var15, double var17
   ) {
      if (this.isVisible()) {
    double var19 = var2 + this.getAbsoluteX();
    double var21 = var4 + this.getAbsoluteY();
         var19 += var1.offsetX;
         var21 += var1.offsetY;
         Texture.lr = var10.r;
         Texture.lg = var10.g;
         Texture.lb = var10.b;
         Texture.la = var10.a;
    double var23 = var1.getXStart();
    double var25 = var1.getYStart();
    double var27 = var1.getXEnd();
    double var29 = var1.getYEnd();
    double var31 = var27 - var23;
    double var33 = var29 - var25;
    double var35 = var15 - var11;
    double var37 = var17 - var13;
    double var39 = var35 / 1.0;
    double var41 = var37 / 1.0;
         var23 += var11 * var31;
         var25 += var13 * var33;
         var27 -= (1.0 - var15) * var31;
         var29 -= (1.0 - var17) * var33;
         var23 = (int)(var23 * 1000.0) / 1000.0F;
         var27 = (int)(var27 * 1000.0) / 1000.0F;
         var25 = (int)(var25 * 1000.0) / 1000.0F;
         var29 = (int)(var29 * 1000.0) / 1000.0F;
    double var43 = var19 + var6;
    double var45 = var21 + var8;
         var19 += var11 * var6;
         var21 += var13 * var8;
         var43 -= (1.0 - var15) * var6;
         var45 -= (1.0 - var17) * var8;
         SpriteRenderer.instance
            .render(
               var1,
               (float)var19 + this.getXScroll().intValue(),
               (float)var21 + this.getYScroll().intValue(),
               (float)(var43 - var19),
               (float)(var45 - var21),
               var10.r,
               var10.g,
               var10.b,
               var10.a,
               (float)var23,
               (float)var25,
               (float)var27,
               (float)var25,
               (float)var27,
               (float)var29,
               (float)var23,
               (float)var29
            );
      }
   }

    bool getScrollChildren() {
      return this.bScrollChildren ? bool.TRUE : bool.FALSE;
   }

    void setScrollChildren(bool var1) {
      this.bScrollChildren = var1;
   }

    bool getScrollWithParent() {
      return this.bScrollWithParent ? bool.TRUE : bool.FALSE;
   }

    void setScrollWithParent(bool var1) {
      this.bScrollWithParent = var1;
   }

    void setRenderClippedChildren(bool var1) {
      this.bRenderClippedChildren = var1;
   }

    double getAbsoluteX() {
      if (this.getParent() != nullptr) {
         return this.getParent().getScrollChildren() && this.getScrollWithParent()
            ? BoxedStaticValues.toDouble(this.getParent().getAbsoluteX() + this.getX().intValue() + this.getParent().getXScroll().intValue())
            : BoxedStaticValues.toDouble(this.getParent().getAbsoluteX() + this.getX().intValue());
      } else {
         return BoxedStaticValues.toDouble(this.getX().intValue());
      }
   }

    double getAbsoluteY() {
      if (this.getParent() != nullptr) {
         return this.getParent().getScrollChildren() && this.getScrollWithParent()
            ? BoxedStaticValues.toDouble(this.getParent().getAbsoluteY() + this.getY().intValue() + this.getParent().getYScroll().intValue())
            : BoxedStaticValues.toDouble(this.getParent().getAbsoluteY() + this.getY().intValue());
      } else {
         return BoxedStaticValues.toDouble(this.getY().intValue());
      }
   }

    std::string getClickedValue() {
      return this.clickedValue;
   }

    void setClickedValue(const std::string& var1) {
      this.clickedValue = var1;
   }

    void bringToTop() {
      UIManager.pushToTop(this);
      if (this.Parent != nullptr) {
         this.Parent.addBringToTop(this);
      }
   }

    void onRightMouseUpOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onRightMouseUpOutside") != nullptr) {
         LuaManager.caller
            .protectedCallVoid(
               UIManager.getDefaultThread(),
               this.getTable().rawget("onRightMouseUpOutside"),
               this.table,
               BoxedStaticValues.toDouble(var1 - this.xScroll),
               BoxedStaticValues.toDouble(var3 - this.yScroll)
            );
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = this.getControls().get(var5);
         var6.onRightMouseUpOutside(var1 - var6.getXScrolled(this).intValue(), var3 - var6.getYScrolled(this).intValue());
      }
   }

    void onRightMouseDownOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onRightMouseDownOutside") != nullptr) {
         LuaManager.caller
            .protectedCallVoid(
               UIManager.getDefaultThread(),
               this.getTable().rawget("onRightMouseDownOutside"),
               this.table,
               BoxedStaticValues.toDouble(var1 - this.xScroll),
               BoxedStaticValues.toDouble(var3 - this.yScroll)
            );
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = this.getControls().get(var5);
         var6.onRightMouseDownOutside(var1 - var6.getXScrolled(this).intValue(), var3 - var6.getYScrolled(this).intValue());
      }
   }

    void onMouseUpOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseUpOutside") != nullptr) {
         LuaManager.caller
            .protectedCallVoid(
               UIManager.getDefaultThread(),
               this.getTable().rawget("onMouseUpOutside"),
               this.table,
               BoxedStaticValues.toDouble(var1 - this.xScroll),
               BoxedStaticValues.toDouble(var3 - this.yScroll)
            );
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = this.getControls().get(var5);
         var6.onMouseUpOutside(var1 - var6.getXScrolled(this).intValue(), var3 - var6.getYScrolled(this).intValue());
      }
   }

    void onMouseDownOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseDownOutside") != nullptr) {
         LuaManager.caller
            .protectedCallVoid(
               UIManager.getDefaultThread(),
               this.getTable().rawget("onMouseDownOutside"),
               this.table,
               BoxedStaticValues.toDouble(var1 - this.xScroll),
               BoxedStaticValues.toDouble(var3 - this.yScroll)
            );
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = this.getControls().get(var5);
         var6.onMouseDownOutside(var1 - var6.getX().intValue(), var3 - var6.getY().intValue());
      }
   }

    bool onMouseDown(double var1, double var3) {
      if (this.clicked
         && UIManager.isDoubleClick((int)this.clickX, (int)this.clickY, (int)var1, (int)var3, this.leftDownTime)
         && this.getTable() != nullptr
         && this.getTable().rawget("onMouseDoubleClick") != nullptr) {
         this.clicked = false;
         return this.onMouseDoubleClick(var1, var3) ? bool.TRUE : bool.FALSE;
      } else {
         this.clicked = true;
         this.clickX = var1;
         this.clickY = var3;
         this.leftDownTime = System.currentTimeMillis();
         if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= var3) {
            return bool.FALSE;
         } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= var3) {
            return bool.FALSE;
         } else if (!this.visible) {
            return bool.FALSE;
         } else {
            if (this.getTable() != nullptr && this.getTable().rawget("onFocus") != nullptr) {
               LuaManager.caller
                  .protectedCallVoid(
                     UIManager.getDefaultThread(),
                     this.getTable().rawget("onFocus"),
                     this.table,
                     BoxedStaticValues.toDouble(var1 - this.xScroll),
                     BoxedStaticValues.toDouble(var3 - this.yScroll)
                  );
            }

    bool var5 = false;

            for (int var6 = this.getControls().size() - 1; var6 >= 0; var6--) {
    UIElement var7 = this.getControls().get(var6);
               if (!var5
                  && (
                     var1 > var7.getXScrolled(this)
                           && var3 > var7.getYScrolled(this)
                           && var1 < var7.getXScrolled(this) + var7.getWidth()
                           && var3 < var7.getYScrolled(this) + var7.getHeight()
                        || var7.isCapture()
                  )) {
                  if (var7.onMouseDown(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue())) {
                     var5 = true;
                  }
               } else if (var7.getTable() != nullptr && var7.getTable().rawget("onMouseDownOutside") != nullptr) {
                  LuaManager.caller
                     .protectedCallVoid(
                        UIManager.getDefaultThread(),
                        var7.getTable().rawget("onMouseDownOutside"),
                        var7.getTable(),
                        BoxedStaticValues.toDouble(var1 - this.xScroll),
                        BoxedStaticValues.toDouble(var3 - this.yScroll)
                     );
               }
            }

            if (this.getTable() != nullptr) {
               if (var5) {
                  if (this.getTable().rawget("onMouseDownOutside") != nullptr) {
                     bool var8 = LuaManager.caller
                        .protectedCallBoolean(
                           UIManager.getDefaultThread(),
                           this.getTable().rawget("onMouseDownOutside"),
                           this.table,
                           BoxedStaticValues.toDouble(var1 - this.xScroll),
                           BoxedStaticValues.toDouble(var3 - this.yScroll)
                        );
                     if (var8 == nullptr) {
                        return bool.TRUE;
                     }

                     if (var8 == bool.TRUE) {
                        return bool.TRUE;
                     }
                  }
               } else if (this.getTable().rawget("onMouseDown") != nullptr) {
                  bool var9 = LuaManager.caller
                     .protectedCallBoolean(
                        UIManager.getDefaultThread(),
                        this.getTable().rawget("onMouseDown"),
                        this.table,
                        BoxedStaticValues.toDouble(var1 - this.xScroll),
                        BoxedStaticValues.toDouble(var3 - this.yScroll)
                     );
                  if (var9 == nullptr) {
                     return bool.TRUE;
                  }

                  if (var9 == bool.TRUE) {
                     return bool.TRUE;
                  }
               }
            }

    return var5;
         }
      }
   }

    bool onMouseDoubleClick(double var1, double var3) {
      if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= this.y) {
         return bool.FALSE;
      } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= this.y) {
         return bool.FALSE;
      } else if (!this.visible) {
         return bool.FALSE;
      } else {
         if (this.getTable().rawget("onMouseDoubleClick") != nullptr) {
            bool var5 = LuaManager.caller
               .protectedCallBoolean(
                  UIManager.getDefaultThread(),
                  this.getTable().rawget("onMouseDoubleClick"),
                  this.table,
                  BoxedStaticValues.toDouble(var1 - this.xScroll),
                  BoxedStaticValues.toDouble(var3 - this.yScroll)
               );
            if (var5 == nullptr) {
               return bool.TRUE;
            }

            if (var5 == bool.TRUE) {
               return bool.TRUE;
            }
         }

         return bool.TRUE;
      }
   }

    bool onMouseWheel(double var1) {
    int var3 = Mouse.getXA();
    int var4 = Mouse.getYA();
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseWheel") != nullptr) {
         bool var5 = LuaManager.caller
            .protectedCallBoolean(UIManager.getDefaultThread(), this.getTable().rawget("onMouseWheel"), this.table, BoxedStaticValues.toDouble(var1));
         if (var5 == bool.TRUE) {
            return bool.TRUE;
         }
      }

      for (int var7 = this.getControls().size() - 1; var7 >= 0; var7--) {
    UIElement var6 = this.getControls().get(var7);
         if (var6.isVisible()
            && (
               var3 >= var6.getAbsoluteX()
                     && var4 >= var6.getAbsoluteY()
                     && var3 < var6.getAbsoluteX() + var6.getWidth()
                     && var4 < var6.getAbsoluteY() + var6.getHeight()
                  || var6.isCapture()
            )
            && var6.onMouseWheel(var1)) {
            return this.bConsumeMouseEvents ? bool.TRUE : bool.FALSE;
         }
      }

      return bool.FALSE;
   }

    bool onMouseMove(double var1, double var3) {
    int var5 = Mouse.getXA();
    int var6 = Mouse.getYA();
      if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= this.y) {
         return bool.FALSE;
      } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= var6 - this.getAbsoluteY()) {
         return bool.FALSE;
      } else if (!this.visible) {
         return bool.FALSE;
      } else {
         if (this.getTable() != nullptr && this.getTable().rawget("onMouseMove") != nullptr) {
            LuaManager.caller
               .protectedCallVoid(
                  UIManager.getDefaultThread(),
                  this.getTable().rawget("onMouseMove"),
                  this.table,
                  BoxedStaticValues.toDouble(var1),
                  BoxedStaticValues.toDouble(var3)
               );
         }

    bool var7 = false;

         for (int var8 = this.getControls().size() - 1; var8 >= 0; var8--) {
    UIElement var9 = this.getControls().get(var8);
            if ((
                  !(var5 >= var9.getAbsoluteX())
                     || !(var6 >= var9.getAbsoluteY())
                     || !(var5 < var9.getAbsoluteX() + var9.getWidth())
                     || !(var6 < var9.getAbsoluteY() + var9.getHeight())
               )
               && !var9.isCapture()) {
               var9.onMouseMoveOutside(var1, var3);
            } else if (!var7 && var9.onMouseMove(var1, var3)) {
               var7 = true;
            }
         }

         return this.bConsumeMouseEvents ? bool.TRUE : bool.FALSE;
      }
   }

    void onMouseMoveOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseMoveOutside") != nullptr) {
         LuaManager.caller
            .protectedCallVoid(
               UIManager.getDefaultThread(),
               this.getTable().rawget("onMouseMoveOutside"),
               this.table,
               BoxedStaticValues.toDouble(var1),
               BoxedStaticValues.toDouble(var3)
            );
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = this.getControls().get(var5);
         var6.onMouseMoveOutside(var1, var3);
      }
   }

    bool onMouseUp(double var1, double var3) {
      if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else if (!this.visible) {
         return bool.FALSE;
      } else {
    bool var5 = false;

         for (int var8 = this.getControls().size() - 1; var8 >= 0; var8--) {
    UIElement var7 = this.getControls().get(var8);
            if (!var5
               && (
                  var1 >= var7.getXScrolled(this)
                        && var3 >= var7.getYScrolled(this)
                        && var1 < var7.getXScrolled(this) + var7.getWidth()
                        && var3 < var7.getYScrolled(this) + var7.getHeight()
                     || var7.isCapture()
               )) {
               if (var7.onMouseUp(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue())) {
                  var5 = true;
               }
            } else {
               var7.onMouseUpOutside(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue());
            }

            var8 = PZMath.min(var8, this.getControls().size());
         }

         if (this.getTable() != nullptr) {
            if (var5) {
               if (this.getTable().rawget("onMouseUpOutside") != nullptr) {
                  bool var9 = LuaManager.caller
                     .protectedCallBoolean(
                        UIManager.getDefaultThread(),
                        this.getTable().rawget("onMouseUpOutside"),
                        this.table,
                        BoxedStaticValues.toDouble(var1 - this.xScroll),
                        BoxedStaticValues.toDouble(var3 - this.yScroll)
                     );
                  if (var9 == nullptr) {
                     return bool.TRUE;
                  }

                  if (var9 == bool.TRUE) {
                     return bool.TRUE;
                  }
               }
            } else if (this.getTable().rawget("onMouseUp") != nullptr) {
               bool var10 = LuaManager.caller
                  .protectedCallBoolean(
                     UIManager.getDefaultThread(),
                     this.getTable().rawget("onMouseUp"),
                     this.table,
                     BoxedStaticValues.toDouble(var1 - this.xScroll),
                     BoxedStaticValues.toDouble(var3 - this.yScroll)
                  );
               if (var10 == nullptr) {
                  return bool.TRUE;
               }

               if (var10 == bool.TRUE) {
                  return bool.TRUE;
               }
            }
         }

         return var5 ? bool.TRUE : bool.FALSE;
      }
   }

    void onresize() {
   }

    void onResize() {
      if (this.Parent != nullptr && this.Parent.bResizeDirty) {
    double var1 = this.Parent.getWidth() - this.Parent.lastwidth;
    double var3 = this.Parent.getHeight() - this.Parent.lastheight;
         if (!this.anchorTop && this.anchorBottom) {
            this.setY(this.getY() + var3);
         }

         if (this.anchorTop && this.anchorBottom) {
            this.setHeight(this.getHeight() + var3);
         }

         if (!this.anchorLeft && this.anchorRight) {
            this.setX(this.getX() + var1);
         }

         if (this.anchorLeft && this.anchorRight) {
            this.setWidth(this.getWidth() + var1);
         }
      }

      if (this.getTable() != nullptr && this.getTable().rawget("onResize") != nullptr) {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this.getTable().rawget("onResize"), this.table, this.getWidth(), this.getHeight());
      }

      for (int var5 = this.getControls().size() - 1; var5 >= 0; var5--) {
    UIElement var2 = this.getControls().get(var5);
         if (var2 == nullptr) {
            this.getControls().remove(var5);
         } else {
            var2.onResize();
         }
      }

      this.bResizeDirty = false;
      this.lastwidth = this.getWidth();
      this.lastheight = this.getHeight();
   }

    bool onRightMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else {
    bool var5 = false;

         for (int var6 = this.getControls().size() - 1; var6 >= 0; var6--) {
    UIElement var7 = this.getControls().get(var6);
            if (!var5
               && (
                  var1 >= var7.getXScrolled(this)
                        && var3 >= var7.getYScrolled(this)
                        && var1 < var7.getXScrolled(this) + var7.getWidth()
                        && var3 < var7.getYScrolled(this) + var7.getHeight()
                     || var7.isCapture()
               )) {
               if (var7.onRightMouseDown(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue())) {
                  var5 = true;
               }
            } else if (var7.getTable() != nullptr && var7.getTable().rawget("onRightMouseDownOutside") != nullptr) {
               LuaManager.caller
                  .protectedCallVoid(
                     UIManager.getDefaultThread(),
                     var7.getTable().rawget("onRightMouseDownOutside"),
                     var7.getTable(),
                     BoxedStaticValues.toDouble(var1 - this.xScroll),
                     BoxedStaticValues.toDouble(var3 - this.yScroll)
                  );
            }
         }

         if (this.getTable() != nullptr) {
            if (var5) {
               if (this.getTable().rawget("onRightMouseDownOutside") != nullptr) {
                  bool var8 = LuaManager.caller
                     .protectedCallBoolean(
                        UIManager.getDefaultThread(),
                        this.getTable().rawget("onRightMouseDownOutside"),
                        this.table,
                        BoxedStaticValues.toDouble(var1 - this.xScroll),
                        BoxedStaticValues.toDouble(var3 - this.yScroll)
                     );
                  if (var8 == nullptr) {
                     return bool.TRUE;
                  }

                  if (var8 == bool.TRUE) {
                     return bool.TRUE;
                  }
               }
            } else if (this.getTable().rawget("onRightMouseDown") != nullptr) {
               bool var9 = LuaManager.caller
                  .protectedCallBoolean(
                     UIManager.getDefaultThread(),
                     this.getTable().rawget("onRightMouseDown"),
                     this.table,
                     BoxedStaticValues.toDouble(var1 - this.xScroll),
                     BoxedStaticValues.toDouble(var3 - this.yScroll)
                  );
               if (var9 == nullptr) {
                  return bool.TRUE;
               }

               if (var9 == bool.TRUE) {
                  return bool.TRUE;
               }
            }
         }

         return var5 ? bool.TRUE : bool.FALSE;
      }
   }

    bool onRightMouseUp(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else if (this.Parent != nullptr && this.Parent.maxDrawHeight != -1 && this.Parent.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else if (this.maxDrawHeight != -1 && this.maxDrawHeight <= var3) {
         return bool.FALSE;
      } else {
    bool var5 = false;

         for (int var6 = this.getControls().size() - 1; var6 >= 0; var6--) {
    UIElement var7 = this.getControls().get(var6);
            if (!var5
               && (
                  var1 >= var7.getXScrolled(this)
                        && var3 >= var7.getYScrolled(this)
                        && var1 < var7.getXScrolled(this) + var7.getWidth()
                        && var3 < var7.getYScrolled(this) + var7.getHeight()
                     || var7.isCapture()
               )) {
               if (var7.onRightMouseUp(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue())) {
                  var5 = true;
               }
            } else {
               var7.onRightMouseUpOutside(var1 - var7.getXScrolled(this).intValue(), var3 - var7.getYScrolled(this).intValue());
            }
         }

         if (this.getTable() != nullptr) {
            if (var5) {
               if (this.getTable().rawget("onRightMouseUpOutside") != nullptr) {
                  bool var8 = LuaManager.caller
                     .protectedCallBoolean(
                        UIManager.getDefaultThread(),
                        this.getTable().rawget("onRightMouseUpOutside"),
                        this.table,
                        BoxedStaticValues.toDouble(var1 - this.xScroll),
                        BoxedStaticValues.toDouble(var3 - this.yScroll)
                     );
                  if (var8 == nullptr) {
                     return bool.TRUE;
                  }

                  if (var8 == bool.TRUE) {
                     return bool.TRUE;
                  }
               }
            } else if (this.getTable().rawget("onRightMouseUp") != nullptr) {
               bool var9 = LuaManager.caller
                  .protectedCallBoolean(
                     UIManager.getDefaultThread(),
                     this.getTable().rawget("onRightMouseUp"),
                     this.table,
                     BoxedStaticValues.toDouble(var1 - this.xScroll),
                     BoxedStaticValues.toDouble(var3 - this.yScroll)
                  );
               if (var9 == nullptr) {
                  return bool.TRUE;
               }

               if (var9 == bool.TRUE) {
                  return bool.TRUE;
               }
            }
         }

         return var5 ? bool.TRUE : bool.FALSE;
      }
   }

    void RemoveControl(UIElement var1) {
      this.getControls().remove(var1);
      var1.setParent(nullptr);
   }

    virtual void render() {
        ImGuiRender();
    }

    void update() {
      if (this.enabled) {
         for (int var1 = 0; var1 < this.Controls.size(); var1++) {
            if (this.toTop.contains(this.Controls.get(var1))) {
    UIElement var2 = this.Controls.remove(var1);
               var1--;
               toAdd.push_back(var2);
            }
         }

         this.Controls.addAll(toAdd);
         toAdd.clear();
         this.toTop.clear();
         if (UIManager.doTick && this.getTable() != nullptr && this.getTable().rawget("update") != nullptr) {
            LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this.getTable().rawget("update"), this.table);
         }

         if (this.bResizeDirty) {
            this.onResize();
            this.lastwidth = this.width;
            this.lastheight = this.height;
            this.bResizeDirty = false;
         }

         for (int var3 = 0; var3 < this.getControls().size(); var3++) {
            this.getControls().get(var3).update();
         }
      }
   }

    void BringToTop(UIElement var1) {
      this.getControls().remove(var1);
      this.getControls().push_back(var1);
   }

    bool isCapture() {
      return this.capture ? bool.TRUE : bool.FALSE;
   }

    void setCapture(bool var1) {
      this.capture = var1;
   }

    bool isIgnoreLossControl() {
      return this.IgnoreLossControl ? bool.TRUE : bool.FALSE;
   }

    void setIgnoreLossControl(bool var1) {
      this.IgnoreLossControl = var1;
   }

   public std::vector<UIElement> getControls() {
      return this.Controls;
   }

    void setControls(Vector<UIElement> var1) {
      this.setControls(var1);
   }

    bool isDefaultDraw() {
      return this.defaultDraw ? bool.TRUE : bool.FALSE;
   }

    void setDefaultDraw(bool var1) {
      this.defaultDraw = var1;
   }

    bool isFollowGameWorld() {
      return this.followGameWorld ? bool.TRUE : bool.FALSE;
   }

    void setFollowGameWorld(bool var1) {
      this.followGameWorld = var1;
   }

    int getRenderThisPlayerOnly() {
      return this.renderThisPlayerOnly;
   }

    void setRenderThisPlayerOnly(int var1) {
      this.renderThisPlayerOnly = var1;
   }

    double getHeight() {
      return BoxedStaticValues.toDouble(this.height);
   }

    void setHeight(double var1) {
      if (this.height != var1) {
         this.bResizeDirty = true;
      }

      this.lastheight = this.height;
      this.height = (float)var1;
   }

    UIElement getParent() {
      return this.Parent;
   }

    void setParent(UIElement var1) {
      this.Parent = var1;
   }

    bool isVisible() {
      return this.visible ? bool.TRUE : bool.FALSE;
   }

    void setVisible(bool var1) {
      this.visible = var1;
   }

    double getWidth() {
      return BoxedStaticValues.toDouble(this.width);
   }

    void setWidth(double var1) {
      if (this.width != var1) {
         this.bResizeDirty = true;
      }

      this.lastwidth = this.width;
      this.width = (float)var1;
   }

    double getX() {
      return BoxedStaticValues.toDouble(this.x);
   }

    void setX(double var1) {
      this.x = (float)var1;
   }

    double getXScrolled(UIElement var1) {
      return var1 != nullptr && var1.bScrollChildren && this.bScrollWithParent
         ? BoxedStaticValues.toDouble(this.x + var1.getXScroll())
         : BoxedStaticValues.toDouble(this.x);
   }

    double getYScrolled(UIElement var1) {
      return var1 != nullptr && var1.bScrollChildren && this.bScrollWithParent
         ? BoxedStaticValues.toDouble(this.y + var1.getYScroll())
         : BoxedStaticValues.toDouble(this.y);
   }

    bool isEnabled() {
      return this.enabled;
   }

    void setEnabled(bool var1) {
      this.enabled = var1;
   }

    double getY() {
      return BoxedStaticValues.toDouble(this.y);
   }

    void setY(double var1) {
      this.y = (float)var1;
   }

    void suspendStencil() {
      IndieGL.disableStencilTest();
      IndieGL.disableAlphaTest();
   }

    void resumeStencil() {
      IndieGL.enableStencilTest();
      IndieGL.enableAlphaTest();
   }

    void setStencilRect(double var1, double var3, double var5, double var7) {
      var1 += this.getAbsoluteX();
      var3 += this.getAbsoluteY();
      IndieGL.glStencilMask(255);
      IndieGL.enableStencilTest();
      IndieGL.enableAlphaTest();
      StencilLevel++;
      IndieGL.glStencilFunc(519, StencilLevel, 255);
      IndieGL.glStencilOp(7680, 7680, 7681);
      IndieGL.glColorMask(false, false, false, false);
      SpriteRenderer.instance.renderi(nullptr, (int)var1, (int)var3, (int)var5, (int)var7, 1.0F, 0.0F, 0.0F, 1.0F, nullptr);
      IndieGL.glColorMask(true, true, true, true);
      IndieGL.glStencilOp(7680, 7680, 7680);
      IndieGL.glStencilFunc(514, StencilLevel, 255);
   }

    void clearStencilRect() {
      if (StencilLevel > 0) {
         StencilLevel--;
      }

      if (StencilLevel > 0) {
         IndieGL.glStencilFunc(514, StencilLevel, 255);
      } else {
         IndieGL.glAlphaFunc(519, 0.0F);
         IndieGL.disableStencilTest();
         IndieGL.disableAlphaTest();
         IndieGL.glStencilFunc(519, 255, 255);
         IndieGL.glStencilOp(7680, 7680, 7680);
         IndieGL.glClear(1280);
      }
   }

    void repaintStencilRect(double var1, double var3, double var5, double var7) {
      if (StencilLevel > 0) {
         var1 += this.getAbsoluteX();
         var3 += this.getAbsoluteY();
         IndieGL.glStencilFunc(519, StencilLevel, 255);
         IndieGL.glStencilOp(7680, 7680, 7681);
         IndieGL.glColorMask(false, false, false, false);
         SpriteRenderer.instance.renderi(nullptr, (int)var1, (int)var3, (int)var5, (int)var7, 1.0F, 0.0F, 0.0F, 1.0F, nullptr);
         IndieGL.glColorMask(true, true, true, true);
         IndieGL.glStencilOp(7680, 7680, 7680);
         IndieGL.glStencilFunc(514, StencilLevel, 255);
      }
   }

    KahluaTable getTable() {
      return this.table;
   }

    void setTable(KahluaTable var1) {
      this.table = var1;
   }

    void setHeightSilent(double var1) {
      this.lastheight = this.height;
      this.height = (float)var1;
   }

    void setWidthSilent(double var1) {
      this.lastwidth = this.width;
      this.width = (float)var1;
   }

    void setHeightOnly(double var1) {
      this.height = (float)var1;
   }

    void setWidthOnly(double var1) {
      this.width = (float)var1;
   }

    bool isAnchorTop() {
      return this.anchorTop;
   }

    void setAnchorTop(bool var1) {
      this.anchorTop = var1;
      this.lastwidth = this.width;
      this.lastheight = this.height;
   }

    void ignoreWidthChange() {
      this.lastwidth = this.width;
   }

    void ignoreHeightChange() {
      this.lastheight = this.height;
   }

    bool isAnchorLeft() {
      return this.anchorLeft ? bool.TRUE : bool.FALSE;
   }

    void setAnchorLeft(bool var1) {
      this.anchorLeft = var1;
      this.lastwidth = this.width;
      this.lastheight = this.height;
   }

    bool isAnchorRight() {
      return this.anchorRight ? bool.TRUE : bool.FALSE;
   }

    void setAnchorRight(bool var1) {
      this.anchorRight = var1;
      this.lastwidth = this.width;
      this.lastheight = this.height;
   }

    bool isAnchorBottom() {
      return this.anchorBottom ? bool.TRUE : bool.FALSE;
   }

    void setAnchorBottom(bool var1) {
      this.anchorBottom = var1;
      this.lastwidth = this.width;
      this.lastheight = this.height;
   }

    void addBringToTop(UIElement var1) {
      this.toTop.push_back(var1);
   }

    int getPlayerContext() {
      return this.playerContext;
   }

    void setPlayerContext(int var1) {
      this.playerContext = var1;
   }

    std::string getUIName() {
      return this.uiname;
   }

    void setUIName(const std::string& var1) {
      this.uiname = var1 != nullptr ? var1 : "";
   }

    double clampToParentX(double var1) {
      if (this.getParent() == nullptr) {
         return BoxedStaticValues.toDouble(var1);
      } else {
    double var3 = this.getParent().clampToParentX(this.getParent().getAbsoluteX());
    double var5 = this.getParent().clampToParentX(var3 + this.getParent().getWidth().intValue());
         if (var1 < var3) {
            var1 = var3;
         }

         if (var1 > var5) {
            var1 = var5;
         }

         return BoxedStaticValues.toDouble(var1);
      }
   }

    double clampToParentY(double var1) {
      if (this.getParent() == nullptr) {
    return var1;
      } else {
    double var3 = this.getParent().clampToParentY(this.getParent().getAbsoluteY());
    double var5 = this.getParent().clampToParentY(var3 + this.getParent().getHeight().intValue());
         if (var1 < var3) {
            var1 = var3;
         }

         if (var1 > var5) {
            var1 = var5;
         }

    return var1;
      }
   }

    bool isPointOver(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
    int var5 = this.getHeight().intValue();
         if (this.maxDrawHeight != -1) {
            var5 = Math.min(var5, this.maxDrawHeight);
         }

    double var6 = var1 - this.getAbsoluteX();
    double var8 = var3 - this.getAbsoluteY();
         if (var6 < 0.0 || var6 >= this.getWidth() || var8 < 0.0 || var8 >= var5) {
            return bool.FALSE;
         } else if (this.Parent == nullptr) {
    std::vector var16 = UIManager.getUI();

            for (int var17 = var16.size() - 1; var17 >= 0; var17--) {
    UIElement var12 = (UIElement)var16.get(var17);
               if (var12 == this) {
                  break;
               }

               if (var12.isPointOver(var1, var3)) {
                  return bool.FALSE;
               }
            }

            return bool.TRUE;
         } else {
            for (int var10 = this.Parent.Controls.size() - 1; var10 >= 0; var10--) {
    UIElement var11 = this.Parent.Controls.get(var10);
               if (var11 == this) {
                  break;
               }

               if (var11.isVisible()) {
                  var5 = var11.getHeight().intValue();
                  if (var11.maxDrawHeight != -1) {
                     var5 = Math.min(var5, var11.maxDrawHeight);
                  }

                  var6 = var1 - var11.getAbsoluteX();
                  var8 = var3 - var11.getAbsoluteY();
                  if (var6 >= 0.0 && var6 < var11.getWidth() && var8 >= 0.0 && var8 < var5) {
                     return bool.FALSE;
                  }
               }
            }

            return this.Parent.isPointOver(var1, var3) ? bool.TRUE : bool.FALSE;
         }
      }
   }

    bool isMouseOver() {
      return this.isPointOver(Mouse.getXA(), Mouse.getYA()) ? bool.TRUE : bool.FALSE;
   }

    void* tryGetTableValue(const std::string& var1) {
      return this.getTable() == nullptr ? nullptr : this.getTable().rawget(var1);
   }

    void setWantKeyEvents(bool var1) {
      this.bWantKeyEvents = var1;
   }

    bool isWantKeyEvents() {
      return this.bWantKeyEvents;
   }

    bool isKeyConsumed(int var1) {
    void* var2 = this.tryGetTableValue("isKeyConsumed");
      if (var2 == nullptr) {
    return false;
      } else {
    bool var3 = LuaManager.caller.pcallBoolean(UIManager.getDefaultThread(), var2, this.getTable(), BoxedStaticValues.toDouble(var1));
    return var3 = = nullptr ? bool.FALSE : var3;
      }
   }

    void onKeyPress(int var1) {
    void* var2 = this.tryGetTableValue("onKeyPress");
      if (var2 != nullptr) {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), var2, this.getTable(), BoxedStaticValues.toDouble(var1));
      }
   }

    void onKeyRepeat(int var1) {
    void* var2 = this.tryGetTableValue("onKeyRepeat");
      if (var2 != nullptr) {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), var2, this.getTable(), BoxedStaticValues.toDouble(var1));
      }
   }

    void onKeyRelease(int var1) {
    void* var2 = this.tryGetTableValue("onKeyRelease");
      if (var2 != nullptr) {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), var2, this.getTable(), BoxedStaticValues.toDouble(var1));
      }
   }

    bool isForceCursorVisible() {
      return this.bForceCursorVisible;
   }

    void setForceCursorVisible(bool var1) {
      this.bForceCursorVisible = var1;
   }
}
} // namespace ui
} // namespace zombie
