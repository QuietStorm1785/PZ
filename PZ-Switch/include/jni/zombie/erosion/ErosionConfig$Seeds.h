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
    int seedMain_0 = 16;
    int seedMain_1 = 32;
    int seedMain_2 = 64;
    int seedMoisture_0 = 96;
    int seedMoisture_1 = 128;
    int seedMoisture_2 = 144;
    int seedMinerals_0 = 196;
    int seedMinerals_1 = 255;
    int seedMinerals_2 = 0;
    int seedKudzu_0 = 200;
    int seedKudzu_1 = 125;
    int seedKudzu_2 = 50;
}
} // namespace erosion
} // namespace zombie
