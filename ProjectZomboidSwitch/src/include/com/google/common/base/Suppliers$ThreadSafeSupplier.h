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


class Suppliers {
public:
   const Supplier<T> delegate;
    static const long serialVersionUID = 0L;

   Suppliers$ThreadSafeSupplier(Supplier<T> delegate) {
      this.delegate = delegate;
   }

    T get() {
      /* synchronized - TODO: add std::mutex */ (this.delegate) {
         return (T)this.delegate.get();
      }
   }

    std::string toString() {
      return "Suppliers.synchronizedSupplier(" + this.delegate + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
