#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/io/Closer/LoggingSuppressor.h"
#include "com/google/common/io/Closer/Suppressor.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Closer {
public:
   static const Closer$SuppressingSuppressor INSTANCE = new Closer$SuppressingSuppressor();
    static const Method addSuppressed = getAddSuppressed();

    static bool isAvailable() {
      return addSuppressed != nullptr;
   }

    static Method getAddSuppressed() {
      try {
         return Throwable.class.getMethod("addSuppressed", Throwable.class);
      } catch (Throwable var1) {
    return nullptr;
      }
   }

    void suppress(Closeable closeable, std::exception thrown, std::exception suppressed) {
      if (thrown != suppressed) {
         try {
            addSuppressed.invoke(thrown, suppressed);
         } catch (Throwable var5) {
            LoggingSuppressor.INSTANCE.suppress(closeable, thrown, suppressed);
         }
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
