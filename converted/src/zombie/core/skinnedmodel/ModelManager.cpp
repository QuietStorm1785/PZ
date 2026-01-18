#include "zombie/core/skinnedmodel/ModelManager.h"

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

void ModelManager::loadAdditionalModel(const std::string& meshName, const std::string& tex, bool bStatic, const std::string& shaderName) {
 // TODO: Implement loadAdditionalModel
}

ModelInstance ModelManager::newAdditionalModelInstance(const std::string& meshName, const std::string& tex, IsoGameCharacter chr, AnimationPlayer animPlayer, const std::string& shaderName) {
 // TODO: Implement newAdditionalModelInstance
 return nullptr;
}

void ModelManager::loadAnimsFromDir(const std::string& string, ModelMesh modelMesh) {
 // TODO: Implement loadAnimsFromDir
}

void ModelManager::loadAnimsFromDir(URI uri0, URI uri1, File file0, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 // TODO: Implement loadAnimsFromDir
}

void ModelManager::RenderSkyBox(TextureDraw texd, int shaderID, int userId, int apiId, int bufferId) {
 // TODO: Implement RenderSkyBox
}

void ModelManager::RenderWater(TextureDraw texd, int shaderID, int userId, bool bShore) {
 // TODO: Implement RenderWater
}

void ModelManager::RenderPuddles(int shaderID, int userId, int z) {
 // TODO: Implement RenderPuddles
}

void ModelManager::RenderParticles(TextureDraw texd, int userId, int va11) {
 // TODO: Implement RenderParticles
}

void ModelManager::Reset(IsoGameCharacter chr) {
 // TODO: Implement Reset
}

void ModelManager::reloadAllOutfits() {
 // TODO: Implement reloadAllOutfits
}

void ModelManager::Add(IsoGameCharacter chr) {
 // TODO: Implement Add
}

void ModelManager::dressInRandomOutfit(IsoGameCharacter chr) {
 // TODO: Implement dressInRandomOutfit
}

Model ModelManager::getBodyModel(IsoGameCharacter chr) {
 // TODO: Implement getBodyModel
 return nullptr;
}

bool ModelManager::ContainsChar(IsoGameCharacter chr) {
 // TODO: Implement ContainsChar
 return false;
}

void ModelManager::ResetCharacterEquippedHands(IsoGameCharacter chr) {
 // TODO: Implement ResetCharacterEquippedHands
}

void ModelManager::DoCharacterModelEquipped(IsoGameCharacter character, ModelManager.ModelSlot modelSlot) {
 // TODO: Implement DoCharacterModelEquipped
}

void ModelManager::addWeaponPartModels(ModelManager.ModelSlot modelSlot, HandWeapon weapon, ModelInstance modelInstance1) {
 // TODO: Implement addWeaponPartModels
}

void ModelManager::resetModelInstance(ModelInstance modelInstance, void* expectedOwner) {
 // TODO: Implement resetModelInstance
}

void ModelManager::resetModelInstanceRecurse(ModelInstance modelInstance, void* expectedOwner) {
 // TODO: Implement resetModelInstanceRecurse
}

void ModelManager::resetModelInstancesRecurse(ArrayList<ModelInstance> modelInstances, void* expectedOwner) {
 // TODO: Implement resetModelInstancesRecurse
}

void ModelManager::derefModelInstance(ModelInstance modelInstance) {
 // TODO: Implement derefModelInstance
}

void ModelManager::derefModelInstances(ArrayList<ModelInstance> modelInstances) {
 // TODO: Implement derefModelInstances
}

void ModelManager::DoCharacterModelParts(IsoGameCharacter character, ModelManager.ModelSlot modelSlot) {
 // TODO: Implement DoCharacterModelParts
}

void ModelManager::update() {
 // TODO: Implement update
}

bool ModelManager::DoRemove(IsoGameCharacter character) {
 // TODO: Implement DoRemove
 return false;
}

void ModelManager::Remove(IsoGameCharacter chr) {
 // TODO: Implement Remove
}

void ModelManager::Remove(BaseVehicle vehicle) {
 // TODO: Implement Remove
}

void ModelManager::ResetNextFrame(IsoGameCharacter isoGameCharacter) {
 // TODO: Implement ResetNextFrame
}

void ModelManager::ResetEquippedNextFrame(IsoGameCharacter isoGameCharacter) {
 // TODO: Implement ResetEquippedNextFrame
}

void ModelManager::Reset() {
 // TODO: Implement Reset
}

void ModelManager::getClosestThreeLights(IsoMovingObject movingObject, IsoLightSource[] lightSources) {
 // TODO: Implement getClosestThreeLights
}

void ModelManager::addVehicle(BaseVehicle vehicle) {
 // TODO: Implement addVehicle
}

ModelInstance ModelManager::addStatic(ModelManager.ModelSlot slot, const std::string& meshName, const std::string& texName, const std::string& boneName, const std::string& shaderName) {
 // TODO: Implement addStatic
 return nullptr;
}

ModelInstance ModelManager::newStaticInstance(ModelManager.ModelSlot slot, const std::string& meshName, const std::string& texName, const std::string& boneName, const std::string& shaderName) {
 // TODO: Implement newStaticInstance
 return nullptr;
}

ModelInstance ModelManager::addStatic(ModelManager.ModelSlot modelSlot, const std::string& string0, const std::string& string1) {
 // TODO: Implement addStatic
 return nullptr;
}

ModelInstance ModelManager::addStaticForcedTex(ModelManager.ModelSlot modelSlot, const std::string& string1, const std::string& string5, const std::string& string4) {
 // TODO: Implement addStaticForcedTex
 return nullptr;
}

ModelInstance ModelManager::addStatic(ModelInstance parentInst, const std::string& modelName, const std::string& attachNameSelf, const std::string& attachNameParent) {
 // TODO: Implement addStatic
 return nullptr;
}

ModelInstance ModelManager::addStaticForcedTex(ModelInstance parentInst, const std::string& modelName, const std::string& attachNameSelf, const std::string& attachNameParent, const std::string& forcedTex) {
 // TODO: Implement addStaticForcedTex
 return nullptr;
}

std::string ModelManager::modifyShaderName(const std::string& string) {
 // TODO: Implement modifyShaderName
 return "";
}

Model ModelManager::loadModelInternal(const std::string& string1, const std::string& string2, const std::string& string0, ModelMesh modelMesh, bool boolean0) {
 // TODO: Implement loadModelInternal
 return nullptr;
}

int ModelManager::getTextureFlags() {
 // TODO: Implement getTextureFlags
 return 0;
}

void ModelManager::setModelMetaData(const std::string& meshName, const std::string& texName, const std::string& shaderName, bool bStatic) {
 // TODO: Implement setModelMetaData
}

void ModelManager::setModelMetaData(const std::string& modelId, const std::string& meshName, const std::string& texName, const std::string& shaderName, bool bStatic) {
 // TODO: Implement setModelMetaData
}

Model ModelManager::loadStaticModel(const std::string& meshName, const std::string& tex, const std::string& shaderName) {
 // TODO: Implement loadStaticModel
 return nullptr;
}

Model ModelManager::loadModel(const std::string& string0, const std::string& string1, ModelMesh modelMesh) {
 // TODO: Implement loadModel
 return nullptr;
}

Model ModelManager::getLoadedModel(const std::string& meshName) {
 // TODO: Implement getLoadedModel
 return nullptr;
}

Model ModelManager::getLoadedModel(const std::string& meshName, const std::string& tex, bool isStatic, const std::string& shaderName) {
 // TODO: Implement getLoadedModel
 return nullptr;
}

Model ModelManager::tryGetLoadedModel(const std::string& meshName, const std::string& tex, bool isStatic, const std::string& shaderName, bool logError) {
 // TODO: Implement tryGetLoadedModel
 return nullptr;
}

void ModelManager::putLoadedModel(const std::string& name, const std::string& tex, bool isStatic, const std::string& shaderName, Model model) {
 // TODO: Implement putLoadedModel
}

std::string ModelManager::createModelKey(const std::string& string0, const std::string& string2, bool boolean0, const std::string& string1) {
 // TODO: Implement createModelKey
 return "";
}

std::string ModelManager::createModelKey2(const std::string& string0, const std::string& string3, bool boolean0, const std::string& string1) {
 // TODO: Implement createModelKey2
 return "";
}

AnimationAsset ModelManager::loadAnim(const std::string& string, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 // TODO: Implement loadAnim
 return {};
}

void ModelManager::putAnimationAsset(const std::string& string1, AnimationAsset animationAsset1, ModelManager.ModAnimations modAnimations) {
 // TODO: Implement putAnimationAsset
}

std::string ModelManager::animAssetToString(AnimationAsset animationAsset) {
 // TODO: Implement animAssetToString
 return "";
}

AnimationAsset ModelManager::getAnimationAsset(const std::string& string1) {
 // TODO: Implement getAnimationAsset
 return {};
}

AnimationAsset ModelManager::getAnimationAssetRequired(const std::string& string) {
 // TODO: Implement getAnimationAssetRequired
 return {};
}

void ModelManager::addAnimationClip(const std::string& name, AnimationClip clip) {
 // TODO: Implement addAnimationClip
}

AnimationClip ModelManager::getAnimationClip(const std::string& name) {
 // TODO: Implement getAnimationClip
 return nullptr;
}

ModelInstance ModelManager::newInstance(Model model, IsoGameCharacter chr, AnimationPlayer player) {
 // TODO: Implement newInstance
 return nullptr;
}

bool ModelManager::isLoadingAnimations() {
 // TODO: Implement isLoadingAnimations
 return false;
}

void ModelManager::reloadModelsMatching(const std::string& meshName) {
 // TODO: Implement reloadModelsMatching
}

void ModelManager::loadModAnimations() {
 // TODO: Implement loadModAnimations
}

void ModelManager::setActiveAnimations() {
 // TODO: Implement setActiveAnimations
}

void ModelManager::animationAssetLoaded(AnimationAsset animationAsset) {
 // TODO: Implement animationAssetLoaded
}

void ModelManager::initAnimationMeshes(bool bReloading) {
 // TODO: Implement initAnimationMeshes
}

bool ModelManager::isLoadingAnimationMeshes() {
 // TODO: Implement isLoadingAnimationMeshes
 return false;
}

void ModelManager::loadHumanAnimations(ChooseGameInfo.Mod mod, ModelManager.ModAnimations modAnimations) {
 // TODO: Implement loadHumanAnimations
}

bool ModelManager::isAnimationsMeshDirectory(const std::string& string) {
 // TODO: Implement isAnimationsMeshDirectory
 return false;
}

public ModelManager::AnimDirReloader(URI uri0, URI uri1, const std::string& string, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 // TODO: Implement AnimDirReloader
 return nullptr;
}

bool ModelManager::IsInDir(const std::string& string) {
 // TODO: Implement IsInDir
 return false;
}

void ModelManager::call(const std::string& string1) {
 // TODO: Implement call
}

PredicatedFileWatcher ModelManager::GetFileWatcher() {
 // TODO: Implement GetFileWatcher
 return nullptr;
}

public ModelManager::ModAnimations(const std::string& modID) {
 // TODO: Implement ModAnimations
 return nullptr;
}

void ModelManager::setPriority(int priority) {
 // TODO: Implement setPriority
}

bool ModelManager::isActive() {
 // TODO: Implement isActive
 return false;
}

public ModelManager::ModelSlot(int _ID, ModelInstance _model, IsoGameCharacter _character) {
 // TODO: Implement ModelSlot
 return nullptr;
}

void ModelManager::Update() {
 // TODO: Implement Update
}

bool ModelManager::isRendering() {
 // TODO: Implement isRendering
 return false;
}

void ModelManager::reset() {
 // TODO: Implement reset
}

} // namespace skinnedmodel
} // namespace core
} // namespace zombie
