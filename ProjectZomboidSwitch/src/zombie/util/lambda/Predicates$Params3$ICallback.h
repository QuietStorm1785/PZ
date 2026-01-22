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

class Predicates {
public:
    virtual ~Predicates() = default;
    bool test(E var1, T1 var2, T2 var3, T3 var4);
}
} // namespace lambda
} // namespace util
} // namespace zombie
