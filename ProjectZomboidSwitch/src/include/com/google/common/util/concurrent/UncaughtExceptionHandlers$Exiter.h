#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class UncaughtExceptionHandlers {
public:
    static const Logger logger = Logger.getLogger(UncaughtExceptionHandlers$Exiter.class.getName());
    const Runtime runtime;

   UncaughtExceptionHandlers$Exiter(Runtime runtime) {
      this.runtime = runtime;
   }

    void uncaughtException(Thread t, std::exception e) {
      try {
         logger.log(Level.SEVERE, std::string.format(Locale.ROOT, "Caught an exception in %s.  Shutting down.", t), e);
      } catch (Throwable var7) {
         System.err.println(e.getMessage());
         System.err.println(var7.getMessage());
      } finally {
         this.runtime.exit(1);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
