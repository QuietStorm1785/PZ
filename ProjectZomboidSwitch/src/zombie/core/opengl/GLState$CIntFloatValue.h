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
    float b;

   public GLState$CIntFloatValue set(int var1, float var2) {
      this.a = var1;
      this.b = var2;
    return this;
   }

    bool equals(void* var1) {
      GLState$CIntFloatValue var2 = (GLState$CIntFloatValue)Type.tryCastTo(var1, GLState$CIntFloatValue.class);
      return var2 != nullptr && var2.a == this.a && var2.b == this.b;
   }

    Value set(Value var1) {
      GLState$CIntFloatValue var2 = (GLState$CIntFloatValue)var1;
      this.a = var2.a;
      this.b = var2.b;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
