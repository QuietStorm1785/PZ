#pragma once
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Sets/1.h"
#include "com/google/common/collect/Sets/2.h"
#include "com/google/common/collect/Sets/3.h"
#include "com/google/common/collect/Sets/4.h"
#include "com/google/common/collect/Sets/CartesianSet.h"
#include "com/google/common/collect/Sets/FilteredNavigableSet.h"
#include "com/google/common/collect/Sets/FilteredSet.h"
#include "com/google/common/collect/Sets/FilteredSortedSet.h"
#include "com/google/common/collect/Sets/PowerSet.h"
#include "com/google/common/collect/Sets/SetView.h"
#include "com/google/common/collect/Sets/UnmodifiableNavigableSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
    private Sets() {
   }

   public static <E : public Enum<E>> ImmutableSet<E> immutableEnumSet(E anElement, E... otherElements) {
      return ImmutableEnumSet.asImmutable(EnumSet.of(anElement, otherElements));
   }

   public static <E : public Enum<E>> ImmutableSet<E> immutableEnumSet(Iterable<E> elements) {
      if (dynamic_cast<ImmutableEnumSet*>(elements) != nullptr) {
         return (ImmutableEnumSet)elements;
      } else if (dynamic_cast<Collection*>(elements) != nullptr) {
         Collection<E> collection = (Collection<E>)elements;
         return collection.empty() ? ImmutableSet.of() : ImmutableEnumSet.asImmutable(EnumSet.copyOf(collection));
      } else {
         Iterator<E> itr = elements.iterator();
         if (itr.hasNext()) {
            EnumSet<E> enumSet = EnumSet.of(itr.next());
            Iterators.addAll(enumSet, itr);
            return ImmutableEnumSet.asImmutable(enumSet);
         } else {
            return ImmutableSet.of();
         }
      }
   }

   public static <E : public Enum<E>> EnumSet<E> newEnumSet(Iterable<E> iterable, Class<E> elementType) {
      EnumSet<E> set = EnumSet.noneOf(elementType);
      Iterables.addAll(set, iterable);
    return set;
   }

   public static <E> std::unordered_set<E> newHashSet() {
      return std::make_unique<std::unordered_set<>>();
   }

   public static <E> std::unordered_set<E> newHashSet(E... elements) {
      std::unordered_set<E> set = newHashSetWithExpectedSize(elements.length);
      Collections.addAll(set, elements);
    return set;
   }

   public static <E> std::unordered_set<E> newHashSetWithExpectedSize(int expectedSize) {
      return new std::unordered_set<>(Maps.capacity(expectedSize));
   }

   public static <E> std::unordered_set<E> newHashSet(Iterable<? : public E> elements) {
      return dynamic_cast<Collection*>(elements) != nullptr ? new std::unordered_set<>(Collections2.cast(elements)) : newHashSet(elements.iterator());
   }

   public static <E> std::unordered_set<E> newHashSet(Iterator<? : public E> elements) {
      std::unordered_set<E> set = newHashSet();
      Iterators.addAll(set, elements);
    return set;
   }

   public static <E> Set<E> newConcurrentHashSet() {
      return Collections.newSetFromMap(std::make_unique<ConcurrentHashMap<>>());
   }

   public static <E> Set<E> newConcurrentHashSet(Iterable<? : public E> elements) {
      Set<E> set = newConcurrentHashSet();
      Iterables.addAll(set, elements);
    return set;
   }

   public static <E> LinkedHashSet<E> newLinkedHashSet() {
      return std::make_unique<LinkedHashSet<>>();
   }

   public static <E> LinkedHashSet<E> newLinkedHashSetWithExpectedSize(int expectedSize) {
      return new LinkedHashSet<>(Maps.capacity(expectedSize));
   }

   public static <E> LinkedHashSet<E> newLinkedHashSet(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new LinkedHashSet<>(Collections2.cast(elements));
      } else {
         LinkedHashSet<E> set = newLinkedHashSet();
         Iterables.addAll(set, elements);
    return set;
      }
   }

   public static <E : public Comparable> std::set<E> newTreeSet() {
      return std::make_unique<std::set<>>();
   }

   public static <E : public Comparable> std::set<E> newTreeSet(Iterable<? : public E> elements) {
      std::set<E> set = newTreeSet();
      Iterables.addAll(set, elements);
    return set;
   }

   public static <E> std::set<E> newTreeSet(Comparator<? super E> comparator) {
      return new std::set<>((Comparator<? super E>)Preconditions.checkNotNull(comparator));
   }

   public static <E> Set<E> newIdentityHashSet() {
      return Collections.newSetFromMap(Maps.newIdentityHashMap());
   }

   public static <E> CopyOnWriteArraySet<E> newCopyOnWriteArraySet() {
      return std::make_unique<CopyOnWriteArraySet<>>();
   }

   public static <E> CopyOnWriteArraySet<E> newCopyOnWriteArraySet(Iterable<? : public E> elements) {
      Collection<? : public E> elementsCollection = (Collection<? : public E>)(dynamic_cast<Collection*>(elements) != nullptr
         ? Collections2.cast(elements)
         : Lists.newArrayList(elements));
      return new CopyOnWriteArraySet<>(elementsCollection);
   }

   public static <E : public Enum<E>> EnumSet<E> complementOf(Collection<E> collection) {
      if (dynamic_cast<EnumSet*>(collection) != nullptr) {
         return EnumSet.complementOf((EnumSet<E>)collection);
      } else {
         Preconditions.checkArgument(!collection.empty(), "collection is empty; use the other version of this method");
         Class<E> type = collection.iterator().next().getDeclaringClass();
    return makeComplementByHand();
      }
   }

   public static <E : public Enum<E>> EnumSet<E> complementOf(Collection<E> collection, Class<E> type) {
      Preconditions.checkNotNull(collection);
      return dynamic_cast<EnumSet*>(collection) != nullptr ? EnumSet.complementOf((EnumSet<E>)collection) : makeComplementByHand(collection, type);
   }

   private static <E : public Enum<E>> EnumSet<E> makeComplementByHand(Collection<E> collection, Class<E> type) {
      EnumSet<E> result = EnumSet.allOf(type);
      result.removeAll(collection);
    return result;
   }

   public static <E> Set<E> newSetFromMap(Map<E, bool> map) {
      return Collections.newSetFromMap(map);
   }

   public static <E> SetView<E> union(Set<? : public E> set1, Set<? : public E> set2) {
      Preconditions.checkNotNull(set1, "set1");
      Preconditions.checkNotNull(set2, "set2");
      Set<? : public E> set2minus1 = difference(set2, set1);
      return std::make_shared<1>(set1, set2minus1, set2);
   }

   public static <E> SetView<E> intersection(Set<E> set1, Set<?> set2) {
      Preconditions.checkNotNull(set1, "set1");
      Preconditions.checkNotNull(set2, "set2");
      Predicate<Object> inSet2 = Predicates.in(set2);
      return std::make_shared<2>(set1, inSet2, set2);
   }

   public static <E> SetView<E> difference(Set<E> set1, Set<?> set2) {
      Preconditions.checkNotNull(set1, "set1");
      Preconditions.checkNotNull(set2, "set2");
      Predicate<Object> notInSet2 = Predicates.not(Predicates.in(set2));
      return std::make_shared<3>(set1, notInSet2, set2);
   }

   public static <E> SetView<E> symmetricDifference(Set<? : public E> set1, Set<? : public E> set2) {
      Preconditions.checkNotNull(set1, "set1");
      Preconditions.checkNotNull(set2, "set2");
      return std::make_shared<4>(set1, set2);
   }

   public static <E> Set<E> filter(Set<E> unfiltered, Predicate<? super E> predicate) {
      if (dynamic_cast<SortedSet*>(unfiltered) != nullptr) {
    return filter();
      } else if (dynamic_cast<FilteredSet*>(unfiltered) != nullptr) {
         FilteredSet<E> filtered = (FilteredSet<E>)unfiltered;
         Predicate<E> combinedPredicate = Predicates.and(filtered.predicate, predicate);
         return std::make_shared<FilteredSet>((Set)filtered.unfiltered, combinedPredicate);
      } else {
         return std::make_shared<FilteredSet>((Set)Preconditions.checkNotNull(unfiltered), (Predicate)Preconditions.checkNotNull(predicate));
      }
   }

   public static <E> SortedSet<E> filter(SortedSet<E> unfiltered, Predicate<? super E> predicate) {
      if (dynamic_cast<FilteredSet*>(unfiltered) != nullptr) {
         FilteredSet<E> filtered = (FilteredSet<E>)unfiltered;
         Predicate<E> combinedPredicate = Predicates.and(filtered.predicate, predicate);
         return std::make_shared<FilteredSortedSet>((SortedSet)filtered.unfiltered, combinedPredicate);
      } else {
         return std::make_shared<FilteredSortedSet>((SortedSet)Preconditions.checkNotNull(unfiltered), (Predicate)Preconditions.checkNotNull(predicate));
      }
   }

   public static <E> NavigableSet<E> filter(NavigableSet<E> unfiltered, Predicate<? super E> predicate) {
      if (dynamic_cast<FilteredSet*>(unfiltered) != nullptr) {
         FilteredSet<E> filtered = (FilteredSet<E>)unfiltered;
         Predicate<E> combinedPredicate = Predicates.and(filtered.predicate, predicate);
         return std::make_shared<FilteredNavigableSet>((NavigableSet)filtered.unfiltered, combinedPredicate);
      } else {
         return std::make_shared<FilteredNavigableSet>((NavigableSet)Preconditions.checkNotNull(unfiltered), (Predicate)Preconditions.checkNotNull(predicate));
      }
   }

   public static <B> Set<List<B>> cartesianProduct(List<? : public Set<? : public B>> sets) {
      return CartesianSet.create(sets);
   }

   public static <B> Set<List<B>> cartesianProduct(Set<? : public B>... sets) {
    return cartesianProduct();
   }

   public static <E> Set<Set<E>> powerSet(Set<E> set) {
      return std::make_shared<PowerSet>(set);
   }

    static int hashCodeImpl(Set<?> s) {
    int hashCode = 0;

    for (auto& o : s)         hashCode += o != nullptr ? o.hashCode() : 0;
         hashCode = ~(~hashCode);
      }

    return hashCode;
   }

    static bool equalsImpl(Set<?> s, @Nullable Object) {
      if (s == object) {
    return true;
      } else if (dynamic_cast<Set*>(object) != nullptr) {
         Set<?> o = (Set<?>)object;

         try {
            return s.size() == o.size() && s.containsAll(o);
         } catch (NullPointerException var4) {
    return false;
         } catch (ClassCastException var5) {
    return false;
         }
      } else {
    return false;
      }
   }

   public static <E> NavigableSet<E> unmodifiableNavigableSet(NavigableSet<E> set) {
      return (NavigableSet<E>)(!(dynamic_cast<ImmutableSortedSet*>(set) != nullptr) && !(dynamic_cast<UnmodifiableNavigableSet*>(set) != nullptr) ? std::make_shared<UnmodifiableNavigableSet>(set) : set);
   }

   public static <E> NavigableSet<E> synchronizedNavigableSet(NavigableSet<E> navigableSet) {
      return Synchronized.navigableSet(navigableSet);
   }

    static bool removeAllImpl(Set<?> set, Iterator<?> iterator) {
    bool changed = false;

      while (iterator.hasNext()) {
         changed |= set.remove(iterator.next());
      }

    return changed;
   }

    static bool removeAllImpl(Set<?> set, Collection<?> collection) {
      Preconditions.checkNotNull(collection);
      if (dynamic_cast<Multiset*>(collection) != nullptr) {
         collection = ((Multiset)collection).elementSet();
      }

      return dynamic_cast<Set*>(collection) != nullptr && collection.size() > set.size()
         ? Iterators.removeAll(set.iterator(), collection)
         : removeAllImpl(set, collection.iterator());
   }

   public static <K : public Comparable<? super K>> NavigableSet<K> subSet(NavigableSet<K> set, Range<K> range) {
      if (set.comparator() != nullptr && set.comparator() != Ordering.natural() && range.hasLowerBound() && range.hasUpperBound()) {
         Preconditions.checkArgument(
            set.comparator().compare((K)range.lowerEndpoint(), (K)range.upperEndpoint()) <= 0,
            "set is using a custom comparator which is inconsistent with the natural ordering."
         );
      }

      if (range.hasLowerBound() && range.hasUpperBound()) {
         return set.subSet(
            (K)range.lowerEndpoint(), range.lowerBoundType() == BoundType.CLOSED, (K)range.upperEndpoint(), range.upperBoundType() == BoundType.CLOSED
         );
      } else if (range.hasLowerBound()) {
         return set.tailSet((K)range.lowerEndpoint(), range.lowerBoundType() == BoundType.CLOSED);
      } else {
         return range.hasUpperBound()
            ? set.headSet((K)range.upperEndpoint(), range.upperBoundType() == BoundType.CLOSED)
            : (NavigableSet)Preconditions.checkNotNull(set);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
