#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoBarricade.h"
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

class BarricadeAble {
public:
  virtual ~BarricadeAble() = default;
  bool isBarricaded();

  bool isBarricadeAllowed();

  IsoBarricade getBarricadeOnSameSquare();

  IsoBarricade getBarricadeOnOppositeSquare();

  IsoBarricade getBarricadeForCharacter(IsoGameCharacter chr);

  IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter chr);

  IsoGridSquare getSquare();

  IsoGridSquare getOppositeSquare();

  bool getNorth();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
