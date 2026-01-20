#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/MapDifference/ValueDifference.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
    const V left;
    const V right;

   static <V> ValueDifference<V> create(@Nullable V left, @Nullable V right) {
      return new Maps$ValueDifferenceImpl<>(left, right);
   }

   private Maps$ValueDifferenceImpl(@Nullable V left, @Nullable V right) {
      this.left = left;
      this.right = right;
   }

    V leftValue() {
      return this.left;
   }

    V rightValue() {
      return this.right;
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<ValueDifference*>(object) != nullptr)) {
    return false;
      } else {
         ValueDifference<?> that = (ValueDifference<?>)object;
         return Objects.equal(this.left, that.leftValue()) && Objects.equal(this.right, that.rightValue());
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.left, this.right});
   }

    std::string toString() {
      return "(" + this.left + ", " + this.right + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
