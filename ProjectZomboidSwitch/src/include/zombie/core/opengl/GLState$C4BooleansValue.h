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
    bool a;
    bool b;
    bool c;
    bool d;

   public GLState$C4BooleansValue set(boolean var1, boolean var2, boolean var3, boolean var4) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
      this.d = var4;
    return this;
   }

    bool equals(void* var1) {
      GLState$C4BooleansValue var2 = (GLState$C4BooleansValue)Type.tryCastTo(var1, GLState$C4BooleansValue.class);
      return var2 != nullptr && var2.a == this.a && var2.b == this.b && var2.c == this.c;
   }

    Value set(Value var1) {
      GLState$C4BooleansValue var2 = (GLState$C4BooleansValue)var1;
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
