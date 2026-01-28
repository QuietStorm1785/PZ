#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector4f.h"
#include <GL/glew.h>
#include <GL/glew.h>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/iso/sprite/SkyBox.h"

namespace zombie {
namespace iso {


class PuddlesShader : public Shader {
public:
    int WaterGroundTex;
    int PuddlesHM;
    int WaterTextureReflectionA;
    int WaterTextureReflectionB;
    int WaterTime;
    int WaterOffset;
    int WaterViewport;
    int WaterReflectionParam;
    int PuddlesParams;

    public PuddlesShader(const std::string& var1) {
      super(var1);
   }

    void onCompileSuccess(ShaderProgram var1) {
    int var2 = var1.getShaderID();
      this.WaterGroundTex = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterGroundTex");
      this.WaterTextureReflectionA = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterTextureReflectionA");
      this.WaterTextureReflectionB = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterTextureReflectionB");
      this.PuddlesHM = ARBShaderObjects.glGetUniformLocationARB(var2, "PuddlesHM");
      this.WaterTime = ARBShaderObjects.glGetUniformLocationARB(var2, "WTime");
      this.WaterOffset = ARBShaderObjects.glGetUniformLocationARB(var2, "WOffset");
      this.WaterViewport = ARBShaderObjects.glGetUniformLocationARB(var2, "WViewport");
      this.WaterReflectionParam = ARBShaderObjects.glGetUniformLocationARB(var2, "WReflectionParam");
      this.PuddlesParams = ARBShaderObjects.glGetUniformLocationARB(var2, "PuddlesParams");
      this.Start();
      if (this.WaterGroundTex != -1) {
         ARBShaderObjects.glUniform1iARB(this.WaterGroundTex, 0);
      }

      if (this.WaterTextureReflectionA != -1) {
         ARBShaderObjects.glUniform1iARB(this.WaterTextureReflectionA, 1);
      }

      if (this.WaterTextureReflectionB != -1) {
         ARBShaderObjects.glUniform1iARB(this.WaterTextureReflectionB, 2);
      }

      if (this.PuddlesHM != -1) {
         ARBShaderObjects.glUniform1iARB(this.PuddlesHM, 3);
      }

      this.End();
   }

    void updatePuddlesParams(int var1, int var2) {
    IsoPuddles var3 = IsoPuddles.getInstance();
    SkyBox var4 = SkyBox.getInstance();
    PlayerCamera var5 = SpriteRenderer.instance.getRenderingPlayerCamera(var1);
      GL13.glActiveTexture(33985);
      var4.getTextureCurrent().bind();
      GL11.glTexParameteri(3553, 10240, 9729);
      GL11.glTexParameteri(3553, 10241, 9729);
      GL11.glTexEnvi(8960, 8704, 7681);
      GL13.glActiveTexture(33986);
      var4.getTexturePrev().bind();
      GL11.glTexParameteri(3553, 10240, 9729);
      GL11.glTexParameteri(3553, 10241, 9729);
      GL11.glTexEnvi(8960, 8704, 7681);
      GL13.glActiveTexture(33987);
      var3.getHMTexture().bind();
      GL11.glTexParameteri(3553, 10240, 9729);
      GL11.glTexParameteri(3553, 10241, 9729);
      GL11.glTexEnvi(8960, 8704, 7681);
      ARBShaderObjects.glUniform1fARB(this.WaterTime, var3.getShaderTime());
    Vector4f var6 = var3.getShaderOffset();
      ARBShaderObjects.glUniform4fARB(this.WaterOffset, var6.x - 90000.0F, var6.y - 640000.0F, var6.z, var6.w);
      ARBShaderObjects.glUniform4fARB(
         this.WaterViewport,
         IsoCamera.getOffscreenLeft(var1),
         IsoCamera.getOffscreenTop(var1),
         var5.OffscreenWidth / var5.zoom,
         var5.OffscreenHeight / var5.zoom
      );
      ARBShaderObjects.glUniform1fARB(this.WaterReflectionParam, var4.getTextureShift());
      ARBShaderObjects.glUniformMatrix4fvARB(this.PuddlesParams, true, var3.getPuddlesParams(var2));
   }
}
} // namespace iso
} // namespace zombie
