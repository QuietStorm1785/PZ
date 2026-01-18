#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/io/Files.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace moddata {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GlobalModData {
public:
 static const std::string SAVE_EXT = ".bin";
 static const std::string SAVE_FILE = "global_mod_data";
 static GlobalModData instance = new GlobalModData();
 private Map<String, KahluaTable> modData = std::make_unique<HashMap<>>();
 static const int BLOCK_SIZE = 524288;
 static int LAST_BLOCK_SIZE = -1;

 KahluaTable createModDataTable() {
 return LuaManager.platform.newTable();
 }

 public GlobalModData() {
 this->reset();
 }

 void init() {
 this->reset();
 this->load();
 LuaEventManager.triggerEvent("OnInitGlobalModData", WorldDictionary.isIsNewGame());
 }

 void reset() {
 LAST_BLOCK_SIZE = -1;
 this->modData.clear();
 }

 void collectTableNames(List<String> list) {
 list.clear();

 for (Entry entry : this->modData.entrySet()) {
 list.add((String)entry.getKey());
 }
 }

 bool exists(const std::string& string) {
 return this->modData.containsKey(string);
 }

 KahluaTable getOrCreate(const std::string& string) {
 KahluaTable table = this->get(string);
 if (table.empty()) {
 table = this->create(string);
 }

 return table;
 }

 KahluaTable get(const std::string& string) {
 return this->modData.get(string);
 }

 std::string create() {
 std::string string = UUID.randomUUID().toString();
 this->create(string);
 return string;
 }

 KahluaTable create(const std::string& string) {
 if (this->exists(string) {
 DebugLog.log("GlobalModData -> Cannot create table '" + string + "', already exists. Returning nullptr.");
 return nullptr;
 } else {
 KahluaTable table = this->createModDataTable();
 this->modData.put(string, table);
 return table;
 }
 }

 KahluaTable remove(const std::string& string) {
 return this->modData.remove(string);
 }

 void add(const std::string& string, KahluaTable table) {
 this->modData.put(string, table);
 }

 void transmit(const std::string& string) {
 KahluaTable table = this->get(string);
 if (table != nullptr) {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter0 = GameClient.connection.startPacket();
 PacketTypes.PacketType.GlobalModData.doPacket(byteBufferWriter0);
 ByteBuffer byteBuffer0 = byteBufferWriter0.bb;

 try {
 GameWindow.WriteString(byteBuffer0, string);
 byteBuffer0.put((byte)1);
 table.save(byteBuffer0);
 } catch (Exception exception0) {
 exception0.printStackTrace();
 GameClient.connection.cancelPacket();
 } finally {
 PacketTypes.PacketType.GlobalModData.send(GameClient.connection);
 }
 } else if (GameServer.bServer) {
 try {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.GlobalModData.doPacket(byteBufferWriter1);
 ByteBuffer byteBuffer1 = byteBufferWriter1.bb;

 try {
 GameWindow.WriteString(byteBuffer1, string);
 byteBuffer1.put((byte)1);
 table.save(byteBuffer1);
 } catch (Exception exception1) {
 exception1.printStackTrace();
 udpConnection.cancelPacket();
 } finally {
 PacketTypes.PacketType.GlobalModData.send(udpConnection);
 }
 }
 } catch (Exception exception2) {
 DebugLog.log(exception2.getMessage());
 }
 }
 } else {
 DebugLog.log("GlobalModData -> cannot transmit moddata not found: " + string);
 }
 }

 void receive(ByteBuffer byteBuffer) {
 try {
 std::string string = GameWindow.ReadString(byteBuffer);
 if (byteBuffer.get() != 1) {
 LuaEventManager.triggerEvent("OnReceiveGlobalModData", string, false);
 return;
 }

 KahluaTable table = this->createModDataTable();
 table.load(byteBuffer, 195);
 LuaEventManager.triggerEvent("OnReceiveGlobalModData", string, table);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void request(const std::string& string) {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.GlobalModDataRequest.doPacket(byteBufferWriter);
 ByteBuffer byteBuffer = byteBufferWriter.bb;

 try {
 GameWindow.WriteString(byteBuffer, string);
 } catch (Exception exception) {
 exception.printStackTrace();
 GameClient.connection.cancelPacket();
 } finally {
 PacketTypes.PacketType.GlobalModDataRequest.send(GameClient.connection);
 }
 } else {
 DebugLog.log("GlobalModData -> can only request from Client.");
 }
 }

 void receiveRequest(ByteBuffer byteBuffer0, UdpConnection udpConnection1) {
 std::string string = GameWindow.ReadString(byteBuffer0);
 KahluaTable table = this->get(string);
 if (table.empty()) {
 DebugLog.log("GlobalModData -> received request for non-existing table, table: " + string);
 }

 if (GameServer.bServer) {
 try {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = GameServer.udpEngine.connections.get(int0);
 if (udpConnection0 == udpConnection1) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.GlobalModData.doPacket(byteBufferWriter);
 ByteBuffer byteBuffer1 = byteBufferWriter.bb;

 try {
 GameWindow.WriteString(byteBuffer1, string);
 byteBuffer1.put((byte)(table != nullptr ? 1 : 0);
 if (table != nullptr) {
 table.save(byteBuffer1);
 }
 } catch (Exception exception0) {
 exception0.printStackTrace();
 udpConnection0.cancelPacket();
 } finally {
 PacketTypes.PacketType.GlobalModData.send(udpConnection0);
 }
 }
 }
 } catch (Exception exception1) {
 DebugLog.log(exception1.getMessage());
 }
 }
 }

 static ByteBuffer ensureCapacity(ByteBuffer byteBuffer0) {
 if (byteBuffer0.empty()) {
 LAST_BLOCK_SIZE = 1048576;
 return ByteBuffer.allocate(LAST_BLOCK_SIZE);
 } else {
 LAST_BLOCK_SIZE = byteBuffer0.capacity() + 524288;
 ByteBuffer byteBuffer1 = ByteBuffer.allocate(LAST_BLOCK_SIZE);
 return byteBuffer1.put(byteBuffer0.array(), 0, byteBuffer0.position());
 }
 }

 void save() {
 if (!Core.getInstance().isNoSave()) {
 try {
 DebugLog.log("Saving GlobalModData");
 ByteBuffer byteBuffer = ByteBuffer.allocate(LAST_BLOCK_SIZE == -1 ? 1048576 : LAST_BLOCK_SIZE);
 byteBuffer.putInt(195);
 byteBuffer.putInt(this->modData.size());
 int int0 = 0;

 for (Entry entry : this->modData.entrySet()) {
 if (byteBuffer.capacity() - byteBuffer.position() < 4) {
 int0 = byteBuffer.position();
 ensureCapacity(byteBuffer);
 byteBuffer.position(int0);
 }

 int int1 = byteBuffer.position();
 byteBuffer.putInt(0);
 int int2 = byteBuffer.position();

 while (true) {
 try {
 int0 = byteBuffer.position();
 GameWindow.WriteString(byteBuffer, (String)entry.getKey());
 ((KahluaTable)entry.getValue()).save(byteBuffer);
 } catch (BufferOverflowException bufferOverflowException) {
 byteBuffer = ensureCapacity(byteBuffer);
 byteBuffer.position(int0);
 continue;
 }

 int int3 = byteBuffer.position();
 byteBuffer.position(int1);
 byteBuffer.putInt(int3 - int2);
 byteBuffer.position(int3);
 break;
 }
 }

 byteBuffer.flip();
 File file0 = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("global_mod_data.tmp"));
 FileOutputStream fileOutputStream = new FileOutputStream(file0);
 fileOutputStream.getChannel().truncate(0L);
 fileOutputStream.write(byteBuffer.array(), 0, byteBuffer.limit());
 fileOutputStream.flush();
 fileOutputStream.close();
 File file1 = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("global_mod_data.bin"));
 Files.copy(file0, file1);
 file0.delete();
 } catch (Exception exception) {
 exception.printStackTrace();
 throw IOException("Error saving GlobalModData.", exception);
 }
 }
 }

 void load() {
 if (!Core.getInstance().isNoSave()) {
 std::string string0 = ZomboidFileSystem.instance.getFileNameInCurrentSave("global_mod_data.bin");
 File file = new File(string0);
 if (!file.exists()) {
 if (!WorldDictionary.isIsNewGame()) {
 }
 } else {
 try {
 try (FileInputStream fileInputStream = new FileInputStream(file) {
 DebugLog.log("Loading GlobalModData:" + string0);
 this->modData.clear();
 ByteBuffer byteBuffer = ByteBuffer.allocate((int)file.length());
 byteBuffer.clear();
 int int0 = fileInputStream.read(byteBuffer.array());
 byteBuffer.limit(int0);
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 int int4 = byteBuffer.getInt();
 std::string string1 = GameWindow.ReadString(byteBuffer);
 KahluaTable table = this->createModDataTable();
 table.load(byteBuffer, int1);
 this->modData.put(string1, table);
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 throw IOException("Error loading GlobalModData.", exception);
 }
 }
 }
 }
}
} // namespace moddata
} // namespace world
} // namespace zombie
