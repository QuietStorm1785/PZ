#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/io/Files.h"
#include "java/time/Instant.h"
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/world/logger/Log/ModIDChangedItem.h"
#include "zombie/world/logger/Log/ObsoleteItem.h"
#include "zombie/world/logger/Log/RegisterItem.h"
#include "zombie/world/logger/Log/RegisterObject.h"
#include "zombie/world/logger/Log/ReinstateItem.h"
#include "zombie/world/logger/Log/RemovedItem.h"
#include "zombie/world/logger/WorldDictionaryLogger.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {


class DictionaryData {
public:
   protected final Map<Short, ItemInfo> itemIdToInfoMap = std::make_unique<HashMap<>>();
   protected final Map<String, ItemInfo> itemTypeToInfoMap = std::make_unique<HashMap<>>();
   protected final Map<String, Integer> spriteNameToIdMap = std::make_unique<HashMap<>>();
   protected final Map<Integer, String> spriteIdToNameMap = std::make_unique<HashMap<>>();
   protected final Map<String, Byte> objectNameToIdMap = std::make_unique<HashMap<>>();
   protected final Map<Byte, String> objectIdToNameMap = std::make_unique<HashMap<>>();
   protected final ArrayList<String> unsetObject = std::make_unique<ArrayList<>>();
   protected final ArrayList<String> unsetSprites = std::make_unique<ArrayList<>>();
    short NextItemID = 0;
    int NextSpriteNameID = 0;
    uint8_t NextObjectNameID = 0;
   protected byte[] serverDataCache;
    File dataBackupPath;

    bool isClient() {
    return false;
   }

    void reset() {
      this.NextItemID = 0;
      this.NextSpriteNameID = 0;
      this.NextObjectNameID = 0;
      this.itemIdToInfoMap.clear();
      this.itemTypeToInfoMap.clear();
      this.objectIdToNameMap.clear();
      this.objectNameToIdMap.clear();
      this.spriteIdToNameMap.clear();
      this.spriteNameToIdMap.clear();
   }

    ItemInfo getItemInfoFromType(const std::string& var1) {
      return this.itemTypeToInfoMap.get(var1);
   }

    ItemInfo getItemInfoFromID(short var1) {
      return this.itemIdToInfoMap.get(var1);
   }

    short getItemRegistryID(const std::string& var1) {
    ItemInfo var2 = this.itemTypeToInfoMap.get(var1);
      if (var2 != nullptr) {
         return var2.registryID;
      } else {
         if (Core.bDebug) {
            DebugLog.log("WARNING: Cannot get registry id for item: " + var1);
         }

         return -1;
      }
   }

    std::string getItemTypeFromID(short var1) {
    ItemInfo var2 = this.itemIdToInfoMap.get(var1);
      return var2 != nullptr ? var2.fullType : nullptr;
   }

    std::string getItemTypeDebugString(short var1) {
    std::string var2 = this.getItemTypeFromID(var1);
      if (var2 == nullptr) {
         var2 = "Unknown";
      }

    return var2;
   }

    std::string getSpriteNameFromID(int var1) {
      if (var1 >= 0) {
         if (this.spriteIdToNameMap.containsKey(var1)) {
            return this.spriteIdToNameMap.get(var1);
         }

    IsoSprite var2 = IsoSprite.getSprite(IsoSpriteManager.instance, var1);
         if (var2 != nullptr && var2.name != nullptr) {
            return var2.name;
         }
      }

      DebugLog.log("WorldDictionary, Couldnt find sprite name for ID '" + var1 + "'.");
    return null;
   }

    int getIdForSpriteName(const std::string& var1) {
      if (var1 != nullptr) {
         if (this.spriteNameToIdMap.containsKey(var1)) {
            return this.spriteNameToIdMap.get(var1);
         }

    IsoSprite var2 = IsoSpriteManager.instance.getSprite(var1);
         if (var2 != nullptr && var2.ID >= 0 && var2.ID != 20000000 && var2.name == var1)) {
            return var2.ID;
         }
      }

      return -1;
   }

    std::string getObjectNameFromID(uint8_t var1) {
      if (var1 >= 0) {
         if (this.objectIdToNameMap.containsKey(var1)) {
            return this.objectIdToNameMap.get(var1);
         }

         if (Core.bDebug) {
            DebugLog.log("WorldDictionary, Couldnt find object name for ID '" + var1 + "'.");
         }
      }

    return null;
   }

    uint8_t getIdForObjectName(const std::string& var1) {
      if (var1 != nullptr) {
         if (this.objectNameToIdMap.containsKey(var1)) {
            return this.objectNameToIdMap.get(var1);
         }

         if (Core.bDebug) {
         }
      }

      return -1;
   }

    void getItemMods(List<String> var1) {
      var1.clear();

      for (Entry var3 : this.itemIdToInfoMap.entrySet()) {
         if (!var1.contains((static_cast<ItemInfo>(var3).getValue()).modID)) {
            var1.add((static_cast<ItemInfo>(var3).getValue()).modID);
         }

         if ((static_cast<ItemInfo>(var3).getValue()).modOverrides != nullptr) {
    std::vector var4 = (static_cast<ItemInfo>(var3).getValue()).modOverrides;

            for (int var5 = 0; var5 < var4.size(); var5++) {
               if (!var1.contains(var4.get(var5))) {
                  var1.add(static_cast<String>(var4).get(var5));
               }
            }
         }
      }
   }

    void getModuleList(List<String> var1) {
      for (Entry var3 : this.itemIdToInfoMap.entrySet()) {
         if (!var1.contains((static_cast<ItemInfo>(var3).getValue()).moduleName)) {
            var1.add((static_cast<ItemInfo>(var3).getValue()).moduleName);
         }
      }
   }

    void parseItemLoadList(ItemInfo> var1) {
      for (Entry var3 : var1.entrySet()) {
    ItemInfo var4 = static_cast<ItemInfo>(var3).getValue();
    ItemInfo var5 = this.itemTypeToInfoMap.get(var4.fullType);
         if (var5 == nullptr) {
            if (!var4.obsolete) {
               if (this.NextItemID >= 32767) {
                  throw new WorldDictionaryException("Max item ID value reached for WorldDictionary!");
               }

               var4.registryID = this.NextItemID++;
               var4.isLoaded = true;
               this.itemTypeToInfoMap.put(var4.fullType, var4);
               this.itemIdToInfoMap.put(var4.registryID, var4);
               WorldDictionaryLogger.log(new RegisterItem(var4.copy()));
            }
         } else {
            if (var5.removed && !var4.obsolete) {
               var5.removed = false;
               WorldDictionaryLogger.log(new ReinstateItem(var5.copy()));
            }

            if (!var5.modID == var4.modID)) {
    std::string var6 = var5.modID;
               var5.modID = var4.modID;
               var5.isModded = !var4.modID == "pz-vanilla");
               WorldDictionaryLogger.log(new ModIDChangedItem(var5.copy(), var6, var5.modID));
            }

            if (var4.obsolete && (!var5.obsolete || !var5.removed)) {
               var5.obsolete = true;
               var5.removed = true;
               WorldDictionaryLogger.log(new ObsoleteItem(var5.copy()));
            }

            var5.isLoaded = true;
         }
      }
   }

    void parseCurrentItemSet() {
      for (Entry var2 : this.itemTypeToInfoMap.entrySet()) {
    ItemInfo var3 = static_cast<ItemInfo>(var2).getValue();
         if (!var3.isLoaded) {
            var3.removed = true;
            WorldDictionaryLogger.log(new RemovedItem(var3.copy(), false));
         }

         if (var3.scriptItem == nullptr) {
            var3.scriptItem = ScriptManager.instance.getSpecificItem(var3.fullType);
         }

         if (var3.scriptItem != nullptr) {
            var3.scriptItem.setRegistry_id(var3.registryID);
         } else {
            var3.removed = true;
            WorldDictionaryLogger.log(new RemovedItem(var3.copy(), true));
         }
      }
   }

    void parseObjectNameLoadList(List<String> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = static_cast<String>(var1).get(var2);
         if (!this.objectNameToIdMap.containsKey(var3)) {
            if (this.NextObjectNameID >= 127) {
               WorldDictionaryLogger.log("Max value for object names reached.");
               if (Core.bDebug) {
                  throw new WorldDictionaryException("Max value for object names reached.");
               }
            } else {
    uint8_t var4 = this.NextObjectNameID++;
               this.objectIdToNameMap.put(var4, var3);
               this.objectNameToIdMap.put(var3, var4);
               WorldDictionaryLogger.log(new RegisterObject(var3, var4));
            }
         }
      }
   }

    void backupCurrentDataSet() {
      this.dataBackupPath = nullptr;
      if (!Core.getInstance().isNoSave()) {
    auto var1 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary.bin"));
         if (var1.exists()) {
    long var2 = Instant.now().getEpochSecond();
            this.dataBackupPath = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary_" + var2 + ".bak"));
            Files.copy(var1, this.dataBackupPath);
         }
      }
   }

    void deleteBackupCurrentDataSet() {
      if (Core.getInstance().isNoSave()) {
         this.dataBackupPath = nullptr;
      } else {
         if (this.dataBackupPath != nullptr) {
            this.dataBackupPath.delete();
         }

         this.dataBackupPath = nullptr;
      }
   }

    void createErrorBackups() {
      if (!Core.getInstance().isNoSave()) {
         try {
            WorldDictionary.log("Attempting to copy WorldDictionary backups...");
    long var1 = Instant.now().getEpochSecond();
    std::string var3 = ZomboidFileSystem.instance.getFileNameInCurrentSave("WD_ERROR_" + var1) + File.separator;
            WorldDictionary.log("path = " + var3);
    auto var4 = std::make_shared<File>(var3);
    bool var5 = true;
            if (!var4.exists()) {
               var5 = var4.mkdir();
            }

            if (!var5) {
               WorldDictionary.log("Could not create backup folder folder.");
               return;
            }

            if (this.dataBackupPath != nullptr) {
    auto var6 = std::make_shared<File>(var3 + "WorldDictionary_backup.bin");
               if (this.dataBackupPath.exists()) {
                  Files.copy(this.dataBackupPath, var6);
               }
            }

    auto var13 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionaryLog.lua"));
    auto var7 = std::make_shared<File>(var3 + "WorldDictionaryLog.lua");
            if (var13.exists()) {
               Files.copy(var13, var7);
            }

    auto var8 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionaryReadable.lua"));
    auto var9 = std::make_shared<File>(var3 + "WorldDictionaryReadable.lua");
            if (var8.exists()) {
               Files.copy(var8, var9);
            }

    auto var10 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary.bin"));
    auto var11 = std::make_shared<File>(var3 + "WorldDictionary.bin");
            if (var10.exists()) {
               Files.copy(var10, var11);
            }
         } catch (const jni::JavaException& var12) {
            var12.printStackTrace();
         }
      }
   }

    void load() {
      if (!Core.getInstance().isNoSave()) {
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary.bin");
    auto var2 = std::make_shared<File>(var1);
         if (!var2.exists()) {
            if (!WorldDictionary.isIsNewGame()) {
               throw new WorldDictionaryException("WorldDictionary data file is missing from world folder.");
            }
         } else {
            try {
               try (FileInputStream var3 = new FileInputStream(var2)) {
                  DebugLog.log("Loading WorldDictionary:" + var1);
    ByteBuffer var4 = ByteBuffer.allocate((int)var2.length());
                  var4.clear();
    int var5 = var3.read(var4.array());
                  var4.limit(var5);
                  this.loadFromByteBuffer(var4);
               }
            } catch (const jni::JavaException& var8) {
               var8.printStackTrace();
               throw new WorldDictionaryException("Error loading WorldDictionary.", var8);
            }
         }
      }
   }

    void loadFromByteBuffer(ByteBuffer var1) {
      this.NextItemID = var1.getShort();
      this.NextObjectNameID = var1.get();
      this.NextSpriteNameID = var1.getInt();
    std::vector var2 = new ArrayList();
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         var2.add(GameWindow.ReadString(var1));
      }

    std::vector var12 = new ArrayList();
    int var5 = var1.getInt();

      for (int var6 = 0; var6 < var5; var6++) {
         var12.add(GameWindow.ReadString(var1));
      }

    int var13 = var1.getInt();

      for (int var7 = 0; var7 < var13; var7++) {
    auto var8 = std::make_shared<ItemInfo>();
         var8.load(var1, 195, var2, var12);
         this.itemIdToInfoMap.put(var8.registryID, var8);
         this.itemTypeToInfoMap.put(var8.fullType, var8);
      }

    int var14 = var1.getInt();

      for (int var15 = 0; var15 < var14; var15++) {
    uint8_t var9 = var1.get();
    std::string var10 = GameWindow.ReadString(var1);
         this.objectIdToNameMap.put(var9, var10);
         this.objectNameToIdMap.put(var10, var9);
      }

    int var16 = var1.getInt();

      for (int var17 = 0; var17 < var16; var17++) {
    int var18 = var1.getInt();
    std::string var11 = GameWindow.ReadString(var1);
         this.spriteIdToNameMap.put(var18, var11);
         this.spriteNameToIdMap.put(var11, var18);
      }
   }

    void save() {
      if (!Core.getInstance().isNoSave()) {
         try {
            std::vector<byte> var1 = std::make_shared<std::array<byte, 5242880>>();
    ByteBuffer var2 = ByteBuffer.wrap(var1);
            this.saveToByteBuffer(var2);
            var2.flip();
            if (GameServer.bServer) {
               var1 = new byte[var2.limit()];
               var2.get(var1, 0, var1.length);
               this.serverDataCache = var1;
            }

    auto var3 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary.tmp"));
    auto var4 = std::make_shared<FileOutputStream>(var3);
            var4.getChannel().truncate(0L);
            var4.write(var2.array(), 0, var2.limit());
            var4.flush();
            var4.close();
    auto var5 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("WorldDictionary.bin"));
            Files.copy(var3, var5);
            var3.delete();
         } catch (const jni::JavaException& var6) {
            var6.printStackTrace();
            throw new WorldDictionaryException("Error saving WorldDictionary.", var6);
         }
      }
   }

    void saveToByteBuffer(ByteBuffer var1) {
      var1.putShort(this.NextItemID);
      var1.put(this.NextObjectNameID);
      var1.putInt(this.NextSpriteNameID);
    std::vector var2 = new ArrayList();
      this.getItemMods(var2);
      var1.putInt(var2.size());

    for (auto& var4 : var2)         GameWindow.WriteString(var1, var4);
      }

    std::vector var7 = new ArrayList();
      this.getModuleList(var7);
      var1.putInt(var7.size());

    for (auto& var5 : var7)         GameWindow.WriteString(var1, var5);
      }

      var1.putInt(this.itemIdToInfoMap.size());

      for (Entry var12 : this.itemIdToInfoMap.entrySet()) {
    ItemInfo var6 = static_cast<ItemInfo>(var12).getValue();
         var6.save(var1, var2, var7);
      }

      var1.putInt(this.objectIdToNameMap.size());

      for (Entry var13 : this.objectIdToNameMap.entrySet()) {
         var1.put(static_cast<Byte>(var13).getKey());
         GameWindow.WriteString(var1, static_cast<String>(var13).getValue());
      }

      var1.putInt(this.spriteIdToNameMap.size());

      for (Entry var14 : this.spriteIdToNameMap.entrySet()) {
         var1.putInt(static_cast<Integer>(var14).getKey());
         GameWindow.WriteString(var1, static_cast<String>(var14).getValue());
      }
   }

    void saveAsText(const std::string& var1) {
      if (!Core.getInstance().isNoSave()) {
    auto var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCurrentSaveDir() + File.separator);
         if (var2.exists() && var2.isDirectory()) {
    std::string var3 = ZomboidFileSystem.instance.getFileNameInCurrentSave(var1);
    auto var4 = std::make_shared<File>(var3);

            try (FileWriter var5 = new FileWriter(var4, false)) {
               var5.write("--[[ ---- ITEMS ---- --]]" + System.lineSeparator());
               var5.write("items = {" + System.lineSeparator());

               for (Entry var7 : this.itemIdToInfoMap.entrySet()) {
                  var5.write("\t{" + System.lineSeparator());
                  (static_cast<ItemInfo>(var7).getValue()).saveAsText(var5, "\t\t");
                  var5.write("\t}," + System.lineSeparator());
               }

               var5.write("}" + System.lineSeparator());
               var5.write(StringConcatFactory.makeConcatWithConstants<"makeConcatWithConstants","\u0001">(System.lineSeparator()));
               var5.write("--[[ ---- OBJECTS ---- --]]" + System.lineSeparator());
               var5.write("objects = {" + System.lineSeparator());

               for (Entry var13 : this.objectIdToNameMap.entrySet()) {
                  var5.write("\t" + var13.getKey() + " = \"" + static_cast<String>(var13).getValue() + "\"," + System.lineSeparator());
               }

               var5.write("}" + System.lineSeparator());
               var5.write(StringConcatFactory.makeConcatWithConstants<"makeConcatWithConstants","\u0001">(System.lineSeparator()));
               var5.write("--[[ ---- SPRITES ---- --]]" + System.lineSeparator());
               var5.write("sprites = {" + System.lineSeparator());

               for (Entry var14 : this.spriteIdToNameMap.entrySet()) {
                  var5.write("\t" + var14.getKey() + " = \"" + static_cast<String>(var14).getValue() + "\"," + System.lineSeparator());
               }

               var5.write("}" + System.lineSeparator());
            } catch (const jni::JavaException& var10) {
               var10.printStackTrace();
               throw new WorldDictionaryException("Error saving WorldDictionary as text.", var10);
            }
         }
      }
   }
}
} // namespace world
} // namespace zombie
