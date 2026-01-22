#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace core {
namespace properties {


class PropertyContainer {
public:
    IsoFlagType flag;
    int count;
}
} // namespace properties
} // namespace core
} // namespace zombie
