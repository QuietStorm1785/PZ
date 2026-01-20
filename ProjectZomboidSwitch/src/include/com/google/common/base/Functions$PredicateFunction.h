#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Functions {
public:
   private const Predicate<T> predicate;
    static const long serialVersionUID = 0L;

   private Functions$PredicateFunction(Predicate<T> predicate) {
      this.predicate = (Predicate<T>)Preconditions.checkNotNull(predicate);
   }

    bool apply(@Nullable T) {
      return this.predicate.apply(t);
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Functions*>(obj) != nullptr$PredicateFunction) {
         Functions$PredicateFunction<?> that = (Functions$PredicateFunction<?>)obj;
         return this.predicate == that.predicate);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.predicate.hashCode();
   }

    std::string toString() {
      return "Functions.forPredicate(" + this.predicate + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
