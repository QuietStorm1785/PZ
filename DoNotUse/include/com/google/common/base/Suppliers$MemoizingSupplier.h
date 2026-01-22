#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Suppliers {
public:
   const Supplier<T> delegate;
   transient volatile boolean initialized;
   transient T value;
    static const long serialVersionUID = 0L;

   Suppliers$MemoizingSupplier(Supplier<T> delegate) {
      this.delegate = delegate;
   }

    T get() {
      if (!this.initialized) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (!this.initialized) {
    T t = (T)this.delegate.get();
               this.value = t;
               this.initialized = true;
    return t;
            }
         }
      }

      return this.value;
   }

    std::string toString() {
      return "Suppliers.memoize(" + this.delegate + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
