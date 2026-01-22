#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteStreams {
public:
    long left;
    long mark = -1L;

   ByteStreams$LimitedInputStream(InputStream in, long limit) {
      super(in);
      Preconditions.checkNotNull(in);
      Preconditions.checkArgument(limit >= 0L, "limit must be non-negative");
      this.left = limit;
   }

    int available() {
      return (int)Math.min((long)this.in.available(), this.left);
   }

   public /* synchronized - TODO: add std::mutex */ void mark(int readLimit) {
      this.in.mark(readLimit);
      this.mark = this.left;
   }

    int read() {
      if (this.left == 0L) {
         return -1;
      } else {
    int result = this.in.read();
         if (result != -1) {
            this.left--;
         }

    return result;
      }
   }

    int read(byte[] b, int off, int len) {
      if (this.left == 0L) {
         return -1;
      } else {
         len = (int)Math.min((long)len, this.left);
    int result = this.in.read(b, off, len);
         if (result != -1) {
            this.left -= result;
         }

    return result;
      }
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
      if (!this.in.markSupported()) {
         throw IOException("Mark not supported");
      } else if (this.mark == -1L) {
         throw IOException("Mark not set");
      } else {
         this.in.reset();
         this.left = this.mark;
      }
   }

    long skip(long n) {
      n = Math.min(n, this.left);
    long skipped = this.in.skip(n);
      this.left -= skipped;
    return skipped;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
