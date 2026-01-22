#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace ui {


class UI3DModel {
public:
    int absX;
    int absY;
    float m_animPlayerAngle;
    bool bRendered;

   private UI3DModel$Drawer(UI3DModel var1) {
      this.this$0 = var1;
   }

    void init(int var1, int var2) {
      this.absX = var1;
      this.absY = var2;
      this.m_animPlayerAngle = this.this$0.animatedModel.getAnimationPlayer().getRenderedAngle();
      this.bRendered = false;
    float var3 = this.this$0.animatedModel.isIsometric() ? -0.45F : -0.5F;
      if (this.this$0.yOffset != 0.0F) {
         var3 = this.this$0.yOffset;
      }

      this.this$0.animatedModel.setOffset(this.this$0.xOffset, var3, 0.0F);
      this.this$0.animatedModel.renderMain();
   }

    void render() {
    float var1 = this.this$0.animatedModel.isIsometric() ? 22.0F : 25.0F;
      if (this.this$0.zoom > 0.0F) {
         var1 -= this.this$0.zoom;
      }

      this.this$0
         .animatedModel
         .DoRender(this.absX, Core.height - this.absY - (int)this.this$0.height, (int)this.this$0.width, (int)this.this$0.height, var1, this.m_animPlayerAngle);
      this.bRendered = true;
   }

    void postRender() {
      this.this$0.animatedModel.postRender(this.bRendered);
   }
}
} // namespace ui
} // namespace zombie
