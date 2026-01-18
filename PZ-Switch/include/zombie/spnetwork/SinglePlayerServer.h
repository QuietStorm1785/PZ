#pragma once
#include <mutex>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/globalObjects/SGlobalObjectNetwork.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
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
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SinglePlayerServer {
public:

 // Mutexes for synchronized blocks
 static std::mutex MainLoopNetData_mutex;
private
 static ArrayList<ZomboidNetData> MainLoopNetData =
 std::make_unique<ArrayList<>>();
public
 static SinglePlayerServer.UdpEngineServer udpEngine =
 new SinglePlayerServer.UdpEngineServer();

 static void addIncoming(short short0, ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 ZomboidNetData zomboidNetData;
 if (byteBuffer.remaining() > 2048) {
 zomboidNetData =
 ZomboidNetDataPool.instance.getLong(byteBuffer.remaining());
 } else {
 zomboidNetData = ZomboidNetDataPool.instance.get();
 }

 zomboidNetData.read(short0, byteBuffer, udpConnection);
 { std::lock_guard<std::mutex> __sync_lock__(MainLoopNetData_mutex); MainLoopNetData.add(zomboidNetData); }
 }

 static void sendObjectChange(IsoObject object, const std::string &string,
 KahluaTable table, UdpConnection udpConnection) {
 if (object.getSquare() != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ObjectChange.doPacket(byteBufferWriter);
 if (object instanceof IsoPlayer) {
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putShort(((IsoPlayer)object).OnlineID);
 } else if (object instanceof BaseVehicle) {
 byteBufferWriter.putByte((byte)2);
 byteBufferWriter.putShort(((BaseVehicle)object).getId());
 } else if (object instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putByte((byte)3);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putInt(
 ((IsoWorldInventoryObject)object).getItem().getID());
 } else {
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putInt(
 object.getSquare().getObjects().indexOf(object);
 }

 byteBufferWriter.putUTF(string);
 object.saveChange(string, table, byteBufferWriter.bb);
 udpConnection.endPacketImmediate();
 }
 }

 static void sendObjectChange(IsoObject object, const std::string &string,
 KahluaTable table) {
 if (object != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.ReleventTo(object.getX(), object.getY())) {
 sendObjectChange(object, string, table, udpConnection);
 }
 }
 }
 }

 static void sendObjectChange(IsoObject object0, const std::string &string,
 Object... objects) {
 if (objects.length == 0) {
 sendObjectChange(object0, string, (KahluaTable) nullptr);
 } else if (objects.length % 2 == 0) {
 KahluaTable table = LuaManager.platform.newTable();

 for (byte byte0 = 0; byte0 < objects.length; byte0 += 2) {
 void *object1 = objects[byte0 + 1];
 if (object1 instanceof Float) {
 table.rawset(objects[byte0], ((Float)object1).doubleValue());
 } else if (object1 instanceof Integer) {
 table.rawset(objects[byte0], ((Integer)object1).doubleValue());
 } else if (object1 instanceof Short) {
 table.rawset(objects[byte0], ((Short)object1).doubleValue());
 } else {
 table.rawset(objects[byte0], object1);
 }
 }

 sendObjectChange(object0, string, table);
 }
 }

 static void sendServerCommand(const std::string &string0,
 const std::string &string1, KahluaTable table,
 UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ClientCommand.doPacket(byteBufferWriter);
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
 iOException.printStackTrace();
 }
 } else {
 byteBufferWriter.putByte((byte)0);
 }

 udpConnection.endPacketImmediate();
 }

 static void sendServerCommand(const std::string &string0,
 const std::string &string1, KahluaTable table) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendServerCommand(string0, string1, table, udpConnection);
 }
 }

 static void update() {
 if (!GameClient.bClient) {
 for (short short0 = 0; short0 < IsoPlayer.numPlayers; short0++) {
 if (IsoPlayer.players[short0] != nullptr) {
 IsoPlayer.players[short0].setOnlineID(short0);
 }
 }

 { std::lock_guard<std::mutex> __sync_lock__(MainLoopNetData_mutex);
 for (int int0 = 0; int0 < MainLoopNetData.size(); int0++) {
 ZomboidNetData zomboidNetData = MainLoopNetData.get(int0);
 mainLoopDealWithNetData(zomboidNetData);
 MainLoopNetData.remove(int0--);
 }
 }
 }
 }

 static void mainLoopDealWithNetData(ZomboidNetData zomboidNetData) {
 ByteBuffer byteBuffer = zomboidNetData.buffer;

 try {
 PacketTypes.PacketType packetType =
 PacketTypes.packetTypes.get(zomboidNetData.type);
 switch (packetType) {
 case ClientCommand:
 receiveClientCommand(byteBuffer, zomboidNetData.connection);
 break;
 case GlobalObjects:
 receiveGlobalObjects(byteBuffer, zomboidNetData.connection);
 }
 } finally {
 ZomboidNetDataPool.instance.discard(zomboidNetData);
 }
 }

 static IsoPlayer getAnyPlayerFromConnection(UdpConnection udpConnection) {
 for (int int0 = 0; int0 < 4; int0++) {
 if (udpConnection.players[int0] != nullptr) {
 return udpConnection.players[int0];
 }
 }

 return nullptr;
 }

 static IsoPlayer getPlayerFromConnection(UdpConnection udpConnection,
 int int0) {
 return int0 >= 0 && int0 < 4 ? udpConnection.players[int0] : nullptr;
 }

 static void receiveClientCommand(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 uint8_t byte0 = byteBuffer.get();
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

 IsoPlayer player = getPlayerFromConnection(udpConnection, byte0);
 if (byte0 == -1) {
 player = getAnyPlayerFromConnection(udpConnection);
 }

 if (player.empty()) {
 DebugLog.log("receiveClientCommand: player is nullptr");
 } else {
 LuaEventManager.triggerEvent("OnClientCommand", string0, string1, player,
 table);
 }
 }

 static void receiveGlobalObjects(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 uint8_t byte0 = byteBuffer.get();
 IsoPlayer player = getPlayerFromConnection(udpConnection, byte0);
 if (byte0 == -1) {
 player = getAnyPlayerFromConnection(udpConnection);
 }

 if (player.empty()) {
 DebugLog.log("receiveGlobalObjects: player is nullptr");
 } else {
 SGlobalObjectNetwork.receive(byteBuffer, player);
 }
 }

 static void Reset() {
 for (auto &zomboidNetData : MainLoopNetData)
 ZomboidNetDataPool.instance.discard(zomboidNetData);
 }

 MainLoopNetData.clear();
}

public static class UdpEngineServer extends UdpEngine {
public
 ArrayList<UdpConnection> connections = std::make_unique<ArrayList<>>();

 UdpEngineServer() { this->connections.add(new UdpConnection(this); }

 void Send(ByteBuffer byteBuffer) {
 SinglePlayerClient.udpEngine.Receive(byteBuffer);
 }

 void Receive(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 short short0 = byteBuffer.getShort();
 SinglePlayerServer.addIncoming(
 short0, byteBuffer, SinglePlayerServer.udpEngine.connections.get(0);
 }
}
}
} // namespace spnetwork
} // namespace zombie
