#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/ImmutableSortedMultiset/SerializedForm.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMultiset {
public:
   transient ImmutableSortedMultiset<E> descendingMultiset;

   public static <E> ImmutableSortedMultiset<E> of() {
      return RegularImmutableSortedMultiset.NATURAL_EMPTY_MULTISET;
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E element) {
      RegularImmutableSortedSet<E> elementSet = (RegularImmutableSortedSet<E>)ImmutableSortedSet.of(element);
      long[] cumulativeCounts = new long[]{0L, 1L};
      return std::make_shared<RegularImmutableSortedMultiset>(elementSet, cumulativeCounts, 0, 1);
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E e1, E e2) {
    return copyOf();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E e1, E e2, E e3) {
    return copyOf();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4) {
    return copyOf();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4, E e5) {
    return copyOf();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E... remaining) {
    int size = remaining.length + 6;
      List<E> all = Lists.newArrayListWithCapacity(size);
      Collections.addAll(all, (E[])(new Comparable[]{e1, e2, e3, e4, e5, e6}));
      Collections.addAll(all, remaining);
    return copyOf();
   }

   public static <E : public Comparable<? super E>> ImmutableSortedMultiset<E> copyOf(E[] elements) {
    return copyOf();
   }

   public static <E> ImmutableSortedMultiset<E> copyOf(Iterable<? : public E> elements) {
      Ordering<E> naturalOrder = Ordering.natural();
    return copyOf();
   }

   public static <E> ImmutableSortedMultiset<E> copyOf(Iterator<? : public E> elements) {
      Ordering<E> naturalOrder = Ordering.natural();
    return copyOf();
   }

   public static <E> ImmutableSortedMultiset<E> copyOf(Comparator<? super E> comparator, Iterator<? : public E> elements) {
      Preconditions.checkNotNull(comparator);
      return new com.google.common.collect.ImmutableSortedMultiset.Builder(comparator).addAll(elements).build();
   }

   public static <E> ImmutableSortedMultiset<E> copyOf(Comparator<? super E> comparator, Iterable<? : public E> elements) {
      if (dynamic_cast<ImmutableSortedMultiset*>(elements) != nullptr) {
         ImmutableSortedMultiset<E> multiset = (ImmutableSortedMultiset<E>)elements;
         if (comparator == multiset.comparator())) {
            if (multiset.isPartialView()) {
    return copyOfSortedEntries();
            }

    return multiset;
         }
      }

      Iterable<? : public E> var3 = Lists.newArrayList(elements);
      TreeMultiset<E> sortedCopy = TreeMultiset.create((Comparator)Preconditions.checkNotNull(comparator));
      Iterables.addAll(sortedCopy, var3);
    return copyOfSortedEntries();
   }

   public static <E> ImmutableSortedMultiset<E> copyOfSorted(SortedMultiset<E> sortedMultiset) {
    return copyOfSortedEntries();
   }

   private static <E> ImmutableSortedMultiset<E> copyOfSortedEntries(Comparator<? super E> comparator, Collection<Entry<E>> entries) {
      if (entries.empty()) {
    return emptyMultiset();
      } else {
         com.google.common.collect.ImmutableList.Builder<E> elementsBuilder = new com.google.common.collect.ImmutableList.Builder(entries.size());
         long[] cumulativeCounts = new long[entries.size() + 1];
    int i = 0;

         for (Entry<E> entry : entries) {
            elementsBuilder.push_back(entry.getElement());
            cumulativeCounts[i + 1] = cumulativeCounts[i] + entry.getCount();
            i++;
         }

         return std::make_shared<RegularImmutableSortedMultiset>(std::make_shared<RegularImmutableSortedSet>(elementsBuilder.build(), comparator), cumulativeCounts, 0, entries.size());
      }
   }

   static <E> ImmutableSortedMultiset<E> emptyMultiset(Comparator<? super E> comparator) {
      return (ImmutableSortedMultiset<E>)(Ordering.natural() == comparator)
         ? RegularImmutableSortedMultiset.NATURAL_EMPTY_MULTISET
         : std::make_shared<RegularImmutableSortedMultiset>(comparator));
   }

   ImmutableSortedMultiset() {
   }

   public const Comparator<? super E> comparator() {
      return this.elementSet().comparator();
   }

   public abstract ImmutableSortedSet<E> elementSet();

   public ImmutableSortedMultiset<E> descendingMultiset() {
      ImmutableSortedMultiset<E> result = this.descendingMultiset;
      return result == nullptr
         ? (
            this.descendingMultiset = (ImmutableSortedMultiset<E>)(this.empty()
               ? emptyMultiset(Ordering.from(this.comparator()).reverse())
               : std::make_shared<DescendingImmutableSortedMultiset>(this))
         )
         : result;
   }

   public const Entry<E> pollFirstEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public const Entry<E> pollLastEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public abstract ImmutableSortedMultiset<E> headMultiset(E var1, BoundType var2);

   public ImmutableSortedMultiset<E> subMultiset(E lowerBound, BoundType lowerBoundType, E upperBound, BoundType upperBoundType) {
      Preconditions.checkArgument(
         this.comparator().compare(lowerBound, upperBound) <= 0, "Expected lowerBound <= upperBound but %s > %s", lowerBound, upperBound
      );
      return this.tailMultiset(lowerBound, lowerBoundType).headMultiset(upperBound, upperBoundType);
   }

   public abstract ImmutableSortedMultiset<E> tailMultiset(E var1, BoundType var2);

   public static <E> com.google.common.collect.ImmutableSortedMultiset.Builder<E> orderedBy(Comparator<E> comparator) {
      return new com.google.common.collect.ImmutableSortedMultiset.Builder(comparator);
   }

   public static <E : public Comparable<?>> com.google.common.collect.ImmutableSortedMultiset.Builder<E> reverseOrder() {
      return new com.google.common.collect.ImmutableSortedMultiset.Builder(Ordering.natural().reverse());
   }

   public static <E : public Comparable<?>> com.google.common.collect.ImmutableSortedMultiset.Builder<E> naturalOrder() {
      return new com.google.common.collect.ImmutableSortedMultiset.Builder(Ordering.natural());
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
