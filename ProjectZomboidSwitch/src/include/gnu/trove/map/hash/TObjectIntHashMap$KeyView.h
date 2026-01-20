#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectIntHashMap {
public:
   protected TObjectIntHashMap$KeyView(TObjectIntHashMap var1) {
      super(var1, nullptr);
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      return std::make_shared<TObjectHashIterator>(this.this$0);
   }

    bool removeElement(K key) {
      return this.this$0.no_entry_value != this.this$0.remove(key);
   }

    bool containsElement(K key) {
      return this.this$0.contains(key);
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
