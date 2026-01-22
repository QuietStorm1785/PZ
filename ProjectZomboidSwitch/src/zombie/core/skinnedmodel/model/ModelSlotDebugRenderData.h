#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/Color.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelSlotDebugRenderData : public PooledObject {
public:
   private static const Pool<ModelSlotDebugRenderData> s_pool = std::make_shared<Pool>(ModelSlotDebugRenderData::new);
    ModelSlotRenderData m_slotData;
    const TFloatArrayList m_boneCoords = std::make_shared<TFloatArrayList>();
   private const std::vector<Matrix4f> m_boneMatrices = std::make_unique<std::vector<>>();
    const TFloatArrayList m_squareLights = std::make_shared<TFloatArrayList>();
   private org.joml.Matrix4f m_weaponMatrix;
    float m_weaponLength;

    static ModelSlotDebugRenderData alloc() {
      return (ModelSlotDebugRenderData)s_pool.alloc();
   }

    ModelSlotDebugRenderData init(ModelSlotRenderData var1) {
      this.m_slotData = var1;
      this.initBoneAxis();
      this.initSkeleton();
      this.initLights();
      this.initWeaponHitPoint();

      for (int var2 = 0; var2 < var1.modelData.size(); var2++) {
    ModelInstanceRenderData var3 = (ModelInstanceRenderData)var1.modelData.get(var2);
         var3.m_debugRenderData = ModelInstanceDebugRenderData.alloc().init(var1, var3);
      }

    return this;
   }

    void initBoneAxis() {
      for (int var1 = 0; var1 < this.m_boneMatrices.size(); var1++) {
         HelperFunctions.returnMatrix(this.m_boneMatrices.get(var1));
      }

      this.m_boneMatrices.clear();
      if (this.m_slotData.animPlayer != nullptr && this.m_slotData.animPlayer.hasSkinningData()) {
         if (DebugOptions.instance.char.Debug.Render.Bip01.getValue()) {
            this.initBoneAxis("Bip01");
         }

         if (DebugOptions.instance.char.Debug.Render.PrimaryHandBone.getValue()) {
            this.initBoneAxis("Bip01_Prop1");
         }

         if (DebugOptions.instance.char.Debug.Render.SecondaryHandBone.getValue()) {
            this.initBoneAxis("Bip01_Prop2");
         }

         if (DebugOptions.instance.char.Debug.Render.TranslationData.getValue()) {
            this.initBoneAxis("Translation_Data");
         }
      }
   }

    void initBoneAxis(const std::string& var1) {
    int var2 = (int)this.m_slotData.animPlayer.getSkinningData().BoneIndices.get(var1);
      if (var2 != nullptr) {
    Matrix4f var3 = HelperFunctions.getMatrix();
         var3.load(this.m_slotData.animPlayer.modelTransforms[var2]);
         this.m_boneMatrices.push_back(var3);
      }
   }

    void initSkeleton() {
      this.m_boneCoords.clear();
      if (DebugOptions.instance.ModelRenderBones.getValue()) {
         this.initSkeleton(this.m_slotData.animPlayer);
         if (this.m_slotData.dynamic_cast<BaseVehicle*>(object) != nullptr) {
            for (int var1 = 0; var1 < this.m_slotData.modelData.size(); var1++) {
    ModelInstanceRenderData var2 = (ModelInstanceRenderData)this.m_slotData.modelData.get(var1);
    VehicleSubModelInstance var3 = (VehicleSubModelInstance)Type.tryCastTo(var2.modelInstance, VehicleSubModelInstance.class);
               if (var3 != nullptr) {
                  this.initSkeleton(var3.AnimPlayer);
               }
            }
         }
      }
   }

    void initSkeleton(AnimationPlayer var1) {
      if (var1 != nullptr && var1.hasSkinningData() && !var1.isBoneTransformsNeedFirstFrame()) {
    int var2 = (int)var1.getSkinningData().BoneIndices.get("Translation_Data");

         for (int var3 = 0; var3 < var1.modelTransforms.length; var3++) {
            if (var2 == nullptr || var3 != var2) {
    int var4 = (int)var1.getSkinningData().SkeletonHierarchy.get(var3);
               if (var4 >= 0) {
                  this.initSkeleton(var1.modelTransforms, var3);
                  this.initSkeleton(var1.modelTransforms, var4);
               }
            }
         }
      }
   }

    void initSkeleton(Matrix4f[] var1, int var2) {
    float var3 = var1[var2].m03;
    float var4 = var1[var2].m13;
    float var5 = var1[var2].m23;
      this.m_boneCoords.push_back(var3);
      this.m_boneCoords.push_back(var4);
      this.m_boneCoords.push_back(var5);
   }

    void initLights() {
      this.m_squareLights.clear();
      if (DebugOptions.instance.ModelRenderLights.getValue()) {
         if (this.m_slotData.character != nullptr) {
            if (this.m_slotData.character.getCurrentSquare() != nullptr) {
    int var1 = IsoCamera.frameState.playerIndex;
    ILighting var2 = this.m_slotData.character.getCurrentSquare().lighting[var1];

               for (int var3 = 0; var3 < var2.resultLightCount(); var3++) {
    ResultLight var4 = var2.getResultLight(var3);
                  this.m_squareLights.push_back(var4.x);
                  this.m_squareLights.push_back(var4.y);
                  this.m_squareLights.push_back(var4.z);
               }
            }
         }
      }
   }

    void initWeaponHitPoint() {
      if (this.m_weaponMatrix != nullptr) {
         ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(this.m_weaponMatrix);
         this.m_weaponMatrix = nullptr;
      }

      if (DebugOptions.instance.ModelRenderWeaponHitPoint.getValue()) {
         if (this.m_slotData.animPlayer != nullptr && this.m_slotData.animPlayer.hasSkinningData()) {
            if (this.m_slotData.character != nullptr) {
    int var1 = (int)this.m_slotData.animPlayer.getSkinningData().BoneIndices.get("Bip01_Prop1");
               if (var1 != nullptr) {
    HandWeapon var2 = (HandWeapon)Type.tryCastTo(this.m_slotData.character.getPrimaryHandItem(), HandWeapon.class);
                  if (var2 != nullptr) {
                     this.m_weaponLength = var2.WeaponLength;
    Matrix4f var3 = this.m_slotData.animPlayer.modelTransforms[var1];
                     this.m_weaponMatrix = (org.joml.Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
                     PZMath.convertMatrix(var3, this.m_weaponMatrix);
                     this.m_weaponMatrix.transpose();
                  }
               }
            }
         }
      }
   }

    void render() {
      this.renderBonesAxis();
      this.renderSkeleton();
      this.renderLights();
      this.renderWeaponHitPoint();
   }

    void renderBonesAxis() {
      for (int var1 = 0; var1 < this.m_boneMatrices.size(); var1++) {
         Model.drawBoneMtx(this.m_boneMatrices.get(var1));
      }
   }

    void renderSkeleton() {
      if (!this.m_boneCoords.empty()) {
         GL11.glDisable(2929);

         for (int var1 = 7; var1 >= 0; var1--) {
            GL13.glActiveTexture(33984 + var1);
            GL11.glDisable(3553);
         }

         GL11.glLineWidth(1.0F);
         GL11.glBegin(1);

         for (byte var6 = 0; var6 < this.m_boneCoords.size(); var6 += 6) {
    Color var2 = Model.debugDrawColours[var6 % Model.debugDrawColours.length];
            GL11.glColor3f(var2.r, var2.g, var2.b);
    float var3 = this.m_boneCoords.get(var6);
    float var4 = this.m_boneCoords.get(var6 + 1);
    float var5 = this.m_boneCoords.get(var6 + 2);
            GL11.glVertex3f(var3, var4, var5);
            var3 = this.m_boneCoords.get(var6 + 3);
            var4 = this.m_boneCoords.get(var6 + 4);
            var5 = this.m_boneCoords.get(var6 + 5);
            GL11.glVertex3f(var3, var4, var5);
         }

         GL11.glEnd();
         GL11.glColor3f(1.0F, 1.0F, 1.0F);
         GL11.glEnable(2929);
      }
   }

    void renderLights() {
      for (byte var1 = 0; var1 < this.m_squareLights.size(); var1 += 3) {
    float var2 = this.m_squareLights.get(var1);
    float var3 = this.m_squareLights.get(var1 + 1);
    float var4 = this.m_squareLights.get(var1 + 2);
         Model.debugDrawLightSource(var2, var3, var4, this.m_slotData.x, this.m_slotData.y, this.m_slotData.z, -this.m_slotData.animPlayerAngle);
      }
   }

    void renderWeaponHitPoint() {
      if (this.m_weaponMatrix != nullptr) {
         PZGLUtil.pushAndMultMatrix(5888, this.m_weaponMatrix);
         Model.debugDrawAxis(0.0F, this.m_weaponLength, 0.0F, 0.05F, 1.0F);
         PZGLUtil.popMatrix(5888);
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
