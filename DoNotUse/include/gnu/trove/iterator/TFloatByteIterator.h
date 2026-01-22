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

class TFloatByteIterator {
public:
    virtual ~TFloatByteIterator() = default;
    float key();

    uint8_t value();

    uint8_t setValue(uint8_t var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
