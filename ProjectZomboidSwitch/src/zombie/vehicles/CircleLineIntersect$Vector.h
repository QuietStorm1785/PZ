#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class CircleLineIntersect {
public:
    virtual ~CircleLineIntersect() = default;
    double getvx();

    double getvy();

    double getLength();
}
} // namespace vehicles
} // namespace zombie
