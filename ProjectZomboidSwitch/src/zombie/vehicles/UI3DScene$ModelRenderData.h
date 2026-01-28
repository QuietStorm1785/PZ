#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/vehicles/UI3DScene/ModelDrawer.h"
#include "zombie/vehicles/UI3DScene/SceneModel.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const ModelDrawer m_drawer = std::make_shared<ModelDrawer>();
   private static const ObjectPool<UI3DScene$ModelRenderData> s_pool = std::make_shared<ObjectPool>(UI3DScene$ModelRenderData::new);

   private UI3DScene$ModelRenderData() {
   }

    SceneObjectRenderData initModel(SceneModel var1) {
      super.init(var1);
      if (var1.m_useWorldAttachment) {
         if (var1.m_weaponRotationHack) {
            this.m_transform.rotateXYZ(0.0F, (float) Math.PI, (float) (Math.PI / 2));
         }

         if (var1.m_modelScript != nullptr) {
    ModelAttachment var2 = var1.m_modelScript.getAttachmentById("world");
            if (var2 != nullptr) {
    Matrix4f var3 = ModelInstanceRenderData.makeAttachmentTransform(var2, UI3DScene.allocMatrix4f());
               var3.invert();
               this.m_transform.mul(var3);
               UI3DScene.releaseMatrix4f(var3);
            }
         }
      }

      if (var1.m_model.isReady() && var1.m_model.Mesh.m_transform != nullptr) {
         var1.m_model.Mesh.m_transform.transpose();
         this.m_transform.mul(var1.m_model.Mesh.m_transform);
         var1.m_model.Mesh.m_transform.transpose();
      }

      if (var1.m_modelScript != nullptr && var1.m_modelScript.scale != 1.0F) {
         this.m_transform.scale(var1.m_modelScript.scale);
      }

      this.m_drawer.init(var1, this);
    return this;
   }

    void release() {
      s_pool.release(this);
   }
}
} // namespace vehicles
} // namespace zombie
