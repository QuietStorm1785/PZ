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

class TLongDoubleProcedure {
public:
    virtual ~TLongDoubleProcedure() = default;
    bool execute(long var1, double var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
