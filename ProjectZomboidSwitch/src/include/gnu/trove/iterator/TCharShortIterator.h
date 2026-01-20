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

class TCharShortIterator {
public:
    virtual ~TCharShortIterator() = default;
    char key();

    short value();

    short setValue(short var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
