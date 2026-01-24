#include "zombie/ai/states/PlayerOnGroundState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerOnGroundState PlayerOnGroundState::instance() {
    static PlayerOnGroundState _instance;
    return _instance;
}

void PlayerOnGroundState::enter(IsoGameCharacter var1) {
    var1.setIgnoreMovement(true);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(&var1);
    if (player) player->setBlockMovement(true);
    var1.setVariable("bAnimEnd", false);
}

void PlayerOnGroundState::execute(IsoGameCharacter var1) {
    if (!GameServer::bServer && var1.isDead()) {
        var1.die();
    } else {
        var1.setReanimateTimer(var1.getReanimateTimer() - GameTime::getInstance().getMultiplier() / 1.6F);
    }
}

void PlayerOnGroundState::exit(IsoGameCharacter var1) {
    var1.setIgnoreMovement(false);
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(&var1);
    if (player) player->setBlockMovement(false);
}

} // namespace states
} // namespace ai
} // namespace zombie
