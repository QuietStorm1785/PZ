#pragma once
#include <stack>
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


class FileBackedOutputStream {
public:
   FileBackedOutputStream$1(FileBackedOutputStream var1) {
      this.this$0 = var1;
   }

    InputStream openStream() {
      return FileBackedOutputStream.access$100(this.this$0);
   }

    void finalize() {
      try {
         this.this$0.reset();
      } catch (Throwable var2) {
         var2.printStackTrace(System.err);
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
