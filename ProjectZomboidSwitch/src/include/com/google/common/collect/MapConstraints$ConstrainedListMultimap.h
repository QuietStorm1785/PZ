#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedMultimap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedListMultimap(ListMultimap<K, V> delegate, MapConstraint<? super K, ? super V> constraint) {
      super(delegate, constraint);
   }

   public List<V> get(K key) {
      return (List<V>)super.get(key);
   }

   public List<V> removeAll(Object key) {
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
