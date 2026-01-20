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

class TObjectCharProcedure {
public:
    virtual ~TObjectCharProcedure() = default;
    bool execute(K var1, char var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
