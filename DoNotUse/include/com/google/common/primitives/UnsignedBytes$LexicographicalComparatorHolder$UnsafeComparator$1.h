#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedExceptionAction.h"
#include "sun/misc/Unsafe.h"

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedBytes {
public:
    Unsafe run() {
      Class<Unsafe> k = Unsafe.class;

      for (Field f : k.getDeclaredFields()) {
         f.setAccessible(true);
    void* x = f.get(nullptr);
         if (k.isInstance(x)) {
            return k.cast(x);
         }
      }

      throw NoSuchFieldError("the Unsafe");
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
