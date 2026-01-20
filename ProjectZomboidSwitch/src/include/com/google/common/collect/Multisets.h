#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/1.h"
#include "com/google/common/collect/Multisets/2.h"
#include "com/google/common/collect/Multisets/3.h"
#include "com/google/common/collect/Multisets/4.h"
#include "com/google/common/collect/Multisets/5.h"
#include "com/google/common/collect/Multisets/FilteredMultiset.h"
#include "com/google/common/collect/Multisets/ImmutableEntry.h"
#include "com/google/common/collect/Multisets/MultisetIteratorImpl.h"
#include "com/google/common/collect/Multisets/UnmodifiableMultiset.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   private static const Ordering<Entry<?>> DECREASING_COUNT_ORDERING = std::make_unique<5>();

    private Multisets() {
   }

   public static <E> Multiset<E> unmodifiableMultiset(Multiset<? : public E> multiset) {
      return (Multiset<E>)(!(dynamic_cast<UnmodifiableMultiset*>(multiset) != nullptr) && !(dynamic_cast<ImmutableMultiset*>(multiset) != nullptr)
         ? std::make_shared<UnmodifiableMultiset>((Multiset)Preconditions.checkNotNull(multiset))
         : multiset);
   }

   public static <E> Multiset<E> unmodifiableMultiset(ImmutableMultiset<E> multiset) {
      return (Multiset<E>)Preconditions.checkNotNull(multiset);
   }

   public static <E> SortedMultiset<E> unmodifiableSortedMultiset(SortedMultiset<E> sortedMultiset) {
      return std::make_shared<UnmodifiableSortedMultiset>((SortedMultiset)Preconditions.checkNotNull(sortedMultiset));
   }

   public static <E> Entry<E> immutableEntry(@Nullable E e, int n) {
      return std::make_shared<ImmutableEntry>(e, n);
   }

   public static <E> Multiset<E> filter(Multiset<E> unfiltered, Predicate<? super E> predicate) {
      if (dynamic_cast<FilteredMultiset*>(unfiltered) != nullptr) {
         FilteredMultiset<E> filtered = (FilteredMultiset<E>)unfiltered;
         Predicate<E> combinedPredicate = Predicates.and(filtered.predicate, predicate);
         return std::make_shared<FilteredMultiset>(filtered.unfiltered, combinedPredicate);
      } else {
         return std::make_shared<FilteredMultiset>(unfiltered, predicate);
      }
   }

    static int inferDistinctElements(Iterable<?> elements) {
      return dynamic_cast<Multiset*>(elements) != nullptr ? ((Multiset)elements).elementSet().size() : 11;
   }

   public static <E> Multiset<E> union(Multiset<? : public E> multiset1, Multiset<? : public E> multiset2) {
      Preconditions.checkNotNull(multiset1);
      Preconditions.checkNotNull(multiset2);
      return std::make_shared<1>(multiset1, multiset2);
   }

   public static <E> Multiset<E> intersection(Multiset<E> multiset1, Multiset<?> multiset2) {
      Preconditions.checkNotNull(multiset1);
      Preconditions.checkNotNull(multiset2);
      return std::make_shared<2>(multiset1, multiset2);
   }

   public static <E> Multiset<E> sum(Multiset<? : public E> multiset1, Multiset<? : public E> multiset2) {
      Preconditions.checkNotNull(multiset1);
      Preconditions.checkNotNull(multiset2);
      return std::make_shared<3>(multiset1, multiset2);
   }

   public static <E> Multiset<E> difference(Multiset<E> multiset1, Multiset<?> multiset2) {
      Preconditions.checkNotNull(multiset1);
      Preconditions.checkNotNull(multiset2);
      return std::make_shared<4>(multiset1, multiset2);
   }

    static bool containsOccurrences(Multiset<?> superMultiset, Multiset<?> subMultiset) {
      Preconditions.checkNotNull(superMultiset);
      Preconditions.checkNotNull(subMultiset);

      for (Entry<?> entry : subMultiset.entrySet()) {
    int superCount = superMultiset.count(entry.getElement());
         if (superCount < entry.getCount()) {
    return false;
         }
      }

    return true;
   }

    static bool retainOccurrences(Multiset<?> multisetToModify, Multiset<?> multisetToRetain) {
    return retainOccurrencesImpl();
   }

   private static <E> boolean retainOccurrencesImpl(Multiset<E> multisetToModify, Multiset<?> occurrencesToRetain) {
      Preconditions.checkNotNull(multisetToModify);
      Preconditions.checkNotNull(occurrencesToRetain);
      Iterator<Entry<E>> entryIterator = multisetToModify.entrySet().iterator();
    bool changed = false;

      while (entryIterator.hasNext()) {
         Entry<E> entry = entryIterator.next();
    int retainCount = occurrencesToRetain.count(entry.getElement());
         if (retainCount == 0) {
            entryIterator.remove();
            changed = true;
         } else if (retainCount < entry.getCount()) {
            multisetToModify.setCount(entry.getElement(), retainCount);
            changed = true;
         }
      }

    return changed;
   }

    static bool removeOccurrences(Multiset<?> multisetToModify, Iterable<?> occurrencesToRemove) {
      if (dynamic_cast<Multiset*>(occurrencesToRemove) != nullptr) {
    return removeOccurrences();
      } else {
         Preconditions.checkNotNull(multisetToModify);
         Preconditions.checkNotNull(occurrencesToRemove);
    bool changed = false;

    for (auto& o : occurrencesToRemove)            changed |= multisetToModify.remove(o);
         }

    return changed;
      }
   }

    static bool removeOccurrences(Multiset<?> multisetToModify, Multiset<?> occurrencesToRemove) {
      Preconditions.checkNotNull(multisetToModify);
      Preconditions.checkNotNull(occurrencesToRemove);
    bool changed = false;
      Iterator<? : public Entry<?>> entryIterator = multisetToModify.entrySet().iterator();

      while (entryIterator.hasNext()) {
         Entry<?> entry = (Entry<?>)entryIterator.next();
    int removeCount = occurrencesToRemove.count(entry.getElement());
         if (removeCount >= entry.getCount()) {
            entryIterator.remove();
            changed = true;
         } else if (removeCount > 0) {
            multisetToModify.remove(entry.getElement(), removeCount);
            changed = true;
         }
      }

    return changed;
   }

    static bool equalsImpl(Multiset<?> multiset, @Nullable Object) {
      if (object == multiset) {
    return true;
      } else if (dynamic_cast<Multiset*>(object) != nullptr) {
         Multiset<?> that = (Multiset<?>)object;
         if (multiset.size() == that.size() && multiset.entrySet().size() == that.entrySet().size()) {
            for (Entry<?> entry : that.entrySet()) {
               if (multiset.count(entry.getElement()) != entry.getCount()) {
    return false;
               }
            }

    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

   static <E> boolean addAllImpl(Multiset<E> self, Collection<? : public E> elements) {
      if (elements.empty()) {
    return false;
      } else {
         if (dynamic_cast<Multiset*>(elements) != nullptr) {
            Multiset<? : public E> that = cast(elements);

            for (Entry<? : public E> entry : that.entrySet()) {
               self.push_back(entry.getElement(), entry.getCount());
            }
         } else {
            Iterators.addAll(self, elements.iterator());
         }

    return true;
      }
   }

    static bool removeAllImpl(Multiset<?> self, Collection<?> elementsToRemove) {
      Collection<?> collection = (Collection<?>)(dynamic_cast<Multiset*>(elementsToRemove) != nullptr ? ((Multiset)elementsToRemove).elementSet() : elementsToRemove);
      return self.elementSet().removeAll(collection);
   }

    static bool retainAllImpl(Multiset<?> self, Collection<?> elementsToRetain) {
      Preconditions.checkNotNull(elementsToRetain);
      Collection<?> collection = (Collection<?>)(dynamic_cast<Multiset*>(elementsToRetain) != nullptr ? ((Multiset)elementsToRetain).elementSet() : elementsToRetain);
      return self.elementSet().retainAll(collection);
   }

   static <E> int setCountImpl(Multiset<E> self, E element, int count) {
      CollectPreconditions.checkNonnegative(count, "count");
    int oldCount = self.count(element);
    int delta = count - oldCount;
      if (delta > 0) {
         self.push_back(element, delta);
      } else if (delta < 0) {
         self.remove(element, -delta);
      }

    return oldCount;
   }

   static <E> boolean setCountImpl(Multiset<E> self, E element, int oldCount, int newCount) {
      CollectPreconditions.checkNonnegative(oldCount, "oldCount");
      CollectPreconditions.checkNonnegative(newCount, "newCount");
      if (self.count(element) == oldCount) {
         self.setCount(element, newCount);
    return true;
      } else {
    return false;
      }
   }

   static <E> Iterator<E> iteratorImpl(Multiset<E> multiset) {
      return std::make_shared<MultisetIteratorImpl>(multiset, multiset.entrySet().iterator());
   }

    static int sizeImpl(Multiset<?> multiset) {
    long size = 0L;

      for (Entry<?> entry : multiset.entrySet()) {
         size += entry.getCount();
      }

      return Ints.saturatedCast(size);
   }

   static <T> Multiset<T> cast(Iterable<T> iterable) {
      return (Multiset<T>)iterable;
   }

   public static <E> ImmutableMultiset<E> copyHighestCountFirst(Multiset<E> multiset) {
      List<Entry<E>> sortedEntries = DECREASING_COUNT_ORDERING.immutableSortedCopy(multiset.entrySet());
      return ImmutableMultiset.copyFromEntries(sortedEntries);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
