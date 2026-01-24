#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerExtState : public State {
public:
      static PlayerExtState& instance();
      void enter(IsoGameCharacter* character) override;
      void execute(IsoGameCharacter* character) override;
      void exit(IsoGameCharacter* character) override;
      void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
private:
      PlayerExtState() = default;
}
} // namespace states
} // namespace ai
} // namespace zombie
