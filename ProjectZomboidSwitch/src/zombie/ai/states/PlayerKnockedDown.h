#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerKnockedDown : public State {
public:
    static PlayerKnockedDown& instance();
    void enter(IsoGameCharacter* character) override;
    void execute(IsoGameCharacter* character) override;
    void animEvent(IsoGameCharacter* character, AnimEvent* event) override;
    void exit(IsoGameCharacter* character) override;
private:
    PlayerKnockedDown() = default;
}
} // namespace states
} // namespace ai
} // namespace zombie
