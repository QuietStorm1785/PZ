#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {


class HairOutfitDefinitions {
public:
    std::string hairStyle;
    int minWorldAge;
   public std::vector<std::string> onlyFor;

   public HairOutfitDefinitions$HaircutDefinition(std::string var1, int var2, std::vector<std::string> var3) {
      this.hairStyle = var1;
      this.minWorldAge = var2;
      this.onlyFor = var3;
   }
}
} // namespace characters
} // namespace zombie
