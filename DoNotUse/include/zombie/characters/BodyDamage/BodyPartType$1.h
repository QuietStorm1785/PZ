#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace BodyDamage {

// $VF: synthetic class
class BodyPartType {
public:
   static {
      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Hand_L.ordinal()] = 1;
      } catch (NoSuchFieldError var18) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Hand_R.ordinal()] = 2;
      } catch (NoSuchFieldError var17) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.ForeArm_L.ordinal()] = 3;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.ForeArm_R.ordinal()] = 4;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperArm_L.ordinal()] = 5;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperArm_R.ordinal()] = 6;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Torso_Upper.ordinal()] = 7;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Torso_Lower.ordinal()] = 8;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Head.ordinal()] = 9;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Neck.ordinal()] = 10;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Groin.ordinal()] = 11;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperLeg_L.ordinal()] = 12;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.UpperLeg_R.ordinal()] = 13;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.LowerLeg_L.ordinal()] = 14;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.LowerLeg_R.ordinal()] = 15;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Foot_L.ordinal()] = 16;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.Foot_R.ordinal()] = 17;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$BodyDamage$BodyPartType[BodyPartType.MAX.ordinal()] = 18;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
