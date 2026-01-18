#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace savefile {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClientPlayerDB {
public:
 static ClientPlayerDB instance = nullptr;
 static bool allow = false;
 private ClientPlayerDB.NetworkCharacterProfile networkProfile = nullptr;
 UpdateLimit saveToDBPeriod4Network = new UpdateLimit(30000L);
 static ByteBuffer SliceBuffer4NetworkPlayer = ByteBuffer.allocate(65536);
 bool forceSavePlayers;
 bool canSavePlayers = false;

 static void setAllow(bool boolean0) {
 allow = boolean0;
 }

 static bool isAllow() {
 return allow;
 }

 public static synchronized ClientPlayerDB getInstance() {
 if (instance == nullptr && allow) {
 instance = std::make_unique<ClientPlayerDB>();
 }

 return instance;
 }

 static bool isAvailable() {
 return instance != nullptr;
 }

 void updateMain() {
 this->saveNetworkPlayersToDB();
 }

 void close() {
 instance = nullptr;
 allow = false;
 }

 void saveNetworkPlayersToDB() {
 if (this->canSavePlayers && (this->forceSavePlayers || this->saveToDBPeriod4Network.Check())) {
 this->forceSavePlayers = false;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 this->clientSendNetworkPlayerInt(player);
 }
 }
 }
 }

 public ArrayList<IsoPlayer> getAllNetworkPlayers() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 1; int0 < this->networkProfile.playerCount; int0++) {
 byte[] bytes = this->getClientLoadNetworkPlayerData(int0 + 1);
 if (bytes != nullptr) {
 ByteBuffer byteBuffer = ByteBuffer.allocate(bytes.length);
 byteBuffer.rewind();
 byteBuffer.put(bytes);
 byteBuffer.rewind();

 try {
 IsoPlayer player = new IsoPlayer(IsoWorld.instance.CurrentCell);
 player.serverPlayerIndex = int0 + 1;
 player.load(byteBuffer, this->networkProfile.worldVersion[int0]);
 if (this->networkProfile.isDead[int0]) {
 player.getBodyDamage().setOverallBodyHealth(0.0F);
 player.setHealth(0.0F);
 }

 arrayList.add(player);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }

 return arrayList;
 }

 void clientLoadNetworkCharacter(ByteBuffer byteBuffer, UdpConnection var2) {
 bool boolean0 = byteBuffer.get() == 1;
 int int0 = byteBuffer.getInt();
 if (boolean0) {
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 int int1 = byteBuffer.getInt();
 bool boolean1 = byteBuffer.get() == 1;
 int int2 = byteBuffer.getInt();
 byte[] bytes = new byte[int2];
 byteBuffer.get(bytes);
 if (this->networkProfile != nullptr) {
 this->networkProfile.playerCount++;
 switch (this->networkProfile.playerCount) {
 case 2:
 this->networkProfile.worldVersion[1] = int1;
 this->networkProfile.character[1] = bytes;
 this->networkProfile.x[1] = float0;
 this->networkProfile.y[1] = float1;
 this->networkProfile.z[1] = float2;
 this->networkProfile.isDead[1] = boolean1;
 break;
 case 3:
 this->networkProfile.worldVersion[2] = int1;
 this->networkProfile.character[2] = bytes;
 this->networkProfile.x[2] = float0;
 this->networkProfile.y[2] = float1;
 this->networkProfile.z[2] = float2;
 this->networkProfile.isDead[2] = boolean1;
 break;
 case 4:
 this->networkProfile.worldVersion[3] = int1;
 this->networkProfile.character[3] = bytes;
 this->networkProfile.x[3] = float0;
 this->networkProfile.y[3] = float1;
 this->networkProfile.z[3] = float2;
 this->networkProfile.isDead[3] = boolean1;
 }
 } else {
 this->networkProfile = new ClientPlayerDB.NetworkCharacterProfile();
 this->networkProfile.playerCount = 1;
 this->networkProfile.username = GameClient.username;
 this->networkProfile.server = GameClient.ip;
 this->networkProfile.character[0] = bytes;
 this->networkProfile.worldVersion[0] = int1;
 this->networkProfile.x[0] = float0;
 this->networkProfile.y[0] = float1;
 this->networkProfile.z[0] = float2;
 this->networkProfile.isDead[0] = boolean1;
 }

 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.LoadPlayerProfile.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)(int0 + 1);
 PacketTypes.PacketType.LoadPlayerProfile.send(GameClient.connection);
 } else if (this->networkProfile != nullptr) {
 this->networkProfile.isLoaded = true;
 } else {
 this->networkProfile = new ClientPlayerDB.NetworkCharacterProfile();
 this->networkProfile.isLoaded = true;
 this->networkProfile.playerCount = 0;
 this->networkProfile.username = GameClient.username;
 this->networkProfile.server = GameClient.ip;
 this->networkProfile.character[0] = nullptr;
 this->networkProfile.worldVersion[0] = IsoWorld.getWorldVersion();
 }
 }

 bool isClientLoadNetworkCharacterCompleted() {
 return this->networkProfile != nullptr && this->networkProfile.isLoaded;
 }

 void clientSendNetworkPlayerInt(IsoPlayer player) {
 if (GameClient.connection != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SendPlayerProfile.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)(player.serverPlayerIndex - 1);
 std::string string = player.getDescriptor().getForename() + " " + player.getDescriptor().getSurname();
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putFloat(player.x);
 byteBufferWriter.putFloat(player.y);
 byteBufferWriter.putFloat(player.z);
 byteBufferWriter.putByte((byte)(player.isDead() ? 1 : 0);
 SliceBuffer4NetworkPlayer.rewind();
 player.save(SliceBuffer4NetworkPlayer);
 byte[] bytes = new byte[SliceBuffer4NetworkPlayer.position()];
 SliceBuffer4NetworkPlayer.rewind();
 SliceBuffer4NetworkPlayer.get(bytes);
 byteBufferWriter.putInt(IsoWorld.getWorldVersion());
 byteBufferWriter.putInt(SliceBuffer4NetworkPlayer.position());
 byteBufferWriter.bb.put(bytes);
 PacketTypes.PacketType.SendPlayerProfile.send(GameClient.connection);
 } catch (IOException iOException) {
 GameClient.connection.cancelPacket();
 ExceptionLogger.logException(iOException);
 } catch (BufferOverflowException bufferOverflowException) {
 GameClient.connection.cancelPacket();
 int int0 = SliceBuffer4NetworkPlayer.capacity();
 if (int0 > 2097152) {
 DebugLog.log("FATAL ERROR: The player " + player.getUsername() + " cannot be saved");
 ExceptionLogger.logException(bufferOverflowException);
 return;
 }

 SliceBuffer4NetworkPlayer = ByteBuffer.allocate(int0 * 2);
 this->clientSendNetworkPlayerInt(player);
 }
 }
 }

 bool isAliveMainNetworkPlayer() {
 return !this->networkProfile.isDead[0];
 }

 bool clientLoadNetworkPlayer() {
 if (this->networkProfile != nullptr
 && this->networkProfile.isLoaded
 && this->networkProfile.username == GameClient.username)
 && this->networkProfile.server == GameClient.ip) {
 return this->networkProfile.playerCount > 0;
 } else if (GameClient.connection == nullptr) {
 return false;
 } else {
 if (this->networkProfile != nullptr) {
 this->networkProfile = nullptr;
 }

 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.LoadPlayerProfile.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)0);
 PacketTypes.PacketType.LoadPlayerProfile.send(GameClient.connection);
 int int0 = 200;

 while (int0-- > 0) {
 if (this->isClientLoadNetworkCharacterCompleted()) {
 return this->networkProfile.playerCount > 0;
 }

 try {
 Thread.sleep(50L);
 } catch (InterruptedException interruptedException) {
 ExceptionLogger.logException(interruptedException);
 }
 }

 return false;
 }
 }

 public byte[] getClientLoadNetworkPlayerData(int int0) {
 if (this->networkProfile != nullptr
 && this->networkProfile.isLoaded
 && this->networkProfile.username == GameClient.username)
 && this->networkProfile.server == GameClient.ip) {
 switch (int0) {
 case 1:
 case 2:
 case 3:
 case 4:
 return this->networkProfile.character[int0 - 1];
 default:
 return nullptr;
 }
 } else if (!this->clientLoadNetworkPlayer()) {
 return nullptr;
 } else {
 switch (int0) {
 case 1:
 case 2:
 case 3:
 case 4:
 return this->networkProfile.character[int0 - 1];
 default:
 return nullptr;
 }
 }
 }

 bool loadNetworkPlayer() {
 try {
 byte[] bytes = this->getClientLoadNetworkPlayerData(1);
 if (bytes != nullptr) {
 ByteBuffer byteBuffer = ByteBuffer.allocate(bytes.length);
 byteBuffer.rewind();
 byteBuffer.put(bytes);
 byteBuffer.rewind();
 if (IsoPlayer.getInstance() == nullptr) {
 IsoPlayer.setInstance(new IsoPlayer(IsoCell.getInstance()));
 IsoPlayer.players[0] = IsoPlayer.getInstance();
 }

 IsoPlayer.getInstance().serverPlayerIndex = 1;
 IsoPlayer.getInstance().load(byteBuffer, this->networkProfile.worldVersion[0]);
 return true;
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 return false;
 }

 bool loadNetworkPlayerInfo(int int0) {
 if (this->networkProfile != nullptr
 && this->networkProfile.isLoaded
 && this->networkProfile.username == GameClient.username)
 && this->networkProfile.server == GameClient.ip)
 && int0 >= 1
 && int0 <= 4
 && int0 <= this->networkProfile.playerCount) {
 int int1 = (int)(this->networkProfile.x[int0 - 1] / 10.0F) + IsoWorld.saveoffsetx * 30;
 int int2 = (int)(this->networkProfile.y[int0 - 1] / 10.0F) + IsoWorld.saveoffsety * 30;
 IsoChunkMap.WorldXA = (int)this->networkProfile.x[int0 - 1];
 IsoChunkMap.WorldYA = (int)this->networkProfile.y[int0 - 1];
 IsoChunkMap.WorldZA = (int)this->networkProfile.z[int0 - 1];
 IsoChunkMap.WorldXA = IsoChunkMap.WorldXA + 300 * IsoWorld.saveoffsetx;
 IsoChunkMap.WorldYA = IsoChunkMap.WorldYA + 300 * IsoWorld.saveoffsety;
 IsoChunkMap.SWorldX[0] = int1;
 IsoChunkMap.SWorldY[0] = int2;
 IsoChunkMap.SWorldX[0] = IsoChunkMap.SWorldX[0] + 30 * IsoWorld.saveoffsetx;
 IsoChunkMap.SWorldY[0] = IsoChunkMap.SWorldY[0] + 30 * IsoWorld.saveoffsety;
 return true;
 } else {
 return false;
 }
 }

 void forgetPlayer(int int0) {
 if (this->networkProfile != nullptr && int0 >= 1 && int0 <= 4) {
 this->networkProfile.character[int0 - 1] = nullptr;
 this->networkProfile.isDead[int0 - 1] = true;
 }
 }

 int getNextServerPlayerIndex() {
 if (this->networkProfile != nullptr
 && this->networkProfile.isLoaded
 && this->networkProfile.username == GameClient.username)
 && this->networkProfile.server == GameClient.ip) {
 for (int int0 = 1; int0 < 4; int0++) {
 if (this->networkProfile.character[int0] == nullptr || this->networkProfile.isDead[int0]) {
 return int0 + 1;
 }
 }
 }

 return 2;
 }

 private class NetworkCharacterProfile {
 bool isLoaded = false;
 byte[][] character;
 std::string username;
 std::string server;
 int playerCount = 0;
 int[] worldVersion;
 float[] x;
 float[] y;
 float[] z;
 boolean[] isDead;

 public NetworkCharacterProfile() {
 this->character = new byte[4][];
 this->worldVersion = new int[4];
 this->x = new float[4];
 this->y = new float[4];
 this->z = new float[4];
 this->isDead = new boolean[4];
 }
 }
}
} // namespace savefile
} // namespace zombie
