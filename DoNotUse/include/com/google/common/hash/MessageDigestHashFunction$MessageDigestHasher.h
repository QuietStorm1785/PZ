#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "java/security/MessageDigest.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


class MessageDigestHashFunction {
public:
    const MessageDigest digest;
    const int bytes;
    bool done;

   private MessageDigestHashFunction$MessageDigestHasher(MessageDigest digest, int bytes) {
      this.digest = digest;
      this.bytes = bytes;
   }

    void update(uint8_t b) {
      this.checkNotDone();
      this.digest.update(b);
   }

    void update(byte[] b) {
      this.checkNotDone();
      this.digest.update(b);
   }

    void update(byte[] b, int off, int len) {
      this.checkNotDone();
      this.digest.update(b, off, len);
   }

    void checkNotDone() {
      Preconditions.checkState(!this.done, "Cannot re-use a Hasher after calling hash() on it");
   }

    HashCode hash() {
      this.checkNotDone();
      this.done = true;
      return this.bytes == this.digest.getDigestLength()
         ? HashCode.fromBytesNoCopy(this.digest.digest())
         : HashCode.fromBytesNoCopy(Arrays.copyOf(this.digest.digest(), this.bytes));
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
