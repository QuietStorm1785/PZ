package zombie.iso.objects;

import zombie.iso.IsoDirections;
import zombie.iso.objects.IsoDoor.DoorType;

// $VF: synthetic class
class IsoDoor$1 {
   static {
      try {
         $SwitchMap$zombie$iso$objects$IsoDoor$DoorType[DoorType.WeakWooden.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$iso$objects$IsoDoor$DoorType[DoorType.StrongWooden.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      $SwitchMap$zombie$iso$IsoDirections = new int[IsoDirections.values().length];

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.N.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.S.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.W.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.E.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
