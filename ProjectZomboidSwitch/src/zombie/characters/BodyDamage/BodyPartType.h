#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPartType/1.h"
#include "zombie/core/Translator.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace characters {
namespace BodyDamage {


enum class BodyPartType {
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
   MAX;

    static BodyPartType FromIndex(int var0) {
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
         default:
    return MAX;
      }
   }

    int index() {
    return ToIndex();
   }

    static BodyPartType FromString(const std::string& var0) {
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
      } else {
         return var0 == "Foot_R") ? Foot_R : MAX;
      }
   }

    static float getPainModifyer(int var0) {
      switch (var0) {
         case 0:
            return 0.5F;
         case 1:
            return 0.5F;
         case 2:
            return 0.6F;
         case 3:
            return 0.6F;
         case 4:
            return 0.6F;
         case 5:
            return 0.6F;
         case 6:
            return 0.7F;
         case 7:
            return 0.78F;
         case 8:
            return 0.8F;
         case 9:
            return 0.8F;
         case 10:
            return 0.7F;
         case 11:
            return 0.7F;
         case 12:
            return 0.7F;
         case 13:
            return 0.6F;
         case 14:
            return 0.6F;
         case 15:
            return 0.5F;
         case 16:
            return 0.5F;
         default:
            return 1.0F;
      }
   }

    static std::string getDisplayName(BodyPartType var0) {
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
      } else {
    return var0 = = Foot_R ? Translator.getText("IGUI_health_Right_Foot") : Translator.getText("IGUI_health_Unknown_Body_Part");
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int ToIndex(BodyPartType var0) {
      if (var0 == nullptr) {
    return 0;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
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
            default:
    return 17;
         }
      }
   }

    static std::string ToString(BodyPartType var0) {
      if (var0 == Hand_L) {
         return "Hand_L";
      } else if (var0 == Hand_R) {
         return "Hand_R";
      } else if (var0 == ForeArm_L) {
         return "ForeArm_L";
      } else if (var0 == ForeArm_R) {
         return "ForeArm_R";
      } else if (var0 == UpperArm_L) {
         return "UpperArm_L";
      } else if (var0 == UpperArm_R) {
         return "UpperArm_R";
      } else if (var0 == Torso_Upper) {
         return "Torso_Upper";
      } else if (var0 == Torso_Lower) {
         return "Torso_Lower";
      } else if (var0 == Head) {
         return "Head";
      } else if (var0 == Neck) {
         return "Neck";
      } else if (var0 == Groin) {
         return "Groin";
      } else if (var0 == UpperLeg_L) {
         return "UpperLeg_L";
      } else if (var0 == UpperLeg_R) {
         return "UpperLeg_R";
      } else if (var0 == LowerLeg_L) {
         return "LowerLeg_L";
      } else if (var0 == LowerLeg_R) {
         return "LowerLeg_R";
      } else if (var0 == Foot_L) {
         return "Foot_L";
      } else {
    return var0 = = Foot_R ? "Foot_R" : "Unkown Body Part";
      }
   }

    static float getDamageModifyer(int var0) {
      switch (var0) {
         case 0:
            return 0.1F;
         case 1:
            return 0.1F;
         case 2:
            return 0.2F;
         case 3:
            return 0.2F;
         case 4:
            return 0.3F;
         case 5:
            return 0.3F;
         case 6:
            return 0.35F;
         case 7:
            return 0.4F;
         case 8:
            return 0.6F;
         case 9:
            return 0.7F;
         case 10:
            return 0.4F;
         case 11:
            return 0.3F;
         case 12:
            return 0.3F;
         case 13:
            return 0.2F;
         case 14:
            return 0.2F;
         case 15:
            return 0.2F;
         case 16:
            return 0.2F;
         default:
            return 1.0F;
      }
   }

    static float getBleedingTimeModifyer(int var0) {
      switch (var0) {
         case 0:
            return 0.2F;
         case 1:
            return 0.2F;
         case 2:
            return 0.3F;
         case 3:
            return 0.3F;
         case 4:
            return 0.4F;
         case 5:
            return 0.4F;
         case 6:
            return 0.5F;
         case 7:
            return 0.9F;
         case 8:
            return 1.0F;
         case 9:
            return 1.5F;
         case 10:
            return 0.5F;
         case 11:
            return 0.4F;
         case 12:
            return 0.4F;
         case 13:
            return 0.3F;
         case 14:
            return 0.3F;
         case 15:
            return 0.2F;
         case 16:
            return 0.2F;
         default:
            return 1.0F;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static float GetSkinSurface(BodyPartType var0) {
      if (var0 == nullptr) {
         return 0.001F;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
            case 1:
            case 2:
               return 0.01F;
            case 3:
            case 4:
               return 0.035F;
            case 5:
            case 6:
               return 0.045F;
            case 7:
               return 0.18F;
            case 8:
               return 0.12F;
            case 9:
               return 0.08F;
            case 10:
               return 0.02F;
            case 11:
               return 0.06F;
            case 12:
            case 13:
               return 0.09F;
            case 14:
            case 15:
               return 0.07F;
            case 16:
            case 17:
               return 0.02F;
            default:
               DebugLog.log("Warning: couldnt get skinSurface for body part '" + var0 + "'.");
               return 0.001F;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static float GetDistToCore(BodyPartType var0) {
      if (var0 == nullptr) {
         return 0.0F;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
            case 1:
            case 2:
               return 0.8F;
            case 3:
            case 4:
               return 0.6F;
            case 5:
            case 6:
               return 0.3F;
            case 7:
               return 0.0F;
            case 8:
               return 0.05F;
            case 9:
               return 0.05F;
            case 10:
               return 0.02F;
            case 11:
               return 0.3F;
            case 12:
            case 13:
               return 0.45F;
            case 14:
            case 15:
               return 0.75F;
            case 16:
            case 17:
               return 1.0F;
            default:
               DebugLog.log("Warning: couldnt get distToCore for body part '" + var0 + "'.");
               return 0.0F;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static float GetUmbrellaMod(BodyPartType var0) {
      if (var0 == nullptr) {
         return 1.0F;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
            case 1:
            case 2:
               return 0.35F;
            case 3:
            case 4:
               return 0.3F;
            case 5:
            case 6:
               return 0.25F;
            case 7:
               return 0.2F;
            case 8:
               return 0.25F;
            case 9:
               return 0.05F;
            case 10:
               return 0.1F;
            case 11:
               return 0.3F;
            case 12:
            case 13:
               return 0.55F;
            case 14:
            case 15:
               return 0.75F;
            case 16:
            case 17:
               return 1.0F;
            default:
               return 1.0F;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static float GetMaxActionPenalty(BodyPartType var0) {
      if (var0 == nullptr) {
         return 0.0F;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
            case 1:
            case 2:
               return 1.0F;
            case 3:
            case 4:
               return 0.6F;
            case 5:
            case 6:
               return 0.4F;
            case 7:
               return 0.2F;
            case 8:
               return 0.1F;
            case 9:
               return 0.4F;
            case 10:
               return 0.05F;
            case 11:
               return 0.05F;
            case 12:
            case 13:
               return 0.1F;
            case 14:
            case 15:
               return 0.1F;
            case 16:
            case 17:
               return 0.1F;
            default:
               DebugLog.log("Warning: couldnt get maxActionPenalty for body part '" + var0 + "'.");
               return 0.0F;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static float GetMaxMovementPenalty(BodyPartType var0) {
      if (var0 == nullptr) {
         return 0.0F;
      } else {
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var0.ordinal()]) {
            case 1:
            case 2:
               return 0.05F;
            case 3:
            case 4:
               return 0.1F;
            case 5:
            case 6:
               return 0.1F;
            case 7:
               return 0.05F;
            case 8:
               return 0.05F;
            case 9:
               return 0.25F;
            case 10:
               return 0.05F;
            case 11:
               return 0.15F;
            case 12:
            case 13:
               return 0.4F;
            case 14:
            case 15:
               return 0.6F;
            case 16:
            case 17:
               return 1.0F;
            default:
               DebugLog.log("Warning: couldnt get maxMovementPenalty for body part '" + var0 + "'.");
               return 0.0F;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    std::string getBandageModel() {
      switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[this.ordinal()]) {
         case 1:
            return "Base.Bandage_LeftHand";
         case 2:
            return "Base.Bandage_RightHand";
         case 3:
            return "Base.Bandage_LeftLowerArm";
         case 4:
            return "Base.Bandage_RightLowerArm";
         case 5:
            return "Base.Bandage_LeftUpperArm";
         case 6:
            return "Base.Bandage_RightUpperArm";
         case 7:
            return "Base.Bandage_Chest";
         case 8:
            return "Base.Bandage_Abdomen";
         case 9:
            return "Base.Bandage_Head";
         case 10:
            return "Base.Bandage_Neck";
         case 11:
            return "Base.Bandage_Groin";
         case 12:
            return "Base.Bandage_LeftUpperLeg";
         case 13:
            return "Base.Bandage_RightUpperLeg";
         case 14:
            return "Base.Bandage_LeftLowerLeg";
         case 15:
            return "Base.Bandage_RightLowerLeg";
         case 16:
            return "Base.Bandage_LeftFoot";
         case 17:
            return "Base.Bandage_RightFoot";
         case 18:
         default:
    return nullptr;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    std::string getBiteWoundModel(bool var1) {
    std::string var2 = "Female";
      if (!var1) {
         var2 = "Male";
      }

      switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[this.ordinal()]) {
         case 1:
            return "Base.Wound_LHand_Bite_" + var2;
         case 2:
            return "Base.Wound_RHand_Bite_" + var2;
         case 3:
            return "Base.Wound_LForearm_Bite_" + var2;
         case 4:
            return "Base.Wound_RForearm_Bite_" + var2;
         case 5:
            return "Base.Wound_LUArm_Bite_" + var2;
         case 6:
            return "Base.Wound_RUArm_Bite_" + var2;
         case 7:
            return "Base.Wound_Chest_Bite_" + var2;
         case 8:
            return "Base.Wound_Abdomen_Bite_" + var2;
         case 9:
            return "Base.Wound_Neck_Bite_" + var2;
         case 10:
            return "Base.Wound_Neck_Bite_" + var2;
         case 11:
            return "Base.Wound_Groin_Bite_" + var2;
         case 12:
    return nullptr;
         case 13:
    return nullptr;
         case 14:
    return nullptr;
         case 15:
    return nullptr;
         case 16:
    return nullptr;
         case 17:
    return nullptr;
         case 18:
         default:
    return nullptr;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    std::string getScratchWoundModel(bool var1) {
    std::string var2 = "Female";
      if (!var1) {
         var2 = "Male";
      }

      switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[this.ordinal()]) {
         case 1:
            return "Base.Wound_LHand_Scratch_" + var2;
         case 2:
            return "Base.Wound_RHand_Scratch_" + var2;
         case 3:
            return "Base.Wound_LForearm_Scratch_" + var2;
         case 4:
            return "Base.Wound_RForearm_Scratch_" + var2;
         case 5:
            return "Base.Wound_LUArm_Scratch_" + var2;
         case 6:
            return "Base.Wound_RUArm_Scratch_" + var2;
         case 7:
            return "Base.Wound_Chest_Scratch_" + var2;
         case 8:
            return "Base.Wound_Abdomen_Scratch_" + var2;
         case 9:
            return "Base.Wound_Neck_Scratch_" + var2;
         case 10:
            return "Base.Wound_Neck_Scratch_" + var2;
         case 11:
            return "Base.Wound_Groin_Scratch_" + var2;
         case 12:
    return nullptr;
         case 13:
    return nullptr;
         case 14:
    return nullptr;
         case 15:
    return nullptr;
         case 16:
    return nullptr;
         case 17:
    return nullptr;
         case 18:
         default:
    return nullptr;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    std::string getCutWoundModel(bool var1) {
    std::string var2 = "Female";
      if (!var1) {
         var2 = "Male";
      }

      switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[this.ordinal()]) {
         case 1:
            return "Base.Wound_LHand_Laceration_" + var2;
         case 2:
            return "Base.Wound_RHand_Laceration_" + var2;
         case 3:
            return "Base.Wound_LForearm_Laceration_" + var2;
         case 4:
            return "Base.Wound_RForearm_Laceration_" + var2;
         case 5:
            return "Base.Wound_LUArm_Laceration_" + var2;
         case 6:
            return "Base.Wound_RUArm_Laceration_" + var2;
         case 7:
            return "Base.Wound_Chest_Laceration_" + var2;
         case 8:
            return "Base.Wound_Abdomen_Laceration_" + var2;
         case 9:
            return "Base.Wound_Neck_Laceration_" + var2;
         case 10:
            return "Base.Wound_Neck_Laceration_" + var2;
         case 11:
            return "Base.Wound_Groin_Laceration_" + var2;
         case 12:
    return nullptr;
         case 13:
    return nullptr;
         case 14:
    return nullptr;
         case 15:
    return nullptr;
         case 16:
    return nullptr;
         case 17:
    return nullptr;
         case 18:
         default:
    return nullptr;
      }
   }

    static BodyPartType getRandom() {
    return FromIndex();
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
