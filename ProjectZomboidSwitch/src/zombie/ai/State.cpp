#include <string>
#include "zombie/ai/State.h"

namespace zombie {
namespace ai {

void State::enter(IsoGameCharacter var1) {
    // TODO: Implement enter
}

void State::execute(IsoGameCharacter var1) {
    // TODO: Implement execute
}

void State::exit(IsoGameCharacter var1) {
    // TODO: Implement exit
}

void State::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // TODO: Implement animEvent
}

bool State::isAttacking(IsoGameCharacter var1) {
    // TODO: Implement isAttacking
    return false;
}

bool State::isMoving(IsoGameCharacter var1) {
    // TODO: Implement isMoving
    return false;
}

bool State::isDoingActionThatCanBeCancelled() {
    // TODO: Implement isDoingActionThatCanBeCancelled
    return false;
}

void State::getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    // TODO: Implement getDeltaModifiers
}

bool State::isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    // TODO: Implement isIgnoreCollide
    return false;
}

std::string State::getName() {
    // TODO: Implement getName
    return "";
}

IStatePermissions State::getStatePermissions() {
    // TODO: Implement getStatePermissions
    return nullptr;
}

} // namespace ai
} // namespace zombie
