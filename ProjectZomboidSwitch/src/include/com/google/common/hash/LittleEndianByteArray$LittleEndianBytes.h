#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace hash {

class LittleEndianByteArray {
public:
    virtual ~LittleEndianByteArray() = default;
    long getLongLittleEndian(byte[] var1, int var2);

    void putLongLittleEndian(byte[] var1, int var2, long var3);
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
