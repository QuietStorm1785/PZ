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
   private const Supplier<T> supplier;
    static const long serialVersionUID = 0L;

   private Functions$SupplierFunction(Supplier<T> supplier) {
      this.supplier = (Supplier<T>)Preconditions.checkNotNull(supplier);
   }

    T apply(@Nullable Object) {
      return (T)this.supplier.get();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Functions*>(obj) != nullptr$SupplierFunction) {
         Functions$SupplierFunction<?> that = (Functions$SupplierFunction<?>)obj;
         return this.supplier == that.supplier);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.supplier.hashCode();
   }

    std::string toString() {
      return "Functions.forSupplier(" + this.supplier + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
