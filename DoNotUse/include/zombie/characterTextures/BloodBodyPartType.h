#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType/1.h"
#include "zombie/core/Translator.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"

namespace zombie {
namespace characterTextures {


enum class BloodBodyPartType {
   Hand_L,
   Hand_R,
   ForeArm_L,
   ForeArm_R,
   UpperArm_L,
   UpperArm_R,
   Torso_Upper,
   Torso_Lower,
   Head,
   Neck,
   Groin,
   UpperLeg_L,
   UpperLeg_R,
   LowerLeg_L,
   LowerLeg_R,
   Foot_L,
   Foot_R,
   Back,
   MAX;

   private Part[] m_characterMaskParts;

    int index() {
    return ToIndex();
   }

    static BloodBodyPartType FromIndex(int var0) {
      switch (var0) {
         case 0:
    return Hand_L;
         case 1:
    return Hand_R;
         case 2:
    return ForeArm_L;
         case 3:
    return ForeArm_R;
         case 4:
    return UpperArm_L;
         case 5:
    return UpperArm_R;
         case 6:
    return Torso_Upper;
         case 7:
    return Torso_Lower;
         case 8:
    return Head;
         case 9:
    return Neck;
         case 10:
    return Groin;
         case 11:
    return UpperLeg_L;
         case 12:
    return UpperLeg_R;
         case 13:
    return LowerLeg_L;
         case 14:
    return LowerLeg_R;
         case 15:
    return Foot_L;
         case 16:
    return Foot_R;
         case 17:
    return Back;
         default:
    return MAX;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int ToIndex(BloodBodyPartType var0) {
      if (var0 == nullptr) {
    return 0;
      } else {
         switch (1.$SwitchMap$zombie$characterTextures$BloodBodyPartType[var0.ordinal()]) {
            case 1:
    return 0;
            case 2:
    return 1;
            case 3:
    return 2;
            case 4:
    return 3;
            case 5:
    return 4;
            case 6:
    return 5;
            case 7:
    return 6;
            case 8:
    return 7;
            case 9:
    return 8;
            case 10:
    return 9;
            case 11:
    return 10;
            case 12:
    return 11;
            case 13:
    return 12;
            case 14:
    return 13;
            case 15:
    return 14;
            case 16:
    return 15;
            case 17:
    return 16;
            case 18:
    return 17;
            case 19:
    return 18;
            default:
    return 17;
         }
      }
   }

    static BloodBodyPartType FromString(const std::string& var0) {
      if (var0 == "Hand_L")) {
    return Hand_L;
      } else if (var0 == "Hand_R")) {
    return Hand_R;
      } else if (var0 == "ForeArm_L")) {
    return ForeArm_L;
      } else if (var0 == "ForeArm_R")) {
    return ForeArm_R;
      } else if (var0 == "UpperArm_L")) {
    return UpperArm_L;
      } else if (var0 == "UpperArm_R")) {
    return UpperArm_R;
      } else if (var0 == "Torso_Upper")) {
    return Torso_Upper;
      } else if (var0 == "Torso_Lower")) {
    return Torso_Lower;
      } else if (var0 == "Head")) {
    return Head;
      } else if (var0 == "Neck")) {
    return Neck;
      } else if (var0 == "Groin")) {
    return Groin;
      } else if (var0 == "UpperLeg_L")) {
    return UpperLeg_L;
      } else if (var0 == "UpperLeg_R")) {
    return UpperLeg_R;
      } else if (var0 == "LowerLeg_L")) {
    return LowerLeg_L;
      } else if (var0 == "LowerLeg_R")) {
    return LowerLeg_R;
      } else if (var0 == "Foot_L")) {
    return Foot_L;
      } else if (var0 == "Foot_R")) {
    return Foot_R;
      } else {
         return var0 == "Back") ? Back : MAX;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public Part[] getCharacterMaskParts() {
      if (this.m_characterMaskParts != nullptr) {
         return this.m_characterMaskParts;
      } else {
    std::vector var1 = new std::vector();
         switch (1.$SwitchMap$zombie$characterTextures$BloodBodyPartType[this.ordinal()]) {
            case 1:
               var1.push_back(Part.LeftHand);
               break;
            case 2:
               var1.push_back(Part.RightHand);
               break;
            case 3:
               var1.push_back(Part.LeftArm);
               break;
            case 4:
               var1.push_back(Part.RightArm);
               break;
            case 5:
               var1.push_back(Part.LeftArm);
               break;
            case 6:
               var1.push_back(Part.RightArm);
               break;
            case 7:
               var1.push_back(Part.Chest);
               break;
            case 8:
               var1.push_back(Part.Waist);
               break;
            case 9:
               var1.push_back(Part.Head);
               break;
            case 10:
               var1.push_back(Part.Head);
               break;
            case 11:
               var1.push_back(Part.Crotch);
               break;
            case 12:
               var1.push_back(Part.LeftLeg);
               var1.push_back(Part.Pelvis);
               break;
            case 13:
               var1.push_back(Part.RightLeg);
               var1.push_back(Part.Pelvis);
               break;
            case 14:
               var1.push_back(Part.LeftLeg);
               break;
            case 15:
               var1.push_back(Part.RightLeg);
               break;
            case 16:
               var1.push_back(Part.LeftFoot);
               break;
            case 17:
               var1.push_back(Part.RightFoot);
               break;
            case 18:
               var1.push_back(Part.Torso);
         }

         this.m_characterMaskParts = new Part[var1.size()];

         for (int var2 = 0; var2 < var1.size(); var2++) {
            this.m_characterMaskParts[var2] = (Part)var1.get(var2);
         }

         return this.m_characterMaskParts;
      }
   }

    std::string getDisplayName() {
    return getDisplayName();
   }

    static std::string getDisplayName(BloodBodyPartType var0) {
      if (var0 == Hand_L) {
         return Translator.getText("IGUI_health_Left_Hand");
      } else if (var0 == Hand_R) {
         return Translator.getText("IGUI_health_Right_Hand");
      } else if (var0 == ForeArm_L) {
         return Translator.getText("IGUI_health_Left_Forearm");
      } else if (var0 == ForeArm_R) {
         return Translator.getText("IGUI_health_Right_Forearm");
      } else if (var0 == UpperArm_L) {
         return Translator.getText("IGUI_health_Left_Upper_Arm");
      } else if (var0 == UpperArm_R) {
         return Translator.getText("IGUI_health_Right_Upper_Arm");
      } else if (var0 == Torso_Upper) {
         return Translator.getText("IGUI_health_Upper_Torso");
      } else if (var0 == Torso_Lower) {
         return Translator.getText("IGUI_health_Lower_Torso");
      } else if (var0 == Head) {
         return Translator.getText("IGUI_health_Head");
      } else if (var0 == Neck) {
         return Translator.getText("IGUI_health_Neck");
      } else if (var0 == Groin) {
         return Translator.getText("IGUI_health_Groin");
      } else if (var0 == UpperLeg_L) {
         return Translator.getText("IGUI_health_Left_Thigh");
      } else if (var0 == UpperLeg_R) {
         return Translator.getText("IGUI_health_Right_Thigh");
      } else if (var0 == LowerLeg_L) {
         return Translator.getText("IGUI_health_Left_Shin");
      } else if (var0 == LowerLeg_R) {
         return Translator.getText("IGUI_health_Right_Shin");
      } else if (var0 == Foot_L) {
         return Translator.getText("IGUI_health_Left_Foot");
      } else if (var0 == Foot_R) {
         return Translator.getText("IGUI_health_Right_Foot");
      } else {
    return var0 = = Back ? Translator.getText("IGUI_health_Back") : Translator.getText("IGUI_health_Unknown_Body_Part");
      }
   }
}
} // namespace characterTextures
} // namespace zombie
