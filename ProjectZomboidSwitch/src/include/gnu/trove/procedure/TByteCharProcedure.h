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

class TByteCharProcedure {
public:
    virtual ~TByteCharProcedure() = default;
    bool execute(uint8_t var1, char var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
