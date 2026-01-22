#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Verify {
public:
    static void verify(bool expression) {
      if (!expression) {
         throw std::make_unique<VerifyException>();
      }
   }

    static void verify(bool expression, @Nullable std::string, @Nullable Object...) {
      if (!expression) {
         throw VerifyException(Preconditions.format(errorMessageTemplate, errorMessageArgs));
      }
   }

   public static <T> T verifyNotNull(@Nullable T reference) {
    return verifyNotNull("expected a);
   }

   public static <T> T verifyNotNull(@Nullable T reference, @Nullable std::string errorMessageTemplate, @Nullable Object... errorMessageArgs) {
      verify(reference != nullptr, errorMessageTemplate, errorMessageArgs);
    return reference;
   }

    private Verify() {
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
