#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IOpenGLState {
public:
  T currentValue = this.defaultValue();
  bool dirty = true;

  void set(T value) {
    if (this.dirty || !value == this.currentValue)) {
        this.setCurrentValue((T)value);
        this.Set((T)value);
      }
  }

  void setCurrentValue(T value) {
    this.dirty = false;
    this.currentValue.set(value);
  }

  void setDirty() { this.dirty = true; }

  T getCurrentValue() { return this.currentValue; }

  abstract T defaultValue();

  abstract void Set(T var1);

public
  interface Value { IOpenGLState.Value set(IOpenGLState.Value var1); }
}
} // namespace opengl
} // namespace core
} // namespace zombie
