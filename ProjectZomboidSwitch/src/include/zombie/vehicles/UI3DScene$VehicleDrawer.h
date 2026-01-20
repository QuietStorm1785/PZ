#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Matrix4fc.h"
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/shader/ShaderManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/vehicles/UI3DScene/SceneVehicle.h"
#include "zombie/vehicles/UI3DScene/VehicleRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneVehicle m_vehicle;
    VehicleRenderData m_renderData;
    bool bRendered;
   const float[] fzeroes = new float[16];
    const Vector3f paintColor = std::make_shared<Vector3f>(0.0F, 0.5F, 0.5F);
    const Matrix4f IDENTITY = std::make_shared<Matrix4f>();

   private UI3DScene$VehicleDrawer() {
   }

    void init(SceneVehicle var1, VehicleRenderData var2) {
      this.m_vehicle = var1;
      this.m_renderData = var2;
      this.bRendered = false;
   }

    void render() {
      for (int var1 = 0; var1 < this.m_renderData.m_models.size(); var1++) {
         GL11.glPushAttrib(1048575);
         GL11.glPushClientAttrib(-1);
         this.render(var1);
         GL11.glPopAttrib();
         GL11.glPopClientAttrib();
         Texture.lastTextureID = -1;
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
         SpriteRenderer.ringBuffer.restoreVBOs = true;
      }
   }

    void render(int var1) {
      this.m_renderData.m_transform.set((Matrix4fc)this.m_renderData.m_transforms.get(var1));
      ModelCamera.instance.Begin();
    Model var2 = (Model)this.m_renderData.m_models.get(var1);
    bool var3 = var2.bStatic;
      if (Core.bDebug && DebugOptions.instance.ModelRenderWireframe.getValue()) {
         GL11.glPolygonMode(1032, 6913);
         GL11.glEnable(2848);
         GL11.glLineWidth(0.75F);
    Shader var6 = ShaderManager.instance.getOrCreateShader("vehicle_wireframe", var3);
         if (var6 != nullptr) {
            var6.Start();
            var6.setTransformMatrix(this.IDENTITY.identity(), false);
            var2.Mesh.Draw(var6);
            var6.End();
         }

         GL11.glDisable(2848);
         ModelCamera.instance.End();
      } else {
    Shader var4 = var2.Effect;
         if (var4 != nullptr && var4.isVehicleShader()) {
            GL11.glDepthFunc(513);
            GL11.glDepthMask(true);
            GL11.glDepthRange(0.0, 1.0);
            GL11.glEnable(2929);
            GL11.glColor3f(1.0F, 1.0F, 1.0F);
            var4.Start();
            if (var2.tex != nullptr) {
               var4.setTexture(var2.tex, "Texture0", 0);
               GL11.glTexEnvi(8960, 8704, 7681);
               if (this.m_vehicle.m_script.getSkinCount() > 0 && this.m_vehicle.m_script.getSkin(0).textureMask != nullptr) {
    Texture var7 = Texture.getSharedTexture("media/textures/" + this.m_vehicle.m_script.getSkin(0).textureMask + ".png");
                  var4.setTexture(var7, "TextureMask", 2);
                  GL11.glTexEnvi(8960, 8704, 7681);
               }
            }

            var4.setDepthBias(0.0F);
            var4.setAmbient(1.0F);
            var4.setLightingAmount(1.0F);
            var4.setHueShift(0.0F);
            var4.setTint(1.0F, 1.0F, 1.0F);
            var4.setAlpha(1.0F);

            for (int var8 = 0; var8 < 5; var8++) {
               var4.setLight(var8, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
            }

            var4.setTextureUninstall1(this.fzeroes);
            var4.setTextureUninstall2(this.fzeroes);
            var4.setTextureLightsEnables2(this.fzeroes);
            var4.setTextureDamage1Enables1(this.fzeroes);
            var4.setTextureDamage1Enables2(this.fzeroes);
            var4.setTextureDamage2Enables1(this.fzeroes);
            var4.setTextureDamage2Enables2(this.fzeroes);
            var4.setMatrixBlood1(this.fzeroes, this.fzeroes);
            var4.setMatrixBlood2(this.fzeroes, this.fzeroes);
            var4.setTextureRustA(0.0F);
            var4.setTexturePainColor(this.paintColor, 1.0F);
            var4.setTransformMatrix(this.IDENTITY.identity(), false);
            var2.Mesh.Draw(var4);
            var4.End();
         } else if (var4 != nullptr && var2.Mesh != nullptr && var2.Mesh.isReady()) {
            GL11.glDepthFunc(513);
            GL11.glDepthMask(true);
            GL11.glDepthRange(0.0, 1.0);
            GL11.glEnable(2929);
            GL11.glColor3f(1.0F, 1.0F, 1.0F);
            var4.Start();
            if (var2.tex != nullptr) {
               var4.setTexture(var2.tex, "Texture", 0);
            }

            var4.setDepthBias(0.0F);
            var4.setAmbient(1.0F);
            var4.setLightingAmount(1.0F);
            var4.setHueShift(0.0F);
            var4.setTint(1.0F, 1.0F, 1.0F);
            var4.setAlpha(1.0F);

            for (int var5 = 0; var5 < 5; var5++) {
               var4.setLight(var5, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, 0.0F, 0.0F, 0.0F, nullptr);
            }

            var4.setTransformMatrix(this.IDENTITY.identity(), false);
            var2.Mesh.Draw(var4);
            var4.End();
         }

         ModelCamera.instance.End();
         this.bRendered = true;
      }
   }

    void postRender() {
   }
}
} // namespace vehicles
} // namespace zombie
