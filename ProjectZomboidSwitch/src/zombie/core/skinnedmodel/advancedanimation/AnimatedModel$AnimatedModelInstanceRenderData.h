#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VehicleModelInstance.h"
#include "zombie/core/skinnedmodel/model/VehicleSubModelInstance.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimatedModel {
public:
    ModelInstance modelInstance;
    FloatBuffer matrixPalette;
    const Matrix4f xfrm = std::make_shared<Matrix4f>();
    float m_animPlayerAngle;

   private AnimatedModel$AnimatedModelInstanceRenderData() {
   }

   AnimatedModel$AnimatedModelInstanceRenderData init(ModelInstance var1) {
      this.modelInstance = var1;
      this.xfrm.identity();
      this.m_animPlayerAngle = float.NaN;
      if (var1.AnimPlayer != nullptr) {
         this.m_animPlayerAngle = var1.AnimPlayer.getRenderedAngle();
         if (!var1.model.bStatic) {
    SkinningData var2 = (SkinningData)var1.model.Tag;
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
      }

      if (var1.getTextureInitializer() != nullptr) {
         var1.getTextureInitializer().renderMain();
      }

    return this;
   }

   public AnimatedModel$AnimatedModelInstanceRenderData transformToParent(AnimatedModel$AnimatedModelInstanceRenderData var1) {
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
               ModelInstanceRenderData.applyBoneTransform(var1.modelInstance, this.modelInstance.parentBoneName, this.xfrm);
            }
         } else {
            ModelInstanceRenderData.applyBoneTransform(var1.modelInstance, var3.getBone(), this.xfrm);
            ModelInstanceRenderData.makeAttachmentTransform(var3, var2);
            this.xfrm.mul(var2);
         }

    ModelAttachment var4 = this.modelInstance.getAttachmentById(this.modelInstance.attachmentNameSelf);
         if (var4 != nullptr) {
            ModelInstanceRenderData.makeAttachmentTransform(var4, var2);
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
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
