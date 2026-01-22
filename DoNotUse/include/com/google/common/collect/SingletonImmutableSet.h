#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class SingletonImmutableSet {
public:
   const transient E element;
   private transient int cachedHashCode;

   SingletonImmutableSet(E element) {
      this.element = (E)Preconditions.checkNotNull(element);
   }

   SingletonImmutableSet(E element, int hashCode) {
      this.element = element;
      this.cachedHashCode = hashCode;
   }

    int size() {
    return 1;
   }

    bool contains(void* target) {
      return this.element == target);
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.singletonIterator(this.element);
   }

   ImmutableList<E> createAsList() {
      return ImmutableList.of(this.element);
   }

    bool isPartialView() {
    return false;
   }

    int copyIntoArray(Object[] dst, int offset) {
      dst[offset] = this.element;
      return offset + 1;
   }

    int hashCode() {
    int code = this.cachedHashCode;
      if (code == 0) {
         this.cachedHashCode = code = this.element.hashCode();
      }

    return code;
   }

    bool isHashCodeFast() {
      return this.cachedHashCode != 0;
   }

    std::string toString() {
      return '[' + this.element + ']';
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
