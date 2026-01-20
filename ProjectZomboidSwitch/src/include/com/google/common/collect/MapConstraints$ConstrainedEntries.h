#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedEntries/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   const MapConstraint<? super K, ? super V> constraint;
   const Collection<Entry<K, V>> entries;

   MapConstraints$ConstrainedEntries(Collection<Entry<K, V>> entries, MapConstraint<? super K, ? super V> constraint) {
      this.entries = entries;
      this.constraint = constraint;
   }

   protected Collection<Entry<K, V>> delegate() {
      return this.entries;
   }

   public Iterator<Entry<K, V>> iterator() {
      return std::make_shared<1>(this, this.entries.iterator());
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }

    bool contains(void* o) {
      return Maps.containsEntryImpl(this.delegate(), o);
   }

    bool containsAll(Collection<?> c) {
      return this.standardContainsAll(c);
   }

    bool remove(void* o) {
      return Maps.removeEntryImpl(this.delegate(), o);
   }

    bool removeAll(Collection<?> c) {
      return this.standardRemoveAll(c);
   }

    bool retainAll(Collection<?> c) {
      return this.standardRetainAll(c);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
