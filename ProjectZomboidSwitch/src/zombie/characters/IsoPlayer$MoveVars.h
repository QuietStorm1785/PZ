#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace characters {


class IsoPlayer {
public:
    float moveX;
    float moveY;
    float strafeX;
    float strafeY;
    IsoDirections NewFacing;
}
} // namespace characters
} // namespace zombie
