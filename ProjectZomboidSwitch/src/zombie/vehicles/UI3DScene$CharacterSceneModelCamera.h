#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include "zombie/core/Core.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/vehicles/UI3DScene/SceneModelCamera.h"
#include "zombie/vehicles/UI3DScene/StateData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
   private UI3DScene$CharacterSceneModelCamera(UI3DScene var1) {
      super(var1);
      this.this$0 = var1;
   }

    void Begin() {
    StateData var1 = this.this$0.stateDataRender();
      GL11.glViewport(
         this.this$0.getAbsoluteX().intValue(),
         Core.getInstance().getScreenHeight() - this.this$0.getAbsoluteY().intValue() - this.this$0.getHeight().intValue(),
         this.this$0.getWidth().intValue(),
         this.this$0.getHeight().intValue()
      );
      PZGLUtil.pushAndLoadMatrix(5889, var1.m_projection);
    Matrix4f var2 = UI3DScene.allocMatrix4f();
      var2.set(var1.m_modelView);
      var2.mul(this.m_renderData.m_transform);
      PZGLUtil.pushAndLoadMatrix(5888, var2);
      UI3DScene.releaseMatrix4f(var2);
   }

    void End() {
      PZGLUtil.popMatrix(5889);
      PZGLUtil.popMatrix(5888);
   }
}
} // namespace vehicles
} // namespace zombie
