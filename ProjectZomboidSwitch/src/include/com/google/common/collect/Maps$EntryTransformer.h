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


class Maps {
public:
    virtual ~Maps() = default;
    V2 transformEntry(@Nullable K, @Nullable V1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
