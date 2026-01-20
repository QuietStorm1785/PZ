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

class TIntObjectProcedure {
public:
    virtual ~TIntObjectProcedure() = default;
    bool execute(int var1, T var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
