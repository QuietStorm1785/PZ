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

class TIntFunction {
public:
    virtual ~TIntFunction() = default;
    int execute(int var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
