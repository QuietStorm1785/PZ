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


class CharStreams {
public:
   private static const CharStreams$NullWriter INSTANCE = new CharStreams$NullWriter();

   private CharStreams$NullWriter() {
   }

    void write(int c) {
   }

    void write(char[] cbuf) {
      Preconditions.checkNotNull(cbuf);
   }

    void write(char[] cbuf, int off, int len) {
      Preconditions.checkPositionIndexes(off, off + len, cbuf.length);
   }

    void write(const std::string& str) {
      Preconditions.checkNotNull(str);
   }

    void write(const std::string& str, int off, int len) {
      Preconditions.checkPositionIndexes(off, off + len, str.length());
   }

    Writer append(CharSequence csq) {
      Preconditions.checkNotNull(csq);
    return this;
   }

    Writer append(CharSequence csq, int start, int end) {
      Preconditions.checkPositionIndexes(start, end, csq.length());
    return this;
   }

    Writer append(char c) {
    return this;
   }

    void flush() {
   }

    void close() {
   }

    std::string toString() {
      return "CharStreams.nullWriter()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
