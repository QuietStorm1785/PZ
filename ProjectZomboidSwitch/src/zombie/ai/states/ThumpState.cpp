#include "zombie\ai\states/ThumpState.h"

namespace zombie {
namespace ai {
namespace states {

ThumpState ThumpState::instance() {
    // TODO: Implement instance
    return nullptr;
}

void ThumpState::enter(IsoGameCharacter var1) {
    // TODO: Implement enter
}

void ThumpState::execute(IsoGameCharacter var1) {
    // TODO: Implement execute
}

void ThumpState::exit(IsoGameCharacter var1) {
    // TODO: Implement exit
}

void ThumpState::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // TODO: Implement animEvent
}

IsoPlayer ThumpState::findPlayer(int var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement findPlayer
    return nullptr;
}

bool ThumpState::lungeThroughDoor(IsoZombie var1, IsoGridSquare var2, IsoGridSquare var3) {
    // TODO: Implement lungeThroughDoor
    return false;
}

int ThumpState::getFastForwardDamageMultiplier() {
    // TODO: Implement getFastForwardDamageMultiplier
    return 0;
}

bool ThumpState::isThumpTargetValid(IsoGameCharacter var1, Thumpable var2) {
    // TODO: Implement isThumpTargetValid
    return false;
}

} // namespace states
} // namespace ai
} // namespace zombie
