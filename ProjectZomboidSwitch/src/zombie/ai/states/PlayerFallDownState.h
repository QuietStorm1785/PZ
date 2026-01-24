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
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerFallDownState : public State {
public:
    static PlayerFallDownState& instance();
    void enter(IsoGameCharacter* character) override;
    void execute(IsoGameCharacter* character) override;
    void exit(IsoGameCharacter* character) override;
    void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
private:
    PlayerFallDownState() = default;
}
} // namespace states
} // namespace ai
} // namespace zombie
