#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoMannequin {
public:
    float x;
    float y;
    float z;
    float m_animPlayerAngle;
    bool bRendered;

   private IsoMannequin$Drawer(IsoMannequin var1) {
      this.this$0 = var1;
   }

    void init(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.bRendered = false;
      this.this$0.animatedModel.renderMain();
      this.m_animPlayerAngle = this.this$0.animatedModel.getAnimationPlayer().getRenderedAngle();
   }

    void render() {
      this.this$0.animatedModel.DoRenderToWorld(this.x, this.y, this.z, this.m_animPlayerAngle);
      this.bRendered = true;
   }

    void postRender() {
      this.this$0.animatedModel.postRender(this.bRendered);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
