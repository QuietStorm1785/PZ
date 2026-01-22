#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Flushables {
public:
    static const Logger logger = Logger.getLogger(Flushables.class.getName());

    private Flushables() {
   }

    static void flush(Flushable flushable, bool swallowIOException) {
      try {
         flushable.flush();
      } catch (IOException var3) {
         if (!swallowIOException) {
    throw var3;
         }

         logger.log(Level.WARNING, "IOException thrown while flushing Flushable.", (Throwable)var3);
      }
   }

    static void flushQuietly(Flushable flushable) {
      try {
         flush(flushable, true);
      } catch (IOException var2) {
         logger.log(Level.SEVERE, "IOException should not have been thrown.", (Throwable)var2);
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
