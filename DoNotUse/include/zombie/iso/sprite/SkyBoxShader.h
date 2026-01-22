#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureDraw.h"

namespace zombie {
namespace iso {
namespace sprite {


class SkyBoxShader : public Shader {
public:
    int SkyBoxTime;
    int SkyBoxParamCloudCount;
    int SkyBoxParamCloudSize;
    int SkyBoxParamSunLight;
    int SkyBoxParamSunColor;
    int SkyBoxParamSkyHColour;
    int SkyBoxParamSkyLColour;
    int SkyBoxParamCloudLight;
    int SkyBoxParamStars;
    int SkyBoxParamFog;
    int SkyBoxParamWind;

    public SkyBoxShader(const std::string& var1) {
      super(var1);
   }

    void startRenderThread(TextureDraw var1) {
    SkyBox var2 = SkyBox.getInstance();
      ARBShaderObjects.glUniform1fARB(this.SkyBoxTime, var2.getShaderTime());
      ARBShaderObjects.glUniform1fARB(this.SkyBoxParamCloudCount, var2.getShaderCloudCount());
      ARBShaderObjects.glUniform1fARB(this.SkyBoxParamCloudSize, var2.getShaderCloudSize());
      ARBShaderObjects.glUniform3fARB(this.SkyBoxParamSunLight, var2.getShaderSunLight().x, var2.getShaderSunLight().y, var2.getShaderSunLight().z);
      ARBShaderObjects.glUniform3fARB(this.SkyBoxParamSunColor, var2.getShaderSunColor().r, var2.getShaderSunColor().g, var2.getShaderSunColor().b);
      ARBShaderObjects.glUniform3fARB(this.SkyBoxParamSkyHColour, var2.getShaderSkyHColour().r, var2.getShaderSkyHColour().g, var2.getShaderSkyHColour().b);
      ARBShaderObjects.glUniform3fARB(this.SkyBoxParamSkyLColour, var2.getShaderSkyLColour().r, var2.getShaderSkyLColour().g, var2.getShaderSkyLColour().b);
      ARBShaderObjects.glUniform1fARB(this.SkyBoxParamCloudLight, var2.getShaderCloudLight());
      ARBShaderObjects.glUniform1fARB(this.SkyBoxParamStars, var2.getShaderStars());
      ARBShaderObjects.glUniform1fARB(this.SkyBoxParamFog, var2.getShaderFog());
      ARBShaderObjects.glUniform3fARB(this.SkyBoxParamWind, var2.getShaderWind().x, var2.getShaderWind().y, var2.getShaderWind().z);
   }

    void onCompileSuccess(ShaderProgram var1) {
    int var2 = this.getID();
      this.SkyBoxTime = ARBShaderObjects.glGetUniformLocationARB(var2, "SBTime");
      this.SkyBoxParamCloudCount = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamCloudCount");
      this.SkyBoxParamCloudSize = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamCloudSize");
      this.SkyBoxParamSunLight = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamSunLight");
      this.SkyBoxParamSunColor = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamSunColour");
      this.SkyBoxParamSkyHColour = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamSkyHColour");
      this.SkyBoxParamSkyLColour = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamSkyLColour");
      this.SkyBoxParamCloudLight = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamCloudLight");
      this.SkyBoxParamStars = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamStars");
      this.SkyBoxParamFog = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamFog");
      this.SkyBoxParamWind = ARBShaderObjects.glGetUniformLocationARB(var2, "SBParamWind");
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
