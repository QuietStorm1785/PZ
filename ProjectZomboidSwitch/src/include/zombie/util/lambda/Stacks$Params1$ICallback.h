#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/lambda/Stacks/GenericStack.h"

namespace zombie {
namespace util {
namespace lambda {


class Stacks {
public:
    virtual ~Stacks() = default;
    void accept(GenericStack var1, T1 var2);
}
} // namespace lambda
} // namespace util
} // namespace zombie
