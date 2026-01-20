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

class TShortObjectIterator {
public:
    virtual ~TShortObjectIterator() = default;
    short key();

    V value();

    V setValue(V var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
