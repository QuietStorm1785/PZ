#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {


class SharedStrings {
public:
   private const std::unordered_map<std::string, std::string> strings = std::make_unique<std::unordered_map<>>();

    std::string get(const std::string& var1) {
    std::string var2 = this.strings.get(var1);
      if (var2 == nullptr) {
         this.strings.put(var1, var1);
         var2 = var1;
      }

    return var2;
   }

    void clear() {
      this.strings.clear();
   }
}
} // namespace util
} // namespace zombie
