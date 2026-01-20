#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class IsoGameCharacter {
public:
    float multiplier;
    int minLevel;
    int maxLevel;
}
} // namespace characters
} // namespace zombie
