#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerFallingState : public State {
public:
   static PlayerFallingState& instance();
   void enter(IsoGameCharacter* character) override;
   void execute(IsoGameCharacter* character) override;
   void exit(IsoGameCharacter* character) override;
private:
   PlayerFallingState() = default;
}
} // namespace states
} // namespace ai
} // namespace zombie
