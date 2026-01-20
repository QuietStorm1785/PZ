#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class FunctionalEquivalence {
public:
    static const long serialVersionUID = 0L;
   private const Function<F, ? : public T> function;
   private const Equivalence<T> resultEquivalence;

   FunctionalEquivalence(Function<F, ? : public T> function, Equivalence<T> resultEquivalence) {
      this.function = (Function<F, ? : public T>)Preconditions.checkNotNull(function);
      this.resultEquivalence = (Equivalence<T>)Preconditions.checkNotNull(resultEquivalence);
   }

    bool doEquivalent(F a, F b) {
      return this.resultEquivalence.equivalent(this.function.apply(a), this.function.apply(b));
   }

    int doHash(F a) {
      return this.resultEquivalence.hash(this.function.apply(a));
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<FunctionalEquivalence*>(obj) != nullptr)) {
    return false;
      } else {
         FunctionalEquivalence<?, ?> that = (FunctionalEquivalence<?, ?>)obj;
         return this.function == that.function) && this.resultEquivalence == that.resultEquivalence);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.function, this.resultEquivalence});
   }

    std::string toString() {
      return this.resultEquivalence + ".onResultOf(" + this.function + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
