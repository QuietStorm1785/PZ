#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
   const Set<V> valuesDelegate;

   private AbstractBiMap$ValueSet(AbstractBiMap var1) {
      this.this$0 = var1;
      this.valuesDelegate = this.this$0.inverse.keySet();
   }

   protected Set<V> delegate() {
      return this.valuesDelegate;
   }

   public Iterator<V> iterator() {
      return Maps.valueIterator(this.this$0.entrySet().iterator());
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }

    std::string toString() {
      return this.standardToString();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
