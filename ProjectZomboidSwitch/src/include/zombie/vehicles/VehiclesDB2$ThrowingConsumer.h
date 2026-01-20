#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class VehiclesDB2 {
public:
    virtual ~VehiclesDB2() = default;
    void accept(T1 var1);
}
} // namespace vehicles
} // namespace zombie
