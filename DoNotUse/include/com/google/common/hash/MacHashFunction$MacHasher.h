#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/crypto/Mac.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class MacHashFunction {
public:
    const Mac mac;
    bool done;

   private MacHashFunction$MacHasher(Mac mac) {
      this.mac = mac;
   }

    void update(uint8_t b) {
      this.checkNotDone();
      this.mac.update(b);
   }

    void update(byte[] b) {
      this.checkNotDone();
      this.mac.update(b);
   }

    void update(byte[] b, int off, int len) {
      this.checkNotDone();
      this.mac.update(b, off, len);
   }

    void checkNotDone() {
      Preconditions.checkState(!this.done, "Cannot re-use a Hasher after calling hash() on it");
   }

    HashCode hash() {
      this.checkNotDone();
      this.done = true;
      return HashCode.fromBytesNoCopy(this.mac.doFinal());
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
