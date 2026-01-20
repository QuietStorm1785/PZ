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

class TShortShortProcedure {
public:
    virtual ~TShortShortProcedure() = default;
    bool execute(short var1, short var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
