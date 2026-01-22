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

class TByteFloatProcedure {
public:
    virtual ~TByteFloatProcedure() = default;
    bool execute(uint8_t var1, float var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
