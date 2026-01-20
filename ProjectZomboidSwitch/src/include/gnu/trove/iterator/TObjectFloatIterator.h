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

class TObjectFloatIterator {
public:
    virtual ~TObjectFloatIterator() = default;
    K key();

    float value();

    float setValue(float var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
