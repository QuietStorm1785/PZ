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

class TCharIntProcedure {
public:
    virtual ~TCharIntProcedure() = default;
    bool execute(char var1, int var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
