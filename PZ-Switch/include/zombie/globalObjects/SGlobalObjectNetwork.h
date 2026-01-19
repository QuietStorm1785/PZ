#pragma once
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
#include "zombie/network/PacketTypes.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SGlobalObjectNetwork {
public:
 static const uint8_t PACKET_ServerCommand = 1;
 static const uint8_t PACKET_ClientCommand = 2;
 static const uint8_t PACKET_NewLuaObjectAt = 3;
 static const uint8_t PACKET_RemoveLuaObjectAt = 4;
 static const uint8_t PACKET_UpdateLuaObjectAt = 5;
 static const ByteBuffer BYTE_BUFFER = ByteBuffer.allocate(1048576);
 static const ByteBufferWriter BYTE_BUFFER_WRITER =
 new ByteBufferWriter(BYTE_BUFFER);

 static void receive(ByteBuffer byteBuffer, IsoPlayer player) {
 uint8_t byte0 = byteBuffer.get();
 switch (byte0) {
 case 2:
 receiveClientCommand(byteBuffer, player);
 }
 }

 static void sendPacket(ByteBuffer byteBuffer) {
 if (GameServer.bServer) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection0 =
 GameServer.udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter0 = udpConnection0.startPacket();
 byteBuffer.flip();
 byteBufferWriter0.bb.put(byteBuffer);
 udpConnection0.endPacketImmediate();
 }
 } else {
 if (GameClient.bClient) {
 throw IllegalStateException("can't call this method on the client");
 }

 for (int int1 = 0; int1 < SinglePlayerServer.udpEngine.connections.size();
 int1++) {
 zombie.spnetwork.UdpConnection udpConnection1 =
 SinglePlayerServer.udpEngine.connections.get(int1);
 ByteBufferWriter byteBufferWriter1 = udpConnection1.startPacket();
 byteBuffer.flip();
 byteBufferWriter1.bb.put(byteBuffer);
 udpConnection1.endPacketImmediate();
 }
 }
 }

 static void writeServerCommand(std::string_view string0,
 std::string_view string1, KahluaTable table,
 ByteBufferWriter byteBufferWriter) {
 PacketTypes.PacketType.GlobalObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 if (table != nullptr && !table.empty()) {
 byteBufferWriter.putByte((byte)1);

 try {
 KahluaTableIterator kahluaTableIterator = table.iterator();

 while (kahluaTableIterator.advance()) {
 if (!TableNetworkUtils.canSave(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue())) {
 DebugLog.log("ERROR: sendServerCommand: can't save key,value=" +
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

 static void sendServerCommand(std::string_view string0,
 std::string_view string1, KahluaTable table) {
 BYTE_BUFFER.clear();
 writeServerCommand(string0, string1, table, BYTE_BUFFER_WRITER);
 sendPacket(BYTE_BUFFER);
 }

 static void addGlobalObjectOnClient(SGlobalObject sGlobalObject) {
 BYTE_BUFFER.clear();
 ByteBufferWriter byteBufferWriter = BYTE_BUFFER_WRITER;
 PacketTypes.PacketType.GlobalObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)3);
 byteBufferWriter.putUTF(sGlobalObject.system.name);
 byteBufferWriter.putInt(sGlobalObject.getX());
 byteBufferWriter.putInt(sGlobalObject.getY());
 byteBufferWriter.putByte((byte)sGlobalObject.getZ());
 SGlobalObjectSystem sGlobalObjectSystem =
 (SGlobalObjectSystem)sGlobalObject.system;
 TableNetworkUtils.saveSome(sGlobalObject.getModData(), byteBufferWriter.bb,
 sGlobalObjectSystem.objectSyncKeys);
 sendPacket(BYTE_BUFFER);
 }

 static void removeGlobalObjectOnClient(GlobalObject globalObject) {
 BYTE_BUFFER.clear();
 ByteBufferWriter byteBufferWriter = BYTE_BUFFER_WRITER;
 PacketTypes.PacketType.GlobalObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)4);
 byteBufferWriter.putUTF(globalObject.system.name);
 byteBufferWriter.putInt(globalObject.getX());
 byteBufferWriter.putInt(globalObject.getY());
 byteBufferWriter.putByte((byte)globalObject.getZ());
 sendPacket(BYTE_BUFFER);
 }

 static void updateGlobalObjectOnClient(SGlobalObject sGlobalObject) {
 BYTE_BUFFER.clear();
 ByteBufferWriter byteBufferWriter = BYTE_BUFFER_WRITER;
 PacketTypes.PacketType.GlobalObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)5);
 byteBufferWriter.putUTF(sGlobalObject.system.name);
 byteBufferWriter.putInt(sGlobalObject.getX());
 byteBufferWriter.putInt(sGlobalObject.getY());
 byteBufferWriter.putByte((byte)sGlobalObject.getZ());
 SGlobalObjectSystem sGlobalObjectSystem =
 (SGlobalObjectSystem)sGlobalObject.system;
 TableNetworkUtils.saveSome(sGlobalObject.getModData(), byteBufferWriter.bb,
 sGlobalObjectSystem.objectSyncKeys);
 sendPacket(BYTE_BUFFER);
 }

 static void receiveClientCommand(ByteBuffer byteBuffer, IsoPlayer player) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 bool boolean0 = byteBuffer.get() == 1;
 KahluaTable table = nullptr;
 if (boolean0) {
 table = LuaManager.platform.newTable();

 try {
 TableNetworkUtils.load(table, byteBuffer);
 } catch (Exception exception) {
 exception.printStackTrace();
 return;
 }
 }

 SGlobalObjects.receiveClientCommand(string0, string1, player, table);
 }
}
} // namespace globalObjects
} // namespace zombie
