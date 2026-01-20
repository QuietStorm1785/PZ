#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace hash {

class IntHashFunction {
public:
    virtual ~IntHashFunction() = default;
    int hash(int var1);
}
} // namespace hash
} // namespace util
} // namespace zombie
