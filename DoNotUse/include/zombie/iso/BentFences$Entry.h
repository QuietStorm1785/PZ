#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {


class BentFences {
public:
    IsoDirections dir = IsoDirections.Max;
   const std::vector<std::string> unbent = std::make_unique<std::vector<>>();
   const std::vector<std::string> bent = std::make_unique<std::vector<>>();

   private BentFences$Entry() {
   }

    bool isNorth() {
      return this.dir == IsoDirections.N || this.dir == IsoDirections.S;
   }
}
} // namespace iso
} // namespace zombie
