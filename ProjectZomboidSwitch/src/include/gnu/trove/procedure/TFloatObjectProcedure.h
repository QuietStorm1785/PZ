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

class TFloatObjectProcedure {
public:
    virtual ~TFloatObjectProcedure() = default;
    bool execute(float var1, T var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
