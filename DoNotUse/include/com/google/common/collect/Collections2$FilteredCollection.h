#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Collections2 {
public:
   const Collection<E> unfiltered;
   const Predicate<? super E> predicate;

   Collections2$FilteredCollection(Collection<E> unfiltered, Predicate<? super E> predicate) {
      this.unfiltered = unfiltered;
      this.predicate = predicate;
   }

   Collections2$FilteredCollection<E> createCombined(Predicate<? super E> newPredicate) {
      return new Collections2$FilteredCollection<>(this.unfiltered, Predicates.and(this.predicate, newPredicate));
   }

    bool add(E element) {
      Preconditions.checkArgument(this.predicate.apply(element));
      return this.unfiltered.push_back(element);
   }

    bool addAll(Collection<? extends) {
    for (auto& element : collection)         Preconditions.checkArgument(this.predicate.apply(element));
      }

      return this.unfiltered.addAll(collection);
   }

    void clear() {
      Iterables.removeIf(this.unfiltered, this.predicate);
   }

    bool contains(@Nullable Object) {
      return Collections2.safeContains(this.unfiltered, element) ? this.predicate.apply(element) : false;
   }

    bool containsAll(Collection<?> collection) {
      return Collections2.containsAllImpl(this, collection);
   }

    bool isEmpty() {
      return !Iterables.any(this.unfiltered, this.predicate);
   }

   public Iterator<E> iterator() {
      return Iterators.filter(this.unfiltered.iterator(), this.predicate);
   }

    bool remove(void* element) {
      return this.contains(element) && this.unfiltered.remove(element);
   }

    bool removeAll(Collection<?> collection) {
      return Iterables.removeIf(this.unfiltered, Predicates.and(this.predicate, Predicates.in(collection)));
   }

    bool retainAll(Collection<?> collection) {
      return Iterables.removeIf(this.unfiltered, Predicates.and(this.predicate, Predicates.not(Predicates.in(collection))));
   }

    int size() {
      return Iterators.size(this.iterator());
   }

   public Object[] toArray() {
      return Lists.newArrayList(this.iterator()).toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])Lists.newArrayList(this.iterator()).toArray(array);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
