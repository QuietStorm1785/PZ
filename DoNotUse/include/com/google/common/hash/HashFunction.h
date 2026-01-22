#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashFunction {
public:
    virtual ~HashFunction() = default;
    Hasher newHasher();

    Hasher newHasher(int var1);

    HashCode hashInt(int var1);

    HashCode hashLong(long var1);

    HashCode hashBytes(byte[] var1);

    HashCode hashBytes(byte[] var1, int var2, int var3);

    HashCode hashUnencodedChars(CharSequence var1);

    HashCode hashString(CharSequence var1, Charset var2);

   <T> HashCode hashObject(T var1, Funnel<? super T> var2);

    int bits();
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
