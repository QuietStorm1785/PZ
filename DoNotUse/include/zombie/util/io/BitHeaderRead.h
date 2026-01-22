#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace io {

class BitHeaderRead {
public:
    virtual ~BitHeaderRead() = default;
    int getStartPosition();

    void read();

    bool hasFlags(int var1);

    bool hasFlags(long var1);

    bool equals(int var1);

    bool equals(long var1);

    int getLen();

    void release();
}
} // namespace io
} // namespace util
} // namespace zombie
