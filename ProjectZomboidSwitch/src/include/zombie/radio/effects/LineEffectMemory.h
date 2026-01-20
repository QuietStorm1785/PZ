#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace radio {
namespace effects {


class LineEffectMemory {
public:
   private const Map<int, std::vector<std::string>> memory = std::make_unique<std::unordered_map<>>();

    void addLine(IsoPlayer var1, const std::string& var2) {
    int var3 = var1.getDescriptor().getID();
    std::vector var4;
      if (!this.memory.containsKey(var3)) {
         var4 = std::make_unique<std::vector>();
         this.memory.put(var3, var4);
      } else {
         var4 = this.memory.get(var3);
      }

      if (!var4.contains(var2)) {
         var4.push_back(var2);
      }
   }

    bool contains(IsoPlayer var1, const std::string& var2) {
    int var3 = var1.getDescriptor().getID();
      return !this.memory.containsKey(var3) ? false : this.memory.get(var3).contains(var2);
   }
}
} // namespace effects
} // namespace radio
} // namespace zombie
