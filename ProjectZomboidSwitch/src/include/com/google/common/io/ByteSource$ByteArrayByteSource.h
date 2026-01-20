#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/HashCode.h"
#include "com/google/common/hash/HashFunction.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSource {
public:
   const byte[] bytes;
    const int offset;
    const int length;

   ByteSource$ByteArrayByteSource(byte[] bytes) {
      this(bytes, 0, bytes.length);
   }

   ByteSource$ByteArrayByteSource(byte[] bytes, int offset, int length) {
      this.bytes = bytes;
      this.offset = offset;
      this.length = length;
   }

    InputStream openStream() {
      return std::make_shared<ByteArrayInputStream>(this.bytes, this.offset, this.length);
   }

    InputStream openBufferedStream() {
      return this.openStream();
   }

    bool isEmpty() {
      return this.length == 0;
   }

    long size() {
      return this.length;
   }

   public Optional<int64_t> sizeIfKnown() {
      return Optional.of((long)this.length);
   }

   public byte[] read() {
      return Arrays.copyOfRange(this.bytes, this.offset, this.offset + this.length);
   }

    long copyTo(OutputStream output) {
      output.write(this.bytes, this.offset, this.length);
      return this.length;
   }

   public <T> T read(ByteProcessor<T> processor) throws IOException {
      processor.processBytes(this.bytes, this.offset, this.length);
      return (T)processor.getResult();
   }

    HashCode hash(HashFunction hashFunction) {
      return hashFunction.hashBytes(this.bytes, this.offset, this.length);
   }

    ByteSource slice(long offset, long length) {
      Preconditions.checkArgument(offset >= 0L, "offset (%s) may not be negative", offset);
      Preconditions.checkArgument(length >= 0L, "length (%s) may not be negative", length);
      offset = Math.min(offset, (long)this.length);
      length = Math.min(length, this.length - offset);
    int newOffset = this.offset + (int)offset;
      return new ByteSource$ByteArrayByteSource(this.bytes, newOffset, (int)length);
   }

    std::string toString() {
      return "ByteSource.wrap(" + Ascii.truncate(BaseEncoding.base16().encode(this.bytes, this.offset, this.length), 30, "...") + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
