#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/vehicles/UI3DScene/SceneCharacter.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneCharacter m_character;
    std::string m_boneName;

   UI3DScene$OriginBone(UI3DScene var1) {
      super(var1, "OriginBone");
   }

    SceneObjectRenderData renderMain() {
    return nullptr;
   }

    Matrix4f getGlobalTransform(Matrix4f var1) {
      return this.m_character.getBoneMatrix(this.m_boneName, var1);
   }
}
} // namespace vehicles
} // namespace zombie
