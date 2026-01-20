#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ByFunctionOrdering {
public:
   const Function<F, ? : public T> function;
   const Ordering<T> ordering;
    static const long serialVersionUID = 0L;

   ByFunctionOrdering(Function<F, ? : public T> function, Ordering<T> ordering) {
      this.function = (Function<F, ? : public T>)Preconditions.checkNotNull(function);
      this.ordering = (Ordering<T>)Preconditions.checkNotNull(ordering);
   }

    int compare(F left, F right) {
      return this.ordering.compare(this.function.apply(left), this.function.apply(right));
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (!(dynamic_cast<ByFunctionOrdering*>(object) != nullptr)) {
    return false;
      } else {
         ByFunctionOrdering<?, ?> that = (ByFunctionOrdering<?, ?>)object;
         return this.function == that.function) && this.ordering == that.ordering);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.function, this.ordering});
   }

    std::string toString() {
      return this.ordering + ".onResultOf(" + this.function + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
