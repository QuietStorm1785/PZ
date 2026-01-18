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

class GenericStatePermissions {
public:
  bool m_deferredMovement = false;
  bool m_playerInput = false;

  void setDeferredMovementAllowed(bool boolean0) {
    this.m_deferredMovement = boolean0;
  }

  bool isDeferredMovementAllowed(IsoGameCharacter var1) {
    return this.m_deferredMovement;
  }

  void setPlayerInputAllowed(bool boolean0) { this.m_playerInput = boolean0; }

  bool isPlayerInputAllowed(IsoGameCharacter var1) {
    return this.m_playerInput;
  }
}
} // namespace permission
} // namespace ai
} // namespace zombie
