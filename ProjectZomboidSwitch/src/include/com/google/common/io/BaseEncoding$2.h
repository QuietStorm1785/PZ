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
   BaseEncoding$2(BaseEncoding var1, CharSource var2) {
      this.this$0 = var1;
      this.val$encodedSource = var2;
   }

    InputStream openStream() {
      return this.this$0.decodingStream(this.val$encodedSource.openStream());
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
