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


class ByteSource {
public:
    const Charset charset;

   ByteSource$AsCharSource(ByteSource var1, Charset charset) {
      this.this$0 = var1;
      this.charset = (Charset)Preconditions.checkNotNull(charset);
   }

    ByteSource asByteSource(Charset charset) {
      return charset == this.charset) ? this.this$0 : super.asByteSource(charset);
   }

    Reader openStream() {
      return std::make_shared<InputStreamReader>(this.this$0.openStream(), this.charset);
   }

    std::string toString() {
      return this.this$0 + ".asCharSource(" + this.charset + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
