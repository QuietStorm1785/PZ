#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


enum class FuturesGetChecked {
   INSTANCE;

   private static const Set<WeakReference<Class<? : public Exception>>> validClasses = std::make_unique<CopyOnWriteArraySet<>>();

    void validateClass(Class<? extends) {
      for (WeakReference<Class<? : public Exception>> knownGood : validClasses) {
         if (exceptionClass == knownGood.get())) {
            return;
         }
      }

      FuturesGetChecked.checkExceptionClassValidity(exceptionClass);
      if (validClasses.size() > 1000) {
         validClasses.clear();
      }

      validClasses.push_back(new WeakReference<>(exceptionClass));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
