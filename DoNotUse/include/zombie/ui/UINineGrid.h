#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Rectangle.h"
#include "zombie/core/Color.h"
#include "zombie/core/textures/Texture.h"
#include <algorithm>

namespace zombie {
namespace ui {


class UINineGrid : public UIElement {
public:
    Texture GridTopLeft = nullptr;
    Texture GridTop = nullptr;
    Texture GridTopRight = nullptr;
    Texture GridLeft = nullptr;
    Texture GridCenter = nullptr;
    Texture GridRight = nullptr;
    Texture GridBottomLeft = nullptr;
    Texture GridBottom = nullptr;
    Texture GridBottomRight = nullptr;
    int TopWidth = 10;
    int LeftWidth = 10;
    int RightWidth = 10;
    int BottomWidth = 10;
    int clientH = 0;
    int clientW = 0;
   public std::stack<Rectangle> nestedItems = std::make_unique<std::stack<>>();
    Color Colour = std::make_shared<Color>(50, 50, 50, 212);

   public UINineGrid(
      int var1,
      int var2,
      int var3,
      int var4,
      int var5,
      int var6,
      int var7,
      int var8,
      std::string var9,
      std::string var10,
      std::string var11,
      std::string var12,
      std::string var13,
      std::string var14,
      std::string var15,
      std::string var16,
      std::string var17
   ) {
      this.x = var1;
      this.y = var2;
      this.width = var3;
      this.height = var4;
      this.TopWidth = var5;
      this.LeftWidth = var6;
      this.RightWidth = var7;
      this.BottomWidth = var8;
      this.GridTopLeft = Texture.getSharedTexture(var9);
      this.GridTop = Texture.getSharedTexture(var10);
      this.GridTopRight = Texture.getSharedTexture(var11);
      this.GridLeft = Texture.getSharedTexture(var12);
      this.GridCenter = Texture.getSharedTexture(var13);
      this.GridRight = Texture.getSharedTexture(var14);
      this.GridBottomLeft = Texture.getSharedTexture(var15);
      this.GridBottom = Texture.getSharedTexture(var16);
      this.GridBottomRight = Texture.getSharedTexture(var17);
      this.clientW = var3;
      this.clientH = var4;
   }

    void Nest(UIElement var1, int var2, int var3, int var4, int var5) {
      this.AddChild(var1);
      this.nestedItems.push_back(std::make_shared<Rectangle>(var5, var2, var3, var4));
      var1.setX(var5);
      var1.setY(var2);
      var1.update();
   }

    void render() {
      this.DrawTextureScaledCol(this.GridTopLeft, 0.0, 0.0, this.LeftWidth, this.TopWidth, this.Colour);
      this.DrawTextureScaledCol(this.GridTop, this.LeftWidth, 0.0, this.getWidth() - (this.LeftWidth + this.RightWidth), this.TopWidth, this.Colour);
      this.DrawTextureScaledCol(this.GridTopRight, this.getWidth() - this.RightWidth, 0.0, this.RightWidth, this.TopWidth, this.Colour);
      this.DrawTextureScaledCol(this.GridLeft, 0.0, this.TopWidth, this.LeftWidth, this.getHeight() - (this.TopWidth + this.BottomWidth), this.Colour);
      this.DrawTextureScaledCol(
         this.GridCenter,
         this.LeftWidth,
         this.TopWidth,
         this.getWidth() - (this.LeftWidth + this.RightWidth),
         this.getHeight() - (this.TopWidth + this.BottomWidth),
         this.Colour
      );
      this.DrawTextureScaledCol(
         this.GridRight, this.getWidth() - this.RightWidth, this.TopWidth, this.RightWidth, this.getHeight() - (this.TopWidth + this.BottomWidth), this.Colour
      );
      this.DrawTextureScaledCol(this.GridBottomLeft, 0.0, this.getHeight() - this.BottomWidth, this.LeftWidth, this.BottomWidth, this.Colour);
      this.DrawTextureScaledCol(
         this.GridBottom,
         this.LeftWidth,
         this.getHeight() - this.BottomWidth,
         this.getWidth() - (this.LeftWidth + this.RightWidth),
         this.BottomWidth,
         this.Colour
      );
      this.DrawTextureScaledCol(
         this.GridBottomRight, this.getWidth() - this.RightWidth, this.getHeight() - this.BottomWidth, this.RightWidth, this.BottomWidth, this.Colour
      );
      super.render();
   }

    void update() {
      super.update();
    int var1 = 0;

      for (Rectangle var3 : this.nestedItems) {
    UIElement var4 = (UIElement)this.getControls().get(var1);
         var4.setX((float)var3.getX());
         var4.setY((float)var3.getY());
         var4.setWidth((int)(this.clientW - (var3.getX() + var3.getWidth())));
         var4.setHeight((int)(this.clientH - (var3.getY() + var3.getHeight())));
         var4.onresize();
         var1++;
      }
   }

    void setAlpha(float var1) {
      this.Colour.a = var1;
   }

    float getAlpha() {
      return this.Colour.a;
   }
}
} // namespace ui
} // namespace zombie
