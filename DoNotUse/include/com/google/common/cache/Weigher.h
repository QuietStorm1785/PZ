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


class Weigher {
public:
    virtual ~Weigher() = default;
    int weigh(K var1, V var2);
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
