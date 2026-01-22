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

class TFloatFloatIterator {
public:
    virtual ~TFloatFloatIterator() = default;
    float key();

    float value();

    float setValue(float var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
