
#pragma once
#include <cstddef>

namespace zombie {
namespace core {
namespace utils {

struct BufferInfo {
   size_t size;
   BufferInfo(size_t sz = 0) : size(sz) {}
};

} // namespace utils
} // namespace core
} // namespace zombie
