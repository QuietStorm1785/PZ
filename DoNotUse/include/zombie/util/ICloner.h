#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class ICloner {
public:
    virtual ~ICloner() = default;
    E clone(E var1);
}
} // namespace util
} // namespace zombie
