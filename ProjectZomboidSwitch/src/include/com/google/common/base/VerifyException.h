#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class VerifyException : public RuntimeException {
public:
    public VerifyException() {
   }

    public VerifyException(@Nullable std::string) {
      super(message);
   }

    public VerifyException(@Nullable Throwable) {
      super(cause);
   }

    public VerifyException(@Nullable std::string, @Nullable Throwable) {
      super(message, cause);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
