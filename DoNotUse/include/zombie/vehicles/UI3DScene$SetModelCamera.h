#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/vehicles/UI3DScene/SceneModelCamera.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneModelCamera m_camera;
    SceneObjectRenderData m_renderData;

   private UI3DScene$SetModelCamera() {
   }

   UI3DScene$SetModelCamera init(SceneModelCamera var1, SceneObjectRenderData var2) {
      this.m_camera = var1;
      this.m_renderData = var2;
    return this;
   }

    void render() {
      this.m_camera.m_renderData = this.m_renderData;
      ModelCamera.instance = this.m_camera;
   }

    void postRender() {
      UI3DScene.s_SetModelCameraPool.release(this);
   }
}
} // namespace vehicles
} // namespace zombie
