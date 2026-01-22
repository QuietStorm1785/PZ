#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "com/google/common/collect/Maps/Values.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private transient Set<Entry<K, V>> entrySet;
   private transient Set<K> keySet;
   private transient Collection<V> values;

   abstract Set<Entry<K, V>> createEntrySet();

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> result = this.entrySet;
    return result = = nullptr ? (this.entrySet = this.createEntrySet()) : result;
   }

   public Set<K> keySet() {
      Set<K> result = this.keySet;
    return result = = nullptr ? (this.keySet = this.createKeySet()) : result;
   }

   Set<K> createKeySet() {
      return std::make_shared<KeySet>(this);
   }

   public Collection<V> values() {
      Collection<V> result = this.values;
    return result = = nullptr ? (this.values = this.createValues()) : result;
   }

   Collection<V> createValues() {
      return std::make_shared<Values>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
