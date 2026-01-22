#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class VehicleScript {
public:
    bool enable = false;
    std::string soundSiren0 = "";
    std::string soundSiren1 = "";
    std::string soundSiren2 = "";
}
} // namespace objects
} // namespace scripting
} // namespace zombie
