#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace util {

class Display {
public:
    static const std::string displayChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#¤%&/()=?'@£${[]}+|^~*-_.:,;

    static std::string display(int var0) {
      return std::string.valueOf(var0);
   }

    static std::string hexChar(char var0) {
    std::string var1 = int.toHexString(var0);
      switch (var1.length()) {
         case 1:
            return "\\u000" + var1;
         case 2:
            return "\\u00" + var1;
         case 3:
            return "\\u0" + var1;
         case 4:
            return "\\u" + var1;
         default:
            throw RuntimeException("Internal error");
      }
   }
}
} // namespace util
} // namespace util
} // namespace zombie
