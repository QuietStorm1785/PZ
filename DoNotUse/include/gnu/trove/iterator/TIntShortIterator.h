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

class TIntShortIterator {
public:
    virtual ~TIntShortIterator() = default;
    int key();

    short value();

    short setValue(short var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
