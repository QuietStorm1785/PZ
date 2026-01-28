#pragma once
#include <vector>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
      std::vector<std::tuple<float, float, float, float>> nestedItems; // x, y, w, h
      float ColourR = 50, ColourG = 50, ColourB = 50, ColourA = 212;

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
      this.nestedItems.push_back(std::make_shared<zombie::core::Rect>(var5, var2, var3, var4));
      var1.setX(var5);
      var1.setY(var2);
      var1.update();
   }

    void ImGuiRender() override;
    void render() override { ImGuiRender(); }

    void update() {
      super.update();
    int var1 = 0;

      for (zombie::core::Rect var3 : this.nestedItems) {
    UIElement var4 = (UIElement)this.getControls().get(var1);
         var4.setX((float)var3.getX());
         var4.setY((float)var3.getY());
         var4.setWidth((int)(this.clientW - (var3.getX() + var3.getWidth())));
         var4.setHeight((int)(this.clientH - (var3.getY() + var3.getHeight())));
         var4.onresize();
         var1++;
      }
   }

      void setAlpha(float var1) { ColourA = var1; }
      float getAlpha() { return ColourA; }
}
} // namespace ui
} // namespace zombie
