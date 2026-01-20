#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    const K key;
    V value;

   LocalCache$WriteThroughEntry(K var1, V key, Object value) {
      this.this$0 = var1;
      this.key = key;
      this.value = value;
   }

    K getKey() {
      return this.key;
   }

    V getValue() {
      return this.value;
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(object) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> that = (Entry<?, ?>)object;
         return this.key == that.getKey()) && this.value == that.getValue());
      }
   }

    int hashCode() {
      return this.key.hashCode() ^ this.value.hashCode();
   }

    V setValue(V newValue) {
    V oldValue = (V)this.this$0.put(this.key, newValue);
      this.value = newValue;
    return oldValue;
   }

    std::string toString() {
      return this.getKey() + "=" + this.getValue();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
