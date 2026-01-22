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

class TByteDoubleIterator {
public:
    virtual ~TByteDoubleIterator() = default;
    uint8_t key();

    double value();

    double setValue(double var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
