#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace erosion {

class ErosionConfig {
:
    int tickunit = 144;
    int ticks = 0;
    int eticks = 0;
    int epoch = 0;
}
} // namespace erosion
} // namespace zombie
