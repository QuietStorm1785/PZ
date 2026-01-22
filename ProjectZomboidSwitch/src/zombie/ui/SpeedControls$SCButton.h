#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class SpeedControls {
public:
    static const int BORDER = 3;

   public SpeedControls$SCButton(std::string var1, float var2, float var3, std::string var4, std::string var5, UIElement var6) {
      super(var1, var2, var3, var4, var5, var6);
      this.width += 6.0F;
      this.height += 6.0F;
   }

    void render() {
    int var1 = 3;
      if (this.clicked) {
         var1++;
      }

      this.DrawTextureScaledCol(nullptr, 0.0, this.clicked ? 1.0 : 0.0, this.width, this.height, 0.0, 0.0, 0.0, 0.5);
      if (!this.mouseOver && !this.name == this.display.getClickedValue())) {
         this.DrawTextureScaled(this.texture, 3.0, var1, this.texture.getWidth(), this.texture.getHeight(), this.notclickedAlpha);
      } else {
         this.DrawTextureScaled(this.highlight, 3.0, var1, this.highlight.getWidth(), this.highlight.getHeight(), this.clickedalpha);
      }

      if (this.overicon != nullptr) {
         this.DrawTextureScaled(this.overicon, 3.0, var1, this.overicon.getWidth(), this.overicon.getHeight(), 1.0);
      }
   }
}
} // namespace ui
} // namespace zombie
