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

class TLongObjectProcedure {
public:
    virtual ~TLongObjectProcedure() = default;
    bool execute(long var1, T var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
