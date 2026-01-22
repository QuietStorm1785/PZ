#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/UnmodifiableMultimap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
    static const long serialVersionUID = 0L;

   Multimaps$UnmodifiableSetMultimap(SetMultimap<K, V> delegate) {
      super(delegate);
   }

   public SetMultimap<K, V> delegate() {
      return (SetMultimap<K, V>)super.delegate();
   }

   public Set<V> get(K key) {
      return Collections.unmodifiableSet(this.delegate().get(key));
   }

   public Set<Entry<K, V>> entries() {
      return Maps.unmodifiableEntrySet(this.delegate().entries());
   }

   public Set<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Set<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
