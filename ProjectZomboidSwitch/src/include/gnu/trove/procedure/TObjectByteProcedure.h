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

class TObjectByteProcedure {
public:
    virtual ~TObjectByteProcedure() = default;
    bool execute(K var1, uint8_t var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
