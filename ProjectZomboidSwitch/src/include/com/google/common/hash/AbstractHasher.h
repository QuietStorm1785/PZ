#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractHasher {
public:
    Hasher putBoolean(bool b) {
      return this.putByte((byte)(b ? 1 : 0));
   }

    Hasher putDouble(double d) {
      return this.putLong(double.doubleToRawLongBits(d));
   }

    Hasher putFloat(float f) {
      return this.putInt(float.floatToRawIntBits(f));
   }

    Hasher putUnencodedChars(CharSequence charSequence) {
    int i = 0;

      for (int len = charSequence.length(); i < len; i++) {
         this.putChar(charSequence.charAt(i));
      }

    return this;
   }

    Hasher putString(CharSequence charSequence, Charset charset) {
      return this.putBytes(charSequence.getBytes(charset));
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
