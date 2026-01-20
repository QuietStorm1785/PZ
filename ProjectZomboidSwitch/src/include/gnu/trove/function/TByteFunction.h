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

class TByteFunction {
public:
    virtual ~TByteFunction() = default;
    uint8_t execute(uint8_t var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
