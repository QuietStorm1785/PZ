#pragma once
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/TextureCombinerCommand.h"
#include "zombie/core/textures/TextureCombinerShaderParam.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characterTextures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMY on 6/30/2016.
 */
class CharacterSmartTexture : public SmartTexture {
public:
  static int BodyCategory = 0;
  static int ClothingBottomCategory = 1;
  static int ClothingTopCategory = 2;
  static int ClothingItemCategory = 3;
  static int DecalOverlayCategory = 300;
  static int DirtOverlayCategory = 400;
public
  static final String[] MaskFiles = new String[]{
      "BloodMaskHandL", "BloodMaskHandR", "BloodMaskLArmL", "BloodMaskLArmR",
      "BloodMaskUArmL", "BloodMaskUArmR", "BloodMaskChest", "BloodMaskStomach",
      "BloodMaskHead",  "BloodMaskNeck",  "BloodMaskGroin", "BloodMaskULegL",
      "BloodMaskULegR", "BloodMaskLLegL", "BloodMaskLLegR", "BloodMaskFootL",
      "BloodMaskFootR", "BloodMaskBack"};
public
  static final String[] BasicPatchesMaskFiles =
      new String[]{"patches_left_hand_sheet",
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
                   "patches_back_sheet"};
public
  static final String[] DenimPatchesMaskFiles =
      new String[]{"patches_left_hand_denim",
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
                   "patches_back_denim"};
public
  static final String[] LeatherPatchesMaskFiles =
      new String[]{"patches_left_hand_leather",
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
                   "patches_back_leather"};

  void setBlood(BloodBodyPartType bodyPart, float intensity) {
    intensity = Math.max(0.0F, Math.min(1.0F, intensity));
    int int0 = DecalOverlayCategory + bodyPart.index();
    TextureCombinerCommand textureCombinerCommand =
        this.getFirstFromCategory(int0);
    if (textureCombinerCommand != nullptr) {
      for (int int1 = 0; int1 < textureCombinerCommand.shaderParams.size();
           int1++) {
        TextureCombinerShaderParam textureCombinerShaderParam =
            textureCombinerCommand.shaderParams.get(int1);
        if (textureCombinerShaderParam.name == "intensity")
                    && (textureCombinerShaderParam.min != intensity || textureCombinerShaderParam.max != intensity)) {
                      textureCombinerShaderParam.min =
                          textureCombinerShaderParam.max = intensity;
                      this.setDirty();
                    }
      }
    } else if (intensity > 0.0F) {
      std::string string = "media/textures/BloodTextures/" +
                           MaskFiles[bodyPart.index()] + ".png";
      this.addOverlay("media/textures/BloodTextures/BloodOverlay.png", string,
                      intensity, int0);
    }
  }

  void setDirt(BloodBodyPartType bodyPart, float intensity) {
    intensity = Math.max(0.0F, Math.min(1.0F, intensity));
    int int0 = DirtOverlayCategory + bodyPart.index();
    TextureCombinerCommand textureCombinerCommand =
        this.getFirstFromCategory(int0);
    if (textureCombinerCommand != nullptr) {
      for (int int1 = 0; int1 < textureCombinerCommand.shaderParams.size();
           int1++) {
        TextureCombinerShaderParam textureCombinerShaderParam =
            textureCombinerCommand.shaderParams.get(int1);
        if (textureCombinerShaderParam.name == "intensity")
                    && (textureCombinerShaderParam.min != intensity || textureCombinerShaderParam.max != intensity)) {
                      textureCombinerShaderParam.min =
                          textureCombinerShaderParam.max = intensity;
                      this.setDirty();
                    }
      }
    } else if (intensity > 0.0F) {
      std::string string = "media/textures/BloodTextures/" +
                           MaskFiles[bodyPart.index()] + ".png";
      this.addDirtOverlay("media/textures/BloodTextures/GrimeOverlay.png",
                          string, intensity, int0);
    }
  }

  void removeBlood() {
    for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
      this.removeBlood(BloodBodyPartType.FromIndex(int0));
    }
  }

  void removeBlood(BloodBodyPartType bodyPart) {
    TextureCombinerCommand textureCombinerCommand =
        this.getFirstFromCategory(DecalOverlayCategory + bodyPart.index());
    if (textureCombinerCommand != nullptr) {
      for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
           int0++) {
        TextureCombinerShaderParam textureCombinerShaderParam =
            textureCombinerCommand.shaderParams.get(int0);
        if (textureCombinerShaderParam.name == "intensity") && (textureCombinerShaderParam.min != 0.0F || textureCombinerShaderParam.max != 0.0F)) {
            textureCombinerShaderParam.min = textureCombinerShaderParam.max =
                0.0F;
            this.setDirty();
          }
      }
    }
  }

  float addBlood(BloodBodyPartType bodyPart, float intensity,
                 IsoGameCharacter chr) {
    int int0 = DecalOverlayCategory + bodyPart.index();
    TextureCombinerCommand textureCombinerCommand =
        this.getFirstFromCategory(int0);
    if (bodyPart == BloodBodyPartType.Head && chr != nullptr) {
      if (chr.hair != nullptr) {
        chr.hair.tintR -= 0.022F;
        if (chr.hair.tintR < 0.0F) {
          chr.hair.tintR = 0.0F;
        }

        chr.hair.tintG -= 0.03F;
        if (chr.hair.tintG < 0.0F) {
          chr.hair.tintG = 0.0F;
        }

        chr.hair.tintB -= 0.03F;
        if (chr.hair.tintB < 0.0F) {
          chr.hair.tintB = 0.0F;
        }
      }

      if (chr.beard != nullptr) {
        chr.beard.tintR -= 0.022F;
        if (chr.beard.tintR < 0.0F) {
          chr.beard.tintR = 0.0F;
        }

        chr.beard.tintG -= 0.03F;
        if (chr.beard.tintG < 0.0F) {
          chr.beard.tintG = 0.0F;
        }

        chr.beard.tintB -= 0.03F;
        if (chr.beard.tintB < 0.0F) {
          chr.beard.tintB = 0.0F;
        }
      }
    }

    if (textureCombinerCommand != nullptr) {
      for (int int1 = 0; int1 < textureCombinerCommand.shaderParams.size();
           int1++) {
        TextureCombinerShaderParam textureCombinerShaderParam =
            textureCombinerCommand.shaderParams.get(int1);
        if (textureCombinerShaderParam.name == "intensity")) {
            float float0 = textureCombinerShaderParam.min;
            float0 += intensity;
            float0 = Math.min(1.0F, float0);
            if (textureCombinerShaderParam.min != float0 ||
                textureCombinerShaderParam.max != float0) {
              textureCombinerShaderParam.min = textureCombinerShaderParam.max =
                  float0;
              this.setDirty();
            }

            return float0;
          }
      }
    } else {
      std::string string = "media/textures/BloodTextures/" +
                           MaskFiles[bodyPart.index()] + ".png";
      this.addOverlay("media/textures/BloodTextures/BloodOverlay.png", string,
                      intensity, int0);
    }

    return intensity;
  }

  float addDirt(BloodBodyPartType bodyPart, float intensity,
                IsoGameCharacter chr) {
    int int0 = DirtOverlayCategory + bodyPart.index();
    TextureCombinerCommand textureCombinerCommand =
        this.getFirstFromCategory(int0);
    if (bodyPart == BloodBodyPartType.Head && chr != nullptr) {
      if (chr.hair != nullptr) {
        chr.hair.tintR -= 0.022F;
        if (chr.hair.tintR < 0.0F) {
          chr.hair.tintR = 0.0F;
        }

        chr.hair.tintG -= 0.03F;
        if (chr.hair.tintG < 0.0F) {
          chr.hair.tintG = 0.0F;
        }

        chr.hair.tintB -= 0.03F;
        if (chr.hair.tintB < 0.0F) {
          chr.hair.tintB = 0.0F;
        }
      }

      if (chr.beard != nullptr) {
        chr.beard.tintR -= 0.022F;
        if (chr.beard.tintR < 0.0F) {
          chr.beard.tintR = 0.0F;
        }

        chr.beard.tintG -= 0.03F;
        if (chr.beard.tintG < 0.0F) {
          chr.beard.tintG = 0.0F;
        }

        chr.beard.tintB -= 0.03F;
        if (chr.beard.tintB < 0.0F) {
          chr.beard.tintB = 0.0F;
        }
      }
    }

    if (textureCombinerCommand != nullptr) {
      for (int int1 = 0; int1 < textureCombinerCommand.shaderParams.size();
           int1++) {
        TextureCombinerShaderParam textureCombinerShaderParam =
            textureCombinerCommand.shaderParams.get(int1);
        if (textureCombinerShaderParam.name == "intensity")) {
            float float0 = textureCombinerShaderParam.min;
            float0 += intensity;
            float0 = Math.min(1.0F, float0);
            if (textureCombinerShaderParam.min != float0 ||
                textureCombinerShaderParam.max != float0) {
              textureCombinerShaderParam.min = textureCombinerShaderParam.max =
                  float0;
              this.setDirty();
            }

            return float0;
          }
      }
    } else {
      std::string string = "media/textures/BloodTextures/" +
                           MaskFiles[bodyPart.index()] + ".png";
      this.addDirtOverlay("media/textures/BloodTextures/GrimeOverlay.png",
                          string, intensity, int0);
    }

    return intensity;
  }

  void addShirtDecal(const std::string &dec) {
    GL11.glTexParameteri(3553, 10241, 9729);
    GL11.glTexParameteri(3553, 10240, 9729);
    this.addRect(dec, 102, 118, 52, 52);
  }
}
} // namespace characterTextures
} // namespace zombie
