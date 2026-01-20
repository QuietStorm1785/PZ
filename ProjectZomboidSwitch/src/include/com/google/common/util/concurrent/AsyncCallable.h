#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AsyncCallable {
public:
    virtual ~AsyncCallable() = default;
   ListenableFuture<V> call() throws Exception;
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
