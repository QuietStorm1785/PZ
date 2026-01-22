#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntIterator.h"

namespace zombie {
namespace util {
namespace list {


class IntListIterator {
public:
    virtual ~IntListIterator() = default;
    void add(int var1);

    bool hasPrevious();

    int nextIndex();

    int previous();

    int previousIndex();

    void set(int var1);
}
} // namespace list
} // namespace util
} // namespace zombie
