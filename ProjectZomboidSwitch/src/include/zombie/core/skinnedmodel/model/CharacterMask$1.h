#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


// $VF: synthetic class
class CharacterMask {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Head.ordinal()] = 1;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Torso.ordinal()] = 2;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Pelvis.ordinal()] = 3;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.LeftArm.ordinal()] = 4;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.LeftHand.ordinal()] = 5;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.RightArm.ordinal()] = 6;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.RightHand.ordinal()] = 7;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.LeftLeg.ordinal()] = 8;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.LeftFoot.ordinal()] = 9;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.RightLeg.ordinal()] = 10;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.RightFoot.ordinal()] = 11;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Dress.ordinal()] = 12;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Chest.ordinal()] = 13;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Waist.ordinal()] = 14;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Belt.ordinal()] = 15;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[Part.Crotch.ordinal()] = 16;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
