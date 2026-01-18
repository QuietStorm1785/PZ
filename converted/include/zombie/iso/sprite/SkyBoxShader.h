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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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

 public SkyBoxShader(const std::string& string) {
 super(string);
 }

 void startRenderThread(TextureDraw var1) {
 SkyBox skyBox = SkyBox.getInstance();
 ARBShaderObjects.glUniform1fARB(this->SkyBoxTime, skyBox.getShaderTime());
 ARBShaderObjects.glUniform1fARB(this->SkyBoxParamCloudCount, skyBox.getShaderCloudCount());
 ARBShaderObjects.glUniform1fARB(this->SkyBoxParamCloudSize, skyBox.getShaderCloudSize());
 ARBShaderObjects.glUniform3fARB(this->SkyBoxParamSunLight, skyBox.getShaderSunLight().x, skyBox.getShaderSunLight().y, skyBox.getShaderSunLight().z);
 ARBShaderObjects.glUniform3fARB(this->SkyBoxParamSunColor, skyBox.getShaderSunColor().r, skyBox.getShaderSunColor().g, skyBox.getShaderSunColor().b);
 ARBShaderObjects.glUniform3fARB(
 this->SkyBoxParamSkyHColour, skyBox.getShaderSkyHColour().r, skyBox.getShaderSkyHColour().g, skyBox.getShaderSkyHColour().b
 );
 ARBShaderObjects.glUniform3fARB(
 this->SkyBoxParamSkyLColour, skyBox.getShaderSkyLColour().r, skyBox.getShaderSkyLColour().g, skyBox.getShaderSkyLColour().b
 );
 ARBShaderObjects.glUniform1fARB(this->SkyBoxParamCloudLight, skyBox.getShaderCloudLight());
 ARBShaderObjects.glUniform1fARB(this->SkyBoxParamStars, skyBox.getShaderStars());
 ARBShaderObjects.glUniform1fARB(this->SkyBoxParamFog, skyBox.getShaderFog());
 ARBShaderObjects.glUniform3fARB(this->SkyBoxParamWind, skyBox.getShaderWind().x, skyBox.getShaderWind().y, skyBox.getShaderWind().z);
 }

 void onCompileSuccess(ShaderProgram var1) {
 int int0 = this->getID();
 this->SkyBoxTime = ARBShaderObjects.glGetUniformLocationARB(int0, "SBTime");
 this->SkyBoxParamCloudCount = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamCloudCount");
 this->SkyBoxParamCloudSize = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamCloudSize");
 this->SkyBoxParamSunLight = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamSunLight");
 this->SkyBoxParamSunColor = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamSunColour");
 this->SkyBoxParamSkyHColour = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamSkyHColour");
 this->SkyBoxParamSkyLColour = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamSkyLColour");
 this->SkyBoxParamCloudLight = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamCloudLight");
 this->SkyBoxParamStars = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamStars");
 this->SkyBoxParamFog = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamFog");
 this->SkyBoxParamWind = ARBShaderObjects.glGetUniformLocationARB(int0, "SBParamWind");
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
