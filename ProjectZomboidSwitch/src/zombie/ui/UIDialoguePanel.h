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


class UIDialoguePanel : public UIElement {
public:
    float alpha = 1.0F;
    Texture dialogBottomLeft = nullptr;
    Texture dialogBottomMiddle = nullptr;
    Texture dialogBottomRight = nullptr;
    Texture dialogLeft = nullptr;
    Texture dialogMiddle = nullptr;
    Texture dialogRight = nullptr;
    Texture titleLeft = nullptr;
    Texture titleMiddle = nullptr;
    Texture titleRight = nullptr;
    float clientH = 0.0F;
    float clientW = 0.0F;
    std::vector<std::tuple<float, float, float, float>> nestedItems; // x, y, w, h

    public UIDialoguePanel(float var1, float var2, float var3, float var4) {
      this.x = var1;
      this.y = var2;
      this.width = var3;
      this.height = var4;
      this.titleLeft = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Left.png");
      this.titleMiddle = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Middle.png");
      this.titleRight = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Right.png");
      this.dialogLeft = Texture.getSharedTexture("media/ui/Dialog_Left.png");
      this.dialogMiddle = Texture.getSharedTexture("media/ui/Dialog_Middle.png");
      this.dialogRight = Texture.getSharedTexture("media/ui/Dialog_Right.png");
      this.dialogBottomLeft = Texture.getSharedTexture("media/ui/Dialog_Bottom_Left.png");
      this.dialogBottomMiddle = Texture.getSharedTexture("media/ui/Dialog_Bottom_Middle.png");
      this.dialogBottomRight = Texture.getSharedTexture("media/ui/Dialog_Bottom_Right.png");
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
}
} // namespace ui
} // namespace zombie
