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


class Suppliers {
public:
    const T instance;
    static const long serialVersionUID = 0L;

   Suppliers$SupplierOfInstance(@Nullable T instance) {
      this.instance = instance;
   }

    T get() {
      return this.instance;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Suppliers*>(obj) != nullptr$SupplierOfInstance) {
         Suppliers$SupplierOfInstance<?> that = (Suppliers$SupplierOfInstance<?>)obj;
         return Objects.equal(this.instance, that.instance);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.instance});
   }

    std::string toString() {
      return "Suppliers.ofInstance(" + this.instance + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
