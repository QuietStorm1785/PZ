#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace iterator {

class TLongLongIterator {
public:
    virtual ~TLongLongIterator() = default;
    long key();

    long value();

    long setValue(long var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
