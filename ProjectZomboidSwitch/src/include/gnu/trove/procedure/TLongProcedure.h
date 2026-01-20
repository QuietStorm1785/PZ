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

class TLongProcedure {
public:
    virtual ~TLongProcedure() = default;
    bool execute(long var1);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
