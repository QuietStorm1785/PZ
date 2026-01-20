#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Closeables {
public:
    static const Logger logger = Logger.getLogger(Closeables.class.getName());

    private Closeables() {
   }

    static void close(@Nullable Closeable, bool swallowIOException) {
      if (closeable != nullptr) {
         try {
            closeable.close();
         } catch (IOException var3) {
            if (!swallowIOException) {
    throw var3;
            }

            logger.log(Level.WARNING, "IOException thrown while closing Closeable.", (Throwable)var3);
         }
      }
   }

    static void closeQuietly(@Nullable InputStream) {
      try {
         close(inputStream, true);
      } catch (IOException var2) {
         throw AssertionError(var2);
      }
   }

    static void closeQuietly(@Nullable Reader) {
      try {
         close(reader, true);
      } catch (IOException var2) {
         throw AssertionError(var2);
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
