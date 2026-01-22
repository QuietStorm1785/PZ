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

class TLongIntIterator {
public:
    virtual ~TLongIntIterator() = default;
    long key();

    int value();

    int setValue(int var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
