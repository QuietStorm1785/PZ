#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {

class AIBrainPlayerControlVars {
public:
    bool bAiming;
    bool bMelee;
    bool bBannedAttacking;
    bool initiateAttack;
    bool bRunning;
    float strafeX;
    float strafeY;
    bool JustMoved;
}
} // namespace ai
} // namespace zombie
