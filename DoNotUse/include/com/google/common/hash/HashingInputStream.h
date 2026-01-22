#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashingInputStream : public FilterInputStream {
public:
    const Hasher hasher;

    public HashingInputStream(HashFunction hashFunction, InputStream in) {
      super((InputStream)Preconditions.checkNotNull(in));
      this.hasher = (Hasher)Preconditions.checkNotNull(hashFunction.newHasher());
   }

    int read() {
    int b = this.in.read();
      if (b != -1) {
         this.hasher.putByte((byte)b);
      }

    return b;
   }

    int read(byte[] bytes, int off, int len) {
    int numOfBytesRead = this.in.read(bytes, off, len);
      if (numOfBytesRead != -1) {
         this.hasher.putBytes(bytes, off, numOfBytesRead);
      }

    return numOfBytesRead;
   }

    bool markSupported() {
    return false;
   }

    void mark(int readlimit) {
   }

    void reset() {
      throw IOException("reset not supported");
   }

    HashCode hash() {
      return this.hasher.hash();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
