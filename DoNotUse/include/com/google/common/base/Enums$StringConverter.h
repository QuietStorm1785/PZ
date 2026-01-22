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


class Enums {
public:
   private const Class<T> enumClass;
    static const long serialVersionUID = 0L;

   Enums$StringConverter(Class<T> enumClass) {
      this.enumClass = (Class<T>)Preconditions.checkNotNull(enumClass);
   }

    T doForward(const std::string& value) {
      return Enum.valueOf(this.enumClass, value);
   }

    std::string doBackward(T enumValue) {
      return enumValue.name();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Enums*>(object) != nullptr$StringConverter) {
         Enums$StringConverter<?> that = (Enums$StringConverter<?>)object;
         return this.enumClass == that.enumClass);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.enumClass.hashCode();
   }

    std::string toString() {
      return "Enums.stringConverter(" + this.enumClass.getName() + ".class)";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
