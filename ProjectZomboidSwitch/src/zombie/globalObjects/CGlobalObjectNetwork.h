#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class CGlobalObjectNetwork {
public:
    static const ByteBuffer BYTE_BUFFER = ByteBuffer.allocate(1048576);
    static const ByteBufferWriter BYTE_BUFFER_WRITER = std::make_shared<ByteBufferWriter>(BYTE_BUFFER);
    static KahluaTable tempTable;

    static void receive(ByteBuffer var0) {
    uint8_t var1 = var0.get();
      switch (var1) {
         case 1:
            receiveServerCommand(var0);
         case 2:
         default:
            break;
         case 3:
            receiveNewLuaObjectAt(var0);
            break;
         case 4:
            receiveRemoveLuaObjectAt(var0);
            break;
         case 5:
            receiveUpdateLuaObjectAt(var0);
      }
   }

    static void receiveServerCommand(ByteBuffer var0) {
    std::string var1 = GameWindow.ReadString(var0);
    std::string var2 = GameWindow.ReadString(var0);
    bool var3 = var0.get() == 1;
    KahluaTable var4 = nullptr;
      if (var3) {
         var4 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var4, var0);
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
            return;
         }
      }

      CGlobalObjects.receiveServerCommand(var1, var2, var4);
   }

    static void receiveNewLuaObjectAt(ByteBuffer var0) {
    std::string var1 = GameWindow.ReadStringUTF(var0);
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    uint8_t var4 = var0.get();
      if (tempTable == nullptr) {
         tempTable = LuaManager.platform.newTable();
      }

      TableNetworkUtils.load(tempTable, var0);
    CGlobalObjectSystem var5 = CGlobalObjects.getSystemByName(var1);
      if (var5 != nullptr) {
         var5.receiveNewLuaObjectAt(var2, var3, var4, tempTable);
      }
   }

    static void receiveRemoveLuaObjectAt(ByteBuffer var0) {
    std::string var1 = GameWindow.ReadStringUTF(var0);
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    uint8_t var4 = var0.get();
    CGlobalObjectSystem var5 = CGlobalObjects.getSystemByName(var1);
      if (var5 != nullptr) {
         var5.receiveRemoveLuaObjectAt(var2, var3, var4);
      }
   }

    static void receiveUpdateLuaObjectAt(ByteBuffer var0) {
    std::string var1 = GameWindow.ReadStringUTF(var0);
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    uint8_t var4 = var0.get();
      if (tempTable == nullptr) {
         tempTable = LuaManager.platform.newTable();
      }

      TableNetworkUtils.load(tempTable, var0);
    CGlobalObjectSystem var5 = CGlobalObjects.getSystemByName(var1);
      if (var5 != nullptr) {
         var5.receiveUpdateLuaObjectAt(var2, var3, var4, tempTable);
      }
   }

    static void sendPacket(ByteBuffer var0) {
      if (GameServer.bServer) {
         throw IllegalStateException("can't call this method on the server");
      } else {
         if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
            var0.flip();
            var1.bb.put(var0);
            PacketType.GlobalObjects.send(GameClient.connection);
         } else {
    ByteBufferWriter var2 = SinglePlayerClient.connection.startPacket();
            var0.flip();
            var2.bb.put(var0);
            SinglePlayerClient.connection.endPacketImmediate();
         }
      }
   }

    static void sendClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
      BYTE_BUFFER.clear();
      writeClientCommand(var0, var1, var2, var3, BYTE_BUFFER_WRITER);
      sendPacket(BYTE_BUFFER);
   }

    static void writeClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3, ByteBufferWriter var4) {
      PacketType.GlobalObjects.doPacket(var4);
      var4.putByte((byte)(var0 != nullptr ? var0.PlayerIndex : -1));
      var4.putByte((byte)2);
      var4.putUTF(var1);
      var4.putUTF(var2);
      if (var3 != nullptr && !var3.empty()) {
         var4.putByte((byte)1);

         try {
    KahluaTableIterator var5 = var3.iterator();

            while (var5.advance()) {
               if (!TableNetworkUtils.canSave(var5.getKey(), var5.getValue())) {
                  DebugLog.log("ERROR: sendClientCommand: can't save key,value=" + var5.getKey() + "," + var5.getValue());
               }
            }

            TableNetworkUtils.save(var3, var4.bb);
         } catch (IOException var6) {
            ExceptionLogger.logException(var6);
         }
      } else {
         var4.putByte((byte)0);
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
