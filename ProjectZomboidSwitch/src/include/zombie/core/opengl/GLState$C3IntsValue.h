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
    int c;

   public GLState$C3IntsValue set(int var1, int var2, int var3) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
    return this;
   }

    bool equals(void* var1) {
      GLState$C3IntsValue var2 = (GLState$C3IntsValue)Type.tryCastTo(var1, GLState$C3IntsValue.class);
      return var2 != nullptr && var2.a == this.a && var2.b == this.b && var2.c == this.c;
   }

    Value set(Value var1) {
      GLState$C3IntsValue var2 = (GLState$C3IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      this.c = var2.c;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
