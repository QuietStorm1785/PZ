#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {

enum class Bits {
   ContainsAll,
   HasEither,
   NotHas;
}
} // namespace utils
} // namespace core
} // namespace zombie
