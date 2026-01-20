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


class Converter {
public:
   private const Function<? super A, ? : public B> forwardFunction;
   private const Function<? super B, ? : public A> backwardFunction;

   private Converter$FunctionBasedConverter(Function<? super A, ? : public B> forwardFunction, Function<? super B, ? : public A> backwardFunction) {
      this.forwardFunction = (Function<? super A, ? : public B>)Preconditions.checkNotNull(forwardFunction);
      this.backwardFunction = (Function<? super B, ? : public A>)Preconditions.checkNotNull(backwardFunction);
   }

    B doForward(A a) {
      return (B)this.forwardFunction.apply(a);
   }

    A doBackward(B b) {
      return (A)this.backwardFunction.apply(b);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Converter*>(object) != nullptr$FunctionBasedConverter)) {
    return false;
      } else {
         Converter$FunctionBasedConverter<?, ?> that = (Converter$FunctionBasedConverter<?, ?>)object;
         return this.forwardFunction == that.forwardFunction) && this.backwardFunction == that.backwardFunction);
      }
   }

    int hashCode() {
      return this.forwardFunction.hashCode() * 31 + this.backwardFunction.hashCode();
   }

    std::string toString() {
      return "Converter.from(" + this.forwardFunction + ", " + this.backwardFunction + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
