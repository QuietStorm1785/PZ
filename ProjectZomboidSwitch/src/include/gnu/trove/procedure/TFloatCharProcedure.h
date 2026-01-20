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

class TFloatCharProcedure {
public:
    virtual ~TFloatCharProcedure() = default;
    bool execute(float var1, char var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
