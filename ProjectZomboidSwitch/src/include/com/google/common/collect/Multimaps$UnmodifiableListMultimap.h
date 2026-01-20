#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/UnmodifiableMultimap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
    static const long serialVersionUID = 0L;

   Multimaps$UnmodifiableListMultimap(ListMultimap<K, V> delegate) {
      super(delegate);
   }

   public ListMultimap<K, V> delegate() {
      return (ListMultimap<K, V>)super.delegate();
   }

   public List<V> get(K key) {
      return Collections.unmodifiableList(this.delegate().get(key));
   }

   public List<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public List<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
