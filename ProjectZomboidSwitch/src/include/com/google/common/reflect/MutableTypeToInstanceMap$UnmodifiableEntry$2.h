#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/reflect/MutableTypeToInstanceMap/UnmodifiableEntry.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class MutableTypeToInstanceMap {
public:
   public Entry<K, V> apply(Entry<K, V> entry) {
      return std::make_shared<UnmodifiableEntry>(entry, nullptr);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
