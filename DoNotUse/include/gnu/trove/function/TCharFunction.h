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

class TCharFunction {
public:
    virtual ~TCharFunction() = default;
    char execute(char var1);
}
} // namespace function
} // namespace trove
} // namespace gnu
