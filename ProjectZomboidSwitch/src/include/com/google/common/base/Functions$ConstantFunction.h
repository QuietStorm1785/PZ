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
    const E value;
    static const long serialVersionUID = 0L;

   public Functions$ConstantFunction(@Nullable E value) {
      this.value = value;
   }

    E apply(@Nullable Object) {
      return this.value;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Functions*>(obj) != nullptr$ConstantFunction) {
         Functions$ConstantFunction<?> that = (Functions$ConstantFunction<?>)obj;
         return Objects.equal(this.value, that.value);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.value == nullptr ? 0 : this.value.hashCode();
   }

    std::string toString() {
      return "Functions.constant(" + this.value + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
