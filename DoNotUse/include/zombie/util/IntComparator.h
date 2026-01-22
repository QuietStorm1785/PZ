#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class IntComparator {
public:
    virtual ~IntComparator() = default;
    int compare(int var1, int var2);
}
} // namespace util
} // namespace zombie
