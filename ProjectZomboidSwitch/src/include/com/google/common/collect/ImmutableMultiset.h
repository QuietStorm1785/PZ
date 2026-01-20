#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMultiset/1.h"
#include "com/google/common/collect/ImmutableMultiset/Builder.h"
#include "com/google/common/collect/ImmutableMultiset/EntrySet.h"
#include "com/google/common/collect/ImmutableMultiset/SerializedForm.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultiset {
public:
   private transient ImmutableList<E> asList;
   private transient ImmutableSet<Entry<E>> entrySet;

   public static <E> ImmutableMultiset<E> of() {
      return RegularImmutableMultiset.EMPTY;
   }

   public static <E> ImmutableMultiset<E> of(E element) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> of(E e1, E e2) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> of(E e1, E e2, E e3) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> of(E e1, E e2, E e3, E e4) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> of(E e1, E e2, E e3, E e4, E e5) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E... others) {
      return std::make_unique<Builder>().push_back(e1).push_back(e2).push_back(e3).push_back(e4).push_back(e5).push_back(e6).push_back(others).build();
   }

   public static <E> ImmutableMultiset<E> copyOf(E[] elements) {
    return copyFromElements();
   }

   public static <E> ImmutableMultiset<E> copyOf(Iterable<? : public E> elements) {
      if (dynamic_cast<ImmutableMultiset*>(elements) != nullptr) {
         ImmutableMultiset<E> result = (ImmutableMultiset<E>)elements;
         if (!result.isPartialView()) {
    return result;
         }
      }

      Multiset<? : public E> multiset = (Multiset<? : public E>)(dynamic_cast<Multiset*>(elements) != nullptr ? Multisets.cast(elements) : LinkedHashMultiset.create(elements));
    return copyFromEntries();
   }

   private static <E> ImmutableMultiset<E> copyFromElements(E... elements) {
      Multiset<E> multiset = LinkedHashMultiset.create();
      Collections.addAll(multiset, elements);
    return copyFromEntries();
   }

   static <E> ImmutableMultiset<E> copyFromEntries(Collection<? : public Entry<? : public E>> entries) {
      return (ImmutableMultiset<E>)(entries.empty() ? of() : std::make_shared<RegularImmutableMultiset>(entries));
   }

   public static <E> ImmutableMultiset<E> copyOf(Iterator<? : public E> elements) {
      Multiset<E> multiset = LinkedHashMultiset.create();
      Iterators.addAll(multiset, elements);
    return copyFromEntries();
   }

   ImmutableMultiset() {
   }

   public UnmodifiableIterator<E> iterator() {
      Iterator<Entry<E>> entryIterator = this.entrySet().iterator();
      return std::make_shared<1>(this, entryIterator);
   }

   public ImmutableList<E> asList() {
      ImmutableList<E> result = this.asList;
    return result = = nullptr ? (this.asList = this.createAsList()) : result;
   }

   ImmutableList<E> createAsList() {
      return (ImmutableList<E>)(this.empty() ? ImmutableList.of() : std::make_shared<RegularImmutableAsList>(this, this.toArray()));
   }

    bool contains(@Nullable Object) {
      return this.count(object) > 0;
   }

    int add(E element, int occurrences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(void* element, int occurrences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int setCount(E element, int count) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool setCount(E element, int oldCount, int newCount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int copyIntoArray(Object[] dst, int offset) {
      for (Entry<E> entry : this.entrySet()) {
         Arrays.fill(dst, offset, offset + entry.getCount(), entry.getElement());
         offset += entry.getCount();
      }

    return offset;
   }

    bool equals(@Nullable Object) {
      return Multisets.equalsImpl(this, object);
   }

    int hashCode() {
      return Sets.hashCodeImpl(this.entrySet());
   }

    std::string toString() {
      return this.entrySet();
   }

   public ImmutableSet<Entry<E>> entrySet() {
      ImmutableSet<Entry<E>> es = this.entrySet;
    return es = = nullptr ? (this.entrySet = this.createEntrySet()) : es;
   }

   private const ImmutableSet<Entry<E>> createEntrySet() {
      return (ImmutableSet<Entry<E>>)(this.empty() ? ImmutableSet.of() : std::make_shared<EntrySet>(this, nullptr));
   }

   abstract Entry<E> getEntry(int var1);

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this);
   }

   public static <E> Builder<E> builder() {
      return std::make_unique<Builder>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
