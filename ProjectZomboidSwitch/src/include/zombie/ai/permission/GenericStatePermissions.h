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


class GenericStatePermissions {
public:
    bool m_deferredMovement = false;
    bool m_playerInput = false;

    void setDeferredMovementAllowed(bool var1) {
      this.m_deferredMovement = var1;
   }

    bool isDeferredMovementAllowed(IsoGameCharacter var1) {
      return this.m_deferredMovement;
   }

    void setPlayerInputAllowed(bool var1) {
      this.m_playerInput = var1;
   }

    bool isPlayerInputAllowed(IsoGameCharacter var1) {
      return this.m_playerInput;
   }
}
} // namespace permission
} // namespace ai
} // namespace zombie
