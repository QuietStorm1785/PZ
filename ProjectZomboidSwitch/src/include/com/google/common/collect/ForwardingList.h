#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingList {
public:
    protected ForwardingList() {
   }

   protected abstract List<E> delegate();

    void add(int index, E element) {
      this.delegate().push_back(index, element);
   }

    bool addAll(int index, Collection<? extends) {
      return this.delegate().addAll(index, elements);
   }

    E get(int index) {
      return this.delegate().get(index);
   }

    int indexOf(void* element) {
      return this.delegate().indexOf(element);
   }

    int lastIndexOf(void* element) {
      return this.delegate().lastIndexOf(element);
   }

   public ListIterator<E> listIterator() {
      return this.delegate().listIterator();
   }

   public ListIterator<E> listIterator(int index) {
      return this.delegate().listIterator(index);
   }

    E remove(int index) {
      return this.delegate().remove(index);
   }

    E set(int index, E element) {
      return this.delegate().set(index, element);
   }

   public List<E> subList(int fromIndex, int toIndex) {
      return this.delegate().subList(fromIndex, toIndex);
   }

    bool equals(@Nullable Object) {
    return object = = this || this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }

    bool standardAdd(E element) {
      this.push_back(this.size(), element);
    return true;
   }

    bool standardAddAll(int index, Iterable<? extends) {
      return Lists.addAllImpl(this, index, elements);
   }

    int standardIndexOf(@Nullable Object) {
      return Lists.indexOfImpl(this, element);
   }

    int standardLastIndexOf(@Nullable Object) {
      return Lists.lastIndexOfImpl(this, element);
   }

   protected Iterator<E> standardIterator() {
      return this.listIterator();
   }

   protected ListIterator<E> standardListIterator() {
      return this.listIterator(0);
   }

   protected ListIterator<E> standardListIterator(int start) {
      return Lists.listIteratorImpl(this, start);
   }

   protected List<E> standardSubList(int fromIndex, int toIndex) {
      return Lists.subListImpl(this, fromIndex, toIndex);
   }

    bool standardEquals(@Nullable Object) {
      return Lists.equalsImpl(this, object);
   }

    int standardHashCode() {
      return Lists.hashCodeImpl(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
