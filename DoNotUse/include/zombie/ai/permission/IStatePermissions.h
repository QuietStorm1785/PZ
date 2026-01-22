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


class IStatePermissions {
public:
    virtual ~IStatePermissions() = default;
    bool isDeferredMovementAllowed(IsoGameCharacter var1);

    bool isPlayerInputAllowed(IsoGameCharacter var1);
}
} // namespace permission
} // namespace ai
} // namespace zombie
