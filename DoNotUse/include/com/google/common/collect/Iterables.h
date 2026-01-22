#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Iterables/1.h"
#include "com/google/common/collect/Iterables/10.h"
#include "com/google/common/collect/Iterables/11.h"
#include "com/google/common/collect/Iterables/12.h"
#include "com/google/common/collect/Iterables/13.h"
#include "com/google/common/collect/Iterables/2.h"
#include "com/google/common/collect/Iterables/3.h"
#include "com/google/common/collect/Iterables/4.h"
#include "com/google/common/collect/Iterables/5.h"
#include "com/google/common/collect/Iterables/6.h"
#include "com/google/common/collect/Iterables/7.h"
#include "com/google/common/collect/Iterables/8.h"
#include "com/google/common/collect/Iterables/9.h"
#include "com/google/common/collect/Iterables/UnmodifiableIterable.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
    private Iterables() {
   }

   public static <T> Iterable<T> unmodifiableIterable(Iterable<? : public T> iterable) {
      Preconditions.checkNotNull(iterable);
      return (Iterable<T>)(!(dynamic_cast<UnmodifiableIterable*>(iterable) != nullptr) && !(dynamic_cast<ImmutableCollection*>(iterable) != nullptr)
         ? std::make_shared<UnmodifiableIterable>(iterable, nullptr)
         : iterable);
   }

   public static <E> Iterable<E> unmodifiableIterable(ImmutableCollection<E> iterable) {
      return (Iterable<E>)Preconditions.checkNotNull(iterable);
   }

    static int size(Iterable<?> iterable) {
      return dynamic_cast<Collection*>(iterable) != nullptr ? ((Collection)iterable).size() : Iterators.size(iterable.iterator());
   }

    static bool contains(Iterable<?> iterable, @Nullable Object) {
      if (dynamic_cast<Collection*>(iterable) != nullptr) {
         Collection<?> collection = (Collection<?>)iterable;
         return Collections2.safeContains(collection, element);
      } else {
         return Iterators.contains(iterable.iterator(), element);
      }
   }

    static bool removeAll(Iterable<?> removeFrom, Collection<?> elementsToRemove) {
      return dynamic_cast<Collection*>(removeFrom) != nullptr
         ? ((Collection)removeFrom).removeAll((Collection<?>)Preconditions.checkNotNull(elementsToRemove))
         : Iterators.removeAll(removeFrom.iterator(), elementsToRemove);
   }

    static bool retainAll(Iterable<?> removeFrom, Collection<?> elementsToRetain) {
      return dynamic_cast<Collection*>(removeFrom) != nullptr
         ? ((Collection)removeFrom).retainAll((Collection<?>)Preconditions.checkNotNull(elementsToRetain))
         : Iterators.retainAll(removeFrom.iterator(), elementsToRetain);
   }

   public static <T> boolean removeIf(Iterable<T> removeFrom, Predicate<? super T> predicate) {
      return dynamic_cast<RandomAccess*>(removeFrom) != nullptr && dynamic_cast<List*>(removeFrom) != nullptr
         ? removeIfFromRandomAccessList((List<T>)removeFrom, (Predicate<? super T>)Preconditions.checkNotNull(predicate))
         : Iterators.removeIf(removeFrom.iterator(), predicate);
   }

   private static <T> boolean removeIfFromRandomAccessList(List<T> list, Predicate<? super T> predicate) {
    int from = 0;

    int to;
      for (to = 0; from < list.size(); from++) {
    T element = list.get(from);
         if (!predicate.apply(element)) {
            if (from > to) {
               try {
                  list.set(to, element);
               } catch (UnsupportedOperationException var6) {
                  slowRemoveIfForRemainingElements(list, predicate, to, from);
    return true;
               } catch (IllegalArgumentException var7) {
                  slowRemoveIfForRemainingElements(list, predicate, to, from);
    return true;
               }
            }

            to++;
         }
      }

      list.subList(to, list.size()).clear();
      return from != to;
   }

   private static <T> void slowRemoveIfForRemainingElements(List<T> list, Predicate<? super T> predicate, int to, int from) {
      for (int n = list.size() - 1; n > from; n--) {
         if (predicate.apply(list.get(n))) {
            list.remove(n);
         }
      }

      for (int nx = from - 1; nx >= to; nx--) {
         list.remove(nx);
      }
   }

   static <T> T removeFirstMatching(Iterable<T> removeFrom, Predicate<? super T> predicate) {
      Preconditions.checkNotNull(predicate);
      Iterator<T> iterator = removeFrom.iterator();

      while (iterator.hasNext()) {
    T next = iterator.next();
         if (predicate.apply(next)) {
            iterator.remove();
    return next;
         }
      }

    return nullptr;
   }

    static bool elementsEqual(Iterable<?> iterable1, Iterable<?> iterable2) {
      if (dynamic_cast<Collection*>(iterable1) != nullptr && dynamic_cast<Collection*>(iterable2) != nullptr) {
         Collection<?> collection1 = (Collection<?>)iterable1;
         Collection<?> collection2 = (Collection<?>)iterable2;
         if (collection1.size() != collection2.size()) {
    return false;
         }
      }

      return Iterators.elementsEqual(iterable1.iterator(), iterable2.iterator());
   }

    static std::string toString(Iterable<?> iterable) {
      return Iterators.toString(iterable.iterator());
   }

   public static <T> T getOnlyElement(Iterable<T> iterable) {
      return (T)Iterators.getOnlyElement(iterable.iterator());
   }

   public static <T> T getOnlyElement(Iterable<? : public T> iterable, @Nullable T defaultValue) {
      return (T)Iterators.getOnlyElement(iterable.iterator(), defaultValue);
   }

   public static <T> T[] toArray(Iterable<? : public T> iterable, Class<T> type) {
    return toArray();
   }

   static <T> T[] toArray(Iterable<? : public T> iterable, T[] array) {
      Collection<? : public T> collection = castOrCopyToCollection(iterable);
      return (T[])collection.toArray(array);
   }

   static Object[] toArray(Iterable<?> iterable) {
    return castOrCopyToCollection();
   }

   private static <E> Collection<E> castOrCopyToCollection(Iterable<E> iterable) {
      return (Collection<E>)(dynamic_cast<Collection*>(iterable) != nullptr ? (Collection)iterable : Lists.newArrayList(iterable.iterator()));
   }

   public static <T> boolean addAll(Collection<T> addTo, Iterable<? : public T> elementsToAdd) {
      if (dynamic_cast<Collection*>(elementsToAdd) != nullptr) {
         Collection<? : public T> c = Collections2.cast(elementsToAdd);
         return addTo.addAll(c);
      } else {
         return Iterators.addAll(addTo, ((Iterable)Preconditions.checkNotNull(elementsToAdd)).iterator());
      }
   }

    static int frequency(Iterable<?> iterable, @Nullable Object) {
      if (dynamic_cast<Multiset*>(iterable) != nullptr) {
         return ((Multiset)iterable).count(element);
      } else if (dynamic_cast<Set*>(iterable) != nullptr) {
         return ((Set)iterable).contains(element) ? 1 : 0;
      } else {
         return Iterators.frequency(iterable.iterator(), element);
      }
   }

   public static <T> Iterable<T> cycle(Iterable<T> iterable) {
      Preconditions.checkNotNull(iterable);
      return std::make_shared<1>(iterable);
   }

   public static <T> Iterable<T> cycle(T... elements) {
    return cycle();
   }

   public static <T> Iterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b) {
      return FluentIterable.concat(a, b);
   }

   public static <T> Iterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b, Iterable<? : public T> c) {
      return FluentIterable.concat(a, b, c);
   }

   public static <T> Iterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b, Iterable<? : public T> c, Iterable<? : public T> d) {
      return FluentIterable.concat(a, b, c, d);
   }

   public static <T> Iterable<T> concat(Iterable<? : public T>... inputs) {
    return concat();
   }

   public static <T> Iterable<T> concat(Iterable<? : public Iterable<? : public T>> inputs) {
      return FluentIterable.concat(inputs);
   }

   public static <T> Iterable<List<T>> partition(Iterable<T> iterable, int size) {
      Preconditions.checkNotNull(iterable);
      Preconditions.checkArgument(size > 0);
      return std::make_shared<2>(iterable, size);
   }

   public static <T> Iterable<List<T>> paddedPartition(Iterable<T> iterable, int size) {
      Preconditions.checkNotNull(iterable);
      Preconditions.checkArgument(size > 0);
      return std::make_shared<3>(iterable, size);
   }

   public static <T> Iterable<T> filter(Iterable<T> unfiltered, Predicate<? super T> retainIfTrue) {
      Preconditions.checkNotNull(unfiltered);
      Preconditions.checkNotNull(retainIfTrue);
      return std::make_shared<4>(unfiltered, retainIfTrue);
   }

   public static <T> Iterable<T> filter(Iterable<?> unfiltered, Class<T> desiredType) {
      Preconditions.checkNotNull(unfiltered);
      Preconditions.checkNotNull(desiredType);
      return std::make_shared<5>(unfiltered, desiredType);
   }

   public static <T> boolean any(Iterable<T> iterable, Predicate<? super T> predicate) {
      return Iterators.any(iterable.iterator(), predicate);
   }

   public static <T> boolean all(Iterable<T> iterable, Predicate<? super T> predicate) {
      return Iterators.all(iterable.iterator(), predicate);
   }

   public static <T> T find(Iterable<T> iterable, Predicate<? super T> predicate) {
      return (T)Iterators.find(iterable.iterator(), predicate);
   }

   public static <T> T find(Iterable<? : public T> iterable, Predicate<? super T> predicate, @Nullable T defaultValue) {
      return (T)Iterators.find(iterable.iterator(), predicate, defaultValue);
   }

   public static <T> Optional<T> tryFind(Iterable<T> iterable, Predicate<? super T> predicate) {
      return Iterators.tryFind(iterable.iterator(), predicate);
   }

   public static <T> int indexOf(Iterable<T> iterable, Predicate<? super T> predicate) {
      return Iterators.indexOf(iterable.iterator(), predicate);
   }

   public static <F, T> Iterable<T> transform(Iterable<F> fromIterable, Function<? super F, ? : public T> function) {
      Preconditions.checkNotNull(fromIterable);
      Preconditions.checkNotNull(function);
      return std::make_shared<6>(fromIterable, function);
   }

   public static <T> T get(Iterable<T> iterable, int position) {
      Preconditions.checkNotNull(iterable);
      return (T)(dynamic_cast<List*>(iterable) != nullptr ? ((List)iterable).get(position) : Iterators.get(iterable.iterator(), position));
   }

   public static <T> T get(Iterable<? : public T> iterable, int position, @Nullable T defaultValue) {
      Preconditions.checkNotNull(iterable);
      Iterators.checkNonnegative(position);
      if (dynamic_cast<List*>(iterable) != nullptr) {
         List<? : public T> list = Lists.cast(iterable);
         return (T)(position < list.size() ? list.get(position) : defaultValue);
      } else {
         Iterator<? : public T> iterator = iterable.iterator();
         Iterators.advance(iterator, position);
         return (T)Iterators.getNext(iterator, defaultValue);
      }
   }

   public static <T> T getFirst(Iterable<? : public T> iterable, @Nullable T defaultValue) {
      return (T)Iterators.getNext(iterable.iterator(), defaultValue);
   }

   public static <T> T getLast(Iterable<T> iterable) {
      if (dynamic_cast<List*>(iterable) != nullptr) {
         List<T> list = (List<T>)iterable;
         if (list.empty()) {
            throw std::make_unique<NoSuchElementException>();
         } else {
    return getLastInNonemptyList();
         }
      } else {
         return (T)Iterators.getLast(iterable.iterator());
      }
   }

   public static <T> T getLast(Iterable<? : public T> iterable, @Nullable T defaultValue) {
      if (dynamic_cast<Collection*>(iterable) != nullptr) {
         Collection<? : public T> c = Collections2.cast(iterable);
         if (c.empty()) {
    return defaultValue;
         }

         if (dynamic_cast<List*>(iterable) != nullptr) {
    return getLastInNonemptyList();
         }
      }

      return (T)Iterators.getLast(iterable.iterator(), defaultValue);
   }

   private static <T> T getLastInNonemptyList(List<T> list) {
      return list.get(list.size() - 1);
   }

   public static <T> Iterable<T> skip(Iterable<T> iterable, int numberToSkip) {
      Preconditions.checkNotNull(iterable);
      Preconditions.checkArgument(numberToSkip >= 0, "number to skip cannot be negative");
      if (dynamic_cast<List*>(iterable) != nullptr) {
         List<T> list = (List<T>)iterable;
         return std::make_shared<7>(list, numberToSkip);
      } else {
         return std::make_shared<8>(iterable, numberToSkip);
      }
   }

   public static <T> Iterable<T> limit(Iterable<T> iterable, int limitSize) {
      Preconditions.checkNotNull(iterable);
      Preconditions.checkArgument(limitSize >= 0, "limit is negative");
      return std::make_shared<9>(iterable, limitSize);
   }

   public static <T> Iterable<T> consumingIterable(Iterable<T> iterable) {
      if (dynamic_cast<std*>(iterable) != nullptr::queue) {
         return std::make_shared<10>(iterable);
      } else {
         Preconditions.checkNotNull(iterable);
         return std::make_shared<11>(iterable);
      }
   }

    static bool isEmpty(Iterable<?> iterable) {
      return dynamic_cast<Collection*>(iterable) != nullptr ? ((Collection)iterable).empty() : !iterable.iterator().hasNext();
   }

   public static <T> Iterable<T> mergeSorted(Iterable<? : public Iterable<? : public T>> iterables, Comparator<? super T> comparator) {
      Preconditions.checkNotNull(iterables, "iterables");
      Preconditions.checkNotNull(comparator, "comparator");
      Iterable<T> iterable = std::make_shared<12>(iterables, comparator);
      return std::make_shared<UnmodifiableIterable>(iterable, nullptr);
   }

   static <T> Function<Iterable<? : public T>, Iterator<? : public T>> toIterator() {
      return std::make_unique<13>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
