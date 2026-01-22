#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoMovingObject.h"

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {


class Thumpable {
public:
    virtual ~Thumpable() = default;
    bool isDestroyed();

    void Thump(IsoMovingObject var1);

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2);

    Thumpable getThumpableFor(IsoGameCharacter var1);

    float getThumpCondition();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
