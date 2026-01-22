#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/IOpenGLState/Value.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    int a;
    int b;

   public GLState$C2IntsValue set(int var1, int var2) {
      this.a = var1;
      this.b = var2;
    return this;
   }

    bool equals(void* var1) {
      GLState$C2IntsValue var2 = (GLState$C2IntsValue)Type.tryCastTo(var1, GLState$C2IntsValue.class);
      return var2 != nullptr && var2.a == this.a && var2.b == this.b;
   }

    Value set(Value var1) {
      GLState$C2IntsValue var2 = (GLState$C2IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
