#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class IsoWeatherFX {
public:
    static const Matrix4f s_matrix4f = std::make_shared<Matrix4f>();
   const org.lwjgl.util.vector.Matrix4f m_mvp = new org.lwjgl.util.vector.Matrix4f();
    int m_width;
    int m_height;
    bool m_bSet = false;

   private IsoWeatherFX$Drawer() {
   }

    void init(int var1, int var2) {
      if (var1 != this.m_width || var2 != this.m_height || !this.m_bSet) {
         this.m_width = var1;
         this.m_height = var2;
         this.m_bSet = false;
         s_matrix4f.setOrtho(0.0F, this.m_width, this.m_height, 0.0F, -1.0F, 1.0F);
         PZMath.convertMatrix(s_matrix4f, this.m_mvp);
         this.m_mvp.transpose();
         SpriteRenderer.instance.drawGeneric(this);
      }
   }

    void render() {
      IsoWeatherFX.s_shader.getShaderProgram().setValue("u_mvp", this.m_mvp);
      this.m_bSet = true;
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
