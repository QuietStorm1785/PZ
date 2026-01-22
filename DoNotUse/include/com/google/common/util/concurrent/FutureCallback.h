#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class FutureCallback {
public:
    virtual ~FutureCallback() = default;
    void onSuccess(@Nullable V);

    void onFailure(std::exception var1);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
