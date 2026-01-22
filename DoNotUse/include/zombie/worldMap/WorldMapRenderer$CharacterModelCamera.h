#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"

namespace zombie {
namespace worldMap {


class WorldMapRenderer {
public:
    float m_worldScale;
    float m_angle;
    float m_playerX;
    float m_playerY;
    bool m_bVehicle;

   private WorldMapRenderer$CharacterModelCamera() {
   }

    void Begin() {
    Matrix4f var1 = WorldMapRenderer.allocMatrix4f();
      var1.identity();
      var1.translate(this.m_playerX * this.m_worldScale, this.m_playerY * this.m_worldScale, 0.0F);
      var1.rotateX((float) (Math.PI / 2));
      var1.rotateY(this.m_angle + (float) (Math.PI * 3.0 / 2.0));
      if (this.m_bVehicle) {
         var1.scale(this.m_worldScale);
      } else {
         var1.scale(1.5F * this.m_worldScale);
      }

      PZGLUtil.pushAndMultMatrix(5888, var1);
      WorldMapRenderer.releaseMatrix4f(var1);
   }

    void End() {
      PZGLUtil.popMatrix(5888);
   }
}
} // namespace worldMap
} // namespace zombie
