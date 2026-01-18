#include "zombie/ai/states/ZombieOnGroundState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieOnGroundState ZombieOnGroundState::instance() {
 // TODO: Implement instance
 return nullptr;
}

void ZombieOnGroundState::enter(IsoGameCharacter owner) {
 // TODO: Implement enter
}

void ZombieOnGroundState::execute(IsoGameCharacter owner) {
 // TODO: Implement execute
}

bool ZombieOnGroundState::isCharacterStandingOnOther(IsoGameCharacter chrStanding, IsoGameCharacter chrProne) {
 // TODO: Implement isCharacterStandingOnOther
 return false;
}

int ZombieOnGroundState::DoCollisionBoneCheck(IsoGameCharacter character1, IsoGameCharacter character0, int int0, float float2) {
 // TODO: Implement DoCollisionBoneCheck
 return 0;
}

void ZombieOnGroundState::exit(IsoGameCharacter owner) {
 // TODO: Implement exit
}

} // namespace states
} // namespace ai
} // namespace zombie
