#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSortedSet {
public:
    protected ForwardingSortedSet() {
   }

   protected abstract SortedSet<E> delegate();

   public Comparator<? super E> comparator() {
      return this.delegate().comparator();
   }

    E first() {
      return this.delegate().first();
   }

   public SortedSet<E> headSet(E toElement) {
      return this.delegate().headSet(toElement);
   }

    E last() {
      return this.delegate().last();
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return this.delegate().subSet(fromElement, toElement);
   }

   public SortedSet<E> tailSet(E fromElement) {
      return this.delegate().tailSet(fromElement);
   }

    int unsafeCompare(void* o1, void* o2) {
      Comparator<? super E> comparator = this.comparator();
    return comparator = = nullptr ? ((Comparable)o1).compareTo(o2) : comparator.compare((E)o1, (E)o2);
   }

    bool standardContains(@Nullable Object) {
      try {
    void* ceiling = this.tailSet((E)object).first();
         return this.unsafeCompare(ceiling, object) == 0;
      } catch (ClassCastException var4) {
    return false;
      } catch (NoSuchElementException var5) {
    return false;
      } catch (NullPointerException var6) {
    return false;
      }
   }

    bool standardRemove(@Nullable Object) {
      try {
         Iterator<Object> iterator = this.tailSet((E)object).iterator();
         if (iterator.hasNext()) {
    void* ceiling = iterator.next();
            if (this.unsafeCompare(ceiling, object) == 0) {
               iterator.remove();
    return true;
            }
         }

    return false;
      } catch (ClassCastException var5) {
    return false;
      } catch (NullPointerException var6) {
    return false;
      }
   }

   protected SortedSet<E> standardSubSet(E fromElement, E toElement) {
      return this.tailSet(fromElement).headSet(toElement);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
