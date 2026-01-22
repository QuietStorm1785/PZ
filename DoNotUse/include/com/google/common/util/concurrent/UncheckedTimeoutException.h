#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class UncheckedTimeoutException : public RuntimeException {
public:
    static const long serialVersionUID = 0L;

    public UncheckedTimeoutException() {
   }

    public UncheckedTimeoutException(@Nullable std::string) {
      super(message);
   }

    public UncheckedTimeoutException(@Nullable Throwable) {
      super(cause);
   }

    public UncheckedTimeoutException(@Nullable std::string, @Nullable Throwable) {
      super(message, cause);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
