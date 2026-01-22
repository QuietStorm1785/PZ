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

class TDoubleByteProcedure {
public:
    virtual ~TDoubleByteProcedure() = default;
    bool execute(double var1, uint8_t var3);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
