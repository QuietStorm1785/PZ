#pragma once
#include "sun/misc/Unsafe.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UtilUnsafe {
public:
private
  UtilUnsafe() {}

  static Unsafe getUnsafe() {
    if (UtilUnsafe.class.getClassLoader() == nullptr) {
      return Unsafe.getUnsafe();
    } else {
      try {
        Field field = Unsafe.class.getDeclaredField("theUnsafe");
        field.setAccessible(true);
        return (Unsafe)field.get(UtilUnsafe.class);
      } catch (Exception exception) {
        throw new RuntimeException("Could not obtain access to sun.misc.Unsafe",
                                   exception);
      }
    }
  }
}
} // namespace Collections
} // namespace core
} // namespace zombie
