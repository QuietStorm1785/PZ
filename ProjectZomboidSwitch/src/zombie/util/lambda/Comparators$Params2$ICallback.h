#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace lambda {

class Comparators {
public:
    virtual ~Comparators() = default;
    int compare(E var1, E var2, T1 var3, T2 var4);
}
} // namespace lambda
} // namespace util
} // namespace zombie
