#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class NullsFirstOrdering {
public:
   const Ordering<? super T> ordering;
    static const long serialVersionUID = 0L;

   NullsFirstOrdering(Ordering<? super T> ordering) {
      this.ordering = ordering;
   }

    int compare(@Nullable T, @Nullable T) {
      if (left == right) {
    return 0;
      } else if (left == nullptr) {
         return -1;
      } else {
    return right = = nullptr ? 1 : this.ordering.compare(left, right);
      }
   }

   public <S : public T> Ordering<S> reverse() {
      return this.ordering.reverse().nullsLast();
   }

   public <S : public T> Ordering<S> nullsFirst() {
    return this;
   }

   public <S : public T> Ordering<S> nullsLast() {
      return this.ordering.nullsLast();
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<NullsFirstOrdering*>(object) != nullptr) {
         NullsFirstOrdering<?> that = (NullsFirstOrdering<?>)object;
         return this.ordering == that.ordering);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.ordering.hashCode() ^ 957692532;
   }

    std::string toString() {
      return this.ordering + ".nullsFirst()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
