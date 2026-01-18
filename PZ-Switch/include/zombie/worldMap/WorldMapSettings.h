#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapSettings {
public:
 static int VERSION1 = 1;
 static int VERSION = VERSION1;
 static WorldMapSettings instance;
 ArrayList<ConfigOption> m_options = std::make_unique<ArrayList<>>();
 WorldMapSettings.WorldMap mWorldMap = new WorldMapSettings.WorldMap();
 WorldMapSettings.MiniMap mMiniMap = new WorldMapSettings.MiniMap();
 int m_readVersion = 0;

 static WorldMapSettings getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<WorldMapSettings>();
 instance.load();
 }

 return instance;
 }

 BooleanConfigOption newOption(const std::string &string, bool boolean0) {
 BooleanConfigOption booleanConfigOption =
 new BooleanConfigOption(string, boolean0);
 this->m_options.add(booleanConfigOption);
 return booleanConfigOption;
 }

 DoubleConfigOption newOption(const std::string &string, double double0,
 double double1, double double2) {
 DoubleConfigOption doubleConfigOption =
 new DoubleConfigOption(string, double0, double1, double2);
 this->m_options.add(doubleConfigOption);
 return doubleConfigOption;
 }

 ConfigOption getOptionByName(const std::string &string) {
 for (int int0 = 0; int0 < this->m_options.size(); int0++) {
 ConfigOption configOption = this->m_options.get(int0);
 if (configOption.getName() == string) {
 return configOption;
 }
 }

 return nullptr;
 }

 int getOptionCount() { return this->m_options.size(); }

 ConfigOption getOptionByIndex(int int0) { return this->m_options.get(int0); }

 void setBoolean(const std::string &string, bool boolean0) {
 ConfigOption configOption = this->getOptionByName(string);
 if (configOption instanceof BooleanConfigOption) {
 ((BooleanConfigOption)configOption).setValue(boolean0);
 }
 }

 bool getBoolean(const std::string &string) {
 ConfigOption configOption = this->getOptionByName(string);
 return configOption instanceof
 BooleanConfigOption ? ((BooleanConfigOption)configOption).getValue()
 : false;
 }

 void setDouble(const std::string &string, double double0) {
 ConfigOption configOption = this->getOptionByName(string);
 if (configOption instanceof DoubleConfigOption) {
 ((DoubleConfigOption)configOption).setValue(double0);
 }
 }

 double getDouble(const std::string &string, double double0) {
 ConfigOption configOption = this->getOptionByName(string);
 return configOption instanceof
 DoubleConfigOption ? ((DoubleConfigOption)configOption).getValue()
 : double0;
 }

 int getFileVersion() { return this->m_readVersion; }

 void save() {
 std::string string =
 ZomboidFileSystem.instance.getFileNameInCurrentSave("InGameMap.ini");
 ConfigFile configFile = new ConfigFile();
 configFile.write(string, VERSION, this->m_options);
 this->m_readVersion = VERSION;
 }

 void load() {
 this->m_readVersion = 0;
 std::string string =
 ZomboidFileSystem.instance.getFileNameInCurrentSave("InGameMap.ini");
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 this->m_readVersion = configFile.getVersion();
 if (this->m_readVersion >= VERSION1 && this->m_readVersion <= VERSION) {
 for (int int0 = 0; int0 < configFile.getOptions().size(); int0++) {
 ConfigOption configOption0 = configFile.getOptions().get(int0);

 try {
 ConfigOption configOption1 =
 this->getOptionByName(configOption0.getName());
 if (configOption1 != nullptr) {
 configOption1.parse(configOption0.getValueAsString());
 }
 } catch (Exception exception) {
 }
 }
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.m_options.clear();
 instance = nullptr;
 }
 }

class MiniMap {
 DoubleConfigOption Zoom =
 WorldMapSettings.this->newOption("MiniMap.Zoom", 0.0, 24.0, 19.0);
 BooleanConfigOption Isometric =
 WorldMapSettings.this->newOption("MiniMap.Isometric", true);
 BooleanConfigOption ShowSymbols =
 WorldMapSettings.this->newOption("MiniMap.ShowSymbols", false);
 BooleanConfigOption StartVisible =
 WorldMapSettings.this->newOption("MiniMap.StartVisible", true);
 }

 class WorldMap {
 DoubleConfigOption CenterX = WorldMapSettings.this->newOption(
 "WorldMap.CenterX", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
 DoubleConfigOption CenterY = WorldMapSettings.this->newOption(
 "WorldMap.CenterY", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
 DoubleConfigOption Zoom =
 WorldMapSettings.this->newOption("WorldMap.Zoom", 0.0, 24.0, 0.0);
 BooleanConfigOption Isometric =
 WorldMapSettings.this->newOption("WorldMap.Isometric", true);
 BooleanConfigOption ShowSymbolsUI =
 WorldMapSettings.this->newOption("WorldMap.ShowSymbolsUI", true);
 }
}
} // namespace worldMap
} // namespace zombie
