#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceDebugRenderData : public PooledObject {
public:
   private static const Pool<ModelInstanceDebugRenderData> s_pool = std::make_shared<Pool>(ModelInstanceDebugRenderData::new);
   private const std::vector<Matrix4f> m_attachmentMatrices = std::make_unique<std::vector<>>();

    static ModelInstanceDebugRenderData alloc() {
      return (ModelInstanceDebugRenderData)s_pool.alloc();
   }

    ModelInstanceDebugRenderData init(ModelSlotRenderData var1, ModelInstanceRenderData var2) {
      this.initAttachments(var1, var2);
    return this;
   }

    void render() {
      this.renderAttachments();
      if (DebugOptions.instance.ModelRenderAxis.getValue()) {
         Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 1.0F, 1.0F);
      }
   }

    void initAttachments(ModelSlotRenderData var1, ModelInstanceRenderData var2) {
    Matrix4fObjectPool var3 = (Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get();
      var3.release(this.m_attachmentMatrices);
      this.m_attachmentMatrices.clear();
      if (DebugOptions.instance.ModelRenderAttachments.getValue()) {
    ModelScript var4 = var2.modelInstance.m_modelScript;
         if (var4 != nullptr) {
    Matrix4f var5 = ((Matrix4f)var3.alloc()).set(var2.xfrm);
    Matrix4f var6 = (Matrix4f)var3.alloc();
            var5.transpose();

            for (int var7 = 0; var7 < var4.getAttachmentCount(); var7++) {
    ModelAttachment var8 = var4.getAttachment(var7);
    Matrix4f var9 = (Matrix4f)var3.alloc();
               var2.modelInstance.getAttachmentMatrix(var8, var9);
               if (var2.model.bStatic || var8.getBone() == nullptr) {
                  var5.mul(var9, var9);
               } else if (var1.animPlayer != nullptr && var1.animPlayer.hasSkinningData()) {
    int var10 = var1.animPlayer.getSkinningBoneIndex(var8.getBone(), 0);
                  org.lwjgl.util.vector.Matrix4f var11 = var1.animPlayer.modelTransforms[var10];
                  PZMath.convertMatrix(var11, var6);
                  var6.transpose();
                  var6.mul(var9, var9);
                  var5.mul(var9, var9);
               }

               this.m_attachmentMatrices.push_back(var9);
            }

            var3.release(var6);
            var3.release(var5);
         }
      }
   }

    void renderAttachments() {
      for (int var1 = 0; var1 < this.m_attachmentMatrices.size(); var1++) {
    Matrix4f var2 = this.m_attachmentMatrices.get(var1);
         PZGLUtil.pushAndMultMatrix(5888, var2);
         Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 0.05F, 1.0F);
         PZGLUtil.popMatrix(5888);
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
