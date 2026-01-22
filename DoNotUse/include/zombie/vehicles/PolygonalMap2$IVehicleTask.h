#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PolygonalMap2 {
public:
    virtual ~PolygonalMap2() = default;
    void init(PolygonalMap2 var1, BaseVehicle var2);

    void execute();

    void release();
}
} // namespace vehicles
} // namespace zombie
