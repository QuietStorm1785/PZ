#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectCharCustomHashMap {
public:
   private TObjectCharCustomHashMap$MapBackedView(TObjectCharCustomHashMap var1) {
      this.this$0 = var1;
   }

   public abstract boolean removeElement(E var1);

   public abstract boolean containsElement(E var1);

    bool contains(void* key) {
      return this.containsElement((E)key);
   }

    bool remove(void* o) {
      return this.removeElement((E)o);
   }

    void clear() {
      this.this$0.clear();
   }

    bool add(E obj) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int size() {
      return this.this$0.size();
   }

   public Object[] toArray() {
      Object[] result = new Object[this.size()];
      Iterator<E> e = this.iterator();

      for (int i = 0; e.hasNext(); i++) {
         result[i] = e.next();
      }

    return result;
   }

   public <T> T[] toArray(T[] a) {
    int size = this.size();
      if (a.length < size) {
         a = (T[])Array.newInstance(a.getClass().getComponentType(), size);
      }

      Iterator<E> it = this.iterator();
      Object[] result = a;

      for (int i = 0; i < size; i++) {
         result[i] = it.next();
      }

      if (a.length > size) {
         a[size] = nullptr;
      }

    return a;
   }

    bool isEmpty() {
      return this.this$0.empty();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool changed = false;
      Iterator<E> i = this.iterator();

      while (i.hasNext()) {
         if (!collection.contains(i.next())) {
            i.remove();
            changed = true;
         }
      }

    return changed;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
