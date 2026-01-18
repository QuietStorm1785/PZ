#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoMovingObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Thumpable {
public:
 virtual ~Thumpable() = default;
 bool isDestroyed();

 void Thump(IsoMovingObject thumper);

 void WeaponHit(IsoGameCharacter chr, HandWeapon weapon);

 Thumpable getThumpableFor(IsoGameCharacter chr);

 float getThumpCondition();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
