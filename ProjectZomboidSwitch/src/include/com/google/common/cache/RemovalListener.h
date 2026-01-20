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


class RemovalListener {
public:
    virtual ~RemovalListener() = default;
    void onRemoval(V> var1);
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
