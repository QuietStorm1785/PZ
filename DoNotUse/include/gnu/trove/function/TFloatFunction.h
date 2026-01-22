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

class TFloatFunction {
public:
    virtual ~TFloatFunction() = default;
    float execute(float var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
