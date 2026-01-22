#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace util {
namespace list {


class PZArrayUtil {
public:
   public static <E> int referencesEqual(E var0, E var1) {
    return var0 = = var1 ? 0 : 1;
   }

   public static <E> int objectsEqual(E var0, E var1) {
      return var0 != nullptr && var0 == var1) ? 0 : 1;
   }

    static int equalsIgnoreCase(const std::string& var0, const std::string& var1) {
      return StringUtils == var0, var1) ? 0 : 1;
   }
}
} // namespace list
} // namespace util
} // namespace zombie
