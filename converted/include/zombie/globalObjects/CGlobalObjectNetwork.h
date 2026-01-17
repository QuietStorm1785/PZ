#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
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

class CGlobalObjectNetwork {
public:
  static const ByteBuffer BYTE_BUFFER = ByteBuffer.allocate(1048576);
  static const ByteBufferWriter BYTE_BUFFER_WRITER =
      new ByteBufferWriter(BYTE_BUFFER);
  static KahluaTable tempTable;

  static void receive(ByteBuffer byteBuffer) {
    uint8_t byte0 = byteBuffer.get();
    switch (byte0) {
    case 1:
      receiveServerCommand(byteBuffer);
    case 2:
    default:
      break;
    case 3:
      receiveNewLuaObjectAt(byteBuffer);
      break;
    case 4:
      receiveRemoveLuaObjectAt(byteBuffer);
      break;
    case 5:
      receiveUpdateLuaObjectAt(byteBuffer);
    }
  }

  static void receiveServerCommand(ByteBuffer byteBuffer) {
    std::string string0 = GameWindow.ReadString(byteBuffer);
    std::string string1 = GameWindow.ReadString(byteBuffer);
    bool boolean0 = byteBuffer.get() == 1;
    KahluaTable table = null;
    if (boolean0) {
      table = LuaManager.platform.newTable();

      try {
        TableNetworkUtils.load(table, byteBuffer);
      } catch (Exception exception) {
        ExceptionLogger.logException(exception);
        return;
      }
    }

    CGlobalObjects.receiveServerCommand(string0, string1, table);
  }

  static void receiveNewLuaObjectAt(ByteBuffer byteBuffer) {
    std::string string = GameWindow.ReadStringUTF(byteBuffer);
    int int0 = byteBuffer.getInt();
    int int1 = byteBuffer.getInt();
    uint8_t byte0 = byteBuffer.get();
    if (tempTable == nullptr) {
      tempTable = LuaManager.platform.newTable();
    }

    TableNetworkUtils.load(tempTable, byteBuffer);
    CGlobalObjectSystem cGlobalObjectSystem =
        CGlobalObjects.getSystemByName(string);
    if (cGlobalObjectSystem != nullptr) {
      cGlobalObjectSystem.receiveNewLuaObjectAt(int0, int1, byte0, tempTable);
    }
  }

  static void receiveRemoveLuaObjectAt(ByteBuffer byteBuffer) {
    std::string string = GameWindow.ReadStringUTF(byteBuffer);
    int int0 = byteBuffer.getInt();
    int int1 = byteBuffer.getInt();
    uint8_t byte0 = byteBuffer.get();
    CGlobalObjectSystem cGlobalObjectSystem =
        CGlobalObjects.getSystemByName(string);
    if (cGlobalObjectSystem != nullptr) {
      cGlobalObjectSystem.receiveRemoveLuaObjectAt(int0, int1, byte0);
    }
  }

  static void receiveUpdateLuaObjectAt(ByteBuffer byteBuffer) {
    std::string string = GameWindow.ReadStringUTF(byteBuffer);
    int int0 = byteBuffer.getInt();
    int int1 = byteBuffer.getInt();
    uint8_t byte0 = byteBuffer.get();
    if (tempTable == nullptr) {
      tempTable = LuaManager.platform.newTable();
    }

    TableNetworkUtils.load(tempTable, byteBuffer);
    CGlobalObjectSystem cGlobalObjectSystem =
        CGlobalObjects.getSystemByName(string);
    if (cGlobalObjectSystem != nullptr) {
      cGlobalObjectSystem.receiveUpdateLuaObjectAt(int0, int1, byte0,
                                                   tempTable);
    }
  }

  static void sendPacket(ByteBuffer byteBuffer) {
    if (GameServer.bServer) {
      throw new IllegalStateException("can't call this method on the server");
    } else {
      if (GameClient.bClient) {
        ByteBufferWriter byteBufferWriter0 =
            GameClient.connection.startPacket();
        byteBuffer.flip();
        byteBufferWriter0.bb.put(byteBuffer);
        PacketTypes.PacketType.GlobalObjects.send(GameClient.connection);
      } else {
        ByteBufferWriter byteBufferWriter1 =
            SinglePlayerClient.connection.startPacket();
        byteBuffer.flip();
        byteBufferWriter1.bb.put(byteBuffer);
        SinglePlayerClient.connection.endPacketImmediate();
      }
    }
  }

  static void sendClientCommand(IsoPlayer player, const std::string &string0,
                                const std::string &string1, KahluaTable table) {
    BYTE_BUFFER.clear();
    writeClientCommand(player, string0, string1, table, BYTE_BUFFER_WRITER);
    sendPacket(BYTE_BUFFER);
  }

  static void writeClientCommand(IsoPlayer player, const std::string &string0,
                                 const std::string &string1, KahluaTable table,
                                 ByteBufferWriter byteBufferWriter) {
    PacketTypes.PacketType.GlobalObjects.doPacket(byteBufferWriter);
    byteBufferWriter.putByte(
        (byte)(player != nullptr ? player.PlayerIndex : -1));
    byteBufferWriter.putByte((byte)2);
    byteBufferWriter.putUTF(string0);
    byteBufferWriter.putUTF(string1);
    if (table != nullptr && !table.isEmpty()) {
      byteBufferWriter.putByte((byte)1);

      try {
        KahluaTableIterator kahluaTableIterator = table.iterator();

        while (kahluaTableIterator.advance()) {
          if (!TableNetworkUtils.canSave(kahluaTableIterator.getKey(),
                                         kahluaTableIterator.getValue())) {
            DebugLog.log("ERROR: sendClientCommand: can't save key,value=" +
                         kahluaTableIterator.getKey() + "," +
                         kahluaTableIterator.getValue());
          }
        }

        TableNetworkUtils.save(table, byteBufferWriter.bb);
      } catch (IOException iOException) {
        ExceptionLogger.logException(iOException);
      }
    } else {
      byteBufferWriter.putByte((byte)0);
    }
  }

  static void Reset() {
    if (tempTable != nullptr) {
      tempTable.wipe();
      tempTable = nullptr;
    }
  }
}
} // namespace globalObjects
} // namespace zombie
