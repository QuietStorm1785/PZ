#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSequenceReader : public Reader {
public:
    CharSequence seq;
    int pos;
    int mark;

    public CharSequenceReader(CharSequence seq) {
      this.seq = (CharSequence)Preconditions.checkNotNull(seq);
   }

    void checkOpen() {
      if (this.seq == nullptr) {
         throw IOException("reader closed");
      }
   }

    bool hasRemaining() {
      return this.remaining() > 0;
   }

    int remaining() {
      return this.seq.length() - this.pos;
   }

   public /* synchronized - TODO: add std::mutex */ int read(CharBuffer target) throws IOException {
      Preconditions.checkNotNull(target);
      this.checkOpen();
      if (!this.hasRemaining()) {
         return -1;
      } else {
    int charsToRead = Math.min(target.remaining(), this.remaining());

         for (int i = 0; i < charsToRead; i++) {
            target.put(this.seq.charAt(this.pos++));
         }

    return charsToRead;
      }
   }

   public /* synchronized - TODO: add std::mutex */ int read() throws IOException {
      this.checkOpen();
      return this.hasRemaining() ? this.seq.charAt(this.pos++) : -1;
   }

   public /* synchronized - TODO: add std::mutex */ int read(char[] cbuf, int off, int len) throws IOException {
      Preconditions.checkPositionIndexes(off, off + len, cbuf.length);
      this.checkOpen();
      if (!this.hasRemaining()) {
         return -1;
      } else {
    int charsToRead = Math.min(len, this.remaining());

         for (int i = 0; i < charsToRead; i++) {
            cbuf[off + i] = this.seq.charAt(this.pos++);
         }

    return charsToRead;
      }
   }

   public /* synchronized - TODO: add std::mutex */ long skip(long n) throws IOException {
      Preconditions.checkArgument(n >= 0L, "n (%s) may not be negative", n);
      this.checkOpen();
    int charsToSkip = (int)Math.min((long)this.remaining(), n);
      this.pos += charsToSkip;
    return charsToSkip;
   }

   public /* synchronized - TODO: add std::mutex */ boolean ready() throws IOException {
      this.checkOpen();
    return true;
   }

    bool markSupported() {
    return true;
   }

   public /* synchronized - TODO: add std::mutex */ void mark(int readAheadLimit) throws IOException {
      Preconditions.checkArgument(readAheadLimit >= 0, "readAheadLimit (%s) may not be negative", readAheadLimit);
      this.checkOpen();
      this.mark = this.pos;
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
      this.checkOpen();
      this.pos = this.mark;
   }

   public /* synchronized - TODO: add std::mutex */ void close() throws IOException {
      this.seq = nullptr;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
