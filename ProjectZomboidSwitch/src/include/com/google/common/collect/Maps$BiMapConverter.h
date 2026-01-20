#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Converter.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const BiMap<A, B> bimap;
    static const long serialVersionUID = 0L;

   Maps$BiMapConverter(BiMap<A, B> bimap) {
      this.bimap = (BiMap<A, B>)Preconditions.checkNotNull(bimap);
   }

    B doForward(A a) {
    return convert();
   }

    A doBackward(B b) {
    return convert();
   }

   private static <X, Y> Y convert(BiMap<X, Y> bimap, X input) {
    Y output = (Y)bimap.get(input);
      Preconditions.checkArgument(output != nullptr, "No non-nullptr mapping present for input: %s", input);
    return output;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Maps*>(object) != nullptr$BiMapConverter) {
         Maps$BiMapConverter<?, ?> that = (Maps$BiMapConverter<?, ?>)object;
         return this.bimap == that.bimap);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.bimap.hashCode();
   }

    std::string toString() {
      return "Maps.asConverter(" + this.bimap + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
