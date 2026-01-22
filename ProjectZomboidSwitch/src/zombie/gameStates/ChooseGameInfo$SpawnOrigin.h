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
    int x;
    int y;
    int w;
    int h;

   public ChooseGameInfo$SpawnOrigin(int var1, int var2, int var3, int var4) {
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
   }
}
} // namespace gameStates
} // namespace zombie
