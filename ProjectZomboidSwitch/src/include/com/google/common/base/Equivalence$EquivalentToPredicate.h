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


class Equivalence {
public:
   private const Equivalence<T> equivalence;
    const T target;
    static const long serialVersionUID = 0L;

   Equivalence$EquivalentToPredicate(Equivalence<T> equivalence, @Nullable T target) {
      this.equivalence = (Equivalence<T>)Preconditions.checkNotNull(equivalence);
      this.target = target;
   }

    bool apply(@Nullable T) {
      return this.equivalence.equivalent(input, this.target);
   }

    bool equals(@Nullable Object) {
      if (this == obj) {
    return true;
      } else if (!(dynamic_cast<Equivalence*>(obj) != nullptr$EquivalentToPredicate)) {
    return false;
      } else {
         Equivalence$EquivalentToPredicate<?> that = (Equivalence$EquivalentToPredicate<?>)obj;
         return this.equivalence == that.equivalence) && Objects.equal(this.target, that.target);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.equivalence, this.target});
   }

    std::string toString() {
      return this.equivalence + ".equivalentTo(" + this.target + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
