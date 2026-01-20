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


class AbstractBiMap {
public:
   const Set<Entry<K, V>> esDelegate;

   private AbstractBiMap$EntrySet(AbstractBiMap var1) {
      this.this$0 = var1;
      this.esDelegate = AbstractBiMap.access$100(this.this$0).entrySet();
   }

   protected Set<Entry<K, V>> delegate() {
      return this.esDelegate;
   }

    void clear() {
      this.this$0.clear();
   }

    bool remove(void* object) {
      if (!this.esDelegate.contains(object)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)object;
         AbstractBiMap.access$100(this.this$0.inverse).remove(entry.getValue());
         this.esDelegate.remove(entry);
    return true;
      }
   }

   public Iterator<Entry<K, V>> iterator() {
      return this.this$0.entrySetIterator();
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
