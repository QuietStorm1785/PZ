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

class Invokers {
public:
    virtual ~Invokers() = default;
    void accept(T1 var1, T2 var2);
}
} // namespace lambda
} // namespace util
} // namespace zombie
