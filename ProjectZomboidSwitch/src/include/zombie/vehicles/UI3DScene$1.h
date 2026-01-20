#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/GridPlane.h"
#include "zombie/vehicles/UI3DScene/View.h"

namespace zombie {
namespace vehicles {


// $VF: synthetic class
class UI3DScene {
public:
   static {
      try {
         $SwitchMap$zombie$vehicles$UI3DScene$Axis[Axis.X.ordinal()] = 1;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$Axis[Axis.Y.ordinal()] = 2;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$Axis[Axis.Z.ordinal()] = 3;
      } catch (NoSuchFieldError var11) {
      }

      $SwitchMap$zombie$vehicles$UI3DScene$View = new int[View.values().length];

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Left.ordinal()] = 1;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Right.ordinal()] = 2;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Top.ordinal()] = 3;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Bottom.ordinal()] = 4;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Front.ordinal()] = 5;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.Back.ordinal()] = 6;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$View[View.UserDefined.ordinal()] = 7;
      } catch (NoSuchFieldError var4) {
      }

      $SwitchMap$zombie$vehicles$UI3DScene$GridPlane = new int[GridPlane.values().length];

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$GridPlane[GridPlane.XY.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$GridPlane[GridPlane.XZ.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$vehicles$UI3DScene$GridPlane[GridPlane.YZ.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace vehicles
} // namespace zombie
