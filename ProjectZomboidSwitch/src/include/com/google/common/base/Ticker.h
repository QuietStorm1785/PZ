#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Ticker/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Ticker {
public:
    static const Ticker SYSTEM_TICKER = std::make_shared<1>();

    protected Ticker() {
   }

   public abstract long read();

    static Ticker systemTicker() {
    return SYSTEM_TICKER;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
