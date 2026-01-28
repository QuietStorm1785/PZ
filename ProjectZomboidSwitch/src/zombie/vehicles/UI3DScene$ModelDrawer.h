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
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/vehicles/UI3DScene/ModelRenderData.h"
#include "zombie/vehicles/UI3DScene/SceneModel.h"
#include "zombie/vehicles/UI3DScene/StateData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneModel m_model;
    ModelRenderData m_renderData;
    bool bRendered;

   private UI3DScene$ModelDrawer() {
   }

    void init(SceneModel var1, ModelRenderData var2) {
      this.m_model = var1;
      this.m_renderData = var2;
      this.bRendered = false;
   }

    void render() {
    StateData var1 = this.m_model.m_scene.stateDataRender();
      PZGLUtil.pushAndLoadMatrix(5889, var1.m_projection);
      PZGLUtil.pushAndLoadMatrix(5888, var1.m_modelView);
    Model var2 = this.m_model.m_model;
    Shader var3 = var2.Effect;
      if (var3 != nullptr && var2.Mesh != nullptr && var2.Mesh.isReady()) {
         GL11.glPushAttrib(1048575);
         GL11.glPushClientAttrib(-1);
    UI3DScene var4 = this.m_renderData.m_object.m_scene;
         GL11.glViewport(
            var4.getAbsoluteX().intValue(),
            Core.getInstance().getScreenHeight() - var4.getAbsoluteY().intValue() - var4.getHeight().intValue(),
            var4.getWidth().intValue(),
            var4.getHeight().intValue()
         );
         GL11.glDepthFunc(513);
         GL11.glDepthMask(true);
         GL11.glDepthRange(0.0, 1.0);
         GL11.glEnable(2929);
         GL11.glColor3f(1.0F, 1.0F, 1.0F);
         var3.Start();
         if (var2.tex != nullptr) {
            var3.setTexture(var2.tex, "Texture", 0);
         }

         var3.setDepthBias(0.0F);
         var3.setAmbient(1.0F);
         var3.setLightingAmount(1.0F);
         var3.setHueShift(0.0F);
         var3.setTint(1.0F, 1.0F, 1.0F);
         var3.setAlpha(1.0F);

         for (int var5 = 0; var5 < 5; var5++) {
            var3.setLight(var5, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
         }

         var3.setTransformMatrix(this.m_renderData.m_transform, false);
         var2.Mesh.Draw(var3);
         var3.End();
         if (Core.bDebug) {
         }

         GL11.glPopAttrib();
         GL11.glPopClientAttrib();
         Texture.lastTextureID = -1;
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
         SpriteRenderer.ringBuffer.restoreVBOs = true;
      }

      PZGLUtil.popMatrix(5889);
      PZGLUtil.popMatrix(5888);
      this.bRendered = true;
   }

    void postRender() {
   }
}
} // namespace vehicles
} // namespace zombie
