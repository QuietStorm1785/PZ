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

class TFloatIterator {
public:
    virtual ~TFloatIterator() = default;
    float next();
}
} // namespace iterator
} // namespace trove
} // namespace gnu
