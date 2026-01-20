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

class TByteObjectProcedure {
public:
    virtual ~TByteObjectProcedure() = default;
    bool execute(uint8_t var1, T var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
