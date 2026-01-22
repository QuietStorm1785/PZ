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


class Predicates {
public:
   const Predicate<T> predicate;
    static const long serialVersionUID = 0L;

   Predicates$NotPredicate(Predicate<T> predicate) {
      this.predicate = (Predicate<T>)Preconditions.checkNotNull(predicate);
   }

    bool apply(@Nullable T) {
      return !this.predicate.apply(t);
   }

    int hashCode() {
      return ~this.predicate.hashCode();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Predicates*>(obj) != nullptr$NotPredicate) {
         Predicates$NotPredicate<?> that = (Predicates$NotPredicate<?>)obj;
         return this.predicate == that.predicate);
      } else {
    return false;
      }
   }

    std::string toString() {
      return "Predicates.not(" + this.predicate + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
