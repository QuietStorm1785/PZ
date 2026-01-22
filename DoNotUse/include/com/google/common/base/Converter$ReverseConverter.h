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
   const Converter<A, B> original;
    static const long serialVersionUID = 0L;

   Converter$ReverseConverter(Converter<A, B> original) {
      this.original = original;
   }

    A doForward(B b) {
      throw std::make_unique<AssertionError>();
   }

    B doBackward(A a) {
      throw std::make_unique<AssertionError>();
   }

    A correctedDoForward(@Nullable B) {
      return (A)this.original.correctedDoBackward(b);
   }

    B correctedDoBackward(@Nullable A) {
      return (B)this.original.correctedDoForward(a);
   }

   public Converter<A, B> reverse() {
      return this.original;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Converter*>(object) != nullptr$ReverseConverter) {
         Converter$ReverseConverter<?, ?> that = (Converter$ReverseConverter<?, ?>)object;
         return this.original == that.original);
      } else {
    return false;
      }
   }

    int hashCode() {
      return ~this.original.hashCode();
   }

    std::string toString() {
      return this.original + ".reverse()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
