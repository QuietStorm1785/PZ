#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class Hasher {
public:
    virtual ~Hasher() = default;
    Hasher putByte(uint8_t var1);

    Hasher putBytes(byte[] var1);

    Hasher putBytes(byte[] var1, int var2, int var3);

    Hasher putShort(short var1);

    Hasher putInt(int var1);

    Hasher putLong(long var1);

    Hasher putFloat(float var1);

    Hasher putDouble(double var1);

    Hasher putBoolean(bool var1);

    Hasher putChar(char var1);

    Hasher putUnencodedChars(CharSequence var1);

    Hasher putString(CharSequence var1, Charset var2);

   <T> Hasher putObject(T var1, Funnel<? super T> var2);

    HashCode hash();

    int hashCode();
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
