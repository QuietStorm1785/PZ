#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"
#include "zombie/vehicles/BaseVehicle/Authorization.h"

namespace zombie {
namespace vehicles {


// $VF: synthetic class
class BaseVehicle {
public:
   static {
      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.E.ordinal()] = 1;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.W.ordinal()] = 2;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.N.ordinal()] = 3;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.S.ordinal()] = 4;
      } catch (NoSuchFieldError var6) {
      }

      $SwitchMap$zombie$vehicles$BaseVehicle$Authorization = new int[Authorization.values().length];

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$Authorization[Authorization.Server.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$Authorization[Authorization.LocalCollide.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$Authorization[Authorization.Local.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$Authorization[Authorization.Remote.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$Authorization[Authorization.RemoteCollide.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace vehicles
} // namespace zombie
