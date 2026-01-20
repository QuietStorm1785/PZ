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


class CharSource {
public:
    const Charset charset;

   CharSource$AsByteSource(CharSource var1, Charset charset) {
      this.this$0 = var1;
      this.charset = (Charset)Preconditions.checkNotNull(charset);
   }

    CharSource asCharSource(Charset charset) {
      return charset == this.charset) ? this.this$0 : super.asCharSource(charset);
   }

    InputStream openStream() {
      return std::make_shared<ReaderInputStream>(this.this$0.openStream(), this.charset, 8192);
   }

    std::string toString() {
      return this.this$0 + ".asByteSource(" + this.charset + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
