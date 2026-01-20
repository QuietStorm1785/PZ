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

class TCharByteProcedure {
public:
    virtual ~TCharByteProcedure() = default;
    bool execute(char var1, uint8_t var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
