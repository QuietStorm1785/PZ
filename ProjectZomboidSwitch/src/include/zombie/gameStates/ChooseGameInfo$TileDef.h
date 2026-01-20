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
    std::string name;
    int fileNumber;

   public ChooseGameInfo$TileDef(std::string var1, int var2) {
      this.name = var1;
      this.fileNumber = var2;
   }
}
} // namespace gameStates
} // namespace zombie
