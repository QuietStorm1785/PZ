#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/Base4Booleans.h"
#include "zombie/core/opengl/GLState/C4BooleansValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(C4BooleansValue var1) {
      SpriteRenderer.instance.glColorMask(var1.a ? 1 : 0, var1.b ? 1 : 0, var1.c ? 1 : 0, var1.d ? 1 : 0);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
