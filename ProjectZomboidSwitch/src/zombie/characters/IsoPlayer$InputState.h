#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class IsoPlayer {
public:
    bool bMelee;
    bool isAttacking;
    bool bRunning;
    bool bSprinting;
    bool isAiming;
    bool isCharging;
    bool isChargingLT;
}
} // namespace characters
} // namespace zombie
