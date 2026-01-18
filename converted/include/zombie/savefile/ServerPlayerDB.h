#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/Connection.h"
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "java/sql/Statement.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace savefile {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ServerPlayerDB {
public:
 static ServerPlayerDB instance = nullptr;
 static bool allow = false;
 Connection conn = nullptr;
 private ConcurrentLinkedQueue<ServerPlayerDB.NetworkCharacterData> CharactersToSave;

 static void setAllow(bool boolean0) {
 allow = boolean0;
 }

 static bool isAllow() {
 return allow;
 }

 public static synchronized ServerPlayerDB getInstance() {
 if (instance == nullptr && allow) {
 instance = std::make_unique<ServerPlayerDB>();
 }

 return instance;
 }

 static bool isAvailable() {
 return instance != nullptr;
 }

 public ServerPlayerDB() {
 if (!Core.getInstance().isNoSave()) {
 this->create();
 }
 }

 void close() {
 instance = nullptr;
 allow = false;
 }

 void create() {
 this->conn = PlayerDBHelper.create();
 this->CharactersToSave = std::make_unique<ConcurrentLinkedQueue<>>();
 DatabaseMetaData databaseMetaData = nullptr;

 try {
 databaseMetaData = this->conn.getMetaData();
 Statement statement = this->conn.createStatement();
 ResultSet resultSet = databaseMetaData.getColumns(nullptr, nullptr, "networkPlayers", "steamid");
 if (!resultSet.next()) {
 statement.executeUpdate("ALTER TABLE 'networkPlayers' ADD 'steamid' STRING NULL");
 }

 resultSet.close();
 statement.close();
 } catch (SQLException sQLException) {
 sQLException.printStackTrace();
 }
 }

 void process() {
 if (!this->CharactersToSave.empty()) {
 for (ServerPlayerDB.NetworkCharacterData networkCharacterData = this->CharactersToSave.poll();
 networkCharacterData != nullptr;
 networkCharacterData = this->CharactersToSave.poll()
 ) {
 this->serverUpdateNetworkCharacterInt(networkCharacterData);
 }
 }
 }

 void serverUpdateNetworkCharacter(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->CharactersToSave.add(new ServerPlayerDB.NetworkCharacterData(byteBuffer, udpConnection);
 }

 void serverUpdateNetworkCharacterInt(ServerPlayerDB.NetworkCharacterData networkCharacterData) {
 if (networkCharacterData.playerIndex >= 0 && networkCharacterData.playerIndex < 4) {
 if (this->conn != nullptr) {
 std::string string0;
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 string0 = "SELECT id FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
 } else {
 string0 = "SELECT id FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
 }

 std::string string1 = "INSERT INTO networkPlayers(world,username,steamid, playerIndex,name,x,y,z,worldversion,isDead,data) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
 std::string string2 = "UPDATE networkPlayers SET x=?, y=?, z=?, worldversion = ?, isDead = ?, data = ?, name = ? WHERE id=?";

 try {
 try (PreparedStatement preparedStatement0 = this->conn.prepareStatement(string0) {
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 preparedStatement0.setString(1, networkCharacterData.steamid);
 } else {
 preparedStatement0.setString(1, networkCharacterData.username);
 }

 preparedStatement0.setString(2, Core.GameSaveWorld);
 preparedStatement0.setInt(3, networkCharacterData.playerIndex);
 ResultSet resultSet = preparedStatement0.executeQuery();
 if (resultSet.next()) {
 int int0 = resultSet.getInt(1);

 try (PreparedStatement preparedStatement1 = this->conn.prepareStatement(string2) {
 preparedStatement1.setFloat(1, networkCharacterData.x);
 preparedStatement1.setFloat(2, networkCharacterData.y);
 preparedStatement1.setFloat(3, networkCharacterData.z);
 preparedStatement1.setInt(4, networkCharacterData.worldVersion);
 preparedStatement1.setBoolean(5, networkCharacterData.isDead);
 preparedStatement1.setBytes(6, networkCharacterData.buffer);
 preparedStatement1.setString(7, networkCharacterData.playerName);
 preparedStatement1.setInt(8, int0);
 int int1 = preparedStatement1.executeUpdate();
 this->conn.commit();
 return;
 }
 }
 }

 try (PreparedStatement preparedStatement2 = this->conn.prepareStatement(string1) {
 preparedStatement2.setString(1, Core.GameSaveWorld);
 preparedStatement2.setString(2, networkCharacterData.username);
 preparedStatement2.setString(3, networkCharacterData.steamid);
 preparedStatement2.setInt(4, networkCharacterData.playerIndex);
 preparedStatement2.setString(5, networkCharacterData.playerName);
 preparedStatement2.setFloat(6, networkCharacterData.x);
 preparedStatement2.setFloat(7, networkCharacterData.y);
 preparedStatement2.setFloat(8, networkCharacterData.z);
 preparedStatement2.setInt(9, networkCharacterData.worldVersion);
 preparedStatement2.setBoolean(10, networkCharacterData.isDead);
 preparedStatement2.setBytes(11, networkCharacterData.buffer);
 int int2 = preparedStatement2.executeUpdate();
 this->conn.commit();
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 PlayerDBHelper.rollback(this->conn);
 }
 }
 }
 }

 void serverConvertNetworkCharacter(const std::string& string2, const std::string& string1) {
 try {
 std::string string0 = "UPDATE networkPlayers SET steamid=? WHERE username=? AND world=? AND (steamid is nullptr or steamid = '')";

 try (PreparedStatement preparedStatement = this->conn.prepareStatement(string0) {
 preparedStatement.setString(1, string1);
 preparedStatement.setString(2, string2);
 preparedStatement.setString(3, Core.GameSaveWorld);
 int int0 = preparedStatement.executeUpdate();
 if (int0 > 0) {
 DebugLog.General.warn("serverConvertNetworkCharacter: The steamid was set for the '" + string2 + "' for " + int0 + " players. ");
 }

 this->conn.commit();
 }
 } catch (SQLException sQLException) {
 ExceptionLogger.logException(sQLException);
 }
 }

 void serverLoadNetworkCharacter(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 < 0 || byte0 >= 4) {
 ByteBufferWriter byteBufferWriter0 = udpConnection.startPacket();
 PacketTypes.PacketType.LoadPlayerProfile.doPacket(byteBufferWriter0);
 byteBufferWriter0.putByte((byte)0);
 byteBufferWriter0.putInt(byte0);
 PacketTypes.PacketType.LoadPlayerProfile.send(udpConnection);
 } else if (this->conn != nullptr) {
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 this->serverConvertNetworkCharacter(udpConnection.username, udpConnection.idStr);
 }

 std::string string;
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 string = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
 } else {
 string = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
 }

 try (PreparedStatement preparedStatement = this->conn.prepareStatement(string) {
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 preparedStatement.setString(1, udpConnection.idStr);
 } else {
 preparedStatement.setString(1, udpConnection.username);
 }

 preparedStatement.setString(2, Core.GameSaveWorld);
 preparedStatement.setInt(3, byte0);
 ResultSet resultSet = preparedStatement.executeQuery();
 if (resultSet.next()) {
 int int0 = resultSet.getInt(1);
 float float0 = resultSet.getFloat(2);
 float float1 = resultSet.getFloat(3);
 float float2 = resultSet.getFloat(4);
 byte[] bytes = resultSet.getBytes(5);
 int int1 = resultSet.getInt(6);
 bool boolean0 = resultSet.getBoolean(7);
 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.LoadPlayerProfile.doPacket(byteBufferWriter1);
 byteBufferWriter1.putByte((byte)1);
 byteBufferWriter1.putInt(byte0);
 byteBufferWriter1.putFloat(float0);
 byteBufferWriter1.putFloat(float1);
 byteBufferWriter1.putFloat(float2);
 byteBufferWriter1.putInt(int1);
 byteBufferWriter1.putByte((byte)(boolean0 ? 1 : 0);
 byteBufferWriter1.putInt(bytes.length);
 byteBufferWriter1.bb.put(bytes);
 PacketTypes.PacketType.LoadPlayerProfile.send(udpConnection);
 } else {
 ByteBufferWriter byteBufferWriter2 = udpConnection.startPacket();
 PacketTypes.PacketType.LoadPlayerProfile.doPacket(byteBufferWriter2);
 byteBufferWriter2.putByte((byte)0);
 byteBufferWriter2.putInt(byte0);
 PacketTypes.PacketType.LoadPlayerProfile.send(udpConnection);
 }
 } catch (SQLException sQLException) {
 ExceptionLogger.logException(sQLException);
 }
 }
 }

 private static class NetworkCharacterData {
 byte[] buffer;
 std::string username;
 std::string steamid;
 int playerIndex;
 std::string playerName;
 float x;
 float y;
 float z;
 bool isDead;
 int worldVersion;

 public NetworkCharacterData(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->playerIndex = byteBuffer.get();
 this->playerName = GameWindow.ReadStringUTF(byteBuffer);
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.getFloat();
 this->isDead = byteBuffer.get() == 1;
 this->worldVersion = byteBuffer.getInt();
 int int0 = byteBuffer.getInt();
 this->buffer = new byte[int0];
 byteBuffer.get(this->buffer);
 if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
 this->steamid = udpConnection.idStr;
 } else {
 this->steamid = "";
 }

 this->username = udpConnection.username;
 }
 }
}
} // namespace savefile
} // namespace zombie
