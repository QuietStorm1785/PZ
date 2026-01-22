#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Predicate.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredKeyListMultimap {
public:
   FilteredKeyListMultimap(ListMultimap<K, V> unfiltered, Predicate<? super K> keyPredicate) {
      super(unfiltered, keyPredicate);
   }

   public ListMultimap<K, V> unfiltered() {
      return (ListMultimap<K, V>)super.unfiltered();
   }

   public List<V> get(K key) {
      return (List<V>)super.get(key);
   }

   public List<V> removeAll(@Nullable Object key) {
      return (List<V>)super.removeAll(key);
   }

   public List<V> replaceValues(K key, Iterable<? : public V> values) {
      return (List<V>)super.replaceValues(key, values);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
