#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneObject m_object;
    const Matrix4f m_transform = std::make_shared<Matrix4f>();
   private static const ObjectPool<UI3DScene$SceneObjectRenderData> s_pool = std::make_shared<ObjectPool>(UI3DScene$SceneObjectRenderData::new);

   private UI3DScene$SceneObjectRenderData() {
   }

   UI3DScene$SceneObjectRenderData init(SceneObject var1) {
      this.m_object = var1;
      var1.getGlobalTransform(this.m_transform);
    return this;
   }

    void release() {
      s_pool.release(this);
   }
}
} // namespace vehicles
} // namespace zombie
