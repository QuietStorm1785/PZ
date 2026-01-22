#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/Normalizer.h"
#include "java/text/Normalizer/Form.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/radio/media/MediaData/MediaLineData.h"
#include "zombie/radio/media/RecordedMedia/MediaNameSorter.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace media {


class RecordedMedia {
public:
    static bool DISABLE_LINE_LEARNING = false;
    static const int SPAWN_COMMON = 0;
    static const int SPAWN_RARE = 1;
    static const int SPAWN_EXCEPTIONAL = 2;
    static const int VERSION1 = 1;
    static const int VERSION2 = 2;
    static const int VERSION = 2;
    static const std::string SAVE_FILE = "recorded_media.bin";
   private const std::vector<std::string> indexes = std::make_unique<std::vector<>>();
   private static const std::vector<std::string> indexesFromServer = std::make_unique<std::vector<>>();
   private const Map<std::string, MediaData> mediaDataMap = std::make_unique<std::unordered_map<>>();
   private const Map<std::string, std::vector<MediaData>> categorizedMap = std::make_unique<std::unordered_map<>>();
   private const std::vector<std::string> categories = std::make_unique<std::vector<>>();
   private const std::vector<std::string> legacyListenedLines = std::make_unique<std::vector<>>();
   private const std::unordered_set<int16_t> homeVhsSpawned = std::make_unique<std::unordered_set<>>();
   private const Map<int, std::vector<MediaData>> retailVhsSpawnTable = std::make_unique<std::unordered_map<>>();
   private const Map<int, std::vector<MediaData>> retailCdSpawnTable = std::make_unique<std::unordered_map<>>();
    bool REQUIRES_SAVING = true;

    void init() {
      try {
         this.load();
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      LuaEventManager.triggerEvent("OnInitRecordedMedia", this);
      this.retailCdSpawnTable.put(0, std::make_unique<std::vector<>>());
      this.retailCdSpawnTable.put(1, std::make_unique<std::vector<>>());
      this.retailCdSpawnTable.put(2, std::make_unique<std::vector<>>());
      this.retailVhsSpawnTable.put(0, std::make_unique<std::vector<>>());
      this.retailVhsSpawnTable.put(1, std::make_unique<std::vector<>>());
      this.retailVhsSpawnTable.put(2, std::make_unique<std::vector<>>());
    std::vector var1 = this.categorizedMap.get("CDs");
      if (var1 != nullptr) {
    for (auto& var3 : var1)            if (var3.getSpawning() == 1) {
               this.retailCdSpawnTable.get(1).push_back(var3);
            } else if (var3.getSpawning() == 2) {
               this.retailCdSpawnTable.get(2).push_back(var3);
            } else {
               this.retailCdSpawnTable.get(0).push_back(var3);
            }
         }
      } else {
         DebugLog.General.error("categorizedMap with CDs is empty");
      }

      var1 = this.categorizedMap.get("Retail-VHS");
      if (var1 != nullptr) {
    for (auto& var8 : var1)            if (var8.getSpawning() == 1) {
               this.retailVhsSpawnTable.get(1).push_back(var8);
            } else if (var8.getSpawning() == 2) {
               this.retailVhsSpawnTable.get(2).push_back(var8);
            } else {
               this.retailVhsSpawnTable.get(0).push_back(var8);
            }
         }
      } else {
         DebugLog.General.error("categorizedMap with Retail-VHS is empty");
      }

      try {
         this.save();
      } catch (Exception var4) {
         var4.printStackTrace();
      }
   }

    static uint8_t getMediaTypeForCategory(const std::string& var0) {
      if (var0 == nullptr) {
         return -1;
      } else {
         return (byte)(var0.equalsIgnoreCase("cds") ? 0 : 1);
      }
   }

   public std::vector<std::string> getCategories() {
      return this.categories;
   }

   public std::vector<MediaData> getAllMediaForType(byte var1) {
    std::vector var2 = new std::vector();

      for (Entry var4 : this.mediaDataMap.entrySet()) {
         if (((MediaData)var4.getValue()).getMediaType() == var1) {
            var2.push_back((MediaData)var4.getValue());
         }
      }

      var2.sort(std::make_unique<MediaNameSorter>());
    return var2;
   }

   public std::vector<MediaData> getAllMediaForCategory(std::string var1) {
    std::vector var2 = new std::vector();

      for (Entry var4 : this.mediaDataMap.entrySet()) {
         if (var1.equalsIgnoreCase(((MediaData)var4.getValue()).getCategory())) {
            var2.push_back((MediaData)var4.getValue());
         }
      }

      var2.sort(std::make_unique<MediaNameSorter>());
    return var2;
   }

    MediaData register(const std::string& var1, const std::string& var2, const std::string& var3, int var4) {
      if (this.mediaDataMap.containsKey(var2)) {
         DebugLog.log("RecordeMedia -> MediaData id already exists : " + var2);
    return nullptr;
      } else {
         if (var4 < 0) {
            var4 = 0;
         }

    MediaData var5 = std::make_shared<MediaData>(var2, var3, var4);
         this.mediaDataMap.put(var2, var5);
         var5.setCategory(var1);
         if (!this.categorizedMap.containsKey(var1)) {
            this.categorizedMap.put(var1, std::make_unique<std::vector<>>());
            this.categories.push_back(var1);
         }

         this.categorizedMap.get(var1).push_back(var5);
    short var6;
         if (this.indexes.contains(var2)) {
            var6 = (short)this.indexes.indexOf(var2);
         } else {
            var6 = (short)this.indexes.size();
            this.indexes.push_back(var2);
         }

         var5.setIndex(var6);
         this.REQUIRES_SAVING = true;
    return var5;
      }
   }

    MediaData getMediaDataFromIndex(short var1) {
      return var1 >= 0 && var1 < this.indexes.size() ? this.getMediaData(this.indexes.get(var1)) : nullptr;
   }

    short getIndexForMediaData(MediaData var1) {
      return (short)this.indexes.indexOf(var1.getId());
   }

    MediaData getMediaData(const std::string& var1) {
      return this.mediaDataMap.get(var1);
   }

    MediaData getRandomFromCategory(const std::string& var1) {
      if (this.categorizedMap.containsKey(var1)) {
    MediaData var2 = nullptr;
         if (var1.equalsIgnoreCase("cds")) {
    int var7 = Rand.Next(0, 1000);
            if (var7 < 100) {
               if (this.retailCdSpawnTable.get(2).size() > 0) {
                  var2 = this.retailCdSpawnTable.get(2).get(Rand.Next(0, this.retailCdSpawnTable.get(2).size()));
               }
            } else if (var7 < 400) {
               if (this.retailCdSpawnTable.get(1).size() > 0) {
                  var2 = this.retailCdSpawnTable.get(1).get(Rand.Next(0, this.retailCdSpawnTable.get(1).size()));
               }
            } else {
               var2 = this.retailCdSpawnTable.get(0).get(Rand.Next(0, this.retailCdSpawnTable.get(0).size()));
            }

            if (var2 != nullptr) {
    return var2;
            }

            return this.retailCdSpawnTable.get(0).get(Rand.Next(0, this.retailCdSpawnTable.get(0).size()));
         }

         if (var1.equalsIgnoreCase("retail-vhs")) {
    int var6 = Rand.Next(0, 1000);
            if (var6 < 100) {
               if (this.retailVhsSpawnTable.get(2).size() > 0) {
                  var2 = this.retailVhsSpawnTable.get(2).get(Rand.Next(0, this.retailVhsSpawnTable.get(2).size()));
               }
            } else if (var6 < 400) {
               if (this.retailVhsSpawnTable.get(1).size() > 0) {
                  var2 = this.retailVhsSpawnTable.get(1).get(Rand.Next(0, this.retailVhsSpawnTable.get(1).size()));
               }
            } else {
               var2 = this.retailVhsSpawnTable.get(0).get(Rand.Next(0, this.retailVhsSpawnTable.get(0).size()));
            }

            if (var2 != nullptr) {
    return var2;
            }

            return this.retailVhsSpawnTable.get(0).get(Rand.Next(0, this.retailVhsSpawnTable.get(0).size()));
         }

         if (var1.equalsIgnoreCase("home-vhs")) {
    int var3 = Rand.Next(0, 1000);
            if (var3 < 200) {
    std::vector var4 = this.categorizedMap.get("Home-VHS");
               var2 = (MediaData)var4.get(Rand.Next(0, var4.size()));
               if (!this.homeVhsSpawned.contains(var2.getIndex())) {
                  this.homeVhsSpawned.push_back(var2.getIndex());
                  this.REQUIRES_SAVING = true;
    return var2;
               }
            }
         }
      }

    return nullptr;
   }

    void load() {
      this.indexes.clear();
      if (GameClient.bClient) {
         this.indexes.addAll(indexesFromServer);
         indexesFromServer.clear();
      }

      if (!Core.getInstance().isNoSave()) {
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("recorded_media.bin");
    File var2 = std::make_shared<File>(var1);
         if (!var2.exists()) {
            if (!WorldDictionary.isIsNewGame()) {
               DebugLog.log("RecordedMedia data file is missing from world folder.");
            }
         } else {
            try (FileInputStream var3 = std::make_shared<FileInputStream>(var2)) {
               DebugLog.log("Loading Recorded Media:" + var1);
    ByteBuffer var4 = ByteBuffer.allocate((int)var2.length());
               var4.clear();
    int var5 = var3.read(var4.array());
               var4.limit(var5);
    int var6 = var4.getInt();
    int var7 = var4.getInt();

               for (int var8 = 0; var8 < var7; var8++) {
    std::string var9 = GameWindow.ReadString(var4);
                  if (!GameClient.bClient) {
                     this.indexes.push_back(var9);
                  }
               }

               if (var6 == 1) {
                  var7 = var4.getInt();

                  for (int var15 = 0; var15 < var7; var15++) {
    std::string var17 = GameWindow.ReadString(var4);
                     this.legacyListenedLines.push_back(var17);
                  }
               }

               var7 = var4.getInt();

               for (int var16 = 0; var16 < var7; var16++) {
                  this.homeVhsSpawned.push_back(var4.getShort());
               }
            } catch (Exception var12) {
               var12.printStackTrace();
            }
         }
      }
   }

    void save() {
      if (!Core.getInstance().isNoSave() && this.REQUIRES_SAVING) {
         try {
    int var1 = 0;
            var1 += this.indexes.size() * 40;
            var1 += this.homeVhsSpawned.size() * 2;
            var1 += 512;
            byte[] var2 = new byte[var1];
    ByteBuffer var3 = ByteBuffer.wrap(var2);
            var3.putInt(2);
            var3.putInt(this.indexes.size());

            for (int var4 = 0; var4 < this.indexes.size(); var4++) {
               GameWindow.WriteString(var3, this.indexes.get(var4));
            }

            var3.putInt(this.homeVhsSpawned.size());
            int16_t[] var12 = this.homeVhsSpawned.toArray(new int16_t[0]);

            for (int var5 = 0; var5 < var12.length; var5++) {
               var3.putShort(var12[var5]);
            }

            var3.flip();
    std::string var13 = ZomboidFileSystem.instance.getFileNameInCurrentSave("recorded_media.bin");
    File var6 = std::make_shared<File>(var13);
            DebugLog.log("Saving Recorded Media:" + var13);
    FileOutputStream var7 = std::make_shared<FileOutputStream>(var6);
            var7.getChannel().truncate(0L);
            var7.write(var3.array(), 0, var3.limit());
            var7.flush();
            var7.close();
         } catch (Exception var8) {
            var8.printStackTrace();
         }

         this.REQUIRES_SAVING = false;
      }
   }

    static std::string toAscii(const std::string& var0) {
    std::stringstream var1 = new std::stringstream(var0.length());
      var0 = Normalizer.normalize(var0, Form.NFD);

      for (char var5 : var0.toCharArray()) {
         if (var5 <= 127) {
            var1.append(var5);
         }
      }

      return var1;
   }

    bool hasListenedToLine(IsoPlayer var1, const std::string& var2) {
      return var1.isKnownMediaLine(var2);
   }

    bool hasListenedToAll(IsoPlayer var1, MediaData var2) {
      if (var1 == nullptr) {
         var1 = IsoPlayer.players[0];
      }

      if (var1 != nullptr && var2 != nullptr) {
         for (int var3 = 0; var3 < var2.getLineCount(); var3++) {
    MediaLineData var4 = var2.getLine(var3);
            if (!var1.isKnownMediaLine(var4.getTextGuid())) {
    return false;
            }
         }

         return var2.getLineCount() > 0;
      } else {
    return false;
      }
   }

    void sendRequestData(ByteBuffer var1) {
      var1.putInt(this.indexes.size());

      for (int var2 = 0; var2 < this.indexes.size(); var2++) {
         GameWindow.WriteStringUTF(var1, this.indexes.get(var2));
      }
   }

    static void receiveRequestData(ByteBuffer var0) {
      indexesFromServer.clear();
    int var1 = var0.getInt();

      for (int var2 = 0; var2 < var1; var2++) {
         indexesFromServer.push_back(GameWindow.ReadStringUTF(var0));
      }
   }

    void handleLegacyListenedLines(IsoPlayer var1) {
      if (!this.legacyListenedLines.empty()) {
         if (var1 != nullptr) {
            for (std::string var3 : this.legacyListenedLines) {
               var1.addKnownMediaLine(var3);
            }
         }

         this.legacyListenedLines.clear();
      }
   }
}
} // namespace media
} // namespace radio
} // namespace zombie
