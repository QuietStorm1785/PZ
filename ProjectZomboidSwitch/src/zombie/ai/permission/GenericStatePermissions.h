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

   void setDeferredMovementAllowed(bool allowed) {
      m_deferredMovement = allowed;
   }

   bool isDeferredMovementAllowed(const IsoGameCharacter& character) const {
      return m_deferredMovement;
   }

   void setPlayerInputAllowed(bool allowed) {
      m_playerInput = allowed;
   }

   bool isPlayerInputAllowed(const IsoGameCharacter& character) const {
      return m_playerInput;
   }
}
} // namespace permission
} // namespace ai
} // namespace zombie
