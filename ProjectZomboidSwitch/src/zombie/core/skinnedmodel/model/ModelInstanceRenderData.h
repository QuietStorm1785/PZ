#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceRenderData {
public:
    static const Vector3f tempVector3f = std::make_shared<Vector3f>();
    Model model;
    Texture tex;
    float depthBias;
    float hue;
    float tintR;
    float tintG;
    float tintB;
    int parentBone;
    FloatBuffer matrixPalette;
    const Matrix4f xfrm = std::make_shared<Matrix4f>();
    SoftwareModelMeshInstance softwareMesh;
    ModelInstance modelInstance;
    bool m_muzzleFlash = false;
    ModelInstanceDebugRenderData m_debugRenderData;
   private static const ObjectPool<ModelInstanceRenderData> pool = std::make_shared<ObjectPool>(ModelInstanceRenderData::new);

    ModelInstanceRenderData init(ModelInstance var1) {
      this.model = var1.model;
      this.tex = var1.tex;
      this.depthBias = var1.depthBias;
      this.hue = var1.hue;
      this.parentBone = var1.parentBone;

      assert var1.character == nullptr || var1.AnimPlayer != nullptr;

      this.m_muzzleFlash = false;
      this.xfrm.identity();
      if (var1.AnimPlayer != nullptr && !this.model.bStatic) {
    SkinningData var2 = (SkinningData)this.model.Tag;
         if (Core.bDebug && var2 == nullptr) {
            DebugLog.General.warn("skinningData is nullptr, matrixPalette may be invalid");
         }

         org.lwjgl.util.vector.Matrix4f[] var3 = var1.AnimPlayer.getSkinTransforms(var2);
         if (this.matrixPalette == nullptr || this.matrixPalette.capacity() < var3.length * 16) {
            this.matrixPalette = BufferUtils.createFloatBuffer(var3.length * 16);
         }

         this.matrixPalette.clear();

         for (int var4 = 0; var4 < var3.length; var4++) {
            var3[var4].store(this.matrixPalette);
         }

         this.matrixPalette.flip();
      }

    VehicleSubModelInstance var5 = (VehicleSubModelInstance)Type.tryCastTo(var1, VehicleSubModelInstance.class);
      if (dynamic_cast<VehicleModelInstance*>(var1) != nullptr || var5 != nullptr) {
         if (dynamic_cast<VehicleModelInstance*>(var1) != nullptr) {
            this.xfrm.set(((BaseVehicle)var1.object).renderTransform);
         } else {
            this.xfrm.set(var5.modelInfo.renderTransform);
         }

         if (var1.model.Mesh != nullptr && var1.model.Mesh.isReady() && var1.model.Mesh.m_transform != nullptr) {
            var1.model.Mesh.m_transform.transpose();
            this.xfrm.mul(var1.model.Mesh.m_transform);
            var1.model.Mesh.m_transform.transpose();
         }
      }

      this.softwareMesh = var1.softwareMesh;
      this.modelInstance = var1;
      var1.renderRefCount++;
      if (var1.getTextureInitializer() != nullptr) {
         var1.getTextureInitializer().renderMain();
      }

    return this;
   }

    void renderDebug() {
      if (this.m_debugRenderData != nullptr) {
         this.m_debugRenderData.render();
      }
   }

    void RenderCharacter(ModelSlotRenderData var1) {
      this.tintR = this.modelInstance.tintR;
      this.tintG = this.modelInstance.tintG;
      this.tintB = this.modelInstance.tintB;
      this.tex = this.modelInstance.tex;
      if (this.tex != nullptr || this.modelInstance.model.tex != nullptr) {
         this.model.DrawChar(var1, this);
      }
   }

    void RenderVehicle(ModelSlotRenderData var1) {
      this.tintR = this.modelInstance.tintR;
      this.tintG = this.modelInstance.tintG;
      this.tintB = this.modelInstance.tintB;
      this.tex = this.modelInstance.tex;
      if (this.tex != nullptr || this.modelInstance.model.tex != nullptr) {
         this.model.DrawVehicle(var1, this);
      }
   }

    static Matrix4f makeAttachmentTransform(ModelAttachment var0, Matrix4f var1) {
      var1.translation(var0.getOffset());
      org.joml.Vector3f var2 = var0.getRotate();
      var1.rotateXYZ(var2.x * (float) (Math.PI / 180.0), var2.y * (float) (Math.PI / 180.0), var2.z * (float) (Math.PI / 180.0));
    return var1;
   }

    static void applyBoneTransform(ModelInstance var0, const std::string& var1, Matrix4f var2) {
      if (var0 != nullptr && var0.AnimPlayer != nullptr) {
         if (!StringUtils.isNullOrWhitespace(var1)) {
    int var3 = var0.AnimPlayer.getSkinningBoneIndex(var1, -1);
            if (var3 != -1) {
               org.lwjgl.util.vector.Matrix4f var4 = var0.AnimPlayer.GetPropBoneMatrix(var3);
    Matrix4f var5 = (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
               PZMath.convertMatrix(var4, var5);
               var5.transpose();
               var2.mul(var5);
               ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var5);
            }
         }
      }
   }

    ModelInstanceRenderData transformToParent(ModelInstanceRenderData var1) {
      if (this.dynamic_cast<VehicleModelInstance*>(modelInstance) != nullptr || this.dynamic_cast<VehicleSubModelInstance*>(modelInstance) != nullptr) {
    return this;
      } else if (var1 == nullptr) {
    return this;
      } else {
         this.xfrm.set(var1.xfrm);
         this.xfrm.transpose();
    Matrix4f var2 = (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
    ModelAttachment var3 = var1.modelInstance.getAttachmentById(this.modelInstance.attachmentNameParent);
         if (var3 == nullptr) {
            if (this.modelInstance.parentBoneName != nullptr && var1.modelInstance.AnimPlayer != nullptr) {
               applyBoneTransform(var1.modelInstance, this.modelInstance.parentBoneName, this.xfrm);
            }
         } else {
            applyBoneTransform(var1.modelInstance, var3.getBone(), this.xfrm);
            makeAttachmentTransform(var3, var2);
            this.xfrm.mul(var2);
         }

    ModelAttachment var4 = this.modelInstance.getAttachmentById(this.modelInstance.attachmentNameSelf);
         if (var4 != nullptr) {
            makeAttachmentTransform(var4, var2);
            var2.invert();
            this.xfrm.mul(var2);
         }

         if (this.modelInstance.model.Mesh != nullptr && this.modelInstance.model.Mesh.isReady() && this.modelInstance.model.Mesh.m_transform != nullptr) {
            this.xfrm.mul(this.modelInstance.model.Mesh.m_transform);
         }

         if (this.modelInstance.scale != 1.0F) {
            this.xfrm.scale(this.modelInstance.scale);
         }

         this.xfrm.transpose();
         ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var2);
    return this;
      }
   }

    void testOnBackItem(ModelInstance var1) {
      if (var1.parent != nullptr && var1.parent.m_modelScript != nullptr) {
    AnimationPlayer var2 = var1.parent.AnimPlayer;
    ModelAttachment var3 = nullptr;

         for (int var4 = 0; var4 < var1.parent.m_modelScript.getAttachmentCount(); var4++) {
    ModelAttachment var5 = var1.parent.getAttachment(var4);
            if (var5.getBone() != nullptr && this.parentBone == var2.getSkinningBoneIndex(var5.getBone(), 0)) {
               var3 = var5;
               break;
            }
         }

         if (var3 != nullptr) {
    Matrix4f var6 = (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
            makeAttachmentTransform(var3, var6);
            this.xfrm.transpose();
            this.xfrm.mul(var6);
            this.xfrm.transpose();
    ModelAttachment var7 = var1.getAttachmentById(var3.getId());
            if (var7 != nullptr) {
               makeAttachmentTransform(var7, var6);
               var6.invert();
               this.xfrm.transpose();
               this.xfrm.mul(var6);
               this.xfrm.transpose();
            }

            ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var6);
         }
      }
   }

    static ModelInstanceRenderData alloc() {
      return (ModelInstanceRenderData)pool.alloc();
   }

    static void release(std::vector<ModelInstanceRenderData> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
    ModelInstanceRenderData var2 = (ModelInstanceRenderData)var0.get(var1);
         if (var2.modelInstance.getTextureInitializer() != nullptr) {
            var2.modelInstance.getTextureInitializer().postRender();
         }

         ModelManager.instance.derefModelInstance(var2.modelInstance);
         var2.modelInstance = nullptr;
         var2.model = nullptr;
         var2.tex = nullptr;
         var2.softwareMesh = nullptr;
         var2.m_debugRenderData = (ModelInstanceDebugRenderData)Pool.tryRelease(var2.m_debugRenderData);
      }

      pool.release(var0);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
