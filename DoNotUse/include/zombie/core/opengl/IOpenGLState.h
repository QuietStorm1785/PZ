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


class IOpenGLState {
public:
    T currentValue = this.defaultValue();
    bool dirty = true;

    void set(T var1) {
      if (this.dirty || !var1 == this.currentValue)) {
         this.setCurrentValue((T)var1);
         this.Set((T)var1);
      }
   }

    void setCurrentValue(T var1) {
      this.dirty = false;
      this.currentValue.set(var1);
   }

    void setDirty() {
      this.dirty = true;
   }

    T getCurrentValue() {
      return this.currentValue;
   }

   abstract T defaultValue();

   abstract void Set(T var1);
}
} // namespace opengl
} // namespace core
} // namespace zombie
