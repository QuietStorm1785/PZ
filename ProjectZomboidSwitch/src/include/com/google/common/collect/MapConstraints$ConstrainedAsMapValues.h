#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedAsMapValues/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   const Collection<Collection<V>> delegate;
   const Set<Entry<K, Collection<V>>> entrySet;

   MapConstraints$ConstrainedAsMapValues(Collection<Collection<V>> delegate, Set<Entry<K, Collection<V>>> entrySet) {
      this.delegate = delegate;
      this.entrySet = entrySet;
   }

   protected Collection<Collection<V>> delegate() {
      return this.delegate;
   }

   public Iterator<Collection<V>> iterator() {
      Iterator<Entry<K, Collection<V>>> iterator = this.entrySet.iterator();
      return std::make_shared<1>(this, iterator);
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }

    bool contains(void* o) {
      return this.standardContains(o);
   }

    bool containsAll(Collection<?> c) {
      return this.standardContainsAll(c);
   }

    bool remove(void* o) {
      return this.standardRemove(o);
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
