#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    IsoGameCharacter character;
    const Vector3f offset = std::make_shared<Vector3f>();
}
} // namespace vehicles
} // namespace zombie
