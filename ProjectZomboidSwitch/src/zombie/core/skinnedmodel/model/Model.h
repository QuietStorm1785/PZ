#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include <GL/glew.h>
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/GameProfiler.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/particle/MuzzleFlash.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/Model/ModelAssetParams.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/EffectLight.h"
#include "zombie/core/skinnedmodel/model/ModelMesh/MeshAssetParams.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/shader/ShaderManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class Model : public Asset {
public:
    std::string Name;
    const ModelMesh Mesh;
    Shader Effect;
    void* Tag;
    bool bStatic = false;
    Texture tex = nullptr;
    SoftwareModelMesh softwareMesh;
    static const FloatBuffer m_staticReusableFloatBuffer = BufferUtils.createFloatBuffer(128);
    static const Matrix4f IDENTITY = std::make_shared<Matrix4f>();
   public static const Color[] debugDrawColours = new Color[]{
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
    std::make_shared<Color>();
   };
    ModelAssetParams assetParams;
    static Vector3 tempo = std::make_shared<Vector3>();
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("Model");

    public Model(AssetPath var1, AssetManager var2, ModelAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
      this.bStatic = this.assetParams != nullptr && this.assetParams.bStatic;
    MeshAssetParams var4 = std::make_shared<MeshAssetParams>();
      var4.bStatic = this.bStatic;
      var4.animationsMesh = this.assetParams == nullptr ? nullptr : this.assetParams.animationsModel;
      this.Mesh = (ModelMesh)MeshAssetManager.instance.load(std::make_shared<AssetPath>(var3.meshName), var4);
      if (!StringUtils.isNullOrWhitespace(var3.textureName)) {
         if (var3.textureName.contains("media/")) {
            this.tex = Texture.getSharedTexture(var3.textureName, var3.textureFlags);
         } else {
            this.tex = Texture.getSharedTexture("media/textures/" + var3.textureName + ".png", var3.textureFlags);
         }
      }

      if (!StringUtils.isNullOrWhitespace(var3.shaderName)) {
         this.CreateShader(var3.shaderName);
      }

      this.onCreated(this.Mesh.getState());
      this.addDependency(this.Mesh);
      if (this.isReady()) {
         this.Tag = this.Mesh.skinningData;
         this.softwareMesh = this.Mesh.softwareMesh;
         this.assetParams = nullptr;
      }
   }

    static void VectorToWorldCoords(IsoGameCharacter var0, Vector3 var1) {
    AnimationPlayer var2 = var0.getAnimationPlayer();
    float var3 = var2.getRenderedAngle();
      var1.x = -var1.x;
      var1.rotatey(var3);
    float var4 = var1.y;
      var1.y = var1.z;
      var1.z = var4 * 0.6F;
      var1.x *= 1.5F;
      var1.y *= 1.5F;
      var1.x = var1.x + var0.x;
      var1.y = var1.y + var0.y;
      var1.z = var1.z + var0.z;
   }

    static void BoneToWorldCoords(IsoGameCharacter var0, int var1, Vector3 var2) {
    AnimationPlayer var3 = var0.getAnimationPlayer();
      var2.x = var3.modelTransforms[var1].m03;
      var2.y = var3.modelTransforms[var1].m13;
      var2.z = var3.modelTransforms[var1].m23;
      VectorToWorldCoords(var0, var2);
   }

    static void BoneYDirectionToWorldCoords(IsoGameCharacter var0, int var1, Vector3 var2, float var3) {
    AnimationPlayer var4 = var0.getAnimationPlayer();
      var2.x = var4.modelTransforms[var1].m01 * var3;
      var2.y = var4.modelTransforms[var1].m11 * var3;
      var2.z = var4.modelTransforms[var1].m21 * var3;
      var2.x = var2.x + var4.modelTransforms[var1].m03;
      var2.y = var2.y + var4.modelTransforms[var1].m13;
      var2.z = var2.z + var4.modelTransforms[var1].m23;
      VectorToWorldCoords(var0, var2);
   }

    static void VectorToWorldCoords(ModelSlotRenderData var0, Vector3 var1) {
    float var2 = var0.animPlayerAngle;
      var1.x = -var1.x;
      var1.rotatey(var2);
    float var3 = var1.y;
      var1.y = var1.z;
      var1.z = var3 * 0.6F;
      var1.x *= 1.5F;
      var1.y *= 1.5F;
      var1.x = var1.x + var0.x;
      var1.y = var1.y + var0.y;
      var1.z = var1.z + var0.z;
   }

    static void BoneToWorldCoords(ModelSlotRenderData var0, int var1, Vector3 var2) {
    AnimationPlayer var3 = var0.animPlayer;
      var2.x = var3.modelTransforms[var1].m03;
      var2.y = var3.modelTransforms[var1].m13;
      var2.z = var3.modelTransforms[var1].m23;
      VectorToWorldCoords(var0, var2);
   }

    static void CharacterModelCameraBegin(ModelSlotRenderData var0) {
      ModelCamera.instance.Begin();
      if (var0.bInVehicle) {
         GL11.glMatrixMode(5888);
         GL11.glTranslatef(0.0F, var0.centerOfMassY, 0.0F);
         GL11.glMatrixMode(5888);
         GL11.glRotatef(var0.vehicleAngleZ, 0.0F, 0.0F, 1.0F);
         GL11.glRotatef(var0.vehicleAngleY, 0.0F, 1.0F, 0.0F);
         GL11.glRotatef(var0.vehicleAngleX, 1.0F, 0.0F, 0.0F);
         GL11.glRotatef(180.0F, 0.0F, 1.0F, 0.0F);
    uint8_t var1 = -1;
         GL11.glTranslatef(var0.inVehicleX, var0.inVehicleY, var0.inVehicleZ * var1);
         GL11.glScalef(1.5F, 1.5F, 1.5F);
      }
   }

    static void CharacterModelCameraEnd() {
      ModelCamera.instance.End();
   }

    void DrawChar(ModelSlotRenderData var1, ModelInstanceRenderData var2) {
      if (!DebugOptions.instance.char.Debug.Render.SkipCharacters.getValue()) {
         if (var1.character == IsoPlayer.getInstance()) {
    bool var3 = false;
         }

         if (!(var1.alpha < 0.01F)) {
            if (var1.animPlayer != nullptr) {
               if (Core.bDebug && GameKeyboard.isKeyDown(199)) {
                  this.Effect = nullptr;
               }

               if (this.Effect == nullptr) {
                  this.CreateShader("basicEffect");
               }

    Shader var5 = this.Effect;
               GL11.glEnable(2884);
               GL11.glCullFace(1028);
               GL11.glEnable(2929);
               GL11.glEnable(3008);
               GL11.glDepthFunc(513);
               GL11.glAlphaFunc(516, 0.01F);
               GL11.glBlendFunc(770, 771);
               if (Core.bDebug && DebugOptions.instance.ModelRenderWireframe.getValue()) {
                  GL11.glPolygonMode(1032, 6913);
                  GL11.glEnable(2848);
                  GL11.glLineWidth(0.75F);
    Shader var4 = ShaderManager.instance.getOrCreateShader("vehicle_wireframe", this.bStatic);
                  if (var4 != nullptr) {
                     var4.Start();
                     if (this.bStatic) {
                        var4.setTransformMatrix(var2.xfrm, true);
                     } else {
                        var4.setMatrixPalette(var2.matrixPalette, true);
                     }

                     this.Mesh.Draw(var4);
                     var4.End();
                  }

                  GL11.glPolygonMode(1032, 6914);
                  GL11.glDisable(2848);
               } else {
                  if (var5 != nullptr) {
                     var5.Start();
                     var5.startCharacter(var1, var2);
                  }

                  if (!DebugOptions.instance.DebugDraw_SkipDrawNonSkinnedModel.getValue()) {
                     GameProfiler.getInstance().invokeAndMeasure("Mesh.Draw.Call", var5, this.Mesh, (var0, var1x) -> var1x.Draw(var0));
                  }

                  if (var5 != nullptr) {
                     var5.End();
                  }

                  this.drawMuzzleFlash(var2);
               }
            }
         }
      }
   }

    void drawMuzzleFlash(ModelInstanceRenderData var1) {
      if (var1.m_muzzleFlash) {
    ModelAttachment var2 = var1.modelInstance.getAttachmentById("muzzle");
         if (var2 != nullptr) {
    Matrix4fObjectPool var3 = (Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get();
    Matrix4f var4 = ((Matrix4f)var3.alloc()).set(var1.xfrm);
            var4.transpose();
    Matrix4f var5 = var1.modelInstance.getAttachmentMatrix(var2, (Matrix4f)var3.alloc());
            var4.mul(var5, var5);
            MuzzleFlash.render(var5);
            var3.release(var4);
            var3.release(var5);
         }
      }
   }

    void drawVehicleLights(ModelSlotRenderData var1) {
      for (int var2 = 7; var2 >= 0; var2--) {
         GL13.glActiveTexture(33984 + var2);
         GL11.glDisable(3553);
      }

      GL11.glLineWidth(1.0F);
      GL11.glColor3f(1.0F, 1.0F, 0.0F);
      GL11.glDisable(2929);

      for (int var8 = 0; var8 < 3; var8++) {
    EffectLight var3 = var1.effectLights[var8];
         if (!(var3.radius <= 0.0F)) {
    float var4 = var3.x;
    float var5 = var3.y;
    float var6 = var3.z;
            var4 *= -54.0F;
    float var10 = var6 * 54.0F;
            var6 = var5 * 54.0F;
            GL11.glBegin(1);
            GL11.glVertex3f(var4, var10, var6);
            GL11.glVertex3f(0.0F, 0.0F, 0.0F);
            GL11.glEnd();
         }
      }

      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glEnable(3553);
      GL11.glEnable(2929);
   }

    static void drawBoneMtx(org.lwjgl.util.vector.Matrix4f var0) {
      GL11.glDisable(2929);
      GL11.glDisable(3553);
      GL11.glBegin(1);
      drawBoneMtxInternal(var0);
      GL11.glEnd();
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glEnable(2929);
   }

    static void drawBoneMtxInternal(org.lwjgl.util.vector.Matrix4f var0) {
    float var1 = 0.5F;
    float var2 = 0.15F;
    float var3 = 0.1F;
    float var4 = var0.m03;
    float var5 = var0.m13;
    float var6 = var0.m23;
    float var7 = var0.m00;
    float var8 = var0.m10;
    float var9 = var0.m20;
    float var10 = var0.m01;
    float var11 = var0.m11;
    float var12 = var0.m21;
    float var13 = var0.m02;
    float var14 = var0.m12;
    float var15 = var0.m22;
      drawArrowInternal(var4, var5, var6, var7, var8, var9, var13, var14, var15, var1, var2, var3, 1.0F, 0.0F, 0.0F);
      drawArrowInternal(var4, var5, var6, var10, var11, var12, var13, var14, var15, var1, var2, var3, 0.0F, 1.0F, 0.0F);
      drawArrowInternal(var4, var5, var6, var13, var14, var15, var7, var8, var9, var1, var2, var3, 0.0F, 0.0F, 1.0F);
   }

   private static void drawArrowInternal(
      float var0,
      float var1,
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
      float var13,
      float var14
   ) {
    float var15 = 1.0F - var10;
      GL11.glColor3f(var12, var13, var14);
      GL11.glVertex3f(var0, var1, var2);
      GL11.glVertex3f(var0 + var3 * var9, var1 + var4 * var9, var2 + var5 * var9);
      GL11.glVertex3f(var0 + var3 * var9, var1 + var4 * var9, var2 + var5 * var9);
      GL11.glVertex3f(var0 + (var3 * var15 + var6 * var11) * var9, var1 + (var4 * var15 + var7 * var11) * var9, var2 + (var5 * var15 + var8 * var11) * var9);
      GL11.glVertex3f(var0 + var3 * var9, var1 + var4 * var9, var2 + var5 * var9);
      GL11.glVertex3f(var0 + (var3 * var15 - var6 * var11) * var9, var1 + (var4 * var15 - var7 * var11) * var9, var2 + (var5 * var15 - var8 * var11) * var9);
   }

    void debugDrawLightSource(IsoLightSource var1, float var2, float var3, float var4, float var5) {
      debugDrawLightSource(var1.x, var1.y, var1.z, var2, var3, var4, var5);
   }

    static void debugDrawLightSource(float var0, float var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = var0 - var3 + 0.5F;
    float var8 = var1 - var4 + 0.5F;
    float var9 = var2 - var5 + 0.0F;
      var7 *= 0.67F;
      var8 *= 0.67F;
    float var14 = (float)(var7 * Math.cos(var6) - var8 * Math.sin(var6));
      var8 = (float)(var7 * Math.sin(var6) + var8 * Math.cos(var6));
      var7 = var14 * -1.0F;
      GL11.glDisable(3553);
      GL11.glDisable(2929);
      GL11.glBegin(1);
      GL11.glColor3f(1.0F, 1.0F, 0.0F);
      GL11.glVertex3f(var7, var9, var8);
      GL11.glVertex3f(0.0F, 0.0F, 0.0F);
      GL11.glVertex3f(var7, var9, var8);
      GL11.glVertex3f(var7 + 0.1F, var9, var8);
      GL11.glVertex3f(var7, var9, var8);
      GL11.glVertex3f(var7, var9 + 0.1F, var8);
      GL11.glVertex3f(var7, var9, var8);
      GL11.glVertex3f(var7, var9, var8 + 0.1F);
      GL11.glEnd();
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glEnable(3553);
      GL11.glEnable(2929);
   }

    void DrawVehicle(ModelSlotRenderData var1, ModelInstanceRenderData var2) {
      if (!DebugOptions.instance.ModelRenderSkipVehicles.getValue()) {
    ModelInstance var3 = var2.modelInstance;
    float var4 = var1.ambientR;
    Texture var5 = var2.tex;
    float var6 = var2.tintR;
    float var7 = var2.tintG;
    float var8 = var2.tintB;
         PZGLUtil.checkGLErrorThrow("Model.drawVehicle Enter inst: %s, instTex: %s, slotData: %s", new Object[]{var3, var5, var1});
         GL11.glEnable(2884);
         GL11.glCullFace(var3.m_modelScript != nullptr && var3.m_modelScript.invertX ? 1029 : 1028);
         GL11.glEnable(2929);
         GL11.glDepthFunc(513);
         ModelCamera.instance.Begin();
         GL11.glMatrixMode(5888);
         GL11.glTranslatef(0.0F, var1.centerOfMassY, 0.0F);
    Shader var9 = this.Effect;
         PZGLUtil.pushAndMultMatrix(5888, var2.xfrm);
         if (Core.bDebug && DebugOptions.instance.ModelRenderWireframe.getValue()) {
            GL11.glPolygonMode(1032, 6913);
            GL11.glEnable(2848);
            GL11.glLineWidth(0.75F);
            var9 = ShaderManager.instance.getOrCreateShader("vehicle_wireframe", this.bStatic);
            if (var9 != nullptr) {
               var9.Start();
               if (this.bStatic) {
                  var9.setTransformMatrix(IDENTITY, false);
               } else {
                  var9.setMatrixPalette(var2.matrixPalette, true);
               }

               this.Mesh.Draw(var9);
               var9.End();
            }

            GL11.glDisable(2848);
            PZGLUtil.popMatrix(5888);
            ModelCamera.instance.End();
         } else {
            if (var9 != nullptr) {
               var9.Start();
               this.setLights(var1, 3);
               if (var9.isVehicleShader()) {
    VehicleModelInstance var10 = (VehicleModelInstance)Type.tryCastTo(var3, VehicleModelInstance.class);
                  if (dynamic_cast<VehicleSubModelInstance*>(var3) != nullptr) {
                     var10 = (VehicleModelInstance)Type.tryCastTo(var3.parent, VehicleModelInstance.class);
                  }

                  var9.setTexture(var10.tex, "Texture0", 0);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureRust, "TextureRust", 1);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureMask, "TextureMask", 2);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureLights, "TextureLights", 3);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureDamage1Overlay, "TextureDamage1Overlay", 4);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureDamage1Shell, "TextureDamage1Shell", 5);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureDamage2Overlay, "TextureDamage2Overlay", 6);
                  GL11.glTexEnvi(8960, 8704, 7681);
                  var9.setTexture(var10.textureDamage2Shell, "TextureDamage2Shell", 7);
                  GL11.glTexEnvi(8960, 8704, 7681);

                  try {
                     if (Core.getInstance().getPerfReflectionsOnLoad()) {
                        var9.setTexture((Texture)SkyBox.getInstance().getTextureCurrent(), "TextureReflectionA", 8);
                        GL11.glTexEnvi(8960, 8704, 7681);
                        GL11.glGetError();
                     }
                  } catch (Throwable var13) {
                  }

                  try {
                     if (Core.getInstance().getPerfReflectionsOnLoad()) {
                        var9.setTexture((Texture)SkyBox.getInstance().getTexturePrev(), "TextureReflectionB", 9);
                        GL11.glTexEnvi(8960, 8704, 7681);
                        GL11.glGetError();
                     }
                  } catch (Throwable var12) {
                  }

                  var9.setReflectionParam(SkyBox.getInstance().getTextureShift(), var10.refWindows, var10.refBody);
                  var9.setTextureUninstall1(var10.textureUninstall1);
                  var9.setTextureUninstall2(var10.textureUninstall2);
                  var9.setTextureLightsEnables1(var10.textureLightsEnables1);
                  var9.setTextureLightsEnables2(var10.textureLightsEnables2);
                  var9.setTextureDamage1Enables1(var10.textureDamage1Enables1);
                  var9.setTextureDamage1Enables2(var10.textureDamage1Enables2);
                  var9.setTextureDamage2Enables1(var10.textureDamage2Enables1);
                  var9.setTextureDamage2Enables2(var10.textureDamage2Enables2);
                  var9.setMatrixBlood1(var10.matrixBlood1Enables1, var10.matrixBlood1Enables2);
                  var9.setMatrixBlood2(var10.matrixBlood2Enables1, var10.matrixBlood2Enables2);
                  var9.setTextureRustA(var10.textureRustA);
                  var9.setTexturePainColor(var10.painColor, var1.alpha);
                  if (this.bStatic) {
                     var9.setTransformMatrix(IDENTITY, false);
                  } else {
                     var9.setMatrixPalette(var2.matrixPalette, true);
                  }
               } else if (dynamic_cast<VehicleSubModelInstance*>(var3) != nullptr) {
                  GL13.glActiveTexture(33984);
                  var9.setTexture(var5, "Texture", 0);
                  var9.setShaderAlpha(var1.alpha);
                  if (this.bStatic) {
                     var9.setTransformMatrix(IDENTITY, false);
                  }
               } else {
                  GL13.glActiveTexture(33984);
                  var9.setTexture(var5, "Texture", 0);
               }

               var9.setAmbient(var4);
               var9.setTint(var6, var7, var8);
               this.Mesh.Draw(var9);
               var9.End();
            }

            if (Core.bDebug && DebugOptions.instance.ModelRenderLights.getValue() && var2 == var1.modelData.get(0)) {
               this.drawVehicleLights(var1);
            }

            PZGLUtil.popMatrix(5888);
            ModelCamera.instance.End();
            PZGLUtil.checkGLErrorThrow("Model.drawVehicle Exit inst: %s, instTex: %s, slotData: %s", new Object[]{var3, var5, var1});
         }
      }
   }

    static void debugDrawAxis(float var0, float var1, float var2, float var3, float var4) {
      for (int var5 = 0; var5 < 8; var5++) {
         GL13.glActiveTexture(33984 + var5);
         GL11.glDisable(3553);
      }

      GL11.glDisable(2929);
      GL11.glLineWidth(var4);
      GL11.glBegin(1);
      GL11.glColor3f(1.0F, 0.0F, 0.0F);
      GL11.glVertex3f(var0, var1, var2);
      GL11.glVertex3f(var0 + var3, var1, var2);
      GL11.glColor3f(0.0F, 1.0F, 0.0F);
      GL11.glVertex3f(var0, var1, var2);
      GL11.glVertex3f(var0, var1 + var3, var2);
      GL11.glColor3f(0.0F, 0.0F, 1.0F);
      GL11.glVertex3f(var0, var1, var2);
      GL11.glVertex3f(var0, var1, var2 + var3);
      GL11.glEnd();
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      GL11.glEnable(2929);
      GL13.glActiveTexture(33984);
      GL11.glEnable(3553);
   }

    void setLights(ModelSlotRenderData var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
    EffectLight var4 = var1.effectLights[var3];
         this.Effect.setLight(var3, var4.x, var4.y, var4.z, var4.r, var4.g, var4.b, var4.radius, var1.animPlayerAngle, var1.x, var1.y, var1.z, var1.object);
      }
   }

    void CreateShader(const std::string& var1) {
      if (!ModelManager.NoOpenGL) {
         Lambda.invoke(
            RenderThread::invokeOnRenderContext, this, var1, (var0, var1x) -> var0.Effect = ShaderManager.instance.getOrCreateShader(var1x, var0.bStatic)
         );
      }
   }

    AssetType getType() {
    return ASSET_TYPE;
   }

    void onBeforeReady() {
      super.onBeforeReady();
      this.Tag = this.Mesh.skinningData;
      this.softwareMesh = this.Mesh.softwareMesh;
      this.assetParams = nullptr;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
