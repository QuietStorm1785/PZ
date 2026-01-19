package zombie.characters.BodyDamage;

import zombie.characters.BodyDamage.Thermoregulator.Multiplier;
import zombie.inventory.types.WeaponType;

// $VF: synthetic class
class Thermoregulator$1 {
   static {
      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.barehand.ordinal()] = 1;
      } catch (NoSuchFieldError var38) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.twohanded.ordinal()] = 2;
      } catch (NoSuchFieldError var37) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.onehanded.ordinal()] = 3;
      } catch (NoSuchFieldError var36) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.heavy.ordinal()] = 4;
      } catch (NoSuchFieldError var35) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.knife.ordinal()] = 5;
      } catch (NoSuchFieldError var34) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.spear.ordinal()] = 6;
      } catch (NoSuchFieldError var33) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.handgun.ordinal()] = 7;
      } catch (NoSuchFieldError var32) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.firearm.ordinal()] = 8;
      } catch (NoSuchFieldError var31) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.throwing.ordinal()] = 9;
      } catch (NoSuchFieldError var30) {
      }

      try {
         $SwitchMap$zombie$inventory$types$WeaponType[WeaponType.chainsaw.ordinal()] = 10;
      } catch (NoSuchFieldError var29) {
      }

      $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier = new int[Multiplier.values().length];

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.MetabolicRateInc.ordinal()] = 1;
      } catch (NoSuchFieldError var28) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.MetabolicRateDec.ordinal()] = 2;
      } catch (NoSuchFieldError var27) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.BodyHeat.ordinal()] = 3;
      } catch (NoSuchFieldError var26) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.CoreHeatExpand.ordinal()] = 4;
      } catch (NoSuchFieldError var25) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.CoreHeatContract.ordinal()] = 5;
      } catch (NoSuchFieldError var24) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.SkinCelcius.ordinal()] = 6;
      } catch (NoSuchFieldError var23) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.SkinCelciusExpand.ordinal()] = 7;
      } catch (NoSuchFieldError var22) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.SkinCelciusContract.ordinal()] = 8;
      } catch (NoSuchFieldError var21) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.PrimaryDelta.ordinal()] = 9;
      } catch (NoSuchFieldError var20) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.SecondaryDelta.ordinal()] = 10;
      } catch (NoSuchFieldError var19) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[Multiplier.Default.ordinal()] = 11;
      } catch (NoSuchFieldError var18) {
      }

      $SwitchMap$zombie$characters$BodyDamage$BodyPartType = new int[BodyPartType.values().length];

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Torso_Upper.ordinal()] = 1;
      } catch (NoSuchFieldError var17) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Head.ordinal()] = 2;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Neck.ordinal()] = 3;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Torso_Lower.ordinal()] = 4;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Groin.ordinal()] = 5;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperLeg_L.ordinal()] = 6;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperLeg_R.ordinal()] = 7;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.LowerLeg_L.ordinal()] = 8;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.LowerLeg_R.ordinal()] = 9;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Foot_L.ordinal()] = 10;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Foot_R.ordinal()] = 11;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperArm_L.ordinal()] = 12;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperArm_R.ordinal()] = 13;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.ForeArm_L.ordinal()] = 14;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.ForeArm_R.ordinal()] = 15;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Hand_L.ordinal()] = 16;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Hand_R.ordinal()] = 17;
      } catch (NoSuchFieldError var1) {
      }
   }
}
