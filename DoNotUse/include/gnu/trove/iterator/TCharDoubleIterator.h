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

class TCharDoubleIterator {
public:
    virtual ~TCharDoubleIterator() = default;
    char key();

    double value();

    double setValue(double var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
