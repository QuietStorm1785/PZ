#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSink {
public:
    const Charset charset;

   private ByteSink$AsCharSink(ByteSink var1, Charset charset) {
      this.this$0 = var1;
      this.charset = (Charset)Preconditions.checkNotNull(charset);
   }

    Writer openStream() {
      return std::make_shared<OutputStreamWriter>(this.this$0.openStream(), this.charset);
   }

    std::string toString() {
      return this.this$0 + ".asCharSink(" + this.charset + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
