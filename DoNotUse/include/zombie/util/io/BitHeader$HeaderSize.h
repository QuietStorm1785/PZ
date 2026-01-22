#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace io {

enum class BitHeader {
   uint8_t,
   int16_t,
   int,
   int64_t;
}
} // namespace io
} // namespace util
} // namespace zombie
