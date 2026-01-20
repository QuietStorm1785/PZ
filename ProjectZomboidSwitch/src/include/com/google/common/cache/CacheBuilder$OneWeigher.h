#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace cache {

enum class CacheBuilder {
   INSTANCE;

    int weigh(void* key, void* value) {
    return 1;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
