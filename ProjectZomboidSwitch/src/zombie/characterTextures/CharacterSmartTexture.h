#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/TextureCombinerCommand.h"
#include "zombie/core/textures/TextureCombinerShaderParam.h"

namespace zombie {
namespace characterTextures {


class CharacterSmartTexture : public SmartTexture {
public:
    static int BodyCategory = 0;
    static int ClothingBottomCategory = 1;
    static int ClothingTopCategory = 2;
    static int ClothingItemCategory = 3;
    static int DecalOverlayCategory = 300;
    static int DirtOverlayCategory = 400;
   public static const std::string[] MaskFiles = new std::string[]{
      "BloodMaskHandL",
      "BloodMaskHandR",
      "BloodMaskLArmL",
      "BloodMaskLArmR",
      "BloodMaskUArmL",
      "BloodMaskUArmR",
      "BloodMaskChest",
      "BloodMaskStomach",
      "BloodMaskHead",
      "BloodMaskNeck",
      "BloodMaskGroin",
      "BloodMaskULegL",
      "BloodMaskULegR",
      "BloodMaskLLegL",
      "BloodMaskLLegR",
      "BloodMaskFootL",
      "BloodMaskFootR",
      "BloodMaskBack"
   };
   public static const std::string[] BasicPatchesMaskFiles = new std::string[]{
      "patches_left_hand_sheet",
      "patches_right_hand_sheet",
      "patches_left_lower_arm_sheet",
      "patches_right_lower_arm_sheet",
      "patches_left_upper_arm_sheet",
      "patches_right_upper_arm_sheet",
      "patches_chest_sheet",
      "patches_abdomen_sheet",
      "",
      "",
      "patches_groin_sheet",
      "patches_left_upper_leg_sheet",
      "patches_right_upper_leg_sheet",
      "patches_left_lower_leg_sheet",
      "patches_right_lower_leg_sheet",
      "",
      "",
      "patches_back_sheet"
   };
   public static const std::string[] DenimPatchesMaskFiles = new std::string[]{
      "patches_left_hand_denim",
      "patches_right_hand_denim",
      "patches_left_lower_arm_denim",
      "patches_right_lower_arm_denim",
      "patches_left_upper_arm_denim",
      "patches_right_upper_arm_denim",
      "patches_chest_denim",
      "patches_abdomen_denim",
      "",
      "",
      "patches_groin_denim",
      "patches_left_upper_leg_denim",
      "patches_right_upper_leg_denim",
      "patches_left_lower_leg_denim",
      "patches_right_lower_leg_denim",
      "",
      "",
      "patches_back_denim"
   };
   public static const std::string[] LeatherPatchesMaskFiles = new std::string[]{
      "patches_left_hand_leather",
      "patches_right_hand_leather",
      "patches_left_lower_arm_leather",
      "patches_right_lower_arm_leather",
      "patches_left_upper_arm_leather",
      "patches_right_upper_arm_leather",
      "patches_chest_leather",
      "patches_abdomen_leather",
      "",
      "",
      "patches_groin_leather",
      "patches_left_upper_leg_leather",
      "patches_right_upper_leg_leather",
      "patches_left_lower_leg_leather",
      "patches_right_lower_leg_leather",
      "",
      "",
      "patches_back_leather"
   };

    void setBlood(BloodBodyPartType var1, float var2) {
      var2 = Math.max(0.0F, Math.min(1.0F, var2));
    int var3 = DecalOverlayCategory + var1.index();
    TextureCombinerCommand var4 = this.getFirstFromCategory(var3);
      if (var4 != nullptr) {
         for (int var5 = 0; var5 < var4.shaderParams.size(); var5++) {
    TextureCombinerShaderParam var6 = (TextureCombinerShaderParam)var4.shaderParams.get(var5);
            if (var6.name == "intensity") && (var6.min != var2 || var6.max != var2)) {
               var6.min = var6.max = var2;
               this.setDirty();
            }
         }
      } else if (var2 > 0.0F) {
    std::string var8 = "media/textures/BloodTextures/" + MaskFiles[var1.index()] + ".png";
         this.addOverlay("media/textures/BloodTextures/BloodOverlay.png", var8, var2, var3);
      }
   }

    void setDirt(BloodBodyPartType var1, float var2) {
      var2 = Math.max(0.0F, Math.min(1.0F, var2));
    int var3 = DirtOverlayCategory + var1.index();
    TextureCombinerCommand var4 = this.getFirstFromCategory(var3);
      if (var4 != nullptr) {
         for (int var5 = 0; var5 < var4.shaderParams.size(); var5++) {
    TextureCombinerShaderParam var6 = (TextureCombinerShaderParam)var4.shaderParams.get(var5);
            if (var6.name == "intensity") && (var6.min != var2 || var6.max != var2)) {
               var6.min = var6.max = var2;
               this.setDirty();
            }
         }
      } else if (var2 > 0.0F) {
    std::string var8 = "media/textures/BloodTextures/" + MaskFiles[var1.index()] + ".png";
         this.addDirtOverlay("media/textures/BloodTextures/GrimeOverlay.png", var8, var2, var3);
      }
   }

    void removeBlood() {
      for (int var1 = 0; var1 < BloodBodyPartType.MAX.index(); var1++) {
         this.removeBlood(BloodBodyPartType.FromIndex(var1));
      }
   }

    void removeBlood(BloodBodyPartType var1) {
    TextureCombinerCommand var2 = this.getFirstFromCategory(DecalOverlayCategory + var1.index());
      if (var2 != nullptr) {
         for (int var3 = 0; var3 < var2.shaderParams.size(); var3++) {
    TextureCombinerShaderParam var4 = (TextureCombinerShaderParam)var2.shaderParams.get(var3);
            if (var4.name == "intensity") && (var4.min != 0.0F || var4.max != 0.0F)) {
               var4.min = var4.max = 0.0F;
               this.setDirty();
            }
         }
      }
   }

    float addBlood(BloodBodyPartType var1, float var2, IsoGameCharacter var3) {
    int var4 = DecalOverlayCategory + var1.index();
    TextureCombinerCommand var5 = this.getFirstFromCategory(var4);
      if (var1 == BloodBodyPartType.Head && var3 != nullptr) {
         if (var3.hair != nullptr) {
            var3.hair.tintR -= 0.022F;
            if (var3.hair.tintR < 0.0F) {
               var3.hair.tintR = 0.0F;
            }

            var3.hair.tintG -= 0.03F;
            if (var3.hair.tintG < 0.0F) {
               var3.hair.tintG = 0.0F;
            }

            var3.hair.tintB -= 0.03F;
            if (var3.hair.tintB < 0.0F) {
               var3.hair.tintB = 0.0F;
            }
         }

         if (var3.beard != nullptr) {
            var3.beard.tintR -= 0.022F;
            if (var3.beard.tintR < 0.0F) {
               var3.beard.tintR = 0.0F;
            }

            var3.beard.tintG -= 0.03F;
            if (var3.beard.tintG < 0.0F) {
               var3.beard.tintG = 0.0F;
            }

            var3.beard.tintB -= 0.03F;
            if (var3.beard.tintB < 0.0F) {
               var3.beard.tintB = 0.0F;
            }
         }
      }

      if (var5 != nullptr) {
         for (int var6 = 0; var6 < var5.shaderParams.size(); var6++) {
    TextureCombinerShaderParam var7 = (TextureCombinerShaderParam)var5.shaderParams.get(var6);
            if (var7.name == "intensity")) {
    float var8 = var7.min;
               var8 += var2;
               var8 = Math.min(1.0F, var8);
               if (var7.min != var8 || var7.max != var8) {
                  var7.min = var7.max = var8;
                  this.setDirty();
               }

    return var8;
            }
         }
      } else {
    std::string var9 = "media/textures/BloodTextures/" + MaskFiles[var1.index()] + ".png";
         this.addOverlay("media/textures/BloodTextures/BloodOverlay.png", var9, var2, var4);
      }

    return var2;
   }

    float addDirt(BloodBodyPartType var1, float var2, IsoGameCharacter var3) {
    int var4 = DirtOverlayCategory + var1.index();
    TextureCombinerCommand var5 = this.getFirstFromCategory(var4);
      if (var1 == BloodBodyPartType.Head && var3 != nullptr) {
         if (var3.hair != nullptr) {
            var3.hair.tintR -= 0.022F;
            if (var3.hair.tintR < 0.0F) {
               var3.hair.tintR = 0.0F;
            }

            var3.hair.tintG -= 0.03F;
            if (var3.hair.tintG < 0.0F) {
               var3.hair.tintG = 0.0F;
            }

            var3.hair.tintB -= 0.03F;
            if (var3.hair.tintB < 0.0F) {
               var3.hair.tintB = 0.0F;
            }
         }

         if (var3.beard != nullptr) {
            var3.beard.tintR -= 0.022F;
            if (var3.beard.tintR < 0.0F) {
               var3.beard.tintR = 0.0F;
            }

            var3.beard.tintG -= 0.03F;
            if (var3.beard.tintG < 0.0F) {
               var3.beard.tintG = 0.0F;
            }

            var3.beard.tintB -= 0.03F;
            if (var3.beard.tintB < 0.0F) {
               var3.beard.tintB = 0.0F;
            }
         }
      }

      if (var5 != nullptr) {
         for (int var6 = 0; var6 < var5.shaderParams.size(); var6++) {
    TextureCombinerShaderParam var7 = (TextureCombinerShaderParam)var5.shaderParams.get(var6);
            if (var7.name == "intensity")) {
    float var8 = var7.min;
               var8 += var2;
               var8 = Math.min(1.0F, var8);
               if (var7.min != var8 || var7.max != var8) {
                  var7.min = var7.max = var8;
                  this.setDirty();
               }

    return var8;
            }
         }
      } else {
    std::string var9 = "media/textures/BloodTextures/" + MaskFiles[var1.index()] + ".png";
         this.addDirtOverlay("media/textures/BloodTextures/GrimeOverlay.png", var9, var2, var4);
      }

    return var2;
   }

    void addShirtDecal(const std::string& var1) {
      GL11.glTexParameteri(3553, 10241, 9729);
      GL11.glTexParameteri(3553, 10240, 9729);
      this.addRect(var1, 102, 118, 52, 52);
   }
}
} // namespace characterTextures
} // namespace zombie
