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

class TFloatLongProcedure {
public:
    virtual ~TFloatLongProcedure() = default;
    bool execute(float var1, long var2);
}
} // namespace procedure
} // namespace trove
} // namespace gnu
