#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets.h"
#include "fmod/fmod/FMODManager.h"
#include "java/net/InetAddress.h"
#include "java/net/UnknownHostException.h"
#include "java/text/DateFormat.h"
#include "java/text/SimpleDateFormat.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "zombie/characters/NetworkCharacter.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/RakNetPeerInterface.h"
#include "zombie/core/raknet/RakVoice.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/secure/PZcrypt.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/ZNet.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/packets/PlayerPacket.h"
#include "zombie/network/packets/SyncInjuriesPacket.h"
#include "zombie/network/packets/ZombiePacket.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FakeClientManager {
public:
 static const int SERVER_PORT = 16261;
 static const int CLIENT_PORT = 17500;
 static const std::string CLIENT_ADDRESS = "0.0.0.0";
 static const std::string versionNumber = Core.getInstance().getVersion();
 static const DateFormat logDateFormat = new SimpleDateFormat("HH:mm:ss.SSS");
 private static ThreadLocal<FakeClientManager.StringUTF> stringUTF = ThreadLocal.withInitial(FakeClientManager.StringUTF::new);
 static int logLevel = 0;
 static long startTime = System.currentTimeMillis();
 private static HashSet<FakeClientManager.Player> players = std::make_unique<HashSet<>>();

 static std::string ReadStringUTF(ByteBuffer byteBuffer) {
 return stringUTF.get().load(byteBuffer);
 }

 static void WriteStringUTF(ByteBuffer byteBuffer, const std::string& string) {
 stringUTF.get().save(byteBuffer, string);
 }

 static void sleep(long long0) {
 try {
 Thread.sleep(long0);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 private static HashMap<Integer, FakeClientManager.Movement> load(String string1) {
 std::unordered_map hashMap = new HashMap();

 try {
 std::string string0 = new String(Files.readAllBytes(Paths.get(string1);
 JSONObject jSONObject0 = new JSONObject(string0);
 FakeClientManager.Movement.version = jSONObject0.getString("version");
 JSONObject jSONObject1 = jSONObject0.getJSONObject("config");
 JSONObject jSONObject2 = jSONObject1.getJSONObject("client");
 JSONObject jSONObject3 = jSONObject2.getJSONObject("connection");
 if (jSONObject3.has("serverHost")) {
 FakeClientManager.Client.connectionServerHost = jSONObject3.getString("serverHost");
 }

 FakeClientManager.Client.connectionInterval = jSONObject3.getLong("interval");
 FakeClientManager.Client.connectionTimeout = jSONObject3.getLong("timeout");
 FakeClientManager.Client.connectionDelay = jSONObject3.getLong("delay");
 JSONObject jSONObject4 = jSONObject2.getJSONObject("statistics");
 FakeClientManager.Client.statisticsPeriod = jSONObject4.getInt("period");
 FakeClientManager.Client.statisticsClientID = Math.max(jSONObject4.getInt("id"), -1);
 if (jSONObject2.has("checksum")) {
 JSONObject jSONObject5 = jSONObject2.getJSONObject("checksum");
 FakeClientManager.Client.luaChecksum = jSONObject5.getString("lua");
 FakeClientManager.Client.scriptChecksum = jSONObject5.getString("script");
 }

 if (jSONObject1.has("zombies")) {
 jSONObject3 = jSONObject1.getJSONObject("zombies");
 FakeClientManager.ZombieSimulator.Behaviour behaviour = FakeClientManager.ZombieSimulator.Behaviour.Normal;
 if (jSONObject3.has("behaviour")) {
 behaviour = FakeClientManager.ZombieSimulator.Behaviour.valueOf(jSONObject3.getString("behaviour"));
 }

 FakeClientManager.ZombieSimulator.behaviour = behaviour;
 if (jSONObject3.has("maxZombiesPerUpdate")) {
 FakeClientManager.ZombieSimulator.maxZombiesPerUpdate = jSONObject3.getInt("maxZombiesPerUpdate");
 }

 if (jSONObject3.has("deleteZombieDistance")) {
 int int0 = jSONObject3.getInt("deleteZombieDistance");
 FakeClientManager.ZombieSimulator.deleteZombieDistanceSquared = int0 * int0;
 }

 if (jSONObject3.has("forgotZombieDistance")) {
 int int1 = jSONObject3.getInt("forgotZombieDistance");
 FakeClientManager.ZombieSimulator.forgotZombieDistanceSquared = int1 * int1;
 }

 if (jSONObject3.has("canSeeZombieDistance")) {
 int int2 = jSONObject3.getInt("canSeeZombieDistance");
 FakeClientManager.ZombieSimulator.canSeeZombieDistanceSquared = int2 * int2;
 }

 if (jSONObject3.has("seeZombieDistance")) {
 int int3 = jSONObject3.getInt("seeZombieDistance");
 FakeClientManager.ZombieSimulator.seeZombieDistanceSquared = int3 * int3;
 }

 if (jSONObject3.has("canChangeTarget")) {
 FakeClientManager.ZombieSimulator.canChangeTarget = jSONObject3.getBoolean("canChangeTarget");
 }
 }

 jSONObject3 = jSONObject1.getJSONObject("player");
 FakeClientManager.Player.fps = jSONObject3.getInt("fps");
 FakeClientManager.Player.predictInterval = jSONObject3.getInt("predict");
 if (jSONObject3.has("damage")) {
 FakeClientManager.Player.damage = (float)jSONObject3.getDouble("damage");
 }

 if (jSONObject3.has("voip")) {
 FakeClientManager.Player.isVOIPEnabled = jSONObject3.getBoolean("voip");
 }

 jSONObject4 = jSONObject1.getJSONObject("movement");
 FakeClientManager.Movement.defaultRadius = jSONObject4.getInt("radius");
 JSONObject jSONObject6 = jSONObject4.getJSONObject("motion");
 FakeClientManager.Movement.aimSpeed = jSONObject6.getInt("aim");
 FakeClientManager.Movement.sneakSpeed = jSONObject6.getInt("sneak");
 FakeClientManager.Movement.sneakRunSpeed = jSONObject6.getInt("sneakrun");
 FakeClientManager.Movement.walkSpeed = jSONObject6.getInt("walk");
 FakeClientManager.Movement.runSpeed = jSONObject6.getInt("run");
 FakeClientManager.Movement.sprintSpeed = jSONObject6.getInt("sprint");
 JSONObject jSONObject7 = jSONObject6.getJSONObject("pedestrian");
 FakeClientManager.Movement.pedestrianSpeedMin = jSONObject7.getInt("min");
 FakeClientManager.Movement.pedestrianSpeedMax = jSONObject7.getInt("max");
 JSONObject jSONObject8 = jSONObject6.getJSONObject("vehicle");
 FakeClientManager.Movement.vehicleSpeedMin = jSONObject8.getInt("min");
 FakeClientManager.Movement.vehicleSpeedMax = jSONObject8.getInt("max");
 JSONArray jSONArray = jSONObject0.getJSONArray("movements");

 for (int int4 = 0; int4 < jSONArray.length(); int4++) {
 jSONObject4 = jSONArray.getJSONObject(int4);
 int int5 = jSONObject4.getInt("id");
 std::string string2 = nullptr;
 if (jSONObject4.has("description")) {
 string2 = jSONObject4.getString("description");
 }

 int int6 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
 int int7 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
 if (jSONObject4.has("spawn")) {
 JSONObject jSONObject9 = jSONObject4.getJSONObject("spawn");
 int6 = jSONObject9.getInt("x");
 int7 = jSONObject9.getInt("y");
 }

 FakeClientManager.Movement.Motion motion = Math.random() > 0.8F
 ? FakeClientManager.Movement.Motion.Vehicle
 : FakeClientManager.Movement.Motion.Pedestrian;
 if (jSONObject4.has("motion")) {
 motion = FakeClientManager.Movement.Motion.valueOf(jSONObject4.getString("motion"));
 }

 int int8 = 0;
 if (jSONObject4.has("speed")) {
 int8 = jSONObject4.getInt("speed");
 } else {
 switch (motion) {
 case Aim:
 int8 = FakeClientManager.Movement.aimSpeed;
 break;
 case Sneak:
 int8 = FakeClientManager.Movement.sneakSpeed;
 break;
 case SneakRun:
 int8 = FakeClientManager.Movement.sneakRunSpeed;
 break;
 case Run:
 int8 = FakeClientManager.Movement.runSpeed;
 break;
 case Sprint:
 int8 = FakeClientManager.Movement.sprintSpeed;
 break;
 case Walk:
 int8 = FakeClientManager.Movement.walkSpeed;
 break;
 case Pedestrian:
 int8 = (int)Math.round(
 Math.random() * (FakeClientManager.Movement.pedestrianSpeedMax - FakeClientManager.Movement.pedestrianSpeedMin)
 + FakeClientManager.Movement.pedestrianSpeedMin
 );
 break;
 case Vehicle:
 int8 = (int)Math.round(
 Math.random() * (FakeClientManager.Movement.vehicleSpeedMax - FakeClientManager.Movement.vehicleSpeedMin)
 + FakeClientManager.Movement.vehicleSpeedMin
 );
 }
 }

 FakeClientManager.Movement.Type type = FakeClientManager.Movement.Type.Line;
 if (jSONObject4.has("type")) {
 type = FakeClientManager.Movement.Type.valueOf(jSONObject4.getString("type"));
 }

 int int9 = FakeClientManager.Movement.defaultRadius;
 if (jSONObject4.has("radius")) {
 int9 = jSONObject4.getInt("radius");
 }

 IsoDirections directions = IsoDirections.fromIndex((int)Math.round(Math.random() * 7.0);
 if (jSONObject4.has("direction")) {
 directions = IsoDirections.valueOf(jSONObject4.getString("direction"));
 }

 bool boolean0 = false;
 if (jSONObject4.has("ghost")) {
 boolean0 = jSONObject4.getBoolean("ghost");
 }

 long long0 = int5 * FakeClientManager.Client.connectionInterval;
 if (jSONObject4.has("connect")) {
 long0 = jSONObject4.getLong("connect");
 }

 long long1 = 0L;
 if (jSONObject4.has("disconnect")) {
 long1 = jSONObject4.getLong("disconnect");
 }

 long long2 = 0L;
 if (jSONObject4.has("reconnect")) {
 long2 = jSONObject4.getLong("reconnect");
 }

 long long3 = 0L;
 if (jSONObject4.has("teleport")) {
 long3 = jSONObject4.getLong("teleport");
 }

 int int10 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
 int int11 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
 if (jSONObject4.has("destination")) {
 JSONObject jSONObject10 = jSONObject4.getJSONObject("destination");
 int10 = jSONObject10.getInt("x");
 int11 = jSONObject10.getInt("y");
 }

 FakeClientManager.HordeCreator hordeCreator = nullptr;
 if (jSONObject4.has("createHorde")) {
 JSONObject jSONObject11 = jSONObject4.getJSONObject("createHorde");
 int int12 = jSONObject11.getInt("count");
 int int13 = jSONObject11.getInt("radius");
 long long4 = jSONObject11.getLong("interval");
 if (long4 != 0L) {
 hordeCreator = new FakeClientManager.HordeCreator(int13, int12, long4);
 }
 }

 FakeClientManager.SoundMaker soundMaker = nullptr;
 if (jSONObject4.has("makeSound")) {
 JSONObject jSONObject12 = jSONObject4.getJSONObject("makeSound");
 int int14 = jSONObject12.getInt("interval");
 int int15 = jSONObject12.getInt("radius");
 std::string string3 = jSONObject12.getString("message");
 if (int14 != 0) {
 soundMaker = new FakeClientManager.SoundMaker(int14, int15, string3);
 }
 }

 FakeClientManager.Movement movement = new FakeClientManager.Movement(
 int5,
 string2,
 int6,
 int7,
 motion,
 int8,
 type,
 int9,
 int10,
 int11,
 directions,
 boolean0,
 long0,
 long1,
 long2,
 long3,
 hordeCreator,
 soundMaker
 );
 if (hashMap.containsKey(int5) {
 error(int5, String.format("Client %d already exists", movement.id);
 } else {
 hashMap.put(int5, movement);
 }
 }

 return hashMap;
 } catch (Exception exception) {
 error(-1, "Scenarios file load failed");
 exception.printStackTrace();
 return hashMap;
 } finally {
 ;
 }
 }

 static void error(int int0, const std::string& string) {
 System.out.print(String.format("%5s : %s , [%2d] > %s\n", "ERROR", logDateFormat.format(Calendar.getInstance().getTime()), int0, string);
 }

 static void info(int int0, const std::string& string) {
 if (logLevel >= 0) {
 System.out.print(String.format("%5s : %s , [%2d] > %s\n", "INFO", logDateFormat.format(Calendar.getInstance().getTime()), int0, string);
 }
 }

 static void log(int int0, const std::string& string) {
 if (logLevel >= 1) {
 System.out.print(String.format("%5s : %s , [%2d] > %s\n", "LOG", logDateFormat.format(Calendar.getInstance().getTime()), int0, string);
 }
 }

 static void trace(int int0, const std::string& string) {
 if (logLevel >= 2) {
 System.out.print(String.format("%5s : %s , [%2d] > %s\n", "TRACE", logDateFormat.format(Calendar.getInstance().getTime()), int0, string);
 }
 }

 static bool isVOIPEnabled() {
 return FakeClientManager.Player.isVOIPEnabled && getOnlineID() != -1L && getConnectedGUID() != -1L;
 }

 static long getConnectedGUID() {
 return players.empty() ? -1L : players.iterator().next().client.connectionGUID;
 }

 static long getOnlineID() {
 return players.empty() ? -1L : players.iterator().next().OnlineID;
 }

 static void main(String[] strings) {
 std::string string0 = nullptr;
 int int0 = -1;

 for (int int1 = 0; int1 < strings.length; int1++) {
 if (strings[int1].startsWith("-scenarios=")) {
 string0 = strings[int1].replace("-scenarios=", "").trim();
 } else if (strings[int1].startsWith("-id=")) {
 int0 = Integer.parseInt(strings[int1].replace("-id=", "").trim());
 }
 }

 if (string0 == nullptr || string0.isBlank()) {
 error(-1, "Invalid scenarios file name");
 System.exit(0);
 }

 Rand.init();
 System.loadLibrary("RakNet64");
 System.loadLibrary("ZNetNoSteam64");

 try {
 std::string string1 = System.getProperty("zomboid.znetlog");
 if (string1 != nullptr) {
 logLevel = Integer.parseInt(string1);
 ZNet.init();
 ZNet.SetLogLevel(logLevel);
 }
 } catch (NumberFormatException numberFormatException) {
 error(-1, "Invalid log arguments");
 }

 DebugLog.setLogEnabled(DebugType.General, false);
 std::unordered_map hashMap = load(string0);
 if (FakeClientManager.Player.isVOIPEnabled) {
 FMODManager.instance.init();
 VoiceManager.instance.InitVMClient();
 VoiceManager.instance.setMode(1);
 }

 FakeClientManager.Network network;
 int int2;
 if (int0 != -1) {
 int2 = 17500 + int0;
 network = new FakeClientManager.Network(hashMap.size(), int2);
 } else {
 int2 = 17500;
 network = new FakeClientManager.Network(hashMap.size(), int2);
 }

 if (network.isStarted()) {
 int int3 = 0;
 if (int0 != -1) {
 FakeClientManager.Movement movement0 = (FakeClientManager.Movement)hashMap.get(int0);
 if (movement0 != nullptr) {
 players.add(new FakeClientManager.Player(movement0, network, int3, int2);
 } else {
 error(int0, "Client movement not found");
 }
 } else {
 for (FakeClientManager.Movement movement1 : hashMap.values()) {
 players.add(new FakeClientManager.Player(movement1, network, int3++, int2);
 }
 }

 while (!players.empty()) {
 sleep(1000L);
 }
 }
 }

 private static class Client {
 static std::string connectionServerHost = "127.0.0.1";
 static long connectionInterval = 1500L;
 static long connectionTimeout = 10000L;
 static long connectionDelay = 15000L;
 static int statisticsClientID = -1;
 static int statisticsPeriod = 1;
 static long serverTimeShift = 0L;
 static bool serverTimeShiftIsSet = false;
 private HashMap<Integer, FakeClientManager.Client.Request> requests = std::make_unique<HashMap<>>();
 private FakeClientManager.Player player;
 private FakeClientManager.Network network;
 const int connectionIndex;
 const int port;
 long connectionGUID = -1L;
 int requestId = 0;
 long stateTime;
 private FakeClientManager.Client.State state;
 std::string host;
 static std::string luaChecksum = "";
 static std::string scriptChecksum = "";

 private Client(FakeClientManager.Player playerx, FakeClientManager.Network networkx, int int0, int int1) {
 this->connectionIndex = int0;
 this->network = networkx;
 this->player = playerx;
 this->port = int1;

 try {
 this->host = InetAddress.getByName(connectionServerHost).getHostAddress();
 this->state = FakeClientManager.Client.State.CONNECT;
 Thread thread = new Thread(ThreadGroups.Workers, this::updateThread, this->player.username);
 thread.setDaemon(true);
 thread.start();
 } catch (UnknownHostException unknownHostException) {
 this->state = FakeClientManager.Client.State.QUIT;
 unknownHostException.printStackTrace();
 }
 }

 void updateThread() {
 FakeClientManager.info(
 this->player.movement.id,
 String.format(
 "Start client (%d) %s:%d => %s:%d / \"%s\"", this->connectionIndex, "0.0.0.0", this->port, this->host, 16261, this->player.movement.description
 )
 );
 FakeClientManager.sleep(this->player.movement.connectDelay);
 switch (this->player.movement.type) {
 case Circle:
 this->player.circleMovement();
 break;
 case Line:
 this->player.lineMovement();
 break;
 case AIAttackZombies:
 this->player.aiAttackZombiesMovement();
 break;
 case AIRunAwayFromZombies:
 this->player.aiRunAwayFromZombiesMovement();
 break;
 case AIRunToAnotherPlayers:
 this->player.aiRunToAnotherPlayersMovement();
 break;
 case AINormal:
 this->player.aiNormalMovement();
 }

 while (this->state != FakeClientManager.Client.State.QUIT) {
 this->update();
 FakeClientManager.sleep(1L);
 }

 FakeClientManager.info(
 this->player.movement.id,
 String.format(
 "Stop client (%d) %s:%d => %s:%d / \"%s\"", this->connectionIndex, "0.0.0.0", this->port, this->host, 16261, this->player.movement.description
 )
 );
 }

 void updateTime() {
 this->stateTime = System.currentTimeMillis();
 }

 long getServerTime() {
 return serverTimeShiftIsSet ? System.nanoTime() + serverTimeShift : 0L;
 }

 bool checkConnectionTimeout() {
 return System.currentTimeMillis() - this->stateTime > connectionTimeout;
 }

 bool checkConnectionDelay() {
 return System.currentTimeMillis() - this->stateTime > connectionDelay;
 }

 void changeState(FakeClientManager.Client.State statex) {
 this->updateTime();
 FakeClientManager.log(this->player.movement.id, String.format("%s >> %s", this->state, statex);
 if (FakeClientManager.Client.State.RUN == statex) {
 this->player.movement.connect(this->player.OnlineID);
 if (this->player.teleportLimiter == nullptr) {
 this->player.teleportLimiter = new UpdateLimit(this->player.movement.teleportDelay);
 }

 if (this->player.movement.id == statisticsClientID) {
 this->sendTimeSync();
 this->sendInjuries();
 this->sendStatisticsEnable(statisticsPeriod);
 }
 } else if (FakeClientManager.Client.State.DISCONNECT == statex) && !FakeClientManager.Client.State.DISCONNECT == this->state) {
 this->player.movement.disconnect(this->player.OnlineID);
 }

 this->state = statex;
 }

 void update() {
 switch (this->state) {
 case CONNECT:
 this->player.movement.timestamp = System.currentTimeMillis();
 this->network.connect(this->player.movement.id, this->host);
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case LOGIN:
 this->sendPlayerLogin();
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case PLAYER_CONNECT:
 this->sendPlayerConnect();
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case CHECKSUM:
 this->sendChecksum();
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case PLAYER_EXTRA_INFO:
 this->sendPlayerExtraInfo(this->player.movement.ghost, this->player.movement.hordeCreator != nullptr || FakeClientManager.Player.isVOIPEnabled);
 this->sendEquip();
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case LOAD:
 this->requestId = 0;
 this->requests.clear();
 this->requestFullUpdate();
 this->requestLargeAreaZip();
 this->changeState(FakeClientManager.Client.State.WAIT);
 break;
 case RUN:
 if (this->player.movement.doDisconnect() && this->player.movement.checkDisconnect()) {
 this->changeState(FakeClientManager.Client.State.DISCONNECT);
 } else {
 this->player.run();
 }
 break;
 case WAIT:
 if (this->checkConnectionTimeout()) {
 this->changeState(FakeClientManager.Client.State.DISCONNECT);
 }
 break;
 case DISCONNECT:
 if (this->network.isConnected()) {
 this->player.movement.timestamp = System.currentTimeMillis();
 this->network.disconnect(this->connectionGUID, this->player.movement.id, this->host);
 }

 if (this->player.movement.doReconnect() && this->player.movement.checkReconnect()
 || !this->player.movement.doReconnect() && this->checkConnectionDelay()) {
 this->changeState(FakeClientManager.Client.State.CONNECT);
 }
 case QUIT:
 }
 }

 void receive(short short0, ByteBuffer byteBuffer) {
 PacketTypes.PacketType packetType = PacketTypes.packetTypes.get(short0);
 FakeClientManager.Network.logUserPacket(this->player.movement.id, short0);
 switch (packetType) {
 case PlayerConnect:
 if (this->receivePlayerConnect(byteBuffer) {
 if (luaChecksum.empty()) {
 this->changeState(FakeClientManager.Client.State.PLAYER_EXTRA_INFO);
 } else {
 this->changeState(FakeClientManager.Client.State.CHECKSUM);
 }
 }
 break;
 case ExtraInfo:
 if (this->receivePlayerExtraInfo(byteBuffer) {
 this->changeState(FakeClientManager.Client.State.RUN);
 }
 break;
 case SentChunk:
 if (this->state == FakeClientManager.Client.State.WAIT && this->receiveChunkPart(byteBuffer) {
 this->updateTime();
 if (this->allChunkPartsReceived()) {
 this->changeState(FakeClientManager.Client.State.PLAYER_CONNECT);
 }
 }
 break;
 case NotRequiredInZip:
 if (this->state == FakeClientManager.Client.State.WAIT && this->receiveNotRequired(byteBuffer) {
 this->updateTime();
 if (this->allChunkPartsReceived()) {
 this->changeState(FakeClientManager.Client.State.PLAYER_CONNECT);
 }
 }
 case HitCharacter:
 default:
 break;
 case StatisticRequest:
 this->receiveStatistics(byteBuffer);
 break;
 case TimeSync:
 this->receiveTimeSync(byteBuffer);
 break;
 case SyncClock:
 this->receiveSyncClock(byteBuffer);
 break;
 case ZombieSimulation:
 case ZombieSimulationReliable:
 this->receiveZombieSimulation(byteBuffer);
 break;
 case PlayerUpdate:
 case PlayerUpdateReliable:
 this->player.playerManager.parsePlayer(byteBuffer);
 break;
 case PlayerTimeout:
 this->player.playerManager.parsePlayerTimeout(byteBuffer);
 break;
 case Kicked:
 this->receiveKicked(byteBuffer);
 break;
 case Checksum:
 this->receiveChecksum(byteBuffer);
 break;
 case KillZombie:
 this->receiveKillZombie(byteBuffer);
 break;
 case Teleport:
 this->receiveTeleport(byteBuffer);
 }

 byteBuffer.clear();
 }

 void doPacket(short short0, ByteBuffer byteBuffer) {
 byteBuffer.put((byte)-122);
 byteBuffer.putShort(short0);
 }

 void putUTF(ByteBuffer byteBuffer, const std::string& string) {
 if (string == nullptr) {
 byteBuffer.putShort((short)0);
 } else {
 byte[] bytes = string.getBytes();
 byteBuffer.putShort((short)bytes.length);
 byteBuffer.put(bytes);
 }
 }

 void putBoolean(ByteBuffer byteBuffer, bool boolean0) {
 byteBuffer.put((byte)(boolean0 ? 1 : 0);
 }

 void sendPlayerLogin() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.Login.getId(), byteBuffer);
 this->putUTF(byteBuffer, this->player.username);
 this->putUTF(byteBuffer, this->player.username);
 this->putUTF(byteBuffer, FakeClientManager.versionNumber);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendPlayerConnect() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.PlayerConnect.getId(), byteBuffer);
 this->writePlayerConnectData(byteBuffer);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void writePlayerConnectData(ByteBuffer byteBuffer) {
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)13);
 byteBuffer.putFloat(this->player.x);
 byteBuffer.putFloat(this->player.y);
 byteBuffer.putFloat(this->player.z);
 byteBuffer.putInt(0);
 this->putUTF(byteBuffer, this->player.username);
 this->putUTF(byteBuffer, this->player.username);
 this->putUTF(byteBuffer, this->player.isFemale == 0 ? "Kate" : "Male");
 byteBuffer.putInt(this->player.isFemale);
 this->putUTF(byteBuffer, "fireofficer");
 byteBuffer.putInt(0);
 byteBuffer.putInt(4);
 this->putUTF(byteBuffer, "Sprinting");
 byteBuffer.putInt(1);
 this->putUTF(byteBuffer, "Fitness");
 byteBuffer.putInt(6);
 this->putUTF(byteBuffer, "Strength");
 byteBuffer.putInt(6);
 this->putUTF(byteBuffer, "Axe");
 byteBuffer.putInt(1);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)Math.round(Math.random() * 5.0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 int int0 = this->player.clothes.size();
 byteBuffer.put((byte)int0);

 for (FakeClientManager.Player.Clothes clothes : this->player.clothes) {
 byteBuffer.put(clothes.flags);
 this->putUTF(byteBuffer, "Base." + clothes.name);
 this->putUTF(byteBuffer, nullptr);
 this->putUTF(byteBuffer, clothes.name);
 byteBuffer.put((byte)-1);
 byteBuffer.put((byte)-1);
 byteBuffer.put((byte)-1);
 byteBuffer.put(clothes.text);
 byteBuffer.putFloat(0.0F);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 }

 this->putUTF(byteBuffer, "fake_str");
 byteBuffer.putShort((short)0);
 byteBuffer.putInt(2);
 this->putUTF(byteBuffer, "Fit");
 this->putUTF(byteBuffer, "Stout");
 byteBuffer.putFloat(0.0F);
 byteBuffer.putInt(0);
 byteBuffer.putInt(0);
 byteBuffer.putInt(4);
 this->putUTF(byteBuffer, "Sprinting");
 byteBuffer.putFloat(75.0F);
 this->putUTF(byteBuffer, "Fitness");
 byteBuffer.putFloat(67500.0F);
 this->putUTF(byteBuffer, "Strength");
 byteBuffer.putFloat(67500.0F);
 this->putUTF(byteBuffer, "Axe");
 byteBuffer.putFloat(75.0F);
 byteBuffer.putInt(4);
 this->putUTF(byteBuffer, "Sprinting");
 byteBuffer.putInt(1);
 this->putUTF(byteBuffer, "Fitness");
 byteBuffer.putInt(6);
 this->putUTF(byteBuffer, "Strength");
 byteBuffer.putInt(6);
 this->putUTF(byteBuffer, "Axe");
 byteBuffer.putInt(1);
 byteBuffer.putInt(0);
 this->putBoolean(byteBuffer, true);
 this->putUTF(byteBuffer, "fake");
 byteBuffer.putFloat(this->player.tagColor.r);
 byteBuffer.putFloat(this->player.tagColor.g);
 byteBuffer.putFloat(this->player.tagColor.b);
 byteBuffer.putInt(0);
 byteBuffer.putDouble(0.0);
 byteBuffer.putInt(0);
 this->putUTF(byteBuffer, this->player.username);
 byteBuffer.putFloat(this->player.speakColor.r);
 byteBuffer.putFloat(this->player.speakColor.g);
 byteBuffer.putFloat(this->player.speakColor.b);
 this->putBoolean(byteBuffer, true);
 this->putBoolean(byteBuffer, false);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.putInt(0);
 byteBuffer.putInt(0);
 }

 void sendPlayerExtraInfo(bool boolean0, bool var2) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.ExtraInfo.getId(), byteBuffer);
 byteBuffer.putShort(this->player.OnlineID);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)(boolean0 ? 1 : 0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)(FakeClientManager.Player.isVOIPEnabled ? 1 : 0);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendSyncRadioData() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.SyncRadioData.getId(), byteBuffer);
 byteBuffer.put((byte)(FakeClientManager.Player.isVOIPEnabled ? 1 : 0);
 byteBuffer.putInt(4);
 byteBuffer.putInt(0);
 byteBuffer.putInt((int)RakVoice.GetMaxDistance());
 byteBuffer.putInt((int)this->player.x);
 byteBuffer.putInt((int)this->player.y);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendEquip() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.Equip.getId(), byteBuffer);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)1);
 byteBuffer.putInt(16);
 byteBuffer.putShort(this->player.registry_id);
 byteBuffer.put((byte)1);
 byteBuffer.putInt(this->player.weapon_id);
 byteBuffer.put((byte)0);
 byteBuffer.putInt(0);
 byteBuffer.putInt(0);
 byteBuffer.put((byte)0);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendChatMessage(const std::string& string) {
 ByteBuffer byteBuffer = this->network.startPacket();
 byteBuffer.putShort(this->player.OnlineID);
 byteBuffer.putInt(2);
 this->putUTF(byteBuffer, this->player.username);
 this->putUTF(byteBuffer, string);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 int getBooleanVariables() {
 short short0 = 0;
 if (this->player.movement.speed > 0.0F) {
 switch (this->player.movement.motion) {
 case Aim:
 short0 |= 64;
 break;
 case Sneak:
 short0 |= 1;
 break;
 case SneakRun:
 short0 |= 17;
 break;
 case Run:
 short0 |= 16;
 break;
 case Sprint:
 short0 |= 32;
 }

 short0 |= 17408;
 }

 return short0;
 }

 void sendPlayer(NetworkCharacter.Transform transform, int int0, Vector2 vector) {
 PlayerPacket playerPacket = new PlayerPacket();
 playerPacket.id = this->player.OnlineID;
 playerPacket.x = transform.position.x;
 playerPacket.y = transform.position.y;
 playerPacket.z = (byte)this->player.z;
 playerPacket.direction = vector.getDirection();
 playerPacket.usePathFinder = false;
 playerPacket.moveType = NetworkVariables.PredictionTypes.None;
 playerPacket.VehicleID = -1;
 playerPacket.VehicleSeat = -1;
 playerPacket.booleanVariables = this->getBooleanVariables();
 playerPacket.footstepSoundRadius = 0;
 playerPacket.bleedingLevel = 0;
 playerPacket.realx = this->player.x;
 playerPacket.realy = this->player.y;
 playerPacket.realz = (byte)this->player.z;
 playerPacket.realdir = (byte)IsoDirections.fromAngleActual(this->player.direction).index();
 playerPacket.realt = int0;
 playerPacket.collidePointX = -1.0F;
 playerPacket.collidePointY = -1.0F;
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.PlayerUpdateReliable.getId(), byteBuffer);
 ByteBufferWriter byteBufferWriter = new ByteBufferWriter(byteBuffer);
 playerPacket.write(byteBufferWriter);
 this->network.endPacket(this->connectionGUID);
 }

 bool receivePlayerConnect(ByteBuffer byteBuffer) {
 short short0 = byteBuffer.getShort();
 if (short0 == -1) {
 uint8_t byte0 = byteBuffer.get();
 short0 = byteBuffer.getShort();
 this->player.OnlineID = short0;
 return true;
 } else {
 return false;
 }
 }

 bool receivePlayerExtraInfo(ByteBuffer byteBuffer) {
 short short0 = byteBuffer.getShort();
 return short0 = = this->player.OnlineID;
 }

 bool receiveChunkPart(ByteBuffer byteBuffer) {
 bool boolean0 = false;
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 int int5 = byteBuffer.getInt();
 if (this->requests.remove(int0) != nullptr) {
 boolean0 = true;
 }

 return boolean0;
 }

 bool receiveNotRequired(ByteBuffer byteBuffer) {
 bool boolean0 = false;
 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = byteBuffer.getInt();
 bool boolean1 = byteBuffer.get() == 1;
 if (this->requests.remove(int2) != nullptr) {
 boolean0 = true;
 }
 }

 return boolean0;
 }

 bool allChunkPartsReceived() {
 return this->requests.size() == 0;
 }

 void addChunkRequest(int int0, int int1, int var3, int var4) {
 FakeClientManager.Client.Request request = new FakeClientManager.Client.Request(int0, int1, this->requestId);
 this->requestId++;
 this->requests.put(request.id, request);
 }

 void requestZipList() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.RequestZipList.getId(), byteBuffer);
 byteBuffer.putInt(this->requests.size());

 for (FakeClientManager.Client.Request request : this->requests.values()) {
 byteBuffer.putInt(request.id);
 byteBuffer.putInt(request.wx);
 byteBuffer.putInt(request.wy);
 byteBuffer.putLong(request.crc);
 }

 this->network.endPacket(this->connectionGUID);
 }

 void requestLargeAreaZip() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.RequestLargeAreaZip.getId(), byteBuffer);
 byteBuffer.putInt(this->player.WorldX);
 byteBuffer.putInt(this->player.WorldY);
 byteBuffer.putInt(13);
 this->network.endPacketImmediate(this->connectionGUID);
 int int0 = this->player.WorldX - 6 + 2;
 int int1 = this->player.WorldY - 6 + 2;
 int int2 = this->player.WorldX + 6 + 2;
 int int3 = this->player.WorldY + 6 + 2;

 for (int int4 = int1; int4 <= int3; int4++) {
 for (int int5 = int0; int5 <= int2; int5++) {
 FakeClientManager.Client.Request request = new FakeClientManager.Client.Request(int5, int4, this->requestId);
 this->requestId++;
 this->requests.put(request.id, request);
 }
 }

 this->requestZipList();
 }

 void requestFullUpdate() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.IsoRegionClientRequestFullUpdate.getId(), byteBuffer);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void requestChunkObjectState() {
 for (FakeClientManager.Client.Request request : this->requests.values()) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.ChunkObjectState.getId(), byteBuffer);
 byteBuffer.putShort((short)request.wx);
 byteBuffer.putShort((short)request.wy);
 this->network.endPacket(this->connectionGUID);
 }
 }

 void requestChunks() {
 if (!this->requests.empty()) {
 this->requestZipList();
 this->requestChunkObjectState();
 this->requests.clear();
 }
 }

 void sendStatisticsEnable(int int0) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.StatisticRequest.getId(), byteBuffer);
 byteBuffer.put((byte)3);
 byteBuffer.putInt(int0);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void receiveStatistics(ByteBuffer byteBuffer) {
 long long0 = byteBuffer.getLong();
 long long1 = byteBuffer.getLong();
 long long2 = byteBuffer.getLong();
 long long3 = byteBuffer.getLong();
 long long4 = byteBuffer.getLong();
 long long5 = byteBuffer.getLong();
 long long6 = byteBuffer.getLong();
 long long7 = byteBuffer.getLong();
 long long8 = byteBuffer.getLong();
 FakeClientManager.info(
 this->player.movement.id,
 String.format(
 "ServerStats: con=[%2d] fps=[%2d] tps=[%2d] upt=[%4d-%4d/%4d], c1=[%d] c2=[%d] c3=[%d]",
 long5,
 long3,
 long4,
 long0,
 long1,
 long2,
 long6,
 long7,
 long8
 )
 );
 }

 void sendTimeSync() {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.TimeSync.getId(), byteBuffer);
 long long0 = System.nanoTime();
 byteBuffer.putLong(long0);
 byteBuffer.putLong(0L);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void receiveTimeSync(ByteBuffer byteBuffer) {
 long long0 = byteBuffer.getLong();
 long long1 = byteBuffer.getLong();
 long long2 = System.nanoTime();
 long long3 = long2 - long0;
 long long4 = long1 - long2 + long3 / 2L;
 long long5 = serverTimeShift;
 if (!serverTimeShiftIsSet) {
 serverTimeShift = long4;
 } else {
 serverTimeShift = (long)((float)serverTimeShift + (float)(long4 - serverTimeShift) * 0.05F);
 }

 long long6 = 10000000L;
 if (Math.abs(serverTimeShift - long5) > long6) {
 this->sendTimeSync();
 } else {
 serverTimeShiftIsSet = true;
 }
 }

 void receiveSyncClock(ByteBuffer var1) {
 FakeClientManager.trace(this->player.movement.id, String.format("Player %3d sync clock", this->player.OnlineID);
 }

 void receiveKicked(ByteBuffer byteBuffer) {
 std::string string = FakeClientManager.ReadStringUTF(byteBuffer);
 FakeClientManager.info(this->player.movement.id, String.format("Client kicked. Reason: %s", string);
 }

 void receiveChecksum(ByteBuffer byteBuffer) {
 FakeClientManager.trace(this->player.movement.id, String.format("Player %3d receive Checksum", this->player.OnlineID);
 short short0 = byteBuffer.getShort();
 bool boolean0 = byteBuffer.get() == 1;
 bool boolean1 = byteBuffer.get() == 1;
 if (short0 != 1 || !boolean0 || !boolean1) {
 FakeClientManager.info(this->player.movement.id, String.format("checksum lua: %b, script: %b", boolean0, boolean1);
 }

 this->changeState(FakeClientManager.Client.State.PLAYER_EXTRA_INFO);
 }

 void receiveKillZombie(ByteBuffer byteBuffer) {
 FakeClientManager.trace(this->player.movement.id, String.format("Player %3d receive KillZombie", this->player.OnlineID);
 short short0 = byteBuffer.getShort();
 FakeClientManager.Zombie zombie0 = this->player.simulator.zombies.get(Integer.valueOf(short0);
 if (zombie0 != nullptr) {
 this->player.simulator.zombies4Delete.add(zombie0);
 }
 }

 void receiveTeleport(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 FakeClientManager.info(this->player.movement.id, String.format("Player %3d teleport to (%d, %d)", this->player.OnlineID, (int)float0, (int)float1);
 this->player.x = float0;
 this->player.y = float1;
 }

 void receiveZombieSimulation(ByteBuffer byteBuffer) {
 this->player.simulator.clear();
 bool boolean0 = byteBuffer.get() == 1;
 short short0 = byteBuffer.getShort();

 for (short short1 = 0; short1 < short0; short1++) {
 short short2 = byteBuffer.getShort();
 FakeClientManager.Zombie zombie0 = this->player.simulator.zombies.get(Integer.valueOf(short2);
 this->player.simulator.zombies4Delete.add(zombie0);
 }

 short short3 = byteBuffer.getShort();

 for (short short4 = 0; short4 < short3; short4++) {
 short short5 = byteBuffer.getShort();
 this->player.simulator.add(short5);
 }

 this->player.simulator.receivePacket(byteBuffer);
 this->player.simulator.process();
 }

 void sendInjuries() {
 SyncInjuriesPacket syncInjuriesPacket = new SyncInjuriesPacket();
 syncInjuriesPacket.id = this->player.OnlineID;
 syncInjuriesPacket.strafeSpeed = 1.0F;
 syncInjuriesPacket.walkSpeed = 1.0F;
 syncInjuriesPacket.walkInjury = 0.0F;
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.SyncInjuries.getId(), byteBuffer);
 ByteBufferWriter byteBufferWriter = new ByteBufferWriter(byteBuffer);
 syncInjuriesPacket.write(byteBufferWriter);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendChecksum() {
 if (!luaChecksum.empty()) {
 FakeClientManager.trace(this->player.movement.id, String.format("Player %3d sendChecksum", this->player.OnlineID);
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.Checksum.getId(), byteBuffer);
 byteBuffer.putShort((short)1);
 this->putUTF(byteBuffer, luaChecksum);
 this->putUTF(byteBuffer, scriptChecksum);
 this->network.endPacketImmediate(this->connectionGUID);
 }
 }

 void sendCommand(const std::string& string) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.ReceiveCommand.getId(), byteBuffer);
 FakeClientManager.WriteStringUTF(byteBuffer, string);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendEventPacket(short short0, int int0, int int1, int int2, uint8_t byte0, const std::string& string) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.EventPacket.getId(), byteBuffer);
 byteBuffer.putShort(short0);
 byteBuffer.putFloat(int0);
 byteBuffer.putFloat(int1);
 byteBuffer.putFloat(int2);
 byteBuffer.put(byte0);
 FakeClientManager.WriteStringUTF(byteBuffer, string);
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putInt(0);
 byteBuffer.putShort((short)0);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 void sendWorldSound4Player(int int0, int int1, int int2, int int3, int int4) {
 ByteBuffer byteBuffer = this->network.startPacket();
 this->doPacket(PacketTypes.PacketType.WorldSound.getId(), byteBuffer);
 byteBuffer.putInt(int0);
 byteBuffer.putInt(int1);
 byteBuffer.putInt(int2);
 byteBuffer.putInt(int3);
 byteBuffer.putInt(int4);
 byteBuffer.put((byte)0);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.put((byte)0);
 this->network.endPacketImmediate(this->connectionGUID);
 }

 private static class Request {
 const int id;
 const int wx;
 const int wy;
 const long crc;

 private Request(int int1, int int2, int int0) {
 this->id = int0;
 this->wx = int1;
 this->wy = int2;
 CRC32 crc32 = new CRC32();
 crc32.reset();
 crc32.update(String.format("map_%d_%d.bin", int1, int2).getBytes());
 this->crc = crc32.getValue();
 }
 }

 private static enum State {
 CONNECT,
 LOGIN,
 CHECKSUM,
 PLAYER_CONNECT,
 PLAYER_EXTRA_INFO,
 LOAD,
 RUN,
 WAIT,
 DISCONNECT,
 QUIT;
 }
 }

 private static class HordeCreator {
 const int radius;
 const int count;
 const long interval;
 const UpdateLimit hordeCreatorLimiter;

 public HordeCreator(int int0, int int1, long long0) {
 this->radius = int0;
 this->count = int1;
 this->interval = long0;
 this->hordeCreatorLimiter = new UpdateLimit(long0);
 }

 std::string getCommand(int int2, int int1, int int0) {
 return String.format(
 "/createhorde2 -x %d -y %d -z %d -count %d -radius %d -crawler false -isFallOnFront false -isFakeDead false -knockedDown false -health 1 -outfit",
 int2,
 int1,
 int0,
 this->count,
 this->radius
 );
 }
 }

 private static class Movement {
 static std::string version;
 static int defaultRadius = 150;
 static int aimSpeed = 4;
 static int sneakSpeed = 6;
 static int walkSpeed = 7;
 static int sneakRunSpeed = 10;
 static int runSpeed = 13;
 static int sprintSpeed = 19;
 static int pedestrianSpeedMin = 5;
 static int pedestrianSpeedMax = 20;
 static int vehicleSpeedMin = 40;
 static int vehicleSpeedMax = 80;
 static const float zombieLungeDistanceSquared = 100.0F;
 static const float zombieWalkSpeed = 3.0F;
 static const float zombieLungeSpeed = 6.0F;
 const int id;
 const std::string description;
 const Vector2 spawn;
 FakeClientManager.Movement.Motion motion;
 float speed;
 FakeClientManager.Movement.Type type;
 const int radius;
 const IsoDirections direction;
 const Vector2 destination;
 const bool ghost;
 const long connectDelay;
 const long disconnectDelay;
 const long reconnectDelay;
 const long teleportDelay;
 FakeClientManager.HordeCreator hordeCreator;
 FakeClientManager.SoundMaker soundMaker;
 long timestamp;

 public Movement(
 int int0,
 String string,
 int int2,
 int int1,
 FakeClientManager.Movement.Motion motionx,
 int int3,
 FakeClientManager.Movement.Type typex,
 int int4,
 int int6,
 int int5,
 IsoDirections directions,
 boolean boolean0,
 long long0,
 long long1,
 long long2,
 long long3,
 FakeClientManager.HordeCreator hordeCreatorx,
 FakeClientManager.SoundMaker soundMakerx
 ) {
 this->id = int0;
 this->description = string;
 this->spawn = new Vector2(int2, int1);
 this->motion = motionx;
 this->speed = int3;
 this->type = typex;
 this->radius = int4;
 this->direction = directions;
 this->destination = new Vector2(int6, int5);
 this->ghost = boolean0;
 this->connectDelay = long0;
 this->disconnectDelay = long1;
 this->reconnectDelay = long2;
 this->teleportDelay = long3;
 this->hordeCreator = hordeCreatorx;
 this->soundMaker = soundMakerx;
 }

 void connect(int int0) {
 long long0 = System.currentTimeMillis();
 if (this->disconnectDelay != 0L) {
 FakeClientManager.info(
 this->id,
 String.format(
 "Player %3d connect in %.3fs, disconnect in %.3fs",
 int0,
 (float)(long0 - this->timestamp) / 1000.0F,
 (float)this->disconnectDelay / 1000.0F
 )
 );
 } else {
 FakeClientManager.info(this->id, String.format("Player %3d connect in %.3fs", int0, (float)(long0 - this->timestamp) / 1000.0F);
 }

 this->timestamp = long0;
 }

 void disconnect(int int0) {
 long long0 = System.currentTimeMillis();
 if (this->reconnectDelay != 0L) {
 FakeClientManager.info(
 this->id,
 String.format(
 "Player %3d disconnect in %.3fs, reconnect in %.3fs",
 int0,
 (float)(long0 - this->timestamp) / 1000.0F,
 (float)this->reconnectDelay / 1000.0F
 )
 );
 } else {
 FakeClientManager.info(this->id, String.format("Player %3d disconnect in %.3fs", int0, (float)(long0 - this->timestamp) / 1000.0F);
 }

 this->timestamp = long0;
 }

 bool doTeleport() {
 return this->teleportDelay != 0L;
 }

 bool doDisconnect() {
 return this->disconnectDelay != 0L;
 }

 bool checkDisconnect() {
 return System.currentTimeMillis() - this->timestamp > this->disconnectDelay;
 }

 bool doReconnect() {
 return this->reconnectDelay != 0L;
 }

 bool checkReconnect() {
 return System.currentTimeMillis() - this->timestamp > this->reconnectDelay;
 }

 private static enum Motion {
 Aim,
 Sneak,
 Walk,
 SneakRun,
 Run,
 Sprint,
 Pedestrian,
 Vehicle;
 }

 private static enum Type {
 Stay,
 Line,
 Circle,
 AIAttackZombies,
 AIRunAwayFromZombies,
 AIRunToAnotherPlayers,
 AINormal;
 }
 }

 private static class Network {
 private HashMap<Integer, FakeClientManager.Client> createdClients = std::make_unique<HashMap<>>();
 private HashMap<Long, FakeClientManager.Client> connectedClients = std::make_unique<HashMap<>>();
 const ByteBuffer rb = ByteBuffer.allocate(1000000);
 const ByteBuffer wb = ByteBuffer.allocate(1000000);
 const RakNetPeerInterface peer;
 const int started;
 int connected = -1;
 private static HashMap<Integer, String> systemPacketTypeNames = std::make_unique<HashMap<>>();

 bool isConnected() {
 return this->connected == 0;
 }

 bool isStarted() {
 return this->started == 0;
 }

 private Network(int int1, int int0) {
 this->peer = std::make_unique<RakNetPeerInterface>();
 this->peer.Init(false);
 this->peer.SetMaximumIncomingConnections(0);
 this->peer.SetClientPort(int0);
 this->peer.SetOccasionalPing(true);
 this->started = this->peer.Startup(int1);
 if (this->started == 0) {
 Thread thread = new Thread(ThreadGroups.Network, this::receiveThread, "PeerInterfaceReceive");
 thread.setDaemon(true);
 thread.start();
 FakeClientManager.log(-1, "Network start ok");
 } else {
 FakeClientManager.error(-1, String.format("Network start failed: %d", this->started);
 }
 }

 void connect(int int0, const std::string& string) {
 this->connected = this->peer.Connect(string, 16261, PZcrypt.hash("", true), false);
 if (this->connected == 0) {
 FakeClientManager.log(int0, String.format("Client connected to %s:%d", string, 16261);
 } else {
 FakeClientManager.error(int0, String.format("Client connection to %s:%d failed: %d", string, 16261, this->connected);
 }
 }

 void disconnect(long long0, int int0, const std::string& string) {
 if (long0 != 0L) {
 this->peer.disconnect(long0, "");
 this->connected = -1;
 }

 if (this->connected == -1) {
 FakeClientManager.log(int0, String.format("Client disconnected from %s:%d", string, 16261);
 } else {
 FakeClientManager.log(int0, String.format("Client disconnection from %s:%d failed: %d", string, 16261, long0);
 }
 }

 ByteBuffer startPacket() {
 this->wb.clear();
 return this->wb;
 }

 void cancelPacket() {
 this->wb.clear();
 }

 void endPacket(long long0) {
 this->wb.flip();
 this->peer.Send(this->wb, 1, 3, (byte)0, long0, false);
 }

 void endPacketImmediate(long long0) {
 this->wb.flip();
 this->peer.Send(this->wb, 0, 3, (byte)0, long0, false);
 }

 void endPacketSuperHighUnreliable(long long0) {
 this->wb.flip();
 this->peer.Send(this->wb, 0, 1, (byte)0, long0, false);
 }

 void receiveThread() {
 while (true) {
 if (this->peer.Receive(this->rb) {
 this->decode(this->rb);
 } else {
 FakeClientManager.sleep(1L);
 }
 }
 }

 static void logUserPacket(int int0, short short0) {
 PacketTypes.PacketType packetType = PacketTypes.packetTypes.get(short0);
 std::string string = packetType == nullptr ? "unknown user packet" : packetType.name();
 FakeClientManager.trace(int0, String.format("## %s (%d)", string, short0);
 }

 static void logSystemPacket(int int1, int int0) {
 std::string string = systemPacketTypeNames.getOrDefault(int0, "unknown system packet");
 FakeClientManager.trace(int1, String.format("## %s (%d)", string, int0);
 }

 void decode(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 int int1 = -1;
 long long0 = -1L;
 logSystemPacket(int1, int0);
 switch (int0) {
 case 0:
 case 1:
 case 20:
 case 25:
 case 31:
 case 33:
 default:
 break;
 case 16:
 int1 = byteBuffer.get() & 255;
 long0 = this->peer.getGuidOfPacket();
 FakeClientManager.Client client1 = this->createdClients.get(int1);
 if (client1 != nullptr) {
 client1.connectionGUID = long0;
 this->connectedClients.put(long0, client1);
 VoiceManager.instance.VoiceConnectReq(long0);
 client1.changeState(FakeClientManager.Client.State.LOGIN);
 }

 FakeClientManager.log(-1, String.format("Connected clients: %d (connection index %d)", this->connectedClients.size(), int1);
 break;
 case 17:
 case 18:
 case 23:
 case 24:
 case 32:
 FakeClientManager.error(-1, "Connection failed: " + int0);
 break;
 case 19:
 int1 = byteBuffer.get() & 255;
 case 44:
 case 45:
 long0 = this->peer.getGuidOfPacket();
 break;
 case 21:
 int1 = byteBuffer.get() & 255;
 long0 = this->peer.getGuidOfPacket();
 FakeClientManager.Client client2 = this->connectedClients.get(long0);
 if (client2 != nullptr) {
 this->connectedClients.remove(long0);
 client2.changeState(FakeClientManager.Client.State.DISCONNECT);
 }

 FakeClientManager.log(-1, String.format("Connected clients: %d (connection index %d)", this->connectedClients.size(), int1);
 break;
 case 22:
 int1 = byteBuffer.get() & 255;
 FakeClientManager.Client client3 = this->createdClients.get(int1);
 if (client3 != nullptr) {
 client3.changeState(FakeClientManager.Client.State.DISCONNECT);
 }
 break;
 case 134:
 short short0 = byteBuffer.getShort();
 long0 = this->peer.getGuidOfPacket();
 FakeClientManager.Client client0 = this->connectedClients.get(long0);
 if (client0 != nullptr) {
 client0.receive((short)short0, byteBuffer);
 int1 = client0.connectionIndex;
 }
 }
 }

 static {
 systemPacketTypeNames.put(22, "connection lost");
 systemPacketTypeNames.put(21, "disconnected");
 systemPacketTypeNames.put(23, "connection banned");
 systemPacketTypeNames.put(17, "connection failed");
 systemPacketTypeNames.put(20, "no free connections");
 systemPacketTypeNames.put(16, "connection accepted");
 systemPacketTypeNames.put(18, "already connected");
 systemPacketTypeNames.put(44, "voice request");
 systemPacketTypeNames.put(45, "voice reply");
 systemPacketTypeNames.put(25, "wrong protocol version");
 systemPacketTypeNames.put(0, "connected ping");
 systemPacketTypeNames.put(1, "unconnected ping");
 systemPacketTypeNames.put(33, "new remote connection");
 systemPacketTypeNames.put(31, "remote disconnection");
 systemPacketTypeNames.put(32, "remote connection lost");
 systemPacketTypeNames.put(24, "invalid password");
 systemPacketTypeNames.put(19, "new connection");
 systemPacketTypeNames.put(134, "user packet");
 }
 }

 private static class Player {
 static const int cellSize = 50;
 static const int spawnMinX = 3550;
 static const int spawnMaxX = 14450;
 static const int spawnMinY = 5050;
 static const int spawnMaxY = 12950;
 static const int ChunkGridWidth = 13;
 static const int ChunksPerWidth = 10;
 static int fps = 60;
 static int predictInterval = 1000;
 static float damage = 1.0F;
 static bool isVOIPEnabled = false;
 const NetworkCharacter networkCharacter;
 const UpdateLimit updateLimiter;
 const UpdateLimit predictLimiter;
 const UpdateLimit timeSyncLimiter;
 private FakeClientManager.Client client;
 private FakeClientManager.Movement movement;
 private ArrayList<FakeClientManager.Player.Clothes> clothes;
 const std::string username;
 const int isFemale;
 const Color tagColor;
 const Color speakColor;
 UpdateLimit teleportLimiter;
 short OnlineID;
 float x;
 float y;
 const float z;
 Vector2 direction;
 int WorldX;
 int WorldY;
 float angle;
 private FakeClientManager.ZombieSimulator simulator;
 private FakeClientManager.PlayerManager playerManager;
 bool weapon_isBareHeads = false;
 int weapon_id = 837602032;
 short registry_id = 1202;
 static float distance = 0.0F;
 int lastPlayerForHello = -1;

 private Player(FakeClientManager.Movement movementx, FakeClientManager.Network network, int int0, int int1) {
 this->username = String.format("Client%d", movementx.id);
 this->tagColor = Colors.SkyBlue;
 this->speakColor = Colors.GetRandomColor();
 this->isFemale = (int)Math.round(Math.random());
 this->OnlineID = -1;
 this->clothes = std::make_unique<ArrayList<>>();
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)11, (byte)0, "Shirt_FormalWhite"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)13, (byte)3, "Tie_Full"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)11, (byte)0, "Socks_Ankle"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)13, (byte)0, "Trousers_Suit"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)13, (byte)0, "Suit_Jacket"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)11, (byte)0, "Shoes_Black"));
 this->clothes.add(new FakeClientManager.Player.Clothes((byte)11, (byte)0, "Glasses_Sun"));
 this->WorldX = (int)this->x / 10;
 this->WorldY = (int)this->y / 10;
 this->movement = movementx;
 this->z = 0.0F;
 this->angle = 0.0F;
 this->x = movementx.spawn.x;
 this->y = movementx.spawn.y;
 this->direction = movementx.direction.ToVector();
 this->networkCharacter = std::make_unique<NetworkCharacter>();
 this->simulator = new FakeClientManager.ZombieSimulator(this);
 this->playerManager = new FakeClientManager.PlayerManager(this);
 this->client = new FakeClientManager.Client(this, network, int0, int1);
 network.createdClients.put(int0, this->client);
 this->updateLimiter = new UpdateLimit(1000 / fps);
 this->predictLimiter = new UpdateLimit((long)(predictInterval * 0.6F);
 this->timeSyncLimiter = new UpdateLimit(10000L);
 }

 float getDistance(float float0) {
 return float0 / 3.6F / fps;
 }

 void teleportMovement() {
 float float0 = this->movement.destination.x;
 float float1 = this->movement.destination.y;
 FakeClientManager.info(
 this->movement.id,
 String.format(
 "Player %3d teleport (%9.3f,%9.3f) => (%9.3f,%9.3f) / %9.3f, next in %.3fs",
 this->OnlineID,
 this->x,
 this->y,
 float0,
 float1,
 Math.sqrt(Math.pow(float0 - this->x, 2.0) + Math.pow(float1 - this->y, 2.0),
 (float)this->movement.teleportDelay / 1000.0F
 )
 );
 this->x = float0;
 this->y = float1;
 this->angle = 0.0F;
 this->teleportLimiter.Reset(this->movement.teleportDelay);
 }

 void lineMovement() {
 distance = this->getDistance(this->movement.speed);
 this->direction.set(this->movement.destination.x - this->x, this->movement.destination.y - this->y);
 this->direction.normalize();
 float float0 = this->x + distance * this->direction.x;
 float float1 = this->y + distance * this->direction.y;
 if (this->x < this->movement.destination.x && float0 > this->movement.destination.x
 || this->x > this->movement.destination.x && float0 < this->movement.destination.x
 || this->y < this->movement.destination.y && float1 > this->movement.destination.y
 || this->y > this->movement.destination.y && float1 < this->movement.destination.y) {
 float0 = this->movement.destination.x;
 float1 = this->movement.destination.y;
 }

 this->x = float0;
 this->y = float1;
 }

 void circleMovement() {
 this->angle = (this->angle + (float)(2.0 * Math.asin(this->getDistance(this->movement.speed) / 2.0F / this->movement.radius) % 360.0F;
 float float0 = this->movement.spawn.x + (float)(this->movement.radius * Math.sin(this->angle);
 float float1 = this->movement.spawn.y + (float)(this->movement.radius * Math.cos(this->angle);
 this->x = float0;
 this->y = float1;
 }

 private FakeClientManager.Zombie getNearestZombie() {
 FakeClientManager.Zombie zombie0 = nullptr;
 float float0 = Float.POSITIVE_INFINITY;

 for (FakeClientManager.Zombie zombie1 : this->simulator.zombies.values()) {
 float float1 = IsoUtils.DistanceToSquared(this->x, this->y, zombie1.x, zombie1.y);
 if (float1 < float0) {
 zombie0 = zombie1;
 float0 = float1;
 }
 }

 return zombie0;
 }

 private FakeClientManager.Zombie getNearestZombie(FakeClientManager.PlayerManager.RemotePlayer remotePlayer) {
 FakeClientManager.Zombie zombie0 = nullptr;
 float float0 = Float.POSITIVE_INFINITY;

 for (FakeClientManager.Zombie zombie1 : this->simulator.zombies.values()) {
 float float1 = IsoUtils.DistanceToSquared(remotePlayer.x, remotePlayer.y, zombie1.x, zombie1.y);
 if (float1 < float0) {
 zombie0 = zombie1;
 float0 = float1;
 }
 }

 return zombie0;
 }

 private FakeClientManager.PlayerManager.RemotePlayer getNearestPlayer() {
 FakeClientManager.PlayerManager.RemotePlayer remotePlayer0 = nullptr;
 float float0 = Float.POSITIVE_INFINITY;
 synchronized (this->playerManager.players) {
 for (FakeClientManager.PlayerManager.RemotePlayer remotePlayer1 : this->playerManager.players.values()) {
 float float1 = IsoUtils.DistanceToSquared(this->x, this->y, remotePlayer1.x, remotePlayer1.y);
 if (float1 < float0) {
 remotePlayer0 = remotePlayer1;
 float0 = float1;
 }
 }

 return remotePlayer0;
 }
 }

 void aiAttackZombiesMovement() {
 FakeClientManager.Zombie zombie0 = this->getNearestZombie();
 float float0 = this->getDistance(this->movement.speed);
 if (zombie0 != nullptr) {
 this->direction.set(zombie0.x - this->x, zombie0.y - this->y);
 this->direction.normalize();
 }

 float float1 = this->x + float0 * this->direction.x;
 float float2 = this->y + float0 * this->direction.y;
 this->x = float1;
 this->y = float2;
 }

 void aiRunAwayFromZombiesMovement() {
 FakeClientManager.Zombie zombie0 = this->getNearestZombie();
 float float0 = this->getDistance(this->movement.speed);
 if (zombie0 != nullptr) {
 this->direction.set(this->x - zombie0.x, this->y - zombie0.y);
 this->direction.normalize();
 }

 float float1 = this->x + float0 * this->direction.x;
 float float2 = this->y + float0 * this->direction.y;
 this->x = float1;
 this->y = float2;
 }

 void aiRunToAnotherPlayersMovement() {
 FakeClientManager.PlayerManager.RemotePlayer remotePlayer = this->getNearestPlayer();
 float float0 = this->getDistance(this->movement.speed);
 float float1 = this->x + float0 * this->direction.x;
 float float2 = this->y + float0 * this->direction.y;
 if (remotePlayer != nullptr) {
 this->direction.set(remotePlayer.x - this->x, remotePlayer.y - this->y);
 float float3 = this->direction.normalize();
 if (float3 > 2.0F) {
 this->x = float1;
 this->y = float2;
 } else if (this->lastPlayerForHello != remotePlayer.OnlineID) {
 this->lastPlayerForHello = remotePlayer.OnlineID;
 }
 }
 }

 void aiNormalMovement() {
 float float0 = this->getDistance(this->movement.speed);
 FakeClientManager.PlayerManager.RemotePlayer remotePlayer = this->getNearestPlayer();
 if (remotePlayer == nullptr) {
 this->aiRunAwayFromZombiesMovement();
 } else {
 float float1 = IsoUtils.DistanceToSquared(this->x, this->y, remotePlayer.x, remotePlayer.y);
 if (float1 > 36.0F) {
 this->movement.speed = 13.0F;
 this->movement.motion = FakeClientManager.Movement.Motion.Run;
 } else {
 this->movement.speed = 4.0F;
 this->movement.motion = FakeClientManager.Movement.Motion.Walk;
 }

 FakeClientManager.Zombie zombie0 = this->getNearestZombie();
 float float2 = Float.POSITIVE_INFINITY;
 if (zombie0 != nullptr) {
 float2 = IsoUtils.DistanceToSquared(this->x, this->y, zombie0.x, zombie0.y);
 }

 FakeClientManager.Zombie zombie1 = this->getNearestZombie(remotePlayer);
 float float3 = Float.POSITIVE_INFINITY;
 if (zombie1 != nullptr) {
 float3 = IsoUtils.DistanceToSquared(remotePlayer.x, remotePlayer.y, zombie1.x, zombie1.y);
 }

 if (float3 < 25.0F) {
 zombie0 = zombie1;
 float2 = float3;
 }

 if (float1 > 25.0F || zombie0 == nullptr) {
 this->direction.set(remotePlayer.x - this->x, remotePlayer.y - this->y);
 float float4 = this->direction.normalize();
 if (float4 > 4.0F) {
 float float5 = this->x + float0 * this->direction.x;
 float float6 = this->y + float0 * this->direction.y;
 this->x = float5;
 this->y = float6;
 } else if (this->lastPlayerForHello != remotePlayer.OnlineID) {
 this->lastPlayerForHello = remotePlayer.OnlineID;
 }
 } else if (float2 < 25.0F) {
 this->direction.set(zombie0.x - this->x, zombie0.y - this->y);
 this->direction.normalize();
 this->x = this->x + float0 * this->direction.x;
 this->y = this->y + float0 * this->direction.y;
 }
 }
 }

 void checkRequestChunks() {
 int int0 = (int)this->x / 10;
 int int1 = (int)this->y / 10;
 if (Math.abs(int0 - this->WorldX) < 13 && Math.abs(int1 - this->WorldY) < 13) {
 if (int0 != this->WorldX) {
 if (int0 < this->WorldX) {
 for (int int2 = -6; int2 <= 6; int2++) {
 this->client.addChunkRequest(this->WorldX - 6, this->WorldY + int2, 0, int2 + 6);
 }
 } else {
 for (int int3 = -6; int3 <= 6; int3++) {
 this->client.addChunkRequest(this->WorldX + 6, this->WorldY + int3, 12, int3 + 6);
 }
 }
 } else if (int1 != this->WorldY) {
 if (int1 < this->WorldY) {
 for (int int4 = -6; int4 <= 6; int4++) {
 this->client.addChunkRequest(this->WorldX + int4, this->WorldY - 6, int4 + 6, 0);
 }
 } else {
 for (int int5 = -6; int5 <= 6; int5++) {
 this->client.addChunkRequest(this->WorldX + int5, this->WorldY + 6, int5 + 6, 12);
 }
 }
 }
 } else {
 int int6 = this->WorldX - 6;
 int int7 = this->WorldY - 6;
 int int8 = this->WorldX + 6;
 int int9 = this->WorldY + 6;

 for (int int10 = int6; int10 <= int8; int10++) {
 for (int int11 = int7; int11 <= int9; int11++) {
 this->client.addChunkRequest(int10, int11, int10 - int6, int11 - int7);
 }
 }
 }

 this->client.requestChunks();
 this->WorldX = int0;
 this->WorldY = int1;
 }

 void hit() {
 FakeClientManager.info(this->movement.id, String.format("Player %3d hit", this->OnlineID);
 }

 void run() {
 this->simulator.update();
 if (this->updateLimiter.Check()) {
 if (isVOIPEnabled) {
 FMODManager.instance.tick();
 VoiceManager.instance.update();
 }

 if (this->movement.doTeleport() && this->teleportLimiter.Check()) {
 this->teleportMovement();
 }

 switch (this->movement.type) {
 case Circle:
 this->circleMovement();
 break;
 case Line:
 this->lineMovement();
 break;
 case AIAttackZombies:
 this->aiAttackZombiesMovement();
 break;
 case AIRunAwayFromZombies:
 this->aiRunAwayFromZombiesMovement();
 break;
 case AIRunToAnotherPlayers:
 this->aiRunToAnotherPlayersMovement();
 break;
 case AINormal:
 this->aiNormalMovement();
 }

 this->checkRequestChunks();
 if (this->predictLimiter.Check()) {
 int int0 = (int)(this->client.getServerTime() / 1000000L);
 this->networkCharacter.checkResetPlayer(int0);
 NetworkCharacter.Transform transform = this->networkCharacter
 .predict(predictInterval, int0, this->x, this->y, this->direction.x, this->direction.y);
 this->client.sendPlayer(transform, int0, this->direction);
 }

 if (this->timeSyncLimiter.Check()) {
 this->client.sendTimeSync();
 this->client.sendSyncRadioData();
 }

 if (this->movement.hordeCreator != nullptr && this->movement.hordeCreator.hordeCreatorLimiter.Check()) {
 this->client.sendCommand(this->movement.hordeCreator.getCommand((int)this->x, (int)this->y, (int)this->z);
 }

 if (this->movement.soundMaker != nullptr && this->movement.soundMaker.soundMakerLimiter.Check()) {
 this->client.sendWorldSound4Player((int)this->x, (int)this->y, (int)this->z, this->movement.soundMaker.radius, this->movement.soundMaker.radius);
 this->client.sendChatMessage(this->movement.soundMaker.message);
 this->client.sendEventPacket(this->OnlineID, (int)this->x, (int)this->y, (int)this->z, (byte)4, "shout");
 }
 }
 }

 private static class Clothes {
 const uint8_t flags;
 const uint8_t text;
 const std::string name;

 Clothes(byte byte0, byte byte1, String string) {
 this->flags = byte0;
 this->text = byte1;
 this->name = string;
 }
 }
 }

 private static class PlayerManager {
 private FakeClientManager.Player player = nullptr;
 const PlayerPacket playerPacket = new PlayerPacket();
 public HashMap<Integer, FakeClientManager.PlayerManager.RemotePlayer> players = std::make_unique<HashMap<>>();

 public PlayerManager(FakeClientManager.Player playerx) {
 this->player = playerx;
 }

 void parsePlayer(ByteBuffer byteBuffer) {
 PlayerPacket playerPacketx = this->playerPacket;
 playerPacketx.parse(byteBuffer, nullptr);
 synchronized (this->players) {
 FakeClientManager.PlayerManager.RemotePlayer remotePlayer = this->players.get(playerPacketx.id);
 if (remotePlayer == nullptr) {
 remotePlayer = new FakeClientManager.PlayerManager.RemotePlayer(playerPacketx.id);
 this->players.put(Integer.valueOf(playerPacketx.id), remotePlayer);
 FakeClientManager.trace(this->player.movement.id, String.format("New player %s", remotePlayer.OnlineID);
 }

 remotePlayer.playerPacket.copy(playerPacketx);
 remotePlayer.x = playerPacketx.realx;
 remotePlayer.y = playerPacketx.realy;
 remotePlayer.z = playerPacketx.realz;
 }
 }

 void parsePlayerTimeout(ByteBuffer byteBuffer) {
 short short0 = byteBuffer.getShort();
 synchronized (this->players) {
 this->players.remove(short0);
 }

 FakeClientManager.trace(this->player.movement.id, String.format("Remove player %s", short0);
 }

 private class RemotePlayer {
 float x;
 float y;
 float z;
 short OnlineID;
 PlayerPacket playerPacket = nullptr;

 public RemotePlayer(short short0) {
 this->playerPacket = std::make_unique<PlayerPacket>();
 this->playerPacket.id = short0;
 this->OnlineID = short0;
 }
 }
 }

 private static class SoundMaker {
 const int radius;
 const int interval;
 const std::string message;
 const UpdateLimit soundMakerLimiter;

 public SoundMaker(int int1, int int0, const std::string& string) {
 this->radius = int0;
 this->message = string;
 this->interval = int1;
 this->soundMakerLimiter = new UpdateLimit(int1);
 }
 }

 private static class StringUTF {
 private char[] chars;
 ByteBuffer byteBuffer;
 CharBuffer charBuffer;
 CharsetEncoder ce;
 CharsetDecoder cd;

 int encode(const std::string& string) {
 if (this->chars == nullptr || this->chars.length < string.length()) {
 int int0 = (string.length() + 128 - 1) / 128 * 128;
 this->chars = new char[int0];
 this->charBuffer = CharBuffer.wrap(this->chars);
 }

 string.getChars(0, string.length(), this->chars, 0);
 this->charBuffer.limit(string.length());
 this->charBuffer.position(0);
 if (this->ce == nullptr) {
 this->ce = StandardCharsets.UTF_8.newEncoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
 }

 this->ce.reset();
 int int1 = (int)((double)string.length() * this->ce.maxBytesPerChar());
 int1 = (int1 + 128 - 1) / 128 * 128;
 if (this->byteBuffer == nullptr || this->byteBuffer.capacity() < int1) {
 this->byteBuffer = ByteBuffer.allocate(int1);
 }

 this->byteBuffer.clear();
 CoderResult coderResult = this->ce.encode(this->charBuffer, this->byteBuffer, true);
 return this->byteBuffer.position();
 }

 std::string decode(int int1) {
 if (this->cd == nullptr) {
 this->cd = StandardCharsets.UTF_8.newDecoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
 }

 this->cd.reset();
 int int0 = (int)((double)int1 * this->cd.maxCharsPerByte());
 if (this->chars == nullptr || this->chars.length < int0) {
 int int2 = (int0 + 128 - 1) / 128 * 128;
 this->chars = new char[int2];
 this->charBuffer = CharBuffer.wrap(this->chars);
 }

 this->charBuffer.clear();
 CoderResult coderResult = this->cd.decode(this->byteBuffer, this->charBuffer, true);
 return new String(this->chars, 0, this->charBuffer.position());
 }

 void save(ByteBuffer byteBufferx, const std::string& string) {
 if (string != nullptr && !string.empty()) {
 int int0 = this->encode(string);
 byteBufferx.putShort((short)int0);
 this->byteBuffer.flip();
 byteBufferx.put(this->byteBuffer);
 } else {
 byteBufferx.putShort((short)0);
 }
 }

 std::string load(ByteBuffer byteBufferx) {
 short short0 = byteBufferx.getShort();
 if (short0 <= 0) {
 return "";
 } else {
 int int0 = (short0 + 128 - 1) / 128 * 128;
 if (this->byteBuffer == nullptr || this->byteBuffer.capacity() < int0) {
 this->byteBuffer = ByteBuffer.allocate(int0);
 }

 this->byteBuffer.clear();
 if (byteBufferx.remaining() < short0) {
 DebugLog.General
 .error("GameWindow.StringUTF.load> numBytes:" + short0 + " is higher than the remaining bytes in the buffer:" + byteBufferx.remaining());
 }

 int int1 = byteBufferx.limit();
 byteBufferx.limit(byteBufferx.position() + short0);
 this->byteBuffer.put(byteBufferx);
 byteBufferx.limit(int1);
 this->byteBuffer.flip();
 return this->decode(short0);
 }
 }
 }

 private static class Zombie {
 long lastUpdate;
 float x;
 float y;
 float z;
 short OnlineID;
 bool localOwnership = false;
 ZombiePacket zombiePacket = nullptr;
 IsoDirections dir = IsoDirections.N;
 float health = 1.0F;
 uint8_t walkType = (byte)Rand.Next(NetworkVariables.WalkType.values().length);
 float dropPositionX;
 float dropPositionY;
 bool isMoving = false;

 public Zombie(short short0) {
 this->zombiePacket = std::make_unique<ZombiePacket>();
 this->zombiePacket.id = short0;
 this->OnlineID = short0;
 this->localOwnership = false;
 }
 }

 private static class ZombieSimulator {
 public static FakeClientManager.ZombieSimulator.Behaviour behaviour = FakeClientManager.ZombieSimulator.Behaviour.Stay;
 static int deleteZombieDistanceSquared = 10000;
 static int forgotZombieDistanceSquared = 225;
 static int canSeeZombieDistanceSquared = 100;
 static int seeZombieDistanceSquared = 25;
 static bool canChangeTarget = true;
 static int updatePeriod = 100;
 static int attackPeriod = 1000;
 static int maxZombiesPerUpdate = 300;
 const ByteBuffer bb = ByteBuffer.allocate(1000000);
 UpdateLimit updateLimiter = new UpdateLimit(updatePeriod);
 UpdateLimit attackLimiter = new UpdateLimit(attackPeriod);
 private FakeClientManager.Player player = nullptr;
 const ZombiePacket zombiePacket = new ZombiePacket();
 private HashSet<Short> authoriseZombiesCurrent = std::make_unique<HashSet<>>();
 private HashSet<Short> authoriseZombiesLast = std::make_unique<HashSet<>>();
 private ArrayList<Short> unknownZombies = std::make_unique<ArrayList<>>();
 private HashMap<Integer, FakeClientManager.Zombie> zombies = std::make_unique<HashMap<>>();
 private ArrayDeque<FakeClientManager.Zombie> zombies4Add = std::make_unique<ArrayDeque<>>();
 private ArrayDeque<FakeClientManager.Zombie> zombies4Delete = std::make_unique<ArrayDeque<>>();
 private HashSet<Short> authoriseZombies = std::make_unique<HashSet<>>();
 private ArrayDeque<FakeClientManager.Zombie> SendQueue = std::make_unique<ArrayDeque<>>();
 static Vector2 tmpDir = new Vector2();

 public ZombieSimulator(FakeClientManager.Player playerx) {
 this->player = playerx;
 }

 void becomeLocal(FakeClientManager.Zombie zombie0) {
 zombie0.localOwnership = true;
 }

 void becomeRemote(FakeClientManager.Zombie zombie0) {
 zombie0.localOwnership = false;
 }

 void clear() {
 std::unordered_set hashSet = this->authoriseZombiesCurrent;
 this->authoriseZombiesCurrent = this->authoriseZombiesLast;
 this->authoriseZombiesLast = hashSet;
 this->authoriseZombiesLast.removeIf(short0 -> this->zombies.get(Integer.valueOf(short0) == nullptr);
 this->authoriseZombiesCurrent.clear();
 }

 void add(short short0) {
 this->authoriseZombiesCurrent.add(short0);
 }

 void receivePacket(ByteBuffer byteBuffer) {
 short short0 = byteBuffer.getShort();

 for (short short1 = 0; short1 < short0; short1++) {
 this->parseZombie(byteBuffer);
 }
 }

 void parseZombie(ByteBuffer byteBuffer) {
 ZombiePacket zombiePacketx = this->zombiePacket;
 zombiePacketx.parse(byteBuffer, nullptr);
 FakeClientManager.Zombie zombie0 = this->zombies.get(Integer.valueOf(zombiePacketx.id);
 if (!this->authoriseZombies.contains(zombiePacketx.id) || zombie0 == nullptr) {
 if (zombie0 == nullptr) {
 zombie0 = new FakeClientManager.Zombie(zombiePacketx.id);
 this->zombies4Add.add(zombie0);
 FakeClientManager.trace(this->player.movement.id, String.format("New zombie %s", zombie0.OnlineID);
 }

 zombie0.lastUpdate = System.currentTimeMillis();
 zombie0.zombiePacket.copy(zombiePacketx);
 zombie0.x = zombiePacketx.realX;
 zombie0.y = zombiePacketx.realY;
 zombie0.z = zombiePacketx.realZ;
 }
 }

 void process() {
 for (Short short0 : Sets.difference(this->authoriseZombiesCurrent, this->authoriseZombiesLast) {
 FakeClientManager.Zombie zombie0 = this->zombies.get(Integer.valueOf(short0);
 if (zombie0 != nullptr) {
 this->becomeLocal(zombie0);
 } else if (!this->unknownZombies.contains(short0) {
 this->unknownZombies.add(short0);
 }
 }

 for (Short short1 : Sets.difference(this->authoriseZombiesLast, this->authoriseZombiesCurrent) {
 FakeClientManager.Zombie zombie1 = this->zombies.get(Integer.valueOf(short1);
 if (zombie1 != nullptr) {
 this->becomeRemote(zombie1);
 }
 }

 synchronized (this->authoriseZombies) {
 this->authoriseZombies.clear();
 this->authoriseZombies.addAll(this->authoriseZombiesCurrent);
 }
 }

 void send() {
 if (this->authoriseZombies.size() != 0 || this->unknownZombies.size() != 0) {
 if (this->SendQueue.empty()) {
 synchronized (this->authoriseZombies) {
 for (Short short0 : this->authoriseZombies) {
 FakeClientManager.Zombie zombie0 = this->zombies.get(Integer.valueOf(short0);
 if (zombie0 != nullptr && zombie0.OnlineID != -1) {
 this->SendQueue.add(zombie0);
 }
 }
 }
 }

 this->bb.clear();
 this->bb.putShort((short)0);
 int int0 = this->unknownZombies.size();
 this->bb.putShort((short)int0);

 for (int int1 = 0; int1 < this->unknownZombies.size(); int1++) {
 if (this->unknownZombies.get(int1) == nullptr) {
 return;
 }

 this->bb.putShort(this->unknownZombies.get(int1);
 }

 this->unknownZombies.clear();
 int int2 = this->bb.position();
 this->bb.putShort((short)maxZombiesPerUpdate);
 int int3 = 0;

 while (!this->SendQueue.empty()) {
 FakeClientManager.Zombie zombie1 = this->SendQueue.poll();
 if (zombie1.OnlineID != -1) {
 zombie1.zombiePacket.write(this->bb);
 if (++int3 >= maxZombiesPerUpdate) {
 break;
 }
 }
 }

 if (int3 < maxZombiesPerUpdate) {
 int int4 = this->bb.position();
 this->bb.position(int2);
 this->bb.putShort((short)int3);
 this->bb.position(int4);
 }

 if (int3 > 0 || int0 > 0) {
 ByteBuffer byteBuffer = this->player.client.network.startPacket();
 this->player.client.doPacket(PacketTypes.PacketType.ZombieSimulation.getId(), byteBuffer);
 byteBuffer.put(this->bb.array(), 0, this->bb.position());
 this->player.client.network.endPacketSuperHighUnreliable(this->player.client.connectionGUID);
 }
 }
 }

 void simulate(int var1, FakeClientManager.Zombie zombie0) {
 float float0 = IsoUtils.DistanceToSquared(this->player.x, this->player.y, zombie0.x, zombie0.y);
 if (!(float0 > deleteZombieDistanceSquared) && (zombie0.localOwnership || zombie0.lastUpdate + 5000L >= System.currentTimeMillis())) {
 tmpDir.set(-zombie0.x + this->player.x, -zombie0.y + this->player.y);
 if (zombie0.isMoving) {
 float float1 = 0.2F;
 zombie0.x = PZMath.lerp(zombie0.x, zombie0.zombiePacket.x, float1);
 zombie0.y = PZMath.lerp(zombie0.y, zombie0.zombiePacket.y, float1);
 zombie0.z = 0.0F;
 zombie0.dir = IsoDirections.fromAngle(tmpDir);
 }

 if (canChangeTarget) {
 synchronized (this->player.playerManager.players) {
 for (FakeClientManager.PlayerManager.RemotePlayer remotePlayer : this->player.playerManager.players.values()) {
 float float2 = IsoUtils.DistanceToSquared(remotePlayer.x, remotePlayer.y, zombie0.x, zombie0.y);
 if (float2 < seeZombieDistanceSquared) {
 zombie0.zombiePacket.target = remotePlayer.OnlineID;
 break;
 }
 }
 }
 } else {
 zombie0.zombiePacket.target = this->player.OnlineID;
 }

 if (behaviour == FakeClientManager.ZombieSimulator.Behaviour.Stay) {
 zombie0.isMoving = false;
 } else if (behaviour == FakeClientManager.ZombieSimulator.Behaviour.Normal) {
 if (float0 > forgotZombieDistanceSquared) {
 zombie0.isMoving = false;
 }

 if (float0 < canSeeZombieDistanceSquared && (Rand.Next(100) < 1 || zombie0.dir == IsoDirections.fromAngle(tmpDir) {
 zombie0.isMoving = true;
 }

 if (float0 < seeZombieDistanceSquared) {
 zombie0.isMoving = true;
 }
 } else {
 zombie0.isMoving = true;
 }

 float float3 = 0.0F;
 if (zombie0.isMoving) {
 Vector2 vector = zombie0.dir.ToVector();
 float3 = 3.0F;
 if (float0 < 100.0F) {
 float3 = 6.0F;
 }

 long long0 = System.currentTimeMillis() - zombie0.lastUpdate;
 zombie0.zombiePacket.x = zombie0.x + vector.x * (float)long0 * 0.001F * float3;
 zombie0.zombiePacket.y = zombie0.y + vector.y * (float)long0 * 0.001F * float3;
 zombie0.zombiePacket.z = (byte)zombie0.z;
 zombie0.zombiePacket.moveType = NetworkVariables.PredictionTypes.Moving;
 } else {
 zombie0.zombiePacket.x = zombie0.x;
 zombie0.zombiePacket.y = zombie0.y;
 zombie0.zombiePacket.z = (byte)zombie0.z;
 zombie0.zombiePacket.moveType = NetworkVariables.PredictionTypes.Static;
 }

 zombie0.zombiePacket.booleanVariables = 0;
 if (float0 < 100.0F) {
 zombie0.zombiePacket.booleanVariables = (short)(zombie0.zombiePacket.booleanVariables | 2);
 }

 zombie0.zombiePacket.timeSinceSeenFlesh = zombie0.isMoving ? 0 : 100000;
 zombie0.zombiePacket.smParamTargetAngle = 0;
 zombie0.zombiePacket.speedMod = 1000;
 zombie0.zombiePacket.walkType = NetworkVariables.WalkType.values()[zombie0.walkType];
 zombie0.zombiePacket.realX = zombie0.x;
 zombie0.zombiePacket.realY = zombie0.y;
 zombie0.zombiePacket.realZ = (byte)zombie0.z;
 zombie0.zombiePacket.realHealth = (short)(zombie0.health * 1000.0F);
 zombie0.zombiePacket.realState = NetworkVariables.ZombieState.fromString("fakezombie-" + behaviour.toString().toLowerCase());
 if (zombie0.isMoving) {
 zombie0.zombiePacket.pfbType = 1;
 zombie0.zombiePacket.pfbTarget = this->player.OnlineID;
 } else {
 zombie0.zombiePacket.pfbType = 0;
 }

 if (float0 < 2.0F && this->attackLimiter.Check()) {
 zombie0.health = zombie0.health - FakeClientManager.Player.damage;
 this->sendHitCharacter(zombie0, FakeClientManager.Player.damage);
 if (zombie0.health <= 0.0F) {
 this->player.client.sendChatMessage("DIE!!");
 this->zombies4Delete.add(zombie0);
 }
 }

 zombie0.lastUpdate = System.currentTimeMillis();
 } else {
 this->zombies4Delete.add(zombie0);
 }
 }

 void writeHitInfoToZombie(ByteBuffer byteBuffer, short short0, float float0, float float1, float float2) {
 byteBuffer.put((byte)2);
 byteBuffer.putShort(short0);
 byteBuffer.put((byte)0);
 byteBuffer.putFloat(float0);
 byteBuffer.putFloat(float1);
 byteBuffer.putFloat(0.0F);
 byteBuffer.putFloat(float2);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putInt(100);
 }

 void sendHitCharacter(FakeClientManager.Zombie zombie0, float float0) {
 bool boolean0 = false;
 ByteBuffer byteBuffer = this->player.client.network.startPacket();
 this->player.client.doPacket(PacketTypes.PacketType.HitCharacter.getId(), byteBuffer);
 byteBuffer.put((byte)3);
 byteBuffer.putShort(this->player.OnlineID);
 byteBuffer.putShort((short)0);
 byteBuffer.putFloat(this->player.x);
 byteBuffer.putFloat(this->player.y);
 byteBuffer.putFloat(this->player.z);
 byteBuffer.putFloat(this->player.direction.x);
 byteBuffer.putFloat(this->player.direction.y);
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 byteBuffer.putShort((short)((this->player.weapon_isBareHeads ? 2 : 0) + (boolean0 ? 8 : 0);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(1.0F);
 FakeClientManager.WriteStringUTF(byteBuffer, "default");
 uint8_t byte0 = 0;
 byte0 = (byte)(byte0 | (byte)(this->player.weapon_isBareHeads ? 9 : 0);
 byteBuffer.put(byte0);
 byteBuffer.put((byte)0);
 byteBuffer.putShort((short)0);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putInt(0);
 uint8_t byte1 = 1;
 byteBuffer.put(byte1);

 for (int int0 = 0; int0 < byte1; int0++) {
 this->writeHitInfoToZombie(byteBuffer, zombie0.OnlineID, zombie0.x, zombie0.y, float0);
 }

 byte1 = 0;
 byteBuffer.put(byte1);
 byte1 = 1;
 byteBuffer.put(byte1);

 for (int int1 = 0; int1 < byte1; int1++) {
 this->writeHitInfoToZombie(byteBuffer, zombie0.OnlineID, zombie0.x, zombie0.y, float0);
 }

 if (!this->player.weapon_isBareHeads) {
 byteBuffer.put((byte)0);
 } else {
 byteBuffer.put((byte)1);
 byteBuffer.putShort(this->player.registry_id);
 byteBuffer.put((byte)1);
 byteBuffer.putInt(this->player.weapon_id);
 byteBuffer.put((byte)0);
 byteBuffer.putInt(0);
 byteBuffer.putInt(0);
 }

 byteBuffer.putShort(zombie0.OnlineID);
 byteBuffer.putShort((short)(float0 >= zombie0.health ? 3 : 0);
 byteBuffer.putFloat(zombie0.x);
 byteBuffer.putFloat(zombie0.y);
 byteBuffer.putFloat(zombie0.z);
 byteBuffer.putFloat(zombie0.dir.ToVector().x);
 byteBuffer.putFloat(zombie0.dir.ToVector().y);
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 byteBuffer.putShort((short)0);
 FakeClientManager.WriteStringUTF(byteBuffer, "");
 FakeClientManager.WriteStringUTF(byteBuffer, "FRONT");
 byteBuffer.put((byte)0);
 byteBuffer.putFloat(float0);
 byteBuffer.putFloat(1.0F);
 byteBuffer.putFloat(this->player.direction.x);
 byteBuffer.putFloat(this->player.direction.y);
 byteBuffer.putFloat(1.0F);
 byteBuffer.put((byte)0);
 if (tmpDir.getLength() > 0.0F) {
 zombie0.dropPositionX = zombie0.x + tmpDir.x / tmpDir.getLength();
 zombie0.dropPositionY = zombie0.y + tmpDir.y / tmpDir.getLength();
 } else {
 zombie0.dropPositionX = zombie0.x;
 zombie0.dropPositionY = zombie0.y;
 }

 byteBuffer.putFloat(zombie0.dropPositionX);
 byteBuffer.putFloat(zombie0.dropPositionY);
 byteBuffer.put((byte)zombie0.z);
 byteBuffer.putFloat(zombie0.dir.toAngle());
 this->player.client.network.endPacketImmediate(this->player.client.connectionGUID);
 }

 void sendSendDeadZombie(FakeClientManager.Zombie zombie0) {
 ByteBuffer byteBuffer = this->player.client.network.startPacket();
 this->player.client.doPacket(PacketTypes.PacketType.ZombieDeath.getId(), byteBuffer);
 byteBuffer.putShort(zombie0.OnlineID);
 byteBuffer.putFloat(zombie0.x);
 byteBuffer.putFloat(zombie0.y);
 byteBuffer.putFloat(zombie0.z);
 byteBuffer.putFloat(zombie0.dir.toAngle());
 byteBuffer.put((byte)zombie0.dir.index());
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 byteBuffer.put((byte)0);
 this->player.client.network.endPacketImmediate(this->player.client.connectionGUID);
 }

 void simulateAll() {
 while (!this->zombies4Add.empty()) {
 FakeClientManager.Zombie zombie0 = this->zombies4Add.poll();
 this->zombies.put(Integer.valueOf(zombie0.OnlineID), zombie0);
 }

 this->zombies.forEach(this::simulate);

 while (!this->zombies4Delete.empty()) {
 FakeClientManager.Zombie zombie1 = this->zombies4Delete.poll();
 this->zombies.remove(Integer.valueOf(zombie1.OnlineID);
 }
 }

 void update() {
 if (this->updateLimiter.Check()) {
 this->simulateAll();
 this->send();
 }
 }

 private static enum Behaviour {
 Stay,
 Normal,
 Attack;
 }
 }
}
} // namespace network
} // namespace zombie
