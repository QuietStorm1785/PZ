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
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractSetMultimap {
public:
    static const long serialVersionUID = 7431625294878419160L;

    protected AbstractSetMultimap(Collection<V>> map) {
      super(map);
   }

   abstract Set<V> createCollection();

   Set<V> createUnmodifiableEmptyCollection() {
      return ImmutableSet.of();
   }

   public Set<V> get(@Nullable K key) {
      return (Set<V>)super.get(key);
   }

   public Set<Entry<K, V>> entries() {
      return (Set<Entry<K, V>>)super.entries();
   }

   public Set<V> removeAll(@Nullable Object key) {
      return (Set<V>)super.removeAll(key);
   }

   public Set<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      return (Set<V>)super.replaceValues(key, values);
   }

   public Map<K, Collection<V>> asMap() {
      return super.asMap();
   }

    bool put(@Nullable K, @Nullable V) {
      return super.put(key, value);
   }

    bool equals(@Nullable Object) {
      return super == object);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
