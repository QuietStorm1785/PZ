#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/Synchronized/SynchronizedMap.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   private transient Set<V> valueSet;
   private transient BiMap<V, K> inverse;
    static const long serialVersionUID = 0L;

   private Synchronized$SynchronizedBiMap(BiMap<K, V> delegate, @Nullable Object mutex, @Nullable BiMap<V, K> inverse) {
      super(delegate, mutex);
      this.inverse = inverse;
   }

   BiMap<K, V> delegate() {
      return (BiMap<K, V>)super.delegate();
   }

   public Set<V> values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.valueSet == nullptr) {
            this.valueSet = Synchronized.set(this.delegate().values(), this.mutex);
         }

         return this.valueSet;
      }
   }

    V forcePut(K key, V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V)this.delegate().forcePut(key, value);
      }
   }

   public BiMap<V, K> inverse() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.inverse == nullptr) {
            this.inverse = new Synchronized$SynchronizedBiMap<>(this.delegate().inverse(), this.mutex, this);
         }

         return this.inverse;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
