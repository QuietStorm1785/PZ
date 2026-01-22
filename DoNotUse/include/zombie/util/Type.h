#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class Type {
public:
   public static <R, I> R tryCastTo(I var0, Class<R> var1) {
      return (R)(var1.isInstance(var0) ? var1.cast(var0) : nullptr);
   }

    static bool asBoolean(void* var0) {
    return asBoolean();
   }

    static bool asBoolean(void* var0, bool var1) {
      if (var0 == nullptr) {
    return var1;
      } else {
    bool var2 = tryCastTo(var0, bool.class);
    return var2 = = nullptr ? var1 : var2;
      }
   }
}
} // namespace util
} // namespace zombie
