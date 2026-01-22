#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/Base3Ints.h"
#include "zombie/core/opengl/GLState/C3IntsValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(C3IntsValue var1) {
      SpriteRenderer.instance.glStencilFunc(var1.a, var1.b, var1.c);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
