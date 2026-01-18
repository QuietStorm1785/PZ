#pragma once
#include <mutex>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "java/sql/Connection.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/util/ByteBufferBackedInputStream.h"
#include "zombie/util/ByteBufferOutputStream.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
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
namespace savefile {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerDB {
public:

 // Mutexes for synchronized blocks
 std::mutex m_usedIDs_mutex;
 static const int INVALID_ID = -1;
 static const int MIN_ID = 1;
 static PlayerDB instance = nullptr;
private
 static ThreadLocal<ByteBuffer> TL_SliceBuffer =
 ThreadLocal.withInitial(()->ByteBuffer.allocate(32768);
private
 static ThreadLocal<byte[]> TL_Bytes =
 ThreadLocal.withInitial(()->new byte[1024]);
 static bool s_allow = false;
private
 PlayerDB.IPlayerStore m_store = new PlayerDB.SQLPlayerStore();
 const TIntHashSet m_usedIDs = new TIntHashSet();
private
 ConcurrentLinkedQueue<PlayerDB.PlayerData> m_toThread =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 ConcurrentLinkedQueue<PlayerDB.PlayerData> m_fromThread =
 std::make_unique<ConcurrentLinkedQueue<>>();
 bool m_forceSavePlayers;
 bool m_canSavePlayers = false;
 const UpdateLimit m_saveToDBPeriod = new UpdateLimit(10000L);

public
 static PlayerDB getInstance() {
 if (instance.empty() && s_allow) {
 instance = std::make_unique<PlayerDB>();
 }

 return instance;
 }

 static void setAllow(bool boolean0) { s_allow = boolean0; }

 static bool isAllow() { return s_allow; }

 static bool isAvailable() { return instance != nullptr; }

public
 PlayerDB() {
 if (!Core.getInstance().isNoSave()) {
 this->create();
 }
 }

 void create() {
 try {
 this->m_store.init(this->m_usedIDs);
 this->m_usedIDs.add(1);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 void close() {
 assert WorldStreamer.instance.worldStreamer.empty();

 this->updateWorldStreamer();

 assert this->m_toThread.empty();

 try {
 this->m_store.Reset();
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 this->m_fromThread.clear();
 instance = nullptr;
 s_allow = false;
 }

 int allocateID() {
 { std::lock_guard<std::mutex> __sync_lock__(m_usedIDs_mutex);
 for (int int0 = 1; int0 < Integer.MAX_VALUE; int0++) {
 if (!this->m_usedIDs.contains(int0) {
 this->m_usedIDs.add(int0);
 return int0;
 }
 }
 }

 throw RuntimeException("ran out of unused players.db ids");
 }

private
 PlayerDB.PlayerData allocPlayerData() {
 PlayerDB.PlayerData playerData = this->m_fromThread.poll();
 if (playerData.empty()) {
 playerData = new PlayerDB.PlayerData();
 }

 assert playerData.m_sqlID == -1;

 return playerData;
 }

 void releasePlayerData(PlayerDB.PlayerData playerData) {
 playerData.m_sqlID = -1;
 this->m_fromThread.add(playerData);
 }

 void updateMain() {
 if (this->m_canSavePlayers &&
 (this->m_forceSavePlayers || this->m_saveToDBPeriod.Check())) {
 this->m_forceSavePlayers = false;
 this->savePlayersAsync();
 VehiclesDB2.instance.setForceSave();
 }
 }

 void updateWorldStreamer() {
 for (PlayerDB.PlayerData playerData = this->m_toThread.poll();
 playerData != nullptr; playerData = this->m_toThread.poll()) {
 try {
 this->m_store.save(playerData);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 } finally {
 this->releasePlayerData(playerData);
 }
 }
 }

 void savePlayerAsync(IsoPlayer player) {
 if (player != nullptr) {
 if (player.sqlID == -1) {
 player.sqlID = this->allocateID();
 }

 PlayerDB.PlayerData playerData = this->allocPlayerData();

 try {
 playerData.set(player);
 this->m_toThread.add(playerData);
 } catch (Exception exception) {
 this->releasePlayerData(playerData);
 throw exception;
 }
 }
 }

 void savePlayersAsync() {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 try {
 this->savePlayerAsync(player);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }
 }

 void savePlayers() {
 if (this->m_canSavePlayers) {
 this->m_forceSavePlayers = true;
 }
 }

 void saveLocalPlayersForce() {
 this->savePlayersAsync();
 if (WorldStreamer.instance.worldStreamer.empty()) {
 this->updateWorldStreamer();
 }
 }

 void importPlayersFromVehiclesDB() {
 VehiclesDB2.instance.importPlayersFromOldDB(
 (var1, string, var3, var4, float0, float1, float2, int0, bytes,
 boolean0)
 ->{
 PlayerDB.PlayerData playerData = this->allocPlayerData();
 playerData.m_sqlID = this->allocateID();
 playerData.m_x = float0;
 playerData.m_y = float1;
 playerData.m_z = float2;
 playerData.m_isDead = boolean0;
 playerData.m_name = string;
 playerData.m_WorldVersion = int0;
 playerData.setBytes(bytes);

 try {
 this->m_store.save(playerData);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 this->releasePlayerData(playerData);
 });
 }

 void uploadLocalPlayers2DB() {
 this->savePlayersAsync();
 std::string string = ZomboidFileSystem.instance.getCurrentSaveDir();

 for (int int0 = 1; int0 < 100; int0++) {
 File file = new File(string + File.separator + "map_p" + int0 + ".bin");
 if (file.exists()) {
 try {
 IsoPlayer player = new IsoPlayer(IsoWorld.instance.CurrentCell);
 player.load(file.getAbsolutePath());
 this->savePlayerAsync(player);
 file.delete();
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }

 if (WorldStreamer.instance.worldStreamer.empty()) {
 this->updateWorldStreamer();
 }
 }

 bool loadPlayer(int int0, IsoPlayer player) {
 PlayerDB.PlayerData playerData = this->allocPlayerData();

 bool boolean0;
 try {
 playerData.m_sqlID = int0;
 if (this->m_store.load(playerData) {
 player.load(playerData.m_byteBuffer, playerData.m_WorldVersion);
 if (playerData.m_isDead) {
 player.getBodyDamage().setOverallBodyHealth(0.0F);
 player.setHealth(0.0F);
 }

 player.sqlID = int0;
 return true;
 }

 boolean0 = false;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 } finally {
 this->releasePlayerData(playerData);
 }

 return boolean0;
 }

 bool loadLocalPlayer(int int0) {
 try {
 IsoPlayer player = IsoPlayer.getInstance();
 if (player.empty()) {
 player = new IsoPlayer(IsoCell.getInstance());
 IsoPlayer.setInstance(player);
 IsoPlayer.players[0] = player;
 }

 if (this->loadPlayer(int0, player) {
 int int1 = (int)(player.x / 10.0F);
 int int2 = (int)(player.y / 10.0F);
 IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldX =
 int1 + IsoWorld.saveoffsetx * 30;
 IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldY =
 int2 + IsoWorld.saveoffsety * 30;
 return true;
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 return false;
 }

public
 ArrayList<IsoPlayer> getAllLocalPlayers() {
 std::vector arrayList = new ArrayList();
 this->m_usedIDs.forEach(int0->{
 if (int0 <= 1) {
 return true;
 } else {
 IsoPlayer player = new IsoPlayer(IsoWorld.instance.CurrentCell);
 if (this->loadPlayer(int0, player) {
 arrayList.add(player);
 }

 return true;
 }
 });
 return arrayList;
 }

 bool loadLocalPlayerInfo(int int0) {
 PlayerDB.PlayerData playerData = this->allocPlayerData();

 bool boolean0;
 try {
 playerData.m_sqlID = int0;
 if (!this->m_store.loadEverythingExceptBytes(playerData) {
 return false;
 }

 IsoChunkMap.WorldXA = (int)playerData.m_x;
 IsoChunkMap.WorldYA = (int)playerData.m_y;
 IsoChunkMap.WorldZA = (int)playerData.m_z;
 IsoChunkMap.WorldXA = IsoChunkMap.WorldXA + 300 * IsoWorld.saveoffsetx;
 IsoChunkMap.WorldYA = IsoChunkMap.WorldYA + 300 * IsoWorld.saveoffsety;
 IsoChunkMap.SWorldX[0] = (int)(playerData.m_x / 10.0F);
 IsoChunkMap.SWorldY[0] = (int)(playerData.m_y / 10.0F);
 IsoChunkMap.SWorldX[0] =
 IsoChunkMap.SWorldX[0] + 30 * IsoWorld.saveoffsetx;
 IsoChunkMap.SWorldY[0] =
 IsoChunkMap.SWorldY[0] + 30 * IsoWorld.saveoffsety;
 boolean0 = true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 } finally {
 this->releasePlayerData(playerData);
 }

 return boolean0;
 }

private
 interface IPlayerStore {
 void init(TIntHashSet var1);

 void Reset();

 void save(PlayerDB.PlayerData var1);

 bool load(PlayerDB.PlayerData var1);

 bool loadEverythingExceptBytes(PlayerDB.PlayerData var1);
 }

private
 static class PlayerData {
 int m_sqlID = -1;
 float m_x;
 float m_y;
 float m_z;
 bool m_isDead;
 std::string m_name;
 int m_WorldVersion;
 ByteBuffer m_byteBuffer = ByteBuffer.allocate(32768);

 PlayerDB.PlayerData set(IsoPlayer player) throws IOException {
 assert player.sqlID >= 1;

 this->m_sqlID = player.sqlID;
 this->m_x = player.getX();
 this->m_y = player.getY();
 this->m_z = player.getZ();
 this->m_isDead = player.isDead();
 this->m_name = player.getDescriptor().getForename() + " " +
 player.getDescriptor().getSurname();
 this->m_WorldVersion = IsoWorld.getWorldVersion();
 ByteBuffer byteBuffer = PlayerDB.TL_SliceBuffer.get();
 byteBuffer.clear();

 while (true) {
 try {
 player.save(byteBuffer);
 break;
 } catch (BufferOverflowException bufferOverflowException) {
 if (byteBuffer.capacity() >= 2097152) {
 DebugLog.General.error("the player %s cannot be saved",
 player.getUsername());
 throw bufferOverflowException;
 }

 byteBuffer = ByteBuffer.allocate(byteBuffer.capacity() + 32768);
 PlayerDB.TL_SliceBuffer.set(byteBuffer);
 }
 }

 byteBuffer.flip();
 this->setBytes(byteBuffer);
 return this;
 }

 void setBytes(ByteBuffer byteBuffer) {
 byteBuffer.rewind();
 ByteBufferOutputStream byteBufferOutputStream =
 new ByteBufferOutputStream(this->m_byteBuffer, true);
 byteBufferOutputStream.clear();
 byte[] bytes = PlayerDB.TL_Bytes.get();
 int int0 = byteBuffer.limit();

 while (int0 > 0) {
 int int1 = Math.min(bytes.length, int0);
 byteBuffer.get(bytes, 0, int1);
 byteBufferOutputStream.write(bytes, 0, int1);
 int0 -= int1;
 }

 byteBufferOutputStream.flip();
 this->m_byteBuffer = byteBufferOutputStream.getWrappedBuffer();
 }

 void setBytes(byte[] bytes) {
 ByteBufferOutputStream byteBufferOutputStream =
 new ByteBufferOutputStream(this->m_byteBuffer, true);
 byteBufferOutputStream.clear();
 byteBufferOutputStream.write(bytes);
 byteBufferOutputStream.flip();
 this->m_byteBuffer = byteBufferOutputStream.getWrappedBuffer();
 }

 void setBytes(InputStream inputStream) {
 ByteBufferOutputStream byteBufferOutputStream =
 new ByteBufferOutputStream(this->m_byteBuffer, true);
 byteBufferOutputStream.clear();
 byte[] bytes = PlayerDB.TL_Bytes.get();

 while (true) {
 int int0 = inputStream.read(bytes);
 if (int0 < 1) {
 byteBufferOutputStream.flip();
 this->m_byteBuffer = byteBufferOutputStream.getWrappedBuffer();
 return;
 }

 byteBufferOutputStream.write(bytes, 0, int0);
 }
 }
 }

 private static class SQLPlayerStore implements PlayerDB.IPlayerStore {
 Connection m_conn = nullptr;

 void init(TIntHashSet tIntHashSet) {
 tIntHashSet.clear();
 if (!Core.getInstance().isNoSave()) {
 this->m_conn = PlayerDBHelper.create();
 this->initUsedIDs(tIntHashSet);
 }
 }

 void Reset() {
 if (this->m_conn != nullptr) {
 try {
 this->m_conn.close();
 } catch (SQLException sQLException) {
 ExceptionLogger.logException(sQLException);
 }

 this->m_conn = nullptr;
 }
 }

 void save(PlayerDB.PlayerData playerData) {
 assert playerData.m_sqlID >= 1;

 if (this->m_conn != nullptr) {
 if (this->isInDB(playerData.m_sqlID) {
 this->update(playerData);
 } else {
 this->add(playerData);
 }
 }
 }

 bool load(PlayerDB.PlayerData playerData) {
 assert playerData.m_sqlID >= 1;

 if (this->m_conn.empty()) {
 return false;
 } else {
 std::string string = "SELECT data,worldversion,x,y,z,isDead,name FROM "
 "localPlayers WHERE id=?";

 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 preparedStatement.setInt(1, playerData.m_sqlID);
 ResultSet resultSet = preparedStatement.executeQuery();
 if (resultSet.next()) {
 InputStream inputStream = resultSet.getBinaryStream(1);
 playerData.setBytes(inputStream);
 playerData.m_WorldVersion = resultSet.getInt(2);
 playerData.m_x = resultSet.getInt(3);
 playerData.m_y = resultSet.getInt(4);
 playerData.m_z = resultSet.getInt(5);
 playerData.m_isDead = resultSet.getBoolean(6);
 playerData.m_name = resultSet.getString(7);
 return true;
 }
 }

 return false;
 }
 }

 bool loadEverythingExceptBytes(PlayerDB.PlayerData playerData) {
 if (this->m_conn.empty()) {
 return false;
 } else {
 std::string string = "SELECT worldversion,x,y,z,isDead,name FROM "
 "localPlayers WHERE id=?";

 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 preparedStatement.setInt(1, playerData.m_sqlID);
 ResultSet resultSet = preparedStatement.executeQuery();
 if (resultSet.next()) {
 playerData.m_WorldVersion = resultSet.getInt(1);
 playerData.m_x = resultSet.getInt(2);
 playerData.m_y = resultSet.getInt(3);
 playerData.m_z = resultSet.getInt(4);
 playerData.m_isDead = resultSet.getBoolean(5);
 playerData.m_name = resultSet.getString(6);
 return true;
 }
 }

 return false;
 }
 }

 void initUsedIDs(TIntHashSet tIntHashSet) {
 std::string string = "SELECT id FROM localPlayers";

 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 ResultSet resultSet = preparedStatement.executeQuery();

 while (resultSet.next()) {
 tIntHashSet.add(resultSet.getInt(1);
 }
 }
 }

 bool isInDB(int int0) {
 std::string string = "SELECT 1 FROM localPlayers WHERE id=?";

 bool boolean0;
 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 preparedStatement.setInt(1, int0);
 ResultSet resultSet = preparedStatement.executeQuery();
 boolean0 = resultSet.next();
 }

 return boolean0;
 }

 void add(PlayerDB.PlayerData playerData) {
 if (this->m_conn != nullptr && playerData.m_sqlID >= 1) {
 std::string string = "INSERT INTO "
 "localPlayers(wx,wy,x,y,z,worldversion,data,"
 "isDead,name,id) VALUES(?,?,?,?,?,?,?,?,?,?)";

 try {
 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 preparedStatement.setInt(1, (int)(playerData.m_x / 10.0F);
 preparedStatement.setInt(2, (int)(playerData.m_y / 10.0F);
 preparedStatement.setFloat(3, playerData.m_x);
 preparedStatement.setFloat(4, playerData.m_y);
 preparedStatement.setFloat(5, playerData.m_z);
 preparedStatement.setInt(6, playerData.m_WorldVersion);
 ByteBuffer byteBuffer = playerData.m_byteBuffer;
 byteBuffer.rewind();
 preparedStatement.setBinaryStream(
 7, new ByteBufferBackedInputStream(byteBuffer),
 byteBuffer.remaining());
 preparedStatement.setBoolean(8, playerData.m_isDead);
 preparedStatement.setString(9, playerData.m_name);
 preparedStatement.setInt(10, playerData.m_sqlID);
 int int0 = preparedStatement.executeUpdate();
 this->m_conn.commit();
 }
 } catch (Exception exception) {
 PlayerDBHelper.rollback(this->m_conn);
 throw exception;
 }
 }
 }

 void update(PlayerDB.PlayerData playerData) {
 if (this->m_conn != nullptr && playerData.m_sqlID >= 1) {
 std::string string =
 "UPDATE localPlayers SET wx = ?, wy = ?, x = ?, y = ?, z = ?, "
 "worldversion = ?, data = ?, isDead = ?, name = ? WHERE id=?";

 try {
 try(PreparedStatement preparedStatement =
 this->m_conn.prepareStatement(string) {
 preparedStatement.setInt(1, (int)(playerData.m_x / 10.0F);
 preparedStatement.setInt(2, (int)(playerData.m_y / 10.0F);
 preparedStatement.setFloat(3, playerData.m_x);
 preparedStatement.setFloat(4, playerData.m_y);
 preparedStatement.setFloat(5, playerData.m_z);
 preparedStatement.setInt(6, playerData.m_WorldVersion);
 ByteBuffer byteBuffer = playerData.m_byteBuffer;
 byteBuffer.rewind();
 preparedStatement.setBinaryStream(
 7, new ByteBufferBackedInputStream(byteBuffer),
 byteBuffer.remaining());
 preparedStatement.setBoolean(8, playerData.m_isDead);
 preparedStatement.setString(9, playerData.m_name);
 preparedStatement.setInt(10, playerData.m_sqlID);
 int int0 = preparedStatement.executeUpdate();
 this->m_conn.commit();
 }
 } catch (Exception exception) {
 PlayerDBHelper.rollback(this->m_conn);
 throw exception;
 }
 }
 }
 }
}
} // namespace savefile
} // namespace zombie
