#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "zombie/util/Type.h"
#include "zombie/vehicles/UI3DScene/SceneModel.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const UI3DScene m_scene;
    const std::string m_id;
    bool m_visible = true;
    const Vector3f m_translate = std::make_shared<Vector3f>();
    const Vector3f m_rotate = std::make_shared<Vector3f>();
   UI3DScene$SceneObject m_parent;
    std::string m_attachment;
    std::string m_parentAttachment;
    bool m_autoRotate = false;
    float m_autoRotateAngle = 0.0F;

   UI3DScene$SceneObject(UI3DScene var1, std::string var2) {
      this.m_scene = var1;
      this.m_id = var2;
   }

   abstract SceneObjectRenderData renderMain();

    Matrix4f getLocalTransform(Matrix4f var1) {
    SceneModel var2 = (SceneModel)Type.tryCastTo(this, SceneModel.class);
      if (var2 != nullptr && var2.m_useWorldAttachment) {
         var1.translation(-this.m_translate.x, this.m_translate.y, this.m_translate.z);
         var1.scale(-1.5F, 1.5F, 1.5F);
      } else {
         var1.translation(this.m_translate);
      }

    float var3 = this.m_rotate.y;
      if (this.m_autoRotate) {
         var3 += this.m_autoRotateAngle;
      }

      var1.rotateXYZ(this.m_rotate.x * (float) (Math.PI / 180.0), var3 * (float) (Math.PI / 180.0), this.m_rotate.z * (float) (Math.PI / 180.0));
      if (this.m_attachment != nullptr) {
    Matrix4f var4 = this.getAttachmentTransform(this.m_attachment, UI3DScene.allocMatrix4f());
         var4.invert();
         var1.mul(var4);
         UI3DScene.releaseMatrix4f(var4);
      }

    return var1;
   }

    Matrix4f getGlobalTransform(Matrix4f var1) {
      this.getLocalTransform(var1);
      if (this.m_parent != nullptr) {
         if (this.m_parentAttachment != nullptr) {
    Matrix4f var2 = this.m_parent.getAttachmentTransform(this.m_parentAttachment, UI3DScene.allocMatrix4f());
            var2.mul(var1, var1);
            UI3DScene.releaseMatrix4f(var2);
         }

    Matrix4f var3 = this.m_parent.getGlobalTransform(UI3DScene.allocMatrix4f());
         var3.mul(var1, var1);
         UI3DScene.releaseMatrix4f(var3);
      }

    return var1;
   }

    Matrix4f getAttachmentTransform(const std::string& var1, Matrix4f var2) {
      var2.identity();
    return var2;
   }
}
} // namespace vehicles
} // namespace zombie
