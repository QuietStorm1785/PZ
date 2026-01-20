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
   BaseEncoding$1(BaseEncoding var1, CharSink var2) {
      this.this$0 = var1;
      this.val$encodedSink = var2;
   }

    OutputStream openStream() {
      return this.this$0.encodingStream(this.val$encodedSink.openStream());
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
