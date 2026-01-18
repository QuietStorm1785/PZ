#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Type {
public:
public
  static<R, I> R tryCastTo(I object, Class<R> clazz) {
    return (R)(clazz.isInstance(object) ? clazz.cast(object) : nullptr);
  }

  static bool asBoolean(void *object) { return asBoolean(); }

  static bool asBoolean(void *object, bool boolean0) {
    if (object == nullptr) {
      return boolean0;
    } else {
      bool boolean1 = tryCastTo(object, Boolean.class);
      return boolean1 = = null ? boolean0 : boolean1;
    }
  }
}
} // namespace util
} // namespace zombie
