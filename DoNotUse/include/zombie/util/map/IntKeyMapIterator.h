#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace map {

class IntKeyMapIterator {
public:
    virtual ~IntKeyMapIterator() = default;
    bool hasNext();

    void next();

    void remove();

    int getKey();

    V getValue();
}
} // namespace map
} // namespace util
} // namespace zombie
