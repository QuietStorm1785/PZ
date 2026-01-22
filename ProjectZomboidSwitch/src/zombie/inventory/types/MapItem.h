#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/SliceY.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/worldMap/symbols/WorldMapSymbols.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class MapItem : public InventoryItem {
public:
    static MapItem WORLD_MAP_INSTANCE;
   private static const byte[] FILE_MAGIC = new byte[]{87, 77, 83, 89};
    std::string m_mapID;
    const WorldMapSymbols m_symbols = std::make_shared<WorldMapSymbols>();

    static MapItem getSingleton() {
      if (WORLD_MAP_INSTANCE == nullptr) {
    Item var0 = ScriptManager.instance.FindItem("Base.Map");
         if (var0 == nullptr) {
    return nullptr;
         }

         WORLD_MAP_INSTANCE = std::make_shared<MapItem>("Base", "World Map", "WorldMap", var0);
      }

    return WORLD_MAP_INSTANCE;
   }

    static void SaveWorldMap() {
      if (WORLD_MAP_INSTANCE != nullptr) {
         try {
    ByteBuffer var0 = SliceY.SliceBuffer;
            var0.clear();
            var0.put(FILE_MAGIC);
            var0.putInt(195);
            WORLD_MAP_INSTANCE.getSymbols().save(var0);
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_symbols.bin"));

            try (
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var1);
    BufferedOutputStream var3 = std::make_shared<BufferedOutputStream>(var2);
            ) {
               var3.write(var0.array(), 0, var0.position());
            }
         } catch (Exception var10) {
            ExceptionLogger.logException(var10);
         }
      }
   }

    static void LoadWorldMap() {
      if (getSingleton() != nullptr) {
    File var0 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_symbols.bin"));

         try (
    FileInputStream var1 = std::make_shared<FileInputStream>(var0);
    BufferedInputStream var2 = std::make_shared<BufferedInputStream>(var1);
         ) {
    ByteBuffer var3 = SliceY.SliceBuffer;
            var3.clear();
    int var4 = var2.read(var3.array());
            var3.limit(var4);
            byte[] var5 = new byte[4];
            var3.get(var5);
            if (!Arrays == var5, FILE_MAGIC)) {
               throw IOException(var0.getAbsolutePath() + " does not appear to be map_symbols.bin");
            }

    int var6 = var3.getInt();
            getSingleton().getSymbols().load(var3, var6);
         } catch (FileNotFoundException var11) {
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }
      }
   }

    static void Reset() {
      if (WORLD_MAP_INSTANCE != nullptr) {
         WORLD_MAP_INSTANCE.getSymbols().clear();
         WORLD_MAP_INSTANCE = nullptr;
      }
   }

    public MapItem(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
   }

    public MapItem(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
   }

    int getSaveType() {
      return Type.Map.ordinal();
   }

    bool IsMap() {
    return true;
   }

    void setMapID(const std::string& var1) {
      this.m_mapID = var1;
   }

    std::string getMapID() {
      return this.m_mapID;
   }

    WorldMapSymbols getSymbols() {
      return this.m_symbols;
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      GameWindow.WriteString(var1, this.m_mapID);
      this.m_symbols.save(var1);
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.m_mapID = GameWindow.ReadString(var1);
      this.m_symbols.load(var1, var2);
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
