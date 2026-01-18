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
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/globalObjects/CGlobalObjectNetwork.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SinglePlayerClient {
public:
 private static ArrayList<ZomboidNetData> MainLoopNetData = std::make_unique<ArrayList<>>();
 static const UdpEngine udpEngine = new SinglePlayerClient.UdpEngineClient();
 static const UdpConnection connection = new UdpConnection(udpEngine);

 static void addIncoming(short short0, ByteBuffer byteBuffer) {
 ZomboidNetData zomboidNetData;
 if (byteBuffer.remaining() > 2048) {
 zomboidNetData = ZomboidNetDataPool.instance.getLong(byteBuffer.remaining());
 } else {
 zomboidNetData = ZomboidNetDataPool.instance.get();
 }

 zomboidNetData.read(short0, byteBuffer, connection);
 synchronized (MainLoopNetData) {
 MainLoopNetData.add(zomboidNetData);
 }
 }

 static void update() {
 if (!GameClient.bClient) {
 for (short short0 = 0; short0 < IsoPlayer.numPlayers; short0++) {
 if (IsoPlayer.players[short0] != nullptr) {
 IsoPlayer.players[short0].setOnlineID(short0);
 }
 }

 synchronized (MainLoopNetData) {
 for (int int0 = 0; int0 < MainLoopNetData.size(); int0++) {
 ZomboidNetData zomboidNetData = MainLoopNetData.get(int0);

 try {
 mainLoopDealWithNetData(zomboidNetData);
 } finally {
 MainLoopNetData.remove(int0--);
 }
 }
 }
 }
 }

 static void mainLoopDealWithNetData(ZomboidNetData zomboidNetData) {
 ByteBuffer byteBuffer = zomboidNetData.buffer;

 try {
 PacketTypes.PacketType packetType = PacketTypes.packetTypes.get(zomboidNetData.type);
 switch (packetType) {
 case ClientCommand:
 receiveServerCommand(byteBuffer);
 break;
 case GlobalObjects:
 CGlobalObjectNetwork.receive(byteBuffer);
 break;
 case ObjectChange:
 receiveObjectChange(byteBuffer);
 break;
 default:
 throw IllegalStateException("Unexpected value: " + packetType);
 }
 } finally {
 ZomboidNetDataPool.instance.discard(zomboidNetData);
 }
 }

 static void delayPacket(int var0, int var1, int var2) {
 }

 static IsoPlayer getPlayerByID(int int0) {
 return IsoPlayer.players[int0];
 }

 static void receiveObjectChange(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 short short0 = byteBuffer.getShort();
 std::string string0 = GameWindow.ReadString(byteBuffer);
 if (Core.bDebug) {
 DebugLog.log("receiveObjectChange " + string0);
 }

 IsoPlayer player = getPlayerByID(short0);
 if (player != nullptr) {
 player.loadChange(string0, byteBuffer);
 }
 } else if (byte0 == 2) {
 short short1 = byteBuffer.getShort();
 std::string string1 = GameWindow.ReadString(byteBuffer);
 if (Core.bDebug) {
 DebugLog.log("receiveObjectChange " + string1);
 }

 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short1);
 if (vehicle != nullptr) {
 vehicle.loadChange(string1, byteBuffer);
 } else if (Core.bDebug) {
 DebugLog.log("receiveObjectChange: unknown vehicle id=" + short1);
 }
 } else if (byte0 == 3) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 std::string string2 = GameWindow.ReadString(byteBuffer);
 if (Core.bDebug) {
 DebugLog.log("receiveObjectChange " + string2);
 }

 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square0 == nullptr) {
 delayPacket(int0, int1, int2);
 return;
 }

 for (int int4 = 0; int4 < square0.getWorldObjects().size(); int4++) {
 IsoWorldInventoryObject worldInventoryObject = square0.getWorldObjects().get(int4);
 if (worldInventoryObject.getItem() != nullptr && worldInventoryObject.getItem().getID() == int3) {
 worldInventoryObject.loadChange(string2, byteBuffer);
 return;
 }
 }

 if (Core.bDebug) {
 DebugLog.log("receiveObjectChange: itemID=" + int3 + " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 }
 } else {
 int int5 = byteBuffer.getInt();
 int int6 = byteBuffer.getInt();
 int int7 = byteBuffer.getInt();
 int int8 = byteBuffer.getInt();
 std::string string3 = GameWindow.ReadString(byteBuffer);
 if (Core.bDebug) {
 DebugLog.log("receiveObjectChange " + string3);
 }

 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(int5, int6, int7);
 if (square1 == nullptr) {
 delayPacket(int5, int6, int7);
 return;
 }

 if (int8 >= 0 && int8 < square1.getObjects().size()) {
 IsoObject object = square1.getObjects().get(int8);
 object.loadChange(string3, byteBuffer);
 } else if (Core.bDebug) {
 DebugLog.log("receiveObjectChange: index=" + int8 + " is invalid x,y,z=" + int5 + "," + int6 + "," + int7);
 }
 }
 }

 static void sendClientCommand(IsoPlayer player, const std::string& string0, const std::string& string1, KahluaTable table) {
 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.ClientCommand.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)(player != nullptr ? player.PlayerIndex : -1);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 if (table != nullptr && !table.empty()) {
 byteBufferWriter.putByte((byte)1);

 try {
 KahluaTableIterator kahluaTableIterator = table.iterator();

 while (kahluaTableIterator.advance()) {
 if (!TableNetworkUtils.canSave(kahluaTableIterator.getKey(), kahluaTableIterator.getValue())) {
 DebugLog.log("ERROR: sendClientCommand: can't save key,value=" + kahluaTableIterator.getKey() + "," + kahluaTableIterator.getValue());
 }
 }

 TableNetworkUtils.save(table, byteBufferWriter.bb);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 } else {
 byteBufferWriter.putByte((byte)0);
 }

 connection.endPacketImmediate();
 }

 static void receiveServerCommand(ByteBuffer byteBuffer) {
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

 LuaEventManager.triggerEvent("OnServerCommand", string0, string1, table);
 }

 static void Reset() {
 for (auto& zomboidNetData : MainLoopNetData) ZomboidNetDataPool.instance.discard(zomboidNetData);
 }

 MainLoopNetData.clear();
 }

 private static class UdpEngineClient extends UdpEngine {
 void Send(ByteBuffer byteBuffer) {
 SinglePlayerServer.udpEngine.Receive(byteBuffer);
 }

 void Receive(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 short short0 = byteBuffer.getShort();
 SinglePlayerClient.addIncoming(short0, byteBuffer);
 }
 }
}
} // namespace spnetwork
} // namespace zombie
