#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Math.h"
#include "org/joml/Vector4f.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/EffectLight.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/model/ModelSlotRenderData.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace shader {


class Shader {
public:
    int HueChange;
    int LightingAmount;
    int MirrorXID;
    int TransformMatrixID = 0;
    const std::string name;
    const ShaderProgram m_shaderProgram;
    int MatrixID = 0;
    int Light0Direction;
    int Light0Colour;
    int Light1Direction;
    int Light1Colour;
    int Light2Direction;
    int Light2Colour;
    int Light3Direction;
    int Light3Colour;
    int Light4Direction;
    int Light4Colour;
    int TintColour;
    int Texture0;
    int TexturePainColor;
    int TextureRust;
    int TextureRustA;
    int TextureMask;
    int TextureLights;
    int TextureDamage1Overlay;
    int TextureDamage1Shell;
    int TextureDamage2Overlay;
    int TextureDamage2Shell;
    int TextureUninstall1;
    int TextureUninstall2;
    int TextureLightsEnables1;
    int TextureLightsEnables2;
    int TextureDamage1Enables1;
    int TextureDamage1Enables2;
    int TextureDamage2Enables1;
    int TextureDamage2Enables2;
    int MatBlood1Enables1;
    int MatBlood1Enables2;
    int MatBlood2Enables1;
    int MatBlood2Enables2;
    int Alpha;
    int TextureReflectionA;
    int TextureReflectionB;
    int ReflectionParam;
    int BoneIndicesAttrib;
    int BoneWeightsAttrib;
    int UVScale;
    const bool bStatic;
    static FloatBuffer floatBuffer;
    static const int MAX_BONES = 64;
    static const Vector3f tempVec3f = std::make_shared<Vector3f>();
    const FloatBuffer floatBuffer2 = BufferUtils.createFloatBuffer(16);

    public Shader(const std::string& var1, bool var2) {
      this.name = var1;
      this.m_shaderProgram = ShaderProgram.createShaderProgram(var1, var2, false);
      this.m_shaderProgram.addCompileListener(this::onProgramCompiled);
      this.bStatic = var2;
      this.compile();
   }

    bool isStatic() {
      return this.bStatic;
   }

    ShaderProgram getShaderProgram() {
      return this.m_shaderProgram;
   }

    void onProgramCompiled(ShaderProgram var1) {
      this.Start();
    int var2 = this.m_shaderProgram.getShaderID();
      if (!this.bStatic) {
         this.MatrixID = ARBShaderObjects.glGetUniformLocationARB(var2, "MatrixPalette");
      } else {
         this.TransformMatrixID = ARBShaderObjects.glGetUniformLocationARB(var2, "transform");
      }

      this.HueChange = ARBShaderObjects.glGetUniformLocationARB(var2, "HueChange");
      this.LightingAmount = ARBShaderObjects.glGetUniformLocationARB(var2, "LightingAmount");
      this.Light0Colour = ARBShaderObjects.glGetUniformLocationARB(var2, "Light0Colour");
      this.Light0Direction = ARBShaderObjects.glGetUniformLocationARB(var2, "Light0Direction");
      this.Light1Colour = ARBShaderObjects.glGetUniformLocationARB(var2, "Light1Colour");
      this.Light1Direction = ARBShaderObjects.glGetUniformLocationARB(var2, "Light1Direction");
      this.Light2Colour = ARBShaderObjects.glGetUniformLocationARB(var2, "Light2Colour");
      this.Light2Direction = ARBShaderObjects.glGetUniformLocationARB(var2, "Light2Direction");
      this.Light3Colour = ARBShaderObjects.glGetUniformLocationARB(var2, "Light3Colour");
      this.Light3Direction = ARBShaderObjects.glGetUniformLocationARB(var2, "Light3Direction");
      this.Light4Colour = ARBShaderObjects.glGetUniformLocationARB(var2, "Light4Colour");
      this.Light4Direction = ARBShaderObjects.glGetUniformLocationARB(var2, "Light4Direction");
      this.TintColour = ARBShaderObjects.glGetUniformLocationARB(var2, "TintColour");
      this.Texture0 = ARBShaderObjects.glGetUniformLocationARB(var2, "Texture0");
      this.TexturePainColor = ARBShaderObjects.glGetUniformLocationARB(var2, "TexturePainColor");
      this.TextureRust = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureRust");
      this.TextureMask = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureMask");
      this.TextureLights = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureLights");
      this.TextureDamage1Overlay = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage1Overlay");
      this.TextureDamage1Shell = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage1Shell");
      this.TextureDamage2Overlay = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage2Overlay");
      this.TextureDamage2Shell = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage2Shell");
      this.TextureRustA = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureRustA");
      this.TextureUninstall1 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureUninstall1");
      this.TextureUninstall2 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureUninstall2");
      this.TextureLightsEnables1 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureLightsEnables1");
      this.TextureLightsEnables2 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureLightsEnables2");
      this.TextureDamage1Enables1 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage1Enables1");
      this.TextureDamage1Enables2 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage1Enables2");
      this.TextureDamage2Enables1 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage2Enables1");
      this.TextureDamage2Enables2 = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureDamage2Enables2");
      this.MatBlood1Enables1 = ARBShaderObjects.glGetUniformLocationARB(var2, "MatBlood1Enables1");
      this.MatBlood1Enables2 = ARBShaderObjects.glGetUniformLocationARB(var2, "MatBlood1Enables2");
      this.MatBlood2Enables1 = ARBShaderObjects.glGetUniformLocationARB(var2, "MatBlood2Enables1");
      this.MatBlood2Enables2 = ARBShaderObjects.glGetUniformLocationARB(var2, "MatBlood2Enables2");
      this.Alpha = ARBShaderObjects.glGetUniformLocationARB(var2, "Alpha");
      this.TextureReflectionA = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureReflectionA");
      this.TextureReflectionB = ARBShaderObjects.glGetUniformLocationARB(var2, "TextureReflectionB");
      this.ReflectionParam = ARBShaderObjects.glGetUniformLocationARB(var2, "ReflectionParam");
      this.UVScale = ARBShaderObjects.glGetUniformLocationARB(var2, "UVScale");
      this.m_shaderProgram.setSamplerUnit("Texture", 0);
      if (this.Texture0 != -1) {
         ARBShaderObjects.glUniform1iARB(this.Texture0, 0);
      }

      if (this.TextureRust != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureRust, 1);
      }

      if (this.TextureMask != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureMask, 2);
      }

      if (this.TextureLights != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureLights, 3);
      }

      if (this.TextureDamage1Overlay != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureDamage1Overlay, 4);
      }

      if (this.TextureDamage1Shell != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureDamage1Shell, 5);
      }

      if (this.TextureDamage2Overlay != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureDamage2Overlay, 6);
      }

      if (this.TextureDamage2Shell != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureDamage2Shell, 7);
      }

      if (this.TextureReflectionA != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureReflectionA, 8);
      }

      if (this.TextureReflectionB != -1) {
         ARBShaderObjects.glUniform1iARB(this.TextureReflectionB, 9);
      }

      this.MirrorXID = ARBShaderObjects.glGetUniformLocationARB(var2, "MirrorX");
      this.BoneIndicesAttrib = GL20.glGetAttribLocation(var2, "boneIndices");
      this.BoneWeightsAttrib = GL20.glGetAttribLocation(var2, "boneWeights");
      this.End();
   }

    void compile() {
      this.m_shaderProgram.compile();
   }

    void setTexture(Texture var1, const std::string& var2, int var3) {
      this.m_shaderProgram.setValue(var2, var1, var3);
   }

    void setUVScale(float var1, float var2) {
      if (this.UVScale > 0) {
         this.m_shaderProgram.setVector2(this.UVScale, var1, var2);
      }
   }

    int getID() {
      return this.m_shaderProgram.getShaderID();
   }

    void Start() {
      this.m_shaderProgram.Start();
   }

    void End() {
      this.m_shaderProgram.End();
   }

    void startCharacter(ModelSlotRenderData var1, ModelInstanceRenderData var2) {
      if (this.bStatic) {
         this.setTransformMatrix(var2.xfrm, true);
      } else {
         this.setMatrixPalette(var2.matrixPalette);
      }

    float var3 = var1.ambientR * 0.45F;
    float var4 = var1.ambientG * 0.45F;
    float var5 = var1.ambientB * 0.45F;
      this.setLights(var1, 5);
    Texture var6 = var2.tex != nullptr ? var2.tex : var2.model.tex;
      if (DebugOptions.instance.IsoSprite.CharacterMipmapColors.getValue()) {
    Texture var7 = dynamic_cast<SmartTexture*>(var6) != nullptr ? ((SmartTexture)var6).result : var6;
         if (var7 != nullptr && var7.getTextureId() != nullptr && var7.getTextureId().hasMipMaps()) {
            var6 = Texture.getEngineMipmapTexture();
         }
      }

      this.setTexture(var6, "Texture", 0);
      this.setDepthBias(var2.depthBias / 50.0F);
      this.setAmbient(var3, var4, var5);
      this.setLightingAmount(1.0F);
      this.setHueShift(var2.hue);
      this.setTint(var2.tintR, var2.tintG, var2.tintB);
      this.setAlpha(var1.alpha);
   }

    void setLights(ModelSlotRenderData var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
    EffectLight var4 = var1.effectLights[var3];
         if (GameServer.bServer && ServerGUI.isCreated()) {
            var4.r = var4.g = var4.b = 1.0F;
         }

         this.setLight(var3, var4.x, var4.y, var4.z, var4.r, var4.g, var4.b, var4.radius, var1.animPlayerAngle, var1.x, var1.y, var1.z, var1.object);
      }
   }

    void updateAlpha(IsoGameCharacter var1, int var2) {
      if (var1 != nullptr) {
         this.setAlpha(var1.getAlpha(var2));
      }
   }

    void setAlpha(float var1) {
      ARBShaderObjects.glUniform1fARB(this.Alpha, var1);
   }

    void updateParams() {
   }

    void setMatrixPalette(Matrix4f[] var1) {
      if (!this.bStatic) {
         if (floatBuffer == nullptr) {
            floatBuffer = BufferUtils.createFloatBuffer(1024);
         }

         floatBuffer.clear();

    for (auto& var5 : var1)            var5.store(floatBuffer);
         }

         floatBuffer.flip();
         ARBShaderObjects.glUniformMatrix4fvARB(this.MatrixID, true, floatBuffer);
      }
   }

    void setMatrixPalette(FloatBuffer var1) {
      this.setMatrixPalette(var1, true);
   }

    void setMatrixPalette(FloatBuffer var1, bool var2) {
      if (!this.bStatic) {
         ARBShaderObjects.glUniformMatrix4fvARB(this.MatrixID, var2, var1);
      }
   }

    void setMatrixPalette(org.joml.Matrix4f[] var1) {
      if (!this.bStatic) {
         if (floatBuffer == nullptr) {
            floatBuffer = BufferUtils.createFloatBuffer(1024);
         }

         floatBuffer.clear();

         for (org.joml.Matrix4f var5 : var1) {
            var5.get(floatBuffer);
            floatBuffer.position(floatBuffer.position() + 16);
         }

         floatBuffer.flip();
         ARBShaderObjects.glUniformMatrix4fvARB(this.MatrixID, true, floatBuffer);
      }
   }

    void setTint(float var1, float var2, float var3) {
      ARBShaderObjects.glUniform3fARB(this.TintColour, var1, var2, var3);
   }

    void setTextureRustA(float var1) {
      ARBShaderObjects.glUniform1fARB(this.TextureRustA, var1);
   }

    void setTexturePainColor(float var1, float var2, float var3, float var4) {
      ARBShaderObjects.glUniform4fARB(this.TexturePainColor, var1, var2, var3, var4);
   }

    void setTexturePainColor(org.joml.Vector3f var1, float var2) {
      ARBShaderObjects.glUniform4fARB(this.TexturePainColor, var1.x(), var1.y(), var1.z(), var2);
   }

    void setTexturePainColor(Vector4f var1) {
      ARBShaderObjects.glUniform4fARB(this.TexturePainColor, var1.x(), var1.y(), var1.z(), var1.w());
   }

    void setReflectionParam(float var1, float var2, float var3) {
      ARBShaderObjects.glUniform3fARB(this.ReflectionParam, var1, var2, var3);
   }

    void setTextureUninstall1(float[] var1) {
      this.setMatrix(this.TextureUninstall1, var1);
   }

    void setTextureUninstall2(float[] var1) {
      this.setMatrix(this.TextureUninstall2, var1);
   }

    void setTextureLightsEnables1(float[] var1) {
      this.setMatrix(this.TextureLightsEnables1, var1);
   }

    void setTextureLightsEnables2(float[] var1) {
      this.setMatrix(this.TextureLightsEnables2, var1);
   }

    void setTextureDamage1Enables1(float[] var1) {
      this.setMatrix(this.TextureDamage1Enables1, var1);
   }

    void setTextureDamage1Enables2(float[] var1) {
      this.setMatrix(this.TextureDamage1Enables2, var1);
   }

    void setTextureDamage2Enables1(float[] var1) {
      this.setMatrix(this.TextureDamage2Enables1, var1);
   }

    void setTextureDamage2Enables2(float[] var1) {
      this.setMatrix(this.TextureDamage2Enables2, var1);
   }

    void setMatrixBlood1(float[] var1, float[] var2) {
      if (this.MatBlood1Enables1 != -1 && this.MatBlood1Enables2 != -1) {
         this.setMatrix(this.MatBlood1Enables1, var1);
         this.setMatrix(this.MatBlood1Enables2, var2);
      }
   }

    void setMatrixBlood2(float[] var1, float[] var2) {
      if (this.MatBlood2Enables1 != -1 && this.MatBlood2Enables2 != -1) {
         this.setMatrix(this.MatBlood2Enables1, var1);
         this.setMatrix(this.MatBlood2Enables2, var2);
      }
   }

    void setShaderAlpha(float var1) {
      ARBShaderObjects.glUniform1fARB(this.Alpha, var1);
   }

    void setLight(int var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, ModelInstance var10) {
    float var11 = 0.0F;
    float var12 = 0.0F;
    float var13 = 0.0F;
    IsoMovingObject var14 = var10.object;
      if (var14 != nullptr) {
         var11 = var14.x;
         var12 = var14.y;
         var13 = var14.z;
      }

      this.setLight(var1, var2, var3, var4, var5, var6, var7, var8, var9, var11, var12, var13, var14);
   }

   public void setLight(
      int var1,
      float var2,
      float var3,
      float var4,
      float var5,
      float var6,
      float var7,
      float var8,
      float var9,
      float var10,
      float var11,
      float var12,
      IsoMovingObject var13
   ) {
      PZGLUtil.checkGLError(true);
    int var14 = this.Light0Direction;
    int var15 = this.Light0Colour;
      if (var1 == 1) {
         var14 = this.Light1Direction;
         var15 = this.Light1Colour;
      }

      if (var1 == 2) {
         var14 = this.Light2Direction;
         var15 = this.Light2Colour;
      }

      if (var1 == 3) {
         var14 = this.Light3Direction;
         var15 = this.Light3Colour;
      }

      if (var1 == 4) {
         var14 = this.Light4Direction;
         var15 = this.Light4Colour;
      }

      if (var5 + var6 + var7 != 0.0F && !(var8 <= 0.0F)) {
    Vector3f var16 = tempVec3f;
         if (!float.isNaN(var9)) {
            var16.set(var2, var3, var4);
            var16.x -= var10;
            var16.y -= var11;
            var16.z -= var12;
         } else {
            var16.set(var2, var3, var4);
         }

    float var17 = var16.length();
         if (var17 < 1.0E-4F) {
            var16.set(0.0F, 0.0F, 1.0F);
         } else {
            var16.normalise();
         }

         if (!float.isNaN(var9)) {
    float var18 = -var9;
    float var19 = var16.x;
    float var20 = var16.y;
            var16.x = var19 * Math.cos(var18) - var20 * Math.sin(var18);
            var16.y = var19 * Math.sin(var18) + var20 * Math.cos(var18);
         }

    float var27 = var16.y;
         var16.y = var16.z;
         var16.z = var27;
         if (var16.length() < 1.0E-4F) {
            var16.set(0.0F, 1.0F, 0.0F);
         }

         var16.normalise();
    float var28 = 1.0F - var17 / var8;
         if (var28 < 0.0F) {
            var28 = 0.0F;
         }

         if (var28 > 1.0F) {
            var28 = 1.0F;
         }

         var5 *= var28;
         var6 *= var28;
         var7 *= var28;
         var5 = PZMath.clamp(var5, 0.0F, 1.0F);
         var6 = PZMath.clamp(var6, 0.0F, 1.0F);
         var7 = PZMath.clamp(var7, 0.0F, 1.0F);
         if (dynamic_cast<BaseVehicle*>(var13) != nullptr) {
            this.doVector3(var14, -var16.x, var16.y, var16.z);
         } else {
            this.doVector3(var14, -var16.x, var16.y, var16.z);
         }

         if (dynamic_cast<IsoPlayer*>(var13) != nullptr) {
    bool var29 = false;
         }

         this.doVector3(var15, var5, var6, var7);
         PZGLUtil.checkGLErrorThrow("Shader.setLightInternal.", new Object[0]);
      } else {
         this.doVector3(var14, 0.0F, 1.0F, 0.0F);
         this.doVector3(var15, 0.0F, 0.0F, 0.0F);
      }
   }

    void doVector3(int var1, float var2, float var3, float var4) {
      this.m_shaderProgram.setVector3(var1, var2, var3, var4);
   }

    void setHueShift(float var1) {
      if (this.HueChange > 0) {
         this.m_shaderProgram.setValue("HueChange", var1);
      }
   }

    void setLightingAmount(float var1) {
      if (this.LightingAmount > 0) {
         this.m_shaderProgram.setValue("LightingAmount", var1);
      }
   }

    void setDepthBias(float var1) {
      this.m_shaderProgram.setValue("DepthBias", var1 / 300.0F);
   }

    void setAmbient(float var1) {
      this.m_shaderProgram.setVector3("AmbientColour", var1, var1, var1);
   }

    void setAmbient(float var1, float var2, float var3) {
      this.m_shaderProgram.setVector3("AmbientColour", var1, var2, var3);
   }

    void setTransformMatrix(Matrix4f var1, bool var2) {
      if (floatBuffer == nullptr) {
         floatBuffer = BufferUtils.createFloatBuffer(1024);
      }

      floatBuffer.clear();
      var1.store(floatBuffer);
      floatBuffer.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(this.TransformMatrixID, var2, floatBuffer);
   }

    void setTransformMatrix(org.joml.Matrix4f var1, bool var2) {
      this.floatBuffer2.clear();
      var1.get(this.floatBuffer2);
      this.floatBuffer2.position(16);
      this.floatBuffer2.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(this.TransformMatrixID, var2, this.floatBuffer2);
   }

    void setMatrix(int var1, org.joml.Matrix4f var2) {
      this.floatBuffer2.clear();
      var2.get(this.floatBuffer2);
      this.floatBuffer2.position(16);
      this.floatBuffer2.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(var1, true, this.floatBuffer2);
   }

    void setMatrix(int var1, float[] var2) {
      this.floatBuffer2.clear();
      this.floatBuffer2.put(var2);
      this.floatBuffer2.flip();
      ARBShaderObjects.glUniformMatrix4fvARB(var1, true, this.floatBuffer2);
   }

    bool isVehicleShader() {
      return this.TextureRust != -1;
   }
}
} // namespace shader
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
