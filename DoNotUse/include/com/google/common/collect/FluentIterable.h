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
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/FluentIterable/1.h"
#include "com/google/common/collect/FluentIterable/2.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FluentIterable {
public:
   private const Optional<Iterable<E>> iterableDelegate;

    protected FluentIterable() {
      this.iterableDelegate = Optional.absent();
   }

   FluentIterable(Iterable<E> iterable) {
      Preconditions.checkNotNull(iterable);
      this.iterableDelegate = Optional.fromNullable(this != iterable ? iterable : nullptr);
   }

   private Iterable<E> getDelegate() {
      return (Iterable<E>)this.iterableDelegate.or(this);
   }

   public static <E> FluentIterable<E> from(Iterable<E> iterable) {
      return (FluentIterable<E>)(dynamic_cast<FluentIterable*>(iterable) != nullptr ? (FluentIterable)iterable : std::make_shared<1>(iterable, iterable));
   }

   public static <E> FluentIterable<E> from(E[] elements) {
    return from();
   }

   public static <E> FluentIterable<E> from(FluentIterable<E> iterable) {
      return (FluentIterable<E>)Preconditions.checkNotNull(iterable);
   }

   public static <T> FluentIterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b) {
    return concat();
   }

   public static <T> FluentIterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b, Iterable<? : public T> c) {
    return concat();
   }

   public static <T> FluentIterable<T> concat(Iterable<? : public T> a, Iterable<? : public T> b, Iterable<? : public T> c, Iterable<? : public T> d) {
    return concat();
   }

   public static <T> FluentIterable<T> concat(Iterable<? : public T>... inputs) {
    return concat();
   }

   public static <T> FluentIterable<T> concat(Iterable<? : public Iterable<? : public T>> inputs) {
      Preconditions.checkNotNull(inputs);
      return std::make_shared<2>(inputs);
   }

   public static <E> FluentIterable<E> of() {
    return from();
   }

   public static <E> FluentIterable<E> of(E[] elements) {
    return from();
   }

   public static <E> FluentIterable<E> of(@Nullable E element, E... elements) {
    return from();
   }

    std::string toString() {
      return Iterables.toString(this.getDelegate());
   }

    int size() {
      return Iterables.size(this.getDelegate());
   }

    bool contains(@Nullable Object) {
      return Iterables.contains(this.getDelegate(), target);
   }

   public const FluentIterable<E> cycle() {
    return from();
   }

   public const FluentIterable<E> append(Iterable<? : public E> other) {
    return from();
   }

   public const FluentIterable<E> append(E... elements) {
    return from();
   }

   public const FluentIterable<E> filter(Predicate<? super E> predicate) {
    return from();
   }

   public const <T> FluentIterable<T> filter(Class<T> type) {
    return from();
   }

    bool anyMatch(Predicate<? super) {
      return Iterables.any(this.getDelegate(), predicate);
   }

    bool allMatch(Predicate<? super) {
      return Iterables.all(this.getDelegate(), predicate);
   }

   public const Optional<E> firstMatch(Predicate<? super E> predicate) {
      return Iterables.tryFind(this.getDelegate(), predicate);
   }

   public const <T> FluentIterable<T> transform(Function<? super E, T> function) {
    return from();
   }

   public <T> FluentIterable<T> transformAndConcat(Function<? super E, ? : public Iterable<? : public T>> function) {
    return from();
   }

   public const Optional<E> first() {
      Iterator<E> iterator = this.getDelegate().iterator();
      return iterator.hasNext() ? Optional.of(iterator.next()) : Optional.absent();
   }

   public const Optional<E> last() {
      Iterable<E> iterable = this.getDelegate();
      if (dynamic_cast<List*>(iterable) != nullptr) {
         List<E> list = (List<E>)iterable;
         return list.empty() ? Optional.absent() : Optional.of(list.get(list.size() - 1));
      } else {
         Iterator<E> iterator = iterable.iterator();
         if (!iterator.hasNext()) {
            return Optional.absent();
         } else if (dynamic_cast<SortedSet*>(iterable) != nullptr) {
            SortedSet<E> sortedSet = (SortedSet<E>)iterable;
            return Optional.of(sortedSet.last());
         } else {
    E current;
            do {
               current = iterator.next();
            } while (iterator.hasNext());

            return Optional.of(current);
         }
      }
   }

   public const FluentIterable<E> skip(int numberToSkip) {
    return from();
   }

   public const FluentIterable<E> limit(int maxSize) {
    return from();
   }

    bool isEmpty() {
      return !this.getDelegate().iterator().hasNext();
   }

   public const ImmutableList<E> toList() {
      return ImmutableList.copyOf(this.getDelegate());
   }

   public const ImmutableList<E> toSortedList(Comparator<? super E> comparator) {
      return Ordering.from(comparator).immutableSortedCopy(this.getDelegate());
   }

   public const ImmutableSet<E> toSet() {
      return ImmutableSet.copyOf(this.getDelegate());
   }

   public const ImmutableSortedSet<E> toSortedSet(Comparator<? super E> comparator) {
      return ImmutableSortedSet.copyOf(comparator, this.getDelegate());
   }

   public const ImmutableMultiset<E> toMultiset() {
      return ImmutableMultiset.copyOf(this.getDelegate());
   }

   public const <V> ImmutableMap<E, V> toMap(Function<? super E, V> valueFunction) {
      return Maps.toMap(this.getDelegate(), valueFunction);
   }

   public const <K> ImmutableListMultimap<K, E> index(Function<? super E, K> keyFunction) {
      return Multimaps.index(this.getDelegate(), keyFunction);
   }

   public const <K> ImmutableMap<K, E> uniqueIndex(Function<? super E, K> keyFunction) {
      return Maps.uniqueIndex(this.getDelegate(), keyFunction);
   }

   public const E[] toArray(Class<E> type) {
      return (E[])Iterables.toArray(this.getDelegate(), type);
   }

   public const <C : public Collection<? super E>> C copyInto(C collection) {
      Preconditions.checkNotNull(collection);
      Iterable<E> iterable = this.getDelegate();
      if (dynamic_cast<Collection*>(iterable) != nullptr) {
         collection.addAll(Collections2.cast(iterable));
      } else {
    for (auto& item : iterable)            collection.push_back(item);
         }
      }

    return collection;
   }

    std::string join(Joiner joiner) {
      return joiner.join(this);
   }

    E get(int position) {
      return (E)Iterables.get(this.getDelegate(), position);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
