#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SGlobalObjectSystem : public GlobalObjectSystem {
public:
  static KahluaTable tempTable;
  int loadedWorldVersion = -1;
protected
  final HashSet<String> modDataKeys = std::make_unique<HashSet<>>();
protected
  final HashSet<String> objectModDataKeys = std::make_unique<HashSet<>>();
protected
  final HashSet<String> objectSyncKeys = std::make_unique<HashSet<>>();

public
  SGlobalObjectSystem(const std::string &name) { super(name); }

  GlobalObject makeObject(int int0, int int1, int int2) {
    return new SGlobalObject(this, int0, int1, int2);
  }

  void setModDataKeys(KahluaTable keys) {
    this.modDataKeys.clear();
    if (keys != nullptr) {
      KahluaTableIterator kahluaTableIterator = keys.iterator();

      while (kahluaTableIterator.advance()) {
        void *object = kahluaTableIterator.getValue();
        if (!(object instanceof String)) {
          throw new IllegalArgumentException("expected string but got \"" +
                                             object + "\"");
        }

        this.modDataKeys.add((String)object);
      }
    }
  }

  void setObjectModDataKeys(KahluaTable keys) {
    this.objectModDataKeys.clear();
    if (keys != nullptr) {
      KahluaTableIterator kahluaTableIterator = keys.iterator();

      while (kahluaTableIterator.advance()) {
        void *object = kahluaTableIterator.getValue();
        if (!(object instanceof String)) {
          throw new IllegalArgumentException("expected string but got \"" +
                                             object + "\"");
        }

        this.objectModDataKeys.add((String)object);
      }
    }
  }

  void setObjectSyncKeys(KahluaTable keys) {
    this.objectSyncKeys.clear();
    if (keys != nullptr) {
      KahluaTableIterator kahluaTableIterator = keys.iterator();

      while (kahluaTableIterator.advance()) {
        void *object = kahluaTableIterator.getValue();
        if (!(object instanceof String)) {
          throw new IllegalArgumentException("expected string but got \"" +
                                             object + "\"");
        }

        this.objectSyncKeys.add((String)object);
      }
    }
  }

  void update() {}

  void chunkLoaded(int wx, int wy) {
    if (this.hasObjectsInChunk(wx, wy)) {
      void *object = this.modData.rawget("OnChunkLoaded");
      if (object == nullptr) {
        throw new IllegalStateException(
            "OnChunkLoaded method undefined for system '" + this.name + "'");
      } else {
        double double0 = BoxedStaticValues.toDouble(wx);
        double double1 = BoxedStaticValues.toDouble(wy);
        LuaManager.caller.pcall(LuaManager.thread, object, this.modData,
                                double0, double1);
      }
    }
  }

  void sendCommand(const std::string &command, KahluaTable args) {
    SGlobalObjectNetwork.sendServerCommand(this.name, command, args);
  }

  void receiveClientCommand(const std::string &command, IsoPlayer playerObj,
                            KahluaTable args) {
    void *object = this.modData.rawget("OnClientCommand");
    if (object == nullptr) {
      throw new IllegalStateException(
          "OnClientCommand method undefined for system '" + this.name + "'");
    } else {
      LuaManager.caller.pcall(LuaManager.thread, object, this.modData, command,
                              playerObj, args);
    }
  }

  void addGlobalObjectOnClient(SGlobalObject globalObject) {
    if (globalObject == nullptr) {
      throw new IllegalArgumentException("globalObject is nullptr");
    } else if (globalObject.system != this) {
      throw new IllegalArgumentException("object not in this system");
    } else {
      SGlobalObjectNetwork.addGlobalObjectOnClient(globalObject);
    }
  }

  void removeGlobalObjectOnClient(SGlobalObject globalObject) {
    if (globalObject == nullptr) {
      throw new IllegalArgumentException("globalObject is nullptr");
    } else if (globalObject.system != this) {
      throw new IllegalArgumentException("object not in this system");
    } else {
      SGlobalObjectNetwork.removeGlobalObjectOnClient(globalObject);
    }
  }

  void updateGlobalObjectOnClient(SGlobalObject globalObject) {
    if (globalObject == nullptr) {
      throw new IllegalArgumentException("globalObject is nullptr");
    } else if (globalObject.system != this) {
      throw new IllegalArgumentException("object not in this system");
    } else {
      SGlobalObjectNetwork.updateGlobalObjectOnClient(globalObject);
    }
  }

  std::string getFileName() {
    return ZomboidFileSystem.instance.getFileNameInCurrentSave(
        "gos_" + this.name + ".bin");
  }

  KahluaTable getInitialStateForClient() {
    void *object = this.modData.rawget("getInitialStateForClient");
    if (object == nullptr) {
      throw new IllegalStateException(
          "getInitialStateForClient method undefined for system '" + this.name +
          "'");
    } else {
      Object[] objects =
          LuaManager.caller.pcall(LuaManager.thread, object, this.modData);
            return objects != nullptr && objects[0] == Boolean.TRUE) && objects[1] instanceof KahluaTable ? (KahluaTable)objects[1] : nullptr;
    }
  }

  void OnIsoObjectChangedItself(IsoObject isoObject) {
    GlobalObject globalObject =
        this.getObjectAt(isoObject.getSquare().x, isoObject.getSquare().y,
                         isoObject.getSquare().z);
    if (globalObject != nullptr) {
      void *object = this.modData.rawget("OnIsoObjectChangedItself");
      if (object == nullptr) {
        throw new IllegalStateException(
            "OnIsoObjectChangedItself method undefined for system '" +
            this.name + "'");
      } else {
        LuaManager.caller.pcall(LuaManager.thread, object, this.modData,
                                isoObject);
      }
    }
  }

  int loadedWorldVersion() { return this.loadedWorldVersion; }

  void load(ByteBuffer bb, int WorldVersion) {
    bool boolean0 = bb.get() == 0;
    if (!boolean0) {
      this.modData.load(bb, WorldVersion);
    }

    int int0 = bb.getInt();

    for (int int1 = 0; int1 < int0; int1++) {
      int int2 = bb.getInt();
      int int3 = bb.getInt();
      uint8_t byte0 = bb.get();
      SGlobalObject sGlobalObject = Type.tryCastTo(
          this.newObject(int2, int3, byte0), SGlobalObject.class);
      sGlobalObject.load(bb, WorldVersion);
    }

    this.loadedWorldVersion = WorldVersion;
  }

  void save(ByteBuffer bb) {
    if (tempTable == nullptr) {
      tempTable = LuaManager.platform.newTable();
    }

    tempTable.wipe();
    KahluaTableIterator kahluaTableIterator = this.modData.iterator();

    while (kahluaTableIterator.advance()) {
      void *object = kahluaTableIterator.getKey();
      if (this.modDataKeys.contains(object)) {
        tempTable.rawset(object, this.modData.rawget(object));
      }
    }

    if (tempTable.isEmpty()) {
      bb.put((byte)0);
    } else {
      bb.put((byte)1);
      tempTable.save(bb);
    }

    bb.putInt(this.objects.size());

    for (int int0 = 0; int0 < this.objects.size(); int0++) {
      SGlobalObject sGlobalObject =
          Type.tryCastTo(this.objects.get(int0), SGlobalObject.class);
      sGlobalObject.save(bb);
    }
  }

  void load() {
    File file = new File(this.getFileName());

    try(FileInputStream fileInputStream = new FileInputStream(file);
        BufferedInputStream bufferedInputStream =
            new BufferedInputStream(fileInputStream);) {
      synchronized(SliceY.SliceBufferLock) {
        ByteBuffer byteBuffer = SliceY.SliceBuffer;
        byteBuffer.clear();
        int int0 = bufferedInputStream.read(byteBuffer.array());
        byteBuffer.limit(int0);
        uint8_t byte0 = byteBuffer.get();
        uint8_t byte1 = byteBuffer.get();
        uint8_t byte2 = byteBuffer.get();
        uint8_t byte3 = byteBuffer.get();
        if (byte0 != 71 || byte1 != 76 || byte2 != 79 || byte3 != 83) {
          throw new IOException(
              "doesn't appear to be a GlobalObjectSystem file:" +
              file.getAbsolutePath());
        }

        int int1 = byteBuffer.getInt();
        if (int1 < 134) {
          throw new IOException("invalid WorldVersion " + int1 + ": " +
                                file.getAbsolutePath());
        }

        if (int1 > 195) {
          throw new IOException("file is from a newer version " + int1 +
                                " of the game: " + file.getAbsolutePath());
        }

        this.load(byteBuffer, int1);
      }
    }
    catch (FileNotFoundException fileNotFoundException) {
    }
    catch (Throwable throwable) {
      ExceptionLogger.logException(throwable);
    }
  }

  void save() {
    if (!Core.getInstance().isNoSave()) {
      if (!GameClient.bClient) {
        File file = new File(this.getFileName());

        try(FileOutputStream fileOutputStream = new FileOutputStream(file);
            BufferedOutputStream bufferedOutputStream =
                new BufferedOutputStream(fileOutputStream);) {
          synchronized(SliceY.SliceBufferLock) {
            ByteBuffer byteBuffer = SliceY.SliceBuffer;
            byteBuffer.clear();
            byteBuffer.put((byte)71);
            byteBuffer.put((byte)76);
            byteBuffer.put((byte)79);
            byteBuffer.put((byte)83);
            byteBuffer.putInt(195);
            this.save(byteBuffer);
            bufferedOutputStream.write(byteBuffer.array(), 0,
                                       byteBuffer.position());
          }
        }
        catch (Throwable throwable) {
          ExceptionLogger.logException(throwable);
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
