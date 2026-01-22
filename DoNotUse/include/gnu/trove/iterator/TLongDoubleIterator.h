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

class TLongDoubleIterator {
public:
    virtual ~TLongDoubleIterator() = default;
    long key();

    double value();

    double setValue(double var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
