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


class FileBackedOutputStream {
public:
   FileBackedOutputStream$2(FileBackedOutputStream var1) {
      this.this$0 = var1;
   }

    InputStream openStream() {
      return FileBackedOutputStream.access$100(this.this$0);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
