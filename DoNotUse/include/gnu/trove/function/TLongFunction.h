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

class TLongFunction {
public:
    virtual ~TLongFunction() = default;
    long execute(long var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
