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

class TObjectObjectProcedure {
public:
    virtual ~TObjectObjectProcedure() = default;
    bool execute(K var1, V var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
