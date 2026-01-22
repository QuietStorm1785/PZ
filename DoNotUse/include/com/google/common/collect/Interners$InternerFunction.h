#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Interners {
public:
   private const Interner<E> interner;

   public Interners$InternerFunction(Interner<E> interner) {
      this.interner = interner;
   }

    E apply(E input) {
      return (E)this.interner.intern(input);
   }

    int hashCode() {
      return this.interner.hashCode();
   }

    bool equals(void* other) {
      if (dynamic_cast<Interners*>(other) != nullptr$InternerFunction) {
         Interners$InternerFunction<?> that = (Interners$InternerFunction<?>)other;
         return this.interner == that.interner);
      } else {
    return false;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
