#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TLongLongMapDecorator/1/1.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TLongLongMapDecorator {
public:
   TLongLongMapDecorator$1(TLongLongMapDecorator var1) {
      this.this$0 = var1;
   }

    int size() {
      return this.this$0._map.size();
   }

    bool isEmpty() {
      return this.this$0.empty();
   }

    bool contains(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
    void* k = ((Entry)o).getKey();
    void* v = ((Entry)o).getValue();
         return this.this$0.containsKey(k) && this.this$0.get(k) == v);
      }
   }

   public Iterator<Entry<int64_t, int64_t>> iterator() {
      return std::make_shared<1>(this);
   }

    bool add(int64_t> o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* o) {
    bool modified = false;
      if (this.contains(o)) {
    long key = (int64_t)((Entry)o).getKey();
         this.this$0._map.remove(this.this$0.unwrapKey(key));
         modified = true;
      }

    return modified;
   }

    bool addAll(Collection<? extends, int64_t>> c) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      this.this$0.clear();
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
