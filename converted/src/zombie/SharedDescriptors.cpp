#include "zombie/SharedDescriptors.h"

namespace zombie {

void SharedDescriptors::initSharedDescriptors() {
  // TODO: Implement initSharedDescriptors
}

void SharedDescriptors::noise(const std::string &string) {
  // TODO: Implement noise
}

void SharedDescriptors::createPlayerZombieDescriptor(IsoZombie zombie0) {
  // TODO: Implement createPlayerZombieDescriptor
}

void SharedDescriptors::releasePlayerZombieDescriptor(IsoZombie zombie0) {
  // TODO: Implement releasePlayerZombieDescriptor
}

void SharedDescriptors::registerPlayerZombieDescriptor(
    SharedDescriptors.Descriptor descriptor) {
  // TODO: Implement registerPlayerZombieDescriptor
}

void SharedDescriptors::ApplyReanimatedPlayerOutfit(
    int int0, const std::string &var1, IsoGameCharacter character) {
  // TODO: Implement ApplyReanimatedPlayerOutfit
}

int SharedDescriptors::getID() {
  // TODO: Implement getID
  return 0;
}

int SharedDescriptors::getPersistentOutfitID() {
  // TODO: Implement getPersistentOutfitID
  return 0;
}

HumanVisual SharedDescriptors::getHumanVisual() {
  // TODO: Implement getHumanVisual
  return nullptr;
}

void SharedDescriptors::getItemVisuals(ItemVisuals _itemVisuals) {
  // TODO: Implement getItemVisuals
}

bool SharedDescriptors::isFemale() {
  // TODO: Implement isFemale
  return false;
}

bool SharedDescriptors::isZombie() {
  // TODO: Implement isZombie
  return false;
}

bool SharedDescriptors::isSkeleton() {
  // TODO: Implement isSkeleton
  return false;
}

void SharedDescriptors::save(ByteBuffer output) {
  // TODO: Implement save
}

void SharedDescriptors::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

} // namespace zombie
