package zombie.ai.states;

import zombie.core.math.PZMath.SideOfLine;
import zombie.iso.IsoDirections;

// $VF: synthetic class
class ClimbThroughWindowState$1 {
   static {
      try {
         $SwitchMap$zombie$core$math$PZMath$SideOfLine[SideOfLine.Left.ordinal()] = 1;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$math$PZMath$SideOfLine[SideOfLine.OnLine.ordinal()] = 2;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$math$PZMath$SideOfLine[SideOfLine.Right.ordinal()] = 3;
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
