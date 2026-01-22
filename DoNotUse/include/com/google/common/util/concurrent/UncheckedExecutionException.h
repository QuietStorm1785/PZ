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


class UncheckedExecutionException : public RuntimeException {
public:
    static const long serialVersionUID = 0L;

    protected UncheckedExecutionException() {
   }

    protected UncheckedExecutionException(@Nullable std::string) {
      super(message);
   }

    public UncheckedExecutionException(@Nullable std::string, @Nullable Throwable) {
      super(message, cause);
   }

    public UncheckedExecutionException(@Nullable Throwable) {
      super(cause);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
