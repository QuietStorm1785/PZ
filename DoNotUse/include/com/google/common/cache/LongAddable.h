#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAddable {
public:
    virtual ~LongAddable() = default;
    void increment();

    void add(long var1);

    long sum();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
