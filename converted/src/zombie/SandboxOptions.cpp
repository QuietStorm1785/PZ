#include "zombie/SandboxOptions.h"

namespace zombie {

public SandboxOptions::SandboxOptions() {
 // TODO: Implement SandboxOptions
 return nullptr;
}

SandboxOptions SandboxOptions::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

void SandboxOptions::toLua() {
 // TODO: Implement toLua
}

void SandboxOptions::updateFromLua() {
 // TODO: Implement updateFromLua
}

void SandboxOptions::initSandboxVars() {
 // TODO: Implement initSandboxVars
}

int SandboxOptions::randomWaterShut(int waterShutoffModifier) {
 // TODO: Implement randomWaterShut
 return 0;
}

int SandboxOptions::randomElectricityShut(int electricityShutoffModifier) {
 // TODO: Implement randomElectricityShut
 return 0;
}

int SandboxOptions::getTemperatureModifier() {
 // TODO: Implement getTemperatureModifier
 return 0;
}

int SandboxOptions::getRainModifier() {
 // TODO: Implement getRainModifier
 return 0;
}

int SandboxOptions::getErosionSpeed() {
 // TODO: Implement getErosionSpeed
 return 0;
}

int SandboxOptions::getFoodLootModifier() {
 // TODO: Implement getFoodLootModifier
 return 0;
}

int SandboxOptions::getWeaponLootModifier() {
 // TODO: Implement getWeaponLootModifier
 return 0;
}

int SandboxOptions::getOtherLootModifier() {
 // TODO: Implement getOtherLootModifier
 return 0;
}

int SandboxOptions::getWaterShutModifier() {
 // TODO: Implement getWaterShutModifier
 return 0;
}

int SandboxOptions::getElecShutModifier() {
 // TODO: Implement getElecShutModifier
 return 0;
}

int SandboxOptions::getTimeSinceApo() {
 // TODO: Implement getTimeSinceApo
 return 0;
}

double SandboxOptions::getEnduranceRegenMultiplier() {
 // TODO: Implement getEnduranceRegenMultiplier
 return 0;
}

double SandboxOptions::getStatsDecreaseMultiplier() {
 // TODO: Implement getStatsDecreaseMultiplier
 return 0;
}

int SandboxOptions::getDayLengthMinutes() {
 // TODO: Implement getDayLengthMinutes
 return 0;
}

int SandboxOptions::getDayLengthMinutesDefault() {
 // TODO: Implement getDayLengthMinutesDefault
 return 0;
}

int SandboxOptions::getCompostHours() {
 // TODO: Implement getCompostHours
 return 0;
}

void SandboxOptions::applySettings() {
 // TODO: Implement applySettings
}

void SandboxOptions::save(ByteBuffer output) {
 // TODO: Implement save
}

void SandboxOptions::load(ByteBuffer input) {
 // TODO: Implement load
}

int SandboxOptions::getFirstYear() {
 // TODO: Implement getFirstYear
 return 0;
}

SandboxOptions SandboxOptions::addOption(SandboxOptions.SandboxOption sandboxOption) {
 // TODO: Implement addOption
 return nullptr;
}

int SandboxOptions::getNumOptions() {
 // TODO: Implement getNumOptions
 return 0;
}

void SandboxOptions::set(const std::string& name, void* o) {
 // TODO: Implement set
}

void SandboxOptions::copyValuesFrom(SandboxOptions other) {
 // TODO: Implement copyValuesFrom
}

void SandboxOptions::resetToDefault() {
 // TODO: Implement resetToDefault
}

void SandboxOptions::setDefaultsToCurrentValues() {
 // TODO: Implement setDefaultsToCurrentValues
}

SandboxOptions SandboxOptions::newCopy() {
 // TODO: Implement newCopy
 return nullptr;
}

bool SandboxOptions::isValidPresetName(const std::string& name) {
 // TODO: Implement isValidPresetName
 return false;
}

bool SandboxOptions::readTextFile(const std::string& string0, bool boolean0) {
 // TODO: Implement readTextFile
 return false;
}

bool SandboxOptions::writeTextFile(const std::string& string, int int0) {
 // TODO: Implement writeTextFile
 return false;
}

bool SandboxOptions::loadServerTextFile(const std::string& serverName) {
 // TODO: Implement loadServerTextFile
 return false;
}

bool SandboxOptions::loadServerLuaFile(const std::string& serverName) {
 // TODO: Implement loadServerLuaFile
 return false;
}

bool SandboxOptions::saveServerLuaFile(const std::string& serverName) {
 // TODO: Implement saveServerLuaFile
 return false;
}

bool SandboxOptions::loadPresetFile(const std::string& presetName) {
 // TODO: Implement loadPresetFile
 return false;
}

bool SandboxOptions::savePresetFile(const std::string& presetName) {
 // TODO: Implement savePresetFile
 return false;
}

bool SandboxOptions::loadGameFile(const std::string& presetName) {
 // TODO: Implement loadGameFile
 return false;
}

bool SandboxOptions::saveGameFile(const std::string& presetName) {
 // TODO: Implement saveGameFile
 return false;
}

void SandboxOptions::saveCurrentGameBinFile() {
 // TODO: Implement saveCurrentGameBinFile
}

void SandboxOptions::handleOldZombiesFile1() {
 // TODO: Implement handleOldZombiesFile1
}

void SandboxOptions::handleOldZombiesFile2() {
 // TODO: Implement handleOldZombiesFile2
}

void SandboxOptions::handleOldServerZombiesFile() {
 // TODO: Implement handleOldServerZombiesFile
}

bool SandboxOptions::loadServerZombiesFile(const std::string& serverName) {
 // TODO: Implement loadServerZombiesFile
 return false;
}

bool SandboxOptions::readLuaFile(const std::string& string) {
 // TODO: Implement readLuaFile
 return false;
}

bool SandboxOptions::writeLuaFile(const std::string& string0, bool boolean0) {
 // TODO: Implement writeLuaFile
 return false;
}

void SandboxOptions::load() {
 // TODO: Implement load
}

void SandboxOptions::loadCurrentGameBinFile() {
 // TODO: Implement loadCurrentGameBinFile
}

std::string SandboxOptions::upgradeOptionName(const std::string& string, int var2) {
 // TODO: Implement upgradeOptionName
 return "";
}

std::string SandboxOptions::upgradeOptionValue(const std::string& string0, const std::string& string1, int int0) {
 // TODO: Implement upgradeOptionValue
 return "";
}

KahluaTable SandboxOptions::upgradeLuaTable(const std::string& object, KahluaTable table1, int int0) {
 // TODO: Implement upgradeLuaTable
 return nullptr;
}

void SandboxOptions::sendToServer() {
 // TODO: Implement sendToServer
}

void SandboxOptions::newCustomOption(CustomSandboxOption customSandboxOption) {
 // TODO: Implement newCustomOption
}

void SandboxOptions::addCustomOption(SandboxOptions.SandboxOption sandboxOption, CustomSandboxOption customSandboxOption) {
 // TODO: Implement addCustomOption
}

void SandboxOptions::removeCustomOptions() {
 // TODO: Implement removeCustomOptions
}

void SandboxOptions::Reset() {
 // TODO: Implement Reset
}

bool SandboxOptions::getAllClothesUnlocked() {
 // TODO: Implement getAllClothesUnlocked
 return false;
}

public SandboxOptions::BooleanSandboxOption(SandboxOptions owner, const std::string& name, bool defaultValue) {
 // TODO: Implement BooleanSandboxOption
 return nullptr;
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

public SandboxOptions::DoubleSandboxOption(SandboxOptions owner, const std::string& name, double min, double max, double defaultValue) {
 // TODO: Implement DoubleSandboxOption
 return nullptr;
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

public SandboxOptions::EnumSandboxOption(SandboxOptions owner, const std::string& name, int numValues, int defaultValue) {
 // TODO: Implement EnumSandboxOption
 return nullptr;
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

std::string SandboxOptions::getValueTranslation() {
 // TODO: Implement getValueTranslation
 return "";
}

std::string SandboxOptions::getValueTranslationByIndex(int index) {
 // TODO: Implement getValueTranslationByIndex
 return "";
}

std::string SandboxOptions::getValueTranslationByIndexOrNull(int index) {
 // TODO: Implement getValueTranslationByIndexOrNull
 return "";
}

public SandboxOptions::IntegerSandboxOption(SandboxOptions owner, const std::string& name, int min, int max, int defaultValue) {
 // TODO: Implement IntegerSandboxOption
 return nullptr;
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

public SandboxOptions::StringSandboxOption(SandboxOptions owner, const std::string& name, const std::string& defaultValue, int maxLength) {
 // TODO: Implement StringSandboxOption
 return nullptr;
}

ConfigOption SandboxOptions::asConfigOption() {
 // TODO: Implement asConfigOption
 return nullptr;
}

std::string SandboxOptions::getShortName() {
 // TODO: Implement getShortName
 return "";
}

std::string SandboxOptions::getTableName() {
 // TODO: Implement getTableName
 return "";
}

std::string SandboxOptions::getTranslatedName() {
 // TODO: Implement getTranslatedName
 return "";
}

std::string SandboxOptions::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void SandboxOptions::fromTable(KahluaTable table) {
 // TODO: Implement fromTable
}

void SandboxOptions::toTable(KahluaTable table) {
 // TODO: Implement toTable
}

void SandboxOptions::setCustom() {
 // TODO: Implement setCustom
}

bool SandboxOptions::isCustom() {
 // TODO: Implement isCustom
 return false;
}

std::string SandboxOptions::getPageName() {
 // TODO: Implement getPageName
 return "";
}

private SandboxOptions::ZombieConfig() {
 // TODO: Implement ZombieConfig
 return nullptr;
}

private SandboxOptions::ZombieLore() {
 // TODO: Implement ZombieLore
 return nullptr;
}

} // namespace zombie
