#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/BaseIntFloat.h"
#include "zombie/core/opengl/GLState/CIntFloatValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(CIntFloatValue var1) {
      SpriteRenderer.instance.glAlphaFunc(var1.a, var1.b);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
