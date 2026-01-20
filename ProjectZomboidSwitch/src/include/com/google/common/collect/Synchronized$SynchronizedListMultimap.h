#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedMultimap.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedListMultimap(ListMultimap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   ListMultimap<K, V> delegate() {
      return (ListMultimap<K, V>)super.delegate();
   }

   public List<V> get(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$200(this.delegate().get(key), this.mutex);
      }
   }

   public List<V> removeAll(Object key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeAll(key);
      }
   }

   public List<V> replaceValues(K key, Iterable<? : public V> values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().replaceValues(key, values);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
