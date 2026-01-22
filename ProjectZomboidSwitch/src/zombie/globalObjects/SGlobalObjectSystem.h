#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SliceY.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class SGlobalObjectSystem : public GlobalObjectSystem {
public:
    static KahluaTable tempTable;
    int loadedWorldVersion = -1;
   protected const std::unordered_set<std::string> modDataKeys = std::make_unique<std::unordered_set<>>();
   protected const std::unordered_set<std::string> objectModDataKeys = std::make_unique<std::unordered_set<>>();
   protected const std::unordered_set<std::string> objectSyncKeys = std::make_unique<std::unordered_set<>>();

    public SGlobalObjectSystem(const std::string& var1) {
      super(var1);
   }

    GlobalObject makeObject(int var1, int var2, int var3) {
      return std::make_shared<SGlobalObject>(this, var1, var2, var3);
   }

    void setModDataKeys(KahluaTable var1) {
      this.modDataKeys.clear();
      if (var1 != nullptr) {
    KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
    void* var3 = var2.getValue();
            if (!(dynamic_cast<std*>(var3) != nullptr::string)) {
               throw IllegalArgumentException("expected string but got \"" + var3 + "\"");
            }

            this.modDataKeys.push_back((std::string)var3);
         }
      }
   }

    void setObjectModDataKeys(KahluaTable var1) {
      this.objectModDataKeys.clear();
      if (var1 != nullptr) {
    KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
    void* var3 = var2.getValue();
            if (!(dynamic_cast<std*>(var3) != nullptr::string)) {
               throw IllegalArgumentException("expected string but got \"" + var3 + "\"");
            }

            this.objectModDataKeys.push_back((std::string)var3);
         }
      }
   }

    void setObjectSyncKeys(KahluaTable var1) {
      this.objectSyncKeys.clear();
      if (var1 != nullptr) {
    KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
    void* var3 = var2.getValue();
            if (!(dynamic_cast<std*>(var3) != nullptr::string)) {
               throw IllegalArgumentException("expected string but got \"" + var3 + "\"");
            }

            this.objectSyncKeys.push_back((std::string)var3);
         }
      }
   }

    void update() {
   }

    void chunkLoaded(int var1, int var2) {
      if (this.hasObjectsInChunk(var1, var2)) {
    void* var3 = this.modData.rawget("OnChunkLoaded");
         if (var3 == nullptr) {
            throw IllegalStateException("OnChunkLoaded method undefined for system '" + this.name + "'");
         } else {
    double var4 = BoxedStaticValues.toDouble(var1);
    double var5 = BoxedStaticValues.toDouble(var2);
            LuaManager.caller.pcall(LuaManager.thread, var3, new Object[]{this.modData, var4, var5});
         }
      }
   }

    void sendCommand(const std::string& var1, KahluaTable var2) {
      SGlobalObjectNetwork.sendServerCommand(this.name, var1, var2);
   }

    void receiveClientCommand(const std::string& var1, IsoPlayer var2, KahluaTable var3) {
    void* var4 = this.modData.rawget("OnClientCommand");
      if (var4 == nullptr) {
         throw IllegalStateException("OnClientCommand method undefined for system '" + this.name + "'");
      } else {
         LuaManager.caller.pcall(LuaManager.thread, var4, new Object[]{this.modData, var1, var2, var3});
      }
   }

    void addGlobalObjectOnClient(SGlobalObject var1) {
      if (var1 == nullptr) {
         throw IllegalArgumentException("globalObject is nullptr");
      } else if (var1.system != this) {
         throw IllegalArgumentException("object not in this system");
      } else {
         SGlobalObjectNetwork.addGlobalObjectOnClient(var1);
      }
   }

    void removeGlobalObjectOnClient(SGlobalObject var1) {
      if (var1 == nullptr) {
         throw IllegalArgumentException("globalObject is nullptr");
      } else if (var1.system != this) {
         throw IllegalArgumentException("object not in this system");
      } else {
         SGlobalObjectNetwork.removeGlobalObjectOnClient(var1);
      }
   }

    void updateGlobalObjectOnClient(SGlobalObject var1) {
      if (var1 == nullptr) {
         throw IllegalArgumentException("globalObject is nullptr");
      } else if (var1.system != this) {
         throw IllegalArgumentException("object not in this system");
      } else {
         SGlobalObjectNetwork.updateGlobalObjectOnClient(var1);
      }
   }

    std::string getFileName() {
      return ZomboidFileSystem.instance.getFileNameInCurrentSave("gos_" + this.name + ".bin");
   }

    KahluaTable getInitialStateForClient() {
    void* var1 = this.modData.rawget("getInitialStateForClient");
      if (var1 == nullptr) {
         throw IllegalStateException("getInitialStateForClient method undefined for system '" + this.name + "'");
      } else {
         Object[] var2 = LuaManager.caller.pcall(LuaManager.thread, var1, this.modData);
         return var2 != nullptr && var2[0] == bool.TRUE) && var2[1] instanceof KahluaTable ? (KahluaTable)var2[1] : nullptr;
      }
   }

    void OnIsoObjectChangedItself(IsoObject var1) {
    GlobalObject var2 = this.getObjectAt(var1.getSquare().x, var1.getSquare().y, var1.getSquare().z);
      if (var2 != nullptr) {
    void* var3 = this.modData.rawget("OnIsoObjectChangedItself");
         if (var3 == nullptr) {
            throw IllegalStateException("OnIsoObjectChangedItself method undefined for system '" + this.name + "'");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, var3, new Object[]{this.modData, var1});
         }
      }
   }

    int loadedWorldVersion() {
      return this.loadedWorldVersion;
   }

    void load(ByteBuffer var1, int var2) {
    bool var3 = var1.get() == 0;
      if (!var3) {
         this.modData.load(var1, var2);
      }

    int var4 = var1.getInt();

      for (int var5 = 0; var5 < var4; var5++) {
    int var6 = var1.getInt();
    int var7 = var1.getInt();
    uint8_t var8 = var1.get();
    SGlobalObject var9 = (SGlobalObject)Type.tryCastTo(this.newObject(var6, var7, var8), SGlobalObject.class);
         var9.load(var1, var2);
      }

      this.loadedWorldVersion = var2;
   }

    void save(ByteBuffer var1) {
      if (tempTable == nullptr) {
         tempTable = LuaManager.platform.newTable();
      }

      tempTable.wipe();
    KahluaTableIterator var2 = this.modData.iterator();

      while (var2.advance()) {
    void* var3 = var2.getKey();
         if (this.modDataKeys.contains(var3)) {
            tempTable.rawset(var3, this.modData.rawget(var3));
         }
      }

      if (tempTable.empty()) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         tempTable.save(var1);
      }

      var1.putInt(this.objects.size());

      for (int var5 = 0; var5 < this.objects.size(); var5++) {
    SGlobalObject var4 = (SGlobalObject)Type.tryCastTo((GlobalObject)this.objects.get(var5), SGlobalObject.class);
         var4.save(var1);
      }
   }

    void load() {
    File var1 = std::make_shared<File>(this.getFileName());

      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
    ByteBuffer var5 = SliceY.SliceBuffer;
            var5.clear();
    int var6 = var3.read(var5.array());
            var5.limit(var6);
    uint8_t var7 = var5.get();
    uint8_t var8 = var5.get();
    uint8_t var9 = var5.get();
    uint8_t var10 = var5.get();
            if (var7 != 71 || var8 != 76 || var9 != 79 || var10 != 83) {
               throw IOException("doesn't appear to be a GlobalObjectSystem file:" + var1.getAbsolutePath());
            }

    int var11 = var5.getInt();
            if (var11 < 134) {
               throw IOException("invalid WorldVersion " + var11 + ": " + var1.getAbsolutePath());
            }

            if (var11 > 195) {
               throw IOException("file is from a newer version " + var11 + " of the game: " + var1.getAbsolutePath());
            }

            this.load(var5, var11);
         }
      } catch (FileNotFoundException var18) {
      } catch (Throwable var19) {
         ExceptionLogger.logException(var19);
      }
   }

    void save() {
      if (!Core.getInstance().isNoSave()) {
         if (!GameClient.bClient) {
    File var1 = std::make_shared<File>(this.getFileName());

            try (
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var1);
    BufferedOutputStream var3 = std::make_shared<BufferedOutputStream>(var2);
            ) {
               /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
    ByteBuffer var5 = SliceY.SliceBuffer;
                  var5.clear();
                  var5.put((byte)71);
                  var5.put((byte)76);
                  var5.put((byte)79);
                  var5.put((byte)83);
                  var5.putInt(195);
                  this.save(var5);
                  var3.write(var5.array(), 0, var5.position());
               }
            } catch (Throwable var12) {
               ExceptionLogger.logException(var12);
            }
         }
      }
   }

    void Reset() {
      super.Reset();
      this.modDataKeys.clear();
      this.objectModDataKeys.clear();
      this.objectSyncKeys.clear();
   }
}
} // namespace globalObjects
} // namespace zombie
