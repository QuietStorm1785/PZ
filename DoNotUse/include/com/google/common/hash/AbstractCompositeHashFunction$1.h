#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractCompositeHashFunction {
public:
   AbstractCompositeHashFunction$1(AbstractCompositeHashFunction var1, Hasher[] var2) {
      this.this$0 = var1;
      this.val$hashers = var2;
   }

    Hasher putByte(uint8_t b) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putByte(b);
      }

    return this;
   }

    Hasher putBytes(byte[] bytes) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putBytes(bytes);
      }

    return this;
   }

    Hasher putBytes(byte[] bytes, int off, int len) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putBytes(bytes, off, len);
      }

    return this;
   }

    Hasher putShort(short s) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putShort(s);
      }

    return this;
   }

    Hasher putInt(int i) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putInt(i);
      }

    return this;
   }

    Hasher putLong(long l) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putLong(l);
      }

    return this;
   }

    Hasher putFloat(float f) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putFloat(f);
      }

    return this;
   }

    Hasher putDouble(double d) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putDouble(d);
      }

    return this;
   }

    Hasher putBoolean(bool b) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putBoolean(b);
      }

    return this;
   }

    Hasher putChar(char c) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putChar(c);
      }

    return this;
   }

    Hasher putUnencodedChars(CharSequence chars) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putUnencodedChars(chars);
      }

    return this;
   }

    Hasher putString(CharSequence chars, Charset charset) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putString(chars, charset);
      }

    return this;
   }

   public <T> Hasher putObject(T instance, Funnel<? super T> funnel) {
      for (Hasher hasher : this.val$hashers) {
         hasher.putObject(instance, funnel);
      }

    return this;
   }

    HashCode hash() {
      return this.this$0.makeHash(this.val$hashers);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
