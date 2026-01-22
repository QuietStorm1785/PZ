#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoWorld {
public:
    int x;
    int y;
    int zombieCount;
    IsoDirections zombieMigrateDirection;
   public int[][] from = new int[3][3];
}
} // namespace iso
} // namespace zombie
