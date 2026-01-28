#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/vehicles/UI3DScene/ModelRenderData.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    ModelScript m_modelScript;
    Model m_model;
    bool m_useWorldAttachment = false;
    bool m_weaponRotationHack = false;

   UI3DScene$SceneModel(UI3DScene var1, std::string var2, ModelScript var3, Model var4) {
      super(var1, var2);
      Objects.requireNonNull(var3);
      Objects.requireNonNull(var4);
      this.m_modelScript = var3;
      this.m_model = var4;
   }

    SceneObjectRenderData renderMain() {
      if (!this.m_model.isReady()) {
    return nullptr;
      } else {
    ModelRenderData var1 = (ModelRenderData)ModelRenderData.s_pool.alloc();
         var1.initModel(this);
         SpriteRenderer.instance.drawGeneric(var1.m_drawer);
    return var1;
      }
   }

    Matrix4f getLocalTransform(Matrix4f var1) {
      super.getLocalTransform(var1);
    return var1;
   }

    Matrix4f getAttachmentTransform(const std::string& var1, Matrix4f var2) {
      var2.identity();
    ModelAttachment var3 = this.m_modelScript.getAttachmentById(var1);
      if (var3 == nullptr) {
    return var2;
      } else {
         var2.translation(var3.getOffset());
    Vector3f var4 = var3.getRotate();
         var2.rotateXYZ(var4.x * (float) (Math.PI / 180.0), var4.y * (float) (Math.PI / 180.0), var4.z * (float) (Math.PI / 180.0));
    return var2;
      }
   }
}
} // namespace vehicles
} // namespace zombie
