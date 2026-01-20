#include "zombie\iso\objects\interfaces/Thumpable.h"

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {

bool Thumpable::isDestroyed() {
    // TODO: Implement isDestroyed
    return false;
}

void Thumpable::Thump(IsoMovingObject var1) {
    // TODO: Implement Thump
}

void Thumpable::WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement WeaponHit
}

Thumpable Thumpable::getThumpableFor(IsoGameCharacter var1) {
    // TODO: Implement getThumpableFor
    return nullptr;
}

float Thumpable::getThumpCondition() {
    // TODO: Implement getThumpCondition
    return 0;
}

} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
