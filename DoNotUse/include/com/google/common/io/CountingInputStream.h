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


class CountingInputStream : public FilterInputStream {
public:
    long count;
    long mark = -1L;

    public CountingInputStream(InputStream in) {
      super((InputStream)Preconditions.checkNotNull(in));
   }

    long getCount() {
      return this.count;
   }

    int read() {
    int result = this.in.read();
      if (result != -1) {
         this.count++;
      }

    return result;
   }

    int read(byte[] b, int off, int len) {
    int result = this.in.read(b, off, len);
      if (result != -1) {
         this.count += result;
      }

    return result;
   }

    long skip(long n) {
    long result = this.in.skip(n);
      this.count += result;
    return result;
   }

   public /* synchronized - TODO: add std::mutex */ void mark(int readlimit) {
      this.in.mark(readlimit);
      this.mark = this.count;
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
      if (!this.in.markSupported()) {
         throw IOException("Mark not supported");
      } else if (this.mark == -1L) {
         throw IOException("Mark not set");
      } else {
         this.in.reset();
         this.count = this.mark;
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
