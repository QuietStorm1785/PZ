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

class TFloatByteProcedure {
public:
    virtual ~TFloatByteProcedure() = default;
    bool execute(float var1, uint8_t var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
