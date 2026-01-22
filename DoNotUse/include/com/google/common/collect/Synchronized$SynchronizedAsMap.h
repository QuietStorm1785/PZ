#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapEntries.h"
#include "com/google/common/collect/Synchronized/SynchronizedAsMapValues.h"
#include "com/google/common/collect/Synchronized/SynchronizedMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient Set<Entry<K, Collection<V>>> asMapEntrySet;
   transient Collection<Collection<V>> asMapValues;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedAsMap(Map<K, Collection<V>> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   public Collection<V> get(Object key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         Collection<V> collection = (Collection<V>)super.get(key);
    return collection = = nullptr ? nullptr : Synchronized.access$400(collection, this.mutex);
      }
   }

   public Set<Entry<K, Collection<V>>> entrySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.asMapEntrySet == nullptr) {
            this.asMapEntrySet = std::make_shared<SynchronizedAsMapEntries>(this.delegate().entrySet(), this.mutex);
         }

         return this.asMapEntrySet;
      }
   }

   public Collection<Collection<V>> values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.asMapValues == nullptr) {
            this.asMapValues = std::make_shared<SynchronizedAsMapValues>(this.delegate().values(), this.mutex);
         }

         return this.asMapValues;
      }
   }

    bool containsValue(void* o) {
      return this.values().contains(o);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
