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

class TCharCharProcedure {
public:
    virtual ~TCharCharProcedure() = default;
    bool execute(char var1, char var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
