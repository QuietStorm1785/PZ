#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Converter {
public:
   static const Converter$IdentityConverter INSTANCE = new Converter$IdentityConverter();
    static const long serialVersionUID = 0L;

   private Converter$IdentityConverter() {
   }

    T doForward(T t) {
    return t;
   }

    T doBackward(T t) {
    return t;
   }

   public Converter$IdentityConverter<T> reverse() {
    return this;
   }

   <S> Converter<T, S> doAndThen(Converter<T, S> otherConverter) {
      return (Converter<T, S>)Preconditions.checkNotNull(otherConverter, "otherConverter");
   }

    std::string toString() {
      return "Converter.identity()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
