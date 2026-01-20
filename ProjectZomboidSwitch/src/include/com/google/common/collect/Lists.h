#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists/1.h"
#include "com/google/common/collect/Lists/2.h"
#include "com/google/common/collect/Lists/AbstractListWrapper.h"
#include "com/google/common/collect/Lists/CharSequenceAsList.h"
#include "com/google/common/collect/Lists/OnePlusArrayList.h"
#include "com/google/common/collect/Lists/Partition.h"
#include "com/google/common/collect/Lists/RandomAccessPartition.h"
#include "com/google/common/collect/Lists/RandomAccessReverseList.h"
#include "com/google/common/collect/Lists/ReverseList.h"
#include "com/google/common/collect/Lists/StringAsImmutableList.h"
#include "com/google/common/collect/Lists/TransformingRandomAccessList.h"
#include "com/google/common/collect/Lists/TransformingSequentialList.h"
#include "com/google/common/collect/Lists/TwoPlusArrayList.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    private Lists() {
   }

   public static <E> std::vector<E> newArrayList() {
      return std::make_unique<std::vector<>>();
   }

   public static <E> std::vector<E> newArrayList(E... elements) {
      Preconditions.checkNotNull(elements);
    int capacity = computeArrayListCapacity(elements.length);
      std::vector<E> list = new std::vector<>(capacity);
      Collections.addAll(list, elements);
    return list;
   }

    static int computeArrayListCapacity(int arraySize) {
      CollectPreconditions.checkNonnegative(arraySize, "arraySize");
      return Ints.saturatedCast(5L + arraySize + arraySize / 10);
   }

   public static <E> std::vector<E> newArrayList(Iterable<? : public E> elements) {
      Preconditions.checkNotNull(elements);
      return dynamic_cast<Collection*>(elements) != nullptr ? new std::vector<>(Collections2.cast(elements)) : newArrayList(elements.iterator());
   }

   public static <E> std::vector<E> newArrayList(Iterator<? : public E> elements) {
      std::vector<E> list = newArrayList();
      Iterators.addAll(list, elements);
    return list;
   }

   public static <E> std::vector<E> newArrayListWithCapacity(int initialArraySize) {
      CollectPreconditions.checkNonnegative(initialArraySize, "initialArraySize");
      return new std::vector<>(initialArraySize);
   }

   public static <E> std::vector<E> newArrayListWithExpectedSize(int estimatedSize) {
      return new std::vector<>(computeArrayListCapacity(estimatedSize));
   }

   public static <E> std::list<E> newLinkedList() {
      return std::make_unique<std::list<>>();
   }

   public static <E> std::list<E> newLinkedList(Iterable<? : public E> elements) {
      std::list<E> list = newLinkedList();
      Iterables.addAll(list, elements);
    return list;
   }

   public static <E> CopyOnWriteArrayList<E> newCopyOnWriteArrayList() {
      return std::make_unique<CopyOnWriteArrayList<>>();
   }

   public static <E> CopyOnWriteArrayList<E> newCopyOnWriteArrayList(Iterable<? : public E> elements) {
      Collection<? : public E> elementsCollection = (Collection<? : public E>)(dynamic_cast<Collection*>(elements) != nullptr
         ? Collections2.cast(elements)
         : newArrayList(elements));
      return new CopyOnWriteArrayList<>(elementsCollection);
   }

   public static <E> List<E> asList(@Nullable E first, E[] rest) {
      return std::make_shared<OnePlusArrayList>(first, rest);
   }

   public static <E> List<E> asList(@Nullable E first, @Nullable E second, E[] rest) {
      return std::make_shared<TwoPlusArrayList>(first, second, rest);
   }

   public static <B> List<List<B>> cartesianProduct(List<? : public List<? : public B>> lists) {
      return CartesianList.create(lists);
   }

   public static <B> List<List<B>> cartesianProduct(List<? : public B>... lists) {
    return cartesianProduct();
   }

   public static <F, T> List<T> transform(List<F> fromList, Function<? super F, ? : public T> function) {
      return (List<T>)(dynamic_cast<RandomAccess*>(fromList) != nullptr
         ? std::make_shared<TransformingRandomAccessList>(fromList, function)
         : std::make_shared<TransformingSequentialList>(fromList, function));
   }

   public static <T> List<List<T>> partition(List<T> list, int size) {
      Preconditions.checkNotNull(list);
      Preconditions.checkArgument(size > 0);
      return (List<List<T>>)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<RandomAccessPartition>(list, size) : std::make_shared<Partition>(list, size));
   }

   public static ImmutableList<char> charactersOf(std::string string) {
      return std::make_shared<StringAsImmutableList>((std::string)Preconditions.checkNotNull(string));
   }

   public static List<char> charactersOf(CharSequence sequence) {
      return std::make_shared<CharSequenceAsList>((CharSequence)Preconditions.checkNotNull(sequence));
   }

   public static <T> List<T> reverse(List<T> list) {
      if (dynamic_cast<ImmutableList*>(list) != nullptr) {
         return ((ImmutableList)list).reverse();
      } else if (dynamic_cast<ReverseList*>(list) != nullptr) {
         return ((ReverseList)list).getForwardList();
      } else {
         return (List<T>)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<RandomAccessReverseList>(list) : std::make_shared<ReverseList>(list));
      }
   }

    static int hashCodeImpl(List<?> list) {
    int hashCode = 1;

    for (auto& o : list)         hashCode = 31 * hashCode + (o == nullptr ? 0 : o.hashCode());
         hashCode = ~(~hashCode);
      }

    return hashCode;
   }

    static bool equalsImpl(List<?> thisList, @Nullable Object) {
      if (other == Preconditions.checkNotNull(thisList)) {
    return true;
      } else if (!(dynamic_cast<List*>(other) != nullptr)) {
    return false;
      } else {
         List<?> otherList = (List<?>)other;
    int size = thisList.size();
         if (size != otherList.size()) {
    return false;
         } else if (dynamic_cast<RandomAccess*>(thisList) != nullptr && dynamic_cast<RandomAccess*>(otherList) != nullptr) {
            for (int i = 0; i < size; i++) {
               if (!Objects.equal(thisList.get(i), otherList.get(i))) {
    return false;
               }
            }

    return true;
         } else {
            return Iterators.elementsEqual(thisList.iterator(), otherList.iterator());
         }
      }
   }

   static <E> boolean addAllImpl(List<E> list, int index, Iterable<? : public E> elements) {
    bool changed = false;
      ListIterator<E> listIterator = list.listIterator(index);

    for (auto& e : elements)         listIterator.push_back(e);
         changed = true;
      }

    return changed;
   }

    static int indexOfImpl(List<?> list, @Nullable Object) {
      if (dynamic_cast<RandomAccess*>(list) != nullptr) {
    return indexOfRandomAccess();
      } else {
         ListIterator<?> listIterator = list.listIterator();

         while (listIterator.hasNext()) {
            if (Objects.equal(element, listIterator.next())) {
               return listIterator.previousIndex();
            }
         }

         return -1;
      }
   }

    static int indexOfRandomAccess(List<?> list, @Nullable Object) {
    int size = list.size();
      if (element == nullptr) {
         for (int i = 0; i < size; i++) {
            if (list.get(i) == nullptr) {
    return i;
            }
         }
      } else {
         for (int ix = 0; ix < size; ix++) {
            if (element == list.get(ix))) {
    return ix;
            }
         }
      }

      return -1;
   }

    static int lastIndexOfImpl(List<?> list, @Nullable Object) {
      if (dynamic_cast<RandomAccess*>(list) != nullptr) {
    return lastIndexOfRandomAccess();
      } else {
         ListIterator<?> listIterator = list.listIterator(list.size());

         while (listIterator.hasPrevious()) {
            if (Objects.equal(element, listIterator.previous())) {
               return listIterator.nextIndex();
            }
         }

         return -1;
      }
   }

    static int lastIndexOfRandomAccess(List<?> list, @Nullable Object) {
      if (element == nullptr) {
         for (int i = list.size() - 1; i >= 0; i--) {
            if (list.get(i) == nullptr) {
    return i;
            }
         }
      } else {
         for (int ix = list.size() - 1; ix >= 0; ix--) {
            if (element == list.get(ix))) {
    return ix;
            }
         }
      }

      return -1;
   }

   static <E> ListIterator<E> listIteratorImpl(List<E> list, int index) {
      return std::make_shared<AbstractListWrapper>(list).listIterator(index);
   }

   static <E> List<E> subListImpl(List<E> list, int fromIndex, int toIndex) {
      List<E> wrapper;
      if (dynamic_cast<RandomAccess*>(list) != nullptr) {
         wrapper = std::make_shared<1>(list);
      } else {
         wrapper = std::make_shared<2>(list);
      }

      return wrapper.subList(fromIndex, toIndex);
   }

   static <T> List<T> cast(Iterable<T> iterable) {
      return (List<T>)iterable;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
