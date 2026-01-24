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
    static std::shared_ptr<DefaultStatePermissions> Instance;

    bool isDeferredMovementAllowed(const IsoGameCharacter& character) const {
        return true;
    }

    bool isPlayerInputAllowed(const IsoGameCharacter& character) const {
        return true;
    }
}
} // namespace permission
} // namespace ai
} // namespace zombie
