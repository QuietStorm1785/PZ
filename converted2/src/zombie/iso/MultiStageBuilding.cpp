#include "zombie/iso/MultiStageBuilding.h"

namespace zombie {
namespace iso {

void MultiStageBuilding::addStage(MultiStageBuilding.Stage stage) {
  // TODO: Implement addStage
}

std::string MultiStageBuilding::getName() {
  // TODO: Implement getName
  return "";
}

std::string MultiStageBuilding::getDisplayName() {
  // TODO: Implement getDisplayName
  return "";
}

std::string MultiStageBuilding::getSprite() {
  // TODO: Implement getSprite
  return "";
}

std::string MultiStageBuilding::getNorthSprite() {
  // TODO: Implement getNorthSprite
  return "";
}

std::string MultiStageBuilding::getThumpSound() {
  // TODO: Implement getThumpSound
  return "";
}

std::string MultiStageBuilding::getRecipeName() {
  // TODO: Implement getRecipeName
  return "";
}

std::string MultiStageBuilding::getKnownRecipe() {
  // TODO: Implement getKnownRecipe
  return "";
}

int MultiStageBuilding::getTimeNeeded(IsoGameCharacter chr) {
  // TODO: Implement getTimeNeeded
  return 0;
}

std::string MultiStageBuilding::getCraftingSound() {
  // TODO: Implement getCraftingSound
  return "";
}

KahluaTable MultiStageBuilding::getItemsLua() {
  // TODO: Implement getItemsLua
  return nullptr;
}

KahluaTable MultiStageBuilding::getPerksLua() {
  // TODO: Implement getPerksLua
  return nullptr;
}

void MultiStageBuilding::doStage(IsoGameCharacter chr, IsoThumpable item,
                                 bool removeItems) {
  // TODO: Implement doStage
}

bool MultiStageBuilding::canBeDone(IsoGameCharacter chr, IsoObject itemClicked,
                                   bool cheat) {
  // TODO: Implement canBeDone
  return false;
}

void MultiStageBuilding::Load(const std::string &string0, String[] strings0) {
  // TODO: Implement Load
}

} // namespace iso
} // namespace zombie
