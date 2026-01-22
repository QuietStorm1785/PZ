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
   const Function<? super F, T> function;
   const Supplier<F> supplier;
    static const long serialVersionUID = 0L;

   Suppliers$SupplierComposition(Function<? super F, T> function, Supplier<F> supplier) {
      this.function = function;
      this.supplier = supplier;
   }

    T get() {
      return (T)this.function.apply(this.supplier.get());
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Suppliers*>(obj) != nullptr$SupplierComposition)) {
    return false;
      } else {
         Suppliers$SupplierComposition<?, ?> that = (Suppliers$SupplierComposition<?, ?>)obj;
         return this.function == that.function) && this.supplier == that.supplier);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.function, this.supplier});
   }

    std::string toString() {
      return "Suppliers.compose(" + this.function + ", " + this.supplier + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
