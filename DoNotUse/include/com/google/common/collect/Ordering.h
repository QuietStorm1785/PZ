#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Ordering/ArbitraryOrderingHolder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Ordering {
public:
    static const int LEFT_IS_GREATER = 1;
    static const int RIGHT_IS_GREATER = -1;

   public static <C : public Comparable> Ordering<C> natural() {
      return NaturalOrdering.INSTANCE;
   }

   public static <T> Ordering<T> from(Comparator<T> comparator) {
      return (Ordering<T>)(dynamic_cast<Ordering*>(comparator) != nullptr ? (Ordering)comparator : std::make_shared<ComparatorOrdering>(comparator));
   }

   public static <T> Ordering<T> from(Ordering<T> ordering) {
      return (Ordering<T>)Preconditions.checkNotNull(ordering);
   }

   public static <T> Ordering<T> explicit(List<T> valuesInOrder) {
      return std::make_shared<ExplicitOrdering>(valuesInOrder);
   }

   public static <T> Ordering<T> explicit(T leastValue, T... remainingValuesInOrder) {
    return explicit();
   }

   public static Ordering<Object> allEqual() {
      return AllEqualOrdering.INSTANCE;
   }

   public static Ordering<Object> usingToString() {
      return UsingToStringOrdering.INSTANCE;
   }

   public static Ordering<Object> arbitrary() {
      return ArbitraryOrderingHolder.ARBITRARY_ORDERING;
   }

    protected Ordering() {
   }

   public <S : public T> Ordering<S> reverse() {
      return std::make_shared<ReverseOrdering>(this);
   }

   public <S : public T> Ordering<S> nullsFirst() {
      return std::make_shared<NullsFirstOrdering>(this);
   }

   public <S : public T> Ordering<S> nullsLast() {
      return std::make_shared<NullsLastOrdering>(this);
   }

   public <F> Ordering<F> onResultOf(Function<F, ? : public T> function) {
      return std::make_shared<ByFunctionOrdering>(function, this);
   }

   <T2 : public T> Ordering<Entry<T2, ?>> onKeys() {
      return this.onResultOf(Maps.keyFunction());
   }

   public <U : public T> Ordering<U> compound(Comparator<? super U> secondaryComparator) {
      return std::make_shared<CompoundOrdering>(this, (Comparator)Preconditions.checkNotNull(secondaryComparator));
   }

   public static <T> Ordering<T> compound(Iterable<? : public Comparator<? super T>> comparators) {
      return std::make_shared<CompoundOrdering>(comparators);
   }

   public <S : public T> Ordering<Iterable<S>> lexicographical() {
      return std::make_shared<LexicographicalOrdering>(this);
   }

   public abstract int compare(@Nullable T var1, @Nullable T var2);

   public <E : public T> E min(Iterator<E> iterator) {
    E minSoFar = iterator.next();

      while (iterator.hasNext()) {
         minSoFar = this.min(minSoFar, iterator.next());
      }

    return minSoFar;
   }

   public <E : public T> E min(Iterable<E> iterable) {
      return this.min(iterable.iterator());
   }

   public <E : public T> E min(@Nullable E a, @Nullable E b) {
      return this.compare((T)a, (T)b) <= 0 ? a : b;
   }

   public <E : public T> E min(@Nullable E a, @Nullable E b, @Nullable E c, E... rest) {
    E minSoFar = this.min(this.min(a, b), c);

    for (auto& r : rest)         minSoFar = this.min(minSoFar, r);
      }

    return minSoFar;
   }

   public <E : public T> E max(Iterator<E> iterator) {
    E maxSoFar = iterator.next();

      while (iterator.hasNext()) {
         maxSoFar = this.max(maxSoFar, iterator.next());
      }

    return maxSoFar;
   }

   public <E : public T> E max(Iterable<E> iterable) {
      return this.max(iterable.iterator());
   }

   public <E : public T> E max(@Nullable E a, @Nullable E b) {
      return this.compare((T)a, (T)b) >= 0 ? a : b;
   }

   public <E : public T> E max(@Nullable E a, @Nullable E b, @Nullable E c, E... rest) {
    E maxSoFar = this.max(this.max(a, b), c);

    for (auto& r : rest)         maxSoFar = this.max(maxSoFar, r);
      }

    return maxSoFar;
   }

   public <E : public T> List<E> leastOf(Iterable<E> iterable, int k) {
      if (dynamic_cast<Collection*>(iterable) != nullptr) {
         Collection<E> collection = (Collection<E>)iterable;
         if (collection.size() <= 2L * k) {
            E[] array = (E[])collection.toArray();
            Arrays.sort(array, this);
            if (array.length > k) {
               array = (E[])ObjectArrays.arraysCopyOf(array, k);
            }

            return Collections.unmodifiableList(Arrays.asList(array));
         }
      }

      return this.leastOf(iterable.iterator(), k);
   }

   public <E : public T> List<E> leastOf(Iterator<E> iterator, int k) {
      Preconditions.checkNotNull(iterator);
      CollectPreconditions.checkNonnegative(k, "k");
      if (k == 0 || !iterator.hasNext()) {
         return ImmutableList.of();
      } else if (k >= 1073741823) {
         std::vector<E> list = Lists.newArrayList(iterator);
         Collections.sort(list, this);
         if (list.size() > k) {
            list.subList(k, list.size()).clear();
         }

         list.trimToSize();
         return Collections.unmodifiableList(list);
      } else {
         TopKSelector<E> selector = TopKSelector.least(k, this);
         selector.offerAll(iterator);
         return selector.topK();
      }
   }

   public <E : public T> List<E> greatestOf(Iterable<E> iterable, int k) {
      return this.reverse().leastOf(iterable, k);
   }

   public <E : public T> List<E> greatestOf(Iterator<E> iterator, int k) {
      return this.reverse().leastOf(iterator, k);
   }

   public <E : public T> List<E> sortedCopy(Iterable<E> elements) {
      E[] array = (E[])Iterables.toArray(elements);
      Arrays.sort(array, this);
      return Lists.newArrayList(Arrays.asList(array));
   }

   public <E : public T> ImmutableList<E> immutableSortedCopy(Iterable<E> elements) {
      E[] array = (E[])Iterables.toArray(elements);

    for (auto& e : array)         Preconditions.checkNotNull(e);
      }

      Arrays.sort(array, this);
      return ImmutableList.asImmutableList(array);
   }

    bool isOrdered(Iterable<? extends) {
      Iterator<? : public T> it = iterable.iterator();
      if (it.hasNext()) {
    T prev = (T)it.next();

         while (it.hasNext()) {
    T next = (T)it.next();
            if (this.compare(prev, next) > 0) {
    return false;
            }

            prev = next;
         }
      }

    return true;
   }

    bool isStrictlyOrdered(Iterable<? extends) {
      Iterator<? : public T> it = iterable.iterator();
      if (it.hasNext()) {
    T prev = (T)it.next();

         while (it.hasNext()) {
    T next = (T)it.next();
            if (this.compare(prev, next) >= 0) {
    return false;
            }

            prev = next;
         }
      }

    return true;
   }

    int binarySearch(List<? extends, @Nullable T) {
      return Collections.binarySearch(sortedList, key, this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
