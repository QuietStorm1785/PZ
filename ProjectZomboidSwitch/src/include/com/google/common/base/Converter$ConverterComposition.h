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
   const Converter<A, B> first;
   const Converter<B, C> second;
    static const long serialVersionUID = 0L;

   Converter$ConverterComposition(Converter<A, B> first, Converter<B, C> second) {
      this.first = first;
      this.second = second;
   }

    C doForward(A a) {
      throw std::make_unique<AssertionError>();
   }

    A doBackward(C c) {
      throw std::make_unique<AssertionError>();
   }

    C correctedDoForward(@Nullable A) {
      return (C)this.second.correctedDoForward(this.first.correctedDoForward(a));
   }

    A correctedDoBackward(@Nullable C) {
      return (A)this.first.correctedDoBackward(this.second.correctedDoBackward(c));
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Converter*>(object) != nullptr$ConverterComposition)) {
    return false;
      } else {
         Converter$ConverterComposition<?, ?, ?> that = (Converter$ConverterComposition<?, ?, ?>)object;
         return this.first == that.first) && this.second == that.second);
      }
   }

    int hashCode() {
      return 31 * this.first.hashCode() + this.second.hashCode();
   }

    std::string toString() {
      return this.first + ".andThen(" + this.second + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
