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
    /**
     * Returns true if deferred movement is allowed for the given character.
     */
    virtual bool isDeferredMovementAllowed(const IsoGameCharacter& character) const = 0;

    /**
     * Returns true if player input is allowed for the given character.
     */
    virtual bool isPlayerInputAllowed(const IsoGameCharacter& character) const = 0;

    /**
     * Returns true if a custom permission is allowed for the given character and permission name.
     */
    virtual bool isPermissionAllowed(const IsoGameCharacter& character, const std::string& permissionName) const {
        // Default: only support deferred movement and player input
        if (permissionName == "deferredMovement") return isDeferredMovementAllowed(character);
        if (permissionName == "playerInput") return isPlayerInputAllowed(character);
        return false;
    }
}
} // namespace permission
} // namespace ai
} // namespace zombie
