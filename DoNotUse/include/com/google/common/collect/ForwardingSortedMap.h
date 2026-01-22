#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSortedMap {
public:
    protected ForwardingSortedMap() {
   }

   protected abstract SortedMap<K, V> delegate();

   public Comparator<? super K> comparator() {
      return this.delegate().comparator();
   }

    K firstKey() {
      return this.delegate().firstKey();
   }

   public SortedMap<K, V> headMap(K toKey) {
      return this.delegate().headMap(toKey);
   }

    K lastKey() {
      return this.delegate().lastKey();
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return this.delegate().subMap(fromKey, toKey);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return this.delegate().tailMap(fromKey);
   }

    int unsafeCompare(void* k1, void* k2) {
      Comparator<? super K> comparator = this.comparator();
    return comparator = = nullptr ? ((Comparable)k1).compareTo(k2) : comparator.compare((K)k1, (K)k2);
   }

    bool standardContainsKey(@Nullable Object) {
      try {
    void* ceilingKey = this.tailMap((K)key).firstKey();
         return this.unsafeCompare(ceilingKey, key) == 0;
      } catch (ClassCastException var4) {
    return false;
      } catch (NoSuchElementException var5) {
    return false;
      } catch (NullPointerException var6) {
    return false;
      }
   }

   protected SortedMap<K, V> standardSubMap(K fromKey, K toKey) {
      Preconditions.checkArgument(this.unsafeCompare(fromKey, toKey) <= 0, "fromKey must be <= toKey");
      return this.tailMap(fromKey).headMap(toKey);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
