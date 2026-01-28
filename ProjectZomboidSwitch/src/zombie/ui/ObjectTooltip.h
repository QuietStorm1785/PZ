#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include <algorithm>

namespace zombie {
namespace ui {


class ObjectTooltip : public UIElement {
public:
    static float alphaStep = 0.1F;
    bool bIsItem = false;
    InventoryItem Item = nullptr;
    IsoObject Object;
    float alpha = 0.0F;
    int showDelay = 0;
    float targetAlpha = 0.0F;
    Texture texture;
    int padRight = 5;
    int padBottom = 5;
    IsoGameCharacter character;
    bool measureOnly;
    float weightOfStack = 0.0F;
    static int lineSpacing = 14;
    static std::string fontSize = "Small";
    static UIFont font = UIFont.Small;
   private static std::stack<Layout> freeLayouts = std::make_unique<std::stack<>>();

   // ImGui rendering override
   virtual void ImGuiRender() override;

    public ObjectTooltip() {
      this.texture = Texture.getSharedTexture("black");
      this.width = 130.0F;
      this.height = 130.0F;
      this.defaultDraw = false;
      lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
      checkFont();
   }

    static void checkFont() {
      if (!fontSize == Core.getInstance().getOptionTooltipFont())) {
         fontSize = Core.getInstance().getOptionTooltipFont();
         if ("Large" == fontSize)) {
            font = UIFont.Large;
         } else if ("Medium" == fontSize)) {
            font = UIFont.Medium;
         } else {
            font = UIFont.Small;
         }

         lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
      }
   }

    UIFont getFont() {
    return font;
   }

    int getLineSpacing() {
    return lineSpacing;
   }

    void DrawText(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawText(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

    void DrawTextCentre(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawTextCentre(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

    void DrawTextRight(UIFont var1, const std::string& var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawTextRight(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

    void DrawValueRight(int var1, int var2, int var3, bool var4) {
    int var5 = var1;
    std::string var6 = var5;
    float var7 = 0.3F;
    float var8 = 1.0F;
    float var9 = 0.2F;
    float var10 = 1.0F;
      if (var1 > 0) {
         var6 = "+" + var6;
      }

      if (var1 < 0 && var4 || var1 > 0 && !var4) {
         var7 = 0.8F;
         var8 = 0.3F;
         var9 = 0.2F;
      }

      this.DrawTextRight(font, var6, var2, var3, var7, var8, var9, var10);
   }

    void DrawValueRightNoPlus(int var1, int var2, int var3) {
    int var4 = var1;
    std::string var5 = var4;
    float var6 = 1.0F;
    float var7 = 1.0F;
    float var8 = 1.0F;
    float var9 = 1.0F;
      this.DrawTextRight(font, var5, var2, var3, var6, var7, var8, var9);
   }

    void DrawValueRightNoPlus(float var1, int var2, int var3) {
    float var4 = var1;
      var4 = (int)((var4.floatValue() + 0.01) * 10.0) / 10.0F;
    std::string var5 = var4;
    float var6 = 1.0F;
    float var7 = 1.0F;
    float var8 = 1.0F;
    float var9 = 1.0F;
      this.DrawTextRight(font, var5, var2, var3, var6, var7, var8, var9);
   }

    void DrawTextureScaled(Texture var1, double var2, double var4, double var6, double var8, double var10) {
      if (!this.measureOnly) {
         super.DrawTextureScaled(var1, var2, var4, var6, var8, var10);
      }
   }

    void DrawTextureScaledAspect(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (!this.measureOnly) {
         super.DrawTextureScaledAspect(var1, var2, var4, var6, var8, var10, var12, var14, var16);
      }
   }

    void DrawProgressBar(int var1, int var2, int var3, int var4, float var5, double var6, double var8, double var10, double var12) {
      if (!this.measureOnly) {
         if (var5 < 0.0F) {
            var5 = 0.0F;
         }

         if (var5 > 1.0F) {
            var5 = 1.0F;
         }

    int var14 = (int)Math.floor(var3 * var5);
         if (var5 > 0.0F && var14 == 0) {
            var14 = 1;
         }

         this.DrawTextureScaledColor(nullptr, (double)var1, (double)var2, (double)var14, 3.0, var6, var8, var10, var12);
         this.DrawTextureScaledColor(nullptr, (double)var1 + var14, (double)var2, (double)var3 - var14, 3.0, 0.25, 0.25, 0.25, 1.0);
      }
   }

    bool onMouseMove(double var1, double var3) {
      this.setX(this.getX() + var1);
      this.setY(this.getY() + var3);
      return bool.FALSE;
   }

    void onMouseMoveOutside(double var1, double var3) {
      this.setX(this.getX() + var1);
      this.setY(this.getY() + var3);
   }

    void render() {
      if (this.isVisible()) {
         if (!(this.alpha <= 0.0F)) {
            if (!this.bIsItem && this.Object != nullptr && this.Object.haveSpecialTooltip()) {
               this.Object.DoSpecialTooltip(this, this.Object.square);
            }

            super.render();
         }
      }
   }

    void show(IsoObject var1, double var2, double var4) {
      this.bIsItem = false;
      this.Object = var1;
      this.setX(var2);
      this.setY(var4);
      this.targetAlpha = 0.5F;
      this.showDelay = 15;
      this.alpha = 0.0F;
   }

    void hide() {
      this.Object = nullptr;
      this.showDelay = 0;
      this.setVisible(false);
   }

    void update() {
      if (!(this.alpha <= 0.0F) || this.targetAlpha != 0.0F) {
         if (this.showDelay > 0) {
            if (--this.showDelay == 0) {
               this.setVisible(true);
            }
         } else {
            if (this.alpha < this.targetAlpha) {
               this.alpha = this.alpha + alphaStep;
               if (this.alpha > 0.5F) {
                  this.alpha = 0.5F;
               }
            } else if (this.alpha > this.targetAlpha) {
               this.alpha = this.alpha - alphaStep;
               if (this.alpha < this.targetAlpha) {
                  this.alpha = this.targetAlpha;
               }
            }
         }
      }
   }

    void show(InventoryItem var1, int var2, int var3) {
      this.Object = nullptr;
      this.Item = var1;
      this.bIsItem = true;
      this.setX(this.getX());
      this.setY(this.getY());
      this.targetAlpha = 0.5F;
      this.showDelay = 15;
      this.alpha = 0.0F;
      this.setVisible(true);
   }

    void adjustWidth(int var1, const std::string& var2) {
    int var3 = TextManager.instance.MeasureStringX(font, var2);
      if (var1 + var3 + this.padRight > this.width) {
         this.setWidth(var1 + var3 + this.padRight);
      }
   }

    Layout beginLayout() {
    Layout var1 = nullptr;
      if (freeLayouts.empty()) {
         var1 = std::make_unique<Layout>();
      } else {
         var1 = freeLayouts.pop();
      }

    return var1;
   }

    void endLayout(Layout var1) {
      while (var1 != nullptr) {
    Layout var2 = var1.next;
         var1.free();
         freeLayouts.push(var1);
         var1 = var2;
      }
   }

    Texture getTexture() {
      return this.texture;
   }

    void setCharacter(IsoGameCharacter var1) {
      this.character = var1;
   }

    IsoGameCharacter getCharacter() {
      return this.character;
   }

    void setMeasureOnly(bool var1) {
      this.measureOnly = var1;
   }

    bool isMeasureOnly() {
      return this.measureOnly;
   }

    float getWeightOfStack() {
      return this.weightOfStack;
   }

    void setWeightOfStack(float var1) {
      this.weightOfStack = var1;
   }
}
} // namespace ui
} // namespace zombie
