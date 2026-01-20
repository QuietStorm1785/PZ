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

class TLongByteProcedure {
public:
    virtual ~TLongByteProcedure() = default;
    bool execute(long var1, uint8_t var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
