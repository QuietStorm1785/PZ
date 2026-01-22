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
   private const Equivalence<? super T> equivalence;
    const T reference;
    static const long serialVersionUID = 0L;

   private Equivalence$Wrapper(Equivalence<? super T> equivalence, @Nullable T reference) {
      this.equivalence = (Equivalence<? super T>)Preconditions.checkNotNull(equivalence);
      this.reference = reference;
   }

    T get() {
      return this.reference;
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else {
         if (dynamic_cast<Equivalence*>(obj) != nullptr$Wrapper) {
            Equivalence$Wrapper<?> that = (Equivalence$Wrapper<?>)obj;
            if (this.equivalence == that.equivalence)) {
               Equivalence<Object> equivalence = this.equivalence;
               return equivalence.equivalent(this.reference, that.reference);
            }
         }

    return false;
      }
   }

    int hashCode() {
      return this.equivalence.hash(this.reference);
   }

    std::string toString() {
      return this.equivalence + ".wrap(" + this.reference + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
