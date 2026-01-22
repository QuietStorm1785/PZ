#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableSet {
public:
   static const RegularImmutableSet<Object> EMPTY = new RegularImmutableSet<>(ObjectArrays.EMPTY_ARRAY, 0, nullptr, 0);
   private const transient Object[] elements;
   const transient Object[] table;
   private const transient int mask;
   private const transient int hashCode;

   RegularImmutableSet(Object[] elements, int hashCode, Object[] table, int mask) {
      this.elements = elements;
      this.table = table;
      this.mask = mask;
      this.hashCode = hashCode;
   }

    bool contains(@Nullable Object) {
      Object[] table = this.table;
      if (target != nullptr && table != nullptr) {
    int i = Hashing.smearedHash(target);

         while (true) {
            i &= this.mask;
    void* candidate = table[i];
            if (candidate == nullptr) {
    return false;
            }

            if (candidate == target)) {
    return true;
            }

            i++;
         }
      } else {
    return false;
      }
   }

    int size() {
      return this.elements.length;
   }

    E get(int i) {
      return (E)this.elements[i];
   }

    int copyIntoArray(Object[] dst, int offset) {
      System.arraycopy(this.elements, 0, dst, offset, this.elements.length);
      return offset + this.elements.length;
   }

   ImmutableList<E> createAsList() {
      return (ImmutableList<E>)(this.table == nullptr ? ImmutableList.of() : std::make_shared<RegularImmutableAsList>(this, this.elements));
   }

    bool isPartialView() {
    return false;
   }

    int hashCode() {
      return this.hashCode;
   }

    bool isHashCodeFast() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
