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


class PrimitiveSink {
public:
    virtual ~PrimitiveSink() = default;
    PrimitiveSink putByte(uint8_t var1);

    PrimitiveSink putBytes(byte[] var1);

    PrimitiveSink putBytes(byte[] var1, int var2, int var3);

    PrimitiveSink putShort(short var1);

    PrimitiveSink putInt(int var1);

    PrimitiveSink putLong(long var1);

    PrimitiveSink putFloat(float var1);

    PrimitiveSink putDouble(double var1);

    PrimitiveSink putBoolean(bool var1);

    PrimitiveSink putChar(char var1);

    PrimitiveSink putUnencodedChars(CharSequence var1);

    PrimitiveSink putString(CharSequence var1, Charset var2);
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
