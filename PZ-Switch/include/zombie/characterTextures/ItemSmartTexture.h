#pragma once
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/TextureCombinerCommand.h"
#include "zombie/core/textures/TextureCombinerShaderParam.h"
#include "zombie/util/StringUtils.h"
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

class ItemSmartTexture : public SmartTexture {
public:
 static const int DecalOverlayCategory = 300;
 std::string m_texName = nullptr;

public
 ItemSmartTexture(const std::string &tex) {
 if (tex != nullptr) {
 this->add(tex);
 this->m_texName = tex;
 }
 }

public
 ItemSmartTexture(const std::string &tex, float hue) {
 this->addHue("media/textures/" + tex + ".png", 300, hue);
 this->m_texName = tex;
 }

 void setDenimPatches(BloodBodyPartType bodyPart) {
 if (!StringUtils.isNullOrEmpty(
 CharacterSmartTexture.DenimPatchesMaskFiles[bodyPart.index()])) {
 std::string string =
 "media/textures/patches/" +
 CharacterSmartTexture.DenimPatchesMaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DecalOverlayCategory + bodyPart.index();
 this->addOverlayPatches(string, "media/textures/patches/patchesmask.png",
 int0);
 }
 }

 void setLeatherPatches(BloodBodyPartType bodyPart) {
 if (!StringUtils.isNullOrEmpty(
 CharacterSmartTexture.LeatherPatchesMaskFiles[bodyPart.index()])) {
 std::string string =
 "media/textures/patches/" +
 CharacterSmartTexture.LeatherPatchesMaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DecalOverlayCategory + bodyPart.index();
 this->addOverlayPatches(string, "media/textures/patches/patchesmask.png",
 int0);
 }
 }

 void setBasicPatches(BloodBodyPartType bodyPart) {
 if (!StringUtils.isNullOrEmpty(
 CharacterSmartTexture.BasicPatchesMaskFiles[bodyPart.index()])) {
 std::string string =
 "media/textures/patches/" +
 CharacterSmartTexture.BasicPatchesMaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DecalOverlayCategory + bodyPart.index();
 this->addOverlayPatches(string, "media/textures/patches/patchesmask.png",
 int0);
 }
 }

 void setBlood(const std::string &tex, BloodBodyPartType bodyPart,
 float intensity) {
 std::string string = "media/textures/BloodTextures/" +
 CharacterSmartTexture.MaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DecalOverlayCategory + bodyPart.index();
 this->setBlood(tex, string, intensity, int0);
 }

 void setBlood(const std::string &tex, const std::string &mask,
 float intensity, int category) {
 intensity = Math.max(0.0F, Math.min(1.0F, intensity);
 TextureCombinerCommand textureCombinerCommand =
 this->getFirstFromCategory(category);
 if (textureCombinerCommand != nullptr) {
 for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
 int0++) {
 TextureCombinerShaderParam textureCombinerShaderParam =
 textureCombinerCommand.shaderParams.get(int0);
 if (textureCombinerShaderParam.name == "intensity")
 && (textureCombinerShaderParam.min != intensity || textureCombinerShaderParam.max != intensity) {
 textureCombinerShaderParam.min =
 textureCombinerShaderParam.max = intensity;
 this->setDirty();
 }
 }
 } else if (intensity > 0.0F) {
 this->addOverlay(tex, mask, intensity, category);
 }
 }

 float addBlood(const std::string &tex, BloodBodyPartType bodyPart,
 float intensity) {
 std::string string = "media/textures/BloodTextures/" +
 CharacterSmartTexture.MaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DecalOverlayCategory + bodyPart.index();
 return this->addBlood(tex, string, intensity, int0);
 }

 float addDirt(const std::string &tex, BloodBodyPartType bodyPart,
 float intensity) {
 std::string string = "media/textures/BloodTextures/" +
 CharacterSmartTexture.MaskFiles[bodyPart.index()] +
 ".png";
 int int0 = CharacterSmartTexture.DirtOverlayCategory + bodyPart.index();
 return this->addDirt(tex, string, intensity, int0);
 }

 float addBlood(const std::string &tex, const std::string &mask,
 float intensity, int category) {
 TextureCombinerCommand textureCombinerCommand =
 this->getFirstFromCategory(category);
 if (textureCombinerCommand.empty()) {
 this->addOverlay(tex, mask, intensity, category);
 return intensity;
 } else {
 for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
 int0++) {
 TextureCombinerShaderParam textureCombinerShaderParam =
 textureCombinerCommand.shaderParams.get(int0);
 if (textureCombinerShaderParam.name == "intensity")) {
 float float0 = textureCombinerShaderParam.min;
 float0 += intensity;
 float0 = Math.min(1.0F, float0);
 if (textureCombinerShaderParam.min != float0 ||
 textureCombinerShaderParam.max != float0) {
 textureCombinerShaderParam.min = textureCombinerShaderParam.max =
 float0;
 this->setDirty();
 }

 return float0;
 }
 }

 this->addOverlay(tex, mask, intensity, category);
 return intensity;
 }
 }

 float addDirt(const std::string &tex, const std::string &mask,
 float intensity, int category) {
 TextureCombinerCommand textureCombinerCommand =
 this->getFirstFromCategory(category);
 if (textureCombinerCommand.empty()) {
 this->addDirtOverlay(tex, mask, intensity, category);
 return intensity;
 } else {
 for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
 int0++) {
 TextureCombinerShaderParam textureCombinerShaderParam =
 textureCombinerCommand.shaderParams.get(int0);
 if (textureCombinerShaderParam.name == "intensity")) {
 float float0 = textureCombinerShaderParam.min;
 float0 += intensity;
 float0 = Math.min(1.0F, float0);
 if (textureCombinerShaderParam.min != float0 ||
 textureCombinerShaderParam.max != float0) {
 textureCombinerShaderParam.min = textureCombinerShaderParam.max =
 float0;
 this->setDirty();
 }

 return float0;
 }
 }

 this->addOverlay(tex, mask, intensity, category);
 return intensity;
 }
 }

 void removeBlood() {
 for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
 this->removeBlood(BloodBodyPartType.FromIndex(int0);
 }
 }

 void removeDirt() {
 for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
 this->removeDirt(BloodBodyPartType.FromIndex(int0);
 }
 }

 void removeBlood(BloodBodyPartType bodyPart) {
 TextureCombinerCommand textureCombinerCommand = this->getFirstFromCategory(
 CharacterSmartTexture.DecalOverlayCategory + bodyPart.index());
 if (textureCombinerCommand != nullptr) {
 for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
 int0++) {
 TextureCombinerShaderParam textureCombinerShaderParam =
 textureCombinerCommand.shaderParams.get(int0);
 if (textureCombinerShaderParam.name == "intensity") && (textureCombinerShaderParam.min != 0.0F || textureCombinerShaderParam.max != 0.0F) {
 textureCombinerShaderParam.min = textureCombinerShaderParam.max =
 0.0F;
 this->setDirty();
 }
 }
 }
 }

 void removeDirt(BloodBodyPartType bodyPart) {
 TextureCombinerCommand textureCombinerCommand = this->getFirstFromCategory(
 CharacterSmartTexture.DirtOverlayCategory + bodyPart.index());
 if (textureCombinerCommand != nullptr) {
 for (int int0 = 0; int0 < textureCombinerCommand.shaderParams.size();
 int0++) {
 TextureCombinerShaderParam textureCombinerShaderParam =
 textureCombinerCommand.shaderParams.get(int0);
 if (textureCombinerShaderParam.name == "intensity") && (textureCombinerShaderParam.min != 0.0F || textureCombinerShaderParam.max != 0.0F) {
 textureCombinerShaderParam.min = textureCombinerShaderParam.max =
 0.0F;
 this->setDirty();
 }
 }
 }
 }

 std::string getTexName() { return this->m_texName; }
}
} // namespace characterTextures
} // namespace zombie
