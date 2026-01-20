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

class TDoubleShortProcedure {
public:
    virtual ~TDoubleShortProcedure() = default;
    bool execute(double var1, short var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
