#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ListenableFuture {
public:
    virtual ~ListenableFuture() = default;
    void addListener(Runnable var1, Executor var2);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
