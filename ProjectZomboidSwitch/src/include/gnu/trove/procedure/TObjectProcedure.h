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

class TObjectProcedure {
public:
    virtual ~TObjectProcedure() = default;
    bool execute(T var1);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
