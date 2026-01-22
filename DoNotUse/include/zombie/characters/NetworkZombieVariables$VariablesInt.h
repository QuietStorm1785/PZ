#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class NetworkZombieVariables {
public:
    static const short health = 0;
    static const short target = 1;
    static const short speedMod = 2;
    static const short timeSinceSeenFlesh = 3;
    static const short smParamTargetAngle = 4;
    static const short MAX = 5;
}
} // namespace characters
} // namespace zombie
