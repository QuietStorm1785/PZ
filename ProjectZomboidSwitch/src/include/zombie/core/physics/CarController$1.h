#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/TransmissionNumber.h"

namespace zombie {
namespace core {
namespace physics {


// $VF: synthetic class
class CarController {
public:
   static {
      try {
         $SwitchMap$zombie$vehicles$TransmissionNumber[TransmissionNumber.Speed1.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$vehicles$TransmissionNumber[TransmissionNumber.Speed2.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$vehicles$TransmissionNumber[TransmissionNumber.Speed3.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$vehicles$TransmissionNumber[TransmissionNumber.Speed4.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$vehicles$TransmissionNumber[TransmissionNumber.Speed5.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
