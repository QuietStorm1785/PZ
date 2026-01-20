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

class TCharLongIterator {
public:
    virtual ~TCharLongIterator() = default;
    char key();

    long value();

    long setValue(long var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
