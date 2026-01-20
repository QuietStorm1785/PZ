#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class UnderwearDefinition {
public:
    std::string str;
    float chance;

   public UnderwearDefinition$StringChance(std::string var1, float var2) {
      this.str = var1;
      this.chance = var2;
   }
}
} // namespace characters
} // namespace zombie
