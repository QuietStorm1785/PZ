#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

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
