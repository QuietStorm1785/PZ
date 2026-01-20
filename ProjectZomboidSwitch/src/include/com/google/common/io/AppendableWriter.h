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

namespace com {
namespace google {
namespace common {
namespace io {


class AppendableWriter : public Writer {
public:
    const Appendable target;
    bool closed;

   AppendableWriter(Appendable target) {
      this.target = (Appendable)Preconditions.checkNotNull(target);
   }

    void write(char[] cbuf, int off, int len) {
      this.checkNotClosed();
      this.target.append(new std::string(cbuf, off, len));
   }

    void flush() {
      this.checkNotClosed();
      if (this.dynamic_cast<Flushable*>(target) != nullptr) {
         ((Flushable)this.target).flush();
      }
   }

    void close() {
      this.closed = true;
      if (this.dynamic_cast<Closeable*>(target) != nullptr) {
         ((Closeable)this.target).close();
      }
   }

    void write(int c) {
      this.checkNotClosed();
      this.target.append((char)c);
   }

    void write(@Nullable std::string) {
      this.checkNotClosed();
      this.target.append(str);
   }

    void write(@Nullable std::string, int off, int len) {
      this.checkNotClosed();
      this.target.append(str, off, off + len);
   }

    Writer append(char c) {
      this.checkNotClosed();
      this.target.append(c);
    return this;
   }

    Writer append(@Nullable CharSequence) {
      this.checkNotClosed();
      this.target.append(charSeq);
    return this;
   }

    Writer append(@Nullable CharSequence, int start, int end) {
      this.checkNotClosed();
      this.target.append(charSeq, start, end);
    return this;
   }

    void checkNotClosed() {
      if (this.closed) {
         throw IOException("Cannot write to a closed writer.");
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
