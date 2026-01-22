#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/TextureCombinerCommand.h"
#include "zombie/core/textures/TextureCombinerShaderParam.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace characterTextures {


class ItemSmartTexture : public SmartTexture {
public:
    static const int DecalOverlayCategory = 300;
    std::string m_texName = nullptr;

    public ItemSmartTexture(const std::string& var1) {
      if (var1 != nullptr) {
         this.push_back(var1);
         this.m_texName = var1;
      }
   }

    public ItemSmartTexture(const std::string& var1, float var2) {
      this.addHue("media/textures/" + var1 + ".png", 300, var2);
      this.m_texName = var1;
   }

    void setDenimPatches(BloodBodyPartType var1) {
      if (!StringUtils.isNullOrEmpty(CharacterSmartTexture.DenimPatchesMaskFiles[var1.index()])) {
    std::string var2 = "media/textures/patches/" + CharacterSmartTexture.DenimPatchesMaskFiles[var1.index()] + ".png";
    int var3 = CharacterSmartTexture.DecalOverlayCategory + var1.index();
         this.addOverlayPatches(var2, "media/textures/patches/patchesmask.png", var3);
      }
   }

    void setLeatherPatches(BloodBodyPartType var1) {
      if (!StringUtils.isNullOrEmpty(CharacterSmartTexture.LeatherPatchesMaskFiles[var1.index()])) {
    std::string var2 = "media/textures/patches/" + CharacterSmartTexture.LeatherPatchesMaskFiles[var1.index()] + ".png";
    int var3 = CharacterSmartTexture.DecalOverlayCategory + var1.index();
         this.addOverlayPatches(var2, "media/textures/patches/patchesmask.png", var3);
      }
   }

    void setBasicPatches(BloodBodyPartType var1) {
      if (!StringUtils.isNullOrEmpty(CharacterSmartTexture.BasicPatchesMaskFiles[var1.index()])) {
    std::string var2 = "media/textures/patches/" + CharacterSmartTexture.BasicPatchesMaskFiles[var1.index()] + ".png";
    int var3 = CharacterSmartTexture.DecalOverlayCategory + var1.index();
         this.addOverlayPatches(var2, "media/textures/patches/patchesmask.png", var3);
      }
   }

    void setBlood(const std::string& var1, BloodBodyPartType var2, float var3) {
    std::string var4 = "media/textures/BloodTextures/" + CharacterSmartTexture.MaskFiles[var2.index()] + ".png";
    int var5 = CharacterSmartTexture.DecalOverlayCategory + var2.index();
      this.setBlood(var1, var4, var3, var5);
   }

    void setBlood(const std::string& var1, const std::string& var2, float var3, int var4) {
      var3 = Math.max(0.0F, Math.min(1.0F, var3));
    TextureCombinerCommand var5 = this.getFirstFromCategory(var4);
      if (var5 != nullptr) {
         for (int var6 = 0; var6 < var5.shaderParams.size(); var6++) {
    TextureCombinerShaderParam var7 = (TextureCombinerShaderParam)var5.shaderParams.get(var6);
            if (var7.name == "intensity") && (var7.min != var3 || var7.max != var3)) {
               var7.min = var7.max = var3;
               this.setDirty();
            }
         }
      } else if (var3 > 0.0F) {
         this.addOverlay(var1, var2, var3, var4);
      }
   }

    float addBlood(const std::string& var1, BloodBodyPartType var2, float var3) {
    std::string var4 = "media/textures/BloodTextures/" + CharacterSmartTexture.MaskFiles[var2.index()] + ".png";
    int var5 = CharacterSmartTexture.DecalOverlayCategory + var2.index();
      return this.addBlood(var1, var4, var3, var5);
   }

    float addDirt(const std::string& var1, BloodBodyPartType var2, float var3) {
    std::string var4 = "media/textures/BloodTextures/" + CharacterSmartTexture.MaskFiles[var2.index()] + ".png";
    int var5 = CharacterSmartTexture.DirtOverlayCategory + var2.index();
      return this.addDirt(var1, var4, var3, var5);
   }

    float addBlood(const std::string& var1, const std::string& var2, float var3, int var4) {
    TextureCombinerCommand var5 = this.getFirstFromCategory(var4);
      if (var5 == nullptr) {
         this.addOverlay(var1, var2, var3, var4);
    return var3;
      } else {
         for (int var6 = 0; var6 < var5.shaderParams.size(); var6++) {
    TextureCombinerShaderParam var7 = (TextureCombinerShaderParam)var5.shaderParams.get(var6);
            if (var7.name == "intensity")) {
    float var8 = var7.min;
               var8 += var3;
               var8 = Math.min(1.0F, var8);
               if (var7.min != var8 || var7.max != var8) {
                  var7.min = var7.max = var8;
                  this.setDirty();
               }

    return var8;
            }
         }

         this.addOverlay(var1, var2, var3, var4);
    return var3;
      }
   }

    float addDirt(const std::string& var1, const std::string& var2, float var3, int var4) {
    TextureCombinerCommand var5 = this.getFirstFromCategory(var4);
      if (var5 == nullptr) {
         this.addDirtOverlay(var1, var2, var3, var4);
    return var3;
      } else {
         for (int var6 = 0; var6 < var5.shaderParams.size(); var6++) {
    TextureCombinerShaderParam var7 = (TextureCombinerShaderParam)var5.shaderParams.get(var6);
            if (var7.name == "intensity")) {
    float var8 = var7.min;
               var8 += var3;
               var8 = Math.min(1.0F, var8);
               if (var7.min != var8 || var7.max != var8) {
                  var7.min = var7.max = var8;
                  this.setDirty();
               }

    return var8;
            }
         }

         this.addOverlay(var1, var2, var3, var4);
    return var3;
      }
   }

    void removeBlood() {
      for (int var1 = 0; var1 < BloodBodyPartType.MAX.index(); var1++) {
         this.removeBlood(BloodBodyPartType.FromIndex(var1));
      }
   }

    void removeDirt() {
      for (int var1 = 0; var1 < BloodBodyPartType.MAX.index(); var1++) {
         this.removeDirt(BloodBodyPartType.FromIndex(var1));
      }
   }

    void removeBlood(BloodBodyPartType var1) {
    TextureCombinerCommand var2 = this.getFirstFromCategory(CharacterSmartTexture.DecalOverlayCategory + var1.index());
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

    void removeDirt(BloodBodyPartType var1) {
    TextureCombinerCommand var2 = this.getFirstFromCategory(CharacterSmartTexture.DirtOverlayCategory + var1.index());
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

    std::string getTexName() {
      return this.m_texName;
   }
}
} // namespace characterTextures
} // namespace zombie
