#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractByteHasher : public AbstractHasher {
public:
    const ByteBuffer scratch = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);

   protected abstract void update(byte var1);

    void update(byte[] b) {
      this.update(b, 0, b.length);
   }

    void update(byte[] b, int off, int len) {
      for (int i = off; i < off + len; i++) {
         this.update(b[i]);
      }
   }

    Hasher putByte(uint8_t b) {
      this.update(b);
    return this;
   }

    Hasher putBytes(byte[] bytes) {
      Preconditions.checkNotNull(bytes);
      this.update(bytes);
    return this;
   }

    Hasher putBytes(byte[] bytes, int off, int len) {
      Preconditions.checkPositionIndexes(off, off + len, bytes.length);
      this.update(bytes, off, len);
    return this;
   }

    Hasher update(int bytes) {
      try {
         this.update(this.scratch.array(), 0, bytes);
      } finally {
         ((Buffer)this.scratch).clear();
      }

    return this;
   }

    Hasher putShort(short s) {
      this.scratch.putShort(s);
      return this.update(2);
   }

    Hasher putInt(int i) {
      this.scratch.putInt(i);
      return this.update(4);
   }

    Hasher putLong(long l) {
      this.scratch.putLong(l);
      return this.update(8);
   }

    Hasher putChar(char c) {
      this.scratch.putChar(c);
      return this.update(2);
   }

   public <T> Hasher putObject(T instance, Funnel<? super T> funnel) {
      funnel.funnel(instance, this);
    return this;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
