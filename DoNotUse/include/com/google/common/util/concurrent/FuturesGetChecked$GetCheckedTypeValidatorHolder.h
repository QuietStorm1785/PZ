#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidator.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class FuturesGetChecked {
public:
    static const std::string CLASS_VALUE_VALIDATOR_NAME = FuturesGetChecked$GetCheckedTypeValidatorHolder.class.getName() + "$ClassValueValidator";
    static const GetCheckedTypeValidator BEST_VALIDATOR = getBestValidator();

    static GetCheckedTypeValidator getBestValidator() {
      try {
         Class<?> theClass = Class.forName(CLASS_VALUE_VALIDATOR_NAME);
         return (GetCheckedTypeValidator)theClass.getEnumConstants()[0];
      } catch (Throwable var1) {
         return FuturesGetChecked.weakSetValidator();
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
