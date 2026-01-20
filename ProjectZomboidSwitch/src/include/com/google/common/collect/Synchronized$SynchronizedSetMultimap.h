#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedMultimap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient Set<Entry<K, V>> entrySet;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedSetMultimap(SetMultimap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   SetMultimap<K, V> delegate() {
      return (SetMultimap<K, V>)super.delegate();
   }

   public Set<V> get(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.set(this.delegate().get(key), this.mutex);
      }
   }

   public Set<V> removeAll(Object key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeAll(key);
      }
   }

   public Set<V> replaceValues(K key, Iterable<? : public V> values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().replaceValues(key, values);
      }
   }

   public Set<Entry<K, V>> entries() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.entrySet == nullptr) {
            this.entrySet = Synchronized.set(this.delegate().entries(), this.mutex);
         }

         return this.entrySet;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
