#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/IOpenGLState/Value.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    int value;

   public GLState$CIntValue set(int var1) {
      this.value = var1;
    return this;
   }

    bool equals(void* var1) {
      return dynamic_cast<GLState*>(var1) != nullptr$CIntValue && ((GLState$CIntValue)var1).value == this.value;
   }

    Value set(Value var1) {
      this.value = ((GLState$CIntValue)var1).value;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
