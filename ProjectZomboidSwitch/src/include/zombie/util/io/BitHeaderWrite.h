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

class BitHeaderWrite {
public:
    virtual ~BitHeaderWrite() = default;
    int getStartPosition();

    void create();

    void write();

    void addFlags(int var1);

    void addFlags(long var1);

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
