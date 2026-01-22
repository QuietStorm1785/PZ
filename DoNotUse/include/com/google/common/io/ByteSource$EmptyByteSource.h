#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/ByteSource/ByteArrayByteSource.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSource {
public:
   static const ByteSource$EmptyByteSource INSTANCE = new ByteSource$EmptyByteSource();

   ByteSource$EmptyByteSource() {
      super(new byte[0]);
   }

    CharSource asCharSource(Charset charset) {
      Preconditions.checkNotNull(charset);
      return CharSource.empty();
   }

   public byte[] read() {
      return this.bytes;
   }

    std::string toString() {
      return "ByteSource.empty()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
