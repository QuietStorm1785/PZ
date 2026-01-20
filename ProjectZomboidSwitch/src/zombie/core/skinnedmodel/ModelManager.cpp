#include <string>
#include <vector>
#include "zombie\core\skinnedmodel/ModelManager.h"

namespace zombie {
namespace core {
namespace skinnedmodel {

bool ModelManager::isCreated() {
    // TODO: Implement isCreated
    return false;
}

void ModelManager::create() {
    // TODO: Implement create
}

void ModelManager::loadAdditionalModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
    // TODO: Implement loadAdditionalModel
}

ModelInstance ModelManager::newAdditionalModelInstance(const std::string& var1, const std::string& var2, IsoGameCharacter var3, AnimationPlayer var4, const std::string& var5) {
    // TODO: Implement newAdditionalModelInstance
    return nullptr;
}

void ModelManager::loadAnimsFromDir(const std::string& var1, ModelMesh var2) {
    // TODO: Implement loadAnimsFromDir
}

void ModelManager::loadAnimsFromDir(URI var1, URI var2, File var3, ModelMesh var4, ModAnimations var5) {
    // TODO: Implement loadAnimsFromDir
}

void ModelManager::RenderSkyBox(TextureDraw var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement RenderSkyBox
}

void ModelManager::RenderWater(TextureDraw var1, int var2, int var3, bool var4) {
    // TODO: Implement RenderWater
}

void ModelManager::RenderPuddles(int var1, int var2, int var3) {
    // TODO: Implement RenderPuddles
}

void ModelManager::RenderParticles(TextureDraw var1, int var2, int var3) {
    // TODO: Implement RenderParticles
}

void ModelManager::Reset(IsoGameCharacter var1) {
    // TODO: Implement Reset
}

void ModelManager::reloadAllOutfits() {
    // TODO: Implement reloadAllOutfits
}

void ModelManager::Add(IsoGameCharacter var1) {
    // TODO: Implement Add
}

void ModelManager::dressInRandomOutfit(IsoGameCharacter var1) {
    // TODO: Implement dressInRandomOutfit
}

Model ModelManager::getBodyModel(IsoGameCharacter var1) {
    // TODO: Implement getBodyModel
    return nullptr;
}

bool ModelManager::ContainsChar(IsoGameCharacter var1) {
    // TODO: Implement ContainsChar
    return false;
}

void ModelManager::ResetCharacterEquippedHands(IsoGameCharacter var1) {
    // TODO: Implement ResetCharacterEquippedHands
}

void ModelManager::DoCharacterModelEquipped(IsoGameCharacter var1, ModelSlot var2) {
    // TODO: Implement DoCharacterModelEquipped
}

ModelInstance ModelManager::addEquippedModelInstance(IsoGameCharacter var1, ModelSlot var2, InventoryItem var3, const std::string& var4, ItemReplacement var5, bool var6) {
    // TODO: Implement addEquippedModelInstance
    return nullptr;
}

ModelInstance ModelManager::addMaskingModel(ModelSlot var1, IsoGameCharacter var2, InventoryItem var3, ItemReplacement var4, const std::string& var5, const std::string& var6, const std::string& var7) {
    // TODO: Implement addMaskingModel
    return nullptr;
}

void ModelManager::addWeaponPartModels(ModelSlot var1, HandWeapon var2, ModelInstance var3) {
    // TODO: Implement addWeaponPartModels
}

void ModelManager::resetModelInstance(ModelInstance var1, void* var2) {
    // TODO: Implement resetModelInstance
}

void ModelManager::resetModelInstanceRecurse(ModelInstance var1, void* var2) {
    // TODO: Implement resetModelInstanceRecurse
}

void ModelManager::resetModelInstancesRecurse(std::vector<ModelInstance> var1, void* var2) {
    // TODO: Implement resetModelInstancesRecurse
}

void ModelManager::derefModelInstance(ModelInstance var1) {
    // TODO: Implement derefModelInstance
}

void ModelManager::derefModelInstances(std::vector<ModelInstance> var1) {
    // TODO: Implement derefModelInstances
}

void ModelManager::DoCharacterModelParts(IsoGameCharacter var1, ModelSlot var2) {
    // TODO: Implement DoCharacterModelParts
}

void ModelManager::update() {
    // TODO: Implement update
}

ModelSlot ModelManager::addNewSlot(IsoGameCharacter var1) {
    // TODO: Implement addNewSlot
    return nullptr;
}

ModelSlot ModelManager::getSlot(IsoGameCharacter var1) {
    // TODO: Implement getSlot
    return nullptr;
}

bool ModelManager::DoRemove(IsoGameCharacter var1) {
    // TODO: Implement DoRemove
    return false;
}

void ModelManager::Remove(IsoGameCharacter var1) {
    // TODO: Implement Remove
}

void ModelManager::Remove(BaseVehicle var1) {
    // TODO: Implement Remove
}

void ModelManager::ResetNextFrame(IsoGameCharacter var1) {
    // TODO: Implement ResetNextFrame
}

void ModelManager::ResetEquippedNextFrame(IsoGameCharacter var1) {
    // TODO: Implement ResetEquippedNextFrame
}

void ModelManager::Reset() {
    // TODO: Implement Reset
}

void ModelManager::getClosestThreeLights(IsoMovingObject var1, IsoLightSource[] var2) {
    // TODO: Implement getClosestThreeLights
}

void ModelManager::addVehicle(BaseVehicle var1) {
    // TODO: Implement addVehicle
}

ModelInstance ModelManager::addStatic(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    // TODO: Implement addStatic
    return nullptr;
}

ModelInstance ModelManager::newStaticInstance(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    // TODO: Implement newStaticInstance
    return nullptr;
}

ModelInstance ModelManager::addStatic(ModelSlot var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement addStatic
    return nullptr;
}

ModelInstance ModelManager::addStaticForcedTex(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement addStaticForcedTex
    return nullptr;
}

ModelInstance ModelManager::addStatic(ModelInstance var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement addStatic
    return nullptr;
}

ModelInstance ModelManager::addStaticForcedTex(ModelInstance var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    // TODO: Implement addStaticForcedTex
    return nullptr;
}

std::string ModelManager::modifyShaderName(const std::string& var1) {
    // TODO: Implement modifyShaderName
    return "";
}

Model ModelManager::loadModelInternal(const std::string& var1, const std::string& var2, const std::string& var3, ModelMesh var4, bool var5) {
    // TODO: Implement loadModelInternal
    return nullptr;
}

int ModelManager::getTextureFlags() {
    // TODO: Implement getTextureFlags
    return 0;
}

void ModelManager::setModelMetaData(const std::string& var1, const std::string& var2, const std::string& var3, bool var4) {
    // TODO: Implement setModelMetaData
}

void ModelManager::setModelMetaData(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, bool var5) {
    // TODO: Implement setModelMetaData
}

Model ModelManager::loadStaticModel(const std::string& var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement loadStaticModel
    return nullptr;
}

Model ModelManager::loadModel(const std::string& var1, const std::string& var2, ModelMesh var3) {
    // TODO: Implement loadModel
    return nullptr;
}

Model ModelManager::getLoadedModel(const std::string& var1) {
    // TODO: Implement getLoadedModel
    return nullptr;
}

Model ModelManager::getLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
    // TODO: Implement getLoadedModel
    return nullptr;
}

Model ModelManager::tryGetLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4, bool var5) {
    // TODO: Implement tryGetLoadedModel
    return nullptr;
}

void ModelManager::putLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4, Model var5) {
    // TODO: Implement putLoadedModel
}

std::string ModelManager::createModelKey(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
    // TODO: Implement createModelKey
    return "";
}

std::string ModelManager::createModelKey2(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
    // TODO: Implement createModelKey2
    return "";
}

AnimationAsset ModelManager::loadAnim(const std::string& var1, ModelMesh var2, ModAnimations var3) {
    // TODO: Implement loadAnim
    return {};
}

void ModelManager::putAnimationAsset(const std::string& var1, AnimationAsset var2, ModAnimations var3) {
    // TODO: Implement putAnimationAsset
}

std::string ModelManager::animAssetToString(AnimationAsset var1) {
    // TODO: Implement animAssetToString
    return "";
}

AnimationAsset ModelManager::getAnimationAsset(const std::string& var1) {
    // TODO: Implement getAnimationAsset
    return {};
}

AnimationAsset ModelManager::getAnimationAssetRequired(const std::string& var1) {
    // TODO: Implement getAnimationAssetRequired
    return {};
}

void ModelManager::addAnimationClip(const std::string& var1, AnimationClip var2) {
    // TODO: Implement addAnimationClip
}

AnimationClip ModelManager::getAnimationClip(const std::string& var1) {
    // TODO: Implement getAnimationClip
    return nullptr;
}

ModelInstance ModelManager::newInstance(Model var1, IsoGameCharacter var2, AnimationPlayer var3) {
    // TODO: Implement newInstance
    return nullptr;
}

bool ModelManager::isLoadingAnimations() {
    // TODO: Implement isLoadingAnimations
    return false;
}

void ModelManager::reloadModelsMatching(const std::string& var1) {
    // TODO: Implement reloadModelsMatching
}

void ModelManager::loadModAnimations() {
    // TODO: Implement loadModAnimations
}

void ModelManager::setActiveAnimations() {
    // TODO: Implement setActiveAnimations
}

void ModelManager::animationAssetLoaded(AnimationAsset var1) {
    // TODO: Implement animationAssetLoaded
}

void ModelManager::initAnimationMeshes(bool var1) {
    // TODO: Implement initAnimationMeshes
}

bool ModelManager::isLoadingAnimationMeshes() {
    // TODO: Implement isLoadingAnimationMeshes
    return false;
}

void ModelManager::loadHumanAnimations(Mod var1, ModAnimations var2) {
    // TODO: Implement loadHumanAnimations
}

bool ModelManager::isAnimationsMeshDirectory(const std::string& var1) {
    // TODO: Implement isAnimationsMeshDirectory
    return false;
}

} // namespace skinnedmodel
} // namespace core
} // namespace zombie
