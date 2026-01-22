#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
   BaseEncoding$5(Appendable var1, Writer var2) {
      this.val$seperatingAppendable = var1;
      this.val$delegate = var2;
   }

    void write(int c) {
      this.val$seperatingAppendable.append((char)c);
   }

    void write(char[] chars, int off, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void flush() {
      this.val$delegate.flush();
   }

    void close() {
      this.val$delegate.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
