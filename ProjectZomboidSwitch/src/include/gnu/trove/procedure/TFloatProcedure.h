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

class TFloatProcedure {
public:
    virtual ~TFloatProcedure() = default;
    bool execute(float var1);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
