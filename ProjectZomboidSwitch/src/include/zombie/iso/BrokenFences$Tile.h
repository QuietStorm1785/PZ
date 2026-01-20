#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace iso {


class BrokenFences {
public:
   std::vector<std::string> self = nullptr;
   std::vector<std::string> left = nullptr;
   std::vector<std::string> right = nullptr;
   std::vector<std::string> debrisN = nullptr;
   std::vector<std::string> debrisS = nullptr;
   std::vector<std::string> debrisW = nullptr;
   std::vector<std::string> debrisE = nullptr;

   private BrokenFences$Tile() {
   }

    std::string pickRandom(std::vector<std::string> var1) {
    return var1 = = nullptr ? nullptr : (std::string)PZArrayUtil.pickRandom(var1);
   }
}
} // namespace iso
} // namespace zombie
