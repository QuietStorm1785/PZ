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

class TDoubleDoubleProcedure {
public:
    virtual ~TDoubleDoubleProcedure() = default;
    bool execute(double var1, double var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
