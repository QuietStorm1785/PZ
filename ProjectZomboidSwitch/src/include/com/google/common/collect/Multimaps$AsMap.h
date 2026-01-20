#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "com/google/common/collect/Multimaps/AsMap/EntrySet.h"
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   private const Multimap<K, V> multimap;

   Multimaps$AsMap(Multimap<K, V> multimap) {
      this.multimap = (Multimap<K, V>)Preconditions.checkNotNull(multimap);
   }

    int size() {
      return this.multimap.keySet().size();
   }

   protected Set<Entry<K, Collection<V>>> createEntrySet() {
      return std::make_shared<EntrySet>(this);
   }

    void removeValuesForKey(void* key) {
      this.multimap.keySet().remove(key);
   }

   public Collection<V> get(Object key) {
      return this.containsKey(key) ? this.multimap.get(key) : nullptr;
   }

   public Collection<V> remove(Object key) {
      return this.containsKey(key) ? this.multimap.removeAll(key) : nullptr;
   }

   public Set<K> keySet() {
      return this.multimap.keySet();
   }

    bool isEmpty() {
      return this.multimap.empty();
   }

    bool containsKey(void* key) {
      return this.multimap.containsKey(key);
   }

    void clear() {
      this.multimap.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
