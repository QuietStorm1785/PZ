#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/KeyList.h"
#include "com/google/common/collect/LinkedListMultimap/ValueForKeyIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   LinkedListMultimap$1(LinkedListMultimap var1, Object var2) {
      this.this$0 = var1;
      this.val$key = var2;
   }

    int size() {
      KeyList<K, V> keyList = (KeyList<K, V>)LinkedListMultimap.access$600(this.this$0).get(this.val$key);
    return keyList = = nullptr ? 0 : keyList.count;
   }

   public ListIterator<V> listIterator(int index) {
      return std::make_shared<ValueForKeyIterator>(this.this$0, this.val$key, index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
