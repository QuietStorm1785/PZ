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


class MultiReader : public Reader {
public:
   private const Iterator<? : public CharSource> it;
    Reader current;

   MultiReader(Iterator<? : public CharSource> readers) throws IOException {
      this.it = readers;
      this.advance();
   }

    void advance() {
      this.close();
      if (this.it.hasNext()) {
         this.current = this.it.next().openStream();
      }
   }

    int read(@Nullable char[], int off, int len) {
      if (this.current == nullptr) {
         return -1;
      } else {
    int result = this.current.read(cbuf, off, len);
         if (result == -1) {
            this.advance();
            return this.read(cbuf, off, len);
         } else {
    return result;
         }
      }
   }

    long skip(long n) {
      Preconditions.checkArgument(n >= 0L, "n is negative");
      if (n > 0L) {
         while (this.current != nullptr) {
    long result = this.current.skip(n);
            if (result > 0L) {
    return result;
            }

            this.advance();
         }
      }

    return 0L;
   }

    bool ready() {
      return this.current != nullptr && this.current.ready();
   }

    void close() {
      if (this.current != nullptr) {
         try {
            this.current.close();
         } finally {
            this.current = nullptr;
         }
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
