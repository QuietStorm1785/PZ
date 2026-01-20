#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidator.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidatorHolder/ClassValueValidator/1.h"
#include "org/codehaus/mojo/animal_sniffer/IgnoreJRERequirement.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


enum class FuturesGetChecked {
   INSTANCE;

   private static const ClassValue<bool> isValidClass = std::make_unique<1>();

    void validateClass(Class<? extends) {
      isValidClass.get(exceptionClass);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
