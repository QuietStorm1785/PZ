#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/iso/Vector3.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
    static const Vector3f forward = std::make_shared<Vector3f>();
    static const Vector3 v1 = std::make_shared<Vector3>();
    static const Vector3f v3 = std::make_shared<Vector3f>();

   private IsoGameCharacter$L_renderShadow() {
   }
}
} // namespace characters
} // namespace zombie
