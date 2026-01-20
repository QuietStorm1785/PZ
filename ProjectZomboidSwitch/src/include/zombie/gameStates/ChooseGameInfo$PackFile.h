#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace gameStates {

class ChooseGameInfo {
public:
    const std::string name;
    const int flags;

   public ChooseGameInfo$PackFile(std::string var1, int var2) {
      this.name = var1;
      this.flags = var2;
   }
}
} // namespace gameStates
} // namespace zombie
