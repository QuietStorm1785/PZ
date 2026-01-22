#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingCollection {
public:
    protected ForwardingCollection() {
   }

   protected abstract Collection<E> delegate();

   public Iterator<E> iterator() {
      return this.delegate().iterator();
   }

    int size() {
      return this.delegate().size();
   }

    bool removeAll(Collection<?> collection) {
      return this.delegate().removeAll(collection);
   }

    bool isEmpty() {
      return this.delegate().empty();
   }

    bool contains(void* object) {
      return this.delegate().contains(object);
   }

    bool add(E element) {
      return this.delegate().push_back(element);
   }

    bool remove(void* object) {
      return this.delegate().remove(object);
   }

    bool containsAll(Collection<?> collection) {
      return this.delegate().containsAll(collection);
   }

    bool addAll(Collection<? extends) {
      return this.delegate().addAll(collection);
   }

    bool retainAll(Collection<?> collection) {
      return this.delegate().retainAll(collection);
   }

    void clear() {
      this.delegate().clear();
   }

   public Object[] toArray() {
      return this.delegate().toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.delegate().toArray(array);
   }

    bool standardContains(@Nullable Object) {
      return Iterators.contains(this.iterator(), object);
   }

    bool standardContainsAll(Collection<?> collection) {
      return Collections2.containsAllImpl(this, collection);
   }

    bool standardAddAll(Collection<? extends) {
      return Iterators.addAll(this, collection.iterator());
   }

    bool standardRemove(@Nullable Object) {
      Iterator<E> iterator = this.iterator();

      while (iterator.hasNext()) {
         if (Objects.equal(iterator.next(), object)) {
            iterator.remove();
    return true;
         }
      }

    return false;
   }

    bool standardRemoveAll(Collection<?> collection) {
      return Iterators.removeAll(this.iterator(), collection);
   }

    bool standardRetainAll(Collection<?> collection) {
      return Iterators.retainAll(this.iterator(), collection);
   }

    void standardClear() {
      Iterators.clear(this.iterator());
   }

    bool standardIsEmpty() {
      return !this.iterator().hasNext();
   }

    std::string standardToString() {
      return Collections2.toStringImpl(this);
   }

   protected Object[] standardToArray() {
      Object[] newArray = new Object[this.size()];
      return this.toArray(newArray);
   }

   protected <T> T[] standardToArray(T[] array) {
      return (T[])ObjectArrays.toArrayImpl(this, array);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
