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
   private const Function<B, C> g;
   private const Function<A, ? : public B> f;
    static const long serialVersionUID = 0L;

   public Functions$FunctionComposition(Function<B, C> g, Function<A, ? : public B> f) {
      this.g = (Function<B, C>)Preconditions.checkNotNull(g);
      this.f = (Function<A, ? : public B>)Preconditions.checkNotNull(f);
   }

    C apply(@Nullable A) {
      return (C)this.g.apply(this.f.apply(a));
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Functions*>(obj) != nullptr$FunctionComposition)) {
    return false;
      } else {
         Functions$FunctionComposition<?, ?, ?> that = (Functions$FunctionComposition<?, ?, ?>)obj;
         return this.f == that.f) && this.g == that.g);
      }
   }

    int hashCode() {
      return this.f.hashCode() ^ this.g.hashCode();
   }

    std::string toString() {
      return this.g + "(" + this.f + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
