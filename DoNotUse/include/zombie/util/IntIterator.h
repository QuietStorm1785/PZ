#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class IntIterator {
public:
    virtual ~IntIterator() = default;
    bool hasNext();

    int next();

    void remove();
}
} // namespace util
} // namespace zombie
