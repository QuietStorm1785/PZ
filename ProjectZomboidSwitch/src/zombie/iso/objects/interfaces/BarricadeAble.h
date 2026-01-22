#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoBarricade.h"

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {


class BarricadeAble {
public:
    virtual ~BarricadeAble() = default;
    bool isBarricaded();

    bool isBarricadeAllowed();

    IsoBarricade getBarricadeOnSameSquare();

    IsoBarricade getBarricadeOnOppositeSquare();

    IsoBarricade getBarricadeForCharacter(IsoGameCharacter var1);

    IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter var1);

    IsoGridSquare getSquare();

    IsoGridSquare getOppositeSquare();

    bool getNorth();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
