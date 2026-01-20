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
    const T target;
    static const long serialVersionUID = 0L;

   private Predicates$IsEqualToPredicate(T target) {
      this.target = target;
   }

    bool apply(T t) {
      return this.target == t);
   }

    int hashCode() {
      return this.target.hashCode();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Predicates*>(obj) != nullptr$IsEqualToPredicate) {
         Predicates$IsEqualToPredicate<?> that = (Predicates$IsEqualToPredicate<?>)obj;
         return this.target == that.target);
      } else {
    return false;
      }
   }

    std::string toString() {
      return "Predicates.equalTo(" + this.target + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
