#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace function {

class TObjectFunction {
public:
    virtual ~TObjectFunction() = default;
    R execute(T var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
