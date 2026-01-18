#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace ai {
namespace permission {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DefaultStatePermissions {
public:
 static const DefaultStatePermissions Instance = new DefaultStatePermissions();

 bool isDeferredMovementAllowed(IsoGameCharacter var1) {
 return true;
 }

 bool isPlayerInputAllowed(IsoGameCharacter var1) {
 return true;
 }
}
} // namespace permission
} // namespace ai
} // namespace zombie
