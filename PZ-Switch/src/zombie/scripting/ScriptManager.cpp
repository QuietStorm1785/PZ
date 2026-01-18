#include "zombie/scripting/ScriptManager.h"

namespace zombie {
namespace scripting {

void ScriptManager::ParseScript(const std::string &totalFile) {
 // TODO: Implement ParseScript
}

void ScriptManager::update() {
 // TODO: Implement update
}

void ScriptManager::LoadFile(const std::string &filename, bool bLoadJar) {
 // TODO: Implement LoadFile
}

void ScriptManager::CreateFromToken(const std::string &string0) {
 // TODO: Implement CreateFromToken
}

void ScriptManager::searchFolders(URI base, File fo,
 ArrayList<String> loadList) {
 // TODO: Implement searchFolders
}

std::string ScriptManager::getItemName(const std::string &name) {
 // TODO: Implement getItemName
 return "";
}

ScriptModule ScriptManager::getModule(const std::string &name) {
 // TODO: Implement getModule
 return nullptr;
}

ScriptModule ScriptManager::getModule(const std::string &name,
 bool defaultToBase) {
 // TODO: Implement getModule
 return nullptr;
}

ScriptModule ScriptManager::getModuleNoDisableCheck(const std::string &name) {
 // TODO: Implement getModuleNoDisableCheck
 return nullptr;
}

Item ScriptManager::getItem(const std::string &name) {
 // TODO: Implement getItem
 return nullptr;
}

Item ScriptManager::FindItem(const std::string &name) {
 // TODO: Implement FindItem
 return nullptr;
}

Item ScriptManager::FindItem(const std::string &name,
 bool moduleDefaultsToBase) {
 // TODO: Implement FindItem
 return nullptr;
}

bool ScriptManager::isDrainableItemType(const std::string &itemType) {
 // TODO: Implement isDrainableItemType
 return false;
}

Recipe ScriptManager::getRecipe(const std::string &name) {
 // TODO: Implement getRecipe
 return nullptr;
}

VehicleScript ScriptManager::getVehicle(const std::string &name) {
 // TODO: Implement getVehicle
 return nullptr;
}

VehicleTemplate ScriptManager::getVehicleTemplate(const std::string &name) {
 // TODO: Implement getVehicleTemplate
 return nullptr;
}

VehicleEngineRPM ScriptManager::getVehicleEngineRPM(const std::string &name) {
 // TODO: Implement getVehicleEngineRPM
 return nullptr;
}

void ScriptManager::CheckExitPoints() {
 // TODO: Implement CheckExitPoints
}

AnimationsMesh ScriptManager::getAnimationsMesh(const std::string &name) {
 // TODO: Implement getAnimationsMesh
 return nullptr;
}

MannequinScript ScriptManager::getMannequinScript(const std::string &name) {
 // TODO: Implement getMannequinScript
 return nullptr;
}

ModelScript ScriptManager::getModelScript(const std::string &name) {
 // TODO: Implement getModelScript
 return nullptr;
}

SoundTimelineScript
ScriptManager::getSoundTimeline(const std::string &eventName) {
 // TODO: Implement getSoundTimeline
 return nullptr;
}

void ScriptManager::Reset() {
 // TODO: Implement Reset
}

std::string ScriptManager::getChecksum() {
 // TODO: Implement getChecksum
 return "";
}

std::string ScriptManager::getCurrentLoadFileMod() {
 // TODO: Implement getCurrentLoadFileMod
 return "";
}

std::string ScriptManager::getCurrentLoadFileAbsPath() {
 // TODO: Implement getCurrentLoadFileAbsPath
 return "";
}

void ScriptManager::Load() {
 // TODO: Implement Load
}

int ScriptManager::compare(const std::string &string1,
 const std::string &string3) {
 // TODO: Implement compare
 return 0;
}

void ScriptManager::debugItems() {
 // TODO: Implement debugItems
}

std::string
ScriptManager::getItemTypeForClothingItem(const std::string &clothingItem) {
 // TODO: Implement getItemTypeForClothingItem
 return "";
}

Item ScriptManager::getItemForClothingItem(const std::string &clothingName) {
 // TODO: Implement getItemForClothingItem
 return nullptr;
}

void ScriptManager::createZedDmgMap() {
 // TODO: Implement createZedDmgMap
}

void ScriptManager::createClothingItemMap() {
 // TODO: Implement createClothingItemMap
}

void ScriptManager::resolveItemTypes() {
 // TODO: Implement resolveItemTypes
}

std::string ScriptManager::resolveItemType(ScriptModule module,
 const std::string &itemType) {
 // TODO: Implement resolveItemType
 return "";
}

std::string
ScriptManager::resolveModelScript(ScriptModule module,
 const std::string &modelScriptName) {
 // TODO: Implement resolveModelScript
 return "";
}

Item ScriptManager::getSpecificItem(const std::string &name) {
 // TODO: Implement getSpecificItem
 return nullptr;
}

} // namespace scripting
} // namespace zombie
