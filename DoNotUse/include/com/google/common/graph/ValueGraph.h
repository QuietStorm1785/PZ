#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ValueGraph {
public:
    virtual ~ValueGraph() = default;
    V edgeValue(void* var1, void* var2);

    V edgeValueOrDefault(void* var1, void* var2, @Nullable V);

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
