#include "zombie/ai/states/ThumpState.h"

namespace zombie {
namespace ai {
namespace states {

ThumpState ThumpState::instance() {
 // TODO: Implement instance
 return nullptr;
}

void ThumpState::enter(IsoGameCharacter owner) {
 // TODO: Implement enter
}

void ThumpState::execute(IsoGameCharacter owner) {
 // TODO: Implement execute
}

void ThumpState::exit(IsoGameCharacter owner) {
 // TODO: Implement exit
}

void ThumpState::animEvent(IsoGameCharacter owner, AnimEvent event) {
 // TODO: Implement animEvent
}

IsoPlayer ThumpState::findPlayer(int int4, int int5, int int1, int int2,
 int int6) {
 // TODO: Implement findPlayer
 return nullptr;
}

bool ThumpState::lungeThroughDoor(IsoZombie zombie0, IsoGridSquare square1,
 IsoGridSquare square0) {
 // TODO: Implement lungeThroughDoor
 return false;
}

int ThumpState::getFastForwardDamageMultiplier() {
 // TODO: Implement getFastForwardDamageMultiplier
 return 0;
}

bool ThumpState::isThumpTargetValid(IsoGameCharacter character,
 Thumpable thumpable) {
 // TODO: Implement isThumpTargetValid
 return false;
}

} // namespace states
} // namespace ai
} // namespace zombie
