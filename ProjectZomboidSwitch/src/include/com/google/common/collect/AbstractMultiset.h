#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/AbstractMultiset/ElementSet.h"
#include "com/google/common/collect/AbstractMultiset/EntrySet.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMultiset {
public:
   private transient Set<E> elementSet;
   private transient Set<Entry<E>> entrySet;

    int size() {
      return Multisets.sizeImpl(this);
   }

    bool isEmpty() {
      return this.entrySet().empty();
   }

    bool contains(@Nullable Object) {
      return this.count(element) > 0;
   }

   public Iterator<E> iterator() {
      return Multisets.iteratorImpl(this);
   }

    int count(@Nullable Object) {
      for (Entry<E> entry : this.entrySet()) {
         if (Objects.equal(entry.getElement(), element)) {
            return entry.getCount();
         }
      }

    return 0;
   }

    bool add(@Nullable E) {
      this.push_back(element, 1);
    return true;
   }

    int add(@Nullable E, int occurrences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(@Nullable Object) {
      return this.remove(element, 1) > 0;
   }

    int remove(@Nullable Object, int occurrences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int setCount(@Nullable E, int count) {
      return Multisets.setCountImpl(this, element, count);
   }

    bool setCount(@Nullable E, int oldCount, int newCount) {
      return Multisets.setCountImpl(this, element, oldCount, newCount);
   }

    bool addAll(Collection<? extends) {
      return Multisets.addAllImpl(this, elementsToAdd);
   }

    bool removeAll(Collection<?> elementsToRemove) {
      return Multisets.removeAllImpl(this, elementsToRemove);
   }

    bool retainAll(Collection<?> elementsToRetain) {
      return Multisets.retainAllImpl(this, elementsToRetain);
   }

    void clear() {
      Iterators.clear(this.entryIterator());
   }

   public Set<E> elementSet() {
      Set<E> result = this.elementSet;
      if (result == nullptr) {
         this.elementSet = result = this.createElementSet();
      }

    return result;
   }

   Set<E> createElementSet() {
      return std::make_shared<ElementSet>(this);
   }

   abstract Iterator<Entry<E>> entryIterator();

   abstract int distinctElements();

   public Set<Entry<E>> entrySet() {
      Set<Entry<E>> result = this.entrySet;
      if (result == nullptr) {
         this.entrySet = result = this.createEntrySet();
      }

    return result;
   }

   Set<Entry<E>> createEntrySet() {
      return std::make_shared<EntrySet>(this);
   }

    bool equals(@Nullable Object) {
      return Multisets.equalsImpl(this, object);
   }

    int hashCode() {
      return this.entrySet().hashCode();
   }

    std::string toString() {
      return this.entrySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
