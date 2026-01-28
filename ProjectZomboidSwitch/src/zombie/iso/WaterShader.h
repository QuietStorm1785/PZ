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
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/iso/sprite/SkyBox.h"

namespace zombie {
namespace iso {


class WaterShader : public Shader {
public:
    int WaterGroundTex;
    int WaterTextureReflectionA;
    int WaterTextureReflectionB;
    int WaterTime;
    int WaterOffset;
    int WaterViewport;
    int WaterReflectionParam;
    int WaterParamWind;
    int WaterParamWindSpeed;
    int WaterParamRainIntensity;

    public WaterShader(const std::string& var1) {
      super(var1);
   }

    void onCompileSuccess(ShaderProgram var1) {
    int var2 = var1.getShaderID();
      this.WaterGroundTex = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterGroundTex");
      this.WaterTextureReflectionA = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterTextureReflectionA");
      this.WaterTextureReflectionB = ARBShaderObjects.glGetUniformLocationARB(var2, "WaterTextureReflectionB");
      this.WaterTime = ARBShaderObjects.glGetUniformLocationARB(var2, "WTime");
      this.WaterOffset = ARBShaderObjects.glGetUniformLocationARB(var2, "WOffset");
      this.WaterViewport = ARBShaderObjects.glGetUniformLocationARB(var2, "WViewport");
      this.WaterReflectionParam = ARBShaderObjects.glGetUniformLocationARB(var2, "WReflectionParam");
      this.WaterParamWind = ARBShaderObjects.glGetUniformLocationARB(var2, "WParamWind");
      this.WaterParamWindSpeed = ARBShaderObjects.glGetUniformLocationARB(var2, "WParamWindSpeed");
      this.WaterParamRainIntensity = ARBShaderObjects.glGetUniformLocationARB(var2, "WParamRainIntensity");
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

      this.End();
   }

    void startMainThread(TextureDraw var1, int var2) {
    IsoWater var3 = IsoWater.getInstance();
    SkyBox var4 = SkyBox.getInstance();
      var1.u0 = var3.getWaterWindX();
      var1.u1 = var3.getWaterWindY();
      var1.u2 = var3.getWaterWindSpeed();
      var1.u3 = IsoPuddles.getInstance().getRainIntensity();
      var1.v0 = var3.getShaderTime();
      var1.v1 = var4.getTextureShift();
   }

    void updateWaterParams(TextureDraw var1, int var2) {
    IsoWater var3 = IsoWater.getInstance();
    SkyBox var4 = SkyBox.getInstance();
    PlayerCamera var5 = SpriteRenderer.instance.getRenderingPlayerCamera(var2);
      GL13.glActiveTexture(33984);
      var3.getTextureBottom().bind();
      GL11.glTexEnvi(8960, 8704, 7681);
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
      ARBShaderObjects.glUniform1fARB(this.WaterTime, var1.v0);
    Vector4f var6 = var3.getShaderOffset();
      ARBShaderObjects.glUniform4fARB(this.WaterOffset, var6.x - 90000.0F, var6.y - 640000.0F, var6.z, var6.w);
      ARBShaderObjects.glUniform4fARB(
         this.WaterViewport,
         IsoCamera.getOffscreenLeft(var2),
         IsoCamera.getOffscreenTop(var2),
         var5.OffscreenWidth / var5.zoom,
         var5.OffscreenHeight / var5.zoom
      );
      ARBShaderObjects.glUniform1fARB(this.WaterReflectionParam, var1.v1);
      ARBShaderObjects.glUniform2fARB(this.WaterParamWind, var1.u0, var1.u1);
      ARBShaderObjects.glUniform1fARB(this.WaterParamWindSpeed, var1.u2);
      ARBShaderObjects.glUniform1fARB(this.WaterParamRainIntensity, var1.u3);
   }
}
} // namespace iso
} // namespace zombie
