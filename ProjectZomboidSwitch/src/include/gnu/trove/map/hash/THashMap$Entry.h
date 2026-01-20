#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class THashMap {
public:
    K key;
    V val;
    const int index;

   THashMap$Entry(K var1, V key, int value, int index) {
      this.this$0 = var1;
      this.key = key;
      this.val = value;
      this.index = index;
   }

    K getKey() {
      return this.key;
   }

    V getValue() {
      return this.val;
   }

    V setValue(V o) {
      if (this.this$0._values[this.index] != this.val) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
    V retval = this.val;
         this.this$0._values[this.index] = o;
         this.val = o;
    return retval;
      }
   }

    bool equals(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
    Entry e2 = (Entry)o;
         return THashMap.access$700(this.this$0, this.getKey(), e2.getKey()) && THashMap.access$800(this.this$0, this.getValue(), this.getValue());
      }
   }

    int hashCode() {
      return (this.getKey() == nullptr ? 0 : this.getKey().hashCode()) ^ (this.getValue() == nullptr ? 0 : this.getValue().hashCode());
   }

    std::string toString() {
      return this.key + "=" + this.val;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
