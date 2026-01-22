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

class TIntLongProcedure {
public:
    virtual ~TIntLongProcedure() = default;
    bool execute(int var1, long var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
