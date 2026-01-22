#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace procedure {

class TDoubleFloatProcedure {
public:
    virtual ~TDoubleFloatProcedure() = default;
    bool execute(double var1, float var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
