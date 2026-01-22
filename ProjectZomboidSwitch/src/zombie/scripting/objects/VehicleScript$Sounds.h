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
    bool hornEnable = false;
    std::string horn = "";
    bool backSignalEnable = false;
    std::string backSignal = "";
    std::string engine = nullptr;
    std::string engineStart = nullptr;
    std::string engineTurnOff = nullptr;
    std::string ignitionFail = nullptr;
    std::string ignitionFailNoPower = nullptr;
}
} // namespace objects
} // namespace scripting
} // namespace zombie
