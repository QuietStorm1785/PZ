#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
   BaseEncoding$3(Reader var1, CharMatcher var2) {
      this.val$delegate = var1;
      this.val$toIgnore = var2;
   }

    int read() {
    int readChar;
      do {
         readChar = this.val$delegate.read();
      } while (readChar != -1 && this.val$toIgnore.matches((char)readChar));

    return readChar;
   }

    int read(char[] cbuf, int off, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void close() {
      this.val$delegate.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
