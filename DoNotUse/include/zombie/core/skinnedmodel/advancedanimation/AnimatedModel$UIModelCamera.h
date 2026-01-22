#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Math.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimatedModel {
public:
    int x;
    int y;
    int w;
    int h;
    float sizeV;
    float m_animPlayerAngle;

   private AnimatedModel$UIModelCamera(AnimatedModel var1) {
      this.this$0 = var1;
   }

    void Begin() {
      GL11.glViewport(this.x, this.y, this.w, this.h);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
    float var1 = (float)this.w / this.h;
      if (this.this$0.flipY) {
         GL11.glOrtho(-this.sizeV * var1, this.sizeV * var1, this.sizeV, -this.sizeV, -100.0, 100.0);
      } else {
         GL11.glOrtho(-this.sizeV * var1, this.sizeV * var1, -this.sizeV, this.sizeV, -100.0, 100.0);
      }

    float var2 = Math.sqrt(2048.0F);
      GL11.glScalef(-var2, var2, var2);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      if (this.this$0.bIsometric) {
         GL11.glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
         GL11.glRotated(this.m_animPlayerAngle * (180.0F / (float)java.lang.Math.PI) + 45.0F, 0.0, 1.0, 0.0);
      } else {
         GL11.glRotated(this.m_animPlayerAngle * (180.0F / (float)java.lang.Math.PI), 0.0, 1.0, 0.0);
      }

      GL11.glTranslatef(this.this$0.offset.x(), this.this$0.offset.y(), this.this$0.offset.z());
   }

    void End() {
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
