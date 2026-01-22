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

class TIterator {
public:
    virtual ~TIterator() = default;
    bool hasNext();

    void remove();
}
} // namespace iterator
} // namespace trove
} // namespace gnu
