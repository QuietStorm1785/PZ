#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/worldMap/WorldMapSettings/MiniMap.h"
#include "zombie/worldMap/WorldMapSettings/WorldMap.h"

namespace zombie {
namespace worldMap {


class WorldMapSettings {
public:
    static int VERSION1 = 1;
    static int VERSION = VERSION1;
    static WorldMapSettings instance;
   final ArrayList<ConfigOption> m_options = std::make_unique<ArrayList<>>();
    const WorldMap mWorldMap = new WorldMap(this);
    const MiniMap mMiniMap = new MiniMap(this);
    int m_readVersion = 0;

    static WorldMapSettings getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<WorldMapSettings>();
         instance.load();
      }

    return instance;
   }

    BooleanConfigOption newOption(const std::string& var1, bool var2) {
    BooleanConfigOption var3 = new BooleanConfigOption(var1, var2);
      this.m_options.add(var3);
    return var3;
   }

    DoubleConfigOption newOption(const std::string& var1, double var2, double var4, double var6) {
    DoubleConfigOption var8 = new DoubleConfigOption(var1, var2, var4, var6);
      this.m_options.add(var8);
    return var8;
   }

    ConfigOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_options.size(); var2++) {
    ConfigOption var3 = this.m_options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return null;
   }

    int getOptionCount() {
      return this.m_options.size();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.m_options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    ConfigOption var3 = this.getOptionByName(var1);
      if (var3 instanceof BooleanConfigOption) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    ConfigOption var2 = this.getOptionByName(var1);
      return var2 instanceof BooleanConfigOption ? ((BooleanConfigOption)var2).getValue() : false;
   }

    void setDouble(const std::string& var1, double var2) {
    ConfigOption var4 = this.getOptionByName(var1);
      if (var4 instanceof DoubleConfigOption) {
         ((DoubleConfigOption)var4).setValue(var2);
      }
   }

    double getDouble(const std::string& var1, double var2) {
    ConfigOption var4 = this.getOptionByName(var1);
      return var4 instanceof DoubleConfigOption ? ((DoubleConfigOption)var4).getValue() : var2;
   }

    int getFileVersion() {
      return this.m_readVersion;
   }

    void save() {
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("InGameMap.ini");
    ConfigFile var2 = new ConfigFile();
      var2.write(var1, VERSION, this.m_options);
      this.m_readVersion = VERSION;
   }

    void load() {
      this.m_readVersion = 0;
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("InGameMap.ini");
    ConfigFile var2 = new ConfigFile();
      if (var2.read(var1)) {
         this.m_readVersion = var2.getVersion();
         if (this.m_readVersion >= VERSION1 && this.m_readVersion <= VERSION) {
            for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);

               try {
    ConfigOption var5 = this.getOptionByName(var4.getName());
                  if (var5 != nullptr) {
                     var5.parse(var4.getValueAsString());
                  }
               } catch (Exception var6) {
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
}
} // namespace worldMap
} // namespace zombie
