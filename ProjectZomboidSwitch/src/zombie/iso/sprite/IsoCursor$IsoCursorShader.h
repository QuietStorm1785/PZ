#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/iso/IsoCamera.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {


class IsoCursor {
public:
    float m_alpha = 1.0F;
    Texture m_textureCursor;
    Texture m_textureWorld;
    int m_screenX;
    int m_screenY;

   IsoCursor$IsoCursorShader() {
      super("isocursor");
   }

    void startMainThread(TextureDraw var1, int var2) {
      this.m_alpha = this.calculateAlpha();
      this.m_textureWorld = Core.getInstance().OffscreenBuffer.getTexture(var2);
   }

    void startRenderThread(TextureDraw var1) {
      this.getProgram().setValue("u_alpha", this.m_alpha);
      this.getProgram().setValue("TextureCursor", this.m_textureCursor, 0);
      this.getProgram().setValue("TextureBackground", this.m_textureWorld, 1);
      SpriteRenderer.ringBuffer.shaderChangedTexture1();
      GL11.glEnable(3042);
   }

    void accept(TextureDraw var1) {
    uint8_t var2 = 0;
    int var3 = (int)var1.x0 - this.m_screenX;
    int var4 = (int)var1.y0 - this.m_screenY;
    int var5 = this.m_screenX + this.width - (int)var1.x2;
    int var6 = this.m_screenY + this.height - (int)var1.y2;
      this.m_screenX += var3;
      this.m_screenY += var4;
      this.width -= var3 + var5;
      this.height -= var4 + var6;
    float var7 = this.m_textureWorld.getWidthHW();
    float var8 = this.m_textureWorld.getHeightHW();
    float var9 = IsoCamera.getScreenTop(var2) + IsoCamera.getScreenHeight(var2) - (this.m_screenY + this.height);
      var1.tex1 = this.m_textureWorld;
      var1.tex1_u0 = this.m_screenX / var7;
      var1.tex1_v3 = var9 / var8;
      var1.tex1_u1 = (this.m_screenX + this.width) / var7;
      var1.tex1_v2 = var9 / var8;
      var1.tex1_u2 = (this.m_screenX + this.width) / var7;
      var1.tex1_v1 = (var9 + this.height) / var8;
      var1.tex1_u3 = this.m_screenX / var7;
      var1.tex1_v0 = (var9 + this.height) / var8;
   }

    float calculateAlpha() {
    float var1 = 0.05F;
      switch (Core.getInstance().getIsoCursorVisibility()) {
         case 0:
            var1 = 0.0F;
            break;
         case 1:
            var1 = 0.05F;
            break;
         case 2:
            var1 = 0.1F;
            break;
         case 3:
            var1 = 0.15F;
            break;
         case 4:
            var1 = 0.3F;
            break;
         case 5:
            var1 = 0.5F;
            break;
         case 6:
            var1 = 0.75F;
      }

    return var1;
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
