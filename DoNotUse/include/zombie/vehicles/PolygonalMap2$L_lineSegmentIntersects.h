#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    static const Vector2 v1 = std::make_shared<Vector2>();
}
} // namespace vehicles
} // namespace zombie
