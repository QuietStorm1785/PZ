#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerEmoteState : public State {
public:
    static PlayerEmoteState& instance();
    void enter(IsoGameCharacter* character) override;
    void execute(IsoGameCharacter* character) override;
    void exit(IsoGameCharacter* character) override;
    void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
    bool isDoingActionThatCanBeCancelled();
private:
    PlayerEmoteState() = default;
}
} // namespace states
} // namespace ai
} // namespace zombie
