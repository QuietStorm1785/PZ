#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractListMultimap {
public:
    static const long serialVersionUID = 6588350623831699109L;

    protected AbstractListMultimap(Collection<V>> map) {
      super(map);
   }

   abstract List<V> createCollection();

   List<V> createUnmodifiableEmptyCollection() {
      return ImmutableList.of();
   }

   public List<V> get(@Nullable K key) {
      return (List<V>)super.get(key);
   }

   public List<V> removeAll(@Nullable Object key) {
      return (List<V>)super.removeAll(key);
   }

   public List<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      return (List<V>)super.replaceValues(key, values);
   }

    bool put(@Nullable K, @Nullable V) {
      return super.put(key, value);
   }

   public Map<K, Collection<V>> asMap() {
      return super.asMap();
   }

    bool equals(@Nullable Object) {
      return super == object);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
