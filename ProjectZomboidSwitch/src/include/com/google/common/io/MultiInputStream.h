#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class MultiInputStream : public InputStream {
public:
   private Iterator<? : public ByteSource> it;
    InputStream in;

    public MultiInputStream(Iterator<? extends) {
      this.it = (Iterator<? : public ByteSource>)Preconditions.checkNotNull(it);
      this.advance();
   }

    void close() {
      if (this.in != nullptr) {
         try {
            this.in.close();
         } finally {
            this.in = nullptr;
         }
      }
   }

    void advance() {
      this.close();
      if (this.it.hasNext()) {
         this.in = this.it.next().openStream();
      }
   }

    int available() {
      return this.in == nullptr ? 0 : this.in.available();
   }

    bool markSupported() {
    return false;
   }

    int read() {
      if (this.in == nullptr) {
         return -1;
      } else {
    int result = this.in.read();
         if (result == -1) {
            this.advance();
            return this.read();
         } else {
    return result;
         }
      }
   }

    int read(@Nullable byte[], int off, int len) {
      if (this.in == nullptr) {
         return -1;
      } else {
    int result = this.in.read(b, off, len);
         if (result == -1) {
            this.advance();
            return this.read(b, off, len);
         } else {
    return result;
         }
      }
   }

    long skip(long n) {
      if (this.in != nullptr && n > 0L) {
    long result = this.in.skip(n);
         if (result != 0L) {
    return result;
         } else {
            return this.read() == -1 ? 0L : 1L + this.in.skip(n - 1L);
         }
      } else {
    return 0L;
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
