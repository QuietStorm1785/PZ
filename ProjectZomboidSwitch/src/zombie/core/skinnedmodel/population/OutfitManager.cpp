#include <string>
#include <vector>
#include "zombie\core\skinnedmodel\population/OutfitManager.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {

void OutfitManager::init() {
    // TODO: Implement init
}

void OutfitManager::Reset() {
    // TODO: Implement Reset
}

void OutfitManager::loaded() {
    // TODO: Implement loaded
}

void OutfitManager::onClothingXmlFileChanged() {
    // TODO: Implement onClothingXmlFileChanged
}

void OutfitManager::Reload() {
    // TODO: Implement Reload
}

void OutfitManager::onReloaded(OutfitManager var1) {
    // TODO: Implement onReloaded
}

void OutfitManager::unload() {
    // TODO: Implement unload
}

void OutfitManager::addClothingItemListener(IClothingItemListener var1) {
    // TODO: Implement addClothingItemListener
}

void OutfitManager::removeClothingItemListener(IClothingItemListener var1) {
    // TODO: Implement removeClothingItemListener
}

void OutfitManager::invokeClothingItemChangedEvent(const std::string& var1) {
    // TODO: Implement invokeClothingItemChangedEvent
}

Outfit OutfitManager::GetRandomOutfit(bool var1) {
    // TODO: Implement GetRandomOutfit
    return nullptr;
}

Outfit OutfitManager::GetRandomNonProfessionalOutfit(bool var1) {
    // TODO: Implement GetRandomNonProfessionalOutfit
    return nullptr;
}

Outfit OutfitManager::GetSpecificOutfit(bool var1, const std::string& var2) {
    // TODO: Implement GetSpecificOutfit
    return nullptr;
}

OutfitManager OutfitManager::tryParse(const std::string& var0, const std::string& var1) {
    // TODO: Implement tryParse
    return nullptr;
}

return OutfitManager::parse() {
    // TODO: Implement parse
    return nullptr;
}

OutfitManager OutfitManager::parse(const std::string& var0, const std::string& var1) {
    // TODO: Implement parse
    return nullptr;
}

void OutfitManager::tryWrite(OutfitManager var0, const std::string& var1) {
    // TODO: Implement tryWrite
}

void OutfitManager::write(OutfitManager var0, const std::string& var1) {
    // TODO: Implement write
}

Outfit OutfitManager::FindMaleOutfit(const std::string& var1) {
    // TODO: Implement FindMaleOutfit
    return nullptr;
}

Outfit OutfitManager::FindFemaleOutfit(const std::string& var1) {
    // TODO: Implement FindFemaleOutfit
    return nullptr;
}

Outfit OutfitManager::FindOutfit(std::vector<Outfit> var1, const std::string& var2) {
    // TODO: Implement FindOutfit
    return nullptr;
}

ClothingItem OutfitManager::getClothingItem(const std::string& var1) {
    // TODO: Implement getClothingItem
    return nullptr;
}

std::string OutfitManager::extractClothingItemName(const std::string& var1) {
    // TODO: Implement extractClothingItemName
    return "";
}

void OutfitManager::onClothingItemFileChanged(ClothingItemEntry var1) {
    // TODO: Implement onClothingItemFileChanged
}

void OutfitManager::onClothingItemStateChanged(ClothingItem var1) {
    // TODO: Implement onClothingItemStateChanged
}

void OutfitManager::loadAllClothingItems() {
    // TODO: Implement loadAllClothingItems
}

bool OutfitManager::isLoadingClothingItems() {
    // TODO: Implement isLoadingClothingItems
    return false;
}

void OutfitManager::debugOutfits() {
    // TODO: Implement debugOutfits
}

void OutfitManager::debugOutfits(std::vector<Outfit> var1) {
    // TODO: Implement debugOutfits
}

void OutfitManager::debugOutfit(Outfit var1) {
    // TODO: Implement debugOutfit
}

} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
