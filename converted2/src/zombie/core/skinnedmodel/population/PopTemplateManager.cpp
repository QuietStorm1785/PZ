#include "zombie/core/skinnedmodel/population/PopTemplateManager.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {

void PopTemplateManager::init() {
  // TODO: Implement init
}

ModelInstance PopTemplateManager::addClothingItem(
    IsoGameCharacter character, ModelManager.ModelSlot modelSlot,
    ItemVisual itemVisual, ClothingItem clothingItem) {
  // TODO: Implement addClothingItem
  return nullptr;
}

void PopTemplateManager::addHeadHairItem(IsoGameCharacter character,
                                         ModelManager.ModelSlot modelSlot,
                                         const std::string &string0,
                                         const std::string &string1,
                                         ImmutableColor immutableColor) {
  // TODO: Implement addHeadHairItem
}

void PopTemplateManager::addHeadHair(IsoGameCharacter character,
                                     ModelManager.ModelSlot modelSlot,
                                     HumanVisual humanVisual,
                                     ItemVisual itemVisual, bool boolean0) {
  // TODO: Implement addHeadHair
}

void PopTemplateManager::populateCharacterModelSlot(
    IsoGameCharacter character, ModelManager.ModelSlot modelSlot) {
  // TODO: Implement populateCharacterModelSlot
}

bool PopTemplateManager::isItemModelHidden(BodyLocationGroup bodyLocationGroup,
                                           ItemVisuals itemVisuals,
                                           ItemVisual itemVisual) {
  // TODO: Implement isItemModelHidden
  return false;
}

std::string
PopTemplateManager::processModelFileName(const std::string &string) {
  // TODO: Implement processModelFileName
  return "";
}

void PopTemplateManager::postProcessNewItemInstance(
    ModelInstance modelInstance, ModelManager.ModelSlot modelSlot,
    ImmutableColor immutableColor) {
  // TODO: Implement postProcessNewItemInstance
}

} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
