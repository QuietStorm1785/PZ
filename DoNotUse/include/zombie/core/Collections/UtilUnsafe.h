#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"

namespace zombie {
namespace core {
namespace Collections {


class UtilUnsafe {
public:
    private UtilUnsafe() {
   }

    static Unsafe getUnsafe() {
      if (UtilUnsafe.class.getClassLoader() == nullptr) {
         return Unsafe.getUnsafe();
      } else {
         try {
    Field var0 = Unsafe.class.getDeclaredField("theUnsafe");
            var0.setAccessible(true);
            return (Unsafe)var0.get(UtilUnsafe.class);
         } catch (Exception var1) {
            throw RuntimeException("Could not obtain access to sun.misc.Unsafe", var1);
         }
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
