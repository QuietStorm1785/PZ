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

class TIntIntProcedure {
public:
    virtual ~TIntIntProcedure() = default;
    bool execute(int var1, int var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
