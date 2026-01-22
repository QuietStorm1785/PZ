#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashingOutputStream : public FilterOutputStream {
public:
    const Hasher hasher;

    public HashingOutputStream(HashFunction hashFunction, OutputStream out) {
      super((OutputStream)Preconditions.checkNotNull(out));
      this.hasher = (Hasher)Preconditions.checkNotNull(hashFunction.newHasher());
   }

    void write(int b) {
      this.hasher.putByte((byte)b);
      this.out.write(b);
   }

    void write(byte[] bytes, int off, int len) {
      this.hasher.putBytes(bytes, off, len);
      this.out.write(bytes, off, len);
   }

    HashCode hash() {
      return this.hasher.hash();
   }

    void close() {
      this.out.close();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
