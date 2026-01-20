#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/j2objc/annotations/Weak.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableAsList {
public:
   private const ImmutableCollection<E> delegate;
   private const ImmutableList<? : public E> delegateList;

   RegularImmutableAsList(ImmutableCollection<E> delegate, ImmutableList<? : public E> delegateList) {
      this.delegate = delegate;
      this.delegateList = delegateList;
   }

   RegularImmutableAsList(ImmutableCollection<E> delegate, Object[] array) {
      this(delegate, ImmutableList.asImmutableList(array));
   }

   ImmutableCollection<E> delegateCollection() {
      return this.delegate;
   }

   ImmutableList<? : public E> delegateList() {
      return this.delegateList;
   }

   public UnmodifiableListIterator<E> listIterator(int index) {
      return this.delegateList.listIterator(index);
   }

    int copyIntoArray(Object[] dst, int offset) {
      return this.delegateList.copyIntoArray(dst, offset);
   }

    E get(int index) {
      return (E)this.delegateList.get(index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
