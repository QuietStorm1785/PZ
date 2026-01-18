#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace permission {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IStatePermissions {
public:
 virtual ~IStatePermissions() = default;
 bool isDeferredMovementAllowed(IsoGameCharacter chr);

 bool isPlayerInputAllowed(IsoGameCharacter chr);
}
} // namespace permission
} // namespace ai
} // namespace zombie
