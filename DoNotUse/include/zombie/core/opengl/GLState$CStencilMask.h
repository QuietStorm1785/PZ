#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/BaseInt.h"
#include "zombie/core/opengl/GLState/CIntValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(CIntValue var1) {
      SpriteRenderer.instance.glStencilMask(var1.value);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
