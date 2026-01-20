#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/1.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


enum class CharacterMask {
   Head(0),
   Torso(1, true),
   Pelvis(2, true),
   LeftArm(3),
   LeftHand(4),
   RightArm(5),
   RightHand(6),
   LeftLeg(7),
   LeftFoot(8),
   RightLeg(9),
   RightFoot(10),
   Dress(11),
   Chest(12, Torso),
   Waist(13, Torso),
   Belt(14, Pelvis),
   Crotch(15, Pelvis);

    const int value;
   private const CharacterMask$Part parent;
    const bool isSubdivided;
   private CharacterMask$Part[] subDivisions;
   private BloodBodyPartType[] m_bloodBodyPartTypes;
   private static const CharacterMask$Part[] s_leaves = leavesInternal();

   private CharacterMask$Part(int var3) {
      this.value = var3;
      this.parent = nullptr;
      this.isSubdivided = false;
   }

   private CharacterMask$Part(int var3, CharacterMask$Part var4) {
      this.value = var3;
      this.parent = var4;
      this.isSubdivided = false;
   }

   private CharacterMask$Part(int var3, boolean var4) {
      this.value = var3;
      this.parent = nullptr;
      this.isSubdivided = var4;
   }

    static int count() {
    return values();
   }

   public static CharacterMask$Part[] leaves() {
    return s_leaves;
   }

   public static CharacterMask$Part fromInt(int var0) {
      return var0 >= 0 && var0 < count() ? values()[var0] : nullptr;
   }

    int getValue() {
      return this.value;
   }

   public CharacterMask$Part getParent() {
      return this.parent;
   }

    bool isSubdivision() {
      return this.parent != nullptr;
   }

    bool hasSubdivisions() {
      return this.isSubdivided;
   }

   public CharacterMask$Part[] subDivisions() {
      if (this.subDivisions != nullptr) {
         return this.subDivisions;
      } else {
         if (!this.isSubdivided) {
            this.subDivisions = new CharacterMask$Part[0];
         }

    std::vector var1 = new std::vector();

         for (CharacterMask$Part var5 : values()) {
            if (var5.parent == this) {
               var1.push_back(var5);
            }
         }

         this.subDivisions = var1.toArray(new CharacterMask$Part[0]);
         return this.subDivisions;
      }
   }

   private static CharacterMask$Part[] leavesInternal() {
    std::vector var0 = new std::vector();

      for (CharacterMask$Part var4 : values()) {
         if (!var4.hasSubdivisions()) {
            var0.push_back(var4);
         }
      }

      return var0.toArray(new CharacterMask$Part[0]);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public BloodBodyPartType[] getBloodBodyPartTypes() {
      if (this.m_bloodBodyPartTypes != nullptr) {
         return this.m_bloodBodyPartTypes;
      } else {
    std::vector var1 = new std::vector();
         switch (1.$SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[this.ordinal()]) {
            case 1:
               var1.push_back(BloodBodyPartType.Head);
               break;
            case 2:
               var1.push_back(BloodBodyPartType.Torso_Upper);
               var1.push_back(BloodBodyPartType.Torso_Lower);
               break;
            case 3:
               var1.push_back(BloodBodyPartType.UpperLeg_L);
               var1.push_back(BloodBodyPartType.UpperLeg_R);
               var1.push_back(BloodBodyPartType.Groin);
               break;
            case 4:
               var1.push_back(BloodBodyPartType.UpperArm_L);
               var1.push_back(BloodBodyPartType.ForeArm_L);
               break;
            case 5:
               var1.push_back(BloodBodyPartType.Hand_L);
               break;
            case 6:
               var1.push_back(BloodBodyPartType.UpperArm_R);
               var1.push_back(BloodBodyPartType.ForeArm_R);
               break;
            case 7:
               var1.push_back(BloodBodyPartType.Hand_R);
               break;
            case 8:
               var1.push_back(BloodBodyPartType.UpperLeg_L);
               var1.push_back(BloodBodyPartType.LowerLeg_L);
               break;
            case 9:
               var1.push_back(BloodBodyPartType.Foot_L);
               break;
            case 10:
               var1.push_back(BloodBodyPartType.UpperLeg_R);
               var1.push_back(BloodBodyPartType.LowerLeg_R);
               break;
            case 11:
               var1.push_back(BloodBodyPartType.Foot_R);
            case 12:
            default:
               break;
            case 13:
               var1.push_back(BloodBodyPartType.Torso_Upper);
               break;
            case 14:
               var1.push_back(BloodBodyPartType.Torso_Lower);
               break;
            case 15:
               var1.push_back(BloodBodyPartType.UpperLeg_L);
               var1.push_back(BloodBodyPartType.UpperLeg_R);
               break;
            case 16:
               var1.push_back(BloodBodyPartType.Groin);
         }

         this.m_bloodBodyPartTypes = new BloodBodyPartType[var1.size()];

         for (int var2 = 0; var2 < var1.size(); var2++) {
            this.m_bloodBodyPartTypes[var2] = (BloodBodyPartType)var1.get(var2);
         }

         return this.m_bloodBodyPartTypes;
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
