#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace world {

class WorldDictionaryException : public Exception {
public:
    public WorldDictionaryException(const std::string& var1) {
      super(var1);
   }

    public WorldDictionaryException(const std::string& var1, std::exception var2) {
      super(var1, var2);
   }
}
} // namespace world
} // namespace zombie
