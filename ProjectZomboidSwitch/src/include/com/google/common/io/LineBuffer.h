#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class LineBuffer {
public:
    std::stringstream line = new std::stringstream();
    bool sawReturn;

    void add(char[] cbuf, int off, int len) {
    int pos = off;
      if (this.sawReturn && len > 0 && this.finishLine(cbuf[off] == '\n')) {
         pos = off + 1;
      }

    int start = pos;

      for (int end = off + len; pos < end; pos++) {
         switch (cbuf[pos]) {
            case '\n':
               this.line.append(cbuf, start, pos - start);
               this.finishLine(true);
               start = pos + 1;
               break;
            case '\r':
               this.line.append(cbuf, start, pos - start);
               this.sawReturn = true;
               if (pos + 1 < end && this.finishLine(cbuf[pos + 1] == '\n')) {
                  pos++;
               }

               start = pos + 1;
         }
      }

      this.line.append(cbuf, start, off + len - start);
   }

    bool finishLine(bool sawNewline) {
    std::string separator = this.sawReturn ? (sawNewline ? "\r\n" : "\r") : (sawNewline ? "\n" : "");
      this.handleLine(this.line, separator);
      this.line = std::make_unique<std::stringstream>();
      this.sawReturn = false;
    return sawNewline;
   }

    void finish() {
      if (this.sawReturn || this.line.length() > 0) {
         this.finishLine(false);
      }
   }

   protected abstract void handleLine(std::string var1, std::string var2) throws IOException;
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
