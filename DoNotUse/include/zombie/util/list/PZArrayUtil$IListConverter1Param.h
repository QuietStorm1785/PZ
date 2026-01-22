#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace list {

class PZArrayUtil {
public:
    virtual ~PZArrayUtil() = default;
    E convert(S var1, T1 var2);
}
} // namespace list
} // namespace util
} // namespace zombie
