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


class ExecutionError : public Error {
public:
    static const long serialVersionUID = 0L;

    protected ExecutionError() {
   }

    protected ExecutionError(@Nullable std::string) {
      super(message);
   }

    public ExecutionError(@Nullable std::string, @Nullable Error) {
      super(message, cause);
   }

    public ExecutionError(@Nullable Error) {
      super(cause);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
