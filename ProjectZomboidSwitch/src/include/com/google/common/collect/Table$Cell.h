#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Table {
public:
    virtual ~Table() = default;
    R getRowKey();

    C getColumnKey();

    V getValue();

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
