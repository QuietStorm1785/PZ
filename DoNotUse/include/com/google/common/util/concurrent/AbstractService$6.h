#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Service/State.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


// $VF: synthetic class
class AbstractService {
public:
   static {
      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.NEW.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.STARTING.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.RUNNING.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.STOPPING.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.TERMINATED.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$google$common$util$concurrent$Service$State[State.FAILED.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
