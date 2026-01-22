#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/BaseBoolean.h"
#include "zombie/core/opengl/GLState/CBooleanValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(CBooleanValue var1) {
      if (var1.value) {
         SpriteRenderer.instance.glEnable(3008);
      } else {
         SpriteRenderer.instance.glDisable(3008);
      }
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
