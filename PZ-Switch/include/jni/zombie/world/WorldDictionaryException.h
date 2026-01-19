#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace world {

class WorldDictionaryException :  Exception {
:
     WorldDictionaryException(std::string_view var1) {
      super(var1);
   }

     WorldDictionaryException(std::string_view var1, std::exception var2) {
      super(var1, var2);
   }
}
} // namespace world
} // namespace zombie
