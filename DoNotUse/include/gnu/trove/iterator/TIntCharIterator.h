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

class TIntCharIterator {
public:
    virtual ~TIntCharIterator() = default;
    int key();

    char value();

    char setValue(char var1);
}
} // namespace iterator
} // namespace trove
} // namespace gnu
