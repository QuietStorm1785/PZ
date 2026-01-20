#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap/AsMapEntries.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap/AsMapIterator.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   const transient Map<K, Collection<V>> submap;

   AbstractMapBasedMultimap$AsMap(Map<K, Collection<V>> var1, Map submap) {
      this.this$0 = var1;
      this.submap = submap;
   }

   protected Set<Entry<K, Collection<V>>> createEntrySet() {
      return std::make_shared<AsMapEntries>(this);
   }

    bool containsKey(void* key) {
      return Maps.safeContainsKey(this.submap, key);
   }

   public Collection<V> get(Object key) {
      Collection<V> collection = (Collection<V>)Maps.safeGet(this.submap, key);
    return collection = = nullptr ? nullptr : this.this$0.wrapCollection(key, collection);
   }

   public Set<K> keySet() {
      return this.this$0.keySet();
   }

    int size() {
      return this.submap.size();
   }

   public Collection<V> remove(Object key) {
      Collection<V> collection = (Collection<V>)this.submap.remove(key);
      if (collection == nullptr) {
    return nullptr;
      } else {
         Collection<V> output = this.this$0.createCollection();
         output.addAll(collection);
         AbstractMapBasedMultimap.access$220(this.this$0, collection.size());
         collection.clear();
    return output;
      }
   }

    bool equals(@Nullable Object) {
    return this = = object || this.submap == object);
   }

    int hashCode() {
      return this.submap.hashCode();
   }

    std::string toString() {
      return this.submap;
   }

    void clear() {
      if (this.submap == AbstractMapBasedMultimap.access$000(this.this$0)) {
         this.this$0.clear();
      } else {
         Iterators.clear(std::make_shared<AsMapIterator>(this));
      }
   }

   Entry<K, Collection<V>> wrapEntry(Entry<K, Collection<V>> entry) {
    K key = (K)entry.getKey();
      return Maps.immutableEntry(key, this.this$0.wrapCollection(key, (Collection)entry.getValue()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
