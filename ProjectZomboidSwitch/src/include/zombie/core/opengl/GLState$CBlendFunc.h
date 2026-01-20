#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/GLState/Base2Ints.h"
#include "zombie/core/opengl/GLState/C2IntsValue.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    void Set(C2IntsValue var1) {
      SpriteRenderer.instance.glBlendFunc(var1.a, var1.b);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
