#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {


class IPredicate {
public:
    virtual ~IPredicate() = default;
}
} // namespace util
} // namespace zombie
