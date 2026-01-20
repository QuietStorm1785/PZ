#include <string>
#include <vector>
#include "zombie\core\skinnedmodel\advancedanimation/AnimatedModel.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

public AnimatedModel::AnimatedModel() {
    // TODO: Implement AnimatedModel
    return nullptr;
}

void AnimatedModel::setVisual(HumanVisual var1) {
    // TODO: Implement setVisual
}

BaseVisual AnimatedModel::getVisual() {
    // TODO: Implement getVisual
    return nullptr;
}

HumanVisual AnimatedModel::getHumanVisual() {
    // TODO: Implement getHumanVisual
    return nullptr;
}

void AnimatedModel::getItemVisuals(ItemVisuals var1) {
    // TODO: Implement getItemVisuals
}

bool AnimatedModel::isFemale() {
    // TODO: Implement isFemale
    return false;
}

bool AnimatedModel::isZombie() {
    // TODO: Implement isZombie
    return false;
}

bool AnimatedModel::isSkeleton() {
    // TODO: Implement isSkeleton
    return false;
}

void AnimatedModel::setAnimSetName(const std::string& var1) {
    // TODO: Implement setAnimSetName
}

void AnimatedModel::setOutfitName(const std::string& var1, bool var2, bool var3) {
    // TODO: Implement setOutfitName
}

void AnimatedModel::setCharacter(IsoGameCharacter var1) {
    // TODO: Implement setCharacter
}

void AnimatedModel::setSurvivorDesc(SurvivorDesc var1) {
    // TODO: Implement setSurvivorDesc
}

void AnimatedModel::setPrimaryHandModelName(const std::string& var1) {
    // TODO: Implement setPrimaryHandModelName
}

void AnimatedModel::setSecondaryHandModelName(const std::string& var1) {
    // TODO: Implement setSecondaryHandModelName
}

void AnimatedModel::setAttachedModelNames(AttachedModelNames var1) {
    // TODO: Implement setAttachedModelNames
}

void AnimatedModel::setModelData(HumanVisual var1, ItemVisuals var2) {
    // TODO: Implement setModelData
}

void AnimatedModel::setAmbient(ColorInfo var1, bool var2, bool var3) {
    // TODO: Implement setAmbient
}

void AnimatedModel::setLights(ResultLight[] var1, float var2, float var3, float var4) {
    // TODO: Implement setLights
}

void AnimatedModel::setState(const std::string& var1) {
    // TODO: Implement setState
}

std::string AnimatedModel::getState() {
    // TODO: Implement getState
    return "";
}

void AnimatedModel::setAngle(Vector2 var1) {
    // TODO: Implement setAngle
}

void AnimatedModel::setOffset(float var1, float var2, float var3) {
    // TODO: Implement setOffset
}

void AnimatedModel::setIsometric(bool var1) {
    // TODO: Implement setIsometric
}

bool AnimatedModel::isIsometric() {
    // TODO: Implement isIsometric
    return false;
}

void AnimatedModel::setFlipY(bool var1) {
    // TODO: Implement setFlipY
}

void AnimatedModel::setAlpha(float var1) {
    // TODO: Implement setAlpha
}

void AnimatedModel::setTrackTime(float var1) {
    // TODO: Implement setTrackTime
}

void AnimatedModel::clothingItemChanged(const std::string& var1) {
    // TODO: Implement clothingItemChanged
}

void AnimatedModel::setAnimate(bool var1) {
    // TODO: Implement setAnimate
}

void AnimatedModel::initOutfit() {
    // TODO: Implement initOutfit
}

void AnimatedModel::populateCharacterModelSlot() {
    // TODO: Implement populateCharacterModelSlot
}

void AnimatedModel::addHeadHair(ItemVisual var1) {
    // TODO: Implement addHeadHair
}

void AnimatedModel::addHeadHairItem(const std::string& var1, const std::string& var2, ImmutableColor var3) {
    // TODO: Implement addHeadHairItem
}

void AnimatedModel::addClothingItem(ItemVisual var1, ClothingItem var2) {
    // TODO: Implement addClothingItem
}

bool AnimatedModel::isItemModelHidden(ItemVisuals var1, ItemVisual var2) {
    // TODO: Implement isItemModelHidden
    return false;
}

std::string AnimatedModel::processModelFileName(const std::string& var1) {
    // TODO: Implement processModelFileName
    return "";
}

void AnimatedModel::postProcessNewItemInstance(ModelInstance var1, ModelInstance var2, ImmutableColor var3) {
    // TODO: Implement postProcessNewItemInstance
}

void AnimatedModel::DoCharacterModelEquipped() {
    // TODO: Implement DoCharacterModelEquipped
}

ModelInstance AnimatedModel::addStatic(const std::string& var1, const std::string& var2) {
    // TODO: Implement addStatic
    return nullptr;
}

ModelInstance AnimatedModel::addStatic(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement addStatic
    return nullptr;
}

StateInfo AnimatedModel::stateInfoMain() {
    // TODO: Implement stateInfoMain
    return nullptr;
}

StateInfo AnimatedModel::stateInfoRender() {
    // TODO: Implement stateInfoRender
    return nullptr;
}

void AnimatedModel::update() {
    // TODO: Implement update
}

void AnimatedModel::updateInternal() {
    // TODO: Implement updateInternal
}

bool AnimatedModel::isModelInstanceReady(ModelInstance var1) {
    // TODO: Implement isModelInstanceReady
    return false;
}

void AnimatedModel::incrementRefCount(ModelInstance var1) {
    // TODO: Implement incrementRefCount
}

void AnimatedModel::initRenderData(StateInfo var1, AnimatedModelInstanceRenderData var2, ModelInstance var3) {
    // TODO: Implement initRenderData
}

bool AnimatedModel::isReadyToRender() {
    // TODO: Implement isReadyToRender
    return false;
}

int AnimatedModel::renderMain() {
    // TODO: Implement renderMain
    return 0;
}

bool AnimatedModel::isRendered() {
    // TODO: Implement isRendered
    return false;
}

void AnimatedModel::doneWithTextureCreator(ModelInstanceTextureCreator var1) {
    // TODO: Implement doneWithTextureCreator
}

void AnimatedModel::release(std::vector<AnimatedModelInstanceRenderData> var1) {
    // TODO: Implement release
}

void AnimatedModel::postRender(bool var1) {
    // TODO: Implement postRender
}

void AnimatedModel::DoRender(ModelCamera var1) {
    // TODO: Implement DoRender
}

void AnimatedModel::DoRender(int var1, int var2, int var3, int var4, float var5, float var6) {
    // TODO: Implement DoRender
}

void AnimatedModel::DoRenderToWorld(float var1, float var2, float var3, float var4) {
    // TODO: Implement DoRenderToWorld
}

void AnimatedModel::debugDrawAxes() {
    // TODO: Implement debugDrawAxes
}

void AnimatedModel::StartCharacter() {
    // TODO: Implement StartCharacter
}

void AnimatedModel::EndCharacter() {
    // TODO: Implement EndCharacter
}

void AnimatedModel::Render() {
    // TODO: Implement Render
}

void AnimatedModel::DrawChar(AnimatedModelInstanceRenderData var1) {
    // TODO: Implement DrawChar
}

void AnimatedModel::releaseAnimationPlayer() {
    // TODO: Implement releaseAnimationPlayer
}

void AnimatedModel::OnAnimEvent(AnimLayer var1, AnimEvent var2) {
    // TODO: Implement OnAnimEvent
}

AnimationPlayer AnimatedModel::getAnimationPlayer() {
    // TODO: Implement getAnimationPlayer
    return nullptr;
}

void AnimatedModel::actionStateChanged(ActionContext var1) {
    // TODO: Implement actionStateChanged
}

AnimationPlayerRecorder AnimatedModel::getAnimationPlayerRecorder() {
    // TODO: Implement getAnimationPlayerRecorder
    return nullptr;
}

bool AnimatedModel::isAnimationRecorderActive() {
    // TODO: Implement isAnimationRecorderActive
    return false;
}

ActionContext AnimatedModel::getActionContext() {
    // TODO: Implement getActionContext
    return nullptr;
}

AdvancedAnimator AnimatedModel::getAdvancedAnimator() {
    // TODO: Implement getAdvancedAnimator
    return nullptr;
}

ModelInstance AnimatedModel::getModelInstance() {
    // TODO: Implement getModelInstance
    return nullptr;
}

std::string AnimatedModel::GetAnimSetName() {
    // TODO: Implement GetAnimSetName
    return "";
}

std::string AnimatedModel::getUID() {
    // TODO: Implement getUID
    return "";
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
