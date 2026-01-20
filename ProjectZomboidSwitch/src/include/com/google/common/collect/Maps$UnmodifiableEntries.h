#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const Collection<Entry<K, V>> entries;

   Maps$UnmodifiableEntries(Collection<Entry<K, V>> entries) {
      this.entries = entries;
   }

   protected Collection<Entry<K, V>> delegate() {
      return this.entries;
   }

   public Iterator<Entry<K, V>> iterator() {
      return Maps.unmodifiableEntryIterator(this.entries.iterator());
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
