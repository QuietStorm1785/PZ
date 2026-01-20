#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Synchronized/SynchronizedObject.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedEntry(Entry<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   Entry<K, V> delegate() {
      return (Entry<K, V>)super.delegate();
   }

    bool equals(void* obj) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate() == obj);
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().hashCode();
      }
   }

    K getKey() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().getKey();
      }
   }

    V getValue() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().getValue();
      }
   }

    V setValue(V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().setValue(value);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
