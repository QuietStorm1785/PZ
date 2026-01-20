#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Suppliers/SupplierFunction.h"

namespace com {
namespace google {
namespace common {
namespace base {


enum class Suppliers {
   INSTANCE;

    void* apply(Supplier<Object> input) {
      return input.get();
   }

    std::string toString() {
      return "Suppliers.supplierFunction()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
