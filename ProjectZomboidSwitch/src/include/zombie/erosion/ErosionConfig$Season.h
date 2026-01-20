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
public:
    int lat = 38;
    int tempMax = 25;
    int tempMin = 0;
    int tempDiff = 7;
    int seasonLag = 31;
    float noon = 12.5F;
    int seedA = 64;
    int seedB = 128;
    int seedC = 255;
    float jan = 0.39F;
    float feb = 0.35F;
    float mar = 0.39F;
    float apr = 0.4F;
    float may = 0.35F;
    float jun = 0.37F;
    float jul = 0.29F;
    float aug = 0.26F;
    float sep = 0.23F;
    float oct = 0.23F;
    float nov = 0.3F;
    float dec = 0.32F;
}
} // namespace erosion
} // namespace zombie
