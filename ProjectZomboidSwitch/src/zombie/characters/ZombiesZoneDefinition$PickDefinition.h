#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/ZombiesZoneDefinition/ZZDOutfit.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"

namespace zombie {
namespace characters {


class ZombiesZoneDefinition {
public:
    Zone zone;
    ZZDOutfit table;
    bool bFemale;
}
} // namespace characters
} // namespace zombie
