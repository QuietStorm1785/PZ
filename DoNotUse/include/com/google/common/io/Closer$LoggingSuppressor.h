#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/io/Closer/Suppressor.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Closer {
public:
   static const Closer$LoggingSuppressor INSTANCE = new Closer$LoggingSuppressor();

    void suppress(Closeable closeable, std::exception thrown, std::exception suppressed) {
      Closeables.logger.log(Level.WARNING, "Suppressing exception thrown when closing " + closeable, suppressed);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
