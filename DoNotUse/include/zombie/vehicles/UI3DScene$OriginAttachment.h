#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneObject m_object;
    std::string m_attachmentName;

   UI3DScene$OriginAttachment(UI3DScene var1) {
      super(var1, "OriginAttachment");
   }

    SceneObjectRenderData renderMain() {
    return nullptr;
   }

    Matrix4f getGlobalTransform(Matrix4f var1) {
      return this.m_object.getAttachmentTransform(this.m_attachmentName, var1);
   }
}
} // namespace vehicles
} // namespace zombie
