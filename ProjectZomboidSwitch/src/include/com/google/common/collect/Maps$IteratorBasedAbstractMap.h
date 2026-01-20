#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   public abstract int size();

   abstract Iterator<Entry<K, V>> entryIterator();

   public Set<Entry<K, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    void clear() {
      Iterators.clear(this.entryIterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
