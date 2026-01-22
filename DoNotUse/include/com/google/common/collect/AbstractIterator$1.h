#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractIterator/State.h"

namespace com {
namespace google {
namespace common {
namespace collect {


// $VF: synthetic class
class AbstractIterator {
public:
   static {
      try {
         $SwitchMap$com$google$common$collect$AbstractIterator$State[State.DONE.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$google$common$collect$AbstractIterator$State[State.READY.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
