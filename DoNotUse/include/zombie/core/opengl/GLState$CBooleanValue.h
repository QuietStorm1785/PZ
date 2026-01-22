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
   public static const GLState$CBooleanValue TRUE = new GLState$CBooleanValue(true);
   public static const GLState$CBooleanValue FALSE = new GLState$CBooleanValue(false);
    bool value;

   GLState$CBooleanValue(boolean var1) {
      this.value = var1;
   }

    bool equals(void* var1) {
      return dynamic_cast<GLState*>(var1) != nullptr$CBooleanValue && ((GLState$CBooleanValue)var1).value == this.value;
   }

    Value set(Value var1) {
      this.value = ((GLState$CBooleanValue)var1).value;
    return this;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
