#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/Base4Ints.h"
#include "zombie/core/opengl/GLState/C4IntsValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(C4IntsValue var1) {
      SpriteRenderer.instance.glBlendFuncSeparate(var1.a, var1.b, var1.c, var1.d);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
