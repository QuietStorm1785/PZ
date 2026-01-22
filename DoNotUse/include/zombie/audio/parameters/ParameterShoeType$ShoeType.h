#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterShoeType {
   Barefoot(0),
   Boots(1),
   FlipFlops(2),
   Shoes(3),
   Slippers(4),
   Sneakers(5);

    const int label;

   private ParameterShoeType$ShoeType(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
