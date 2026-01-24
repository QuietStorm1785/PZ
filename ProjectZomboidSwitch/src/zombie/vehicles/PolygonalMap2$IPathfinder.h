#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "AstarCpp/Mover.h"
#include "zombie/vehicles/PolygonalMap2/Path.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    virtual ~PolygonalMap2() = default;
    void Succeeded(Path var1, Mover var2);

    void Failed(Mover var1);
}
} // namespace vehicles
} // namespace zombie
