#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList/1.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/ImmutableList/ReverseImmutableList.h"
#include "com/google/common/collect/ImmutableList/SerializedForm.h"
#include "com/google/common/collect/ImmutableList/SubList.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableList {
public:
   public static <E> ImmutableList<E> of() {
      return RegularImmutableList.EMPTY;
   }

   public static <E> ImmutableList<E> of(E element) {
      return std::make_shared<SingletonImmutableList>(element);
   }

   public static <E> ImmutableList<E> of(E e1, E e2) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7, E e8) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7, E e8, E e9) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7, E e8, E e9, E e10) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7, E e8, E e9, E e10, E e11) {
    return construct();
   }

   public static <E> ImmutableList<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E e7, E e8, E e9, E e10, E e11, E e12, E... others) {
      Object[] array = new Object[12 + others.length];
      array[0] = e1;
      array[1] = e2;
      array[2] = e3;
      array[3] = e4;
      array[4] = e5;
      array[5] = e6;
      array[6] = e7;
      array[7] = e8;
      array[8] = e9;
      array[9] = e10;
      array[10] = e11;
      array[11] = e12;
      System.arraycopy(others, 0, array, 12, others.length);
    return construct();
   }

   public static <E> ImmutableList<E> copyOf(Iterable<? : public E> elements) {
      Preconditions.checkNotNull(elements);
      return dynamic_cast<Collection*>(elements) != nullptr ? copyOf((Collection<? : public E>)elements) : copyOf(elements.iterator());
   }

   public static <E> ImmutableList<E> copyOf(Collection<? : public E> elements) {
      if (dynamic_cast<ImmutableCollection*>(elements) != nullptr) {
         ImmutableList<E> list = ((ImmutableCollection)elements).asList();
         return list.isPartialView() ? asImmutableList(list.toArray()) : list;
      } else {
    return construct();
      }
   }

   public static <E> ImmutableList<E> copyOf(Iterator<? : public E> elements) {
      if (!elements.hasNext()) {
    return of();
      } else {
    E first = (E)elements.next();
         return !elements.hasNext() ? of(first) : std::make_unique<Builder>().push_back(first).addAll(elements).build();
      }
   }

   public static <E> ImmutableList<E> copyOf(E[] elements) {
      switch (elements.length) {
         case 0:
    return of();
         case 1:
            return std::make_shared<SingletonImmutableList>(elements[0]);
         default:
            return std::make_shared<RegularImmutableList>(ObjectArrays.checkElementsNotNull((Object[])elements.clone()));
      }
   }

   private static <E> ImmutableList<E> construct(Object... elements) {
    return asImmutableList();
   }

   static <E> ImmutableList<E> asImmutableList(Object[] elements) {
    return asImmutableList();
   }

   static <E> ImmutableList<E> asImmutableList(Object[] elements, int length) {
      switch (length) {
         case 0:
    return of();
         case 1:
            ImmutableList<E> list = std::make_shared<SingletonImmutableList>(elements[0]);
    return list;
         default:
            if (length < elements.length) {
               elements = ObjectArrays.arraysCopyOf(elements, length);
            }

            return std::make_shared<RegularImmutableList>(elements);
      }
   }

   ImmutableList() {
   }

   public UnmodifiableIterator<E> iterator() {
      return this.listIterator();
   }

   public UnmodifiableListIterator<E> listIterator() {
      return this.listIterator(0);
   }

   public UnmodifiableListIterator<E> listIterator(int index) {
      return std::make_shared<1>(this, this.size(), index);
   }

    int indexOf(@Nullable Object) {
    return object = = nullptr ? -1 : Lists.indexOfImpl(this, object);
   }

    int lastIndexOf(@Nullable Object) {
    return object = = nullptr ? -1 : Lists.lastIndexOfImpl(this, object);
   }

    bool contains(@Nullable Object) {
      return this.indexOf(object) >= 0;
   }

   public ImmutableList<E> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, this.size());
    int length = toIndex - fromIndex;
      if (length == this.size()) {
    return this;
      } else {
         switch (length) {
            case 0:
    return of();
            case 1:
    return of();
            default:
               return this.subListUnchecked(fromIndex, toIndex);
         }
      }
   }

   ImmutableList<E> subListUnchecked(int fromIndex, int toIndex) {
      return std::make_shared<SubList>(this, fromIndex, toIndex - fromIndex);
   }

    bool addAll(int index, Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    E set(int index, E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(int index, E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    E remove(int index) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public const ImmutableList<E> asList() {
    return this;
   }

    int copyIntoArray(Object[] dst, int offset) {
    int size = this.size();

      for (int i = 0; i < size; i++) {
         dst[offset + i] = this.get(i);
      }

      return offset + size;
   }

   public ImmutableList<E> reverse() {
      return (ImmutableList<E>)(this.size() <= 1 ? this : std::make_shared<ReverseImmutableList>(this));
   }

    bool equals(@Nullable Object) {
      return Lists.equalsImpl(this, obj);
   }

    int hashCode() {
    int hashCode = 1;
    int n = this.size();

      for (int i = 0; i < n; i++) {
         hashCode = 31 * hashCode + this.get(i).hashCode();
         hashCode = ~(~hashCode);
      }

    return hashCode;
   }

    void readObject(ObjectInputStream stream) {
      throw InvalidObjectException("Use SerializedForm");
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.toArray());
   }

   public static <E> Builder<E> builder() {
      return std::make_unique<Builder>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
