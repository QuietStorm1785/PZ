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

class TIntProcedure {
public:
    virtual ~TIntProcedure() = default;
    bool execute(int var1);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
