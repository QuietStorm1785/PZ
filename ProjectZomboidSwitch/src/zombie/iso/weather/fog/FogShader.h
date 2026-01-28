#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/IndieGL.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fog {


class FogShader {
public:
    static const FogShader instance = std::make_shared<FogShader>();
    ShaderProgram shaderProgram;
    int noiseTexture;
    int screenInfo;
    int textureInfo;
    int rectangleInfo;
    int worldOffset;
    int scalingInfo;
    int colorInfo;
    int paramInfo;
    int cameraInfo;

    void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("fog", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.noiseTexture = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "NoiseTexture");
         this.screenInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "screenInfo");
         this.textureInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "textureInfo");
         this.rectangleInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "rectangleInfo");
         this.scalingInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "scalingInfo");
         this.colorInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "colorInfo");
         this.worldOffset = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "worldOffset");
         this.paramInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "paramInfo");
         this.cameraInfo = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "cameraInfo");
         ARBShaderObjects.glUseProgramObjectARB(this.shaderProgram.getShaderID());
         ARBShaderObjects.glUseProgramObjectARB(0);
      }
   }

    void setScreenInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.screenInfo, var1, var2, var3, var4);
   }

    void setTextureInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.textureInfo, var1, var2, var3, var4);
   }

    void setRectangleInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.rectangleInfo, var1, var2, var3, var4);
   }

    void setScalingInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.scalingInfo, var1, var2, var3, var4);
   }

    void setColorInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.colorInfo, var1, var2, var3, var4);
   }

    void setWorldOffset(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.worldOffset, var1, var2, var3, var4);
   }

    void setParamInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.paramInfo, var1, var2, var3, var4);
   }

    void setCameraInfo(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.cameraInfo, var1, var2, var3, var4);
   }

    bool StartShader() {
      if (this.shaderProgram == nullptr) {
         RenderThread.invokeOnRenderContext(this::initShader);
      }

      if (this.shaderProgram.isCompiled()) {
         IndieGL.StartShader(this.shaderProgram.getShaderID(), 0);
    return true;
      } else {
    return false;
      }
   }

    void reloadShader() {
      if (this.shaderProgram != nullptr) {
         this.shaderProgram = nullptr;
      }
   }
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
