#pragma once
#include <stack>
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
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class SGlobalObjectNetwork {
public:
    static const uint8_t PACKET_ServerCommand = 1;
    static const uint8_t PACKET_ClientCommand = 2;
    static const uint8_t PACKET_NewLuaObjectAt = 3;
    static const uint8_t PACKET_RemoveLuaObjectAt = 4;
    static const uint8_t PACKET_UpdateLuaObjectAt = 5;
    static const ByteBuffer BYTE_BUFFER = ByteBuffer.allocate(1048576);
    static const ByteBufferWriter BYTE_BUFFER_WRITER = std::make_shared<ByteBufferWriter>(BYTE_BUFFER);

    static void receive(ByteBuffer var0, IsoPlayer var1) {
    uint8_t var2 = var0.get();
      switch (var2) {
         case 2:
            receiveClientCommand(var0, var1);
      }
   }

    static void sendPacket(ByteBuffer var0) {
      if (GameServer.bServer) {
         for (int var1 = 0; var1 < GameServer.udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)GameServer.udpEngine.connections.get(var1);
    ByteBufferWriter var3 = var2.startPacket();
            var0.flip();
            var3.bb.put(var0);
            var2.endPacketImmediate();
         }
      } else {
         if (GameClient.bClient) {
            throw IllegalStateException("can't call this method on the client");
         }

         for (int var4 = 0; var4 < SinglePlayerServer.udpEngine.connections.size(); var4++) {
            zombie.spnetwork.UdpConnection var5 = (zombie.spnetwork.UdpConnection)SinglePlayerServer.udpEngine.connections.get(var4);
    ByteBufferWriter var6 = var5.startPacket();
            var0.flip();
            var6.bb.put(var0);
            var5.endPacketImmediate();
         }
      }
   }

    static void writeServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2, ByteBufferWriter var3) {
      PacketType.GlobalObjects.doPacket(var3);
      var3.putByte((byte)1);
      var3.putUTF(var0);
      var3.putUTF(var1);
      if (var2 != nullptr && !var2.empty()) {
         var3.putByte((byte)1);

         try {
    KahluaTableIterator var4 = var2.iterator();

            while (var4.advance()) {
               if (!TableNetworkUtils.canSave(var4.getKey(), var4.getValue())) {
                  DebugLog.log("ERROR: sendServerCommand: can't save key,value=" + var4.getKey() + "," + var4.getValue());
               }
            }

            TableNetworkUtils.save(var2, var3.bb);
         } catch (IOException var5) {
            ExceptionLogger.logException(var5);
         }
      } else {
         var3.putByte((byte)0);
      }
   }

    static void sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
      BYTE_BUFFER.clear();
      writeServerCommand(var0, var1, var2, BYTE_BUFFER_WRITER);
      sendPacket(BYTE_BUFFER);
   }

    static void addGlobalObjectOnClient(SGlobalObject var0) {
      BYTE_BUFFER.clear();
    ByteBufferWriter var1 = BYTE_BUFFER_WRITER;
      PacketType.GlobalObjects.doPacket(var1);
      var1.putByte((byte)3);
      var1.putUTF(var0.system.name);
      var1.putInt(var0.getX());
      var1.putInt(var0.getY());
      var1.putByte((byte)var0.getZ());
    SGlobalObjectSystem var2 = (SGlobalObjectSystem)var0.system;
      TableNetworkUtils.saveSome(var0.getModData(), var1.bb, var2.objectSyncKeys);
      sendPacket(BYTE_BUFFER);
   }

    static void removeGlobalObjectOnClient(GlobalObject var0) {
      BYTE_BUFFER.clear();
    ByteBufferWriter var1 = BYTE_BUFFER_WRITER;
      PacketType.GlobalObjects.doPacket(var1);
      var1.putByte((byte)4);
      var1.putUTF(var0.system.name);
      var1.putInt(var0.getX());
      var1.putInt(var0.getY());
      var1.putByte((byte)var0.getZ());
      sendPacket(BYTE_BUFFER);
   }

    static void updateGlobalObjectOnClient(SGlobalObject var0) {
      BYTE_BUFFER.clear();
    ByteBufferWriter var1 = BYTE_BUFFER_WRITER;
      PacketType.GlobalObjects.doPacket(var1);
      var1.putByte((byte)5);
      var1.putUTF(var0.system.name);
      var1.putInt(var0.getX());
      var1.putInt(var0.getY());
      var1.putByte((byte)var0.getZ());
    SGlobalObjectSystem var2 = (SGlobalObjectSystem)var0.system;
      TableNetworkUtils.saveSome(var0.getModData(), var1.bb, var2.objectSyncKeys);
      sendPacket(BYTE_BUFFER);
   }

    static void receiveClientCommand(ByteBuffer var0, IsoPlayer var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    bool var4 = var0.get() == 1;
    KahluaTable var5 = nullptr;
      if (var4) {
         var5 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var5, var0);
         } catch (Exception var7) {
            var7.printStackTrace();
            return;
         }
      }

      SGlobalObjects.receiveClientCommand(var2, var3, var1, var5);
   }
}
} // namespace globalObjects
} // namespace zombie
