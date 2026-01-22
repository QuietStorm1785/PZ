#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/RadioGlobalType.h"

namespace zombie {
namespace radio {


// $VF: synthetic class
class RadioXmlReader {
public:
   static {
      try {
         $SwitchMap$zombie$radio$globals$RadioGlobalType[RadioGlobalType.std::string.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$radio$globals$RadioGlobalType[RadioGlobalType.int.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$radio$globals$RadioGlobalType[RadioGlobalType.float.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$radio$globals$RadioGlobalType[RadioGlobalType.bool.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace radio
} // namespace zombie
