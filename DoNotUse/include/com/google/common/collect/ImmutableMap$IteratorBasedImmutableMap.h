#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/IteratorBasedImmutableMap/1EntrySetImpl.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   abstract UnmodifiableIterator<Entry<K, V>> entryIterator();

   ImmutableSet<Entry<K, V>> createEntrySet() {
      return std::make_shared<1EntrySetImpl>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
