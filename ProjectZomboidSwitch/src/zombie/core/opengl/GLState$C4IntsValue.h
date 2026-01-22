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
    int d;

   public GLState$C4IntsValue set(int var1, int var2, int var3, int var4) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
      this.d = var4;
    return this;
   }

    bool equals(void* var1) {
      GLState$C4IntsValue var2 = (GLState$C4IntsValue)Type.tryCastTo(var1, GLState$C4IntsValue.class);
      return var2 != nullptr && var2.a == this.a && var2.b == this.b && var2.c == this.c && var2.d == this.d;
   }

    Value set(Value var1) {
      GLState$C4IntsValue var2 = (GLState$C4IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      this.c = var2.c;
      this.d = var2.d;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
