#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace javax {
namespace vecmath {


class VecMathI18N {
public:
    static std::string getString(const std::string& var0) {
    std::string var1;
      try {
         var1 = ResourceBundle.getBundle("javax.vecmath.ExceptionStrings").getString(var0);
      } catch (MissingResourceException var3) {
         System.err.println("VecMathI18N: Error looking up: " + var0);
         var1 = var0;
      }

    return var1;
   }
}
} // namespace vecmath
} // namespace javax
