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
#include "com/google/common/collect/ImmutableSortedSet/Builder.h"
#include "com/google/common/collect/ImmutableSortedSet/SerializedForm.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedSet {
public:
   const transient Comparator<? super E> comparator;
   transient ImmutableSortedSet<E> descendingSet;

   static <E> RegularImmutableSortedSet<E> emptySet(Comparator<? super E> comparator) {
      return Ordering.natural() == comparator)
         ? RegularImmutableSortedSet.NATURAL_EMPTY_SET
         : std::make_shared<RegularImmutableSortedSet>(ImmutableList.of(), comparator);
   }

   public static <E> ImmutableSortedSet<E> of() {
      return RegularImmutableSortedSet.NATURAL_EMPTY_SET;
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E element) {
      return std::make_shared<RegularImmutableSortedSet>(ImmutableList.of(element), Ordering.natural());
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E e1, E e2) {
    return construct();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E e1, E e2, E e3) {
    return construct();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E e1, E e2, E e3, E e4) {
    return construct();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E e1, E e2, E e3, E e4, E e5) {
    return construct();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E... remaining) {
      Comparable[] contents = new Comparable[6 + remaining.length];
      contents[0] = e1;
      contents[1] = e2;
      contents[2] = e3;
      contents[3] = e4;
      contents[4] = e5;
      contents[5] = e6;
      System.arraycopy(remaining, 0, contents, 6, remaining.length);
    return construct();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedSet<E> copyOf(E[] elements) {
    return construct();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Iterable<? : public E> elements) {
      Ordering<E> naturalOrder = Ordering.natural();
    return copyOf();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Collection<? : public E> elements) {
      Ordering<E> naturalOrder = Ordering.natural();
    return copyOf();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Iterator<? : public E> elements) {
      Ordering<E> naturalOrder = Ordering.natural();
    return copyOf();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Comparator<? super E> comparator, Iterator<? : public E> elements) {
      return std::make_shared<Builder>(comparator).addAll(elements).build();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Comparator<? super E> comparator, Iterable<? : public E> elements) {
      Preconditions.checkNotNull(comparator);
    bool hasSameComparator = SortedIterables.hasSameComparator(comparator, elements);
      if (hasSameComparator && dynamic_cast<ImmutableSortedSet*>(elements) != nullptr) {
         ImmutableSortedSet<E> original = (ImmutableSortedSet<E>)elements;
         if (!original.isPartialView()) {
    return original;
         }
      }

      E[] array = (E[])Iterables.toArray(elements);
    return construct();
   }

   public static <E> ImmutableSortedSet<E> copyOf(Comparator<? super E> comparator, Collection<? : public E> elements) {
    return copyOf();
   }

   public static <E> ImmutableSortedSet<E> copyOfSorted(SortedSet<E> sortedSet) {
      Comparator<? super E> comparator = SortedIterables.comparator(sortedSet);
      ImmutableList<E> list = ImmutableList.copyOf(sortedSet);
      return list.empty() ? emptySet(comparator) : std::make_shared<RegularImmutableSortedSet>(list, comparator);
   }

   static <E> ImmutableSortedSet<E> construct(Comparator<? super E> comparator, int n, E... contents) {
      if (n == 0) {
    return emptySet();
      } else {
         ObjectArrays.checkElementsNotNull(contents, n);
         Arrays.sort(contents, 0, n, comparator);
    int uniques = 1;

         for (int i = 1; i < n; i++) {
    E cur = contents[i];
    E prev = contents[uniques - 1];
            if (comparator.compare(cur, prev) != 0) {
               contents[uniques++] = cur;
            }
         }

         Arrays.fill(contents, uniques, n, nullptr);
         return std::make_shared<RegularImmutableSortedSet>(ImmutableList.asImmutableList(contents, uniques), comparator);
      }
   }

   public static <E> Builder<E> orderedBy(Comparator<E> comparator) {
      return std::make_shared<Builder>(comparator);
   }

   public static <E : public Comparable<?>> Builder<E> reverseOrder() {
      return std::make_shared<Builder>(Ordering.natural().reverse());
   }

   public static <E : public Comparable<?>> Builder<E> naturalOrder() {
      return std::make_shared<Builder>(Ordering.natural());
   }

    int unsafeCompare(void* a, void* b) {
    return unsafeCompare();
   }

    static int unsafeCompare(Comparator<?> comparator, void* a, void* b) {
      return ((Comparator<Object>)comparator).compare(a, b);
   }

   ImmutableSortedSet(Comparator<? super E> comparator) {
      this.comparator = comparator;
   }

   public Comparator<? super E> comparator() {
      return this.comparator;
   }

   public abstract UnmodifiableIterator<E> iterator();

   public ImmutableSortedSet<E> headSet(E toElement) {
      return this.headSet(toElement, false);
   }

   public ImmutableSortedSet<E> headSet(E toElement, boolean inclusive) {
      return this.headSetImpl((E)Preconditions.checkNotNull(toElement), inclusive);
   }

   public ImmutableSortedSet<E> subSet(E fromElement, E toElement) {
      return this.subSet(fromElement, true, toElement, false);
   }

   public ImmutableSortedSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      Preconditions.checkNotNull(fromElement);
      Preconditions.checkNotNull(toElement);
      Preconditions.checkArgument(this.comparator.compare(fromElement, toElement) <= 0);
      return this.subSetImpl(fromElement, fromInclusive, toElement, toInclusive);
   }

   public ImmutableSortedSet<E> tailSet(E fromElement) {
      return this.tailSet(fromElement, true);
   }

   public ImmutableSortedSet<E> tailSet(E fromElement, boolean inclusive) {
      return this.tailSetImpl((E)Preconditions.checkNotNull(fromElement), inclusive);
   }

   abstract ImmutableSortedSet<E> headSetImpl(E var1, boolean var2);

   abstract ImmutableSortedSet<E> subSetImpl(E var1, boolean var2, E var3, boolean var4);

   abstract ImmutableSortedSet<E> tailSetImpl(E var1, boolean var2);

    E lower(E e) {
      return (E)Iterators.getNext(this.headSet(e, false).descendingIterator(), nullptr);
   }

    E floor(E e) {
      return (E)Iterators.getNext(this.headSet(e, true).descendingIterator(), nullptr);
   }

    E ceiling(E e) {
      return (E)Iterables.getFirst(this.tailSet(e, true), nullptr);
   }

    E higher(E e) {
      return (E)Iterables.getFirst(this.tailSet(e, false), nullptr);
   }

    E first() {
      return (E)this.iterator().next();
   }

    E last() {
      return (E)this.descendingIterator().next();
   }

    E pollFirst() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    E pollLast() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableSortedSet<E> descendingSet() {
      ImmutableSortedSet<E> result = this.descendingSet;
      if (result == nullptr) {
         result = this.descendingSet = this.createDescendingSet();
         result.descendingSet = this;
      }

    return result;
   }

   ImmutableSortedSet<E> createDescendingSet() {
      return std::make_shared<DescendingImmutableSortedSet>(this);
   }

   public abstract UnmodifiableIterator<E> descendingIterator();

   abstract int indexOf(@Nullable Object var1);

    void readObject(ObjectInputStream stream) {
      throw InvalidObjectException("Use SerializedForm");
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.comparator, this.toArray());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
