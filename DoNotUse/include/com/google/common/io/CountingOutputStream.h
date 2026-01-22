#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class CountingOutputStream : public FilterOutputStream {
public:
    long count;

    public CountingOutputStream(OutputStream out) {
      super((OutputStream)Preconditions.checkNotNull(out));
   }

    long getCount() {
      return this.count;
   }

    void write(byte[] b, int off, int len) {
      this.out.write(b, off, len);
      this.count += len;
   }

    void write(int b) {
      this.out.write(b);
      this.count++;
   }

    void close() {
      this.out.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
