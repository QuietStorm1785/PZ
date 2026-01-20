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

class TFloatFloatProcedure {
public:
    virtual ~TFloatFloatProcedure() = default;
    bool execute(float var1, float var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
