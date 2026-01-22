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


class DefaultStatePermissions {
public:
    static const DefaultStatePermissions Instance = std::make_shared<DefaultStatePermissions>();

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
