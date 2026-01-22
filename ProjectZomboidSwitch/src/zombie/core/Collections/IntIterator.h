#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Collections {

class IntIterator {
public:
    virtual ~IntIterator() = default;
    int next();

    bool hasNext();
}
} // namespace Collections
} // namespace core
} // namespace zombie
