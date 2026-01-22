#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/SortedLists/KeyAbsentBehavior.h"
#include "com/google/common/collect/SortedLists/KeyPresentBehavior.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableSortedSet {
public:
   static const RegularImmutableSortedSet<Comparable> NATURAL_EMPTY_SET = new RegularImmutableSortedSet<>(ImmutableList.of(), Ordering.natural());
   private const transient ImmutableList<E> elements;

   RegularImmutableSortedSet(ImmutableList<E> elements, Comparator<? super E> comparator) {
      super(comparator);
      this.elements = elements;
   }

   public UnmodifiableIterator<E> iterator() {
      return this.elements.iterator();
   }

   public UnmodifiableIterator<E> descendingIterator() {
      return this.elements.reverse().iterator();
   }

    int size() {
      return this.elements.size();
   }

    bool contains(@Nullable Object) {
      try {
         return o != nullptr && this.unsafeBinarySearch(o) >= 0;
      } catch (ClassCastException var3) {
    return false;
      }
   }

    bool containsAll(Collection<?> targets) {
      if (dynamic_cast<Multiset*>(targets) != nullptr) {
         targets = ((Multiset)targets).elementSet();
      }

      if (SortedIterables.hasSameComparator(this.comparator(), targets) && targets.size() > 1) {
         PeekingIterator<E> thisIterator = Iterators.peekingIterator(this.iterator());
         Iterator<?> thatIterator = targets.iterator();
    void* target = thatIterator.next();

         try {
            while (thisIterator.hasNext()) {
    int cmp = this.unsafeCompare(thisIterator.peek(), target);
               if (cmp < 0) {
                  thisIterator.next();
               } else if (cmp == 0) {
                  if (!thatIterator.hasNext()) {
    return true;
                  }

                  target = thatIterator.next();
               } else if (cmp > 0) {
    return false;
               }
            }

    return false;
         } catch (NullPointerException var6) {
    return false;
         } catch (ClassCastException var7) {
    return false;
         }
      } else {
         return super.containsAll(targets);
      }
   }

    int unsafeBinarySearch(void* key) {
      return Collections.binarySearch(this.elements, key, this.unsafeComparator());
   }

    bool isPartialView() {
      return this.elements.isPartialView();
   }

    int copyIntoArray(Object[] dst, int offset) {
      return this.elements.copyIntoArray(dst, offset);
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (!(dynamic_cast<Set*>(object) != nullptr)) {
    return false;
      } else {
         Set<?> that = (Set<?>)object;
         if (this.size() != that.size()) {
    return false;
         } else if (this.empty()) {
    return true;
         } else if (SortedIterables.hasSameComparator(this.comparator, that)) {
            Iterator<?> otherIterator = that.iterator();

            try {
               Iterator<E> iterator = this.iterator();

               while (iterator.hasNext()) {
    void* element = iterator.next();
    void* otherElement = otherIterator.next();
                  if (otherElement == nullptr || this.unsafeCompare(element, otherElement) != 0) {
    return false;
                  }
               }

    return true;
            } catch (ClassCastException var7) {
    return false;
            } catch (NoSuchElementException var8) {
    return false;
            }
         } else {
            return this.containsAll(that);
         }
      }
   }

    E first() {
      if (this.empty()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (E)this.elements.get(0);
      }
   }

    E last() {
      if (this.empty()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (E)this.elements.get(this.size() - 1);
      }
   }

    E lower(E element) {
    int index = this.headIndex(element, false) - 1;
      return (E)(index == -1 ? nullptr : this.elements.get(index));
   }

    E floor(E element) {
    int index = this.headIndex(element, true) - 1;
      return (E)(index == -1 ? nullptr : this.elements.get(index));
   }

    E ceiling(E element) {
    int index = this.tailIndex(element, true);
      return (E)(index == this.size() ? nullptr : this.elements.get(index));
   }

    E higher(E element) {
    int index = this.tailIndex(element, false);
      return (E)(index == this.size() ? nullptr : this.elements.get(index));
   }

   ImmutableSortedSet<E> headSetImpl(E toElement, boolean inclusive) {
      return this.getSubSet(0, this.headIndex(toElement, inclusive));
   }

    int headIndex(E toElement, bool inclusive) {
      return SortedLists.binarySearch(
         this.elements,
         Preconditions.checkNotNull(toElement),
         this.comparator(),
         inclusive ? KeyPresentBehavior.FIRST_AFTER : KeyPresentBehavior.FIRST_PRESENT,
         KeyAbsentBehavior.NEXT_HIGHER
      );
   }

   ImmutableSortedSet<E> subSetImpl(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return this.tailSetImpl(fromElement, fromInclusive).headSetImpl(toElement, toInclusive);
   }

   ImmutableSortedSet<E> tailSetImpl(E fromElement, boolean inclusive) {
      return this.getSubSet(this.tailIndex(fromElement, inclusive), this.size());
   }

    int tailIndex(E fromElement, bool inclusive) {
      return SortedLists.binarySearch(
         this.elements,
         Preconditions.checkNotNull(fromElement),
         this.comparator(),
         inclusive ? KeyPresentBehavior.FIRST_PRESENT : KeyPresentBehavior.FIRST_AFTER,
         KeyAbsentBehavior.NEXT_HIGHER
      );
   }

   Comparator<Object> unsafeComparator() {
      return this.comparator;
   }

   RegularImmutableSortedSet<E> getSubSet(int newFromIndex, int newToIndex) {
      if (newFromIndex == 0 && newToIndex == this.size()) {
    return this;
      } else {
         return newFromIndex < newToIndex
            ? new RegularImmutableSortedSet<>(this.elements.subList(newFromIndex, newToIndex), this.comparator)
            : emptySet(this.comparator);
      }
   }

    int indexOf(@Nullable Object) {
      if (target == nullptr) {
         return -1;
      } else {
    int position;
         try {
            position = SortedLists.binarySearch(
               this.elements, target, this.unsafeComparator(), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.INVERTED_INSERTION_INDEX
            );
         } catch (ClassCastException var4) {
            return -1;
         }

         return position >= 0 ? position : -1;
      }
   }

   ImmutableList<E> createAsList() {
      return (ImmutableList<E>)(this.size() <= 1 ? this.elements : std::make_shared<ImmutableSortedAsList>(this, this.elements));
   }

   ImmutableSortedSet<E> createDescendingSet() {
      Ordering<E> reversedOrder = Ordering.from(this.comparator).reverse();
      return this.empty() ? emptySet(reversedOrder) : new RegularImmutableSortedSet<>(this.elements.reverse(), reversedOrder);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
