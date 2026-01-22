#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace scripting {

class RadioScript {
public:
    std::string scriptname = "";
    int chance = 0;
    int startDelay = 0;

   public RadioScript$ExitOption(std::string var1, int var2, int var3) {
      this.scriptname = var1;
      this.chance = var2;
      this.startDelay = var3;
   }

    std::string getScriptname() {
      return this.scriptname;
   }

    int getChance() {
      return this.chance;
   }

    int getStartDelay() {
      return this.startDelay;
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
