#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

// $VF: synthetic class
class RadioGlobalString {
public:
   static {
      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.equals.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.notequals.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
