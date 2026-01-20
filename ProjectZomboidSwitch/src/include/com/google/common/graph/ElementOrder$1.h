#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/graph/ElementOrder/Type.h"

namespace com {
namespace google {
namespace common {
namespace graph {


// $VF: synthetic class
class ElementOrder {
public:
   static {
      try {
         $SwitchMap$com$google$common$graph$ElementOrder$Type[Type.UNORDERED.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$google$common$graph$ElementOrder$Type[Type.INSERTION.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$google$common$graph$ElementOrder$Type[Type.SORTED.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
