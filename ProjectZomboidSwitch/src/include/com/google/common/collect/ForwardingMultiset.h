#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMultiset {
public:
    protected ForwardingMultiset() {
   }

   protected abstract Multiset<E> delegate();

    int count(void* element) {
      return this.delegate().count(element);
   }

    int add(E element, int occurrences) {
      return this.delegate().push_back(element, occurrences);
   }

    int remove(void* element, int occurrences) {
      return this.delegate().remove(element, occurrences);
   }

   public Set<E> elementSet() {
      return this.delegate().elementSet();
   }

   public Set<Entry<E>> entrySet() {
      return this.delegate().entrySet();
   }

    bool equals(@Nullable Object) {
    return object = = this || this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }

    int setCount(E element, int count) {
      return this.delegate().setCount(element, count);
   }

    bool setCount(E element, int oldCount, int newCount) {
      return this.delegate().setCount(element, oldCount, newCount);
   }

    bool standardContains(@Nullable Object) {
      return this.count(object) > 0;
   }

    void standardClear() {
      Iterators.clear(this.entrySet().iterator());
   }

    int standardCount(@Nullable Object) {
      for (Entry<?> entry : this.entrySet()) {
         if (Objects.equal(entry.getElement(), object)) {
            return entry.getCount();
         }
      }

    return 0;
   }

    bool standardAdd(E element) {
      this.push_back(element, 1);
    return true;
   }

    bool standardAddAll(Collection<? extends) {
      return Multisets.addAllImpl(this, elementsToAdd);
   }

    bool standardRemove(void* element) {
      return this.remove(element, 1) > 0;
   }

    bool standardRemoveAll(Collection<?> elementsToRemove) {
      return Multisets.removeAllImpl(this, elementsToRemove);
   }

    bool standardRetainAll(Collection<?> elementsToRetain) {
      return Multisets.retainAllImpl(this, elementsToRetain);
   }

    int standardSetCount(E element, int count) {
      return Multisets.setCountImpl(this, element, count);
   }

    bool standardSetCount(E element, int oldCount, int newCount) {
      return Multisets.setCountImpl(this, element, oldCount, newCount);
   }

   protected Iterator<E> standardIterator() {
      return Multisets.iteratorImpl(this);
   }

    int standardSize() {
      return Multisets.sizeImpl(this);
   }

    bool standardEquals(@Nullable Object) {
      return Multisets.equalsImpl(this, object);
   }

    int standardHashCode() {
      return this.entrySet().hashCode();
   }

    std::string standardToString() {
      return this.entrySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
