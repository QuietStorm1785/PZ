#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "zombie/GameProfiler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/EffectLight.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/PlayerData.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/util/Pool.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelSlotRenderData : public GenericDrawer {
public:
    IsoGameCharacter character;
    IsoMovingObject object;
    ModelSlot modelSlot;
    const ModelInstanceRenderDataList modelData = std::make_shared<ModelInstanceRenderDataList>();
    const ModelInstanceRenderDataList readyModelData = std::make_shared<ModelInstanceRenderDataList>();
    ModelInstanceTextureCreator textureCreator;
    AnimationPlayer animPlayer;
    float animPlayerAngle;
    float x;
    float y;
    float z;
    float ambientR;
    float ambientG;
    float ambientB;
    bool bOutside;
    const Matrix4f vehicleTransform = std::make_shared<Matrix4f>();
    bool bInVehicle;
    float inVehicleX;
    float inVehicleY;
    float inVehicleZ;
    float vehicleAngleX;
    float vehicleAngleY;
    float vehicleAngleZ;
    float alpha;
    bool bRendered;
    bool bReady;
   public const EffectLight[] effectLights = new EffectLight[5];
    float centerOfMassY;
    bool RENDER_TO_TEXTURE;
    static Shader solidColor;
    static Shader solidColorStatic;
    bool bCharacterOutline = false;
    const ColorInfo outlineColor = std::make_shared<ColorInfo>(1.0F, 0.0F, 0.0F, 1.0F);
    ModelSlotDebugRenderData m_debugRenderData;
   private static const ObjectPool<ModelSlotRenderData> pool = std::make_shared<ObjectPool>(ModelSlotRenderData::new);

    public ModelSlotRenderData() {
      for (int var1 = 0; var1 < this.effectLights.length; var1++) {
         this.effectLights[var1] = std::make_unique<EffectLight>();
      }
   }

    ModelSlotRenderData init(ModelSlot var1) {
    int var2 = IsoCamera.frameState.playerIndex;
      this.modelSlot = var1;
      this.object = var1.model.object;
      this.x = this.object.x;
      this.y = this.object.y;
      this.z = this.object.z;
      this.character = var1.character;
    BaseVehicle var3 = (BaseVehicle)Type.tryCastTo(this.object, BaseVehicle.class);
      if (var3 != nullptr) {
         this.textureCreator = nullptr;
         this.animPlayer = var3.getAnimationPlayer();
         this.animPlayerAngle = float.NaN;
         this.centerOfMassY = var3.jniTransform.origin.y - BaseVehicle.CENTER_OF_MASS_MAGIC;
         if (BaseVehicle.RENDER_TO_TEXTURE) {
            this.centerOfMassY = 0.0F - BaseVehicle.CENTER_OF_MASS_MAGIC;
         }

         this.alpha = this.object.getAlpha(var2);
    VehicleModelInstance var4 = (VehicleModelInstance)var1.model;
         IsoLightSource[] var5 = var4.getLights();

         for (int var6 = 0; var6 < this.effectLights.length; var6++) {
            this.effectLights[var6].set(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0);
         }

    Vector3f var16 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();

         for (int var7 = 0; var7 < var5.length; var7++) {
    IsoLightSource var8 = var5[var7];
            if (var8 != nullptr) {
    Vector3f var9 = var3.getLocalPos(var8.x + 0.5F, var8.y + 0.5F, var8.z + 0.75F, var16);
               var3.fixLightbarModelLighting(var8, var16);
               this.effectLights[var7].set(var9.x, var9.y, var9.z, var8.r, var8.g, var8.b, var8.radius);
            }
         }

         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var16);
    float var21 = 1.0F - Math.min(RenderSettings.getInstance().getPlayerSettings(var2).getDarkness() * 0.6F, 0.8F);
         var21 *= 0.9F;
         this.ambientR = this.ambientG = this.ambientB = var21;
         this.vehicleTransform.set(var3.vehicleTransform);
      } else {
         this.textureCreator = this.character.getTextureCreator();
         if (this.textureCreator != nullptr && this.textureCreator.isRendered()) {
            this.textureCreator = nullptr;
         }

    PlayerData var10 = var1.model.playerData[var2];
         this.animPlayer = this.character.getAnimationPlayer();
         this.animPlayerAngle = this.animPlayer.getRenderedAngle();

         for (int var12 = 0; var12 < this.effectLights.length; var12++) {
    EffectLight var17 = var10.effectLightsMain[var12];
            this.effectLights[var12].set(var17.x, var17.y, var17.z, var17.r, var17.g, var17.b, var17.radius);
         }

         this.ambientR = var10.currentAmbient.x;
         this.ambientG = var10.currentAmbient.y;
         this.ambientB = var10.currentAmbient.z;
         this.bOutside = this.character.getCurrentSquare() != nullptr && this.character.getCurrentSquare().isOutside();
         this.alpha = this.character.getAlpha(var2);
         if (Core.bDebug && DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
            this.ambientR = this.ambientG = this.ambientB = 1.0F;
         }

         if (GameServer.bServer && ServerGUI.isCreated()) {
            this.ambientR = this.ambientG = this.ambientB = 1.0F;
         }

         this.bCharacterOutline = this.character.bOutline[var2];
         if (this.bCharacterOutline) {
            this.outlineColor.set(this.character.outlineColor[var2]);
         }

         this.bInVehicle = this.character.isSeatedInVehicle();
         if (this.bInVehicle) {
            this.animPlayerAngle = 0.0F;
    BaseVehicle var13 = this.character.getVehicle();
            this.centerOfMassY = var13.jniTransform.origin.y - BaseVehicle.CENTER_OF_MASS_MAGIC;
            this.x = var13.x;
            this.y = var13.y;
            this.z = var13.z;
    Vector3f var18 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
            var13.getPassengerLocalPos(var13.getSeat(this.character), var18);
            this.inVehicleX = var18.x;
            this.inVehicleY = var18.y;
            this.inVehicleZ = var18.z;
            ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var18);
    Vector3f var23 = var13.vehicleTransform.getEulerAnglesZYX((Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc());
            this.vehicleAngleZ = (float)java.lang.Math.toDegrees(var23.z);
            this.vehicleAngleY = (float)java.lang.Math.toDegrees(var23.y);
            this.vehicleAngleX = (float)java.lang.Math.toDegrees(var23.x);
            ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var23);
         }
      }

      this.RENDER_TO_TEXTURE = BaseVehicle.RENDER_TO_TEXTURE;
      this.modelData.clear();
    ModelInstanceRenderData var11 = nullptr;
      if (var1.model.model.isReady() && (var1.model.AnimPlayer == nullptr || var1.model.AnimPlayer.isReady())) {
         var11 = ModelInstanceRenderData.alloc().init(var1.model);
         this.modelData.push_back(var11);
         if (var1.sub.size() != var1.model.sub.size()) {
    bool var14 = true;
         }
      }

      this.initRenderData(var1.model.sub, var11);
    bool var15 = false;

      for (int var19 = 0; var19 < this.modelData.size(); var19++) {
    ModelInstanceRenderData var24 = (ModelInstanceRenderData)this.modelData.get(var19);
         if (this.character != nullptr && var24.modelInstance == this.character.primaryHandModel && this.character.isMuzzleFlash()) {
            var24.m_muzzleFlash = true;
         }

         if (var24.modelInstance != nullptr && var24.modelInstance.hasTextureCreator()) {
            var15 = true;
         }
      }

      if (this.textureCreator != nullptr) {
         this.textureCreator.renderRefCount++;
      }

      if (this.character != nullptr && (this.textureCreator != nullptr || var15)) {
         assert this.readyModelData.empty();

         ModelInstanceRenderData.release(this.readyModelData);
         this.readyModelData.clear();

         for (int var20 = 0; var20 < this.character.getReadyModelData().size(); var20++) {
    ModelInstance var25 = (ModelInstance)this.character.getReadyModelData().get(var20);
    ModelInstanceRenderData var26 = ModelInstanceRenderData.alloc().init(var25);
            var26.transformToParent(this.getParentData(var25));
            this.readyModelData.push_back(var26);
         }
      }

      if (Core.bDebug) {
         this.m_debugRenderData = ModelSlotDebugRenderData.alloc().init(this);
      }

      this.bRendered = false;
    return this;
   }

    ModelInstanceRenderData getParentData(ModelInstance var1) {
      for (int var2 = 0; var2 < this.readyModelData.size(); var2++) {
    ModelInstanceRenderData var3 = (ModelInstanceRenderData)this.readyModelData.get(var2);
         if (var3.modelInstance == var1.parent) {
    return var3;
         }
      }

    return nullptr;
   }

    ModelInstanceRenderData initRenderData(ModelInstance var1, ModelInstanceRenderData var2) {
    ModelInstanceRenderData var3 = ModelInstanceRenderData.alloc().init(var1);
      var3.transformToParent(var2);
      this.modelData.push_back(var3);
      this.initRenderData(var1.sub, var3);
    return var3;
   }

    void initRenderData(std::vector<ModelInstance> var1, ModelInstanceRenderData var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    ModelInstance var4 = (ModelInstance)var1.get(var3);
         if (var4.model.isReady() && (var4.AnimPlayer == nullptr || var4.AnimPlayer.isReady())) {
            this.initRenderData(var4, var2);
         }
      }
   }

    void render() {
      if (this.character == nullptr) {
         this.renderVehicle();
      } else {
         this.renderCharacter();
      }
   }

    void renderDebug() {
      if (this.m_debugRenderData != nullptr) {
         this.m_debugRenderData.render();
      }
   }

    void renderCharacter() {
      this.bReady = true;
      if (this.textureCreator != nullptr && !this.textureCreator.isRendered()) {
         this.textureCreator.render();
         if (!this.textureCreator.isRendered()) {
            this.bReady = false;
         }
      }

      for (int var1 = 0; var1 < this.modelData.size(); var1++) {
    ModelInstanceRenderData var2 = (ModelInstanceRenderData)this.modelData.get(var1);
    ModelInstanceTextureInitializer var3 = var2.modelInstance.getTextureInitializer();
         if (var3 != nullptr && !var3.isRendered()) {
            var3.render();
            if (!var3.isRendered()) {
               this.bReady = false;
            }
         }
      }

      if (this.bReady || !this.readyModelData.empty()) {
         if (this.bCharacterOutline) {
            ModelCamera.instance.bDepthMask = false;
            GameProfiler.getInstance().invokeAndMeasure("performRenderCharacterOutline", this, ModelSlotRenderData::performRenderCharacterOutline);
         }

         ModelCamera.instance.bDepthMask = true;
         GameProfiler.getInstance().invokeAndMeasure("renderCharacter", this, ModelSlotRenderData::performRenderCharacter);
    int var4 = SpriteRenderer.instance.getRenderingPlayerIndex();
    IsoPlayer var5 = (IsoPlayer)Type.tryCastTo(this.character, IsoPlayer.class);
         if (var5 != nullptr && !this.bCharacterOutline && var5 == IsoPlayer.players[var4]) {
            ModelOutlines.instance.setPlayerRenderData(this);
         }

         this.bRendered = this.bReady;
      }
   }

    void renderVehicleDebug() {
      if (Core.bDebug) {
    Vector3 var1 = Model.tempo;
         ModelCamera.instance.Begin();
         GL11.glMatrixMode(5888);
         GL11.glTranslatef(0.0F, this.centerOfMassY, 0.0F);
         if (this.m_debugRenderData != nullptr && !this.modelData.empty()) {
            PZGLUtil.pushAndMultMatrix(5888, ((ModelInstanceRenderData)this.modelData.get(0)).xfrm);
            this.m_debugRenderData.render();
            PZGLUtil.popMatrix(5888);
         }

         if (DebugOptions.instance.ModelRenderAttachments.getValue()) {
    BaseVehicle var2 = (BaseVehicle)this.object;
    ModelInstanceRenderData var3 = (ModelInstanceRenderData)this.modelData.get(0);
            PZGLUtil.pushAndMultMatrix(5888, this.vehicleTransform);
    float var4 = var2.getScript().getModelScale();
    float var5 = var3.modelInstance.scale;
    Matrix4f var6 = (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
            var6.scaling(1.0F / var4);
    Matrix4f var7 = (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();

            for (int var8 = 0; var8 < var2.getScript().getAttachmentCount(); var8++) {
    ModelAttachment var9 = var2.getScript().getAttachment(var8);
               var3.modelInstance.getAttachmentMatrix(var9, var7);
               var6.mul(var7, var7);
               PZGLUtil.pushAndMultMatrix(5888, var7);
               Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 1.0F, 2.0F);
               PZGLUtil.popMatrix(5888);
            }

            ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var7);
            ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var6);
            PZGLUtil.popMatrix(5888);
         }

         if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue() && !this.modelData.empty()) {
    BaseVehicle var10 = (BaseVehicle)this.object;
            GL11.glMatrixMode(5888);
    Vector3f var11 = this.vehicleTransform.getEulerAnglesZYX((Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc());
            GL11.glRotatef((float)java.lang.Math.toDegrees(var11.z), 0.0F, 0.0F, 1.0F);
            GL11.glRotatef((float)java.lang.Math.toDegrees(var11.y), 0.0F, 1.0F, 0.0F);
            GL11.glRotatef((float)java.lang.Math.toDegrees(var11.x), 1.0F, 0.0F, 0.0F);
            ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var11);
            Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 1.0F, 4.0F);

            for (int var12 = 1; var12 < this.modelData.size(); var12++) {
               VehicleSubModelInstance var13 = (VehicleSubModelInstance)Type.tryCastTo(
                  ((ModelInstanceRenderData)this.modelData.get(var12)).modelInstance, VehicleSubModelInstance.class
               );
               if (var13 != nullptr && var13.modelInfo.wheelIndex >= 0) {
    float var14 = 1.0F;
    Wheel var15 = var10.getScript().getWheel(var13.modelInfo.wheelIndex);
    uint8_t var16 = -1;
                  var1.set(
                     var15.offset.x * var16,
                     var10.getScript().getModel().offset.y + var15.offset.y + var10.getScript().getSuspensionRestLength(),
                     var15.offset.z
                  );
                  Model.debugDrawAxis(var1.x / var14, var1.y / var14, var1.z / var14, var10.getScript().getSuspensionRestLength() / var14, 2.0F);
               }
            }
         }

         ModelCamera.instance.End();
      }
   }

    void performRenderCharacter() {
      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
      GL11.glEnable(2929);
      GL11.glDisable(3089);
    ModelInstanceRenderDataList var1 = this.modelData;
      if (this.character != nullptr && !this.bReady) {
         var1 = this.readyModelData;
      }

      Model.CharacterModelCameraBegin(this);

      for (int var2 = 0; var2 < var1.size(); var2++) {
    ModelInstanceRenderData var3 = (ModelInstanceRenderData)var1.get(var2);
         var3.RenderCharacter(this);
      }

      if (Core.bDebug) {
         this.renderDebug();

         for (int var4 = 0; var4 < var1.size(); var4++) {
    ModelInstanceRenderData var5 = (ModelInstanceRenderData)var1.get(var4);
            var5.renderDebug();
         }
      }

      Model.CharacterModelCameraEnd();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      GL11.glEnable(3553);
      SpriteRenderer.ringBuffer.restoreVBOs = true;
      GL11.glDisable(2929);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
   }

    void performRenderCharacterOutline() {
      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
      GL11.glEnable(2929);
      GL11.glDisable(3089);
    ModelInstanceRenderDataList var1 = this.modelData;
      if (this.character != nullptr && !this.bReady) {
         var1 = this.readyModelData;
      }

      if (solidColor == nullptr) {
         solidColor = std::make_shared<Shader>("aim_outline_solid", false);
         solidColorStatic = std::make_shared<Shader>("aim_outline_solid", true);
      }

      solidColor.Start();
      solidColor.getShaderProgram().setVector4("u_color", this.outlineColor.r, this.outlineColor.g, this.outlineColor.b, this.outlineColor.a);
      solidColor.End();
      solidColorStatic.Start();
      solidColorStatic.getShaderProgram().setVector4("u_color", this.outlineColor.r, this.outlineColor.g, this.outlineColor.b, this.outlineColor.a);
      solidColorStatic.End();
    bool var2 = ModelOutlines.instance.beginRenderOutline(this.outlineColor);
      ModelOutlines.instance.m_fboA.startDrawing(var2, true);
      Model.CharacterModelCameraBegin(this);

      for (int var3 = 0; var3 < var1.size(); var3++) {
    ModelInstanceRenderData var4 = (ModelInstanceRenderData)var1.get(var3);
    Shader var5 = var4.model.Effect;

         try {
            var4.model.Effect = var4.model.bStatic ? solidColorStatic : solidColor;
            var4.RenderCharacter(this);
         } finally {
            var4.model.Effect = var5;
         }
      }

      Model.CharacterModelCameraEnd();
      ModelOutlines.instance.m_fboA.endDrawing();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      GL11.glEnable(3553);
      SpriteRenderer.ringBuffer.restoreVBOs = true;
      GL11.glDisable(2929);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
   }

    void renderVehicle() {
      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
      if (this.RENDER_TO_TEXTURE) {
         GL11.glClear(256);
      }

      GL11.glEnable(2929);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
      GL11.glDisable(3089);
      if (this.RENDER_TO_TEXTURE) {
         ModelManager.instance.bitmap.startDrawing(true, true);
         GL11.glViewport(0, 0, ModelManager.instance.bitmap.getWidth(), ModelManager.instance.bitmap.getHeight());
      }

      for (int var1 = 0; var1 < this.modelData.size(); var1++) {
    ModelInstanceRenderData var2 = (ModelInstanceRenderData)this.modelData.get(var1);
         var2.RenderVehicle(this);
      }

      this.renderVehicleDebug();
      if (this.RENDER_TO_TEXTURE) {
         ModelManager.instance.bitmap.endDrawing();
      }

      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      GL11.glEnable(3553);
      SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      SpriteRenderer.ringBuffer.restoreVBOs = true;
      GL11.glDisable(2929);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
   }

    void doneWithTextureCreator(ModelInstanceTextureCreator var1) {
      if (var1 != nullptr) {
         if (var1.testNotReady > 0) {
            var1.testNotReady--;
         }

         if (var1.renderRefCount <= 0) {
            if (var1.isRendered()) {
               var1.postRender();
               if (var1 == this.character.getTextureCreator()) {
                  this.character.setTextureCreator(nullptr);
               }
            } else if (var1 != this.character.getTextureCreator()) {
               var1.postRender();
            }
         }
      }
   }

    void postRender() {
      assert this.modelSlot.renderRefCount > 0;

      this.modelSlot.renderRefCount--;
      if (this.textureCreator != nullptr) {
         this.textureCreator.renderRefCount--;
         this.doneWithTextureCreator(this.textureCreator);
         this.textureCreator = nullptr;
      }

      ModelInstanceRenderData.release(this.readyModelData);
      this.readyModelData.clear();
      if (this.bRendered) {
         ModelManager.instance.derefModelInstances(this.character.getReadyModelData());
         this.character.getReadyModelData().clear();

         for (int var1 = 0; var1 < this.modelData.size(); var1++) {
    ModelInstance var2 = ((ModelInstanceRenderData)this.modelData.get(var1)).modelInstance;
            var2.renderRefCount++;
            this.character.getReadyModelData().push_back(var2);
         }
      }

      this.character = nullptr;
      this.object = nullptr;
      this.animPlayer = nullptr;
      this.m_debugRenderData = (ModelSlotDebugRenderData)Pool.tryRelease(this.m_debugRenderData);
      ModelInstanceRenderData.release(this.modelData);
      pool.release(this);
   }

    static ModelSlotRenderData alloc() {
      return (ModelSlotRenderData)pool.alloc();
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
