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

class TByteObjectIterator {
public:
    virtual ~TByteObjectIterator() = default;
    uint8_t key();

    V value();

    V setValue(V var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
