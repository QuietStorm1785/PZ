#pragma once
#include <mutex>
#include "java/net/ConnectException.h"
#include "java/sql/SQLException.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/AmbientSoundManager.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameProfiler.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/asset/AssetManagers.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Safety.h"
#include "zombie/characters/SafetySystemManager.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/skills/CustomPerks.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Languages.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/ProxyPrintStream.h"
#include "zombie/core/Rand.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/backup/ZipBackup.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferReader.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/profiling/PerformanceProfileFrameProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/raknet/RakNetPeerInterface.h"
#include "zombie/core/raknet/RakVoice.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/UdpEngine.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNodeAssetManager.h"
#include "zombie/core/skinnedmodel/model/AiSceneAsset.h"
#include "zombie/core/skinnedmodel/model/AiSceneAssetManager.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/AnimationAssetManager.h"
#include "zombie/core/skinnedmodel/model/MeshAssetManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/ClothingItemAssetManager.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureAssetManager.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/PortMapper.h"
#include "zombie/core/znet/SteamGameServer.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/globalObjects/SGlobalObjectNetwork.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/inventory/CompressIdenticalItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/RecipeManager.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/ObjectsSyncRequests.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/BSFurnace.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/packets/ActionPacket.h"
#include "zombie/network/packets/AddXp.h"
#include "zombie/network/packets/CleanBurn.h"
#include "zombie/network/packets/DeadPlayerPacket.h"
#include "zombie/network/packets/DeadZombiePacket.h"
#include "zombie/network/packets/Disinfect.h"
#include "zombie/network/packets/EventPacket.h"
#include "zombie/network/packets/PlaySoundPacket.h"
#include "zombie/network/packets/PlayWorldSoundPacket.h"
#include "zombie/network/packets/PlayerDataRequestPacket.h"
#include "zombie/network/packets/PlayerPacket.h"
#include "zombie/network/packets/RemoveBullet.h"
#include "zombie/network/packets/RemoveCorpseFromMap.h"
#include "zombie/network/packets/RemoveGlass.h"
#include "zombie/network/packets/RequestDataPacket.h"
#include "zombie/network/packets/SafetyPacket.h"
#include "zombie/network/packets/StartFire.h"
#include "zombie/network/packets/Stitch.h"
#include "zombie/network/packets/StopSoundPacket.h"
#include "zombie/network/packets/SyncClothingPacket.h"
#include "zombie/network/packets/SyncInjuriesPacket.h"
#include "zombie/network/packets/SyncNonPvpZonePacket.h"
#include "zombie/network/packets/SyncSafehousePacket.h"
#include "zombie/network/packets/ValidatePacket.h"
#include "zombie/network/packets/WaveSignal.h"
#include "zombie/network/packets/hit/HitCharacterPacket.h"
#include "zombie/popman/MPDebugInfo.h"
#include "zombie/popman/NetworkZombieManager.h"
#include "zombie/popman/NetworkZombiePacker.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/sandbox/CustomSandboxOptions.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/util/PZSQLUtils.h"
#include "zombie/util/PublicServerUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/moddata/GlobalModData.h"
#include "zombie/worldMap/WorldMapRemotePlayer.h"
#include "zombie/worldMap/WorldMapRemotePlayers.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GameServer {
public:

 // Mutexes for synchronized blocks
 static std::mutex MainLoopNetDataHighPriorityQ_mutex;

 std::mutex consoleCommands_mutex;
 static const int MAX_PLAYERS = 512;
 static const int TimeLimitForProcessPackets = 70;
 static const int PacketsUpdateRate = 200;
 static const int FPS = 10;
private
 static HashMap<String, GameServer.CCFilter> ccFilters =
 std::make_unique<HashMap<>>();
 static int test = 432432;
 static int DEFAULT_PORT = 16261;
 static int UDPPort = 16262;
 static std::string IPCommandline = nullptr;
 static int PortCommandline = -1;
 static int UDPPortCommandline = -1;
 static bool SteamVACCommandline;
 static bool GUICommandline;
 static bool bServer = false;
 static bool bCoop = false;
 static bool bDebug = false;
 static bool bSoftReset = false;
 static UdpEngine udpEngine;
public
 static HashMap<Short, Long> IDToAddressMap =
 std::make_unique<HashMap<>>();
public
 static HashMap<Short, IsoPlayer> IDToPlayerMap =
 std::make_unique<HashMap<>>();
public
 static ArrayList<IsoPlayer> Players = std::make_unique<ArrayList<>>();
 static float timeSinceKeepAlive = 0.0F;
 static int MaxTicksSinceKeepAliveBeforeStall = 60;
public
 static HashSet<UdpConnection> DebugPlayer =
 std::make_unique<HashSet<>>();
 static int ResetID = 0;
public
 static ArrayList<String> ServerMods = std::make_unique<ArrayList<>>();
public
 static ArrayList<Long> WorkshopItems = std::make_unique<ArrayList<>>();
public
 static String[] WorkshopInstallFolders;
public
 static long[] WorkshopTimeStamps;
 static std::string ServerName = "servertest";
public
 static DiscordBot discordBot = new DiscordBot(
 ServerName, (string0, string1)
 ->ChatServer.getInstance()
 .sendMessageFromDiscordToGeneralChat(string0, string1);
 static std::string checksum = "";
 static std::string GameMap = "Muldraugh, KY";
 static bool bFastForward;
public
 static HashMap<String, Integer> transactionIDMap =
 std::make_unique<HashMap<>>();
 static const ObjectsSyncRequests worldObjectsServerSyncReq =
 new ObjectsSyncRequests(false);
 static std::string ip = "127.0.0.1";
 static int count = 0;
private
 static UdpConnection[] SlotToConnection = new UdpConnection[512];
private
 static HashMap<IsoPlayer, Long> PlayerToAddressMap =
 std::make_unique<HashMap<>>();
private
 static ArrayList<Integer> alreadyRemoved =
 std::make_unique<ArrayList<>>();
 static bool bDone;
 static bool launched = false;
private
 static ArrayList<String> consoleCommands =
 std::make_unique<ArrayList<>>();
private
 static HashMap<Long, IZomboidPacket> MainLoopPlayerUpdate =
 std::make_unique<HashMap<>>();
private
 static ConcurrentLinkedQueue<IZomboidPacket> MainLoopPlayerUpdateQ =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<IZomboidPacket>
 MainLoopNetDataHighPriorityQ =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<IZomboidPacket> MainLoopNetDataQ =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ArrayList<IZomboidPacket> MainLoopNetData2 =
 std::make_unique<ArrayList<>>();
private
 static HashMap<Short, Vector2> playerToCoordsMap =
 std::make_unique<HashMap<>>();
private
 static HashMap<Short, Integer> playerMovedToFastMap =
 std::make_unique<HashMap<>>();
 static ByteBuffer large_file_bb = ByteBuffer.allocate(2097152);
 static long previousSave = Calendar.getInstance().getTimeInMillis();
 std::string poisonousBerry = nullptr;
 std::string poisonousMushroom = nullptr;
 std::string difficulty = "Hardcore";
 static int droppedPackets = 0;
 static int countOfDroppedPackets = 0;
 static int countOfDroppedConnections = 0;
 static UdpConnection removeZombiesConnection = nullptr;
 static UpdateLimit calcCountPlayersInRelevantPositionLimiter =
 new UpdateLimit(2000L);
 static UpdateLimit sendWorldMapPlayerPositionLimiter = new UpdateLimit(1000L);
 static LoginQueue loginQueue = new LoginQueue();
 static int mainCycleExceptionLogCount = 25;
 static Thread MainThread;
public
 static ArrayList<IsoPlayer> tempPlayers =
 std::make_unique<ArrayList<>>();

 static void PauseAllClients() {
 std::string string = "[SERVERMSG] Server saving...Please wait";

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StartPause.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.StartPause.send(udpConnection);
 }
 }

 static void UnPauseAllClients() {
 std::string string = "[SERVERMSG] Server saved game...enjoy :)";

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StopPause.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.StopPause.send(udpConnection);
 }
 }

 static std::string parseIPFromCommandline(String[] strings0, int int0,
 std::string_view string) {
 if (int0 == strings0.length - 1) {
 DebugLog.log("expected argument after \"" + string + "\"");
 System.exit(0);
 } else if (strings0[int0 + 1].trim().empty()) {
 DebugLog.log("empty argument given to \"\" + option + \"\"");
 System.exit(0);
 } else {
 String[] strings1 = strings0[int0 + 1].trim().split("\\.");
 if (strings1.length == 4) {
 for (int int1 = 0; int1 < 4; int1++) {
 try {
 int int2 = Integer.parseInt(strings1[int1]);
 if (int2 < 0 || int2 > 255) {
 DebugLog.log("expected IP address after \"" + string +
 "\", got \"" + strings0[int0 + 1] + "\"");
 System.exit(0);
 }
 } catch (NumberFormatException numberFormatException) {
 DebugLog.log("expected IP address after \"" + string +
 "\", got \"" + strings0[int0 + 1] + "\"");
 System.exit(0);
 }
 }
 } else {
 DebugLog.log("expected IP address after \"" + string + "\", got \"" +
 strings0[int0 + 1] + "\"");
 System.exit(0);
 }
 }

 return strings0[int0 + 1];
 }

 static int parsePortFromCommandline(String[] strings, int int0,
 std::string_view string) {
 if (int0 == strings.length - 1) {
 DebugLog.log("expected argument after \"" + string + "\"");
 System.exit(0);
 } else if (strings[int0 + 1].trim().empty()) {
 DebugLog.log("empty argument given to \"" + string + "\"");
 System.exit(0);
 } else {
 try {
 return Integer.parseInt(strings[int0 + 1].trim());
 } catch (NumberFormatException numberFormatException) {
 DebugLog.log("expected an integer after \"" + string + "\"");
 System.exit(0);
 }
 }

 return -1;
 }

 static bool parseBooleanFromCommandline(String[] strings, int int0,
 std::string_view string0) {
 if (int0 == strings.length - 1) {
 DebugLog.log("expected argument after \"" + string0 + "\"");
 System.exit(0);
 } else if (strings[int0 + 1].trim().empty()) {
 DebugLog.log("empty argument given to \"" + string0 + "\"");
 System.exit(0);
 } else {
 std::string string1 = strings[int0 + 1].trim();
 if ("true".equalsIgnoreCase(string1) {
 return true;
 }

 if ("false".equalsIgnoreCase(string1) {
 return false;
 }

 DebugLog.log("expected true or false after \"" + string0 + "\"");
 System.exit(0);
 }

 return false;
 }

 static void setupCoop() { CoopSlave.init(); }

 static void main(String[] strings0) {
 MainThread = Thread.currentThread();
 bServer = true;
 bSoftReset = System.getProperty("softreset") != nullptr;

 for (int int0 = 0; int0 < strings0.length; int0++) {
 if (strings0[int0] != nullptr) {
 if (strings0[int0].startsWith("-cachedir=")) {
 ZomboidFileSystem.instance.setCacheDir(
 strings0[int0].replace("-cachedir=", "").trim());
 } else if (strings0[int0] == "-coop")) {
 bCoop = true;
 }
 }
 }

 if (bCoop) {
 try {
 CoopSlave.initStreams();
 } catch (FileNotFoundException fileNotFoundException0) {
 fileNotFoundException0.printStackTrace();
 }
 } else {
 try {
 std::string string0 = ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "server-console.txt";
 FileOutputStream fileOutputStream = new FileOutputStream(string0);
 PrintStream printStream = new PrintStream(fileOutputStream, true);
 System.setOut(new ProxyPrintStream(System.out, printStream);
 System.setErr(new ProxyPrintStream(System.err, printStream);
 } catch (FileNotFoundException fileNotFoundException1) {
 fileNotFoundException1.printStackTrace();
 }
 }

 DebugLog.init();
 LoggerManager.init();
 DebugLog.log("cachedir set to \"" +
 ZomboidFileSystem.instance.getCacheDir() + "\"");
 if (bCoop) {
 try {
 setupCoop();
 CoopSlave.status("UI_ServerStatus_Initialising");
 } catch (FileNotFoundException fileNotFoundException2) {
 fileNotFoundException2.printStackTrace();
 SteamUtils.shutdown();
 System.exit(37);
 return;
 }
 }

 PZSQLUtils.init();
 Clipper.init();
 Rand.init();
 if (System.getProperty("debug") != nullptr) {
 bDebug = true;
 Core.bDebug = true;
 }

 DebugLog.General.println("version=%s demo=%s",
 Core.getInstance().getVersion(), false);
 DebugLog.General.println("revision=%s date=%s time=%s", "", "", "");

 for (int int1 = 0; int1 < strings0.length; int1++) {
 if (strings0[int1] != nullptr) {
 if (!strings0[int1].startsWith("-disablelog=")) {
 if (strings0[int1].startsWith("-debuglog=")) {
 for (String string1 :
 strings0[int1].replace("-debuglog=", "").split(",")) {
 try {
 DebugLog.setLogEnabled(DebugType.valueOf(string1), true);
 } catch (IllegalArgumentException illegalArgumentException0) {
 }
 }
 } else if (strings0[int1] == "-adminusername")) {
 if (int1 == strings0.length - 1) {
 DebugLog.log("expected argument after \"-adminusername\"");
 System.exit(0);
 } else if (!ServerWorldDatabase.isValidUserName(
 strings0[int1 + 1].trim())) {
 DebugLog.log("invalid username given to \"-adminusername\"");
 System.exit(0);
 } else {
 ServerWorldDatabase.instance.CommandLineAdminUsername =
 strings0[int1 + 1].trim();
 int1++;
 }
 }
 else if (strings0[int1] == "-adminpassword")) {
 if (int1 == strings0.length - 1) {
 DebugLog.log("expected argument after \"-adminpassword\"");
 System.exit(0);
 } else if (strings0[int1 + 1].trim().empty()) {
 DebugLog.log("empty argument given to \"-adminpassword\"");
 System.exit(0);
 } else {
 ServerWorldDatabase.instance.CommandLineAdminPassword =
 strings0[int1 + 1].trim();
 int1++;
 }
 }
 else if (!strings0[int1].startsWith("-cachedir=")) {
 if (strings0[int1] == "-ip")) {
 IPCommandline = parseIPFromCommandline(strings0, int1, "-ip");
 int1++;
 }
 else if (strings0[int1] == "-gui")) {
 GUICommandline = true;
 }
 else if (strings0[int1] == "-nosteam")) {
 System.setProperty("zomboid.steam", "0");
 }
 else if (strings0[int1] == "-statistic")) {
 int int2 =
 parsePortFromCommandline(strings0, int1, "-statistic");
 if (int2 >= 0) {
 MPStatistic.getInstance().setPeriod(int2);
 MPStatistic.getInstance().writeEnabled(true);
 }
 }
 else if (strings0[int1] == "-port")) {
 PortCommandline =
 parsePortFromCommandline(strings0, int1, "-port");
 int1++;
 }
 else if (strings0[int1] == "-udpport")) {
 UDPPortCommandline =
 parsePortFromCommandline(strings0, int1, "-udpport");
 int1++;
 }
 else if (strings0[int1] == "-steamvac")) {
 SteamVACCommandline =
 parseBooleanFromCommandline(strings0, int1, "-steamvac");
 int1++;
 }
 else if (strings0[int1] == "-servername")) {
 if (int1 == strings0.length - 1) {
 DebugLog.log("expected argument after \"-servername\"");
 System.exit(0);
 } else if (strings0[int1 + 1].trim().empty()) {
 DebugLog.log("empty argument given to \"-servername\"");
 System.exit(0);
 } else {
 ServerName = strings0[int1 + 1].trim();
 int1++;
 }
 }
 else if (strings0[int1] == "-coop")) {
 ServerWorldDatabase.instance.doAdmin = false;
 }
 else {
 DebugLog.log("unknown option \"" + strings0[int1] + "\"");
 }
 }
 } else {
 for (String string2 :
 strings0[int1].replace("-disablelog=", "").split(",")) {
 if ("All" == string2) {
 for (DebugType debugType : DebugType.values()) {
 DebugLog.setLogEnabled(debugType, false);
 }
 }
 else {
 try {
 DebugLog.setLogEnabled(DebugType.valueOf(string2), false);
 } catch (IllegalArgumentException illegalArgumentException1) {
 }
 }
 }
 }
 }
 }

 DebugLog.log("server name is \"" + ServerName + "\"");
 std::string string3 = isWorldVersionUnsupported();
 if (string3 != nullptr) {
 DebugLog.log(string3);
 CoopSlave.status(string3);
 } else {
 SteamUtils.init();
 RakNetPeerInterface.init();
 ZombiePopulationManager.init();

 try {
 ZomboidFileSystem.instance.init();
 Languages.instance.init();
 Translator.loadFiles();
 } catch (Exception exception0) {
 DebugLog.General.printException(exception0, "Exception Thrown",
 LogSeverity.Error);
 DebugLog.General.println("Server Terminated.");
 }

 ServerOptions.instance.init();
 initClientCommandFilter();
 if (PortCommandline != -1) {
 ServerOptions.instance.DefaultPort.setValue(PortCommandline);
 }

 if (UDPPortCommandline != -1) {
 ServerOptions.instance.UDPPort.setValue(UDPPortCommandline);
 }

 if (SteamVACCommandline != nullptr) {
 ServerOptions.instance.SteamVAC.setValue(SteamVACCommandline);
 }

 DEFAULT_PORT = ServerOptions.instance.DefaultPort.getValue();
 UDPPort = ServerOptions.instance.UDPPort.getValue();
 if (CoopSlave.instance != nullptr) {
 ServerOptions.instance.ServerPlayerID.setValue("");
 }

 if (SteamUtils.isSteamModeEnabled()) {
 std::string string4 = ServerOptions.instance.PublicName.getValue();
 if (string4.empty() || string4.empty()) {
 ServerOptions.instance.PublicName.setValue("My PZ Server");
 }
 }

 std::string string5 = ServerOptions.instance.Map.getValue();
 if (string5 != nullptr && !string5.trim().empty()) {
 GameMap = string5.trim();
 if (GameMap.contains(";")) {
 String[] strings1 = GameMap.split(";");
 string5 = strings1[0];
 }

 Core.GameMap = string5.trim();
 }

 std::string string6 = ServerOptions.instance.Mods.getValue();
 if (string6 != nullptr) {
 String[] strings2 = string6.split(";");

 for (auto &string7 : strings2)
 if (!string7.trim().empty()) {
 ServerMods.add(string7.trim());
 }
 }
 }

 if (SteamUtils.isSteamModeEnabled()) {
 int int3 = ServerOptions.instance.SteamVAC.getValue() ? 3 : 2;
 if (!SteamGameServer.Init(IPCommandline, DEFAULT_PORT, UDPPort, int3,
 Core.getInstance().getSteamServerVersion())) {
 SteamUtils.shutdown();
 return;
 }

 SteamGameServer.SetProduct("zomboid");
 SteamGameServer.SetGameDescription("Project Zomboid");
 SteamGameServer.SetModDir("zomboid");
 SteamGameServer.SetDedicatedServer(true);
 SteamGameServer.SetMaxPlayerCount(
 ServerOptions.getInstance().getMaxPlayers());
 SteamGameServer.SetServerName(
 ServerOptions.instance.PublicName.getValue());
 SteamGameServer.SetMapName(ServerOptions.instance.Map.getValue());
 if (ServerOptions.instance.Public.getValue()) {
 SteamGameServer.SetGameTags(CoopSlave.instance != nullptr ? "hosted"
 : "");
 } else {
 SteamGameServer.SetGameTags(
 "hidden" + (CoopSlave.instance != nullptr ? ";hosted" : ""));
 }

 SteamGameServer.SetKeyValue(
 "description", ServerOptions.instance.PublicDescription.getValue());
 SteamGameServer.SetKeyValue("version", Core.getInstance().getVersion());
 SteamGameServer.SetKeyValue(
 "open", ServerOptions.instance.Open.getValue() ? "1" : "0");
 SteamGameServer.SetKeyValue(
 "public", ServerOptions.instance.Public.getValue() ? "1" : "0");
 std::string string8 = ServerOptions.instance.Mods.getValue();
 int int4 = 0;
 String[] strings3 = string8.split(";");

 for (auto &string9 : strings3)
 if (!StringUtils.isNullOrWhitespace(string9) {
 int4++;
 }
 }

 if (string8.length() > 128) {
 StringBuilder stringBuilder = new StringBuilder();
 String[] strings4 = string8.split(";");

 for (auto &string10 : strings4)
 if (stringBuilder.length() + 1 + string10.length() > 128) {
 break;
 }

 if (stringBuilder.length() > 0) {
 stringBuilder.append(';');
 }

 stringBuilder.append(string10);
 }

 string8 = stringBuilder.toString();
 }

 SteamGameServer.SetKeyValue("mods", string8);
 SteamGameServer.SetKeyValue("modCount", String.valueOf(int4);
 SteamGameServer.SetKeyValue("pvp", ServerOptions.instance.PVP.getValue()
 ? "1"
 : "0");
 if (bDebug) {
 }

 std::string string11 = ServerOptions.instance.WorkshopItems.getValue();
 if (string11 != nullptr) {
 String[] strings5 = string11.split(";");

 for (auto &string12 : strings5)
 string12 = string12.trim();
 if (!string12.empty() && SteamUtils.isValidSteamID(string12) {
 WorkshopItems.add(SteamUtils.convertStringToSteamID(string12);
 }
 }
}

SteamWorkshop.init();
SteamGameServer.LogOnAnonymous();
SteamGameServer.EnableHeartBeats(true);
DebugLog.log("Waiting for response from Steam servers");

while (true) {
 SteamUtils.runLoop();
 int int5 = SteamGameServer.GetSteamServersConnectState();
 if (int5 == SteamGameServer.STEAM_SERVERS_CONNECTED) {
 if (!GameServerWorkshopItems.Install(WorkshopItems) {
 return;
 }
 break;
 }

 if (int5 == SteamGameServer.STEAM_SERVERS_CONNECTFAILURE) {
 DebugLog.log("Failed to connect to Steam servers");
 SteamUtils.shutdown();
 return;
 }

 try {
 Thread.sleep(100L);
 } catch (InterruptedException interruptedException0) {
 }
}
}

ZipBackup.onStartup();
ZipBackup.onVersion();
int int6 = 0;

try {
 ServerWorldDatabase.instance.create();
} catch (ClassNotFoundException | SQLException sQLException) {
 sQLException.printStackTrace();
}

if (ServerOptions.instance.UPnP.getValue()) {
 DebugLog.log("Router detection/configuration starting.");
 DebugLog.log("If the server hangs here, set UPnP=false.");
 PortMapper.startup();
 if (PortMapper.discover()) {
 DebugLog.log("UPnP-enabled internet gateway found: " +
 PortMapper.getGatewayInfo());
 std::string string13 = PortMapper.getExternalAddress();
 DebugLog.log("External IP address: " + string13);
 DebugLog.log("trying to setup port forwarding rules...");
 int int7 = 86400;
 bool boolean0 = true;
 if (PortMapper.addMapping(DEFAULT_PORT, DEFAULT_PORT,
 "PZ Server default port", "UDP", int7,
 boolean0) {
 DebugLog.log(DebugType.Network,
 "Default port has been mapped successfully");
 } else {
 DebugLog.log(DebugType.Network, "Failed to map default port");
 }

 if (SteamUtils.isSteamModeEnabled()) {
 int int8 = ServerOptions.instance.UDPPort.getValue();
 if (PortMapper.addMapping(int8, int8, "PZ Server UDPPort", "UDP", int7,
 boolean0) {
 DebugLog.log(DebugType.Network,
 "AdditionUDPPort has been mapped successfully");
 } else {
 DebugLog.log(DebugType.Network, "Failed to map AdditionUDPPort");
 }
 }
 } else {
 DebugLog.log(DebugType.Network,
 "No UPnP-enabled Internet gateway found, you must configure "
 "port forwarding on your gateway manually in order to make "
 "your server accessible from the Internet.");
 }
}

Core.GameMode = "Multiplayer";
bDone = false;
DebugLog.log(DebugType.Network, "Initialising Server Systems...");
CoopSlave.status("UI_ServerStatus_Initialising");

try {
 doMinimumInit();
} catch (Exception exception1) {
 DebugLog.General.printException(exception1, "Exception Thrown",
 LogSeverity.Error);
 DebugLog.General.println("Server Terminated.");
}

LosUtil.init(100, 100);
ChatServer.getInstance().init();
DebugLog.log(DebugType.Network, "Loading world...");
CoopSlave.status("UI_ServerStatus_LoadingWorld");

try {
 ClimateManager.setInstance(std::make_unique<ClimateManager>());
 IsoWorld.instance.init();
} catch (Exception exception2) {
 DebugLog.General.printException(exception2, "Exception Thrown",
 LogSeverity.Error);
 DebugLog.General.println("Server Terminated.");
 CoopSlave.status("UI_ServerStatus_Terminated");
 return;
}

File file = ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");
if (!file.exists()) {
 ServerOptions.instance.changeOption(
 "ResetID", new Integer(Rand.Next(100000000).toString());
}

try {
 SpawnPoints.instance.initServer2();
} catch (Exception exception3) {
 exception3.printStackTrace();
}

LuaEventManager.triggerEvent("OnGameTimeLoaded");
SGlobalObjects.initSystems();
SoundManager.instance = std::make_unique<SoundManager>();
AmbientStreamManager.instance = std::make_unique<AmbientSoundManager>();
AmbientStreamManager.instance.init();
ServerMap.instance.LastSaved = System.currentTimeMillis();
VehicleManager.instance = std::make_unique<VehicleManager>();
ServerPlayersVehicles.instance.init();
DebugOptions.instance.init();
GameProfiler.init();

try {
 startServer();
} catch (ConnectException connectException) {
 connectException.printStackTrace();
 SteamUtils.shutdown();
 return;
}

if (SteamUtils.isSteamModeEnabled()) {
 DebugLog.log("##########\nServer Steam ID " + SteamGameServer.GetSteamID() +
 "\n##########");
}

UpdateLimit updateLimit = new UpdateLimit(100L);
PerformanceSettings.setLockFPS(10);
IngameState ingameState = new IngameState();
float float0 = 0.0F;
float[] floats = new float[20];

for (int int9 = 0; int9 < 20; int9++) {
 floats[int9] = PerformanceSettings.getLockFPS();
}

float float1 = PerformanceSettings.getLockFPS();
long long0 = System.currentTimeMillis();
long long1 = System.currentTimeMillis();
if (!SteamUtils.isSteamModeEnabled()) {
 PublicServerUtil.init();
 PublicServerUtil.insertOrUpdate();
}

ServerLOS.init();
NetworkAIParams.Init();
int int10 = ServerOptions.instance.RCONPort.getValue();
std::string string14 = ServerOptions.instance.RCONPassword.getValue();
if (int10 != 0 && string14 != nullptr && !string14.empty()) {
 std::string string15 = System.getProperty("rconlo");
 RCONServer.init(int10, string14, string15 != nullptr);
}

LuaManager.GlobalObject.refreshAnimSets(true);

while (!bDone) {
 try {
 long long2 = System.nanoTime();
 MPStatistics.countServerNetworkingFPS();
 MainLoopNetData2.clear();

 for (IZomboidPacket iZomboidPacket0 = MainLoopNetDataHighPriorityQ.poll();
 iZomboidPacket0 != nullptr;
 iZomboidPacket0 = MainLoopNetDataHighPriorityQ.poll()) {
 MainLoopNetData2.add(iZomboidPacket0);
 }

 MPStatistic.getInstance().setPacketsLength(MainLoopNetData2.size());

 for (int int11 = 0; int11 < MainLoopNetData2.size(); int11++) {
 IZomboidPacket iZomboidPacket1 = MainLoopNetData2.get(int11);
 if (iZomboidPacket1.isConnect()) {
 UdpConnection udpConnection0 =
 ((GameServer.DelayedConnection)iZomboidPacket1).connection;
 LoggerManager.getLogger("user").write(
 "added connection index=" + udpConnection0.index + " " +
 ((GameServer.DelayedConnection)iZomboidPacket1).hostString);
 udpEngine.connections.add(udpConnection0);
 } else if (iZomboidPacket1.isDisconnect()) {
 UdpConnection udpConnection1 =
 ((GameServer.DelayedConnection)iZomboidPacket1).connection;
 LoginQueue.disconnect(udpConnection1);
 LoggerManager.getLogger("user").write(
 udpConnection1.idStr + " \"" + udpConnection1.username +
 "\" removed connection index=" + udpConnection1.index);
 udpEngine.connections.remove(udpConnection1);
 disconnect(udpConnection1, "receive-disconnect");
 } else {
 mainLoopDealWithNetData((ZomboidNetData)iZomboidPacket1);
 }
 }

 MainLoopPlayerUpdate.clear();

 for (IZomboidPacket iZomboidPacket2 = MainLoopPlayerUpdateQ.poll();
 iZomboidPacket2 != nullptr;
 iZomboidPacket2 = MainLoopPlayerUpdateQ.poll()) {
 ZomboidNetData zomboidNetData0 = (ZomboidNetData)iZomboidPacket2;
 long long3 =
 zomboidNetData0.connection * 4L + zomboidNetData0.buffer.getShort(0);
 ZomboidNetData zomboidNetData1 =
 (ZomboidNetData)MainLoopPlayerUpdate.put(long3, zomboidNetData0);
 if (zomboidNetData1 != nullptr) {
 ZomboidNetDataPool.instance.discard(zomboidNetData1);
 }
 }

 MainLoopNetData2.clear();
 MainLoopNetData2.addAll(MainLoopPlayerUpdate.values());
 MainLoopPlayerUpdate.clear();
 MPStatistic.getInstance().setPacketsLength(MainLoopNetData2.size());

 for (int int12 = 0; int12 < MainLoopNetData2.size(); int12++) {
 IZomboidPacket iZomboidPacket3 = MainLoopNetData2.get(int12);
 GameServer.s_performance.mainLoopDealWithNetData.invokeAndMeasure(
 (ZomboidNetData)iZomboidPacket3, GameServer::mainLoopDealWithNetData);
 }

 MainLoopNetData2.clear();

 for (IZomboidPacket iZomboidPacket4 = MainLoopNetDataQ.poll();
 iZomboidPacket4 != nullptr;
 iZomboidPacket4 = MainLoopNetDataQ.poll()) {
 MainLoopNetData2.add(iZomboidPacket4);
 }

 for (int int13 = 0; int13 < MainLoopNetData2.size(); int13++) {
 if (int13 % 10 == 0 && (System.nanoTime() - long2) / 1000000L > 70L) {
 if (droppedPackets == 0) {
 DebugLog.log(
 "Server is too busy. Server will drop updates of vehicle's "
 "physics. Server is closed for new connections.");
 }

 droppedPackets += 2;
 countOfDroppedPackets =
 countOfDroppedPackets + (MainLoopNetData2.size() - int13);
 break;
 }

 IZomboidPacket iZomboidPacket5 = MainLoopNetData2.get(int13);
 GameServer.s_performance.mainLoopDealWithNetData.invokeAndMeasure(
 (ZomboidNetData)iZomboidPacket5, GameServer::mainLoopDealWithNetData);
 }

 MainLoopNetData2.clear();
 if (droppedPackets == 1) {
 DebugLog.log(
 "Server is working normal. Server will not drop updates of vehicle's "
 "physics. The server is open for new connections. Server dropped " +
 countOfDroppedPackets + " packets and " + countOfDroppedConnections +
 " connections.");
 countOfDroppedPackets = 0;
 countOfDroppedConnections = 0;
 }

 droppedPackets = Math.max(0, Math.min(1000, droppedPackets - 1);
 if (!updateLimit.Check()) {
 long long4 = PZMath.clamp(
 (5000000L - System.nanoTime() + long2) / 1000000L, 0L, 100L);
 if (long4 > 0L) {
 try {
 MPStatistic.getInstance().Main.StartSleep();
 Thread.sleep(long4);
 MPStatistic.getInstance().Main.EndSleep();
 } catch (InterruptedException interruptedException1) {
 interruptedException1.printStackTrace();
 }
 }
 } else {
 MPStatistic.getInstance().Main.Start();
 IsoCamera.frameState.frameCount++;
 GameServer.s_performance.frameStep.start();

 try {
 timeSinceKeepAlive =
 timeSinceKeepAlive + GameTime.getInstance().getMultiplier();
 MPStatistic.getInstance().ServerMapPreupdate.Start();
 ServerMap.instance.preupdate();
 MPStatistic.getInstance().ServerMapPreupdate.End();
 { std::lock_guard<std::mutex> __sync_lock__(consoleCommands_mutex);
 for (int int14 = 0; int14 < consoleCommands.size(); int14++) {
 std::string string16 = consoleCommands.get(int14);

 try {
 if (CoopSlave.instance.empty() ||
 !CoopSlave.instance.handleCommand(string16) {
 System.out.println(handleServerCommand(string16, nullptr);
 }
 } catch (Exception exception4) {
 exception4.printStackTrace();
 }
 }

 consoleCommands.clear();
 }

 if (removeZombiesConnection != nullptr) {
 NetworkZombieManager.removeZombies(removeZombiesConnection);
 removeZombiesConnection = nullptr;
 }

 GameServer.s_performance.RCONServerUpdate.invokeAndMeasure(
 RCONServer::update);

 try {
 MapCollisionData.instance.updateGameState();
 MPStatistic.getInstance().IngameStateUpdate.Start();
 ingameState.update();
 MPStatistic.getInstance().IngameStateUpdate.End();
 VehicleManager.instance.serverUpdate();
 } catch (Exception exception5) {
 exception5.printStackTrace();
 }

 int int15 = 0;
 int int16 = 0;

 for (int int17 = 0; int17 < Players.size(); int17++) {
 IsoPlayer player = Players.get(int17);
 if (player.isAlive()) {
 if (!IsoWorld.instance.CurrentCell.getObjectList().contains(
 player) {
 IsoWorld.instance.CurrentCell.getObjectList().add(player);
 }

 int16++;
 if (player.isAsleep()) {
 int15++;
 }
 }

 ServerMap.instance.characterIn(player);
 }

 setFastForward(ServerOptions.instance.SleepAllowed.getValue() &&
 int16 > 0 && int15 == int16);
 bool boolean1 = calcCountPlayersInRelevantPositionLimiter.Check();

 for (int int18 = 0; int18 < udpEngine.connections.size(); int18++) {
 UdpConnection udpConnection2 = udpEngine.connections.get(int18);
 if (boolean1) {
 udpConnection2.calcCountPlayersInRelevantPosition();
 }

 for (int int19 = 0; int19 < 4; int19++) {
 Vector3 vector = udpConnection2.connectArea[int19];
 if (vector != nullptr) {
 ServerMap.instance.characterIn((int)vector.x, (int)vector.y,
 (int)vector.z);
 }

 ClientServerMap.characterIn(udpConnection2, int19);
 }

 if (udpConnection2.playerDownloadServer != nullptr) {
 udpConnection2.playerDownloadServer.update();
 }
 }

 for (int int20 = 0;
 int20 < IsoWorld.instance.CurrentCell.getObjectList().size();
 int20++) {
 IsoMovingObject movingObject =
 IsoWorld.instance.CurrentCell.getObjectList().get(int20);
 if (movingObject instanceof
 IsoPlayer && !Players.contains(movingObject) {
 DebugLog.log(
 "Disconnected player in CurrentCell.getObjectList() removed");
 IsoWorld.instance.CurrentCell.getObjectList().remove(int20--);
 }
 }

 if (++int6 > 150) {
 for (int int21 = 0; int21 < udpEngine.connections.size(); int21++) {
 UdpConnection udpConnection3 = udpEngine.connections.get(int21);

 try {
 if (udpConnection3.username.empty() &&
 !udpConnection3.awaitingCoopApprove &&
 !LoginQueue.isInTheQueue(udpConnection3) &&
 udpConnection3.isConnectionAttemptTimeout()) {
 disconnect(udpConnection3, "connection-attempt-timeout");
 udpEngine.forceDisconnect(udpConnection3.getConnectedGUID(),
 "connection-attempt-timeout");
 }
 } catch (Exception exception6) {
 exception6.printStackTrace();
 }
 }

 int6 = 0;
 }

 worldObjectsServerSyncReq.serverSendRequests(udpEngine);
 MPStatistic.getInstance().ServerMapPostupdate.Start();
 ServerMap.instance.postupdate();
 MPStatistic.getInstance().ServerMapPostupdate.End();

 try {
 ServerGUI.update();
 } catch (Exception exception7) {
 exception7.printStackTrace();
 }

 long1 = long0;
 long0 = System.currentTimeMillis();
 long long5 = long0 - long1;
 float0 = 1000.0F / (float)long5;
 if (!Float.isNaN(float0) {
 float1 = (float)(float1 + Math.min((float0 - float1) * 0.05, 1.0);
 }

 GameTime.instance.FPSMultiplier = 60.0F / float1;
 launchCommandHandler();
 MPStatistic.getInstance().process(long5);
 if (!SteamUtils.isSteamModeEnabled()) {
 PublicServerUtil.update();
 PublicServerUtil.updatePlayerCountIfChanged();
 }

 for (int int22 = 0; int22 < udpEngine.connections.size(); int22++) {
 UdpConnection udpConnection4 = udpEngine.connections.get(int22);
 if (udpConnection4.checksumState ==
 UdpConnection.ChecksumState.Different &&
 udpConnection4.checksumTime + 8000L <
 System.currentTimeMillis()) {
 DebugLog.log("timed out connection because checksum was different");
 udpConnection4.checksumState = UdpConnection.ChecksumState.Init;
 udpConnection4.forceDisconnect("checksum-timeout");
 } else {
 udpConnection4.validator.update();
 if (!udpConnection4.chunkObjectState.empty()) {
 for (byte byte0 = 0;
 byte0 < udpConnection4.chunkObjectState.size(); byte0 += 2) {
 short short0 = udpConnection4.chunkObjectState.get(byte0);
 short short1 = udpConnection4.chunkObjectState.get(byte0 + 1);
 if (!udpConnection4.RelevantTo(short0 * 10 + 5, short1 * 10 + 5,
 udpConnection4.ChunkGridWidth *
 4 * 10) {
 udpConnection4.chunkObjectState.remove(byte0, 2);
 byte0 -= 2;
 }
 }
 }
 }
 }

 if (sendWorldMapPlayerPositionLimiter.Check()) {
 try {
 sendWorldMapPlayerPosition();
 } catch (Exception exception8) {
 bool boolean2 = true;
 }
 }

 if (CoopSlave.instance != nullptr) {
 CoopSlave.instance.update();
 if (CoopSlave.instance.masterLost()) {
 DebugLog.log("Coop master is not responding, terminating");
 ServerMap.instance.QueueQuit();
 }
 }

 LoginQueue.update();
 ZipBackup.onPeriod();
 SteamUtils.runLoop();
 GameWindow.fileSystem.updateAsyncTransactions();
 } catch (Exception exception9) {
 if (mainCycleExceptionLogCount-- > 0) {
 DebugLog.Multiplayer.printException(
 exception9, "Server processing error", LogSeverity.Error);
 }
 } finally {
 GameServer.s_performance.frameStep.end();
 }
 }
 } catch (Exception exception10) {
 if (mainCycleExceptionLogCount-- > 0) {
 DebugLog.Multiplayer.printException(exception10, "Server error",
 LogSeverity.Error);
 }
 }
}

CoopSlave.status("UI_ServerStatus_Terminated");
DebugLog.log(DebugType.Network, "Server exited");
ServerGUI.shutdown();
ServerPlayerDB.getInstance().close();
VehiclesDB2.instance.Reset();
SteamUtils.shutdown();
System.exit(0);
}
}

static void launchCommandHandler() {
 if (!launched) {
 launched = true;
 new Thread() {
 try {
 BufferedReader bufferedReader =
 new BufferedReader(new InputStreamReader(System.in);

 while (true) {
 std::string string = bufferedReader.readLine();
 if (string.empty()) {
 consoleCommands.add("process-status@eof");
 break;
 }

 if (!string.empty()) {
 System.out.println(
 "command entered via server console (System.in): \"" + string +
 "\"");
 { std::lock_guard<std::mutex> __sync_lock__(consoleCommands_mutex); consoleCommands.add(string); }
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }, "command handler").start();
 }
}

static std::string rcon(std::string_view string) {
 try {
 return handleServerCommand();
 } catch (Throwable throwable) {
 throwable.printStackTrace();
 return nullptr;
 }
}

static std::string handleServerCommand(std::string_view string0,
 UdpConnection udpConnection) {
 if (string0.empty()) {
 return nullptr;
 } else {
 std::string string1 = "admin";
 std::string string2 = "admin";
 if (udpConnection != nullptr) {
 string1 = udpConnection.username;
 string2 = PlayerType.toString(udpConnection.accessLevel);
 }

 if (udpConnection != nullptr && udpConnection.isCoopHost) {
 string2 = "admin";
 }

 Class clazz = CommandBase.findCommandCls(string0);
 if (clazz != nullptr) {
 Constructor constructor = clazz.getConstructors()[0];

 try {
 CommandBase commandBase = (CommandBase)constructor.newInstance(
 string1, string2, string0, udpConnection);
 return commandBase.Execute();
 } catch (InvocationTargetException invocationTargetException) {
 invocationTargetException.printStackTrace();
 return "A InvocationTargetException error occured";
 } catch (IllegalAccessException illegalAccessException) {
 illegalAccessException.printStackTrace();
 return "A IllegalAccessException error occured";
 } catch (InstantiationException instantiationException) {
 instantiationException.printStackTrace();
 return "A InstantiationException error occured";
 } catch (SQLException sQLException) {
 sQLException.printStackTrace();
 return "A SQL error occured";
 }
 } else {
 return "Unknown command " + string0;
 }
 }
}

static void sendTeleport(IsoPlayer player, float float0, float float1,
 float float2) {
 UdpConnection udpConnection = getConnectionFromPlayer(player);
 if (udpConnection.empty()) {
 DebugLog.log("No connection found for user " + player.getUsername());
 } else {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.Teleport.send(udpConnection);
 if (udpConnection.players[0] != nullptr &&
 udpConnection.players[0].getNetworkCharacterAI() != nullptr) {
 udpConnection.players[0].getNetworkCharacterAI().resetSpeedLimiter();
 }
 }
}

static void receiveTeleport(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 std::string string = GameWindow.ReadString(byteBuffer);
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 IsoPlayer player = getPlayerByRealUserName(string);
 if (player != nullptr) {
 UdpConnection udpConnection = getConnectionFromPlayer(player);
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)player.PlayerIndex);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.Teleport.send(udpConnection);
 if (player.getNetworkCharacterAI() != nullptr) {
 player.getNetworkCharacterAI().resetSpeedLimiter();
 }

 if (player.isAsleep()) {
 player.setAsleep(false);
 player.setAsleepTime(0.0F);
 sendWakeUpPlayer(player, nullptr);
 }
 }
 }
}

static void sendPlayerExtraInfo(IsoPlayer player, UdpConnection var1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ExtraInfo.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.OnlineID);
 byteBufferWriter.putUTF(player.accessLevel);
 byteBufferWriter.putByte((byte)(player.isGodMod() ? 1 : 0);
 byteBufferWriter.putByte((byte)(player.isGhostMode() ? 1 : 0);
 byteBufferWriter.putByte((byte)(player.isInvisible() ? 1 : 0);
 byteBufferWriter.putByte((byte)(player.isNoClip() ? 1 : 0);
 byteBufferWriter.putByte((byte)(player.isShowAdminTag() ? 1 : 0);
 PacketTypes.PacketType.ExtraInfo.send(udpConnection);
 }
}

static void receiveExtraInfo(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 short short0 = byteBuffer.getShort();
 bool boolean0 = byteBuffer.get() == 1;
 bool boolean1 = byteBuffer.get() == 1;
 bool boolean2 = byteBuffer.get() == 1;
 bool boolean3 = byteBuffer.get() == 1;
 bool boolean4 = byteBuffer.get() == 1;
 bool boolean5 = byteBuffer.get() == 1;
 IsoPlayer player = getPlayerFromConnection(udpConnection, short0);
 if (player != nullptr) {
 player.setGodMod(boolean0);
 player.setGhostMode(boolean1);
 player.setInvisible(boolean2);
 player.setNoClip(boolean3);
 player.setShowAdminTag(boolean4);
 player.setCanHearAll(boolean5);
 sendPlayerExtraInfo(player, udpConnection);
 }
}

static void receiveAddXp(ByteBuffer byteBuffer, UdpConnection udpConnection0,
 short var2) {
 AddXp addXp = new AddXp();
 addXp.parse(byteBuffer, udpConnection0);
 if (addXp.isConsistent() && addXp.validate(udpConnection0) {
 if (!canModifyPlayerStats(udpConnection0, addXp.target.getCharacter())) {
 PacketTypes.PacketType.AddXP.onUnauthorized(udpConnection0);
 } else {
 addXp.process();
 if (canModifyPlayerStats(udpConnection0, nullptr) {
 addXp.target.getCharacter().getXp().recalcSumm();
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.getConnectedGUID() ==
 PlayerToAddressMap.get(addXp.target.getCharacter())) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.AddXP.doPacket(byteBufferWriter);
 addXp.write(byteBufferWriter);
 PacketTypes.PacketType.AddXP.send(udpConnection1);
 }
 }
 }
 }
}

static bool canSeePlayerStats(UdpConnection udpConnection) {
 return udpConnection.accessLevel != 1;
}

static bool canModifyPlayerStats(UdpConnection udpConnection,
 IsoPlayer player) {
 return (udpConnection.accessLevel & 56) != 0 ||
 udpConnection.havePlayer(player);
}

static void receiveSyncXP(ByteBuffer byteBuffer, UdpConnection udpConnection0,
 short var2) {
 IsoPlayer player = IDToPlayerMap.get(byteBuffer.getShort());
 if (player != nullptr) {
 if (!canModifyPlayerStats(udpConnection0, player) {
 PacketTypes.PacketType.SyncXP.onUnauthorized(udpConnection0);
 } else {
 if (player != nullptr && !player.isDead()) {
 try {
 player.getXp().load(byteBuffer, 195);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncXP.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.getOnlineID());

 try {
 player.getXp().save(byteBufferWriter.bb);
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }

 PacketTypes.PacketType.SyncXP.send(udpConnection1);
 }
 }
 }
 }
 }
}

static void receiveChangePlayerStats(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 std::string string = GameWindow.ReadString(byteBuffer);
 player.setPlayerStats(byteBuffer, string);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 if (udpConnection0.getConnectedGUID() ==
 PlayerToAddressMap.get(player) {
 udpConnection0.allChatMuted = player.isAllChatMuted();
 udpConnection0.accessLevel =
 PlayerType.fromString(player.accessLevel);
 }

 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.ChangePlayerStats.doPacket(byteBufferWriter);
 player.createPlayerStats(byteBufferWriter, string);
 PacketTypes.PacketType.ChangePlayerStats.send(udpConnection0);
 }
 }
 }
}

static void doMinimumInit() {
 Rand.init();
 DebugFileWatcher.instance.init();
 std::vector arrayList = new ArrayList<>(ServerMods);
 ZomboidFileSystem.instance.loadMods(arrayList);
 LuaManager.init();
 PerkFactory.init();
 CustomPerks.instance.init();
 CustomPerks.instance.initLua();
 AssetManagers assetManagers = GameWindow.assetManagers;
 AiSceneAssetManager.instance.create(AiSceneAsset.ASSET_TYPE, assetManagers);
 AnimationAssetManager.instance.create(AnimationAsset.ASSET_TYPE,
 assetManagers);
 AnimNodeAssetManager.instance.create(AnimationAsset.ASSET_TYPE,
 assetManagers);
 ClothingItemAssetManager.instance.create(ClothingItem.ASSET_TYPE,
 assetManagers);
 MeshAssetManager.instance.create(ModelMesh.ASSET_TYPE, assetManagers);
 ModelAssetManager.instance.create(Model.ASSET_TYPE, assetManagers);
 TextureIDAssetManager.instance.create(TextureID.ASSET_TYPE, assetManagers);
 TextureAssetManager.instance.create(Texture.ASSET_TYPE, assetManagers);
 if (GUICommandline && !bSoftReset) {
 ServerGUI.init();
 }

 CustomSandboxOptions.instance.init();
 CustomSandboxOptions.instance.initInstance(SandboxOptions.instance);
 ScriptManager.instance.Load();
 ClothingDecals.init();
 BeardStyles.init();
 HairStyles.init();
 OutfitManager.init();
 if (!bSoftReset) {
 JAssImpImporter.Init();
 ModelManager.NoOpenGL = !ServerGUI.isCreated();
 ModelManager.instance.create();
 System.out.println("LOADING ASSETS: START");

 while (GameWindow.fileSystem.hasWork()) {
 GameWindow.fileSystem.updateAsyncTransactions();
 }

 System.out.println("LOADING ASSETS: FINISH");
 }

 try {
 LuaManager.initChecksum();
 LuaManager.LoadDirBase("shared");
 LuaManager.LoadDirBase("client", true);
 LuaManager.LoadDirBase("server");
 LuaManager.finishChecksum();
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 RecipeManager.LoadedAfterLua();
 File file =
 new File(ZomboidFileSystem.instance.getCacheDir() + File.separator +
 "Server" + File.separator + ServerName + "_SandboxVars.lua");
 if (file.exists()) {
 if (!SandboxOptions.instance.loadServerLuaFile(ServerName) {
 System.out.println("Exiting due to errors loading " +
 file.getCanonicalPath());
 System.exit(1);
 }

 SandboxOptions.instance.handleOldServerZombiesFile();
 SandboxOptions.instance.saveServerLuaFile(ServerName);
 SandboxOptions.instance.toLua();
 } else {
 SandboxOptions.instance.handleOldServerZombiesFile();
 SandboxOptions.instance.saveServerLuaFile(ServerName);
 SandboxOptions.instance.toLua();
 }

 LuaEventManager.triggerEvent("OnGameBoot");
 ZomboidGlobals.Load();
 SpawnPoints.instance.initServer1();
 ServerGUI.init2();
}

static void startServer() {
 std::string string0 = ServerOptions.instance.Password.getValue();
 if (CoopSlave.instance != nullptr && SteamUtils.isSteamModeEnabled()) {
 string0 = "";
 }

 udpEngine =
 new UdpEngine(DEFAULT_PORT, UDPPort,
 ServerOptions.getInstance().getMaxPlayers(), string0, true);
 DebugLog.log(DebugType.Network, "*** SERVER STARTED ****");
 DebugLog.log(DebugType.Network,
 "*** Steam is " + (SteamUtils.isSteamModeEnabled()
 ? "enabled"
 : "not enabled"));
 if (SteamUtils.isSteamModeEnabled()) {
 DebugLog.log(DebugType.Network,
 "Server is listening on port " + DEFAULT_PORT +
 " (for Steam connection) and port " + UDPPort +
 " (for UDPRakNet connection)");
 DebugLog.log(DebugType.Network, "Clients should use " + DEFAULT_PORT +
 " port for connections");
 } else {
 DebugLog.log(DebugType.Network,
 "server is listening on port " + DEFAULT_PORT);
 }

 ResetID = ServerOptions.instance.ResetID.getValue();
 if (CoopSlave.instance != nullptr) {
 if (SteamUtils.isSteamModeEnabled()) {
 RakNetPeerInterface rakNetPeerInterface = udpEngine.getPeer();
 CoopSlave.instance.sendMessage("server-address", nullptr,
 rakNetPeerInterface.GetServerIP() + ":" +
 DEFAULT_PORT);
 long long0 = SteamGameServer.GetSteamID();
 CoopSlave.instance.sendMessage("steam-id", nullptr,
 SteamUtils.convertSteamIDToString(long0);
 } else {
 std::string string1 = "127.0.0.1";
 CoopSlave.instance.sendMessage("server-address", nullptr,
 string1 + ":" + DEFAULT_PORT);
 }
 }

 LuaEventManager.triggerEvent("OnServerStarted");
 if (SteamUtils.isSteamModeEnabled()) {
 CoopSlave.status("UI_ServerStatus_Started");
 } else {
 CoopSlave.status("UI_ServerStatus_Started");
 }

 std::string string2 = ServerOptions.instance.DiscordChannel.getValue();
 std::string string3 = ServerOptions.instance.DiscordToken.getValue();
 bool boolean0 = ServerOptions.instance.DiscordEnable.getValue();
 std::string string4 = ServerOptions.instance.DiscordChannelID.getValue();
 discordBot.connect(boolean0, string3, string2, string4);
}

static void mainLoopDealWithNetData(ZomboidNetData zomboidNetData) {
 if (SystemDisabler.getDoMainLoopDealWithNetData()) {
 ByteBuffer byteBuffer = zomboidNetData.buffer;
 UdpConnection udpConnection =
 udpEngine.getActiveConnection(zomboidNetData.connection);
 if (zomboidNetData.type.empty()) {
 ZomboidNetDataPool.instance.discard(zomboidNetData);
 } else {
 zomboidNetData.type.serverPacketCount++;
 MPStatistic.getInstance().addIncomePacket(zomboidNetData.type,
 byteBuffer.limit());

 try {
 if (udpConnection.empty()) {
 DebugLog.log(DebugType.Network,
 "Received packet type=" + zomboidNetData.type.name() +
 " connection is nullptr.");
 return;
 }

 if (udpConnection.username.empty()) {
 switch (zomboidNetData.type) {
 case Login:
 case Ping:
 case ScoreboardUpdate:
 break;
 default:
 DebugLog.log("Received packet type=" + zomboidNetData.type.name() +
 " before Login, disconnecting " +
 udpConnection.getInetSocketAddress().getHostString());
 udpConnection.forceDisconnect("unacceptable-packet");
 ZomboidNetDataPool.instance.discard(zomboidNetData);
 return;
 }
 }

 zomboidNetData.type.onServerPacket(byteBuffer, udpConnection);
 } catch (Exception exception) {
 if (udpConnection.empty()) {
 DebugLog.log(DebugType.Network,
 "Error with packet of type: " + zomboidNetData.type +
 " connection is nullptr.");
 } else {
 DebugLog.General.error(
 "Error with packet of type: " + zomboidNetData.type + " for " +
 udpConnection.username);
 }

 exception.printStackTrace();
 }

 ZomboidNetDataPool.instance.discard(zomboidNetData);
 }
 }
}

static void receiveInvMngRemoveItem(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection0.getConnectedGUID() == PlayerToAddressMap.get(player) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.InvMngRemoveItem.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 PacketTypes.PacketType.InvMngRemoveItem.send(udpConnection0);
 break;
 }
 }
 }
}

static void receiveInvMngGetItem(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection0.getConnectedGUID() == PlayerToAddressMap.get(player) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.InvMngGetItem.doPacket(byteBufferWriter);
 byteBuffer.rewind();
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.InvMngGetItem.send(udpConnection0);
 break;
 }
 }
 }
}

static void receiveInvMngReqItem(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = 0;
 std::string string = nullptr;
 if (byteBuffer.get() == 1) {
 string = GameWindow.ReadString(byteBuffer);
 } else {
 int0 = byteBuffer.getInt();
 }

 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short1);
 if (player != nullptr) {
 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection0.getConnectedGUID() == PlayerToAddressMap.get(player) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.InvMngReqItem.doPacket(byteBufferWriter);
 if (string != nullptr) {
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putUTF(string);
 } else {
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putInt(int0);
 }

 byteBufferWriter.putShort(short0);
 PacketTypes.PacketType.InvMngReqItem.send(udpConnection0);
 break;
 }
 }
 }
}

static void receiveRequestZipList(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 if (!udpConnection.wasInLoadingQueue) {
 kick(udpConnection, "UI_Policy_Kick",
 "The server received an invalid request");
 }

 if (udpConnection.playerDownloadServer != nullptr) {
 udpConnection.playerDownloadServer.receiveRequestArray(byteBuffer);
 }
}

static void receiveRequestLargeAreaZip(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 if (!udpConnection.wasInLoadingQueue) {
 kick(udpConnection, "UI_Policy_Kick",
 "The server received an invalid request");
 }

 if (udpConnection.playerDownloadServer != nullptr) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 udpConnection.connectArea[0] = new Vector3(int0, int1, int2);
 udpConnection.ChunkGridWidth = int2;
 ZombiePopulationManager.instance.updateLoadedAreas();
 }
}

static void receiveNotRequiredInZip(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 if (udpConnection.playerDownloadServer != nullptr) {
 udpConnection.playerDownloadServer.receiveCancelRequest(byteBuffer);
 }
}

static void receiveLogin(ByteBuffer byteBuffer, UdpConnection udpConnection0,
 short var2) {
 ConnectionManager.log("receive-packet", "login", udpConnection0);
 std::string string0 = GameWindow.ReadString(byteBuffer).trim();
 std::string string1 = GameWindow.ReadString(byteBuffer).trim();
 std::string string2 = GameWindow.ReadString(byteBuffer).trim();
 if (!string2 == Core.getInstance().getVersion())) {
 ByteBufferWriter byteBufferWriter0 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter0);
 LoggerManager.getLogger("user").write(
 "access denied: user \"" + string0 + "\" client version (" + string2 +
 ") does not match server version (" +
 Core.getInstance().getVersion() + ")");
 byteBufferWriter0.putUTF("ClientVersionMismatch##" + string2 + "##" +
 Core.getInstance().getVersion());
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "version-mismatch",
 udpConnection0);
 udpConnection0.forceDisconnect("access-denied-client-version");
 }

 udpConnection0.wasInLoadingQueue = false;
 udpConnection0.ip = udpConnection0.getInetSocketAddress().getHostString();
 udpConnection0.validator.reset();
 udpConnection0.idStr = udpConnection0.ip;
 if (SteamUtils.isSteamModeEnabled()) {
 udpConnection0.steamID =
 udpEngine.getClientSteamID(udpConnection0.getConnectedGUID());
 if (udpConnection0.steamID == -1L) {
 ByteBufferWriter byteBufferWriter1 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter1);
 LoggerManager.getLogger("user").write(
 "access denied: The client \"" + string0 +
 "\" did not complete the connection and authorization procedure in "
 "zombienet");
 byteBufferWriter1.putUTF("ClientIsNofFullyConnectedInZombienet");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "znet-error", udpConnection0);
 udpConnection0.forceDisconnect("access-denied-zombienet-connect");
 }

 udpConnection0.ownerID =
 udpEngine.getClientOwnerSteamID(udpConnection0.getConnectedGUID());
 udpConnection0.idStr =
 SteamUtils.convertSteamIDToString(udpConnection0.steamID);
 if (udpConnection0.steamID != udpConnection0.ownerID) {
 udpConnection0.idStr =
 udpConnection0.idStr + "(owner=" +
 SteamUtils.convertSteamIDToString(udpConnection0.ownerID) + ")";
 }
 }

 udpConnection0.password = string1;
 LoggerManager.getLogger("user").write(udpConnection0.idStr + " \"" + string0 +
 "\" attempting to join");
 if (CoopSlave.instance != nullptr && SteamUtils.isSteamModeEnabled()) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1 != udpConnection0 &&
 udpConnection1.steamID == udpConnection0.steamID) {
 LoggerManager.getLogger("user").write("access denied: user \"" +
 string0 + "\" already connected");
 ByteBufferWriter byteBufferWriter2 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter2);
 byteBufferWriter2.putUTF("AlreadyConnected");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "already-connected-steamid",
 udpConnection0);
 udpConnection0.forceDisconnect("access-denied-already-connected-cs");
 return;
 }
 }

 udpConnection0.username = string0;
 udpConnection0.usernames[0] = string0;
 udpConnection0.isCoopHost = udpEngine.connections.size() == 1;
 DebugLog.Multiplayer.debugln(udpConnection0.idStr +
 " isCoopHost=" + udpConnection0.isCoopHost);
 udpConnection0.accessLevel = 1;
 if (!ServerOptions.instance.DoLuaChecksum.getValue()) {
 udpConnection0.checksumState = UdpConnection.ChecksumState.Done;
 }

 if (getPlayerCount() >= ServerOptions.getInstance().getMaxPlayers()) {
 ByteBufferWriter byteBufferWriter3 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter3);
 byteBufferWriter3.putUTF("ServerFull");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "server-full", udpConnection0);
 udpConnection0.forceDisconnect("access-denied-server-full-cs");
 } else {
 if (isServerDropPackets() &&
 ServerOptions.instance.DenyLoginOnOverloadedServer.getValue()) {
 ByteBufferWriter byteBufferWriter4 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter4);
 LoggerManager.getLogger("user").write(
 "access denied: user \"" + string0 + "\" Server is too busy");
 byteBufferWriter4.putUTF("Server is too busy.");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "server-busy", udpConnection0);
 udpConnection0.forceDisconnect("access-denied-server-busy-cs");
 countOfDroppedConnections++;
 }

 LoggerManager.getLogger("user").write(udpConnection0.idStr + " \"" +
 string0 + "\" allowed to join");
 ServerWorldDatabase.LogonResult logonResult0 =
 ServerWorldDatabase.instance.std::make_unique<LogonResult>();
 logonResult0.accessLevel =
 PlayerType.toString(udpConnection0.accessLevel);
 receiveClientConnect(udpConnection0, logonResult0);
 }
 } else {
 ServerWorldDatabase.LogonResult logonResult1 =
 ServerWorldDatabase.instance.authClient(
 string0, string1, udpConnection0.ip, udpConnection0.steamID);
 if (logonResult1.bAuthorized) {
 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection2 = udpEngine.connections.get(int1);

 for (int int2 = 0; int2 < 4; int2++) {
 if (string0 == udpConnection2.usernames[int2])) {
 LoggerManager.getLogger("user").write(
 "access denied: user \"" + string0 + "\" already connected");
 ByteBufferWriter byteBufferWriter5 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter5);
 byteBufferWriter5.putUTF("AlreadyConnected");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied",
 "already-connected-username",
 udpConnection0);
 udpConnection0.forceDisconnect(
 "access-denied-already-connected-username");
 return;
 }
 }
 }

 udpConnection0.username = string0;
 udpConnection0.usernames[0] = string0;
 transactionIDMap.put(string0, logonResult1.transactionID);
 if (CoopSlave.instance != nullptr) {
 udpConnection0.isCoopHost = udpEngine.connections.size() == 1;
 DebugLog.log(udpConnection0.idStr +
 " isCoopHost=" + udpConnection0.isCoopHost);
 }

 udpConnection0.accessLevel =
 PlayerType.fromString(logonResult1.accessLevel);
 udpConnection0.preferredInQueue = logonResult1.priority;
 if (!ServerOptions.instance.DoLuaChecksum.getValue() ||
 logonResult1.accessLevel == "admin")) {
 udpConnection0.checksumState = UdpConnection.ChecksumState.Done;
 }

 if (!logonResult1.accessLevel == "") && getPlayerCount() >= ServerOptions.getInstance().getMaxPlayers()) {
 ByteBufferWriter byteBufferWriter6 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter6);
 byteBufferWriter6.putUTF("ServerFull");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "server-full-no-admin",
 udpConnection0);
 udpConnection0.forceDisconnect("access-denied-server-full");
 return;
 }

 if (!ServerWorldDatabase.instance.containsUser(string0) &&
 ServerWorldDatabase.instance.containsCaseinsensitiveUser(string0) {
 ByteBufferWriter byteBufferWriter7 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter7);
 byteBufferWriter7.putUTF("InvalidUsername");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "invalid-username",
 udpConnection0);
 udpConnection0.forceDisconnect("access-denied-invalid-username");
 return;
 }

 int int3 = udpConnection0.getAveragePing();
 DebugLog.Multiplayer.debugln("User %s ping %d ms",
 udpConnection0.username, int3);
 if (MPStatistics.doKickWhileLoading(udpConnection0, int3) {
 ByteBufferWriter byteBufferWriter8 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter8);
 LoggerManager.getLogger("user").write("access denied: user \"" +
 string0 + "\" ping is too high");
 byteBufferWriter8.putUTF("Ping");
 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "ping-limit", udpConnection0);
 udpConnection0.forceDisconnect("access-denied-ping-limit");
 return;
 }

 if (logonResult1.newUser) {
 try {
 ServerWorldDatabase.instance.addUser(string0, string1);
 LoggerManager.getLogger("user").write(udpConnection0.idStr + " \"" +
 string0 + "\" was added");
 } catch (SQLException sQLException) {
 DebugLog.Multiplayer.printException(
 sQLException, "ServerWorldDatabase.addUser error",
 LogSeverity.Error);
 }
 }

 LoggerManager.getLogger("user").write(udpConnection0.idStr + " \"" +
 string0 + "\" allowed to join");

 try {
 if (ServerOptions.instance.AutoCreateUserInWhiteList.getValue() &&
 !ServerWorldDatabase.instance.containsUser(string0) {
 ServerWorldDatabase.instance.addUser(string0, string1);
 } else {
 ServerWorldDatabase.instance.setPassword(string0, string1);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 ServerWorldDatabase.instance.updateLastConnectionDate(string0, string1);
 if (SteamUtils.isSteamModeEnabled()) {
 std::string string3 =
 SteamUtils.convertSteamIDToString(udpConnection0.steamID);
 ServerWorldDatabase.instance.setUserSteamID(string0, string3);
 }

 receiveClientConnect(udpConnection0, logonResult1);
 } else {
 ByteBufferWriter byteBufferWriter9 = udpConnection0.startPacket();
 PacketTypes.PacketType.AccessDenied.doPacket(byteBufferWriter9);
 if (logonResult1.banned) {
 LoggerManager.getLogger("user").write("access denied: user \"" +
 string0 + "\" is banned");
 if (logonResult1.bannedReason != nullptr &&
 !logonResult1.bannedReason.empty()) {
 byteBufferWriter9.putUTF("BannedReason##" +
 logonResult1.bannedReason);
 } else {
 byteBufferWriter9.putUTF("Banned");
 }
 } else if (!logonResult1.bAuthorized) {
 LoggerManager.getLogger("user").write("access denied: user \"" +
 string0 + "\" reason \"" +
 logonResult1.dcReason + "\"");
 byteBufferWriter9.putUTF(logonResult1.dcReason != nullptr
 ? logonResult1.dcReason
 : "AccessDenied");
 }

 PacketTypes.PacketType.AccessDenied.send(udpConnection0);
 ConnectionManager.log("access-denied", "unauthorized", udpConnection0);
 udpConnection0.forceDisconnect("access-denied-unauthorized");
 }
 }
}

static void receiveSendInventory(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 short short0 = byteBuffer.getShort();
 long long0 = IDToAddressMap.get(short0);
 if (long0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SendInventory.doPacket(byteBufferWriter);
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.SendInventory.send(udpConnection);
 break;
 }
 }
 }
}

static void receivePlayerStartPMChat(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 ChatServer.getInstance().processPlayerStartWhisperChatPacket(byteBuffer);
}

static void receiveRequestInventory(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 long long0 = IDToAddressMap.get(short1);
 if (long0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RequestInventory.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 PacketTypes.PacketType.RequestInventory.send(udpConnection);
 break;
 }
 }
 }
}

static void receiveStatistic(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 try {
 udpConnection.statistic.parse(byteBuffer);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
}

static void receiveStatisticRequest(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 if (udpConnection.accessLevel != 32 && !Core.bDebug) {
 DebugLog.General.error("User " + udpConnection.username +
 " has no rights to access statistics.");
 } else {
 try {
 udpConnection.statistic.enable = byteBuffer.get();
 sendStatistic(udpConnection);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

static void receiveZombieSimulation(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 NetworkZombiePacker.getInstance().receivePacket(byteBuffer, udpConnection);
}

static void sendShortStatistic() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.statistic.enable == 3) {
 sendShortStatistic(udpConnection);
 }
 }
}

static void sendShortStatistic(UdpConnection udpConnection) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StatisticRequest.doPacket(byteBufferWriter);
 MPStatistic.getInstance().write(byteBufferWriter);
 PacketTypes.PacketType.StatisticRequest.send(udpConnection);
 } catch (Exception exception) {
 exception.printStackTrace();
 udpConnection.cancelPacket();
 }
}

static void sendStatistic() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.statistic.enable == 1) {
 sendStatistic(udpConnection);
 }
 }
}

static void sendStatistic(UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StatisticRequest.doPacket(byteBufferWriter);

 try {
 MPStatistic.getInstance().getStatisticTable(byteBufferWriter.bb);
 PacketTypes.PacketType.StatisticRequest.send(udpConnection);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 udpConnection.cancelPacket();
 }
}

static void getStatisticFromClients() {
 try {
 for (UdpConnection udpConnection : udpEngine.connections) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Statistic.doPacket(byteBufferWriter);
 byteBufferWriter.putLong(System.currentTimeMillis());
 PacketTypes.PacketType.Statistic.send(udpConnection);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
}

static void updateZombieControl(IsoZombie zombie0, short short0, int int0) {
 try {
 if (zombie0.authOwner.empty()) {
 return;
 }

 ByteBufferWriter byteBufferWriter = zombie0.authOwner.startPacket();
 PacketTypes.PacketType.ZombieControl.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(zombie0.OnlineID);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 PacketTypes.PacketType.ZombieControl.send(zombie0.authOwner);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
}

static void receivePlayerUpdate(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short short0) {
 if (udpConnection0.checksumState != UdpConnection.ChecksumState.Done) {
 kick(udpConnection0, "UI_Policy_Kick", nullptr);
 udpConnection0.forceDisconnect("kick-checksum");
 } else {
 PlayerPacket playerPacket = PlayerPacket.l_receive.playerPacket;
 playerPacket.parse(byteBuffer, udpConnection0);
 IsoPlayer player = getPlayerFromConnection(udpConnection0, playerPacket.id);

 try {
 if (player.empty()) {
 DebugLog.General.error("receivePlayerUpdate: Server received position "
 "for unknown player (id:" +
 playerPacket.id +
 "). Server will ignore this data.");
 } else {
 if (udpConnection0.accessLevel == 1 &&
 player.networkAI.doCheckAccessLevel() &&
 (playerPacket.booleanVariables &
 (!SystemDisabler.getAllowDebugConnections() &&
 !SystemDisabler.getOverrideServerConnectDebugCheck()
 ? '\uf000'
 : '\uc000')) != 0 &&
 ServerOptions.instance.AntiCheatProtectionType12.getValue() &&
 PacketValidator.checkUser(udpConnection0) {
 PacketValidator.doKickUser(udpConnection0,
 playerPacket.getClass().getSimpleName(),
 "Type12", nullptr);
 }

 if (!player.networkAI.checkPosition(
 udpConnection0, player, PZMath.fastfloor(playerPacket.realx),
 PZMath.fastfloor(playerPacket.realy)) {
 return;
 }

 if (!player.networkAI.isSetVehicleHit()) {
 player.networkAI.parse(playerPacket);
 }

 player.bleedingLevel = playerPacket.bleedingLevel;
 if (player.networkAI.distance.getLength() >
 IsoChunkMap.ChunkWidthInTiles) {
 MPStatistic.getInstance().teleport();
 }

 udpConnection0.ReleventPos[player.PlayerIndex].x = playerPacket.realx;
 udpConnection0.ReleventPos[player.PlayerIndex].y = playerPacket.realy;
 udpConnection0.ReleventPos[player.PlayerIndex].z = playerPacket.realz;
 playerPacket.id = player.getOnlineID();
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (ServerOptions.instance.KickFastPlayers.getValue()) {
 Vector2 vector = playerToCoordsMap.get(Integer.valueOf(playerPacket.id);
 if (vector.empty()) {
 vector = std::make_unique<Vector2>();
 vector.x = playerPacket.x;
 vector.y = playerPacket.y;
 playerToCoordsMap.put(playerPacket.id, vector);
 } else {
 if (!player.accessLevel == "")
 && !player.isGhostMode()
 && (Math.abs(playerPacket.x - vector.x) > 4.0F || Math.abs(playerPacket.y - vector.y) > 4.0F) {
 if (playerMovedToFastMap.get(playerPacket.id) ==
 nullptr) {
 playerMovedToFastMap.put(playerPacket.id, 1);
 } else {
 playerMovedToFastMap.put(
 playerPacket.id,
 playerMovedToFastMap.get(
 Integer.valueOf(playerPacket.id) +
 1);
 }

 LoggerManager.getLogger("admin").write(
 player.getDisplayName() + " go too fast (" +
 playerMovedToFastMap.get(
 Integer.valueOf(playerPacket.id) +
 " times)");
 if (playerMovedToFastMap.get(playerPacket.id) == 10) {
 LoggerManager.getLogger("admin").write(
 player.getDisplayName() +
 " kicked for going too fast");
 kick(udpConnection0, "UI_Policy_Kick", nullptr);
 udpConnection0.forceDisconnect("kick-fast-player");
 return;
 }
 }

 vector.x = playerPacket.x;
 vector.y = playerPacket.y;
 }
 }

 if (player != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection1.isFullyConnected() &&
 (player.checkCanSeeClient(udpConnection1) &&
 udpConnection1.RelevantTo(playerPacket.x, playerPacket.y) ||
 short0 == PacketTypes.PacketType.PlayerUpdateReliable.getId() &&
 (udpConnection1.accessLevel > udpConnection0.accessLevel ||
 udpConnection0.accessLevel == 32)) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.packetTypes.get(short0).doPacket(byteBufferWriter);
 byteBuffer.position(0);
 byteBuffer.position(2);
 byteBufferWriter.bb.putShort(player.getOnlineID());
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.packetTypes.get(short0).send(udpConnection1);
 }
 }
 }
 }
}

static void receivePacketCounts(ByteBuffer var0, UdpConnection udpConnection,
 short var2) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.PacketCounts.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(PacketTypes.packetTypes.size());

 for (PacketTypes.PacketType packetType : PacketTypes.packetTypes.values()) {
 byteBufferWriter.putShort(packetType.getId());
 byteBufferWriter.putLong(packetType.serverPacketCount);
 }

 PacketTypes.PacketType.PacketCounts.send(udpConnection);
}

static void receiveSandboxOptions(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 try {
 SandboxOptions.instance.load(byteBuffer);
 SandboxOptions.instance.applySettings();
 SandboxOptions.instance.toLua();
 SandboxOptions.instance.saveServerLuaFile(ServerName);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SandboxOptions.doPacket(byteBufferWriter);
 byteBuffer.rewind();
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.SandboxOptions.send(udpConnection);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
}

static void receiveChunkObjectState(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 IsoChunk chunk = ServerMap.instance.getChunk(short0, short1);
 if (chunk.empty()) {
 udpConnection.chunkObjectState.add(short0);
 udpConnection.chunkObjectState.add(short1);
 } else {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ChunkObjectState.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putShort(short1);

 try {
 if (chunk.saveObjectState(byteBufferWriter.bb) {
 PacketTypes.PacketType.ChunkObjectState.send(udpConnection);
 } else {
 udpConnection.cancelPacket();
 }
 } catch (Throwable throwable) {
 throwable.printStackTrace();
 udpConnection.cancelPacket();
 return;
 }
 }
}

static void receiveReadAnnotedMap(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 std::string string = GameWindow.ReadString(byteBuffer);
 StashSystem.prepareBuildingStash(string);
}

static void receiveTradingUIRemoveItem(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 long long0 = IDToAddressMap.get(short1);
 if (long0 != nullptr) {
 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection = udpEngine.connections.get(int1);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.TradingUIRemoveItem.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 PacketTypes.PacketType.TradingUIRemoveItem.send(udpConnection);
 break;
 }
 }
 }
}

static void receiveTradingUIUpdateState(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 long long0 = IDToAddressMap.get(short1);
 if (long0 != nullptr) {
 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection = udpEngine.connections.get(int1);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.TradingUIUpdateState.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 PacketTypes.PacketType.TradingUIUpdateState.send(udpConnection);
 break;
 }
 }
 }
}

static void receiveTradingUIAddItem(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 InventoryItem item = nullptr;

 try {
 item = InventoryItem.loadItem(byteBuffer, 195);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (item != nullptr) {
 long long0 = IDToAddressMap.get(short1);
 if (long0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.TradingUIAddItem.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);

 try {
 item.saveWithSize(byteBufferWriter.bb, false);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 PacketTypes.PacketType.TradingUIAddItem.send(udpConnection);
 break;
 }
 }
 }
 }
}

static void receiveRequestTrading(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 uint8_t byte0 = byteBuffer.get();
 long long0 = IDToAddressMap.get(short0);
 if (byte0 == 0) {
 long0 = IDToAddressMap.get(short1);
 }

 if (long0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RequestTrading.doPacket(byteBufferWriter);
 if (byte0 == 0) {
 byteBufferWriter.putShort(short0);
 } else {
 byteBufferWriter.putShort(short1);
 }

 byteBufferWriter.putByte(byte0);
 PacketTypes.PacketType.RequestTrading.send(udpConnection);
 break;
 }
 }
 }
}

static void receiveSyncFaction(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBuffer.getInt();
 Faction faction = Faction.getFaction(string0);
 bool boolean0 = false;
 if (faction.empty()) {
 faction = new Faction(string0, string1);
 boolean0 = true;
 Faction.getFactions().add(faction);
 }

 faction.getPlayers().clear();
 if (byteBuffer.get() == 1) {
 faction.setTag(GameWindow.ReadString(byteBuffer);
 faction.setTagColor(new ColorInfo(byteBuffer.getFloat(),
 byteBuffer.getFloat(),
 byteBuffer.getFloat(), 1.0F);
 }

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string2 = GameWindow.ReadString(byteBuffer);
 faction.getPlayers().add(string2);
 }

 if (!faction.getOwner() == string1) {
 faction.setOwner(string1);
 }

 bool boolean1 = byteBuffer.get() == 1;
 if (ChatServer.isInited()) {
 if (boolean0) {
 ChatServer.getInstance().createFactionChat(string0);
 }

 if (boolean1) {
 ChatServer.getInstance().removeFactionChat(string0);
 } else {
 ChatServer.getInstance().syncFactionChatMembers(string0, string1,
 faction.getPlayers());
 }
 }

 if (boolean1) {
 Faction.getFactions().remove(faction);
 DebugLog.log("faction: removed " + string0 +
 " owner=" + faction.getOwner());
 }

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int2);
 if (udpConnection1.empty() || udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncFaction.doPacket(byteBufferWriter);
 faction.writeToBuffer(byteBufferWriter, boolean1);
 PacketTypes.PacketType.SyncFaction.send(udpConnection0);
 }
 }
}

static void receiveSyncNonPvpZone(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 SyncNonPvpZonePacket syncNonPvpZonePacket = new SyncNonPvpZonePacket();
 syncNonPvpZonePacket.parse(byteBuffer, udpConnection);
 if (syncNonPvpZonePacket.isConsistent()) {
 sendNonPvpZone(syncNonPvpZonePacket.zone, syncNonPvpZonePacket.doRemove,
 udpConnection);
 syncNonPvpZonePacket.process();
 DebugLog.Multiplayer.debugln("ReceiveSyncNonPvpZone: %s",
 syncNonPvpZonePacket.getDescription());
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(
 exception, "ReceiveSyncNonPvpZone: failed", LogSeverity.Error);
 }
}

static void sendNonPvpZone(NonPvpZone nonPvpZone, bool boolean0,
 UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncNonPvpZone.doPacket(byteBufferWriter);
 nonPvpZone.save(byteBufferWriter.bb);
 byteBufferWriter.putBoolean(boolean0);
 PacketTypes.PacketType.SyncNonPvpZone.send(udpConnection0);
 }
 }
}

static void receiveChangeTextColor(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = getPlayerFromConnection(udpConnection0, short0);
 if (player != nullptr) {
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 player.setSpeakColourInfo(new ColorInfo(float0, float1, float2, 1.0F);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.ChangeTextColor.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.getOnlineID());
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.ChangeTextColor.send(udpConnection1);
 }
 }
 }
}

static void receiveTransactionID(ByteBuffer byteBuffer, UdpConnection var1) {
 short short0 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 transactionIDMap.put(player.username, int0);
 player.setTransactionID(int0);
 ServerWorldDatabase.instance.saveTransactionID(player.username, int0);
 }
}

static void receiveSyncCompost(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 IsoCompost compost = square.getCompost();
 if (compost.empty()) {
 compost = new IsoCompost(square.getCell(), square);
 square.AddSpecialObject(compost);
 }

 float float0 = byteBuffer.getFloat();
 compost.setCompost(float0);
 sendCompost(compost, udpConnection);
 }
}

static void sendCompost(IsoCompost compost, UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.RelevantTo(compost.square.x, compost.square.y) &&
 (udpConnection1 != nullptr && udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() ||
 udpConnection1.empty())) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncCompost.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(compost.square.x);
 byteBufferWriter.putInt(compost.square.y);
 byteBufferWriter.putInt(compost.square.z);
 byteBufferWriter.putFloat(compost.getCompost());
 PacketTypes.PacketType.SyncCompost.send(udpConnection0);
 }
 }
}

static void receiveCataplasm(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 int int0 = byteBuffer.getInt();
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 if (float0 > 0.0F) {
 player.getBodyDamage()
 .getBodyPart(BodyPartType.FromIndex(int0)
 .setPlantainFactor(float0);
 }

 if (float1 > 0.0F) {
 player.getBodyDamage()
 .getBodyPart(BodyPartType.FromIndex(int0)
 .setComfreyFactor(float1);
 }

 if (float2 > 0.0F) {
 player.getBodyDamage()
 .getBodyPart(BodyPartType.FromIndex(int0)
 .setGarlicFactor(float2);
 }

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.Cataplasm.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.Cataplasm.send(udpConnection0);
 }
 }
 }
}

static void receiveSledgehammerDestroy(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short short0) {
 if (ServerOptions.instance.AllowDestructionBySledgehammer.getValue()) {
 receiveRemoveItemFromSquare(byteBuffer, udpConnection, short0);
 }
}

static void AddExplosiveTrap(HandWeapon weapon, IsoGridSquare square,
 bool boolean0) {
 IsoTrap trap = new IsoTrap(weapon, square.getCell(), square);
 int int0 = 0;
 if (weapon.getExplosionRange() > 0) {
 int0 = weapon.getExplosionRange();
 }

 if (weapon.getFireRange() > 0) {
 int0 = weapon.getFireRange();
 }

 if (weapon.getSmokeRange() > 0) {
 int0 = weapon.getSmokeRange();
 }

 square.AddTileObject(trap);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection = udpEngine.connections.get(int1);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddExplosiveTrap.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(square.x);
 byteBufferWriter.putInt(square.y);
 byteBufferWriter.putInt(square.z);

 try {
 weapon.saveWithSize(byteBufferWriter.bb, false);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 byteBufferWriter.putInt(int0);
 byteBufferWriter.putBoolean(boolean0);
 byteBufferWriter.putBoolean(false);
 PacketTypes.PacketType.AddExplosiveTrap.send(udpConnection);
 }
}

static void receiveAddExplosiveTrap(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 InventoryItem item = nullptr;

 try {
 item = InventoryItem.loadItem(byteBuffer, 195);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (item.empty()) {
 return;
 }

 HandWeapon weapon = (HandWeapon)item;
 DebugLog.log("trap: user \"" + udpConnection0.username + "\" added " +
 item.getFullType() + " at " + int0 + "," + int1 + "," + int2);
 LoggerManager.getLogger("map").write(
 udpConnection0.idStr + " \"" + udpConnection0.username + "\" added " +
 item.getFullType() + " at " + int0 + "," + int1 + "," + int2);
 if (weapon.isInstantExplosion()) {
 IsoTrap trap = new IsoTrap(weapon, square.getCell(), square);
 square.AddTileObject(trap);
 trap.triggerExplosion(false);
 }

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int3);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.AddExplosiveTrap.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);

 try {
 weapon.saveWithSize(byteBufferWriter.bb, false);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 PacketTypes.PacketType.AddExplosiveTrap.send(udpConnection1);
 }
 }
 }
}

static void sendHelicopter(float float0, float float1, bool boolean0) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Helicopter.doPacket(byteBufferWriter);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putBoolean(boolean0);
 PacketTypes.PacketType.Helicopter.send(udpConnection);
 }
}

static void receiveRegisterZone(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 int int5 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 std::vector arrayList =
 IsoWorld.instance.getMetaGrid().getZonesAt(int0, int1, int2);
 bool boolean1 = false;

 for (IsoMetaGrid.Zone zone : arrayList) {
 if (string1 == zone.getType())) {
 boolean1 = true;
 zone.setName(string0);
 zone.setLastActionTimestamp(int5);
 }
 }

 if (!boolean1) {
 IsoWorld.instance.getMetaGrid().registerZone(string0, string1, int0, int1,
 int2, int3, int4);
 }

 if (boolean0) {
 for (int int6 = 0; int6 < udpEngine.connections.size(); int6++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int6);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.RegisterZone.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putInt(int4);
 byteBufferWriter.putInt(int5);
 PacketTypes.PacketType.RegisterZone.send(udpConnection0);
 }
 }
 }
}

static void sendZone(IsoMetaGrid.Zone zone, UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.RegisterZone.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(zone.name);
 byteBufferWriter.putUTF(zone.type);
 byteBufferWriter.putInt(zone.x);
 byteBufferWriter.putInt(zone.y);
 byteBufferWriter.putInt(zone.z);
 byteBufferWriter.putInt(zone.w);
 byteBufferWriter.putInt(zone.h);
 byteBufferWriter.putInt(zone.lastActionTimestamp);
 PacketTypes.PacketType.RegisterZone.send(udpConnection0);
 }
 }
}

static void receiveConstructedZone(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoMetaGrid.Zone zone =
 IsoWorld.instance.MetaGrid.getZoneAt(int0, int1, int2);
 if (zone != nullptr) {
 zone.setHaveConstruction(true);
 }
}

static void addXp(IsoPlayer player, PerkFactory.Perk perk, int int0) {
 if (PlayerToAddressMap.containsKey(player) {
 long long0 = PlayerToAddressMap.get(player);
 UdpConnection udpConnection = udpEngine.getActiveConnection(long0);
 if (udpConnection.empty()) {
 return;
 }

 AddXp addXp = new AddXp();
 addXp.set(player, perk, int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddXP.doPacket(byteBufferWriter);
 addXp.write(byteBufferWriter);
 PacketTypes.PacketType.AddXP.send(udpConnection);
 }
}

static void receiveWriteLog(ByteBuffer var0, UdpConnection var1, short var2) {}

static void receiveChecksum(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 NetChecksum.comparer.serverPacket(byteBuffer, udpConnection);
}

static void answerPing(ByteBuffer byteBuffer, UdpConnection udpConnection1) {
 std::string string = GameWindow.ReadString(byteBuffer);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() ==
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.Ping.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putInt(udpEngine.connections.size());
 byteBufferWriter.putInt(512);
 PacketTypes.PacketType.Ping.send(udpConnection0);
 }
 }
}

static void receiveUpdateItemSprite(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 int int0 = byteBuffer.getInt();
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int1, int2, int3);
 if (square != nullptr && int4 < square.getObjects().size()) {
 try {
 IsoObject object = square.getObjects().get(int4);
 if (object != nullptr) {
 object.sprite = IsoSpriteManager.instance.getSprite(int0);
 if (object.sprite.empty() && !string.empty()) {
 object.setSprite(string);
 }

 object.RemoveAttachedAnims();
 int int5 = byteBuffer.get() & 255;

 for (int int6 = 0; int6 < int5; int6++) {
 int int7 = byteBuffer.getInt();
 IsoSprite sprite = IsoSpriteManager.instance.getSprite(int7);
 if (sprite != nullptr) {
 object.AttachExistingAnim(sprite, 0, 0, false, 0, false, 0.0F);
 }
 }

 object.transmitUpdatedSpriteToClients(udpConnection);
 }
 } catch (Exception exception) {
 }
 }
}

static void receiveWorldMessage(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 if (!udpConnection0.allChatMuted) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 if (string1.length() > 256) {
 string1 = string1.substring(0, 256);
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.WorldMessage.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 PacketTypes.PacketType.WorldMessage.send(udpConnection1);
 }

 discordBot.sendMessage(string0, string1);
 LoggerManager.getLogger("chat").write(udpConnection0.index + " \"" +
 udpConnection0.username + "\" A \"" +
 string1 + "\"");
 }
}

static void receiveGetModData(ByteBuffer var0, UdpConnection var1, short var2) {
 LuaEventManager.triggerEvent("SendCustomModData");
}

static void receiveStopFire(ByteBuffer byteBuffer, UdpConnection udpConnection1,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 player.sendObjectChange("StopBurning");
 }
 } else if (byte0 == 2) {
 short short1 = byteBuffer.getShort();
 IsoZombie zombie0 = ServerMap.instance.ZombieMap.get(short1);
 if (zombie0 != nullptr) {
 zombie0.StopBurning();
 }
 } else {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 square.stopFire();

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int3);
 if (udpConnection0.RelevantTo(int0, int1) &&
 udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.StopFire.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 PacketTypes.PacketType.StopFire.send(udpConnection0);
 }
 }
 }
 }
}

static void receiveStartFire(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 StartFire startFire = new StartFire();
 startFire.parse(byteBuffer, udpConnection0);
 if (startFire.isConsistent() && startFire.validate(udpConnection0) {
 startFire.process();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.StartFire.doPacket(byteBufferWriter);
 startFire.write(byteBufferWriter);
 PacketTypes.PacketType.StartFire.send(udpConnection1);
 }
 }
 }
}

static void startFireOnClient(IsoGridSquare square, int int0, bool boolean0,
 int int1, bool boolean1) {
 StartFire startFire = new StartFire();
 startFire.set(square, boolean0, int0, int1, boolean1);
 startFire.process();

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection = udpEngine.connections.get(int2);
 if (udpConnection.RelevantTo(square.getX(), square.getY())) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StartFire.doPacket(byteBufferWriter);
 startFire.write(byteBufferWriter);
 PacketTypes.PacketType.StartFire.send(udpConnection);
 }
 }
}

static void sendOptionsToClients() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ReloadOptions.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(ServerOptions.instance.getPublicOptions().size());
 void *object = nullptr;

 for (String string : ServerOptions.instance.getPublicOptions()) {
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putUTF(ServerOptions.instance.getOption(string);
 }

 PacketTypes.PacketType.ReloadOptions.send(udpConnection);
 }
}

static void sendBecomeCorpse(IsoDeadBody deadBody) {
 IsoGridSquare square = deadBody.getSquare();
 if (square != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(square.x, square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.BecomeCorpse.doPacket(byteBufferWriter);

 try {
 byteBufferWriter.putShort(deadBody.getObjectID());
 byteBufferWriter.putShort(deadBody.getOnlineID());
 byteBufferWriter.putFloat(deadBody.getReanimateTime());
 if (deadBody.isPlayer()) {
 byteBufferWriter.putByte((byte)2);
 } else if (deadBody.isZombie()) {
 byteBufferWriter.putByte((byte)1);
 } else {
 byteBufferWriter.putByte((byte)0);
 }

 byteBufferWriter.putInt(square.x);
 byteBufferWriter.putInt(square.y);
 byteBufferWriter.putInt(square.z);
 PacketTypes.PacketType.BecomeCorpse.send(udpConnection);
 } catch (Exception exception) {
 udpConnection.cancelPacket();
 DebugLog.Multiplayer.printException(
 exception, "SendBecomeCorpse failed", LogSeverity.Error);
 }
 }
 }
 }
}

static void sendCorpse(IsoDeadBody deadBody) {
 IsoGridSquare square = deadBody.getSquare();
 if (square != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(square.x, square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddCorpseToMap.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(deadBody.getObjectID());
 byteBufferWriter.putShort(deadBody.getOnlineID());
 byteBufferWriter.putInt(square.x);
 byteBufferWriter.putInt(square.y);
 byteBufferWriter.putInt(square.z);
 deadBody.writeToRemoteBuffer(byteBufferWriter);
 PacketTypes.PacketType.AddCorpseToMap.send(udpConnection);
 }
 }
 }
}

static void receiveAddCorpseToMap(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoObject object = WorldItemTypes.createFromBuffer(byteBuffer);
 if (object != nullptr && object instanceof IsoDeadBody) {
 object.loadFromRemoteBuffer(byteBuffer, false);
 ((IsoDeadBody)object).setObjectID(short0);
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 square.addCorpse((IsoDeadBody)object, true);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int3);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection0.RelevantTo(int0, int1) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.AddCorpseToMap.doPacket(byteBufferWriter);
 byteBuffer.rewind();
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.AddCorpseToMap.send(udpConnection0);
 }
 }
 }

 LoggerManager.getLogger("item").write(
 udpConnection1.idStr + " \"" + udpConnection1.username +
 "\" corpse +1 " + int0 + "," + int1 + "," + int2);
 }
}

static void receiveSmashWindow(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 IsoObject object = IsoWorld.instance.getItemFromXYZIndexBuffer(byteBuffer);
 if (object != nullptr && object instanceof IsoWindow) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 ((IsoWindow)object).smashWindow(true);
 smashWindow((IsoWindow)object, 1);
 } else if (byte0 == 2) {
 ((IsoWindow)object).setGlassRemoved(true);
 smashWindow((IsoWindow)object, 2);
 }
 }
}

static void sendPlayerConnect(IsoPlayer player, UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.PlayerConnect.doPacket(byteBufferWriter);
 if (udpConnection.getConnectedGUID() != PlayerToAddressMap.get(player) {
 byteBufferWriter.putShort(player.OnlineID);
 } else {
 byteBufferWriter.putShort((short)-1);
 byteBufferWriter.putByte((byte)player.PlayerIndex);
 byteBufferWriter.putShort(player.OnlineID);

 try {
 GameTime.getInstance().saveToPacket(byteBufferWriter.bb);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }
 }

 byteBufferWriter.putFloat(player.x);
 byteBufferWriter.putFloat(player.y);
 byteBufferWriter.putFloat(player.z);
 byteBufferWriter.putUTF(player.username);
 if (udpConnection.getConnectedGUID() != PlayerToAddressMap.get(player) {
 try {
 player.getDescriptor().save(byteBufferWriter.bb);
 player.getHumanVisual().save(byteBufferWriter.bb);
 ItemVisuals itemVisuals = new ItemVisuals();
 player.getItemVisuals(itemVisuals);
 itemVisuals.save(byteBufferWriter.bb);
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }

 if (SteamUtils.isSteamModeEnabled()) {
 byteBufferWriter.putLong(player.getSteamID());
 }

 byteBufferWriter.putByte((byte)(player.isGodMod() ? 1 : 0);
 byteBufferWriter.putByte((byte)(player.isGhostMode() ? 1 : 0);
 player.getSafety().save(byteBufferWriter.bb);
 byteBufferWriter.putByte(PlayerType.fromString(player.accessLevel);
 byteBufferWriter.putByte((byte)(player.isInvisible() ? 1 : 0);
 if (udpConnection.getConnectedGUID() != PlayerToAddressMap.get(player) {
 try {
 player.getXp().save(byteBufferWriter.bb);
 } catch (IOException iOException2) {
 iOException2.printStackTrace();
 }
 }

 byteBufferWriter.putUTF(player.getTagPrefix());
 byteBufferWriter.putFloat(player.getTagColor().r);
 byteBufferWriter.putFloat(player.getTagColor().g);
 byteBufferWriter.putFloat(player.getTagColor().b);
 byteBufferWriter.putDouble(player.getHoursSurvived());
 byteBufferWriter.putInt(player.getZombieKills());
 byteBufferWriter.putUTF(player.getDisplayName());
 byteBufferWriter.putFloat(player.getSpeakColour().r);
 byteBufferWriter.putFloat(player.getSpeakColour().g);
 byteBufferWriter.putFloat(player.getSpeakColour().b);
 byteBufferWriter.putBoolean(player.showTag);
 byteBufferWriter.putBoolean(player.factionPvp);
 byteBufferWriter.putInt(player.getAttachedItems().size());

 for (int int0 = 0; int0 < player.getAttachedItems().size(); int0++) {
 byteBufferWriter.putUTF(player.getAttachedItems().get(int0).getLocation());
 byteBufferWriter.putUTF(
 player.getAttachedItems().get(int0).getItem().getFullType());
 }

 byteBufferWriter.putInt(player.remoteSneakLvl);
 byteBufferWriter.putInt(player.remoteStrLvl);
 byteBufferWriter.putInt(player.remoteFitLvl);
 PacketTypes.PacketType.PlayerConnect.send(udpConnection);
 if (udpConnection.getConnectedGUID() != PlayerToAddressMap.get(player) {
 updateHandEquips(udpConnection, player);
 }
}

static void receiveRequestPlayerData(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 IsoPlayer player = IDToPlayerMap.get(byteBuffer.getShort());
 if (player != nullptr) {
 sendPlayerConnect(player, udpConnection);
 }
}

static void receiveChatMessageFromPlayer(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 ChatServer.getInstance().processMessageFromPlayerPacket(byteBuffer);
}

static void loadModData(IsoGridSquare square) {
 if (square.getModData().rawget("id") != nullptr &&
 square.getModData().rawget("id") != nullptr &&
 (square.getModData().rawget("remove") == nullptr ||
 ((String)square.getModData().rawget("remove")) == "false"))) {
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":x",
 new Double(square.getX()));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":y",
 new Double(square.getY()));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":z",
 new Double(square.getZ()));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":typeOfSeed",
 square.getModData().rawget("typeOfSeed"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":nbOfGrow",
 (Double)square.getModData().rawget("nbOfGrow"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":id",
 square.getModData().rawget("id"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":waterLvl",
 square.getModData().rawget("waterLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":lastWaterHour",
 square.getModData().rawget("lastWaterHour"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":waterNeeded",
 square.getModData().rawget("waterNeeded"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":waterNeededMax",
 square.getModData().rawget("waterNeededMax"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":mildewLvl",
 square.getModData().rawget("mildewLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":aphidLvl",
 square.getModData().rawget("aphidLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":fliesLvl",
 square.getModData().rawget("fliesLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":fertilizer",
 square.getModData().rawget("fertilizer"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":nextGrowing",
 square.getModData().rawget("nextGrowing"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":hasVegetable",
 square.getModData().rawget("hasVegetable"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":hasSeed",
 square.getModData().rawget("hasSeed"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":health",
 square.getModData().rawget("health"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":badCare",
 square.getModData().rawget("badCare"));
 GameTime.getInstance().getModData().rawset(
 "planting:" + ((Double)square.getModData().rawget("id")).intValue() +
 ":state",
 square.getModData().rawget("state"));
 if (square.getModData().rawget("hoursElapsed") != nullptr) {
 GameTime.getInstance().getModData().rawset(
 "hoursElapsed", square.getModData().rawget("hoursElapsed"));
 }
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(square.getX(), square.getY())) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ReceiveModData.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(square.getX());
 byteBufferWriter.putInt(square.getY());
 byteBufferWriter.putInt(square.getZ());

 try {
 square.getModData().save(byteBufferWriter.bb);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 PacketTypes.PacketType.ReceiveModData.send(udpConnection);
 }
 }
}

static void receiveSendModData(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 try {
 square.getModData().load(byteBuffer, 195);
 if (square.getModData().rawget("id") != nullptr &&
 (square.getModData().rawget("remove") == nullptr ||
 ((String)square.getModData().rawget("remove")) == "false"))) {
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() + ":x",
 new Double(square.getX()));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() + ":y",
 new Double(square.getY()));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() + ":z",
 new Double(square.getZ()));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":typeOfSeed",
 square.getModData().rawget("typeOfSeed"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":nbOfGrow",
 (Double)square.getModData().rawget("nbOfGrow"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() + ":id",
 square.getModData().rawget("id"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":waterLvl",
 square.getModData().rawget("waterLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":lastWaterHour",
 square.getModData().rawget("lastWaterHour"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":waterNeeded",
 square.getModData().rawget("waterNeeded"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":waterNeededMax",
 square.getModData().rawget("waterNeededMax"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":mildewLvl",
 square.getModData().rawget("mildewLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":aphidLvl",
 square.getModData().rawget("aphidLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":fliesLvl",
 square.getModData().rawget("fliesLvl"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":fertilizer",
 square.getModData().rawget("fertilizer"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":nextGrowing",
 square.getModData().rawget("nextGrowing"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":hasVegetable",
 square.getModData().rawget("hasVegetable"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":hasSeed",
 square.getModData().rawget("hasSeed"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":health",
 square.getModData().rawget("health"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":badCare",
 square.getModData().rawget("badCare"));
 GameTime.getInstance().getModData().rawset(
 "planting:" +
 ((Double)square.getModData().rawget("id")).intValue() +
 ":state",
 square.getModData().rawget("state"));
 if (square.getModData().rawget("hoursElapsed") != nullptr) {
 GameTime.getInstance().getModData().rawset(
 "hoursElapsed", square.getModData().rawget("hoursElapsed"));
 }
 }

 LuaEventManager.triggerEvent("onLoadModDataFromServer", square);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int3);
 if (udpConnection0.RelevantTo(square.getX(), square.getY()) &&
 (udpConnection1.empty() ||
 udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID())) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.ReceiveModData.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);

 try {
 square.getModData().save(byteBufferWriter.bb);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }

 PacketTypes.PacketType.ReceiveModData.send(udpConnection0);
 }
 }
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }
}

static void receiveWeaponHit(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 IsoObject object = getIsoObjectRefFromByteBuffer(byteBuffer);
 short short0 = byteBuffer.getShort();
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 IsoPlayer player = getPlayerFromConnection(udpConnection, short0);
 if (object != nullptr && player != nullptr) {
 InventoryItem item = nullptr;
 if (!string.empty()) {
 item = InventoryItemFactory.CreateItem(string);
 if (!(item instanceof HandWeapon) {
 return;
 }
 }

 if (item.empty() && !(object instanceof IsoWindow) {
 return;
 }

 int int0 = (int)object.getX();
 int int1 = (int)object.getY();
 int int2 = (int)object.getZ();
 if (object instanceof IsoDoor) {
 ((IsoDoor)object).WeaponHit(player, (HandWeapon)item);
 } else if (object instanceof IsoThumpable) {
 ((IsoThumpable)object).WeaponHit(player, (HandWeapon)item);
 } else if (object instanceof IsoWindow) {
 ((IsoWindow)object).WeaponHit(player, (HandWeapon)item);
 } else if (object instanceof IsoBarricade) {
 ((IsoBarricade)object).WeaponHit(player, (HandWeapon)item);
 }

 if (object.getObjectIndex() == -1) {
 LoggerManager.getLogger("map").write(
 udpConnection.idStr + " \"" + udpConnection.username +
 "\" destroyed " +
 (object.getName() != nullptr ? object.getName()
 : object.getObjectName()) +
 " with " + (string.empty() ? "BareHands" : string) + " at " + int0 +
 "," + int1 + "," + int2);
 }
 }
}

static void putIsoObjectRefToByteBuffer(IsoObject object,
 ByteBuffer byteBuffer) {
 byteBuffer.putInt(object.square.x);
 byteBuffer.putInt(object.square.y);
 byteBuffer.putInt(object.square.z);
 byteBuffer.put((byte)object.square.getObjects().indexOf(object);
}

static IsoObject getIsoObjectRefFromByteBuffer(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 return square != nullptr && byte0 >= 0 && byte0 < square.getObjects().size()
 ? square.getObjects().get(byte0)
 : nullptr;
}

static void receiveDrink(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 float float0 = byteBuffer.getFloat();
 IsoPlayer player = getPlayerFromConnection(udpConnection, byte0);
 if (player != nullptr) {
 player.getStats().thirst -= float0;
 if (player.getStats().thirst < 0.0F) {
 player.getStats().thirst = 0.0F;
 }
 }
}

static void process(ZomboidNetData zomboidNetData) {
 ByteBuffer byteBuffer = zomboidNetData.buffer;
 UdpConnection udpConnection =
 udpEngine.getActiveConnection(zomboidNetData.connection);

 try {
 switch (zomboidNetData.type) {
 default:
 doZomboidDataInMainLoop(zomboidNetData);
 }
 } catch (Exception exception) {
 DebugLog.log(DebugType.Network,
 "Error with packet of type: " + zomboidNetData.type);
 exception.printStackTrace();
 }
}

static void receiveEatFood(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 float float0 = byteBuffer.getFloat();
 InventoryItem item = nullptr;

 try {
 item = InventoryItem.loadItem(byteBuffer, 195);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (item instanceof Food) {
 IsoPlayer player = getPlayerFromConnection(udpConnection, byte0);
 if (player != nullptr) {
 player.Eat(item, float0);
 }
 }
}

static void receivePingFromClient(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 long long0 = byteBuffer.getLong();
 if (long0 == -1L) {
 DebugLog.Multiplayer.warn("Player \"%s\" toggled lua debugger",
 udpConnection.username);
 } else {
 if (udpConnection.accessLevel != 32) {
 return;
 }

 PacketTypes.PacketType.PingFromClient.doPacket(byteBufferWriter);

 try {
 byteBufferWriter.putLong(long0);
 MPStatistics.write(udpConnection, byteBufferWriter.bb);
 PacketTypes.PacketType.PingFromClient.send(udpConnection);
 MPStatistics.requested();
 } catch (Exception exception) {
 udpConnection.cancelPacket();
 }
 }
}

static void receiveBandage(ByteBuffer byteBuffer, UdpConnection udpConnection1,
 short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 int int0 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 float float0 = byteBuffer.getFloat();
 bool boolean1 = byteBuffer.get() == 1;
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 player.getBodyDamage().SetBandaged(int0, boolean0, float0, boolean1,
 string);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.Bandage.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putBoolean(boolean0);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putBoolean(boolean1);
 GameWindow.WriteStringUTF(byteBufferWriter.bb, string);
 PacketTypes.PacketType.Bandage.send(udpConnection0);
 }
 }
 }
}

static void receiveStitch(ByteBuffer byteBuffer, UdpConnection udpConnection0,
 short var2) {
 Stitch stitch = new Stitch();
 stitch.parse(byteBuffer, udpConnection0);
 if (stitch.isConsistent() && stitch.validate(udpConnection0) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.Stitch.doPacket(byteBufferWriter);
 stitch.write(byteBufferWriter);
 PacketTypes.PacketType.Stitch.send(udpConnection1);
 }
 }
 }
}

static void receiveWoundInfection(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 int int0 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 player.getBodyDamage()
 .getBodyPart(BodyPartType.FromIndex(int0)
 .setInfectedWound(boolean0);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.WoundInfection.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putBoolean(boolean0);
 PacketTypes.PacketType.WoundInfection.send(udpConnection0);
 }
 }
 }
}

static void receiveDisinfect(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 Disinfect disinfect = new Disinfect();
 disinfect.parse(byteBuffer, udpConnection0);
 if (disinfect.isConsistent() && disinfect.validate(udpConnection0) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.Disinfect.doPacket(byteBufferWriter);
 disinfect.write(byteBufferWriter);
 PacketTypes.PacketType.Disinfect.send(udpConnection1);
 }
 }
 }
}

static void receiveSplint(ByteBuffer byteBuffer, UdpConnection udpConnection1,
 short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 int int0 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 std::string string = boolean0 ? GameWindow.ReadStringUTF(byteBuffer) : nullptr;
 float float0 = boolean0 ? byteBuffer.getFloat() : 0.0F;
 BodyPart bodyPart =
 player.getBodyDamage().getBodyPart(BodyPartType.FromIndex(int0);
 bodyPart.setSplint(boolean0, float0);
 bodyPart.setSplintItem(string);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.Splint.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putBoolean(boolean0);
 if (boolean0) {
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putFloat(float0);
 }

 PacketTypes.PacketType.Splint.send(udpConnection0);
 }
 }
 }
}

static void receiveAdditionalPain(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 int int0 = byteBuffer.getInt();
 float float0 = byteBuffer.getFloat();
 BodyPart bodyPart =
 player.getBodyDamage().getBodyPart(BodyPartType.FromIndex(int0);
 bodyPart.setAdditionalPain(bodyPart.getAdditionalPain() + float0);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.AdditionalPain.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putFloat(float0);
 PacketTypes.PacketType.AdditionalPain.send(udpConnection0);
 }
 }
 }
}

static void receiveRemoveGlass(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 RemoveGlass removeGlass = new RemoveGlass();
 removeGlass.parse(byteBuffer, udpConnection0);
 if (removeGlass.isConsistent() && removeGlass.validate(udpConnection0) {
 removeGlass.process();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.RemoveGlass.doPacket(byteBufferWriter);
 removeGlass.write(byteBufferWriter);
 PacketTypes.PacketType.RemoveGlass.send(udpConnection1);
 }
 }
 }
}

static void receiveRemoveBullet(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 RemoveBullet removeBullet = new RemoveBullet();
 removeBullet.parse(byteBuffer, udpConnection0);
 if (removeBullet.isConsistent() && removeBullet.validate(udpConnection0) {
 removeBullet.process();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.RemoveBullet.doPacket(byteBufferWriter);
 removeBullet.write(byteBufferWriter);
 PacketTypes.PacketType.RemoveBullet.send(udpConnection1);
 }
 }
 }
}

static void receiveCleanBurn(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 CleanBurn cleanBurn = new CleanBurn();
 cleanBurn.parse(byteBuffer, udpConnection0);
 if (cleanBurn.isConsistent() && cleanBurn.validate(udpConnection0) {
 cleanBurn.process();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.CleanBurn.doPacket(byteBufferWriter);
 cleanBurn.write(byteBufferWriter);
 PacketTypes.PacketType.CleanBurn.send(udpConnection1);
 }
 }
 }
}

static void receiveBodyDamageUpdate(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 BodyDamageSync.instance.serverPacket(byteBuffer);
}

static void receiveReceiveCommand(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 std::string string = GameWindow.ReadString(byteBuffer);
 void *object = nullptr;
 object = handleClientCommand(string.substring(1), udpConnection);
 if (object.empty()) {
 object = handleServerCommand(string.substring(1), udpConnection);
 }

 if (object.empty()) {
 object = "Unknown command " + string;
 }

 if (!string.substring(1).startsWith("roll") &&
 !string.substring(1).startsWith("card")) {
 ChatServer.getInstance().sendMessageToServerChat(udpConnection,
 (String)object);
 } else {
 ChatServer.getInstance().sendMessageToServerChat(udpConnection,
 (String)object);
 }
}

static std::string handleClientCommand(std::string_view string0,
 UdpConnection udpConnection) {
 if (string0.empty()) {
 return nullptr;
 } else {
 std::vector arrayList = new ArrayList();
 Matcher matcher =
 Pattern.compile("([^\"]\\S*|\".*?\")\\s*").matcher(string0);

 while (matcher.find()) {
 arrayList.add(matcher.group(1).replace("\"", ""));
 }

 int int0 = arrayList.size();
 String[] strings = arrayList.toArray(new String[int0]);
 std::string string1 = int0 > 0 ? strings[0].toLowerCase() : "";
 if (string1 == "card")) {
 PlayWorldSoundServer(
 "ChatDrawCard", false,
 getAnyPlayerFromConnection(udpConnection).getCurrentSquare(), 0.0F,
 3.0F, 1.0F, false);
 return udpConnection.username + " drew " +
 ServerOptions.getRandomCard();
 }
 else if (string1 == "roll")) {
 if (int0 != 2) {
 return ServerOptions.clientOptionsList.get("roll");
 } else {
 int int1 = 0;

 try {
 int1 = Integer.parseInt(strings[1]);
 PlayWorldSoundServer(
 "ChatRollDice", false,
 getAnyPlayerFromConnection(udpConnection).getCurrentSquare(),
 0.0F, 3.0F, 1.0F, false);
 return udpConnection.username + " rolls a " + int1 +
 "-sided dice and obtains " + Rand.Next(int1);
 } catch (Exception exception) {
 return ServerOptions.clientOptionsList.get("roll");
 }
 }
 }
 else if (string1 == "changepwd")) {
 if (int0 == 3) {
 std::string string2 = strings[1];
 std::string string3 = strings[2];

 try {
 return ServerWorldDatabase.instance.changePwd(
 udpConnection.username, string2.trim(), string3.trim());
 } catch (SQLException sQLException) {
 sQLException.printStackTrace();
 return "A SQL error occured";
 }
 } else {
 return ServerOptions.clientOptionsList.get("changepwd");
 }
 }
 else if (string1 == "dragons")) {
 return "Sorry, you don't have the required materials.";
 }
 else if (string1 == "dance")) {
 return "Stop kidding me...";
 }
 else if (string1 == "safehouse")) {
 if (int0 != 2 || udpConnection.empty()) {
 return ServerOptions.clientOptionsList.get("safehouse");
 } else if (!ServerOptions.instance.PlayerSafehouse.getValue() &&
 !ServerOptions.instance.AdminSafehouse.getValue()) {
 return "Safehouses are disabled on this server.";
 } else if ("release" == strings[1])) {
 SafeHouse safeHouse =
 SafeHouse.hasSafehouse(udpConnection.username);
 if (safeHouse.empty()) {
 return "You don't own a safehouse.";
 } else if (!ServerOptions.instance.PlayerSafehouse.getValue() &&
 !"admin" == udpConnection.accessLevel)
 && !"moderator" == udpConnection.accessLevel) {
 return "Only admin or moderator may release "
 "safehouses";
 }
 else {
 safeHouse.removeSafeHouse(nullptr);
 return "Safehouse released";
 }
 }
 else {
 return ServerOptions.clientOptionsList.get("safehouse");
 }
 }
 else {
 return nullptr;
 }
 }
}

static void doZomboidDataInMainLoop(ZomboidNetData zomboidNetData) {
 { std::lock_guard<std::mutex> __sync_lock__(MainLoopNetDataHighPriorityQ_mutex);
 MainLoopNetDataHighPriorityQ.add(zomboidNetData);
 }
}

static void receiveEquip(ByteBuffer byteBuffer, UdpConnection udpConnection0,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 uint8_t byte1 = byteBuffer.get();
 uint8_t byte2 = byteBuffer.get();
 InventoryItem item = nullptr;
 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (byte2 == 1) {
 try {
 item = InventoryItem.loadItem(byteBuffer, 195);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (item.empty()) {
 LoggerManager.getLogger("user").write(udpConnection0.idStr +
 " equipped unknown item type");
 return;
 }
 }

 if (player0 != nullptr) {
 if (item != nullptr) {
 item.setContainer(player0.getInventory());
 }

 if (byte1 == 0) {
 player0.setPrimaryHandItem(item);
 } else {
 if (byte2 == 2) {
 item = player0.getPrimaryHandItem();
 }

 player0.setSecondaryHandItem(item);
 }

 try {
 if (byte2 == 1 && item != nullptr && byteBuffer.get() == 1) {
 item.getVisual().load(byteBuffer, 195);
 }
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }
 }

 if (player0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection1);
 if (player1 != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.Equip.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 byteBufferWriter.putByte(byte1);
 byteBufferWriter.putByte(byte2);
 if (byte2 == 1) {
 try {
 item.saveWithSize(byteBufferWriter.bb, false);
 if (item.getVisual() != nullptr) {
 byteBufferWriter.bb.put((byte)1);
 item.getVisual().save(byteBufferWriter.bb);
 } else {
 byteBufferWriter.bb.put((byte)0);
 }
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }

 PacketTypes.PacketType.Equip.send(udpConnection1);
 }
 }
 }
 }
}

static void receivePlayerConnect(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 receivePlayerConnect(byteBuffer, udpConnection, udpConnection.username);
 sendInitialWorldState(udpConnection);
}

static void receiveScoreboardUpdate(ByteBuffer var0,
 UdpConnection udpConnection0, short var2) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.ScoreboardUpdate.doPacket(byteBufferWriter);
 std::vector arrayList0 = new ArrayList();
 std::vector arrayList1 = new ArrayList();
 std::vector arrayList2 = new ArrayList();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.isFullyConnected()) {
 for (int int1 = 0; int1 < 4; int1++) {
 if (udpConnection1.usernames[int1] != nullptr) {
 arrayList0.add(udpConnection1.usernames[int1]);
 IsoPlayer player =
 getPlayerByRealUserName(udpConnection1.usernames[int1]);
 if (player != nullptr) {
 arrayList1.add(player.getDisplayName());
 } else {
 std::string string = ServerWorldDatabase.instance.getDisplayName(
 udpConnection1.usernames[int1]);
 arrayList1.add(string.empty() ? udpConnection1.usernames[int1]
 : string);
 }

 if (SteamUtils.isSteamModeEnabled()) {
 arrayList2.add(udpConnection1.steamID);
 }
 }
 }
 }
 }

 byteBufferWriter.putInt(arrayList0.size());

 for (int int2 = 0; int2 < arrayList0.size(); int2++) {
 byteBufferWriter.putUTF((String)arrayList0.get(int2);
 byteBufferWriter.putUTF((String)arrayList1.get(int2);
 if (SteamUtils.isSteamModeEnabled()) {
 byteBufferWriter.putLong((Long)arrayList2.get(int2);
 }
 }

 PacketTypes.PacketType.ScoreboardUpdate.send(udpConnection0);
}

static void receiveStopSound(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 StopSoundPacket stopSoundPacket = new StopSoundPacket();
 stopSoundPacket.parse(byteBuffer, udpConnection0);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.isFullyConnected()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.StopSound.doPacket(byteBufferWriter);
 stopSoundPacket.write(byteBufferWriter);
 PacketTypes.PacketType.StopSound.send(udpConnection1);
 }
 }
}

static void receivePlaySound(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 PlaySoundPacket playSoundPacket = new PlaySoundPacket();
 playSoundPacket.parse(byteBuffer, udpConnection0);
 IsoMovingObject movingObject = playSoundPacket.getMovingObject();
 if (playSoundPacket.isConsistent()) {
 int int0 = 70;
 GameSound gameSound = GameSounds.getSound(playSoundPacket.getName());
 if (gameSound != nullptr) {
 for (int int1 = 0; int1 < gameSound.clips.size(); int1++) {
 GameSoundClip gameSoundClip = gameSound.clips.get(int1);
 if (gameSoundClip.hasMaxDistance()) {
 int0 = Math.max(int0, (int)gameSoundClip.distanceMax);
 }
 }
 }

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int2);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.isFullyConnected()) {
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection1);
 if (player != nullptr &&
 (movingObject.empty() ||
 udpConnection1.RelevantTo(movingObject.getX(), movingObject.getY(),
 int0)) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.PlaySound.doPacket(byteBufferWriter);
 playSoundPacket.write(byteBufferWriter);
 PacketTypes.PacketType.PlaySound.send(udpConnection1);
 }
 }
 }
 }
}

static void receivePlayWorldSound(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 PlayWorldSoundPacket playWorldSoundPacket = new PlayWorldSoundPacket();
 playWorldSoundPacket.parse(byteBuffer, udpConnection0);
 if (playWorldSoundPacket.isConsistent()) {
 int int0 = 70;
 GameSound gameSound = GameSounds.getSound(playWorldSoundPacket.getName());
 if (gameSound != nullptr) {
 for (int int1 = 0; int1 < gameSound.clips.size(); int1++) {
 GameSoundClip gameSoundClip = gameSound.clips.get(int1);
 if (gameSoundClip.hasMaxDistance()) {
 int0 = Math.max(int0, (int)gameSoundClip.distanceMax);
 }
 }
 }

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int2);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.isFullyConnected()) {
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection1);
 if (player != nullptr &&
 udpConnection1.RelevantTo(playWorldSoundPacket.getX(),
 playWorldSoundPacket.getY(), int0) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.PlayWorldSound.doPacket(byteBufferWriter);
 playWorldSoundPacket.write(byteBufferWriter);
 PacketTypes.PacketType.PlayWorldSound.send(udpConnection1);
 }
 }
 }
 }
}

static void PlayWorldSound(std::string_view string, IsoGridSquare square,
 float float0) {
 if (bServer && square != nullptr) {
 int int0 = square.getX();
 int int1 = square.getY();
 int int2 = square.getZ();
 PlayWorldSoundPacket playWorldSoundPacket = new PlayWorldSoundPacket();
 playWorldSoundPacket.set(string, int0, int1, (byte)int2);
 DebugLog.log(DebugType.Sound, "sending " +
 playWorldSoundPacket.getDescription() +
 " radius=" + float0);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection = udpEngine.connections.get(int3);
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection);
 if (player != nullptr &&
 udpConnection.RelevantTo(int0, int1, float0 * 2.0F) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.PlayWorldSound.doPacket(byteBufferWriter);
 playWorldSoundPacket.write(byteBufferWriter);
 PacketTypes.PacketType.PlayWorldSound.send(udpConnection);
 }
 }
 }
}

static void PlayWorldSoundServer(std::string_view string, bool var1,
 IsoGridSquare square, float var3, float float0,
 float var5, bool var6) {
 PlayWorldSound(string, square, float0);
}

public
static void PlayWorldSoundServer(IsoGameCharacter character, String string,
 boolean var2, IsoGridSquare square, float var4,
 float float0, float var6, boolean var7) {
 if (character.empty() || !character.isInvisible() ||
 DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible.getValue()) {
 PlayWorldSound(string, square, float0);
 }
}

static void PlayWorldSoundWavServer(std::string_view string, bool var1,
 IsoGridSquare square, float var3,
 float float0, float var5, bool var6) {
 PlayWorldSound(string, square, float0);
}

static void PlaySoundAtEveryPlayer(std::string_view string, int int0,
 int int1, int int2) {
 PlaySoundAtEveryPlayer(string, int0, int1, int2, false);
}

static void PlaySoundAtEveryPlayer(std::string_view string) {
 PlaySoundAtEveryPlayer(string, -1, -1, -1, true);
}

static void PlaySoundAtEveryPlayer(std::string_view string, int int1,
 int int0, int int3, bool boolean0) {
 if (bServer) {
 if (boolean0) {
 DebugLog.log(DebugType.Sound,
 "sound: sending " + string +
 " at every player (using player location)");
 } else {
 DebugLog.log(DebugType.Sound, "sound: sending " + string +
 " at every player location x=" + int1 +
 " y=" + int0);
 }

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection = udpEngine.connections.get(int2);
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection);
 if (player != nullptr && !player.isDeaf()) {
 if (boolean0) {
 int1 = (int)player.getX();
 int0 = (int)player.getY();
 int3 = (int)player.getZ();
 }

 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.PlaySoundEveryPlayer.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.PlaySoundEveryPlayer.send(udpConnection);
 }
 }
 }
}

static void sendZombieSound(IsoZombie.ZombieSound zombieSound,
 IsoZombie zombie0) {
 float float0 = zombieSound.radius();
 DebugLog.log(DebugType.Sound, "sound: sending zombie sound " + zombieSound);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.isFullyConnected() &&
 udpConnection.RelevantTo(zombie0.getX(), zombie0.getY(), float0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ZombieSound.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(zombie0.OnlineID);
 byteBufferWriter.putByte((byte)zombieSound.ordinal());
 PacketTypes.PacketType.ZombieSound.send(udpConnection);
 }
 }
}

static void receiveZombieHelmetFalling(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 short short0 = byteBuffer.getShort();
 std::string string = GameWindow.ReadString(byteBuffer);
 IsoZombie zombie0 = ServerMap.instance.ZombieMap.get(short0);
 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (player0 != nullptr && zombie0 != nullptr) {
 zombie0.serverRemoveItemFromZombie(string);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection0);
 if (player1 != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.ZombieHelmetFalling.doPacket(
 byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.ZombieHelmetFalling.send(udpConnection1);
 } catch (Throwable throwable) {
 udpConnection0.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
}

static void receivePlayerAttachedItem(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 std::string string0 = GameWindow.ReadString(byteBuffer);
 bool boolean0 = byteBuffer.get() == 1;
 InventoryItem item = nullptr;
 if (boolean0) {
 std::string string1 = GameWindow.ReadString(byteBuffer);
 item = InventoryItemFactory.CreateItem(string1);
 if (item.empty()) {
 return;
 }
 }

 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (player0 != nullptr) {
 player0.setAttachedItem(string0, item);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection0);
 if (player1 != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.PlayerAttachedItem.doPacket(
 byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 GameWindow.WriteString(byteBufferWriter.bb, string0);
 byteBufferWriter.putByte((byte)(boolean0 ? 1 : 0);
 if (boolean0) {
 GameWindow.WriteString(byteBufferWriter.bb, item.getFullType());
 }

 PacketTypes.PacketType.PlayerAttachedItem.send(udpConnection1);
 } catch (Throwable throwable) {
 udpConnection0.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
}

static void receiveSyncClothing(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 SyncClothingPacket syncClothingPacket = new SyncClothingPacket();
 syncClothingPacket.parse(byteBuffer, udpConnection0);
 if (syncClothingPacket.isConsistent()) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection0);
 if (player != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncClothing.doPacket(byteBufferWriter);
 syncClothingPacket.write(byteBufferWriter);
 PacketTypes.PacketType.SyncClothing.send(udpConnection1);
 }
 }
 }
 }
}

static void receiveHumanVisual(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 short short0 = byteBuffer.getShort();
 IsoPlayer player0 = IDToPlayerMap.get(short0);
 if (player0 != nullptr) {
 if (!udpConnection0.havePlayer(player0) {
 DebugLog.Network.warn("User " + udpConnection0.username +
 " sent HumanVisual packet for non owned player #" +
 player0.OnlineID);
 } else {
 try {
 player0.getHumanVisual().load(byteBuffer, 195);
 } catch (Throwable throwable0) {
 ExceptionLogger.logException(throwable0);
 return;
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection1);
 if (player1 != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.HumanVisual.doPacket(byteBufferWriter);

 try {
 byteBufferWriter.putShort(player0.OnlineID);
 player0.getHumanVisual().save(byteBufferWriter.bb);
 PacketTypes.PacketType.HumanVisual.send(udpConnection1);
 } catch (Throwable throwable1) {
 udpConnection1.cancelPacket();
 ExceptionLogger.logException(throwable1);
 }
 }
 }
 }
 }
 }
}

static void initClientCommandFilter() {
 std::string string0 =
 ServerOptions.getInstance().ClientCommandFilter.getValue();
 ccFilters.clear();
 String[] strings0 = string0.split(";");

 for (auto &string1 : strings0)
 if (!string1.empty() && string1.contains(".") &&
 (string1.startsWith("+") || string1.startsWith("-"))) {
 String[] strings1 = string1.split("\\.");
 if (strings1.length == 2) {
 std::string string2 = strings1[0].substring(1);
 std::string string3 = strings1[1];
 GameServer.CCFilter cCFilter = new GameServer.CCFilter();
 cCFilter.command = string3;
 cCFilter.allow = strings1[0].startsWith("+");
 cCFilter.next = ccFilters.get(string2);
 ccFilters.put(string2, cCFilter);
 }
 }
}
}

static void receiveClientCommand(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
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
 GameServer.CCFilter cCFilter = ccFilters.get(string0);
 if (cCFilter.empty() || cCFilter.passes(string1) {
 LoggerManager.getLogger("cmd").write(
 udpConnection.idStr + " \"" + player.username + "\" " + string0 +
 "." + string1 + " @ " + (int)player.getX() + "," +
 (int)player.getY() + "," + (int)player.getZ());
 }

 if (!"vehicle" == string0)
 || !"remove" == string1)
 || Core.bDebug
 || PlayerType.isPrivileged(udpConnection.accessLevel)
 || player.networkAI.isDismantleAllowed()) {
 LuaEventManager.triggerEvent("OnClientCommand", string0,
 string1, player, table);
 }
 }
}

static void receiveGlobalObjects(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
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

static IsoPlayer getPlayerByRealUserName(std::string_view string) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 IsoPlayer player = udpConnection.players[int1];
 if (player != nullptr && player.username == string) {
 return player;
 }
 }
 }

 return nullptr;
}

static IsoPlayer getPlayerByUserName(std::string_view string) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 IsoPlayer player = udpConnection.players[int1];
 if (player != nullptr && (player.getDisplayName() == string) ||
 player.getUsername() == string)) {
 return player;
 }
 }
 }

 return nullptr;
}

static IsoPlayer getPlayerByUserNameForCommand(std::string_view string) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 IsoPlayer player = udpConnection.players[int1];
 if (player != nullptr &&
 (player.getDisplayName().toLowerCase() == string.toLowerCase()) ||
 player.getDisplayName().toLowerCase().startsWith(
 string.toLowerCase()))) {
 return player;
 }
 }
 }

 return nullptr;
}

static UdpConnection getConnectionByPlayerOnlineID(short short0) {
 return udpEngine.getActiveConnection(IDToAddressMap.get(short0);
}

static UdpConnection getConnectionFromPlayer(IsoPlayer player) {
 long long0 = PlayerToAddressMap.get(player);
 return long0 = = nullptr ? nullptr : udpEngine.getActiveConnection(long0);
}

static void receiveRemoveBlood(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 square.removeBlood(false, boolean0);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int3);
 if (udpConnection0 != udpConnection1 &&
 udpConnection0.RelevantTo(int0, int1) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.RemoveBlood.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putBoolean(boolean0);
 PacketTypes.PacketType.RemoveBlood.send(udpConnection0);
 }
 }
 }
}

static void sendAddItemToContainer(ItemContainer container,
 InventoryItem item) {
 void *object = container.getParent();
 if (container.getContainingItem() != nullptr &&
 container.getContainingItem().getWorldItem() != nullptr) {
 object = container.getContainingItem().getWorldItem();
 }

 if (object.empty()) {
 DebugLog.General.error("container has no parent object");
 } else {
 IsoGridSquare square = ((IsoObject)object).getSquare();
 if (square.empty()) {
 DebugLog.General.error("container parent object has no square");
 } else {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(square.x, square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(
 byteBufferWriter);
 if (object instanceof IsoDeadBody) {
 byteBufferWriter.putShort((short)0);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).getStaticMovingObjectIndex());
 } else if (object instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putShort((short)1);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putInt(
 ((IsoWorldInventoryObject)object).getItem().id);
 } else if (object instanceof BaseVehicle) {
 byteBufferWriter.putShort((short)3);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putShort(((BaseVehicle)object).VehicleID);
 byteBufferWriter.putByte((byte)container.vehiclePart.getIndex());
 } else {
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).square.getObjects().indexOf(object);
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).getContainerIndex(container);
 }

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb, item);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(
 udpConnection);
 }
 }
 }
 }
}

static void sendRemoveItemFromContainer(ItemContainer container,
 InventoryItem item) {
 void *object = container.getParent();
 if (container.getContainingItem() != nullptr &&
 container.getContainingItem().getWorldItem() != nullptr) {
 object = container.getContainingItem().getWorldItem();
 }

 if (object.empty()) {
 DebugLog.log("sendRemoveItemFromContainer: o is nullptr");
 } else {
 IsoGridSquare square = ((IsoObject)object).getSquare();
 if (square.empty()) {
 DebugLog.log("sendRemoveItemFromContainer: square is nullptr");
 } else {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(square.x, square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RemoveInventoryItemFromContainer.doPacket(
 byteBufferWriter);
 if (object instanceof IsoDeadBody) {
 byteBufferWriter.putShort((short)0);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).getStaticMovingObjectIndex());
 byteBufferWriter.putInt(1);
 byteBufferWriter.putInt(item.id);
 } else if (object instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putShort((short)1);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putInt(
 ((IsoWorldInventoryObject)object).getItem().id);
 byteBufferWriter.putInt(1);
 byteBufferWriter.putInt(item.id);
 } else if (object instanceof BaseVehicle) {
 byteBufferWriter.putShort((short)3);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putShort(((BaseVehicle)object).VehicleID);
 byteBufferWriter.putByte((byte)container.vehiclePart.getIndex());
 byteBufferWriter.putInt(1);
 byteBufferWriter.putInt(item.id);
 } else {
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putInt(((IsoObject)object).square.getX());
 byteBufferWriter.putInt(((IsoObject)object).square.getY());
 byteBufferWriter.putInt(((IsoObject)object).square.getZ());
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).square.getObjects().indexOf(object);
 byteBufferWriter.putByte(
 (byte)((IsoObject)object).getContainerIndex(container);
 byteBufferWriter.putInt(1);
 byteBufferWriter.putInt(item.id);
 }

 PacketTypes.PacketType.RemoveInventoryItemFromContainer.send(
 udpConnection);
 }
 }
 }
 }
}

static void receiveRemoveInventoryItemFromContainer(
 ByteBuffer byteBuffer, UdpConnection udpConnection1, short var2) {
 alreadyRemoved.clear();
 ByteBufferReader byteBufferReader = new ByteBufferReader(byteBuffer);
 short short0 = byteBufferReader.getShort();
 int int0 = byteBufferReader.getInt();
 int int1 = byteBufferReader.getInt();
 int int2 = byteBufferReader.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square.empty()) {
 square = ServerMap.instance.getGridSquare(int0, int1, int2);
 }

 std::unordered_set hashSet = new HashSet();
 bool boolean0 = false;
 int int3 = 0;
 if (short0 == 0) {
 uint8_t byte0 = byteBufferReader.getByte();
 int3 = byteBuffer.getInt();
 if (square != nullptr && byte0 >= 0 &&
 byte0 < square.getStaticMovingObjects().size()) {
 IsoObject object0 = square.getStaticMovingObjects().get(byte0);
 if (object0 != nullptr && object0.getContainer() != nullptr) {
 for (int int4 = 0; int4 < int3; int4++) {
 int int5 = byteBufferReader.getInt();
 InventoryItem item0 = object0.getContainer().getItemWithID(int5);
 if (item0.empty()) {
 alreadyRemoved.add(int5);
 } else {
 object0.getContainer().Remove(item0);
 boolean0 = true;
 hashSet.add(item0.getFullType());
 }
 }

 object0.getContainer().setExplored(true);
 object0.getContainer().setHasBeenLooted(true);
 }
 }
 } else if (short0 == 1) {
 if (square != nullptr) {
 int int6 = byteBufferReader.getInt();
 int3 = byteBuffer.getInt();
 ItemContainer container0 = nullptr;

 for (int int7 = 0; int7 < square.getWorldObjects().size(); int7++) {
 IsoWorldInventoryObject worldInventoryObject =
 square.getWorldObjects().get(int7);
 if (worldInventoryObject != nullptr && worldInventoryObject.getItem()
 instanceof
 InventoryContainer && worldInventoryObject.getItem().id == int6) {
 container0 = ((InventoryContainer)worldInventoryObject.getItem())
 .getInventory();
 break;
 }
 }

 if (container0 != nullptr) {
 for (int int8 = 0; int8 < int3; int8++) {
 int int9 = byteBufferReader.getInt();
 InventoryItem item1 = container0.getItemWithID(int9);
 if (item1.empty()) {
 alreadyRemoved.add(int9);
 } else {
 container0.Remove(item1);
 hashSet.add(item1.getFullType());
 }
 }

 container0.setExplored(true);
 container0.setHasBeenLooted(true);
 }
 }
 } else if (short0 == 2) {
 uint8_t byte1 = byteBufferReader.getByte();
 uint8_t byte2 = byteBufferReader.getByte();
 int3 = byteBuffer.getInt();
 if (square != nullptr && byte1 >= 0 && byte1 < square.getObjects().size()) {
 IsoObject object1 = square.getObjects().get(byte1);
 ItemContainer container1 =
 object1 != nullptr ? object1.getContainerByIndex(byte2) : nullptr;
 if (container1 != nullptr) {
 for (int int10 = 0; int10 < int3; int10++) {
 int int11 = byteBufferReader.getInt();
 InventoryItem item2 = container1.getItemWithID(int11);
 if (item2.empty()) {
 alreadyRemoved.add(int11);
 } else {
 container1.Remove(item2);
 container1.setExplored(true);
 container1.setHasBeenLooted(true);
 boolean0 = true;
 hashSet.add(item2.getFullType());
 }
 }

 LuaManager.updateOverlaySprite(object1);
 }
 }
 } else if (short0 == 3) {
 short short1 = byteBufferReader.getShort();
 uint8_t byte3 = byteBufferReader.getByte();
 int3 = byteBuffer.getInt();
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short1);
 if (vehicle != nullptr) {
 VehiclePart part = vehicle == nullptr ? nullptr : vehicle.getPartByIndex(byte3);
 ItemContainer container2 = part == nullptr ? nullptr : part.getItemContainer();
 if (container2 != nullptr) {
 for (int int12 = 0; int12 < int3; int12++) {
 int int13 = byteBufferReader.getInt();
 InventoryItem item3 = container2.getItemWithID(int13);
 if (item3.empty()) {
 alreadyRemoved.add(int13);
 } else {
 container2.Remove(item3);
 container2.setExplored(true);
 container2.setHasBeenLooted(true);
 boolean0 = true;
 hashSet.add(item3.getFullType());
 }
 }
 }
 }
 }

 for (int int14 = 0; int14 < udpEngine.connections.size(); int14++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int14);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 square != nullptr && udpConnection0.RelevantTo(square.x, square.y) {
 byteBuffer.rewind();
 ByteBufferWriter byteBufferWriter0 = udpConnection0.startPacket();
 PacketTypes.PacketType.RemoveInventoryItemFromContainer.doPacket(
 byteBufferWriter0);
 byteBufferWriter0.bb.put(byteBuffer);
 PacketTypes.PacketType.RemoveInventoryItemFromContainer.send(
 udpConnection0);
 }
 }

 if (!alreadyRemoved.empty()) {
 ByteBufferWriter byteBufferWriter1 = udpConnection1.startPacket();
 PacketTypes.PacketType.RemoveContestedItemsFromInventory.doPacket(
 byteBufferWriter1);
 byteBufferWriter1.putInt(alreadyRemoved.size());

 for (int int15 = 0; int15 < alreadyRemoved.size(); int15++) {
 byteBufferWriter1.putInt(alreadyRemoved.get(int15);
 }

 PacketTypes.PacketType.RemoveContestedItemsFromInventory.send(
 udpConnection1);
 }

 alreadyRemoved.clear();
 LoggerManager.getLogger("item").write(
 udpConnection1.idStr + " \"" + udpConnection1.username +
 "\" container -" + int3 + " " + int0 + "," + int1 + "," + int2 + " " +
 hashSet.toString());
}

static void readItemStats(ByteBuffer byteBuffer, InventoryItem item) {
 int int0 = byteBuffer.getInt();
 float float0 = byteBuffer.getFloat();
 bool boolean0 = byteBuffer.get() == 1;
 item.setUses(int0);
 if (item instanceof DrainableComboItem) {
 ((DrainableComboItem)item).setDelta(float0);
 ((DrainableComboItem)item).updateWeight();
 }

 if (boolean0 && item instanceof Food food) {
 food.setHungChange(byteBuffer.getFloat());
 food.setCalories(byteBuffer.getFloat());
 food.setCarbohydrates(byteBuffer.getFloat());
 food.setLipids(byteBuffer.getFloat());
 food.setProteins(byteBuffer.getFloat());
 food.setThirstChange(byteBuffer.getFloat());
 food.setFluReduction(byteBuffer.getInt());
 food.setPainReduction(byteBuffer.getFloat());
 food.setEndChange(byteBuffer.getFloat());
 food.setReduceFoodSickness(byteBuffer.getInt());
 food.setStressChange(byteBuffer.getFloat());
 food.setFatigueChange(byteBuffer.getFloat());
 }
}

static void receiveItemStats(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 switch (short0) {
 case 0:
 uint8_t byte3 = byteBuffer.get();
 int int5 = byteBuffer.getInt();
 if (square != nullptr && byte3 >= 0 &&
 byte3 < square.getStaticMovingObjects().size()) {
 IsoMovingObject movingObject = square.getStaticMovingObjects().get(byte3);
 ItemContainer container2 = movingObject.getContainer();
 if (container2 != nullptr) {
 InventoryItem item2 = container2.getItemWithID(int5);
 if (item2 != nullptr) {
 readItemStats(byteBuffer, item2);
 }
 }
 }
 break;
 case 1:
 int int6 = byteBuffer.getInt();
 if (square != nullptr) {
 for (int int7 = 0; int7 < square.getWorldObjects().size(); int7++) {
 IsoWorldInventoryObject worldInventoryObject =
 square.getWorldObjects().get(int7);
 if (worldInventoryObject.getItem() != nullptr &&
 worldInventoryObject.getItem().id == int6) {
 readItemStats(byteBuffer, worldInventoryObject.getItem());
 break;
 }

 if (worldInventoryObject.getItem() instanceof InventoryContainer) {
 ItemContainer container3 =
 ((InventoryContainer)worldInventoryObject.getItem())
 .getInventory();
 InventoryItem item3 = container3.getItemWithID(int6);
 if (item3 != nullptr) {
 readItemStats(byteBuffer, item3);
 break;
 }
 }
 }
 }
 break;
 case 2:
 uint8_t byte1 = byteBuffer.get();
 uint8_t byte2 = byteBuffer.get();
 int int4 = byteBuffer.getInt();
 if (square != nullptr && byte1 >= 0 && byte1 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(byte1);
 ItemContainer container1 = object.getContainerByIndex(byte2);
 if (container1 != nullptr) {
 InventoryItem item1 = container1.getItemWithID(int4);
 if (item1 != nullptr) {
 readItemStats(byteBuffer, item1);
 }
 }
 }
 break;
 case 3:
 short short1 = byteBuffer.getShort();
 uint8_t byte0 = byteBuffer.get();
 int int3 = byteBuffer.getInt();
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short1);
 if (vehicle != nullptr) {
 VehiclePart part = vehicle.getPartByIndex(byte0);
 if (part != nullptr) {
 ItemContainer container0 = part.getItemContainer();
 if (container0 != nullptr) {
 InventoryItem item0 = container0.getItemWithID(int3);
 if (item0 != nullptr) {
 readItemStats(byteBuffer, item0);
 }
 }
 }
 }
 }

 for (int int8 = 0; int8 < udpEngine.connections.size(); int8++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int8);
 if (udpConnection0 != udpConnection1 &&
 udpConnection0.RelevantTo(int0, int1) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.ItemStats.doPacket(byteBufferWriter);
 byteBuffer.rewind();
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.ItemStats.send(udpConnection0);
 }
 }
}

static void receiveRequestItemsForContainer(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 ByteBufferReader byteBufferReader = new ByteBufferReader(byteBuffer);
 short short0 = byteBuffer.getShort();
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBufferReader.getInt();
 int int1 = byteBufferReader.getInt();
 int int2 = byteBufferReader.getInt();
 short short1 = byteBufferReader.getShort();
 uint8_t byte0 = -1;
 uint8_t byte1 = -1;
 int int3 = 0;
 short short2 = 0;
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 IsoObject object = nullptr;
 ItemContainer container = nullptr;
 if (short1 == 2) {
 byte0 = byteBufferReader.getByte();
 byte1 = byteBufferReader.getByte();
 if (square != nullptr && byte0 >= 0 && byte0 < square.getObjects().size()) {
 object = square.getObjects().get(byte0);
 if (object != nullptr) {
 container = object.getContainerByIndex(byte1);
 if (container.empty() || container.isExplored()) {
 return;
 }
 }
 }
 } else if (short1 == 3) {
 short2 = byteBufferReader.getShort();
 byte1 = byteBufferReader.getByte();
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short2);
 if (vehicle != nullptr) {
 VehiclePart part = vehicle.getPartByIndex(byte1);
 container = part.empty() ? nullptr : part.getItemContainer();
 if (container.empty() || container.isExplored()) {
 return;
 }
 }
 } else if (short1 == 1) {
 int3 = byteBufferReader.getInt();

 for (int int4 = 0; int4 < square.getWorldObjects().size(); int4++) {
 IsoWorldInventoryObject worldInventoryObject =
 square.getWorldObjects().get(int4);
 if (worldInventoryObject != nullptr && worldInventoryObject.getItem()
 instanceof
 InventoryContainer && worldInventoryObject.getItem().id == int3) {
 container =
 ((InventoryContainer)worldInventoryObject.getItem()).getInventory();
 break;
 }
 }
 } else if (short1 == 0) {
 byte0 = byteBufferReader.getByte();
 if (square != nullptr && byte0 >= 0 &&
 byte0 < square.getStaticMovingObjects().size()) {
 object = square.getStaticMovingObjects().get(byte0);
 if (object != nullptr && object.getContainer() != nullptr) {
 if (object.getContainer().isExplored()) {
 return;
 }

 container = object.getContainer();
 }
 }
 }

 if (container != nullptr && !container.isExplored()) {
 container.setExplored(true);
 int int5 = container.Items.size();
 ItemPickerJava.fillContainer(container, IDToPlayerMap.get(short0);
 if (int5 != container.Items.size()) {
 for (int int6 = 0; int6 < udpEngine.connections.size(); int6++) {
 UdpConnection udpConnection = udpEngine.connections.get(int6);
 if (udpConnection.RelevantTo(square.x, square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(
 byteBufferWriter);
 byteBufferWriter.putShort(short1);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 if (short1 == 0) {
 byteBufferWriter.putByte(byte0);
 } else if (short1 == 1) {
 byteBufferWriter.putInt(int3);
 } else if (short1 == 3) {
 byteBufferWriter.putShort(short2);
 byteBufferWriter.putByte(byte1);
 } else {
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putByte(byte1);
 }

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb,
 container.getItems(), nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(
 udpConnection);
 }
 }
 }
 }
}

static void sendItemsInContainer(IsoObject object, ItemContainer container) {
 if (udpEngine != nullptr) {
 if (container.empty()) {
 DebugLog.log("sendItemsInContainer: container is nullptr");
 } else {
 if (object instanceof IsoWorldInventoryObject worldInventoryObject) {
 if (!(worldInventoryObject.getItem() instanceof InventoryContainer) {
 DebugLog.log("sendItemsInContainer: IsoWorldInventoryObject item "
 "isn't a container");
 return;
 }

 InventoryContainer inventoryContainer =
 (InventoryContainer)worldInventoryObject.getItem();
 if (inventoryContainer.getInventory() != container) {
 DebugLog.log("sendItemsInContainer: wrong container for "
 "IsoWorldInventoryObject");
 return;
 }
 } else if (object instanceof BaseVehicle) {
 if (container.vehiclePart.empty() ||
 container.vehiclePart.getItemContainer() != container ||
 container.vehiclePart.getVehicle() != object) {
 DebugLog.log("sendItemsInContainer: wrong container for BaseVehicle");
 return;
 }
 } else if (object instanceof IsoDeadBody) {
 if (container != object.getContainer()) {
 DebugLog.log("sendItemsInContainer: wrong container for IsoDeadBody");
 return;
 }
 } else if (object.getContainerIndex(container) == -1) {
 DebugLog.log("sendItemsInContainer: wrong container for IsoObject");
 return;
 }

 if (object != nullptr && container != nullptr &&
 !container.getItems().empty()) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(object.square.x, object.square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(
 byteBufferWriter);
 if (object instanceof IsoDeadBody) {
 byteBufferWriter.putShort((short)0);
 } else if (object instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putShort((short)1);
 } else if (object instanceof BaseVehicle) {
 byteBufferWriter.putShort((short)3);
 } else {
 byteBufferWriter.putShort((short)2);
 }

 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 if (object instanceof IsoDeadBody) {
 byteBufferWriter.putByte(
 (byte)object.getStaticMovingObjectIndex());
 } else if (object instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putInt(
 ((IsoWorldInventoryObject)object).getItem().id);
 } else if (object instanceof BaseVehicle) {
 byteBufferWriter.putShort(((BaseVehicle)object).VehicleID);
 byteBufferWriter.putByte((byte)container.vehiclePart.getIndex());
 } else {
 byteBufferWriter.putByte((byte)object.getObjectIndex());
 byteBufferWriter.putByte(
 (byte)object.getContainerIndex(container);
 }

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb,
 container.getItems(), nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(
 udpConnection);
 }
 }
 }
 }
 }
}

static void logDupeItem(UdpConnection udpConnection,
 std::string_view string1) {
 IsoPlayer player = nullptr;

 for (int int0 = 0; int0 < Players.size(); int0++) {
 if (udpConnection.username == Players.get(int0).username) {
 player = Players.get(int0);
 break;
 }
 }

 std::string string0 = "";
 if (player != nullptr) {
 string0 = LoggerManager.getPlayerCoords(player);
 LoggerManager.getLogger("user").write(
 "Error: Dupe item ID for " + player.getDisplayName() + " " + string0);
 }

 ServerWorldDatabase.instance.addUserlog(udpConnection.username,
 Userlog.UserlogType.DupeItem, string1,
 GameServer.class.getSimpleName(), 1);
}

static void receiveAddInventoryItemToContainer(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 ByteBufferReader byteBufferReader = new ByteBufferReader(byteBuffer);
 short short0 = byteBufferReader.getShort();
 int int0 = byteBufferReader.getInt();
 int int1 = byteBufferReader.getInt();
 int int2 = byteBufferReader.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 std::unordered_set hashSet = new HashSet();
 uint8_t byte0 = 0;
 if (square.empty()) {
 DebugLog.log("ERROR sendItemsToContainer square is nullptr");
 } else {
 ItemContainer container = nullptr;
 IsoObject object0 = nullptr;
 if (short0 == 0) {
 uint8_t byte1 = byteBufferReader.getByte();
 if (byte1 < 0 || byte1 >= square.getStaticMovingObjects().size()) {
 DebugLog.log("ERROR sendItemsToContainer invalid corpse index");
 return;
 }

 IsoObject object1 = square.getStaticMovingObjects().get(byte1);
 if (object1 != nullptr && object1.getContainer() != nullptr) {
 container = object1.getContainer();
 }
 } else if (short0 == 1) {
 int int3 = byteBufferReader.getInt();

 for (int int4 = 0; int4 < square.getWorldObjects().size(); int4++) {
 IsoWorldInventoryObject worldInventoryObject =
 square.getWorldObjects().get(int4);
 if (worldInventoryObject != nullptr && worldInventoryObject.getItem()
 instanceof
 InventoryContainer && worldInventoryObject.getItem().id == int3) {
 container = ((InventoryContainer)worldInventoryObject.getItem())
 .getInventory();
 break;
 }
 }

 if (container.empty()) {
 DebugLog.log(
 "ERROR sendItemsToContainer can't find world item with id=" + int3);
 return;
 }
 } else if (short0 == 2) {
 uint8_t byte2 = byteBufferReader.getByte();
 uint8_t byte3 = byteBufferReader.getByte();
 if (byte2 < 0 || byte2 >= square.getObjects().size()) {
 DebugLog.log("ERROR sendItemsToContainer invalid object index");

 for (int int5 = 0; int5 < square.getObjects().size(); int5++) {
 if (square.getObjects().get(int5).getContainer() != nullptr) {
 byte2 = (byte)int5;
 byte3 = 0;
 break;
 }
 }

 if (byte2 == -1) {
 return;
 }
 }

 object0 = square.getObjects().get(byte2);
 container =
 object0 != nullptr ? object0.getContainerByIndex(byte3) : nullptr;
 } else if (short0 == 3) {
 short short1 = byteBufferReader.getShort();
 uint8_t byte4 = byteBufferReader.getByte();
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short1);
 if (vehicle.empty()) {
 DebugLog.log("ERROR sendItemsToContainer invalid vehicle id");
 return;
 }

 VehiclePart part = vehicle.getPartByIndex(byte4);
 container = part.empty() ? nullptr : part.getItemContainer();
 }

 if (container != nullptr) {
 try {
 std::vector arrayList =
 CompressIdenticalItems.load(byteBufferReader.bb, 195, nullptr, nullptr);

 for (int int6 = 0; int6 < arrayList.size(); int6++) {
 InventoryItem item = (InventoryItem)arrayList.get(int6);
 if (item != nullptr) {
 if (container.containsID(item.id) {
 System.out.println("Error: Dupe item ID for " +
 udpConnection0.username);
 logDupeItem(udpConnection0, item.getDisplayName());
 } else {
 container.addItem(item);
 container.setExplored(true);
 hashSet.add(item.getFullType());
 if (object0 instanceof IsoMannequin) {
 ((IsoMannequin)object0).wearItem(item, nullptr);
 }
 }
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (object0 != nullptr) {
 LuaManager.updateOverlaySprite(object0);
 if ("campfire" == container.getType())) {
 object0.sendObjectChange("container.customTemperature");
 }
 }
 }
 }

 for (int int7 = 0; int7 < udpEngine.connections.size(); int7++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int7);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.RelevantTo(square.x, square.y) {
 byteBuffer.rewind();
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(
 byteBufferWriter);
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.AddInventoryItemToContainer.send(udpConnection1);
 }
 }

 LoggerManager.getLogger("item").write(
 udpConnection0.idStr + " \"" + udpConnection0.username +
 "\" container +" + byte0 + " " + int0 + "," + int1 + "," + int2 + " " +
 hashSet.toString());
}

static void addConnection(UdpConnection udpConnection) {
 { std::lock_guard<std::mutex> __sync_lock__(MainLoopNetDataHighPriorityQ_mutex);
 MainLoopNetDataHighPriorityQ.add(
 new GameServer.DelayedConnection(udpConnection, true);
 }
}

static void addDisconnect(UdpConnection udpConnection) {
 { std::lock_guard<std::mutex> __sync_lock__(MainLoopNetDataHighPriorityQ_mutex);
 MainLoopNetDataHighPriorityQ.add(
 new GameServer.DelayedConnection(udpConnection, false);
 }
}

static void disconnectPlayer(IsoPlayer player0, UdpConnection udpConnection0) {
 if (player0 != nullptr) {
 SafetySystemManager.storeSafety(player0);
 ChatServer.getInstance().disconnectPlayer(player0.getOnlineID());
 if (player0.getVehicle() != nullptr) {
 VehiclesDB2.instance.updateVehicleAndTrailer(player0.getVehicle());
 if (player0.getVehicle().isDriver(player0) &&
 player0.getVehicle().isNetPlayerId(player0.getOnlineID())) {
 player0.getVehicle().setNetPlayerAuthorization(
 BaseVehicle.Authorization.Server, -1);
 player0.getVehicle().getController().clientForce = 0.0F;
 player0.getVehicle().jniLinearVelocity.set(0.0F, 0.0F, 0.0F);
 }

 int int0 = player0.getVehicle().getSeat(player0);
 if (int0 != -1) {
 player0.getVehicle().clearPassenger(int0);
 }
 }

 if (!player0.isDead()) {
 ServerWorldDatabase.instance.saveTransactionID(
 player0.username, player0.getTransactionID());
 }

 NetworkZombieManager.getInstance().clearTargetAuth(udpConnection0, player0);
 player0.removeFromWorld();
 player0.removeFromSquare();
 PlayerToAddressMap.remove(player0);
 IDToAddressMap.remove(player0.OnlineID);
 IDToPlayerMap.remove(player0.OnlineID);
 Players.remove(player0);
 SafeHouse.updateSafehousePlayersConnected();
 SafeHouse safeHouse = SafeHouse.hasSafehouse(player0);
 if (safeHouse != nullptr && safeHouse.isOwner(player0) {
 for (IsoPlayer player1 : IDToPlayerMap.values()) {
 safeHouse.checkTrespass(player1);
 }
 }

 udpConnection0.usernames[player0.PlayerIndex] = nullptr;
 udpConnection0.players[player0.PlayerIndex] = nullptr;
 udpConnection0.playerIDs[player0.PlayerIndex] = -1;
 udpConnection0.ReleventPos[player0.PlayerIndex] = nullptr;
 udpConnection0.connectArea[player0.PlayerIndex] = nullptr;

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int1);
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.PlayerTimeout.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 PacketTypes.PacketType.PlayerTimeout.send(udpConnection1);
 }

 ServerLOS.instance.removePlayer(player0);
 ZombiePopulationManager.instance.updateLoadedAreas();
 DebugLog.log(DebugType.Network, "Disconnected player \"" +
 player0.getDisplayName() + "\" " +
 udpConnection0.idStr);
 LoggerManager.getLogger("user").write(
 udpConnection0.idStr + " \"" + player0.getUsername() +
 "\" disconnected player " + LoggerManager.getPlayerCoords(player0);
 }
}

static void heartBeat() { count++; }

static short getFreeSlot() {
 for (short short0 = 0; short0 < udpEngine.getMaxConnections(); short0++) {
 if (SlotToConnection[short0] == nullptr) {
 return short0;
 }
 }

 return -1;
}

static void receiveClientConnect(UdpConnection udpConnection,
 ServerWorldDatabase.LogonResult logonResult) {
 ConnectionManager.log("receive-packet", "client-connect", udpConnection);
 short short0 = getFreeSlot();
 short short1 = (short)(short0 * 4);
 if (udpConnection.playerDownloadServer != nullptr) {
 try {
 IDToAddressMap.put(short1, udpConnection.getConnectedGUID());
 udpConnection.playerDownloadServer.destroy();
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 playerToCoordsMap.put(short1, std::make_unique<Vector2>());
 playerMovedToFastMap.put(short1, 0);
 SlotToConnection[short0] = udpConnection;
 udpConnection.playerIDs[0] = short1;
 IDToAddressMap.put(short1, udpConnection.getConnectedGUID());
 udpConnection.playerDownloadServer = new PlayerDownloadServer(udpConnection);
 DebugLog.log(DebugType.Network, "Connected new client " +
 udpConnection.username + " ID # " +
 short1);
 udpConnection.playerDownloadServer.startConnectionTest();
 KahluaTable table = SpawnPoints.instance.getSpawnRegions();

 for (int int0 = 1; int0 < table.size() + 1; int0++) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SpawnRegion.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);

 try {
 ((KahluaTable)table.rawget(int0).save(byteBufferWriter.bb);
 PacketTypes.PacketType.SpawnRegion.send(udpConnection);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 RequestDataPacket requestDataPacket = new RequestDataPacket();
 requestDataPacket.sendConnectingDetails(udpConnection, logonResult);
}

static void receiveReplaceOnCooked(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 ByteBufferReader byteBufferReader = new ByteBufferReader(byteBuffer);
 int int0 = byteBufferReader.getInt();
 int int1 = byteBufferReader.getInt();
 int int2 = byteBufferReader.getInt();
 uint8_t byte0 = byteBufferReader.getByte();
 uint8_t byte1 = byteBufferReader.getByte();
 int int3 = byteBufferReader.getInt();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 if (byte0 >= 0 && byte0 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(byte0);
 if (object != nullptr) {
 ItemContainer container = object.getContainerByIndex(byte1);
 if (container != nullptr) {
 InventoryItem item0 = container.getItemWithID(int3);
 if (item0 != nullptr) {
 Food food = Type.tryCastTo(item0, Food.class);
 if (food != nullptr) {
 if (food.getReplaceOnCooked() != nullptr && !food.isRotten()) {
 for (int int4 = 0; int4 < food.getReplaceOnCooked().size();
 int4++) {
 InventoryItem item1 =
 container.AddItem(food.getReplaceOnCooked().get(int4);
 if (item1 != nullptr) {
 item1.copyConditionModData(food);
 if (item1 instanceof Food && food instanceof Food) {
 }

 if (item1 instanceof Food &&
 ((Food)item1).isBadInMicrowave() &&
 container.isMicrowave()) {
 item1.setUnhappyChange(5.0F);
 item1.setBoredomChange(5.0F);
 ((Food)item1).setCookedInMicrowave(true);
 }

 sendAddItemToContainer(container, item1);
 }
 }

 sendRemoveItemFromContainer(container, food);
 container.Remove(food);
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(food);
 }
 }
 }
 }
 }
 }
 }
}

static void receivePlayerDataRequest(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 PlayerDataRequestPacket playerDataRequestPacket =
 new PlayerDataRequestPacket();
 playerDataRequestPacket.parse(byteBuffer, udpConnection);
 if (playerDataRequestPacket.isConsistent()) {
 playerDataRequestPacket.process(udpConnection);
 }
}

static void receiveRequestData(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 RequestDataPacket requestDataPacket = new RequestDataPacket();
 requestDataPacket.parse(byteBuffer, udpConnection);
 requestDataPacket.processServer(PacketTypes.PacketType.RequestData,
 udpConnection);
}

static void sendMetaGrid(int int1, int int0, int int2,
 UdpConnection udpConnection) {
 IsoMetaGrid metaGrid = IsoWorld.instance.MetaGrid;
 if (int1 >= metaGrid.getMinX() && int1 <= metaGrid.getMaxX() &&
 int0 >= metaGrid.getMinY() && int0 <= metaGrid.getMaxY()) {
 IsoMetaCell metaCell = metaGrid.getCellData(int1, int0);
 if (metaCell.info != nullptr && int2 >= 0 &&
 int2 < metaCell.info.RoomList.size()) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.MetaGrid.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)int1);
 byteBufferWriter.putShort((short)int0);
 byteBufferWriter.putShort((short)int2);
 byteBufferWriter.putBoolean(
 metaCell.info.getRoom(int2).def.bLightsActive);
 PacketTypes.PacketType.MetaGrid.send(udpConnection);
 }
 }
}

static void sendMetaGrid(int int1, int int2, int int3) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendMetaGrid(int1, int2, int3, udpConnection);
 }
}

static void preventIndoorZombies(int int0, int int1, int int2) {
 RoomDef roomDef = IsoWorld.instance.MetaGrid.getRoomAt(int0, int1, int2);
 if (roomDef != nullptr) {
 bool boolean0 = isSpawnBuilding(roomDef.getBuilding());
 roomDef.getBuilding().setAllExplored(true);
 roomDef.getBuilding().setAlarmed(false);
 std::vector arrayList = IsoWorld.instance.CurrentCell.getZombieList();

 for (int int3 = 0; int3 < arrayList.size(); int3++) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(int3);
 if ((boolean0 || zombie0.bIndoorZombie) &&
 zombie0.getSquare() != nullptr &&
 zombie0.getSquare().getRoom() != nullptr &&
 zombie0.getSquare().getRoom().def.building == roomDef.getBuilding()) {
 VirtualZombieManager.instance.removeZombieFromWorld(zombie0);
 if (int3 >= arrayList.size() || arrayList.get(int3) != zombie0) {
 int3--;
 }
 }
 }
 }
}

static void receivePlayerConnect(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 std::string_view string0) {
 ConnectionManager.log("receive-packet", "player-connect", udpConnection0);
 DebugLog.General.println("User:'" + string0 + "' ip:" + udpConnection0.ip +
 " is trying to connect");
 uint8_t byte0 = byteBuffer.get();
 if (byte0 >= 0 && byte0 < 4 && udpConnection0.players[byte0] == nullptr) {
 uint8_t byte1 = (byte)Math.min(20, byteBuffer.get());
 udpConnection0.ReleventRange = (byte)(byte1 / 2 + 2);
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 udpConnection0.ReleventPos[byte0].x = float0;
 udpConnection0.ReleventPos[byte0].y = float1;
 udpConnection0.ReleventPos[byte0].z = float2;
 udpConnection0.connectArea[byte0] = nullptr;
 udpConnection0.ChunkGridWidth = byte1;
 udpConnection0.loadedCells[byte0] =
 new ClientServerMap(byte0, (int)float0, (int)float1, byte1);
 SurvivorDesc survivorDesc = SurvivorFactory.CreateSurvivor();

 try {
 survivorDesc.load(byteBuffer, 195, nullptr);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }

 IsoPlayer player0 = new IsoPlayer(nullptr, survivorDesc, (int)float0,
 (int)float1, (int)float2);
 player0.realx = float0;
 player0.realy = float1;
 player0.realz = (byte)float2;
 player0.PlayerIndex = byte0;
 player0.OnlineChunkGridWidth = byte1;
 Players.add(player0);
 player0.bRemote = true;

 try {
 player0.getHumanVisual().load(byteBuffer, 195);
 player0.getItemVisuals().load(byteBuffer, 195);
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }

 short short0 = udpConnection0.playerIDs[byte0];
 IDToPlayerMap.put(short0, player0);
 udpConnection0.players[byte0] = player0;
 PlayerToAddressMap.put(player0, udpConnection0.getConnectedGUID());
 player0.setOnlineID(short0);

 try {
 player0.getXp().load(byteBuffer, 195);
 } catch (IOException iOException2) {
 iOException2.printStackTrace();
 }

 player0.setAllChatMuted(byteBuffer.get() == 1);
 udpConnection0.allChatMuted = player0.isAllChatMuted();
 player0.setTagPrefix(GameWindow.ReadString(byteBuffer);
 player0.setTagColor(new ColorInfo(byteBuffer.getFloat(),
 byteBuffer.getFloat(),
 byteBuffer.getFloat(), 1.0F);
 player0.setTransactionID(byteBuffer.getInt());
 player0.setHoursSurvived(byteBuffer.getDouble());
 player0.setZombieKills(byteBuffer.getInt());
 player0.setDisplayName(GameWindow.ReadString(byteBuffer);
 player0.setSpeakColour(new Color(byteBuffer.getFloat(),
 byteBuffer.getFloat(),
 byteBuffer.getFloat(), 1.0F);
 player0.showTag = byteBuffer.get() == 1;
 player0.factionPvp = byteBuffer.get() == 1;
 if (SteamUtils.isSteamModeEnabled()) {
 player0.setSteamID(udpConnection0.steamID);
 std::string string1 = GameWindow.ReadStringUTF(byteBuffer);
 SteamGameServer.BUpdateUserData(udpConnection0.steamID,
 udpConnection0.username, 0);
 }

 uint8_t byte2 = byteBuffer.get();
 void *object = nullptr;
 if (byte2 == 1) {
 try {
 object = InventoryItem.loadItem(byteBuffer, 195);
 } catch (IOException iOException3) {
 iOException3.printStackTrace();
 return;
 }

 if (object.empty()) {
 LoggerManager.getLogger("user").write(udpConnection0.idStr +
 " equipped unknown item");
 return;
 }

 player0.setPrimaryHandItem((InventoryItem)object);
 }

 object = nullptr;
 uint8_t byte3 = byteBuffer.get();
 if (byte3 == 2) {
 player0.setSecondaryHandItem(player0.getPrimaryHandItem());
 }

 if (byte3 == 1) {
 try {
 object = InventoryItem.loadItem(byteBuffer, 195);
 } catch (IOException iOException4) {
 iOException4.printStackTrace();
 return;
 }

 if (object.empty()) {
 LoggerManager.getLogger("user").write(udpConnection0.idStr +
 " equipped unknown item");
 return;
 }

 player0.setSecondaryHandItem((InventoryItem)object);
 }

 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string2 = GameWindow.ReadString(byteBuffer);
 InventoryItem item =
 InventoryItemFactory.CreateItem(GameWindow.ReadString(byteBuffer);
 if (item != nullptr) {
 player0.setAttachedItem(string2, item);
 }
 }

 int int2 = byteBuffer.getInt();
 player0.remoteSneakLvl = int2;
 player0.username = string0;
 player0.accessLevel = PlayerType.toString(udpConnection0.accessLevel);
 if (!player0.accessLevel == "") && CoopSlave.instance.empty()) {
 player0.setGhostMode(true);
 player0.setInvisible(true);
 player0.setGodMod(true);
 }

 ChatServer.getInstance().initPlayer(player0.OnlineID);
 udpConnection0.setFullyConnected();
 sendWeather(udpConnection0);
 SafetySystemManager.restoreSafety(player0);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int3);
 sendPlayerConnect(player0, udpConnection1);
 }

 SyncInjuriesPacket syncInjuriesPacket = new SyncInjuriesPacket();

 for (IsoPlayer player1 : IDToPlayerMap.values()) {
 if (player1.getOnlineID() != player0.getOnlineID() && player1.isAlive()) {
 sendPlayerConnect(player1, udpConnection0);
 syncInjuriesPacket.set(player1);
 sendPlayerInjuries(udpConnection0, syncInjuriesPacket);
 }
 }

 udpConnection0.loadedCells[byte0].setLoaded();
 udpConnection0.loadedCells[byte0].sendPacket(udpConnection0);
 preventIndoorZombies((int)float0, (int)float1, (int)float2);
 ServerLOS.instance.addPlayer(player0);
 LoggerManager.getLogger("user").write(
 udpConnection0.idStr + " \"" + player0.username +
 "\" fully connected " + LoggerManager.getPlayerCoords(player0);

 try {
 for (NonPvpZone nonPvpZone : NonPvpZone.getAllZones()) {
 sendNonPvpZone(nonPvpZone, false, udpConnection0);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "Send non PVP zones",
 LogSeverity.Error);
 }
 }
}

static void receivePlayerSave(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 if ((Calendar.getInstance().getTimeInMillis() - previousSave) / 60000L >=
 0L) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 >= 0 && byte0 < 4) {
 short short0 = byteBuffer.getShort();
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 ServerMap.instance.saveZoneInsidePlayerInfluence(short0);
 }
 }
}

static void receiveSendPlayerProfile(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 ServerPlayerDB.getInstance().serverUpdateNetworkCharacter(byteBuffer,
 udpConnection);
}

static void receiveLoadPlayerProfile(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 ServerPlayerDB.getInstance().serverLoadNetworkCharacter(byteBuffer,
 udpConnection);
}

static void coopAccessGranted(int int0, UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddCoopPlayer.doPacket(byteBufferWriter);
 byteBufferWriter.putBoolean(true);
 byteBufferWriter.putByte((byte)int0);
 PacketTypes.PacketType.AddCoopPlayer.send(udpConnection);
}

static void coopAccessDenied(std::string_view string, int int0,
 UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddCoopPlayer.doPacket(byteBufferWriter);
 byteBufferWriter.putBoolean(false);
 byteBufferWriter.putByte((byte)int0);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.AddCoopPlayer.send(udpConnection);
}

static void receiveAddCoopPlayer(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 uint8_t byte0 = byteBuffer.get();
 uint8_t byte1 = byteBuffer.get();
 if (!ServerOptions.instance.AllowCoop.getValue() && byte1 != 0) {
 coopAccessDenied("Coop players not allowed", byte1, udpConnection0);
 } else if (byte1 >= 0 && byte1 < 4) {
 if (udpConnection0.players[byte1] != nullptr &&
 !udpConnection0.players[byte1].isDead()) {
 coopAccessDenied("Coop player " + (byte1 + 1) + "/4 already exists",
 byte1, udpConnection0);
 } else if (byte0 != 1) {
 if (byte0 == 2) {
 std::string string0 = udpConnection0.usernames[byte1];
 if (string0.empty()) {
 coopAccessDenied("Coop player login wasn't received", byte1,
 udpConnection0);
 } else {
 DebugLog.log("coop player=" + (byte1 + 1) + "/4 username=\"" +
 string0 + "\" player info received");
 receivePlayerConnect(byteBuffer, udpConnection0, string0);
 }
 }
 } else {
 std::string string1 = GameWindow.ReadStringUTF(byteBuffer);
 if (string1.empty()) {
 coopAccessDenied("No username given", byte1, udpConnection0);
 } else {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 if ((udpConnection1 != udpConnection0 || byte1 != int1) &&
 string1 == udpConnection1.usernames[int1])) {
 coopAccessDenied("User \"" + string1 + "\" already connected",
 byte1, udpConnection0);
 return;
 }
 }
 }

 DebugLog.log("coop player=" + (byte1 + 1) + "/4 username=\"" + string1 +
 "\" is joining");
 if (udpConnection0.players[byte1] != nullptr) {
 DebugLog.log("coop player=" + (byte1 + 1) + "/4 username=\"" +
 string1 + "\" is replacing dead player");
 short short0 = udpConnection0.players[byte1].OnlineID;
 disconnectPlayer(udpConnection0.players[byte1], udpConnection0);
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 udpConnection0.usernames[byte1] = string1;
 udpConnection0.ReleventPos[byte1] = new Vector3(float0, float1, 0.0F);
 udpConnection0.connectArea[byte1] = new Vector3(
 float0 / 10.0F, float1 / 10.0F, udpConnection0.ChunkGridWidth);
 udpConnection0.playerIDs[byte1] = short0;
 IDToAddressMap.put(short0, udpConnection0.getConnectedGUID());
 coopAccessGranted(byte1, udpConnection0);
 ZombiePopulationManager.instance.updateLoadedAreas();
 if (ChatServer.isInited()) {
 ChatServer.getInstance().initPlayer(short0);
 }
 } else if (getPlayerCount() >=
 ServerOptions.getInstance().getMaxPlayers()) {
 coopAccessDenied("Server is full", byte1, udpConnection0);
 } else {
 short short1 = -1;

 for (short short2 = 0; short2 < udpEngine.getMaxConnections();
 short2++) {
 if (SlotToConnection[short2] == udpConnection0) {
 short1 = short2;
 break;
 }
 }

 short short3 = (short)(short1 * 4 + byte1);
 DebugLog.log("coop player=" + (byte1 + 1) + "/4 username=\"" +
 string1 + "\" assigned id=" + short3);
 float float2 = byteBuffer.getFloat();
 float float3 = byteBuffer.getFloat();
 udpConnection0.usernames[byte1] = string1;
 udpConnection0.ReleventPos[byte1] = new Vector3(float2, float3, 0.0F);
 udpConnection0.playerIDs[byte1] = short3;
 udpConnection0.connectArea[byte1] = new Vector3(
 float2 / 10.0F, float3 / 10.0F, udpConnection0.ChunkGridWidth);
 IDToAddressMap.put(short3, udpConnection0.getConnectedGUID());
 coopAccessGranted(byte1, udpConnection0);
 ZombiePopulationManager.instance.updateLoadedAreas();
 }
 }
 }
 } else {
 coopAccessDenied("Invalid coop player index", byte1, udpConnection0);
 }
}

static void sendInitialWorldState(UdpConnection udpConnection) {
 if (RainManager.isRaining()) {
 sendStartRain(udpConnection);
 }

 VehicleManager.instance.serverSendInitialWorldState(udpConnection);

 try {
 if (!ClimateManager.getInstance().isUpdated()) {
 ClimateManager.getInstance().update();
 }

 ClimateManager.getInstance().sendInitialState(udpConnection);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
}

static void receiveObjectModData(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && int3 >= 0 && int3 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(int3);
 if (boolean0) {
 int int4 = object.getWaterAmount();

 try {
 object.getModData().load(byteBuffer, 195);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 if (int4 != object.getWaterAmount()) {
 LuaEventManager.triggerEvent("OnWaterAmountChange", object, int4);
 }
 } else if (object.hasModData()) {
 object.getModData().wipe();
 }

 for (int int5 = 0; int5 < udpEngine.connections.size(); int5++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int5);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 udpConnection0.RelevantTo(int0, int1) {
 sendObjectModData(object, udpConnection0);
 }
 }
 } else if (square != nullptr) {
 DebugLog.log("receiveObjectModData: index=" + int3 +
 " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 } else if (bDebug) {
 DebugLog.log("receiveObjectModData: sq is nullptr x,y,z=" + int0 + "," +
 int1 + "," + int2);
 }
}

static void sendObjectModData(IsoObject object, UdpConnection udpConnection) {
 if (object.getSquare() != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ObjectModData.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putInt(object.getSquare().getObjects().indexOf(object);
 if (object.getModData().empty()) {
 byteBufferWriter.putByte((byte)0);
 } else {
 byteBufferWriter.putByte((byte)1);

 try {
 object.getModData().save(byteBufferWriter.bb);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 PacketTypes.PacketType.ObjectModData.send(udpConnection);
 }
}

static void sendObjectModData(IsoObject object) {
 if (!bSoftReset && !bFastForward) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(object.getX(), object.getY())) {
 sendObjectModData(object, udpConnection);
 }
 }
 }
}

static void sendSlowFactor(IsoGameCharacter character) {
 if (character instanceof IsoPlayer) {
 if (PlayerToAddressMap.containsKey(character) {
 long long0 = PlayerToAddressMap.get((IsoPlayer)character);
 UdpConnection udpConnection = udpEngine.getActiveConnection(long0);
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SlowFactor.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)((IsoPlayer)character).PlayerIndex);
 byteBufferWriter.putFloat(character.getSlowTimer());
 byteBufferWriter.putFloat(character.getSlowFactor());
 PacketTypes.PacketType.SlowFactor.send(udpConnection);
 }
 }
 }
}

static void sendObjectChange(IsoObject object, std::string_view string,
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
 } else if (object instanceof IsoDeadBody) {
 byteBufferWriter.putByte((byte)4);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putInt(object.getStaticMovingObjectIndex());
 } else {
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putInt(object.getSquare().getObjects().indexOf(object);
 }

 byteBufferWriter.putUTF(string);
 object.saveChange(string, table, byteBufferWriter.bb);
 PacketTypes.PacketType.ObjectChange.send(udpConnection);
 }
}

static void sendObjectChange(IsoObject object, std::string_view string,
 KahluaTable table) {
 if (!bSoftReset) {
 if (object != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(object.getX(), object.getY())) {
 sendObjectChange(object, string, table, udpConnection);
 }
 }
 }
 }
}

static void sendObjectChange(IsoObject object0, std::string_view string,
 Object... objects) {
 if (!bSoftReset) {
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
}

static void updateHandEquips(UdpConnection udpConnection, IsoPlayer player) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Equip.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.OnlineID);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putByte(
 (byte)(player.getPrimaryHandItem() != nullptr ? 1 : 0);
 if (player.getPrimaryHandItem() != nullptr) {
 try {
 player.getPrimaryHandItem().saveWithSize(byteBufferWriter.bb, false);
 if (player.getPrimaryHandItem().getVisual() != nullptr) {
 byteBufferWriter.bb.put((byte)1);
 player.getPrimaryHandItem().getVisual().save(byteBufferWriter.bb);
 } else {
 byteBufferWriter.bb.put((byte)0);
 }
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }
 }

 PacketTypes.PacketType.Equip.send(udpConnection);
 byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Equip.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.OnlineID);
 byteBufferWriter.putByte((byte)1);
 if (player.getSecondaryHandItem() == player.getPrimaryHandItem() &&
 player.getSecondaryHandItem() != nullptr) {
 byteBufferWriter.putByte((byte)2);
 } else {
 byteBufferWriter.putByte(
 (byte)(player.getSecondaryHandItem() != nullptr ? 1 : 0);
 }

 if (player.getSecondaryHandItem() != nullptr) {
 try {
 player.getSecondaryHandItem().saveWithSize(byteBufferWriter.bb, false);
 if (player.getSecondaryHandItem().getVisual() != nullptr) {
 byteBufferWriter.bb.put((byte)1);
 player.getSecondaryHandItem().getVisual().save(byteBufferWriter.bb);
 } else {
 byteBufferWriter.bb.put((byte)0);
 }
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }

 PacketTypes.PacketType.Equip.send(udpConnection);
}

static void receiveSyncCustomLightSettings(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr && byte0 >= 0 && byte0 < square.getObjects().size()) {
 if (square.getObjects().get(byte0) instanceof IsoLightSwitch) {
 ((IsoLightSwitch)square.getObjects().get(byte0)
 .receiveSyncCustomizedSettings(byteBuffer, udpConnection);
 } else {
 DebugLog.log("Sync Lightswitch custom settings: found object not a "
 "instance of IsoLightSwitch, x,y,z=" +
 int0 + "," + int1 + "," + int2);
 }
 } else if (square != nullptr) {
 DebugLog.log("Sync Lightswitch custom settings: index=" + byte0 +
 " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 } else {
 DebugLog.log("Sync Lightswitch custom settings: sq is nullptr x,y,z=" +
 int0 + "," + int1 + "," + int2);
 }
}

static void sendAlarmClock_Player(short short0, int int0, bool boolean0,
 int int1, int int2, bool boolean1,
 UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncAlarmClock.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(AlarmClock.PacketPlayer);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putByte((byte)(boolean0 ? 1 : 0);
 if (!boolean0) {
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putByte((byte)(boolean1 ? 1 : 0);
 }

 PacketTypes.PacketType.SyncAlarmClock.send(udpConnection);
}

private
static void sendAlarmClock_World(int int0, int int1, int int2, int int3,
 boolean boolean0, int int4, int int5,
 boolean boolean1,
 UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncAlarmClock.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(AlarmClock.PacketWorld);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putByte((byte)(boolean0 ? 1 : 0);
 if (!boolean0) {
 byteBufferWriter.putInt(int4);
 byteBufferWriter.putInt(int5);
 byteBufferWriter.putByte((byte)(boolean1 ? 1 : 0);
 }

 PacketTypes.PacketType.SyncAlarmClock.send(udpConnection);
}

static void receiveSyncAlarmClock(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 short short0 = byteBuffer.getShort();
 if (short0 == AlarmClock.PacketPlayer) {
 short short1 = byteBuffer.getShort();
 int int0 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 int int1 = 0;
 int int2 = 0;
 bool boolean1 = false;
 if (!boolean0) {
 int1 = byteBuffer.getInt();
 int2 = byteBuffer.getInt();
 boolean1 = byteBuffer.get() == 1;
 }

 IsoPlayer player = getPlayerFromConnection(udpConnection0, short1);
 if (player != nullptr) {
 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int3);
 if (udpConnection1 != udpConnection0) {
 sendAlarmClock_Player(player.getOnlineID(), int0, boolean0, int1,
 int2, boolean1, udpConnection1);
 }
 }
 }
 } else if (short0 == AlarmClock.PacketWorld) {
 int int4 = byteBuffer.getInt();
 int int5 = byteBuffer.getInt();
 int int6 = byteBuffer.getInt();
 int int7 = byteBuffer.getInt();
 bool boolean2 = byteBuffer.get() == 1;
 int int8 = 0;
 int int9 = 0;
 bool boolean3 = false;
 if (!boolean2) {
 int8 = byteBuffer.getInt();
 int9 = byteBuffer.getInt();
 boolean3 = byteBuffer.get() == 1;
 }

 IsoGridSquare square = ServerMap.instance.getGridSquare(int4, int5, int6);
 if (square.empty()) {
 DebugLog.log("SyncAlarmClock: sq is nullptr x,y,z=" + int4 + "," + int5 +
 "," + int6);
 } else {
 AlarmClock alarmClock = nullptr;

 for (int int10 = 0; int10 < square.getWorldObjects().size(); int10++) {
 IsoWorldInventoryObject worldInventoryObject =
 square.getWorldObjects().get(int10);
 if (worldInventoryObject != nullptr && worldInventoryObject.getItem()
 instanceof
 AlarmClock && worldInventoryObject.getItem().id == int7) {
 alarmClock = (AlarmClock)worldInventoryObject.getItem();
 break;
 }
 }

 if (alarmClock.empty()) {
 DebugLog.log("SyncAlarmClock: AlarmClock is nullptr x,y,z=" + int4 +
 "," + int5 + "," + int6);
 } else {
 if (boolean2) {
 alarmClock.stopRinging();
 } else {
 alarmClock.setHour(int8);
 alarmClock.setMinute(int9);
 alarmClock.setAlarmSet(boolean3);
 }

 for (int int11 = 0; int11 < udpEngine.connections.size(); int11++) {
 UdpConnection udpConnection2 = udpEngine.connections.get(int11);
 if (udpConnection2 != udpConnection0) {
 sendAlarmClock_World(int4, int5, int6, int7, boolean2, int8, int9,
 boolean3, udpConnection2);
 }
 }
 }
 }
 }
}

static void receiveSyncIsoObject(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 if (DebugOptions.instance.Network.Server.SyncIsoObject.getValue()) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 uint8_t byte1 = byteBuffer.get();
 uint8_t byte2 = byteBuffer.get();
 if (byte1 == 1) {
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square != nullptr && byte0 >= 0 &&
 byte0 < square.getObjects().size()) {
 square.getObjects().get(byte0).syncIsoObject(true, byte2, udpConnection,
 byteBuffer);
 } else if (square != nullptr) {
 DebugLog.log("SyncIsoObject: index=" + byte0 +
 " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 } else {
 DebugLog.log("SyncIsoObject: sq is nullptr x,y,z=" + int0 + "," + int1 +
 "," + int2);
 }
 }
 }
}

static void receiveSyncIsoObjectReq(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 short short0 = byteBuffer.getShort();
 if (short0 <= 50 && short0 > 0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncIsoObjectReq.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);

 for (int int0 = 0; int0 < short0; int0++) {
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 IsoGridSquare square = ServerMap.instance.getGridSquare(int1, int2, int3);
 if (square != nullptr && byte0 >= 0 &&
 byte0 < square.getObjects().size()) {
 square.getObjects().get(byte0).syncIsoObjectSend(byteBufferWriter);
 } else if (square != nullptr) {
 byteBufferWriter.putInt(square.getX());
 byteBufferWriter.putInt(square.getY());
 byteBufferWriter.putInt(square.getZ());
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putByte((byte)0);
 } else {
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putByte((byte)2);
 byteBufferWriter.putByte((byte)0);
 }
 }

 PacketTypes.PacketType.SyncIsoObjectReq.send(udpConnection);
 }
}

static void receiveSyncObjects(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 short short0 = byteBuffer.getShort();
 if (short0 == 1) {
 SyncObjectChunkHashes(byteBuffer, udpConnection);
 } else if (short0 == 3) {
 SyncObjectsGridSquareRequest(byteBuffer, udpConnection);
 } else if (short0 == 5) {
 SyncObjectsRequest(byteBuffer, udpConnection);
 }
}

static void SyncObjectChunkHashes(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 short short0 = byteBuffer.getShort();
 if (short0 <= 10 && short0 > 0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)2);
 int int0 = byteBufferWriter.bb.position();
 byteBufferWriter.putShort((short)0);
 int int1 = 0;

 for (int int2 = 0; int2 < short0; int2++) {
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 long long0 = byteBuffer.getLong();
 IsoChunk chunk = ServerMap.instance.getChunk(int3, int4);
 if (chunk != nullptr) {
 int1++;
 byteBufferWriter.putShort((short)chunk.wx);
 byteBufferWriter.putShort((short)chunk.wy);
 byteBufferWriter.putLong(chunk.getHashCodeObjects());
 int int5 = byteBufferWriter.bb.position();
 byteBufferWriter.putShort((short)0);
 int int6 = 0;

 for (int int7 = int3 * 10; int7 < int3 * 10 + 10; int7++) {
 for (int int8 = int4 * 10; int8 < int4 * 10 + 10; int8++) {
 for (int int9 = 0; int9 <= 7; int9++) {
 IsoGridSquare square =
 ServerMap.instance.getGridSquare(int7, int8, int9);
 if (square.empty()) {
 break;
 }

 byteBufferWriter.putByte((byte)(square.getX() - chunk.wx * 10);
 byteBufferWriter.putByte((byte)(square.getY() - chunk.wy * 10);
 byteBufferWriter.putByte((byte)square.getZ());
 byteBufferWriter.putInt((int)square.getHashCodeObjects());
 int6++;
 }
 }
 }

 int int10 = byteBufferWriter.bb.position();
 byteBufferWriter.bb.position(int5);
 byteBufferWriter.putShort((short)int6);
 byteBufferWriter.bb.position(int10);
 }
 }

 int int11 = byteBufferWriter.bb.position();
 byteBufferWriter.bb.position(int0);
 byteBufferWriter.putShort((short)int1);
 byteBufferWriter.bb.position(int11);
 PacketTypes.PacketType.SyncObjects.send(udpConnection);
 }
}

static void SyncObjectChunkHashes(IsoChunk chunk, UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putShort((short)1);
 byteBufferWriter.putShort((short)chunk.wx);
 byteBufferWriter.putShort((short)chunk.wy);
 byteBufferWriter.putLong(chunk.getHashCodeObjects());
 int int0 = byteBufferWriter.bb.position();
 byteBufferWriter.putShort((short)0);
 int int1 = 0;

 for (int int2 = chunk.wx * 10; int2 < chunk.wx * 10 + 10; int2++) {
 for (int int3 = chunk.wy * 10; int3 < chunk.wy * 10 + 10; int3++) {
 for (int int4 = 0; int4 <= 7; int4++) {
 IsoGridSquare square =
 ServerMap.instance.getGridSquare(int2, int3, int4);
 if (square.empty()) {
 break;
 }

 byteBufferWriter.putByte((byte)(square.getX() - chunk.wx * 10);
 byteBufferWriter.putByte((byte)(square.getY() - chunk.wy * 10);
 byteBufferWriter.putByte((byte)square.getZ());
 byteBufferWriter.putInt((int)square.getHashCodeObjects());
 int1++;
 }
 }
 }

 int int5 = byteBufferWriter.bb.position();
 byteBufferWriter.bb.position(int0);
 byteBufferWriter.putShort((short)int1);
 byteBufferWriter.bb.position(int5);
 PacketTypes.PacketType.SyncObjects.send(udpConnection);
}

static void SyncObjectsGridSquareRequest(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 short short0 = byteBuffer.getShort();
 if (short0 <= 100 && short0 > 0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)4);
 int int0 = byteBufferWriter.bb.position();
 byteBufferWriter.putShort((short)0);
 int int1 = 0;

 for (int int2 = 0; int2 < short0; int2++) {
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 IsoGridSquare square =
 ServerMap.instance.getGridSquare(int3, int4, byte0);
 if (square != nullptr) {
 int1++;
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putInt(int4);
 byteBufferWriter.putByte((byte)byte0);
 byteBufferWriter.putByte((byte)square.getObjects().size());
 byteBufferWriter.putInt(0);
 int int5 = byteBufferWriter.bb.position();

 for (int int6 = 0; int6 < square.getObjects().size(); int6++) {
 byteBufferWriter.putLong(
 square.getObjects().get(int6).customHashCode());
 }

 int int7 = byteBufferWriter.bb.position();
 byteBufferWriter.bb.position(int5 - 4);
 byteBufferWriter.putInt(int7);
 byteBufferWriter.bb.position(int7);
 }
 }

 int int8 = byteBufferWriter.bb.position();
 byteBufferWriter.bb.position(int0);
 byteBufferWriter.putShort((short)int1);
 byteBufferWriter.bb.position(int8);
 PacketTypes.PacketType.SyncObjects.send(udpConnection);
 }
}

static void SyncObjectsRequest(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 short short0 = byteBuffer.getShort();
 if (short0 <= 100 && short0 > 0) {
 for (int int0 = 0; int0 < short0; int0++) {
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 long long0 = byteBuffer.getLong();
 IsoGridSquare square =
 ServerMap.instance.getGridSquare(int1, int2, byte0);
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 if (square.getObjects().get(int3).customHashCode() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncObjects.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)6);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putByte((byte)byte0);
 byteBufferWriter.putLong(long0);
 byteBufferWriter.putByte((byte)square.getObjects().size());

 for (int int4 = 0; int4 < square.getObjects().size(); int4++) {
 byteBufferWriter.putLong(
 square.getObjects().get(int4).customHashCode());
 }

 try {
 square.getObjects().get(int3).writeToRemoteBuffer(
 byteBufferWriter);
 } catch (Throwable throwable) {
 DebugLog.log("ERROR: GameServer.SyncObjectsRequest " +
 throwable.getMessage());
 udpConnection.cancelPacket();
 break;
 }

 PacketTypes.PacketType.SyncObjects.send(udpConnection);
 break;
 }
 }
 }
 }
 }
}

static void receiveSyncDoorKey(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 int int3 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && byte0 >= 0 && byte0 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(byte0);
 if (object instanceof IsoDoor door) {
 door.keyId = int3;

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int4);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncDoorKey.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.SyncDoorKey.send(udpConnection0);
 }
 }
 } else {
 DebugLog.log("SyncDoorKey: expected IsoDoor index=" + byte0 +
 " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 }
 } else if (square != nullptr) {
 DebugLog.log("SyncDoorKey: index=" + byte0 + " is invalid x,y,z=" + int0 +
 "," + int1 + "," + int2);
 } else {
 DebugLog.log("SyncDoorKey: sq is nullptr x,y,z=" + int0 + "," + int1 + "," +
 int2);
 }
}

static void receiveSyncThumpable(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 uint8_t byte0 = byteBuffer.get();
 int int3 = byteBuffer.getInt();
 uint8_t byte1 = byteBuffer.get();
 int int4 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && byte0 >= 0 && byte0 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(byte0);
 if (object instanceof IsoThumpable thumpable) {
 thumpable.lockedByCode = int3;
 thumpable.lockedByPadlock = byte1 == 1;
 thumpable.keyId = int4;

 for (int int5 = 0; int5 < udpEngine.connections.size(); int5++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int5);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncThumpable.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putByte(byte1);
 byteBufferWriter.putInt(int4);
 PacketTypes.PacketType.SyncThumpable.send(udpConnection0);
 }
 }
 } else {
 DebugLog.log("SyncThumpable: expected IsoThumpable index=" + byte0 +
 " is invalid x,y,z=" + int0 + "," + int1 + "," + int2);
 }
 } else if (square != nullptr) {
 DebugLog.log("SyncThumpable: index=" + byte0 + " is invalid x,y,z=" + int0 +
 "," + int1 + "," + int2);
 } else {
 DebugLog.log("SyncThumpable: sq is nullptr x,y,z=" + int0 + "," + int1 +
 "," + int2);
 }
}

static void receiveRemoveItemFromSquare(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && int3 >= 0 && int3 < square.getObjects().size()) {
 IsoObject object0 = square.getObjects().get(int3);
 if (!(object0 instanceof IsoWorldInventoryObject) {
 IsoRegions.setPreviousFlags(square);
 }

 DebugLog.log(DebugType.Objects, "object: removing " + object0 +
 " index=" + int3 + " " + int0 + "," +
 int1 + "," + int2);
 if (object0 instanceof IsoWorldInventoryObject) {
 LoggerManager.getLogger("item").write(
 udpConnection0.idStr + " \"" + udpConnection0.username +
 "\" floor -1 " + int0 + "," + int1 + "," + int2 + " [" +
 ((IsoWorldInventoryObject)object0).getItem().getFullType() + "]");
 } else {
 std::string string = object0.getName() != nullptr ? object0.getName()
 : object0.getObjectName();
 if (object0.getSprite() != nullptr &&
 object0.getSprite().getName() != nullptr) {
 string = string + " (" + object0.getSprite().getName() + ")";
 }

 LoggerManager.getLogger("map").write(
 udpConnection0.idStr + " \"" + udpConnection0.username +
 "\" removed " + string + " at " + int0 + "," + int1 + "," + int2);
 }

 if (object0.isTableSurface()) {
 for (int int4 = int3 + 1; int4 < square.getObjects().size(); int4++) {
 IsoObject object1 = square.getObjects().get(int4);
 if (object1.isTableTopObject() || object1.isTableSurface()) {
 object1.setRenderYOffset(object1.getRenderYOffset() -
 object0.getSurfaceOffset());
 }
 }
 }

 if (!(object0 instanceof IsoWorldInventoryObject) {
 LuaEventManager.triggerEvent("OnObjectAboutToBeRemoved", object0);
 }

 if (!square.getObjects().contains(object0) {
 throw IllegalArgumentException(
 "OnObjectAboutToBeRemoved not allowed to remove the object");
 }

 object0.removeFromWorld();
 object0.removeFromSquare();
 square.RecalcAllWithNeighbours(true);
 if (!(object0 instanceof IsoWorldInventoryObject) {
 IsoWorld.instance.CurrentCell.checkHaveRoof(int0, int1);
 MapCollisionData.instance.squareChanged(square);
 PolygonalMap2.instance.squareChanged(square);
 ServerMap.instance.physicsCheck(int0, int1);
 IsoRegions.squareChanged(square, true);
 IsoGenerator.updateGenerator(square);
 }

 for (int int5 = 0; int5 < udpEngine.connections.size(); int5++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int5);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.RemoveItemFromSquare.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.RemoveItemFromSquare.send(udpConnection1);
 }
 }
 }
}

static int RemoveItemFromMap(IsoObject object) {
 int int0 = object.getSquare().getX();
 int int1 = object.getSquare().getY();
 int int2 = object.getSquare().getZ();
 int int3 = object.getSquare().getObjects().indexOf(object);
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && !(object instanceof IsoWorldInventoryObject) {
 IsoRegions.setPreviousFlags(square);
 }

 LuaEventManager.triggerEvent("OnObjectAboutToBeRemoved", object);
 if (!object.getSquare().getObjects().contains(object) {
 throw IllegalArgumentException(
 "OnObjectAboutToBeRemoved not allowed to remove the object");
 } else {
 object.removeFromWorld();
 object.removeFromSquare();
 if (square != nullptr) {
 square.RecalcAllWithNeighbours(true);
 }

 if (!(object instanceof IsoWorldInventoryObject) {
 IsoWorld.instance.CurrentCell.checkHaveRoof(int0, int1);
 MapCollisionData.instance.squareChanged(square);
 PolygonalMap2.instance.squareChanged(square);
 ServerMap.instance.physicsCheck(int0, int1);
 IsoRegions.squareChanged(square, true);
 IsoGenerator.updateGenerator(square);
 }

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = udpEngine.connections.get(int4);
 if (udpConnection.RelevantTo(int0, int1) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RemoveItemFromSquare.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.RemoveItemFromSquare.send(udpConnection);
 }
 }

 return int3;
 }
}

static void sendBloodSplatter(HandWeapon weapon, float float0, float float1,
 float float2, Vector2 vector, bool boolean0,
 bool boolean1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.BloodSplatter.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(weapon != nullptr ? weapon.getType() : "");
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 byteBufferWriter.putFloat(vector.getX());
 byteBufferWriter.putFloat(vector.getY());
 byteBufferWriter.putByte((byte)(boolean0 ? 1 : 0);
 byteBufferWriter.putByte((byte)(boolean1 ? 1 : 0);
 uint8_t byte0 = 0;
 if (weapon != nullptr) {
 byte0 = (byte)Math.max(weapon.getSplatNumber(), 1);
 }

 byteBufferWriter.putByte(byte0);
 PacketTypes.PacketType.BloodSplatter.send(udpConnection);
 }
}

static void receiveAddItemToMap(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 IsoObject object = WorldItemTypes.createFromBuffer(byteBuffer);
 if (object instanceof IsoFire && ServerOptions.instance.NoFire.getValue()) {
 DebugLog.log("user \"" + udpConnection0.username +
 "\" tried to start a fire");
 } else {
 object.loadFromRemoteBuffer(byteBuffer);
 if (object.square != nullptr) {
 DebugLog.log(DebugType.Objects, "object: added " + object +
 " index=" + object.getObjectIndex() +
 " " + object.getX() + "," +
 object.getY() + "," + object.getZ());
 if (object instanceof IsoWorldInventoryObject) {
 LoggerManager.getLogger("item").write(
 udpConnection0.idStr + " \"" + udpConnection0.username +
 "\" floor +1 " + (int)object.getX() + "," + (int)object.getY() +
 "," + (int)object.getZ() + " [" +
 ((IsoWorldInventoryObject)object).getItem().getFullType() + "]");
 } else {
 std::string string = object.getName() != nullptr ? object.getName()
 : object.getObjectName();
 if (object.getSprite() != nullptr &&
 object.getSprite().getName() != nullptr) {
 string = string + " (" + object.getSprite().getName() + ")";
 }

 LoggerManager.getLogger("map").write(
 udpConnection0.idStr + " \"" + udpConnection0.username +
 "\" added " + string + " at " + object.getX() + "," +
 object.getY() + "," + object.getZ());
 }

 object.addToWorld();
 object.square.RecalcProperties();
 if (!(object instanceof IsoWorldInventoryObject) {
 object.square.restackSheetRope();
 IsoWorld.instance.CurrentCell.checkHaveRoof(object.square.getX(),
 object.square.getY());
 MapCollisionData.instance.squareChanged(object.square);
 PolygonalMap2.instance.squareChanged(object.square);
 ServerMap.instance.physicsCheck(object.square.x, object.square.y);
 IsoRegions.squareChanged(object.square);
 IsoGenerator.updateGenerator(object.square);
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection1.RelevantTo(object.square.x, object.square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.AddItemToMap.doPacket(byteBufferWriter);
 object.writeToRemoteBuffer(byteBufferWriter);
 PacketTypes.PacketType.AddItemToMap.send(udpConnection1);
 }
 }

 if (!(object instanceof IsoWorldInventoryObject) {
 LuaEventManager.triggerEvent("OnObjectAdded", object);
 } else {
 ((IsoWorldInventoryObject)object).dropTime =
 GameTime.getInstance().getWorldAgeHours();
 }
 } else if (bDebug) {
 DebugLog.log("AddItemToMap: sq is nullptr");
 }
 }
}

static void disconnect(UdpConnection udpConnection, std::string_view string) {
 if (udpConnection.playerDownloadServer != nullptr) {
 try {
 udpConnection.playerDownloadServer.destroy();
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 udpConnection.playerDownloadServer = nullptr;
 }

 RequestDataManager.getInstance().disconnect(udpConnection);

 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player = udpConnection.players[int0];
 if (player != nullptr) {
 ChatServer.getInstance().disconnectPlayer(udpConnection.playerIDs[int0]);
 disconnectPlayer(player, udpConnection);
 }

 udpConnection.usernames[int0] = nullptr;
 udpConnection.players[int0] = nullptr;
 udpConnection.playerIDs[int0] = -1;
 udpConnection.ReleventPos[int0] = nullptr;
 udpConnection.connectArea[int0] = nullptr;
 }

 for (int int1 = 0; int1 < udpEngine.getMaxConnections(); int1++) {
 if (SlotToConnection[int1] == udpConnection) {
 SlotToConnection[int1] = nullptr;
 }
 }

 Iterator iterator = IDToAddressMap.entrySet().iterator();

 while (iterator.hasNext()) {
 Entry entry = (Entry)iterator.next();
 if ((Long)entry.getValue() == udpConnection.getConnectedGUID()) {
 iterator.remove();
 }
 }

 if (!SteamUtils.isSteamModeEnabled()) {
 PublicServerUtil.updatePlayers();
 }

 if (CoopSlave.instance != nullptr && udpConnection.isCoopHost) {
 DebugLog.log("Host user disconnected, stopping the server");
 ServerMap.instance.QueueQuit();
 }

 if (bServer) {
 ConnectionManager.log("disconnect", string, udpConnection);
 }
}

static void addIncoming(short short0, ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 ZomboidNetData zomboidNetData = nullptr;
 if (byteBuffer.limit() > 2048) {
 zomboidNetData = ZomboidNetDataPool.instance.getLong(byteBuffer.limit());
 } else {
 zomboidNetData = ZomboidNetDataPool.instance.get();
 }

 zomboidNetData.read(short0, byteBuffer, udpConnection);
 if (zomboidNetData.type.empty()) {
 try {
 if (ServerOptions.instance.AntiCheatProtectionType13.getValue() &&
 PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection, String.valueOf((int)short0),
 "Type13", nullptr);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 } else {
 zomboidNetData.time = System.currentTimeMillis();
 if (zomboidNetData.type == PacketTypes.PacketType.PlayerUpdate ||
 zomboidNetData.type == PacketTypes.PacketType.PlayerUpdateReliable) {
 MainLoopPlayerUpdateQ.add(zomboidNetData);
 } else if (zomboidNetData.type !=
 PacketTypes.PacketType.VehiclesUnreliable &&
 zomboidNetData.type != PacketTypes.PacketType.Vehicles) {
 MainLoopNetDataHighPriorityQ.add(zomboidNetData);
 } else {
 uint8_t byte0 = zomboidNetData.buffer.get(0);
 if (byte0 == 9) {
 MainLoopNetDataQ.add(zomboidNetData);
 } else {
 MainLoopNetDataHighPriorityQ.add(zomboidNetData);
 }
 }
 }
}

static void smashWindow(IsoWindow window, int int1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(window.getX(), window.getY())) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SmashWindow.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(window.square.getX());
 byteBufferWriter.putInt(window.square.getY());
 byteBufferWriter.putInt(window.square.getZ());
 byteBufferWriter.putByte(
 (byte)window.square.getObjects().indexOf(window);
 byteBufferWriter.putByte((byte)int1);
 PacketTypes.PacketType.SmashWindow.send(udpConnection);
 }
 }
}

static void receiveHitCharacter(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 HitCharacterPacket hitCharacterPacket =
 HitCharacterPacket.process(byteBuffer);
 if (hitCharacterPacket != nullptr) {
 hitCharacterPacket.parse(byteBuffer, udpConnection);
 if (hitCharacterPacket.isConsistent() &&
 hitCharacterPacket.validate(udpConnection) {
 DebugLog.Damage.trace(hitCharacterPacket.getDescription());
 sendHitCharacter(hitCharacterPacket, udpConnection);
 hitCharacterPacket.tryProcess();
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(
 exception, "ReceiveHitCharacter: failed", LogSeverity.Error);
 }
}

static void sendHitCharacter(HitCharacterPacket hitCharacterPacket,
 UdpConnection udpConnection1) {
 DebugLog.Damage.trace(hitCharacterPacket.getDescription());

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() &&
 hitCharacterPacket.isRelevant(udpConnection0) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.HitCharacter.doPacket(byteBufferWriter);
 hitCharacterPacket.write(byteBufferWriter);
 PacketTypes.PacketType.HitCharacter.send(udpConnection0);
 }
 }
}

static void receiveZombieDeath(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 DeadZombiePacket deadZombiePacket = new DeadZombiePacket();
 deadZombiePacket.parse(byteBuffer, udpConnection);
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln("ReceiveZombieDeath: %s",
 deadZombiePacket.getDescription());
 }

 if (deadZombiePacket.isConsistent()) {
 if (deadZombiePacket.getZombie().isReanimatedPlayer()) {
 sendZombieDeath(deadZombiePacket.getZombie());
 } else {
 sendZombieDeath(deadZombiePacket);
 }

 deadZombiePacket.process();
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveZombieDeath: failed",
 LogSeverity.Error);
 }
}

static void sendZombieDeath(IsoZombie zombie0) {
 try {
 DeadZombiePacket deadZombiePacket = new DeadZombiePacket();
 deadZombiePacket.set(zombie0);
 sendZombieDeath(deadZombiePacket);
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "SendZombieDeath: failed",
 LogSeverity.Error);
 }
}

static void sendZombieDeath(DeadZombiePacket deadZombiePacket) {
 try {
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln("SendZombieDeath: %s",
 deadZombiePacket.getDescription());
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(deadZombiePacket.getZombie().getX(),
 deadZombiePacket.getZombie().getY())) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ZombieDeath.doPacket(byteBufferWriter);

 try {
 deadZombiePacket.write(byteBufferWriter);
 PacketTypes.PacketType.ZombieDeath.send(udpConnection);
 } catch (Exception exception0) {
 udpConnection.cancelPacket();
 DebugLog.Multiplayer.printException(
 exception0, "SendZombieDeath: failed", LogSeverity.Error);
 }
 }
 }
 } catch (Exception exception1) {
 DebugLog.Multiplayer.printException(exception1, "SendZombieDeath: failed",
 LogSeverity.Error);
 }
}

static void receivePlayerDeath(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 DeadPlayerPacket deadPlayerPacket = new DeadPlayerPacket();
 deadPlayerPacket.parse(byteBuffer, udpConnection);
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln("ReceivePlayerDeath: %s",
 deadPlayerPacket.getDescription());
 }

 std::string string = deadPlayerPacket.getPlayer().username;
 ChatServer.getInstance().disconnectPlayer(
 deadPlayerPacket.getPlayer().getOnlineID());
 ServerWorldDatabase.instance.saveTransactionID(string, 0);
 deadPlayerPacket.getPlayer().setTransactionID(0);
 transactionIDMap.put(string, 0);
 SafetySystemManager.clearSafety(deadPlayerPacket.getPlayer());
 if (deadPlayerPacket.getPlayer().accessLevel == "")
 && !ServerOptions.instance.Open.getValue()
 && ServerOptions.instance.DropOffWhiteListAfterDeath.getValue()) {
 try {
 ServerWorldDatabase.instance.removeUser(string);
 } catch (SQLException sQLException) {
 DebugLog.Multiplayer.printException(
 sQLException, "ReceivePlayerDeath: db failed",
 LogSeverity.Warning);
 }
 }

 if (deadPlayerPacket.isConsistent()) {
 deadPlayerPacket.id = deadPlayerPacket.getPlayer().getOnlineID();
 sendPlayerDeath(deadPlayerPacket, udpConnection);
 deadPlayerPacket.process();
 }

 deadPlayerPacket.getPlayer().setStateMachineLocked(true);
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceivePlayerDeath: failed",
 LogSeverity.Error);
 }
}

static void sendPlayerDeath(DeadPlayerPacket deadPlayerPacket,
 UdpConnection udpConnection1) {
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln("SendPlayerDeath: %s",
 deadPlayerPacket.getDescription());
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.PlayerDeath.doPacket(byteBufferWriter);
 deadPlayerPacket.write(byteBufferWriter);
 PacketTypes.PacketType.PlayerDeath.send(udpConnection0);
 }
 }
}

static void receivePlayerDamage(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 short short0 = byteBuffer.getShort();
 float float0 = byteBuffer.getFloat();
 IsoPlayer player = getPlayerFromConnection(udpConnection, short0);
 if (player != nullptr) {
 player.getBodyDamage().load(byteBuffer, IsoWorld.getWorldVersion());
 player.getStats().setPain(float0);
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln(
 "ReceivePlayerDamage: \"%s\" %f", player.getUsername(),
 player.getBodyDamage().getOverallBodyHealth());
 }

 sendPlayerDamage(player, udpConnection);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(
 exception, "ReceivePlayerDamage: failed", LogSeverity.Error);
 }
}

static void sendPlayerDamage(IsoPlayer player, UdpConnection udpConnection1) {
 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln("SendPlayerDamage: \"%s\" %f",
 player.getUsername(),
 player.getBodyDamage().getOverallBodyHealth());
 }

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.PlayerDamage.doPacket(byteBufferWriter);

 try {
 byteBufferWriter.putShort(player.getOnlineID());
 byteBufferWriter.putFloat(player.getStats().getPain());
 player.getBodyDamage().save(byteBufferWriter.bb);
 PacketTypes.PacketType.PlayerDamage.send(udpConnection0);
 } catch (Exception exception) {
 udpConnection0.cancelPacket();
 DebugLog.Multiplayer.printException(
 exception, "SendPlayerDamage: failed", LogSeverity.Error);
 }
 }
 }
}

static void receiveSyncInjuries(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 SyncInjuriesPacket syncInjuriesPacket = new SyncInjuriesPacket();
 syncInjuriesPacket.parse(byteBuffer, udpConnection);
 DebugLog.Damage.trace(syncInjuriesPacket.getDescription());
 if (syncInjuriesPacket.process()) {
 syncInjuriesPacket.id = syncInjuriesPacket.player.getOnlineID();
 sendPlayerInjuries(udpConnection, syncInjuriesPacket);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(
 exception, "ReceivePlayerInjuries: failed", LogSeverity.Error);
 }
}

static void sendPlayerInjuries(UdpConnection udpConnection,
 SyncInjuriesPacket syncInjuriesPacket) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncInjuries.doPacket(byteBufferWriter);
 syncInjuriesPacket.write(byteBufferWriter);
 PacketTypes.PacketType.SyncInjuries.send(udpConnection);
}

static void receiveKeepAlive(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 MPDebugInfo.instance.serverPacket(byteBuffer, udpConnection);
}

static void receiveRemoveCorpseFromMap(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 RemoveCorpseFromMap removeCorpseFromMap = new RemoveCorpseFromMap();
 removeCorpseFromMap.parse(byteBuffer, udpConnection0);
 if (removeCorpseFromMap.isConsistent()) {
 removeCorpseFromMap.process();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 removeCorpseFromMap.isRelevant(udpConnection1) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.RemoveCorpseFromMap.doPacket(byteBufferWriter);
 removeCorpseFromMap.write(byteBufferWriter);
 PacketTypes.PacketType.RemoveCorpseFromMap.send(udpConnection1);
 }
 }
 }
}

static void sendRemoveCorpseFromMap(IsoDeadBody deadBody) {
 RemoveCorpseFromMap removeCorpseFromMap = new RemoveCorpseFromMap();
 removeCorpseFromMap.set(deadBody);
 DebugLog.Death.trace(removeCorpseFromMap.getDescription());

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RemoveCorpseFromMap.doPacket(byteBufferWriter);
 removeCorpseFromMap.write(byteBufferWriter);
 PacketTypes.PacketType.RemoveCorpseFromMap.send(udpConnection);
 }
}

static void receiveEventPacket(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 try {
 EventPacket eventPacket = new EventPacket();
 eventPacket.parse(byteBuffer, udpConnection0);

 for (UdpConnection udpConnection1 : udpEngine.connections) {
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 eventPacket.isRelevant(udpConnection1) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.EventPacket.doPacket(byteBufferWriter);
 eventPacket.write(byteBufferWriter);
 PacketTypes.PacketType.EventPacket.send(udpConnection1);
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveEvent: failed",
 LogSeverity.Error);
 }
}

static void receiveActionPacket(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 try {
 ActionPacket actionPacket = new ActionPacket();
 actionPacket.parse(byteBuffer, udpConnection0);

 for (UdpConnection udpConnection1 : udpEngine.connections) {
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 actionPacket.isRelevant(udpConnection1) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.ActionPacket.doPacket(byteBufferWriter);
 actionPacket.write(byteBufferWriter);
 PacketTypes.PacketType.ActionPacket.send(udpConnection1);
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveAction: failed",
 LogSeverity.Error);
 }
}

static void receiveKillZombie(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 try {
 short short0 = byteBuffer.getShort();
 bool boolean0 = byteBuffer.get() != 0;
 DebugLog.Death.trace("id=%d, isFallOnFront=%b", short0, boolean0);
 IsoZombie zombie0 = ServerMap.instance.ZombieMap.get(short0);
 if (zombie0 != nullptr) {
 zombie0.setFallOnFront(boolean0);
 zombie0.becomeCorpse();
 } else {
 DebugLog.Multiplayer.error("ReceiveKillZombie: zombie not found");
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveKillZombie: failed",
 LogSeverity.Error);
 }
}

static void receiveEatBody(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 try {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "ReceiveEatBody");
 }

 short short0 = byteBuffer.getShort();
 IsoZombie zombie0 = ServerMap.instance.ZombieMap.get(short0);
 if (zombie0.empty()) {
 DebugLog.Multiplayer.error("ReceiveEatBody: zombie " + short0 +
 " not found");
 return;
 }

 for (UdpConnection udpConnection : udpEngine.connections) {
 if (udpConnection.RelevantTo(zombie0.x, zombie0.y) {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "SendEatBody");
 }

 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.EatBody.doPacket(byteBufferWriter);
 byteBuffer.position(0);
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.EatBody.send(udpConnection);
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveEatBody: failed",
 LogSeverity.Error);
 }
}

static void receiveSyncRadioData(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 try {
 bool boolean0 = byteBuffer.get() == 1;
 int int0 = byteBuffer.getInt();
 int[] ints = new int[int0];

 for (int int1 = 0; int1 < int0; int1++) {
 ints[int1] = byteBuffer.getInt();
 }

 RakVoice.SetChannelsRouting(udpConnection0.getConnectedGUID(), boolean0,
 ints, (short)int0);

 for (UdpConnection udpConnection1 : udpEngine.connections) {
 if (udpConnection1 != udpConnection0 &&
 udpConnection0.players[0] != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncRadioData.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(udpConnection0.players[0].OnlineID);
 byteBuffer.position(0);
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.SyncRadioData.send(udpConnection1);
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "SyncRadioData: failed",
 LogSeverity.Error);
 }
}

static void receiveThump(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 try {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "ReceiveThump");
 }

 short short0 = byteBuffer.getShort();
 IsoZombie zombie0 = ServerMap.instance.ZombieMap.get(short0);
 if (zombie0.empty()) {
 DebugLog.Multiplayer.error("ReceiveThump: zombie " + short0 +
 " not found");
 return;
 }

 for (UdpConnection udpConnection : udpEngine.connections) {
 if (udpConnection.RelevantTo(zombie0.x, zombie0.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Thump.doPacket(byteBufferWriter);
 byteBuffer.position(0);
 byteBufferWriter.bb.put(byteBuffer);
 PacketTypes.PacketType.Thump.send(udpConnection);
 }
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveEatBody: failed",
 LogSeverity.Error);
 }
}

static void sendWorldSound(UdpConnection udpConnection,
 WorldSoundManager.WorldSound worldSound) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.WorldSound.doPacket(byteBufferWriter);

 try {
 byteBufferWriter.putInt(worldSound.x);
 byteBufferWriter.putInt(worldSound.y);
 byteBufferWriter.putInt(worldSound.z);
 byteBufferWriter.putInt(worldSound.radius);
 byteBufferWriter.putInt(worldSound.volume);
 byteBufferWriter.putByte((byte)(worldSound.stresshumans ? 1 : 0);
 byteBufferWriter.putFloat(worldSound.zombieIgnoreDist);
 byteBufferWriter.putFloat(worldSound.stressMod);
 byteBufferWriter.putByte((byte)(worldSound.sourceIsZombie ? 1 : 0);
 PacketTypes.PacketType.WorldSound.send(udpConnection);
 } catch (Exception exception) {
 DebugLog.Sound.printException(exception, "SendWorldSound: failed",
 LogSeverity.Error);
 udpConnection.cancelPacket();
 }
}

static void sendWorldSound(WorldSoundManager.WorldSound worldSound,
 UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if ((udpConnection1.empty() || udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) &&
 udpConnection0.isFullyConnected()) {
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection0);
 if (player != nullptr &&
 udpConnection0.RelevantTo(worldSound.x, worldSound.y,
 worldSound.radius) {
 sendWorldSound(udpConnection0, worldSound);
 }
 }
 }
}

static void receiveWorldSound(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 int int4 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 bool boolean1 = byteBuffer.get() == 1;
 DebugLog.Sound.noise("x=%d y=%d z=%d, radius=%d", int0, int1, int2, int3);
 WorldSoundManager.WorldSound worldSound = WorldSoundManager.instance.addSound(
 nullptr, int0, int1, int2, int3, int4, boolean0, float0, float1, boolean1,
 false, true);
 if (worldSound != nullptr) {
 sendWorldSound(worldSound, udpConnection);
 }
}

static void kick(UdpConnection udpConnection, std::string_view string1,
 std::string_view string0) {
 DebugLog.General.warn("The player " + udpConnection.username +
 " was kicked. The reason was " + string1 + ", " +
 string0);
 ConnectionManager.log("kick", string0, udpConnection);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();

 try {
 PacketTypes.PacketType.Kicked.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putUTF(string0);
 PacketTypes.PacketType.Kicked.send(udpConnection);
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "Kick: failed",
 LogSeverity.Error);
 udpConnection.cancelPacket();
 }
}

static void sendStartRain(UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StartRain.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(RainManager.randRainMin);
 byteBufferWriter.putInt(RainManager.randRainMax);
 byteBufferWriter.putFloat(RainManager.RainDesiredIntensity);
 PacketTypes.PacketType.StartRain.send(udpConnection);
}

static void startRain() {
 if (udpEngine != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendStartRain(udpConnection);
 }
 }
}

static void sendStopRain(UdpConnection udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.StopRain.doPacket(byteBufferWriter);
 PacketTypes.PacketType.StopRain.send(udpConnection);
}

static void stopRain() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendStopRain(udpConnection);
 }
}

static void sendWeather(UdpConnection udpConnection) {
 GameTime gameTime = GameTime.getInstance();
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Weather.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)gameTime.getDawn());
 byteBufferWriter.putByte((byte)gameTime.getDusk());
 byteBufferWriter.putByte((byte)(gameTime.isThunderDay() ? 1 : 0);
 byteBufferWriter.putFloat(gameTime.Moon);
 byteBufferWriter.putFloat(gameTime.getAmbientMin());
 byteBufferWriter.putFloat(gameTime.getAmbientMax());
 byteBufferWriter.putFloat(gameTime.getViewDistMin());
 byteBufferWriter.putFloat(gameTime.getViewDistMax());
 byteBufferWriter.putFloat(IsoWorld.instance.getGlobalTemperature());
 byteBufferWriter.putUTF(IsoWorld.instance.getWeather());
 ErosionMain.getInstance().sendState(byteBufferWriter.bb);
 PacketTypes.PacketType.Weather.send(udpConnection);
}

static void sendWeather() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendWeather(udpConnection);
 }
}

static bool isInSameFaction(IsoPlayer player0, IsoPlayer player1) {
 Faction faction0 = Faction.getPlayerFaction(player0);
 Faction faction1 = Faction.getPlayerFaction(player1);
 return faction0 != nullptr && faction0 == faction1;
}

static bool isInSameSafehouse(IsoPlayer player1, IsoPlayer player0) {
 std::vector arrayList = SafeHouse.getSafehouseList();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 SafeHouse safeHouse = (SafeHouse)arrayList.get(int0);
 if (safeHouse.playerAllowed(player1.getUsername()) &&
 safeHouse.playerAllowed(player0.getUsername())) {
 return true;
 }
 }

 return false;
}

static bool isAnyPlayerInSameFaction(UdpConnection udpConnection,
 IsoPlayer player1) {
 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player0 = udpConnection.players[int0];
 if (player0 != nullptr && isInSameFaction(player0, player1) {
 return true;
 }
 }

 return false;
}

static bool isAnyPlayerInSameSafehouse(UdpConnection udpConnection,
 IsoPlayer player1) {
 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player0 = udpConnection.players[int0];
 if (player0 != nullptr && isInSameSafehouse(player0, player1) {
 return true;
 }
 }

 return false;
}

static bool shouldSendWorldMapPlayerPosition(UdpConnection udpConnection1,
 IsoPlayer player) {
 if (player != nullptr && !player.isDead()) {
 UdpConnection udpConnection0 = getConnectionFromPlayer(player);
 if (udpConnection0.empty() || udpConnection0 == udpConnection1 ||
 !udpConnection0.isFullyConnected()) {
 return false;
 } else if (udpConnection1.accessLevel > 1) {
 return true;
 } else {
 int int0 =
 ServerOptions.getInstance().MapRemotePlayerVisibility.getValue();
 return int0 != 2 ? true
 : isAnyPlayerInSameFaction(udpConnection1, player) ||
 isAnyPlayerInSameSafehouse(udpConnection1, player);
 }
 } else {
 return false;
 }
}

static void sendWorldMapPlayerPosition(UdpConnection udpConnection) {
 tempPlayers.clear();

 for (int int0 = 0; int0 < Players.size(); int0++) {
 IsoPlayer player0 = Players.get(int0);
 if (shouldSendWorldMapPlayerPosition(udpConnection, player0) {
 tempPlayers.add(player0);
 }
 }

 if (!tempPlayers.empty()) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.WorldMapPlayerPosition.doPacket(byteBufferWriter);
 byteBufferWriter.putBoolean(false);
 byteBufferWriter.putShort((short)tempPlayers.size());

 for (int int1 = 0; int1 < tempPlayers.size(); int1++) {
 IsoPlayer player1 = tempPlayers.get(int1);
 WorldMapRemotePlayer worldMapRemotePlayer =
 WorldMapRemotePlayers.instance.getOrCreatePlayer(player1);
 worldMapRemotePlayer.setPlayer(player1);
 byteBufferWriter.putShort(worldMapRemotePlayer.getOnlineID());
 byteBufferWriter.putShort(worldMapRemotePlayer.getChangeCount());
 byteBufferWriter.putFloat(worldMapRemotePlayer.getX());
 byteBufferWriter.putFloat(worldMapRemotePlayer.getY());
 }

 PacketTypes.PacketType.WorldMapPlayerPosition.send(udpConnection);
 }
}

static void sendWorldMapPlayerPosition() {
 int int0 = ServerOptions.getInstance().MapRemotePlayerVisibility.getValue();

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection = udpEngine.connections.get(int1);
 if (int0 != 1 || udpConnection.accessLevel != 1) {
 sendWorldMapPlayerPosition(udpConnection);
 }
 }
}

static void receiveWorldMapPlayerPosition(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 short short0 = byteBuffer.getShort();
 tempPlayers.clear();

 for (int int0 = 0; int0 < short0; int0++) {
 short short1 = byteBuffer.getShort();
 IsoPlayer player0 = IDToPlayerMap.get(short1);
 if (player0 != nullptr &&
 shouldSendWorldMapPlayerPosition(udpConnection, player0) {
 tempPlayers.add(player0);
 }
 }

 if (!tempPlayers.empty()) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.WorldMapPlayerPosition.doPacket(byteBufferWriter);
 byteBufferWriter.putBoolean(true);
 byteBufferWriter.putShort((short)tempPlayers.size());

 for (int int1 = 0; int1 < tempPlayers.size(); int1++) {
 IsoPlayer player1 = tempPlayers.get(int1);
 WorldMapRemotePlayer worldMapRemotePlayer =
 WorldMapRemotePlayers.instance.getOrCreatePlayer(player1);
 worldMapRemotePlayer.setPlayer(player1);
 byteBufferWriter.putShort(worldMapRemotePlayer.getOnlineID());
 byteBufferWriter.putShort(worldMapRemotePlayer.getChangeCount());
 byteBufferWriter.putUTF(worldMapRemotePlayer.getUsername());
 byteBufferWriter.putUTF(worldMapRemotePlayer.getForename());
 byteBufferWriter.putUTF(worldMapRemotePlayer.getSurname());
 byteBufferWriter.putUTF(worldMapRemotePlayer.getAccessLevel());
 byteBufferWriter.putFloat(worldMapRemotePlayer.getX());
 byteBufferWriter.putFloat(worldMapRemotePlayer.getY());
 byteBufferWriter.putBoolean(worldMapRemotePlayer.isInvisible());
 }

 PacketTypes.PacketType.WorldMapPlayerPosition.send(udpConnection);
 }
}

static void syncClock(UdpConnection udpConnection) {
 GameTime gameTime = GameTime.getInstance();
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncClock.doPacket(byteBufferWriter);
 byteBufferWriter.putBoolean(bFastForward);
 byteBufferWriter.putFloat(gameTime.getTimeOfDay());
 byteBufferWriter.putInt(gameTime.getNightsSurvived());
 PacketTypes.PacketType.SyncClock.send(udpConnection);
}

static void syncClock() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 syncClock(udpConnection);
 }
}

static void sendServerCommand(std::string_view string0,
 std::string_view string1, KahluaTable table,
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

 PacketTypes.PacketType.ClientCommand.send(udpConnection);
}

static void sendServerCommand(std::string_view string0,
 std::string_view string1, KahluaTable table) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 sendServerCommand(string0, string1, table, udpConnection);
 }
}

static void sendServerCommandV(std::string_view string0,
 std::string_view string1, Object... objects) {
 if (objects.length == 0) {
 sendServerCommand(string0, string1, (KahluaTable) nullptr);
 } else if (objects.length % 2 != 0) {
 DebugLog.log(
 "ERROR: sendServerCommand called with invalid number of arguments (" +
 string0 + " " + string1 + ")");
 } else {
 KahluaTable table = LuaManager.platform.newTable();

 for (byte byte0 = 0; byte0 < objects.length; byte0 += 2) {
 void *object = objects[byte0 + 1];
 if (object instanceof Float) {
 table.rawset(objects[byte0], ((Float)object).doubleValue());
 } else if (object instanceof Integer) {
 table.rawset(objects[byte0], ((Integer)object).doubleValue());
 } else if (object instanceof Short) {
 table.rawset(objects[byte0], ((Short)object).doubleValue());
 } else {
 table.rawset(objects[byte0], object);
 }
 }

 sendServerCommand(string0, string1, table);
 }
}

static void sendServerCommand(IsoPlayer player, std::string_view string0,
 std::string_view string1, KahluaTable table) {
 if (PlayerToAddressMap.containsKey(player) {
 long long0 = PlayerToAddressMap.get(player);
 UdpConnection udpConnection = udpEngine.getActiveConnection(long0);
 if (udpConnection != nullptr) {
 sendServerCommand(string0, string1, table, udpConnection);
 }
 }
}

public
static ArrayList<IsoPlayer> getPlayers(ArrayList<IsoPlayer> arrayList) {
 arrayList.clear();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 IsoPlayer player = udpConnection.players[int1];
 if (player != nullptr && player.OnlineID != -1) {
 arrayList.add(player);
 }
 }
 }

 return arrayList;
}

public
static ArrayList<IsoPlayer> getPlayers() {
 std::vector arrayList = new ArrayList();
 return getPlayers();
}

static int getPlayerCount() noexcept{
 int int0 = 0;

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection = udpEngine.connections.get(int1);

 for (int int2 = 0; int2 < 4; int2++) {
 if (udpConnection.playerIDs[int2] != -1) {
 int0++;
 }
 }
 }

 return int0;
}

static void sendAmbient(std::string_view string, int int2, int int1, int int0,
 float float0) {
 DebugLog.log(DebugType.Sound, "ambient: sending " + string + " at " + int2 +
 "," + int1 + " radius=" + int0);

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection = udpEngine.connections.get(int3);
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection);
 if (player != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddAmbient.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putFloat(float0);
 PacketTypes.PacketType.AddAmbient.send(udpConnection);
 }
 }
}

static void receiveChangeSafety(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 try {
 SafetyPacket safetyPacket = new SafetyPacket();
 safetyPacket.parse(byteBuffer, udpConnection);
 safetyPacket.log(udpConnection, "ReceiveChangeSafety");
 safetyPacket.process();
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "ReceiveZombieDeath: failed",
 LogSeverity.Error);
 }
}

static void sendChangeSafety(Safety safety) {
 try {
 SafetyPacket safetyPacket = new SafetyPacket(safety);
 safetyPacket.log(nullptr, "SendChangeSafety");

 for (UdpConnection udpConnection : udpEngine.connections) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ChangeSafety.doPacket(byteBufferWriter);
 safetyPacket.write(byteBufferWriter);
 PacketTypes.PacketType.ChangeSafety.send(udpConnection);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "SendChangeSafety: failed",
 LogSeverity.Error);
 }
}

static void receivePing(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 udpConnection.ping = true;
 answerPing(byteBuffer, udpConnection);
}

public
static void updateOverlayForClients(IsoObject object, String string,
 float float0, float float1, float float2,
 float float3,
 UdpConnection udpConnection1) {
 if (udpEngine != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0 != nullptr && object.square != nullptr &&
 udpConnection0.RelevantTo(object.square.x, object.square.y) &&
 (udpConnection1.empty() ||
 udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID())) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.UpdateOverlaySprite.doPacket(byteBufferWriter);
 GameWindow.WriteStringUTF(byteBufferWriter.bb, string);
 byteBufferWriter.putInt(object.getSquare().getX());
 byteBufferWriter.putInt(object.getSquare().getY());
 byteBufferWriter.putInt(object.getSquare().getZ());
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 byteBufferWriter.putFloat(float3);
 byteBufferWriter.putInt(
 object.getSquare().getObjects().indexOf(object);
 PacketTypes.PacketType.UpdateOverlaySprite.send(udpConnection0);
 }
 }
 }
}

static void receiveUpdateOverlaySprite(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 float float3 = byteBuffer.getFloat();
 int int3 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && int3 < square.getObjects().size()) {
 try {
 IsoObject object = square.getObjects().get(int3);
 if (object != nullptr && object.setOverlaySprite(string, float0, float1,
 float2, float3, false) {
 updateOverlayForClients(object, string, float0, float1, float2, float3,
 udpConnection);
 }
 } catch (Exception exception) {
 }
 }
}

static void sendReanimatedZombieID(IsoPlayer player, IsoZombie zombie0) {
 if (PlayerToAddressMap.containsKey(player) {
 sendObjectChange(player, "reanimatedID", "ID", (double)zombie0.OnlineID);
 }
}

static void receiveSyncSafehouse(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 SyncSafehousePacket syncSafehousePacket = new SyncSafehousePacket();
 syncSafehousePacket.parse(byteBuffer, udpConnection);
 if (syncSafehousePacket.validate(udpConnection) {
 syncSafehousePacket.process();
 sendSafehouse(syncSafehousePacket, udpConnection);
 if (ChatServer.isInited()) {
 if (syncSafehousePacket.shouldCreateChat) {
 ChatServer.getInstance().createSafehouseChat(
 syncSafehousePacket.safehouse.getId());
 }

 if (syncSafehousePacket.remove) {
 ChatServer.getInstance().removeSafehouseChat(
 syncSafehousePacket.safehouse.getId());
 } else {
 ChatServer.getInstance().syncSafehouseChatMembers(
 syncSafehousePacket.safehouse.getId(),
 syncSafehousePacket.ownerUsername,
 syncSafehousePacket.safehouse.getPlayers());
 }
 }
 }
}

static void receiveKickOutOfSafehouse(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 try {
 IsoPlayer player0 = IDToPlayerMap.get(byteBuffer.getShort());
 if (player0.empty()) {
 return;
 }

 IsoPlayer player1 = udpConnection0.players[0];
 if (player1.empty()) {
 return;
 }

 SafeHouse safeHouse = SafeHouse.hasSafehouse(player1);
 if (safeHouse.empty()) {
 return;
 }

 if (!safeHouse.isOwner(player1) {
 return;
 }

 if (!safeHouse.playerAllowed(player0) {
 return;
 }

 UdpConnection udpConnection1 = getConnectionFromPlayer(player0);
 if (udpConnection1.empty()) {
 return;
 }

 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.KickOutOfSafehouse.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)player0.PlayerIndex);
 byteBufferWriter.putFloat(safeHouse.getX() - 1);
 byteBufferWriter.putFloat(safeHouse.getY() - 1);
 byteBufferWriter.putFloat(0.0F);
 PacketTypes.PacketType.KickOutOfSafehouse.send(udpConnection1);
 if (player0.getNetworkCharacterAI() != nullptr) {
 player0.getNetworkCharacterAI().resetSpeedLimiter();
 }

 if (player0.isAsleep()) {
 player0.setAsleep(false);
 player0.setAsleepTime(0.0F);
 sendWakeUpPlayer(player0, nullptr);
 }
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(
 exception, "ReceiveKickOutOfSafehouse: failed", LogSeverity.Error);
 }
}

static void sendSafehouse(SyncSafehousePacket syncSafehousePacket,
 UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncSafehouse.doPacket(byteBufferWriter);
 syncSafehousePacket.write(byteBufferWriter);
 PacketTypes.PacketType.SyncSafehouse.send(udpConnection0);
 }
 }
}

static void receiveRadioServerData(ByteBuffer var0, UdpConnection udpConnection,
 short var2) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RadioServerData.doPacket(byteBufferWriter);
 ZomboidRadio.getInstance().WriteRadioServerDataPacket(byteBufferWriter);
 PacketTypes.PacketType.RadioServerData.send(udpConnection);
}

static void receiveRadioDeviceDataState(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && int3 >= 0 && int3 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(int3);
 if (object instanceof IsoWaveSignal) {
 DeviceData deviceData0 = ((IsoWaveSignal)object).getDeviceData();
 if (deviceData0 != nullptr) {
 try {
 deviceData0.receiveDeviceDataStatePacket(byteBuffer, nullptr);
 } catch (Exception exception0) {
 System.out.print(exception0.getMessage());
 }
 }
 }
 }
 } else if (byte0 == 0) {
 uint8_t byte1 = byteBuffer.get();
 IsoPlayer player = getPlayerFromConnection(udpConnection, byte1);
 uint8_t byte2 = byteBuffer.get();
 if (player != nullptr) {
 Radio radio = nullptr;
 if (byte2 == 1 && player.getPrimaryHandItem() instanceof Radio) {
 radio = (Radio)player.getPrimaryHandItem();
 }

 if (byte2 == 2 && player.getSecondaryHandItem() instanceof Radio) {
 radio = (Radio)player.getSecondaryHandItem();
 }

 if (radio != nullptr && radio.getDeviceData() != nullptr) {
 try {
 radio.getDeviceData().receiveDeviceDataStatePacket(byteBuffer,
 udpConnection);
 } catch (Exception exception1) {
 System.out.print(exception1.getMessage());
 }
 }
 }
 } else if (byte0 == 2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(short0);
 if (vehicle != nullptr) {
 VehiclePart part = vehicle.getPartByIndex(short1);
 if (part != nullptr) {
 DeviceData deviceData1 = part.getDeviceData();
 if (deviceData1 != nullptr) {
 try {
 deviceData1.receiveDeviceDataStatePacket(byteBuffer, nullptr);
 } catch (Exception exception2) {
 System.out.print(exception2.getMessage());
 }
 }
 }
 }
 }
}

public
static void sendIsoWaveSignal(long long0, int int0, int int1, int int2,
 String string0, String string1, String string2,
 float float0, float float1, float float2,
 int int3, boolean boolean0) {
 WaveSignal waveSignal = new WaveSignal();
 waveSignal.set(int0, int1, int2, string0, string1, string2, float0, float1,
 float2, int3, boolean0);

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = udpEngine.connections.get(int4);
 if (long0 != udpConnection.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.WaveSignal.doPacket(byteBufferWriter);
 waveSignal.write(byteBufferWriter);
 PacketTypes.PacketType.WaveSignal.send(udpConnection);
 }
 }
}

static void receiveWaveSignal(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 WaveSignal waveSignal = new WaveSignal();
 waveSignal.parse(byteBuffer, udpConnection);
 waveSignal.process(udpConnection);
}

static void receivePlayerListensChannel(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 int int0 = byteBuffer.getInt();
 bool boolean0 = byteBuffer.get() == 1;
 bool boolean1 = byteBuffer.get() == 1;
 ZomboidRadio.getInstance().PlayerListensChannel(int0, boolean0, boolean1);
}

static void sendAlarm(int int1, int int0) {
 DebugLog.log(DebugType.Multiplayer,
 "SendAlarm at [ " + int1 + " , " + int0 + " ]");

 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection = udpEngine.connections.get(int2);
 IsoPlayer player = getAnyPlayerFromConnection(udpConnection);
 if (player != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddAlarm.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int0);
 PacketTypes.PacketType.AddAlarm.send(udpConnection);
 }
 }
}

static bool isSpawnBuilding(BuildingDef buildingDef) {
 return SpawnPoints.instance.isSpawnBuilding(buildingDef);
}

static void setFastForward(bool boolean0) {
 if (boolean0 != bFastForward) {
 bFastForward = boolean0;
 syncClock();
 }
}

static void receiveSendCustomColor(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 float float3 = byteBuffer.getFloat();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && int3 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(int3);
 if (object != nullptr) {
 object.setCustomColor(float0, float1, float2, float3);
 }
 }

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int4);
 if (udpConnection0.RelevantTo(int0, int1) &&
 (udpConnection1 != nullptr && udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() ||
 udpConnection1.empty())) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SendCustomColor.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 byteBufferWriter.putFloat(float3);
 PacketTypes.PacketType.SendCustomColor.send(udpConnection0);
 }
 }
}

static void receiveSyncFurnace(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square.empty()) {
 DebugLog.log("receiveFurnaceChange: square is nullptr x,y,z=" + int0 + "," +
 int1 + "," + int2);
 } else {
 BSFurnace bSFurnace = nullptr;

 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 if (square.getObjects().get(int3) instanceof BSFurnace) {
 bSFurnace = (BSFurnace)square.getObjects().get(int3);
 break;
 }
 }

 if (bSFurnace.empty()) {
 DebugLog.log("receiveFurnaceChange: furnace is nullptr x,y,z=" + int0 +
 "," + int1 + "," + int2);
 } else {
 bSFurnace.fireStarted = byteBuffer.get() == 1;
 bSFurnace.fuelAmount = byteBuffer.getFloat();
 bSFurnace.fuelDecrease = byteBuffer.getFloat();
 bSFurnace.heat = byteBuffer.getFloat();
 bSFurnace.sSprite = GameWindow.ReadString(byteBuffer);
 bSFurnace.sLitSprite = GameWindow.ReadString(byteBuffer);
 sendFuranceChange(bSFurnace, udpConnection);
 }
 }
}

static void receiveVehicles(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short short0) {
 VehicleManager.instance.serverPacket(byteBuffer, udpConnection, short0);
}

static void receiveTimeSync(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 GameTime.receiveTimeSync(byteBuffer, udpConnection);
}

static void sendFuranceChange(BSFurnace bSFurnace,
 UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.RelevantTo(bSFurnace.square.x, bSFurnace.square.y) &&
 (udpConnection1 != nullptr && udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID() ||
 udpConnection1.empty())) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncFurnace.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(bSFurnace.square.x);
 byteBufferWriter.putInt(bSFurnace.square.y);
 byteBufferWriter.putInt(bSFurnace.square.z);
 byteBufferWriter.putByte((byte)(bSFurnace.isFireStarted() ? 1 : 0);
 byteBufferWriter.putFloat(bSFurnace.getFuelAmount());
 byteBufferWriter.putFloat(bSFurnace.getFuelDecrease());
 byteBufferWriter.putFloat(bSFurnace.getHeat());
 GameWindow.WriteString(byteBufferWriter.bb, bSFurnace.sSprite);
 GameWindow.WriteString(byteBufferWriter.bb, bSFurnace.sLitSprite);
 PacketTypes.PacketType.SyncFurnace.send(udpConnection0);
 }
 }
}

static void receiveUserlog(ByteBuffer byteBuffer, UdpConnection udpConnection1,
 short var2) {
 std::string string = GameWindow.ReadString(byteBuffer);
 std::vector arrayList = ServerWorldDatabase.instance.getUserlog(string);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() ==
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.Userlog.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(arrayList.size());
 byteBufferWriter.putUTF(string);

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 Userlog userlog = (Userlog)arrayList.get(int1);
 byteBufferWriter.putInt(
 Userlog.UserlogType.FromString(userlog.getType()).index());
 byteBufferWriter.putUTF(userlog.getText());
 byteBufferWriter.putUTF(userlog.getIssuedBy());
 byteBufferWriter.putInt(userlog.getAmount());
 byteBufferWriter.putUTF(userlog.getLastUpdate());
 }

 PacketTypes.PacketType.Userlog.send(udpConnection0);
 }
 }
}

static void receiveAddUserlog(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 ServerWorldDatabase.instance.addUserlog(
 string0, Userlog.UserlogType.FromString(string1), string2,
 udpConnection.username, 1);
 LoggerManager.getLogger("admin").write(udpConnection.username +
 " added log on user " + string0 +
 ", log: " + string2);
}

static void receiveRemoveUserlog(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 ServerWorldDatabase.instance.removeUserLog(string0, string1, string2);
 LoggerManager.getLogger("admin").write(
 udpConnection.username + " removed log on user " + string0 +
 ", type:" + string1 + ", log: " + string2);
}

static void receiveAddWarningPoint(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBuffer.getInt();
 ServerWorldDatabase.instance.addWarningPoint(string0, string1, int0,
 udpConnection0.username);
 LoggerManager.getLogger("admin").write(udpConnection0.username + " added " +
 int0 + " warning point(s) on " +
 string0 + ", reason:" + string1);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int1);
 if (udpConnection1.username == string0) {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.WorldMessage.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(udpConnection0.username);
 byteBufferWriter.putUTF(" gave you " + int0 +
 " warning point(s), reason: " + string1 + " ");
 PacketTypes.PacketType.WorldMessage.send(udpConnection1);
 }
 }
}

static void sendAdminMessage(std::string_view string, int int1, int int2,
 int int3) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (canSeePlayerStats(udpConnection) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.MessageForAdmin.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.MessageForAdmin.send(udpConnection);
 }
 }
}

static void receiveWakeUpPlayer(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 IsoPlayer player =
 getPlayerFromConnection(udpConnection, byteBuffer.getShort());
 if (player != nullptr) {
 player.setAsleep(false);
 player.setAsleepTime(0.0F);
 sendWakeUpPlayer(player, udpConnection);
 }
}

static void sendWakeUpPlayer(IsoPlayer player, UdpConnection udpConnection1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection0.getConnectedGUID() !=
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.WakeUpPlayer.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player.getOnlineID());
 PacketTypes.PacketType.WakeUpPlayer.send(udpConnection0);
 }
 }
}

static void receiveGetDBSchema(ByteBuffer var0, UdpConnection udpConnection1,
 short var2) {
 DBSchema dBSchema = ServerWorldDatabase.instance.getDBSchema();

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1 != nullptr && udpConnection0.getConnectedGUID() ==
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.GetDBSchema.doPacket(byteBufferWriter);
 std::unordered_map hashMap0 = dBSchema.getSchema();
 byteBufferWriter.putInt(hashMap0.size());

 for (String string0 : hashMap0.keySet()) {
 std::unordered_map hashMap1 = (HashMap)hashMap0.get(string0);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putInt(hashMap1.size());

 for (String string1 : hashMap1.keySet()) {
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putUTF((String)hashMap1.get(string1);
 }
 }

 PacketTypes.PacketType.GetDBSchema.send(udpConnection0);
 }
 }
}

static void receiveGetTableResult(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 int int0 = byteBuffer.getInt();
 std::string string = GameWindow.ReadString(byteBuffer);
 std::vector arrayList = ServerWorldDatabase.instance.getTableResult(string);

 for (int int1 = 0; int1 < udpEngine.connections.size(); int1++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int1);
 if (udpConnection1 != nullptr && udpConnection0.getConnectedGUID() ==
 udpConnection1.getConnectedGUID()) {
 doTableResult(udpConnection0, string, arrayList, 0, int0);
 }
 }
}

static void doTableResult(UdpConnection udpConnection,
 std::string_view string0,
 ArrayList<DBResult> arrayList, int int1, int int2) {
 int int0 = 0;
 bool boolean0 = true;
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.GetTableResult.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putUTF(string0);
 if (arrayList.size() < int2) {
 byteBufferWriter.putInt(arrayList.size());
 } else if (arrayList.size() - int1 < int2) {
 byteBufferWriter.putInt(arrayList.size() - int1);
 } else {
 byteBufferWriter.putInt(int2);
 }

 for (int int3 = int1; int3 < arrayList.size(); int3++) {
 DBResult dBResult = nullptr;

 try {
 dBResult = (DBResult)arrayList.get(int3);
 byteBufferWriter.putInt(dBResult.getColumns().size());
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 for (String string1 : dBResult.getColumns()) {
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putUTF(dBResult.getValues().get(string1);
 }

 if (++int0 >= int2) {
 boolean0 = false;
 PacketTypes.PacketType.GetTableResult.send(udpConnection);
 doTableResult(udpConnection, string0, arrayList, int1 + int0, int2);
 break;
 }
 }

 if (boolean0) {
 PacketTypes.PacketType.GetTableResult.send(udpConnection);
 }
}

static void receiveExecuteQuery(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 if (udpConnection.accessLevel == 32) {
 try {
 std::string string = GameWindow.ReadString(byteBuffer);
 KahluaTable table = LuaManager.platform.newTable();
 table.load(byteBuffer, 195);
 ServerWorldDatabase.instance.executeQuery(string, table);
 } catch (Throwable throwable) {
 throwable.printStackTrace();
 }
 }
}

static void receiveSendFactionInvite(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 IsoPlayer player = getPlayerByUserName(string2);
 if (player != nullptr) {
 long long0 = IDToAddressMap.get(player.getOnlineID());

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SendFactionInvite.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 PacketTypes.PacketType.SendFactionInvite.send(udpConnection);
 break;
 }
 }
 }
}

static void receiveAcceptedFactionInvite(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 IsoPlayer player = getPlayerByUserName(string1);
 long long0 = IDToAddressMap.get(player.getOnlineID());

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.getConnectedGUID() == long0) {
 Faction faction = Faction.getPlayerFaction(udpConnection.username);
 if (faction != nullptr && faction.getName() == string0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AcceptedFactionInvite.doPacket(
 byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 PacketTypes.PacketType.AcceptedFactionInvite.send(udpConnection);
 }
 }
 }
}

static void receiveViewTickets(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 std::string string = GameWindow.ReadString(byteBuffer);
 if ("" == string) {
 string = nullptr;
 }

 sendTickets(string, udpConnection);
}

static void sendTickets(std::string_view string,
 UdpConnection udpConnection1) {
 std::vector arrayList = ServerWorldDatabase.instance.getTickets(string);

 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection0.getConnectedGUID() ==
 udpConnection1.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.ViewTickets.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(arrayList.size());

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 DBTicket dBTicket = (DBTicket)arrayList.get(int1);
 byteBufferWriter.putUTF(dBTicket.getAuthor());
 byteBufferWriter.putUTF(dBTicket.getMessage());
 byteBufferWriter.putInt(dBTicket.getTicketID());
 if (dBTicket.getAnswer() != nullptr) {
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putUTF(dBTicket.getAnswer().getAuthor());
 byteBufferWriter.putUTF(dBTicket.getAnswer().getMessage());
 byteBufferWriter.putInt(dBTicket.getAnswer().getTicketID());
 } else {
 byteBufferWriter.putByte((byte)0);
 }
 }

 PacketTypes.PacketType.ViewTickets.send(udpConnection0);
 break;
 }
 }
}

static void receiveAddTicket(ByteBuffer byteBuffer, UdpConnection udpConnection,
 short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBuffer.getInt();
 if (int0 == -1) {
 sendAdminMessage("user " + string0 + " added a ticket <LINE> <LINE> " +
 string1,
 -1, -1, -1);
 }

 ServerWorldDatabase.instance.addTicket(string0, string1, int0);
 sendTickets(string0, udpConnection);
}

static void receiveRemoveTicket(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 int int0 = byteBuffer.getInt();
 ServerWorldDatabase.instance.removeTicket(int0);
 sendTickets(nullptr, udpConnection);
}

public
static boolean sendItemListNet(UdpConnection udpConnection1, IsoPlayer player2,
 ArrayList<InventoryItem> arrayList,
 IsoPlayer player0, String string0,
 String string1) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.empty() || udpConnection0 != udpConnection1) {
 if (player0 != nullptr) {
 bool boolean0 = false;

 for (int int1 = 0; int1 < udpConnection0.players.length; int1++) {
 IsoPlayer player1 = udpConnection0.players[int1];
 if (player1 != nullptr && player1 == player0) {
 boolean0 = true;
 break;
 }
 }

 if (!boolean0) {
 continue;
 }
 }

 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SendItemListNet.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)(player0 != nullptr ? 1 : 0);
 if (player0 != nullptr) {
 byteBufferWriter.putShort(player0.getOnlineID());
 }

 byteBufferWriter.putByte((byte)(player2 != nullptr ? 1 : 0);
 if (player2 != nullptr) {
 byteBufferWriter.putShort(player2.getOnlineID());
 }

 GameWindow.WriteString(byteBufferWriter.bb, string0);
 byteBufferWriter.putByte((byte)(string1 != nullptr ? 1 : 0);
 if (string1 != nullptr) {
 GameWindow.WriteString(byteBufferWriter.bb, string1);
 }

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb, arrayList, nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 udpConnection0.cancelPacket();
 return false;
 }

 PacketTypes.PacketType.SendItemListNet.send(udpConnection0);
 }
 }

 return true;
}

static void receiveSendItemListNet(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 IsoPlayer player0 = nullptr;
 if (byteBuffer.get() == 1) {
 player0 = IDToPlayerMap.get(byteBuffer.getShort());
 }

 IsoPlayer player1 = nullptr;
 if (byteBuffer.get() == 1) {
 player1 = IDToPlayerMap.get(byteBuffer.getShort());
 }

 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = nullptr;
 if (byteBuffer.get() == 1) {
 string1 = GameWindow.ReadString(byteBuffer);
 }

 std::vector arrayList = new ArrayList();

 try {
 CompressIdenticalItems.load(byteBuffer, 195, arrayList, nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (player0.empty()) {
 LuaEventManager.triggerEvent("OnReceiveItemListNet", player1, arrayList,
 player0, string0, string1);
 } else {
 sendItemListNet(udpConnection, player1, arrayList, player0, string0,
 string1);
 }
}

static void sendPlayerDamagedByCarCrash(IsoPlayer player, float float0) {
 UdpConnection udpConnection = getConnectionFromPlayer(player);
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.PlayerDamageFromCarCrash.doPacket(byteBufferWriter);
 byteBufferWriter.putFloat(float0);
 PacketTypes.PacketType.PlayerDamageFromCarCrash.send(udpConnection);
 }
}

static void receiveClimateManagerPacket(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 ClimateManager climateManager = ClimateManager.getInstance();
 if (climateManager != nullptr) {
 try {
 climateManager.receiveClimatePacket(byteBuffer, udpConnection);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

static void receivePassengerMap(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 PassengerMap.serverReceivePacket(byteBuffer, udpConnection);
}

static void receiveIsoRegionClientRequestFullUpdate(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 IsoRegions.receiveClientRequestFullDataChunks(byteBuffer, udpConnection);
}

static std::string isWorldVersionUnsupported() {
 File file = new File(ZomboidFileSystem.instance.getSaveDir() +
 File.separator + "Multiplayer" + File.separator +
 ServerName + File.separator + "map_t.bin");
 if (file.exists()) {
 DebugLog.log("checking server WorldVersion in map_t.bin");

 try {
 std::string string;
 try(FileInputStream fileInputStream = new FileInputStream(file);
 DataInputStream dataInputStream =
 new DataInputStream(fileInputStream);) {
 uint8_t byte0 = dataInputStream.readByte();
 uint8_t byte1 = dataInputStream.readByte();
 uint8_t byte2 = dataInputStream.readByte();
 uint8_t byte3 = dataInputStream.readByte();
 if (byte0 == 71 && byte1 == 77 && byte2 == 84 && byte3 == 77) {
 int int0 = dataInputStream.readInt();
 if (int0 > 195) {
 return "The server savefile appears to be from a newer version of "
 "the game and cannot be loaded.";
 }

 if (int0 > 143) {
 return nullptr;
 }

 return "The server savefile appears to be from a pre-animations "
 "version of the game and cannot be loaded.\nDue to the extent "
 "of changes required to implement animations, saves from "
 "earlier versions are not compatible.";
 }

 string = "The server savefile appears to be from an old version of the "
 "game and cannot be loaded.";
 }

 return string;
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 } else {
 DebugLog.log(
 "map_t.bin does not exist, cannot determine the server's WorldVersion. "
 " This is ok the first time a server is started.");
 }

 return nullptr;
}

std::string getPoisonousBerry() { return this->poisonousBerry; }

void setPoisonousBerry(std::string_view string) {
 this->poisonousBerry = string;
}

std::string getPoisonousMushroom() { return this->poisonousMushroom; }

void setPoisonousMushroom(std::string_view string) {
 this->poisonousMushroom = string;
}

std::string getDifficulty() { return this->difficulty; }

void setDifficulty(std::string_view string) { this->difficulty = string; }

static void transmitBrokenGlass(IsoGridSquare square) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);

 try {
 if (udpConnection.RelevantTo(square.getX(), square.getY())) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddBrokenGlass.doPacket(byteBufferWriter);
 byteBufferWriter.putInt((short)square.getX());
 byteBufferWriter.putInt((short)square.getY());
 byteBufferWriter.putInt((short)square.getZ());
 PacketTypes.PacketType.AddBrokenGlass.send(udpConnection);
 }
 } catch (Throwable throwable) {
 udpConnection.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
}

static bool isServerDropPackets() { return droppedPackets > 0; }

static void receiveSyncPerks(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 uint8_t byte0 = byteBuffer.get();
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (player0 != nullptr) {
 player0.remoteSneakLvl = int0;
 player0.remoteStrLvl = int1;
 player0.remoteFitLvl = int2;

 for (int int3 = 0; int3 < udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int3);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection0);
 if (player1 != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncPerks.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 PacketTypes.PacketType.SyncPerks.send(udpConnection1);
 } catch (Throwable throwable) {
 udpConnection0.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
}

static void receiveSyncWeight(ByteBuffer byteBuffer,
 UdpConnection udpConnection0, short var2) {
 uint8_t byte0 = byteBuffer.get();
 double double0 = byteBuffer.getDouble();
 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (player0 != nullptr) {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection0);
 if (player1 != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncWeight.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 byteBufferWriter.putDouble(double0);
 PacketTypes.PacketType.SyncWeight.send(udpConnection1);
 } catch (Throwable throwable) {
 udpConnection0.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
}

static void receiveSyncEquippedRadioFreq(ByteBuffer byteBuffer,
 UdpConnection udpConnection0,
 short var2) {
 uint8_t byte0 = byteBuffer.get();
 int int0 = byteBuffer.getInt();
 std::vector arrayList = new ArrayList();

 for (int int1 = 0; int1 < int0; int1++) {
 arrayList.add(byteBuffer.getInt());
 }

 IsoPlayer player0 = getPlayerFromConnection(udpConnection0, byte0);
 if (player0 != nullptr) {
 for (int int2 = 0; int2 < udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection1 = udpEngine.connections.get(int2);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID()) {
 IsoPlayer player1 = getAnyPlayerFromConnection(udpConnection0);
 if (player1 != nullptr) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncEquippedRadioFreq.doPacket(
 byteBufferWriter);
 byteBufferWriter.putShort(player0.OnlineID);
 byteBufferWriter.putInt(int0);

 for (int int3 = 0; int3 < arrayList.size(); int3++) {
 byteBufferWriter.putInt((Integer)arrayList.get(int3);
 }

 PacketTypes.PacketType.SyncEquippedRadioFreq.send(udpConnection1);
 } catch (Throwable throwable) {
 udpConnection0.cancelPacket();
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
}

static void receiveGlobalModData(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 GlobalModData.instance.receive(byteBuffer);
}

static void receiveGlobalModDataRequest(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 GlobalModData.instance.receiveRequest(byteBuffer, udpConnection);
}

static void receiveSendSafehouseInvite(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 IsoPlayer player = getPlayerByUserName(string2);
 long long0 = IDToAddressMap.get(player.getOnlineID());
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = udpEngine.connections.get(int4);
 if (udpConnection.getConnectedGUID() == long0) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SendSafehouseInvite.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.SendSafehouseInvite.send(udpConnection);
 break;
 }
 }
}

static void receiveAcceptedSafehouseInvite(ByteBuffer byteBuffer,
 UdpConnection var1, short var2) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 std::string string2 = GameWindow.ReadString(byteBuffer);
 int int0 = byteBuffer.getInt();
 int int1 = byteBuffer.getInt();
 int int2 = byteBuffer.getInt();
 int int3 = byteBuffer.getInt();
 SafeHouse safeHouse = SafeHouse.getSafeHouse(int0, int1, int2, int3);
 if (safeHouse != nullptr) {
 safeHouse.addPlayer(string2);
 } else {
 DebugLog.log(
 "WARN: player '" + string2 +
 "' accepted the invitation, but the safehouse not found for x=" + int0 +
 " y=" + int1 + " w=" + int2 + " h=" + int3);
 }

 for (int int4 = 0; int4 < udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = udpEngine.connections.get(int4);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AcceptedSafehouseInvite.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(string0);
 byteBufferWriter.putUTF(string1);
 byteBufferWriter.putUTF(string2);
 byteBufferWriter.putInt(int0);
 byteBufferWriter.putInt(int1);
 byteBufferWriter.putInt(int2);
 byteBufferWriter.putInt(int3);
 PacketTypes.PacketType.AcceptedSafehouseInvite.send(udpConnection);
 }
}

static void sendRadioPostSilence() {
 for (int int0 = 0; int0 < udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = udpEngine.connections.get(int0);
 if (udpConnection.statistic.enable == 3) {
 sendShortStatistic(udpConnection);
 }
 }
}

static void sendRadioPostSilence(UdpConnection udpConnection) {
 try {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RadioPostSilenceEvent.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)(ZomboidRadio.POST_RADIO_SILENCE ? 1 : 0);
 PacketTypes.PacketType.RadioPostSilenceEvent.send(udpConnection);
 } catch (Exception exception) {
 exception.printStackTrace();
 udpConnection.cancelPacket();
 }
}

static void receiveSneezeCough(ByteBuffer byteBuffer,
 UdpConnection udpConnection1, short var2) {
 short short0 = byteBuffer.getShort();
 uint8_t byte0 = byteBuffer.get();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player != nullptr) {
 float float0 = player.x;
 float float1 = player.y;
 int int0 = 0;

 for (int int1 = udpEngine.connections.size(); int0 < int1; int0++) {
 UdpConnection udpConnection0 = udpEngine.connections.get(int0);
 if (udpConnection1.getConnectedGUID() !=
 udpConnection0.getConnectedGUID() &&
 udpConnection0.RelevantTo(float0, float1) {
 ByteBufferWriter byteBufferWriter = udpConnection0.startPacket();
 PacketTypes.PacketType.SneezeCough.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(short0);
 byteBufferWriter.putByte(byte0);
 PacketTypes.PacketType.SneezeCough.send(udpConnection0);
 }
 }
 }
}

static void receiveBurnCorpse(ByteBuffer byteBuffer, UdpConnection var1,
 short var2) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 IsoPlayer player = IDToPlayerMap.get(short0);
 if (player.empty()) {
 DebugLog.Network.warn("Player not found by id " + short0);
 } else {
 IsoDeadBody deadBody = IsoDeadBody.getDeadBody(short1);
 if (deadBody.empty()) {
 DebugLog.Network.warn("Corpse not found by id " + short1);
 } else {
 float float0 =
 IsoUtils.DistanceTo(player.x, player.y, deadBody.x, deadBody.y);
 if (float0 <= 1.8F) {
 IsoFireManager.StartFire(deadBody.getCell(), deadBody.getSquare(), true,
 100);
 } else {
 DebugLog.Network.warn("Distance between player and corpse too big: " +
 float0);
 }
 }
 }
}

static void sendValidatePacket(UdpConnection udpConnection, bool boolean0,
 bool boolean1, bool boolean2) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();

 try {
 ValidatePacket validatePacket = new ValidatePacket();
 validatePacket.setSalt(udpConnection.validator.getSalt(), boolean0,
 boolean1, boolean2);
 PacketTypes.PacketType.Validate.doPacket(byteBufferWriter);
 validatePacket.write(byteBufferWriter);
 PacketTypes.PacketType.Validate.send(udpConnection);
 validatePacket.log(GameClient.connection, "send-packet");
 } catch (Exception exception) {
 udpConnection.cancelPacket();
 DebugLog.Multiplayer.printException(exception, "SendValidatePacket: failed",
 LogSeverity.Error);
 }
}

static void receiveValidatePacket(ByteBuffer byteBuffer,
 UdpConnection udpConnection, short var2) {
 ValidatePacket validatePacket = new ValidatePacket();
 validatePacket.parse(byteBuffer, udpConnection);
 validatePacket.log(GameClient.connection, "receive-packet");
 if (validatePacket.isConsistent()) {
 validatePacket.process(udpConnection);
 }
}

private
static class CCFilter {
 std::string command;
 bool allow;
 GameServer.CCFilter next;

 bool matches(std::string_view string) {
 return this->command == string) || "*" == this->command);
 }

 bool passes(std::string_view string) {
 if (this->matches(string) {
 return this->allow;
 } else {
 return this->next.empty() ? true : this->next.passes(string);
 }
 }
}

private static class DelayedConnection implements IZomboidPacket {
 UdpConnection connection;
 bool connect;
 std::string hostString;

public
 DelayedConnection(UdpConnection udpConnection, bool boolean0) {
 this->connection = udpConnection;
 this->connect = boolean0;
 if (boolean0) {
 try {
 this->hostString = udpConnection.getInetSocketAddress().getHostString();
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 bool isConnect() { return this->connect; }

 bool isDisconnect() { return !this->connect; }
}

private static class s_performance {
 static const PerformanceProfileFrameProbe frameStep =
 new PerformanceProfileFrameProbe("GameServer.frameStep");
 static const PerformanceProfileProbe mainLoopDealWithNetData =
 new PerformanceProfileProbe("GameServer.mainLoopDealWithNetData");
 static const PerformanceProfileProbe RCONServerUpdate =
 new PerformanceProfileProbe("RCONServer.update");
}
}
} // namespace network
} // namespace zombie
