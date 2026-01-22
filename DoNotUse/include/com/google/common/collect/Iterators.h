#pragma once
#include <queue>
#include <sstream>
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
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Iterators/1.h"
#include "com/google/common/collect/Iterators/10.h"
#include "com/google/common/collect/Iterators/11.h"
#include "com/google/common/collect/Iterators/12.h"
#include "com/google/common/collect/Iterators/13.h"
#include "com/google/common/collect/Iterators/2.h"
#include "com/google/common/collect/Iterators/3.h"
#include "com/google/common/collect/Iterators/4.h"
#include "com/google/common/collect/Iterators/5.h"
#include "com/google/common/collect/Iterators/6.h"
#include "com/google/common/collect/Iterators/7.h"
#include "com/google/common/collect/Iterators/8.h"
#include "com/google/common/collect/Iterators/9.h"
#include "com/google/common/collect/Iterators/ConcatenatedIterator.h"
#include "com/google/common/collect/Iterators/MergingIterator.h"
#include "com/google/common/collect/Iterators/PeekingImpl.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   static const UnmodifiableListIterator<Object> EMPTY_LIST_ITERATOR = std::make_unique<1>();
   private static const Iterator<Object> EMPTY_MODIFIABLE_ITERATOR = std::make_unique<2>();

    private Iterators() {
   }

   static <T> UnmodifiableIterator<T> emptyIterator() {
    return emptyListIterator();
   }

   static <T> UnmodifiableListIterator<T> emptyListIterator() {
      return (UnmodifiableListIterator<T>)EMPTY_LIST_ITERATOR;
   }

   static <T> Iterator<T> emptyModifiableIterator() {
      return (Iterator<T>)EMPTY_MODIFIABLE_ITERATOR;
   }

   public static <T> UnmodifiableIterator<T> unmodifiableIterator(Iterator<? : public T> iterator) {
      Preconditions.checkNotNull(iterator);
      return (UnmodifiableIterator<T>)(dynamic_cast<UnmodifiableIterator*>(iterator) != nullptr ? (UnmodifiableIterator)iterator : std::make_shared<3>(iterator));
   }

   public static <T> UnmodifiableIterator<T> unmodifiableIterator(UnmodifiableIterator<T> iterator) {
      return (UnmodifiableIterator<T>)Preconditions.checkNotNull(iterator);
   }

    static int size(Iterator<?> iterator) {
    long count;
      for (count = 0L; iterator.hasNext(); count++) {
         iterator.next();
      }

      return Ints.saturatedCast(count);
   }

    static bool contains(Iterator<?> iterator, @Nullable Object) {
    return any();
   }

    static bool removeAll(Iterator<?> removeFrom, Collection<?> elementsToRemove) {
    return removeIf();
   }

   public static <T> boolean removeIf(Iterator<T> removeFrom, Predicate<? super T> predicate) {
      Preconditions.checkNotNull(predicate);
    bool modified = false;

      while (removeFrom.hasNext()) {
         if (predicate.apply(removeFrom.next())) {
            removeFrom.remove();
            modified = true;
         }
      }

    return modified;
   }

    static bool retainAll(Iterator<?> removeFrom, Collection<?> elementsToRetain) {
    return removeIf();
   }

    static bool elementsEqual(Iterator<?> iterator1, Iterator<?> iterator2) {
      while (iterator1.hasNext()) {
         if (!iterator2.hasNext()) {
    return false;
         }

    void* o1 = iterator1.next();
    void* o2 = iterator2.next();
         if (!Objects.equal(o1, o2)) {
    return false;
         }
      }

      return !iterator2.hasNext();
   }

    static std::string toString(Iterator<?> iterator) {
      return Collections2.STANDARD_JOINER.appendTo(std::make_unique<std::stringstream>().append('['), iterator).append(']');
   }

   public static <T> T getOnlyElement(Iterator<T> iterator) {
    T first = iterator.next();
      if (!iterator.hasNext()) {
    return first;
      } else {
    std::stringstream sb = new std::stringstream().append("expected one element but was: <").append(first);

         for (int i = 0; i < 4 && iterator.hasNext(); i++) {
            sb.append(", ").append(iterator.next());
         }

         if (iterator.hasNext()) {
            sb.append(", ...");
         }

         sb.append('>');
         throw IllegalArgumentException(sb);
      }
   }

   public static <T> T getOnlyElement(Iterator<? : public T> iterator, @Nullable T defaultValue) {
      return iterator.hasNext() ? getOnlyElement((Iterator<T>)iterator) : defaultValue;
   }

   public static <T> T[] toArray(Iterator<? : public T> iterator, Class<T> type) {
      List<T> list = Lists.newArrayList(iterator);
      return (T[])Iterables.toArray(list, type);
   }

   public static <T> boolean addAll(Collection<T> addTo, Iterator<? : public T> iterator) {
      Preconditions.checkNotNull(addTo);
      Preconditions.checkNotNull(iterator);
    bool wasModified = false;

      while (iterator.hasNext()) {
         wasModified |= addTo.push_back((T)iterator.next());
      }

    return wasModified;
   }

    static int frequency(Iterator<?> iterator, @Nullable Object) {
    return size();
   }

   public static <T> Iterator<T> cycle(Iterable<T> iterable) {
      Preconditions.checkNotNull(iterable);
      return std::make_shared<4>(iterable);
   }

   public static <T> Iterator<T> cycle(T... elements) {
    return cycle();
   }

   public static <T> Iterator<T> concat(Iterator<? : public T> a, Iterator<? : public T> b) {
      Preconditions.checkNotNull(a);
      Preconditions.checkNotNull(b);
    return concat(std::make_shared<ConsumingQueueIterator>(new);
   }

   public static <T> Iterator<T> concat(Iterator<? : public T> a, Iterator<? : public T> b, Iterator<? : public T> c) {
      Preconditions.checkNotNull(a);
      Preconditions.checkNotNull(b);
      Preconditions.checkNotNull(c);
    return concat(std::make_shared<ConsumingQueueIterator>(new);
   }

   public static <T> Iterator<T> concat(Iterator<? : public T> a, Iterator<? : public T> b, Iterator<? : public T> c, Iterator<? : public T> d) {
      Preconditions.checkNotNull(a);
      Preconditions.checkNotNull(b);
      Preconditions.checkNotNull(c);
      Preconditions.checkNotNull(d);
    return concat(std::make_shared<ConsumingQueueIterator>(new);
   }

   public static <T> Iterator<T> concat(Iterator<? : public T>... inputs) {
      for (Iterator<? : public T> input : (Iterator[])Preconditions.checkNotNull(inputs)) {
         Preconditions.checkNotNull(input);
      }

    return concat(std::make_shared<ConsumingQueueIterator>(inputs);
   }

   public static <T> Iterator<T> concat(Iterator<? : public Iterator<? : public T>> inputs) {
      return std::make_shared<ConcatenatedIterator>(inputs);
   }

   public static <T> UnmodifiableIterator<List<T>> partition(Iterator<T> iterator, int size) {
    return partitionImpl();
   }

   public static <T> UnmodifiableIterator<List<T>> paddedPartition(Iterator<T> iterator, int size) {
    return partitionImpl();
   }

   private static <T> UnmodifiableIterator<List<T>> partitionImpl(Iterator<T> iterator, int size, boolean pad) {
      Preconditions.checkNotNull(iterator);
      Preconditions.checkArgument(size > 0);
      return std::make_shared<5>(iterator, size, pad);
   }

   public static <T> UnmodifiableIterator<T> filter(Iterator<T> unfiltered, Predicate<? super T> retainIfTrue) {
      Preconditions.checkNotNull(unfiltered);
      Preconditions.checkNotNull(retainIfTrue);
      return std::make_shared<6>(unfiltered, retainIfTrue);
   }

   public static <T> UnmodifiableIterator<T> filter(Iterator<?> unfiltered, Class<T> desiredType) {
    return filter();
   }

   public static <T> boolean any(Iterator<T> iterator, Predicate<? super T> predicate) {
    return indexOf();
   }

   public static <T> boolean all(Iterator<T> iterator, Predicate<? super T> predicate) {
      Preconditions.checkNotNull(predicate);

      while (iterator.hasNext()) {
    T element = iterator.next();
         if (!predicate.apply(element)) {
    return false;
         }
      }

    return true;
   }

   public static <T> T find(Iterator<T> iterator, Predicate<? super T> predicate) {
      return (T)filter(iterator, predicate).next();
   }

   public static <T> T find(Iterator<? : public T> iterator, Predicate<? super T> predicate, @Nullable T defaultValue) {
    return getNext();
   }

   public static <T> Optional<T> tryFind(Iterator<T> iterator, Predicate<? super T> predicate) {
      UnmodifiableIterator<T> filteredIterator = filter(iterator, predicate);
      return filteredIterator.hasNext() ? Optional.of(filteredIterator.next()) : Optional.absent();
   }

   public static <T> int indexOf(Iterator<T> iterator, Predicate<? super T> predicate) {
      Preconditions.checkNotNull(predicate, "predicate");

      for (int i = 0; iterator.hasNext(); i++) {
    T current = iterator.next();
         if (predicate.apply(current)) {
    return i;
         }
      }

      return -1;
   }

   public static <F, T> Iterator<T> transform(Iterator<F> fromIterator, Function<? super F, ? : public T> function) {
      Preconditions.checkNotNull(function);
      return std::make_shared<7>(fromIterator, function);
   }

   public static <T> T get(Iterator<T> iterator, int position) {
      checkNonnegative(position);
    int skipped = advance(iterator, position);
      if (!iterator.hasNext()) {
         throw IndexOutOfBoundsException("position (" + position + ") must be less than the number of elements that remained (" + skipped + ")");
      } else {
         return iterator.next();
      }
   }

    static void checkNonnegative(int position) {
      if (position < 0) {
         throw IndexOutOfBoundsException("position (" + position + ") must not be negative");
      }
   }

   public static <T> T get(Iterator<? : public T> iterator, int position, @Nullable T defaultValue) {
      checkNonnegative(position);
      advance(iterator, position);
    return getNext();
   }

   public static <T> T getNext(Iterator<? : public T> iterator, @Nullable T defaultValue) {
      return (T)(iterator.hasNext() ? iterator.next() : defaultValue);
   }

   public static <T> T getLast(Iterator<T> iterator) {
    T current;
      do {
         current = iterator.next();
      } while (iterator.hasNext());

    return current;
   }

   public static <T> T getLast(Iterator<? : public T> iterator, @Nullable T defaultValue) {
      return iterator.hasNext() ? getLast((Iterator<T>)iterator) : defaultValue;
   }

    static int advance(Iterator<?> iterator, int numberToAdvance) {
      Preconditions.checkNotNull(iterator);
      Preconditions.checkArgument(numberToAdvance >= 0, "numberToAdvance must be nonnegative");

    int i;
      for (i = 0; i < numberToAdvance && iterator.hasNext(); i++) {
         iterator.next();
      }

    return i;
   }

   public static <T> Iterator<T> limit(Iterator<T> iterator, int limitSize) {
      Preconditions.checkNotNull(iterator);
      Preconditions.checkArgument(limitSize >= 0, "limit is negative");
      return std::make_shared<8>(limitSize, iterator);
   }

   public static <T> Iterator<T> consumingIterator(Iterator<T> iterator) {
      Preconditions.checkNotNull(iterator);
      return std::make_shared<9>(iterator);
   }

   static <T> T pollNext(Iterator<T> iterator) {
      if (iterator.hasNext()) {
    T result = iterator.next();
         iterator.remove();
    return result;
      } else {
    return nullptr;
      }
   }

    static void clear(Iterator<?> iterator) {
      Preconditions.checkNotNull(iterator);

      while (iterator.hasNext()) {
         iterator.next();
         iterator.remove();
      }
   }

   public static <T> UnmodifiableIterator<T> forArray(T... array) {
    return forArray();
   }

   static <T> UnmodifiableListIterator<T> forArray(T[] array, int offset, int length, int index) {
      Preconditions.checkArgument(length >= 0);
    int end = offset + length;
      Preconditions.checkPositionIndexes(offset, end, array.length);
      Preconditions.checkPositionIndex(index, length);
      return (UnmodifiableListIterator<T>)(length == 0 ? emptyListIterator() : std::make_shared<10>(length, index, array, offset));
   }

   public static <T> UnmodifiableIterator<T> singletonIterator(@Nullable T value) {
      return std::make_shared<11>(value);
   }

   public static <T> UnmodifiableIterator<T> forEnumeration(Enumeration<T> enumeration) {
      Preconditions.checkNotNull(enumeration);
      return std::make_shared<12>(enumeration);
   }

   public static <T> Enumeration<T> asEnumeration(Iterator<T> iterator) {
      Preconditions.checkNotNull(iterator);
      return std::make_shared<13>(iterator);
   }

   public static <T> PeekingIterator<T> peekingIterator(Iterator<? : public T> iterator) {
      return dynamic_cast<PeekingImpl*>(iterator) != nullptr ? (PeekingImpl)iterator : std::make_shared<PeekingImpl>(iterator);
   }

   public static <T> PeekingIterator<T> peekingIterator(PeekingIterator<T> iterator) {
      return (PeekingIterator<T>)Preconditions.checkNotNull(iterator);
   }

   public static <T> UnmodifiableIterator<T> mergeSorted(Iterable<? : public Iterator<? : public T>> iterators, Comparator<? super T> comparator) {
      Preconditions.checkNotNull(iterators, "iterators");
      Preconditions.checkNotNull(comparator, "comparator");
      return std::make_shared<MergingIterator>(iterators, comparator);
   }

   static <T> ListIterator<T> cast(Iterator<T> iterator) {
      return (ListIterator<T>)iterator;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
