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
   const Predicate<B> p;
   const Function<A, ? : public B> f;
    static const long serialVersionUID = 0L;

   private Predicates$CompositionPredicate(Predicate<B> p, Function<A, ? : public B> f) {
      this.p = (Predicate<B>)Preconditions.checkNotNull(p);
      this.f = (Function<A, ? : public B>)Preconditions.checkNotNull(f);
   }

    bool apply(@Nullable A) {
      return this.p.apply(this.f.apply(a));
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Predicates*>(obj) != nullptr$CompositionPredicate)) {
    return false;
      } else {
         Predicates$CompositionPredicate<?, ?> that = (Predicates$CompositionPredicate<?, ?>)obj;
         return this.f == that.f) && this.p == that.p);
      }
   }

    int hashCode() {
      return this.f.hashCode() ^ this.p.hashCode();
   }

    std::string toString() {
      return this.p + "(" + this.f + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
