#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

void ModelInstanceTextureCreator::init(IsoGameCharacter chr) {
  // TODO: Implement init
}

void ModelInstanceTextureCreator::init(BaseVisual baseVisual,
                                       ItemVisuals _itemVisuals,
                                       ModelInstance chrModelInstance) {
  // TODO: Implement init
}

void ModelInstanceTextureCreator::init(HumanVisual humanVisual,
                                       ItemVisuals _itemVisuals,
                                       ModelInstance chrModelInstance) {
  // TODO: Implement init
}

ModelInstance ModelInstanceTextureCreator::findModelInstance(
    ArrayList<ModelInstance> arrayList, ItemVisual itemVisual1) {
  // TODO: Implement findModelInstance
  return nullptr;
}

void ModelInstanceTextureCreator::addClothingItem(ModelInstance modelInstance,
                                                  ItemVisual itemVisual,
                                                  ClothingItem clothingItem,
                                                  CharacterMask characterMask,
                                                  const std::string &string1) {
  // TODO: Implement addClothingItem
}

void ModelInstanceTextureCreator::render() {
  // TODO: Implement render
}

CharacterSmartTexture
ModelInstanceTextureCreator::createFullCharacterTexture() {
  // TODO: Implement createFullCharacterTexture
  return nullptr;
}

void ModelInstanceTextureCreator::applyCharacterTexture(
    Texture texture, CharacterSmartTexture characterSmartTexturex) {
  // TODO: Implement applyCharacterTexture
}

bool ModelInstanceTextureCreator::isSimpleTexture(
    ModelInstanceTextureCreator.ItemData itemDatax) {
  // TODO: Implement isSimpleTexture
  return false;
}

ItemSmartTexture ModelInstanceTextureCreator::createFullItemTexture(
    ModelInstanceTextureCreator.ItemData itemDatax) {
  // TODO: Implement createFullItemTexture
  return nullptr;
}

bool ModelInstanceTextureCreator::isItemSmartTextureRequired(
    ModelInstanceTextureCreator.ItemData itemDatax) {
  // TODO: Implement isItemSmartTextureRequired
  return false;
}

void ModelInstanceTextureCreator::applyItemTexture(
    ModelInstanceTextureCreator.ItemData itemDatax, Texture texture,
    SmartTexture smartTexture) {
  // TODO: Implement applyItemTexture
}

void ModelInstanceTextureCreator::postRender() {
  // TODO: Implement postRender
}

bool ModelInstanceTextureCreator::isRendered() {
  // TODO: Implement isRendered
  return false;
}

Texture
ModelInstanceTextureCreator::getTextureWithFlags(const std::string &string) {
  // TODO: Implement getTextureWithFlags
  return nullptr;
}

ModelInstanceTextureCreator ModelInstanceTextureCreator::alloc() {
  // TODO: Implement alloc
  return nullptr;
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
