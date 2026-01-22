#pragma once
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/WorldSoundManager/WorldSound.h"
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
#include "zombie/characters/IsoZombie/ZombieSound.h"
#include "zombie/characters/Safety.h"
#include "zombie/characters/SafetySystemManager.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/skills/CustomPerks.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
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
#include "zombie/core/raknet/RakNetPeerInterface.h"
#include "zombie/core/raknet/RakVoice.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/UdpConnection/ChecksumState.h"
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
#include "zombie/iso/IsoMetaGrid/Zone.h"
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
#include "zombie/network/GameServer/1.h"
#include "zombie/network/GameServer/CCFilter.h"
#include "zombie/network/GameServer/DelayedConnection.h"
#include "zombie/network/GameServer/s_performance.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerWorldDatabase/LogonResult.h"
#include "zombie/network/Userlog/UserlogType.h"
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
#include "zombie/network/packets/PlayerPacket/l_receive.h"
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
#include "zombie/vehicles/BaseVehicle/Authorization.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/moddata/GlobalModData.h"
#include "zombie/worldMap/WorldMapRemotePlayer.h"
#include "zombie/worldMap/WorldMapRemotePlayers.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace network {


class GameServer {
public:
    static const int MAX_PLAYERS = 512;
    static const int TimeLimitForProcessPackets = 70;
    static const int PacketsUpdateRate = 200;
    static const int FPS = 10;
   private static const std::unordered_map<std::string, CCFilter> ccFilters = std::make_unique<std::unordered_map<>>();
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
   public static const std::unordered_map<int16_t, int64_t> IDToAddressMap = std::make_unique<std::unordered_map<>>();
   public static const std::unordered_map<int16_t, IsoPlayer> IDToPlayerMap = std::make_unique<std::unordered_map<>>();
   public static const std::vector<IsoPlayer> Players = std::make_unique<std::vector<>>();
    static float timeSinceKeepAlive = 0.0F;
    static int MaxTicksSinceKeepAliveBeforeStall = 60;
   public static const std::unordered_set<UdpConnection> DebugPlayer = std::make_unique<std::unordered_set<>>();
    static int ResetID = 0;
   public static const std::vector<std::string> ServerMods = std::make_unique<std::vector<>>();
   public static const std::vector<int64_t> WorkshopItems = std::make_unique<std::vector<>>();
   public static std::string[] WorkshopInstallFolders;
   public static long[] WorkshopTimeStamps;
    static std::string ServerName = "servertest";
   public static const DiscordBot discordBot = std::make_shared<DiscordBot>(
      ServerName, (var0, var1) -> ChatServer.getInstance().sendMessageFromDiscordToGeneralChat(var0, var1)
   );
    static std::string checksum = "";
    static std::string GameMap = "Muldraugh, KY";
    static bool bFastForward;
   public static const std::unordered_map<std::string, int> transactionIDMap = std::make_unique<std::unordered_map<>>();
    static const ObjectsSyncRequests worldObjectsServerSyncReq = std::make_shared<ObjectsSyncRequests>(false);
    static std::string ip = "127.0.0.1";
    static int count = 0;
   private static const UdpConnection[] SlotToConnection = new UdpConnection[512];
   private static const std::unordered_map<IsoPlayer, int64_t> PlayerToAddressMap = std::make_unique<std::unordered_map<>>();
   private static const std::vector<int> alreadyRemoved = std::make_unique<std::vector<>>();
    static bool bDone;
    static bool launched = false;
   private static const std::vector<std::string> consoleCommands = std::make_unique<std::vector<>>();
   private static const std::unordered_map<int64_t, IZomboidPacket> MainLoopPlayerUpdate = std::make_unique<std::unordered_map<>>();
   private static const ConcurrentLinkedQueue<IZomboidPacket> MainLoopPlayerUpdateQ = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<IZomboidPacket> MainLoopNetDataHighPriorityQ = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<IZomboidPacket> MainLoopNetDataQ = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const std::vector<IZomboidPacket> MainLoopNetData2 = std::make_unique<std::vector<>>();
   private static const std::unordered_map<int16_t, Vector2> playerToCoordsMap = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int16_t, int> playerMovedToFastMap = std::make_unique<std::unordered_map<>>();
    static ByteBuffer large_file_bb = ByteBuffer.allocate(2097152);
    static long previousSave = Calendar.getInstance().getTimeInMillis();
    std::string poisonousBerry = nullptr;
    std::string poisonousMushroom = nullptr;
    std::string difficulty = "Hardcore";
    static int droppedPackets = 0;
    static int countOfDroppedPackets = 0;
    static int countOfDroppedConnections = 0;
    static UdpConnection removeZombiesConnection = nullptr;
    static UpdateLimit calcCountPlayersInRelevantPositionLimiter = std::make_shared<UpdateLimit>(2000L);
    static UpdateLimit sendWorldMapPlayerPositionLimiter = std::make_shared<UpdateLimit>(1000L);
    static LoginQueue loginQueue = std::make_shared<LoginQueue>();
    static int mainCycleExceptionLogCount = 25;
    static Thread MainThread;
   public static const std::vector<IsoPlayer> tempPlayers = std::make_unique<std::vector<>>();

    static void PauseAllClients() {
    std::string var0 = "[SERVERMSG] Server saving...Please wait";

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
    ByteBufferWriter var3 = var2.startPacket();
         PacketType.StartPause.doPacket(var3);
         var3.putUTF(var0);
         PacketType.StartPause.send(var2);
      }
   }

    static void UnPauseAllClients() {
    std::string var0 = "[SERVERMSG] Server saved game...enjoy :)";

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
    ByteBufferWriter var3 = var2.startPacket();
         PacketType.StopPause.doPacket(var3);
         var3.putUTF(var0);
         PacketType.StopPause.send(var2);
      }
   }

    static std::string parseIPFromCommandline(std::string[] var0, int var1, const std::string& var2) {
      if (var1 == var0.length - 1) {
         DebugLog.log("expected argument after \"" + var2 + "\"");
         System.exit(0);
      } else if (var0[var1 + 1].trim().empty()) {
         DebugLog.log("empty argument given to \"\" + option + \"\"");
         System.exit(0);
      } else {
         std::string[] var3 = var0[var1 + 1].trim().split("\\.");
         if (var3.length == 4) {
            for (int var4 = 0; var4 < 4; var4++) {
               try {
    int var5 = int.parseInt(var3[var4]);
                  if (var5 < 0 || var5 > 255) {
                     DebugLog.log("expected IP address after \"" + var2 + "\", got \"" + var0[var1 + 1] + "\"");
                     System.exit(0);
                  }
               } catch (NumberFormatException var6) {
                  DebugLog.log("expected IP address after \"" + var2 + "\", got \"" + var0[var1 + 1] + "\"");
                  System.exit(0);
               }
            }
         } else {
            DebugLog.log("expected IP address after \"" + var2 + "\", got \"" + var0[var1 + 1] + "\"");
            System.exit(0);
         }
      }

      return var0[var1 + 1];
   }

    static int parsePortFromCommandline(std::string[] var0, int var1, const std::string& var2) {
      if (var1 == var0.length - 1) {
         DebugLog.log("expected argument after \"" + var2 + "\"");
         System.exit(0);
      } else if (var0[var1 + 1].trim().empty()) {
         DebugLog.log("empty argument given to \"" + var2 + "\"");
         System.exit(0);
      } else {
         try {
            return int.parseInt(var0[var1 + 1].trim());
         } catch (NumberFormatException var4) {
            DebugLog.log("expected an integer after \"" + var2 + "\"");
            System.exit(0);
         }
      }

      return -1;
   }

    static bool parseBooleanFromCommandline(std::string[] var0, int var1, const std::string& var2) {
      if (var1 == var0.length - 1) {
         DebugLog.log("expected argument after \"" + var2 + "\"");
         System.exit(0);
      } else if (var0[var1 + 1].trim().empty()) {
         DebugLog.log("empty argument given to \"" + var2 + "\"");
         System.exit(0);
      } else {
    std::string var3 = var0[var1 + 1].trim();
         if ("true".equalsIgnoreCase(var3)) {
    return true;
         }

         if ("false".equalsIgnoreCase(var3)) {
    return false;
         }

         DebugLog.log("expected true or false after \"" + var2 + "\"");
         System.exit(0);
      }

    return false;
   }

    static void setupCoop() {
      CoopSlave.init();
   }

    static void main(std::string[] var0) {
      MainThread = Thread.currentThread();
      bServer = true;
      bSoftReset = System.getProperty("softreset") != nullptr;

      for (int var1 = 0; var1 < var0.length; var1++) {
         if (var0[var1] != nullptr) {
            if (var0[var1].startsWith("-cachedir=")) {
               ZomboidFileSystem.instance.setCacheDir(var0[var1].replace("-cachedir=", "").trim());
            } else if (var0[var1] == "-coop")) {
               bCoop = true;
            }
         }
      }

      if (bCoop) {
         try {
            CoopSlave.initStreams();
         } catch (FileNotFoundException var68) {
            var68.printStackTrace();
         }
      } else {
         try {
    std::string var74 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "server-console.txt";
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var74);
    PrintStream var3 = std::make_shared<PrintStream>(var2, true);
            System.setOut(std::make_shared<ProxyPrintStream>(System.out, var3));
            System.setErr(std::make_shared<ProxyPrintStream>(System.err, var3));
         } catch (FileNotFoundException var67) {
            var67.printStackTrace();
         }
      }

      DebugLog.init();
      LoggerManager.init();
      DebugLog.log("cachedir set to \"" + ZomboidFileSystem.instance.getCacheDir() + "\"");
      if (bCoop) {
         try {
            setupCoop();
            CoopSlave.status("UI_ServerStatus_Initialising");
         } catch (FileNotFoundException var66) {
            var66.printStackTrace();
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

      DebugLog.General.println("version=%s demo=%s", Core.getInstance().getVersion(), false);
      DebugLog.General.println("revision=%s date=%s time=%s", "", "", "");

      for (int var75 = 0; var75 < var0.length; var75++) {
         if (var0[var75] != nullptr) {
            if (!var0[var75].startsWith("-disablelog=")) {
               if (var0[var75].startsWith("-debuglog=")) {
                  for (std::string var90 : var0[var75].replace("-debuglog=", "").split(",")) {
                     try {
                        DebugLog.setLogEnabled(DebugType.valueOf(var90), true);
                     } catch (IllegalArgumentException var64) {
                     }
                  }
               } else if (var0[var75] == "-adminusername")) {
                  if (var75 == var0.length - 1) {
                     DebugLog.log("expected argument after \"-adminusername\"");
                     System.exit(0);
                  } else if (!ServerWorldDatabase.isValidUserName(var0[var75 + 1].trim())) {
                     DebugLog.log("invalid username given to \"-adminusername\"");
                     System.exit(0);
                  } else {
                     ServerWorldDatabase.instance.CommandLineAdminUsername = var0[var75 + 1].trim();
                     var75++;
                  }
               } else if (var0[var75] == "-adminpassword")) {
                  if (var75 == var0.length - 1) {
                     DebugLog.log("expected argument after \"-adminpassword\"");
                     System.exit(0);
                  } else if (var0[var75 + 1].trim().empty()) {
                     DebugLog.log("empty argument given to \"-adminpassword\"");
                     System.exit(0);
                  } else {
                     ServerWorldDatabase.instance.CommandLineAdminPassword = var0[var75 + 1].trim();
                     var75++;
                  }
               } else if (!var0[var75].startsWith("-cachedir=")) {
                  if (var0[var75] == "-ip")) {
                     IPCommandline = parseIPFromCommandline(var0, var75, "-ip");
                     var75++;
                  } else if (var0[var75] == "-gui")) {
                     GUICommandline = true;
                  } else if (var0[var75] == "-nosteam")) {
                     System.setProperty("zomboid.steam", "0");
                  } else if (var0[var75] == "-statistic")) {
    int var78 = parsePortFromCommandline(var0, var75, "-statistic");
                     if (var78 >= 0) {
                        MPStatistic.getInstance().setPeriod(var78);
                        MPStatistic.getInstance().writeEnabled(true);
                     }
                  } else if (var0[var75] == "-port")) {
                     PortCommandline = parsePortFromCommandline(var0, var75, "-port");
                     var75++;
                  } else if (var0[var75] == "-udpport")) {
                     UDPPortCommandline = parsePortFromCommandline(var0, var75, "-udpport");
                     var75++;
                  } else if (var0[var75] == "-steamvac")) {
                     SteamVACCommandline = parseBooleanFromCommandline(var0, var75, "-steamvac");
                     var75++;
                  } else if (var0[var75] == "-servername")) {
                     if (var75 == var0.length - 1) {
                        DebugLog.log("expected argument after \"-servername\"");
                        System.exit(0);
                     } else if (var0[var75 + 1].trim().empty()) {
                        DebugLog.log("empty argument given to \"-servername\"");
                        System.exit(0);
                     } else {
                        ServerName = var0[var75 + 1].trim();
                        var75++;
                     }
                  } else if (var0[var75] == "-coop")) {
                     ServerWorldDatabase.instance.doAdmin = false;
                  } else {
                     DebugLog.log("unknown option \"" + var0[var75] + "\"");
                  }
               }
            } else {
               for (std::string var5 : var0[var75].replace("-disablelog=", "").split(",")) {
                  if ("All" == var5)) {
                     for (DebugType var9 : DebugType.values()) {
                        DebugLog.setLogEnabled(var9, false);
                     }
                  } else {
                     try {
                        DebugLog.setLogEnabled(DebugType.valueOf(var5), false);
                     } catch (IllegalArgumentException var65) {
                     }
                  }
               }
            }
         }
      }

      DebugLog.log("server name is \"" + ServerName + "\"");
    std::string var76 = isWorldVersionUnsupported();
      if (var76 != nullptr) {
         DebugLog.log(var76);
         CoopSlave.status(var76);
      } else {
         SteamUtils.init();
         RakNetPeerInterface.init();
         ZombiePopulationManager.init();

         try {
            ZomboidFileSystem.instance.init();
            Languages.instance.init();
            Translator.loadFiles();
         } catch (Exception var63) {
            DebugLog.General.printException(var63, "Exception Thrown", LogSeverity.Error);
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
    std::string var80 = ServerOptions.instance.PublicName.getValue();
            if (var80 == nullptr || var80.empty()) {
               ServerOptions.instance.PublicName.setValue("My PZ Server");
            }
         }

    std::string var81 = ServerOptions.instance.Map.getValue();
         if (var81 != nullptr && !var81.trim().empty()) {
            GameMap = var81.trim();
            if (GameMap.contains(";")) {
               std::string[] var84 = GameMap.split(";");
               var81 = var84[0];
            }

            Core.GameMap = var81.trim();
         }

    std::string var85 = ServerOptions.instance.Mods.getValue();
         if (var85 != nullptr) {
            std::string[] var87 = var85.split(";");

    for (auto& var103 : var87)               if (!var103.trim().empty()) {
                  ServerMods.push_back(var103.trim());
               }
            }
         }

         if (SteamUtils.isSteamModeEnabled()) {
    int var88 = ServerOptions.instance.SteamVAC.getValue() ? 3 : 2;
            if (!SteamGameServer.Init(IPCommandline, DEFAULT_PORT, UDPPort, var88, Core.getInstance().getSteamServerVersion())) {
               SteamUtils.shutdown();
               return;
            }

            SteamGameServer.SetProduct("zomboid");
            SteamGameServer.SetGameDescription("Project Zomboid");
            SteamGameServer.SetModDir("zomboid");
            SteamGameServer.SetDedicatedServer(true);
            SteamGameServer.SetMaxPlayerCount(ServerOptions.getInstance().getMaxPlayers());
            SteamGameServer.SetServerName(ServerOptions.instance.PublicName.getValue());
            SteamGameServer.SetMapName(ServerOptions.instance.Map.getValue());
            if (ServerOptions.instance.Public.getValue()) {
               SteamGameServer.SetGameTags(CoopSlave.instance != nullptr ? "hosted" : "");
            } else {
               SteamGameServer.SetGameTags("hidden" + (CoopSlave.instance != nullptr ? ";hosted" : ""));
            }

            SteamGameServer.SetKeyValue("description", ServerOptions.instance.PublicDescription.getValue());
            SteamGameServer.SetKeyValue("version", Core.getInstance().getVersion());
            SteamGameServer.SetKeyValue("open", ServerOptions.instance.Open.getValue() ? "1" : "0");
            SteamGameServer.SetKeyValue("public", ServerOptions.instance.Public.getValue() ? "1" : "0");
    std::string var92 = ServerOptions.instance.Mods.getValue();
    int var96 = 0;
            std::string[] var100 = var92.split(";");

    for (auto& var11 : var100)               if (!StringUtils.isNullOrWhitespace(var11)) {
                  var96++;
               }
            }

            if (var92.length() > 128) {
    std::stringstream var105 = new std::stringstream();
               std::string[] var111 = var92.split(";");

    for (auto& var13 : var111)                  if (var105.length() + 1 + var13.length() > 128) {
                     break;
                  }

                  if (var105.length() > 0) {
                     var105.append(';');
                  }

                  var105.append(var13);
               }

               var92 = var105;
            }

            SteamGameServer.SetKeyValue("mods", var92);
            SteamGameServer.SetKeyValue("modCount", std::string.valueOf(var96));
            SteamGameServer.SetKeyValue("pvp", ServerOptions.instance.PVP.getValue() ? "1" : "0");
            if (bDebug) {
            }

    std::string var106 = ServerOptions.instance.WorkshopItems.getValue();
            if (var106 != nullptr) {
               std::string[] var112 = var106.split(";");

    for (auto& var123 : var112)                  var123 = var123.trim();
                  if (!var123.empty() && SteamUtils.isValidSteamID(var123)) {
                     WorkshopItems.push_back(SteamUtils.convertStringToSteamID(var123));
                  }
               }
            }

            SteamWorkshop.init();
            SteamGameServer.LogOnAnonymous();
            SteamGameServer.EnableHeartBeats(true);
            DebugLog.log("Waiting for response from Steam servers");

            while (true) {
               SteamUtils.runLoop();
    int var113 = SteamGameServer.GetSteamServersConnectState();
               if (var113 == SteamGameServer.STEAM_SERVERS_CONNECTED) {
                  if (!GameServerWorkshopItems.Install(WorkshopItems)) {
                     return;
                  }
                  break;
               }

               if (var113 == SteamGameServer.STEAM_SERVERS_CONNECTFAILURE) {
                  DebugLog.log("Failed to connect to Steam servers");
                  SteamUtils.shutdown();
                  return;
               }

               try {
                  Thread.sleep(100L);
               } catch (InterruptedException var62) {
               }
            }
         }

         ZipBackup.onStartup();
         ZipBackup.onVersion();
    int var89 = 0;

         try {
            ServerWorldDatabase.instance.create();
         } catch (ClassNotFoundException | SQLException var61) {
            var61.printStackTrace();
         }

         if (ServerOptions.instance.UPnP.getValue()) {
            DebugLog.log("Router detection/configuration starting.");
            DebugLog.log("If the server hangs here, set UPnP=false.");
            PortMapper.startup();
            if (PortMapper.discover()) {
               DebugLog.log("UPnP-enabled internet gateway found: " + PortMapper.getGatewayInfo());
    std::string var93 = PortMapper.getExternalAddress();
               DebugLog.log("External IP address: " + var93);
               DebugLog.log("trying to setup port forwarding rules...");
    int var97 = 86400;
    bool var101 = true;
               if (PortMapper.addMapping(DEFAULT_PORT, DEFAULT_PORT, "PZ Server default port", "UDP", var97, var101)) {
                  DebugLog.log(DebugType.Network, "Default port has been mapped successfully");
               } else {
                  DebugLog.log(DebugType.Network, "Failed to map default port");
               }

               if (SteamUtils.isSteamModeEnabled()) {
    int var107 = ServerOptions.instance.UDPPort.getValue();
                  if (PortMapper.addMapping(var107, var107, "PZ Server UDPPort", "UDP", var97, var101)) {
                     DebugLog.log(DebugType.Network, "AdditionUDPPort has been mapped successfully");
                  } else {
                     DebugLog.log(DebugType.Network, "Failed to map AdditionUDPPort");
                  }
               }
            } else {
               DebugLog.log(
                  DebugType.Network,
                  "No UPnP-enabled Internet gateway found, you must configure port forwarding on your gateway manually in order to make your server accessible from the Internet."
               );
            }
         }

         Core.GameMode = "Multiplayer";
         bDone = false;
         DebugLog.log(DebugType.Network, "Initialising Server Systems...");
         CoopSlave.status("UI_ServerStatus_Initialising");

         try {
            doMinimumInit();
         } catch (Exception var60) {
            DebugLog.General.printException(var60, "Exception Thrown", LogSeverity.Error);
            DebugLog.General.println("Server Terminated.");
         }

         LosUtil.init(100, 100);
         ChatServer.getInstance().init();
         DebugLog.log(DebugType.Network, "Loading world...");
         CoopSlave.status("UI_ServerStatus_LoadingWorld");

         try {
            ClimateManager.setInstance(std::make_unique<ClimateManager>());
            IsoWorld.instance.init();
         } catch (Exception var59) {
            DebugLog.General.printException(var59, "Exception Thrown", LogSeverity.Error);
            DebugLog.General.println("Server Terminated.");
            CoopSlave.status("UI_ServerStatus_Terminated");
            return;
         }

    File var94 = ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");
         if (!var94.exists()) {
            ServerOptions.instance.changeOption("ResetID", std::make_shared<int>(Rand.Next(100000000)));
         }

         try {
            SpawnPoints.instance.initServer2();
         } catch (Exception var58) {
            var58.printStackTrace();
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
         } catch (ConnectException var57) {
            var57.printStackTrace();
            SteamUtils.shutdown();
            return;
         }

         if (SteamUtils.isSteamModeEnabled()) {
            DebugLog.log("##########\nServer Steam ID " + SteamGameServer.GetSteamID() + "\n##########");
         }

    UpdateLimit var98 = std::make_shared<UpdateLimit>(100L);
         PerformanceSettings.setLockFPS(10);
    IngameState var102 = std::make_shared<IngameState>();
    float var108 = 0.0F;
         float[] var114 = new float[20];

         for (int var117 = 0; var117 < 20; var117++) {
            var114[var117] = PerformanceSettings.getLockFPS();
         }

    float var118 = PerformanceSettings.getLockFPS();
    long var121 = System.currentTimeMillis();
    long var125 = System.currentTimeMillis();
         if (!SteamUtils.isSteamModeEnabled()) {
            PublicServerUtil.init();
            PublicServerUtil.insertOrUpdate();
         }

         ServerLOS.init();
         NetworkAIParams.Init();
    int var15 = ServerOptions.instance.RCONPort.getValue();
    std::string var16 = ServerOptions.instance.RCONPassword.getValue();
         if (var15 != 0 && var16 != nullptr && !var16.empty()) {
    std::string var17 = System.getProperty("rconlo");
            RCONServer.init(var15, var16, var17 != nullptr);
         }

         GlobalObject.refreshAnimSets(true);

         while (!bDone) {
            try {
    long var127 = System.nanoTime();
               MPStatistics.countServerNetworkingFPS();
               MainLoopNetData2.clear();

               for (IZomboidPacket var19 = MainLoopNetDataHighPriorityQ.poll(); var19 != nullptr; var19 = MainLoopNetDataHighPriorityQ.poll()) {
                  MainLoopNetData2.push_back(var19);
               }

               MPStatistic.getInstance().setPacketsLength(MainLoopNetData2.size());

               for (int var128 = 0; var128 < MainLoopNetData2.size(); var128++) {
    IZomboidPacket var20 = MainLoopNetData2.get(var128);
                  if (var20.isConnect()) {
    UdpConnection var21 = ((DelayedConnection)var20).connection;
                     LoggerManager.getLogger("user").write("added connection index=" + var21.index + " " + ((DelayedConnection)var20).hostString);
                     udpEngine.connections.push_back(var21);
                  } else if (var20.isDisconnect()) {
    UdpConnection var141 = ((DelayedConnection)var20).connection;
                     LoginQueue.disconnect(var141);
                     LoggerManager.getLogger("user").write(var141.idStr + " \"" + var141.username + "\" removed connection index=" + var141.index);
                     udpEngine.connections.remove(var141);
                     disconnect(var141, "receive-disconnect");
                  } else {
                     mainLoopDealWithNetData((ZomboidNetData)var20);
                  }
               }

               MainLoopPlayerUpdate.clear();

               for (IZomboidPacket var129 = MainLoopPlayerUpdateQ.poll(); var129 != nullptr; var129 = MainLoopPlayerUpdateQ.poll()) {
    ZomboidNetData var136 = (ZomboidNetData)var129;
    long var142 = var136.connection * 4L + var136.buffer.getShort(0);
    ZomboidNetData var23 = (ZomboidNetData)MainLoopPlayerUpdate.put(var142, var136);
                  if (var23 != nullptr) {
                     ZomboidNetDataPool.instance.discard(var23);
                  }
               }

               MainLoopNetData2.clear();
               MainLoopNetData2.addAll(MainLoopPlayerUpdate.values());
               MainLoopPlayerUpdate.clear();
               MPStatistic.getInstance().setPacketsLength(MainLoopNetData2.size());

               for (int var130 = 0; var130 < MainLoopNetData2.size(); var130++) {
    IZomboidPacket var137 = MainLoopNetData2.get(var130);
                  s_performance.mainLoopDealWithNetData.invokeAndMeasure((ZomboidNetData)var137, GameServer::mainLoopDealWithNetData);
               }

               MainLoopNetData2.clear();

               for (IZomboidPacket var131 = MainLoopNetDataQ.poll(); var131 != nullptr; var131 = MainLoopNetDataQ.poll()) {
                  MainLoopNetData2.push_back(var131);
               }

               for (int var132 = 0; var132 < MainLoopNetData2.size(); var132++) {
                  if (var132 % 10 == 0 && (System.nanoTime() - var127) / 1000000L > 70L) {
                     if (droppedPackets == 0) {
                        DebugLog.log("Server is too busy. Server will drop updates of vehicle's physics. Server is closed for new connections.");
                     }

                     droppedPackets += 2;
                     countOfDroppedPackets = countOfDroppedPackets + (MainLoopNetData2.size() - var132);
                     break;
                  }

    IZomboidPacket var138 = MainLoopNetData2.get(var132);
                  s_performance.mainLoopDealWithNetData.invokeAndMeasure((ZomboidNetData)var138, GameServer::mainLoopDealWithNetData);
               }

               MainLoopNetData2.clear();
               if (droppedPackets == 1) {
                  DebugLog.log(
                     "Server is working normal. Server will not drop updates of vehicle's physics. The server is open for new connections. Server dropped "
                        + countOfDroppedPackets
                        + " packets and "
                        + countOfDroppedConnections
                        + " connections."
                  );
                  countOfDroppedPackets = 0;
                  countOfDroppedConnections = 0;
               }

               droppedPackets = Math.max(0, Math.min(1000, droppedPackets - 1));
               if (!var98.Check()) {
    long var135 = PZMath.clamp((5000000L - System.nanoTime() + var127) / 1000000L, 0L, 100L);
                  if (var135 > 0L) {
                     try {
                        MPStatistic.getInstance().Main.StartSleep();
                        Thread.sleep(var135);
                        MPStatistic.getInstance().Main.EndSleep();
                     } catch (InterruptedException var56) {
                        var56.printStackTrace();
                     }
                  }
               } else {
                  MPStatistic.getInstance().Main.Start();
                  IsoCamera.frameState.frameCount++;
                  s_performance.frameStep.start();

                  try {
                     timeSinceKeepAlive = timeSinceKeepAlive + GameTime.getInstance().getMultiplier();
                     MPStatistic.getInstance().ServerMapPreupdate.Start();
                     ServerMap.instance.preupdate();
                     MPStatistic.getInstance().ServerMapPreupdate.End();
                     /* synchronized - TODO: add std::mutex */ (consoleCommands) {
                        for (int var139 = 0; var139 < consoleCommands.size(); var139++) {
    std::string var143 = consoleCommands.get(var139);

                           try {
                              if (CoopSlave.instance == nullptr || !CoopSlave.instance.handleCommand(var143)) {
                                 System.out.println(handleServerCommand(var143, nullptr));
                              }
                           } catch (Exception var69) {
                              var69.printStackTrace();
                           }
                        }

                        consoleCommands.clear();
                     }

                     if (removeZombiesConnection != nullptr) {
                        NetworkZombieManager.removeZombies(removeZombiesConnection);
                        removeZombiesConnection = nullptr;
                     }

                     s_performance.RCONServerUpdate.invokeAndMeasure(RCONServer::update);

                     try {
                        MapCollisionData.instance.updateGameState();
                        MPStatistic.getInstance().IngameStateUpdate.Start();
                        var102.update();
                        MPStatistic.getInstance().IngameStateUpdate.End();
                        VehicleManager.instance.serverUpdate();
                     } catch (Exception var55) {
                        var55.printStackTrace();
                     }

    int var134 = 0;
    int var140 = 0;

                     for (int var144 = 0; var144 < Players.size(); var144++) {
    IsoPlayer var22 = Players.get(var144);
                        if (var22.isAlive()) {
                           if (!IsoWorld.instance.CurrentCell.getObjectList().contains(var22)) {
                              IsoWorld.instance.CurrentCell.getObjectList().push_back(var22);
                           }

                           var140++;
                           if (var22.isAsleep()) {
                              var134++;
                           }
                        }

                        ServerMap.instance.characterIn(var22);
                     }

                     setFastForward(ServerOptions.instance.SleepAllowed.getValue() && var140 > 0 && var134 == var140);
    bool var145 = calcCountPlayersInRelevantPositionLimiter.Check();

                     for (int var146 = 0; var146 < udpEngine.connections.size(); var146++) {
    UdpConnection var150 = (UdpConnection)udpEngine.connections.get(var146);
                        if (var145) {
                           var150.calcCountPlayersInRelevantPosition();
                        }

                        for (int var24 = 0; var24 < 4; var24++) {
    Vector3 var25 = var150.connectArea[var24];
                           if (var25 != nullptr) {
                              ServerMap.instance.characterIn((int)var25.x, (int)var25.y, (int)var25.z);
                           }

                           ClientServerMap.characterIn(var150, var24);
                        }

                        if (var150.playerDownloadServer != nullptr) {
                           var150.playerDownloadServer.update();
                        }
                     }

                     for (int var147 = 0; var147 < IsoWorld.instance.CurrentCell.getObjectList().size(); var147++) {
    IsoMovingObject var151 = (IsoMovingObject)IsoWorld.instance.CurrentCell.getObjectList().get(var147);
                        if (dynamic_cast<IsoPlayer*>(var151) != nullptr && !Players.contains(var151)) {
                           DebugLog.log("Disconnected player in CurrentCell.getObjectList() removed");
                           IsoWorld.instance.CurrentCell.getObjectList().remove(var147--);
                        }
                     }

                     if (++var89 > 150) {
                        for (int var148 = 0; var148 < udpEngine.connections.size(); var148++) {
    UdpConnection var152 = (UdpConnection)udpEngine.connections.get(var148);

                           try {
                              if (var152.username == nullptr
                                 && !var152.awaitingCoopApprove
                                 && !LoginQueue.isInTheQueue(var152)
                                 && var152.isConnectionAttemptTimeout()) {
                                 disconnect(var152, "connection-attempt-timeout");
                                 udpEngine.forceDisconnect(var152.getConnectedGUID(), "connection-attempt-timeout");
                              }
                           } catch (Exception var54) {
                              var54.printStackTrace();
                           }
                        }

                        var89 = 0;
                     }

                     worldObjectsServerSyncReq.serverSendRequests(udpEngine);
                     MPStatistic.getInstance().ServerMapPostupdate.Start();
                     ServerMap.instance.postupdate();
                     MPStatistic.getInstance().ServerMapPostupdate.End();

                     try {
                        ServerGUI.update();
                     } catch (Exception var53) {
                        var53.printStackTrace();
                     }

                     var125 = var121;
                     var121 = System.currentTimeMillis();
    long var149 = var121 - var125;
                     var108 = 1000.0F / (float)var149;
                     if (!float.isNaN(var108)) {
                        var118 = (float)(var118 + Math.min((var108 - var118) * 0.05, 1.0));
                     }

                     GameTime.instance.FPSMultiplier = 60.0F / var118;
                     launchCommandHandler();
                     MPStatistic.getInstance().process(var149);
                     if (!SteamUtils.isSteamModeEnabled()) {
                        PublicServerUtil.update();
                        PublicServerUtil.updatePlayerCountIfChanged();
                     }

                     for (int var153 = 0; var153 < udpEngine.connections.size(); var153++) {
    UdpConnection var154 = (UdpConnection)udpEngine.connections.get(var153);
                        if (var154.checksumState == ChecksumState.Different && var154.checksumTime + 8000L < System.currentTimeMillis()) {
                           DebugLog.log("timed out connection because checksum was different");
                           var154.checksumState = ChecksumState.Init;
                           var154.forceDisconnect("checksum-timeout");
                        } else {
                           var154.validator.update();
                           if (!var154.chunkObjectState.empty()) {
                              for (byte var26 = 0; var26 < var154.chunkObjectState.size(); var26 += 2) {
    short var27 = var154.chunkObjectState.get(var26);
    short var28 = var154.chunkObjectState.get(var26 + 1);
                                 if (!var154.RelevantTo(var27 * 10 + 5, var28 * 10 + 5, var154.ChunkGridWidth * 4 * 10)) {
                                    var154.chunkObjectState.remove(var26, 2);
                                    var26 -= 2;
                                 }
                              }
                           }
                        }
                     }

                     if (sendWorldMapPlayerPositionLimiter.Check()) {
                        try {
                           sendWorldMapPlayerPosition();
                        } catch (Exception var52) {
    bool var155 = true;
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
                  } catch (Exception var71) {
                     if (mainCycleExceptionLogCount-- > 0) {
                        DebugLog.Multiplayer.printException(var71, "Server processing error", LogSeverity.Error);
                     }
                  } finally {
                     s_performance.frameStep.end();
                  }
               }
            } catch (Exception var73) {
               if (mainCycleExceptionLogCount-- > 0) {
                  DebugLog.Multiplayer.printException(var73, "Server error", LogSeverity.Error);
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
    std::make_shared<Thread>() {
            try {
    BufferedReader var0 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(System.in));

               while (true) {
    std::string var1 = var0.readLine();
                  if (var1 == nullptr) {
                     consoleCommands.push_back("process-status@eof");
                     break;
                  }

                  if (!var1.empty()) {
                     System.out.println("command entered via server console (System.in): \"" + var1 + "\"");
                     /* synchronized - TODO: add std::mutex */ (consoleCommands) {
                        consoleCommands.push_back(var1);
                     }
                  }
               }
            } catch (Exception var5) {
               var5.printStackTrace();
            }
         }, "command handler").start();
      }
   }

    static std::string rcon(const std::string& var0) {
      try {
    return handleServerCommand();
      } catch (Throwable var2) {
         var2.printStackTrace();
    return nullptr;
      }
   }

    static std::string handleServerCommand(const std::string& var0, UdpConnection var1) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    std::string var2 = "admin";
    std::string var3 = "admin";
         if (var1 != nullptr) {
            var2 = var1.username;
            var3 = PlayerType.toString(var1.accessLevel);
         }

         if (var1 != nullptr && var1.isCoopHost) {
            var3 = "admin";
         }

    Class var4 = CommandBase.findCommandCls(var0);
         if (var4 != nullptr) {
    Constructor var5 = var4.getConstructors()[0];

            try {
    CommandBase var6 = (CommandBase)var5.newInstance(var2, var3, var0, var1);
               return var6.Execute();
            } catch (InvocationTargetException var7) {
               var7.printStackTrace();
               return "A InvocationTargetException error occured";
            } catch (IllegalAccessException var8) {
               var8.printStackTrace();
               return "A IllegalAccessException error occured";
            } catch (InstantiationException var9) {
               var9.printStackTrace();
               return "A InstantiationException error occured";
            } catch (SQLException var10) {
               var10.printStackTrace();
               return "A SQL error occured";
            }
         } else {
            return "Unknown command " + var0;
         }
      }
   }

    static void sendTeleport(IsoPlayer var0, float var1, float var2, float var3) {
    UdpConnection var4 = getConnectionFromPlayer(var0);
      if (var4 == nullptr) {
         DebugLog.log("No connection found for user " + var0.getUsername());
      } else {
    ByteBufferWriter var5 = var4.startPacket();
         PacketType.Teleport.doPacket(var5);
         var5.putByte((byte)0);
         var5.putFloat(var1);
         var5.putFloat(var2);
         var5.putFloat(var3);
         PacketType.Teleport.send(var4);
         if (var4.players[0] != nullptr && var4.players[0].getNetworkCharacterAI() != nullptr) {
            var4.players[0].getNetworkCharacterAI().resetSpeedLimiter();
         }
      }
   }

    static void receiveTeleport(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    float var4 = var0.getFloat();
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    IsoPlayer var7 = getPlayerByRealUserName(var3);
      if (var7 != nullptr) {
    UdpConnection var8 = getConnectionFromPlayer(var7);
         if (var8 != nullptr) {
    ByteBufferWriter var9 = var8.startPacket();
            PacketType.Teleport.doPacket(var9);
            var9.putByte((byte)var7.PlayerIndex);
            var9.putFloat(var4);
            var9.putFloat(var5);
            var9.putFloat(var6);
            PacketType.Teleport.send(var8);
            if (var7.getNetworkCharacterAI() != nullptr) {
               var7.getNetworkCharacterAI().resetSpeedLimiter();
            }

            if (var7.isAsleep()) {
               var7.setAsleep(false);
               var7.setAsleepTime(0.0F);
               sendWakeUpPlayer(var7, nullptr);
            }
         }
      }
   }

    static void sendPlayerExtraInfo(IsoPlayer var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
    ByteBufferWriter var4 = var3.startPacket();
         PacketType.ExtraInfo.doPacket(var4);
         var4.putShort(var0.OnlineID);
         var4.putUTF(var0.accessLevel);
         var4.putByte((byte)(var0.isGodMod() ? 1 : 0));
         var4.putByte((byte)(var0.isGhostMode() ? 1 : 0));
         var4.putByte((byte)(var0.isInvisible() ? 1 : 0));
         var4.putByte((byte)(var0.isNoClip() ? 1 : 0));
         var4.putByte((byte)(var0.isShowAdminTag() ? 1 : 0));
         PacketType.ExtraInfo.send(var3);
      }
   }

    static void receiveExtraInfo(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    bool var4 = var0.get() == 1;
    bool var5 = var0.get() == 1;
    bool var6 = var0.get() == 1;
    bool var7 = var0.get() == 1;
    bool var8 = var0.get() == 1;
    bool var9 = var0.get() == 1;
    IsoPlayer var10 = getPlayerFromConnection(var1, var3);
      if (var10 != nullptr) {
         var10.setGodMod(var4);
         var10.setGhostMode(var5);
         var10.setInvisible(var6);
         var10.setNoClip(var7);
         var10.setShowAdminTag(var8);
         var10.setCanHearAll(var9);
         sendPlayerExtraInfo(var10, var1);
      }
   }

    static void receiveAddXp(ByteBuffer var0, UdpConnection var1, short var2) {
    AddXp var3 = std::make_shared<AddXp>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         if (!canModifyPlayerStats(var1, var3.target.getCharacter())) {
            PacketType.AddXP.onUnauthorized(var1);
         } else {
            var3.process();
            if (canModifyPlayerStats(var1, nullptr)) {
               var3.target.getCharacter().getXp().recalcSumm();
            }

            for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
               if (var5.getConnectedGUID() != var1.getConnectedGUID() && var5.getConnectedGUID() == PlayerToAddressMap.get(var3.target.getCharacter())) {
    ByteBufferWriter var6 = var5.startPacket();
                  PacketType.AddXP.doPacket(var6);
                  var3.write(var6);
                  PacketType.AddXP.send(var5);
               }
            }
         }
      }
   }

    static bool canSeePlayerStats(UdpConnection var0) {
      return var0.accessLevel != 1;
   }

    static bool canModifyPlayerStats(UdpConnection var0, IsoPlayer var1) {
      return (var0.accessLevel & 56) != 0 || var0.havePlayer(var1);
   }

    static void receiveSyncXP(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoPlayer var3 = IDToPlayerMap.get(var0.getShort());
      if (var3 != nullptr) {
         if (!canModifyPlayerStats(var1, var3)) {
            PacketType.SyncXP.onUnauthorized(var1);
         } else {
            if (var3 != nullptr && !var3.isDead()) {
               try {
                  var3.getXp().load(var0, 195);
               } catch (IOException var9) {
                  var9.printStackTrace();
               }

               for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
                  if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
                     PacketType.SyncXP.doPacket(var6);
                     var6.putShort(var3.getOnlineID());

                     try {
                        var3.getXp().save(var6.bb);
                     } catch (IOException var8) {
                        var8.printStackTrace();
                     }

                     PacketType.SyncXP.send(var5);
                  }
               }
            }
         }
      }
   }

    static void receiveChangePlayerStats(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    std::string var5 = GameWindow.ReadString(var0);
         var4.setPlayerStats(var0, var5);

         for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
            if (var7.getConnectedGUID() != var1.getConnectedGUID()) {
               if (var7.getConnectedGUID() == PlayerToAddressMap.get(var4)) {
                  var7.allChatMuted = var4.isAllChatMuted();
                  var7.accessLevel = PlayerType.fromString(var4.accessLevel);
               }

    ByteBufferWriter var8 = var7.startPacket();
               PacketType.ChangePlayerStats.doPacket(var8);
               var4.createPlayerStats(var8, var5);
               PacketType.ChangePlayerStats.send(var7);
            }
         }
      }
   }

    static void doMinimumInit() {
      Rand.init();
      DebugFileWatcher.instance.init();
    std::vector var0 = new std::vector<>(ServerMods);
      ZomboidFileSystem.instance.loadMods(var0);
      LuaManager.init();
      PerkFactory.init();
      CustomPerks.instance.init();
      CustomPerks.instance.initLua();
    AssetManagers var1 = GameWindow.assetManagers;
      AiSceneAssetManager.instance.create(AiSceneAsset.ASSET_TYPE, var1);
      AnimationAssetManager.instance.create(AnimationAsset.ASSET_TYPE, var1);
      AnimNodeAssetManager.instance.create(AnimationAsset.ASSET_TYPE, var1);
      ClothingItemAssetManager.instance.create(ClothingItem.ASSET_TYPE, var1);
      MeshAssetManager.instance.create(ModelMesh.ASSET_TYPE, var1);
      ModelAssetManager.instance.create(Model.ASSET_TYPE, var1);
      TextureIDAssetManager.instance.create(TextureID.ASSET_TYPE, var1);
      TextureAssetManager.instance.create(Texture.ASSET_TYPE, var1);
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
      } catch (Exception var3) {
         var3.printStackTrace();
      }

      RecipeManager.LoadedAfterLua();
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server" + File.separator + ServerName + "_SandboxVars.lua");
      if (var2.exists()) {
         if (!SandboxOptions.instance.loadServerLuaFile(ServerName)) {
            System.out.println("Exiting due to errors loading " + var2.getCanonicalPath());
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
    std::string var0 = ServerOptions.instance.Password.getValue();
      if (CoopSlave.instance != nullptr && SteamUtils.isSteamModeEnabled()) {
         var0 = "";
      }

      udpEngine = std::make_shared<UdpEngine>(DEFAULT_PORT, UDPPort, ServerOptions.getInstance().getMaxPlayers(), var0, true);
      DebugLog.log(DebugType.Network, "*** SERVER STARTED ****");
      DebugLog.log(DebugType.Network, "*** Steam is " + (SteamUtils.isSteamModeEnabled() ? "enabled" : "not enabled"));
      if (SteamUtils.isSteamModeEnabled()) {
         DebugLog.log(
            DebugType.Network, "Server is listening on port " + DEFAULT_PORT + " (for Steam connection) and port " + UDPPort + " (for UDPRakNet connection)"
         );
         DebugLog.log(DebugType.Network, "Clients should use " + DEFAULT_PORT + " port for connections");
      } else {
         DebugLog.log(DebugType.Network, "server is listening on port " + DEFAULT_PORT);
      }

      ResetID = ServerOptions.instance.ResetID.getValue();
      if (CoopSlave.instance != nullptr) {
         if (SteamUtils.isSteamModeEnabled()) {
    RakNetPeerInterface var1 = udpEngine.getPeer();
            CoopSlave.instance.sendMessage("server-address", nullptr, var1.GetServerIP() + ":" + DEFAULT_PORT);
    long var2 = SteamGameServer.GetSteamID();
            CoopSlave.instance.sendMessage("steam-id", nullptr, SteamUtils.convertSteamIDToString(var2));
         } else {
    std::string var5 = "127.0.0.1";
            CoopSlave.instance.sendMessage("server-address", nullptr, var5 + ":" + DEFAULT_PORT);
         }
      }

      LuaEventManager.triggerEvent("OnServerStarted");
      if (SteamUtils.isSteamModeEnabled()) {
         CoopSlave.status("UI_ServerStatus_Started");
      } else {
         CoopSlave.status("UI_ServerStatus_Started");
      }

    std::string var6 = ServerOptions.instance.DiscordChannel.getValue();
    std::string var7 = ServerOptions.instance.DiscordToken.getValue();
    bool var3 = ServerOptions.instance.DiscordEnable.getValue();
    std::string var4 = ServerOptions.instance.DiscordChannelID.getValue();
      discordBot.connect(var3, var7, var6, var4);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void mainLoopDealWithNetData(ZomboidNetData var0) {
      if (SystemDisabler.getDoMainLoopDealWithNetData()) {
    ByteBuffer var1 = var0.buffer;
    UdpConnection var2 = udpEngine.getActiveConnection(var0.connection);
         if (var0.type == nullptr) {
            ZomboidNetDataPool.instance.discard(var0);
         } else {
            var0.type.serverPacketCount++;
            MPStatistic.getInstance().addIncomePacket(var0.type, var1.limit());

            try {
               if (var2 == nullptr) {
                  DebugLog.log(DebugType.Network, "Received packet type=" + var0.type.name() + " connection is nullptr.");
                  return;
               }

               if (var2.username == nullptr) {
                  switch (1.$SwitchMap$zombie$network$PacketTypes$PacketType[var0.type.ordinal()]) {
                     case 1:
                     case 2:
                     case 3:
                        break;
                     default:
                        DebugLog.log("Received packet type=" + var0.type.name() + " before Login, disconnecting " + var2.getInetSocketAddress().getHostString());
                        var2.forceDisconnect("unacceptable-packet");
                        ZomboidNetDataPool.instance.discard(var0);
                        return;
                  }
               }

               var0.type.onServerPacket(var1, var2);
            } catch (Exception var4) {
               if (var2 == nullptr) {
                  DebugLog.log(DebugType.Network, "Error with packet of type: " + var0.type + " connection is nullptr.");
               } else {
                  DebugLog.General.error("Error with packet of type: " + var0.type + " for " + var2.username);
               }

               var4.printStackTrace();
            }

            ZomboidNetDataPool.instance.discard(var0);
         }
      }
   }

    static void receiveInvMngRemoveItem(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    short var4 = var0.getShort();
    IsoPlayer var5 = IDToPlayerMap.get(var4);
      if (var5 != nullptr) {
         for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
            if (var7.getConnectedGUID() != var1.getConnectedGUID() && var7.getConnectedGUID() == PlayerToAddressMap.get(var5)) {
    ByteBufferWriter var8 = var7.startPacket();
               PacketType.InvMngRemoveItem.doPacket(var8);
               var8.putInt(var3);
               PacketType.InvMngRemoveItem.send(var7);
               break;
            }
         }
      }
   }

    static void receiveInvMngGetItem(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
         for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
            if (var6.getConnectedGUID() != var1.getConnectedGUID() && var6.getConnectedGUID() == PlayerToAddressMap.get(var4)) {
    ByteBufferWriter var7 = var6.startPacket();
               PacketType.InvMngGetItem.doPacket(var7);
               var0.rewind();
               var7.bb.put(var0);
               PacketType.InvMngGetItem.send(var6);
               break;
            }
         }
      }
   }

    static void receiveInvMngReqItem(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = 0;
    std::string var4 = nullptr;
      if (var0.get() == 1) {
         var4 = GameWindow.ReadString(var0);
      } else {
         var3 = var0.getInt();
      }

    short var5 = var0.getShort();
    short var6 = var0.getShort();
    IsoPlayer var7 = IDToPlayerMap.get(var6);
      if (var7 != nullptr) {
         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID() && var9.getConnectedGUID() == PlayerToAddressMap.get(var7)) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.InvMngReqItem.doPacket(var10);
               if (var4 != nullptr) {
                  var10.putByte((byte)1);
                  var10.putUTF(var4);
               } else {
                  var10.putByte((byte)0);
                  var10.putInt(var3);
               }

               var10.putShort(var5);
               PacketType.InvMngReqItem.send(var9);
               break;
            }
         }
      }
   }

    static void receiveRequestZipList(ByteBuffer var0, UdpConnection var1, short var2) {
      if (!var1.wasInLoadingQueue) {
         kick(var1, "UI_Policy_Kick", "The server received an invalid request");
      }

      if (var1.playerDownloadServer != nullptr) {
         var1.playerDownloadServer.receiveRequestArray(var0);
      }
   }

    static void receiveRequestLargeAreaZip(ByteBuffer var0, UdpConnection var1, short var2) {
      if (!var1.wasInLoadingQueue) {
         kick(var1, "UI_Policy_Kick", "The server received an invalid request");
      }

      if (var1.playerDownloadServer != nullptr) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
         var1.connectArea[0] = std::make_shared<Vector3>(var3, var4, var5);
         var1.ChunkGridWidth = var5;
         ZombiePopulationManager.instance.updateLoadedAreas();
      }
   }

    static void receiveNotRequiredInZip(ByteBuffer var0, UdpConnection var1, short var2) {
      if (var1.playerDownloadServer != nullptr) {
         var1.playerDownloadServer.receiveCancelRequest(var0);
      }
   }

    static void receiveLogin(ByteBuffer var0, UdpConnection var1, short var2) {
      ConnectionManager.log("receive-packet", "login", var1);
    std::string var3 = GameWindow.ReadString(var0).trim();
    std::string var4 = GameWindow.ReadString(var0).trim();
    std::string var5 = GameWindow.ReadString(var0).trim();
      if (!var5 == Core.getInstance().getVersion())) {
    ByteBufferWriter var6 = var1.startPacket();
         PacketType.AccessDenied.doPacket(var6);
         LoggerManager.getLogger("user")
            .write("access denied: user \"" + var3 + "\" client version (" + var5 + ") does not match server version (" + Core.getInstance().getVersion() + ")");
         var6.putUTF("ClientVersionMismatch##" + var5 + "##" + Core.getInstance().getVersion());
         PacketType.AccessDenied.send(var1);
         ConnectionManager.log("access-denied", "version-mismatch", var1);
         var1.forceDisconnect("access-denied-client-version");
      }

      var1.wasInLoadingQueue = false;
      var1.ip = var1.getInetSocketAddress().getHostString();
      var1.validator.reset();
      var1.idStr = var1.ip;
      if (SteamUtils.isSteamModeEnabled()) {
         var1.steamID = udpEngine.getClientSteamID(var1.getConnectedGUID());
         if (var1.steamID == -1L) {
    ByteBufferWriter var13 = var1.startPacket();
            PacketType.AccessDenied.doPacket(var13);
            LoggerManager.getLogger("user")
               .write("access denied: The client \"" + var3 + "\" did not complete the connection and authorization procedure in zombienet");
            var13.putUTF("ClientIsNofFullyConnectedInZombienet");
            PacketType.AccessDenied.send(var1);
            ConnectionManager.log("access-denied", "znet-error", var1);
            var1.forceDisconnect("access-denied-zombienet-connect");
         }

         var1.ownerID = udpEngine.getClientOwnerSteamID(var1.getConnectedGUID());
         var1.idStr = SteamUtils.convertSteamIDToString(var1.steamID);
         if (var1.steamID != var1.ownerID) {
            var1.idStr = var1.idStr + "(owner=" + SteamUtils.convertSteamIDToString(var1.ownerID) + ")";
         }
      }

      var1.password = var4;
      LoggerManager.getLogger("user").write(var1.idStr + " \"" + var3 + "\" attempting to join");
      if (CoopSlave.instance != nullptr && SteamUtils.isSteamModeEnabled()) {
         for (int var15 = 0; var15 < udpEngine.connections.size(); var15++) {
    UdpConnection var24 = (UdpConnection)udpEngine.connections.get(var15);
            if (var24 != var1 && var24.steamID == var1.steamID) {
               LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" already connected");
    ByteBufferWriter var26 = var1.startPacket();
               PacketType.AccessDenied.doPacket(var26);
               var26.putUTF("AlreadyConnected");
               PacketType.AccessDenied.send(var1);
               ConnectionManager.log("access-denied", "already-connected-steamid", var1);
               var1.forceDisconnect("access-denied-already-connected-cs");
               return;
            }
         }

         var1.username = var3;
         var1.usernames[0] = var3;
         var1.isCoopHost = udpEngine.connections.size() == 1;
         DebugLog.Multiplayer.debugln(var1.idStr + " isCoopHost=" + var1.isCoopHost);
         var1.accessLevel = 1;
         if (!ServerOptions.instance.DoLuaChecksum.getValue()) {
            var1.checksumState = ChecksumState.Done;
         }

         if (getPlayerCount() >= ServerOptions.getInstance().getMaxPlayers()) {
    ByteBufferWriter var18 = var1.startPacket();
            PacketType.AccessDenied.doPacket(var18);
            var18.putUTF("ServerFull");
            PacketType.AccessDenied.send(var1);
            ConnectionManager.log("access-denied", "server-full", var1);
            var1.forceDisconnect("access-denied-server-full-cs");
         } else {
            if (isServerDropPackets() && ServerOptions.instance.DenyLoginOnOverloadedServer.getValue()) {
    ByteBufferWriter var16 = var1.startPacket();
               PacketType.AccessDenied.doPacket(var16);
               LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" Server is too busy");
               var16.putUTF("Server is too busy.");
               PacketType.AccessDenied.send(var1);
               ConnectionManager.log("access-denied", "server-busy", var1);
               var1.forceDisconnect("access-denied-server-busy-cs");
               countOfDroppedConnections++;
            }

            LoggerManager.getLogger("user").write(var1.idStr + " \"" + var3 + "\" allowed to join");
    ServerWorldDatabase var10002 = ServerWorldDatabase.instance;
            Objects.requireNonNull(ServerWorldDatabase.instance);
    LogonResult var17 = std::make_shared<LogonResult>(var10002);
            var17.accessLevel = PlayerType.toString(var1.accessLevel);
            receiveClientConnect(var1, var17);
         }
      } else {
    LogonResult var14 = ServerWorldDatabase.instance.authClient(var3, var4, var1.ip, var1.steamID);
         if (var14.bAuthorized) {
            for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);

               for (int var9 = 0; var9 < 4; var9++) {
                  if (var3 == var8.usernames[var9])) {
                     LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" already connected");
    ByteBufferWriter var10 = var1.startPacket();
                     PacketType.AccessDenied.doPacket(var10);
                     var10.putUTF("AlreadyConnected");
                     PacketType.AccessDenied.send(var1);
                     ConnectionManager.log("access-denied", "already-connected-username", var1);
                     var1.forceDisconnect("access-denied-already-connected-username");
                     return;
                  }
               }
            }

            var1.username = var3;
            var1.usernames[0] = var3;
            transactionIDMap.put(var3, var14.transactionID);
            if (CoopSlave.instance != nullptr) {
               var1.isCoopHost = udpEngine.connections.size() == 1;
               DebugLog.log(var1.idStr + " isCoopHost=" + var1.isCoopHost);
            }

            var1.accessLevel = PlayerType.fromString(var14.accessLevel);
            var1.preferredInQueue = var14.priority;
            if (!ServerOptions.instance.DoLuaChecksum.getValue() || var14.accessLevel == "admin")) {
               var1.checksumState = ChecksumState.Done;
            }

            if (!var14.accessLevel == "") && getPlayerCount() >= ServerOptions.getInstance().getMaxPlayers()) {
    ByteBufferWriter var22 = var1.startPacket();
               PacketType.AccessDenied.doPacket(var22);
               var22.putUTF("ServerFull");
               PacketType.AccessDenied.send(var1);
               ConnectionManager.log("access-denied", "server-full-no-admin", var1);
               var1.forceDisconnect("access-denied-server-full");
               return;
            }

            if (!ServerWorldDatabase.instance.containsUser(var3) && ServerWorldDatabase.instance.containsCaseinsensitiveUser(var3)) {
    ByteBufferWriter var21 = var1.startPacket();
               PacketType.AccessDenied.doPacket(var21);
               var21.putUTF("InvalidUsername");
               PacketType.AccessDenied.send(var1);
               ConnectionManager.log("access-denied", "invalid-username", var1);
               var1.forceDisconnect("access-denied-invalid-username");
               return;
            }

    int var19 = var1.getAveragePing();
            DebugLog.Multiplayer.debugln("User %s ping %d ms", var1.username, var19);
            if (MPStatistics.doKickWhileLoading(var1, var19)) {
    ByteBufferWriter var25 = var1.startPacket();
               PacketType.AccessDenied.doPacket(var25);
               LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" ping is too high");
               var25.putUTF("Ping");
               PacketType.AccessDenied.send(var1);
               ConnectionManager.log("access-denied", "ping-limit", var1);
               var1.forceDisconnect("access-denied-ping-limit");
               return;
            }

            if (var14.newUser) {
               try {
                  ServerWorldDatabase.instance.addUser(var3, var4);
                  LoggerManager.getLogger("user").write(var1.idStr + " \"" + var3 + "\" was added");
               } catch (SQLException var11) {
                  DebugLog.Multiplayer.printException(var11, "ServerWorldDatabase.addUser error", LogSeverity.Error);
               }
            }

            LoggerManager.getLogger("user").write(var1.idStr + " \"" + var3 + "\" allowed to join");

            try {
               if (ServerOptions.instance.AutoCreateUserInWhiteList.getValue() && !ServerWorldDatabase.instance.containsUser(var3)) {
                  ServerWorldDatabase.instance.addUser(var3, var4);
               } else {
                  ServerWorldDatabase.instance.setPassword(var3, var4);
               }
            } catch (Exception var12) {
               var12.printStackTrace();
            }

            ServerWorldDatabase.instance.updateLastConnectionDate(var3, var4);
            if (SteamUtils.isSteamModeEnabled()) {
    std::string var20 = SteamUtils.convertSteamIDToString(var1.steamID);
               ServerWorldDatabase.instance.setUserSteamID(var3, var20);
            }

            receiveClientConnect(var1, var14);
         } else {
    ByteBufferWriter var23 = var1.startPacket();
            PacketType.AccessDenied.doPacket(var23);
            if (var14.banned) {
               LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" is banned");
               if (var14.bannedReason != nullptr && !var14.bannedReason.empty()) {
                  var23.putUTF("BannedReason##" + var14.bannedReason);
               } else {
                  var23.putUTF("Banned");
               }
            } else if (!var14.bAuthorized) {
               LoggerManager.getLogger("user").write("access denied: user \"" + var3 + "\" reason \"" + var14.dcReason + "\"");
               var23.putUTF(var14.dcReason != nullptr ? var14.dcReason : "AccessDenied");
            }

            PacketType.AccessDenied.send(var1);
            ConnectionManager.log("access-denied", "unauthorized", var1);
            var1.forceDisconnect("access-denied-unauthorized");
         }
      }
   }

    static void receiveSendInventory(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    long var4 = IDToAddressMap.get(var3);
      if (var4 != nullptr) {
         for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
            if (var6.getConnectedGUID() == var4) {
    ByteBufferWriter var7 = var6.startPacket();
               PacketType.SendInventory.doPacket(var7);
               var7.bb.put(var0);
               PacketType.SendInventory.send(var6);
               break;
            }
         }
      }
   }

    static void receivePlayerStartPMChat(ByteBuffer var0, UdpConnection var1, short var2) {
      ChatServer.getInstance().processPlayerStartWhisperChatPacket(var0);
   }

    static void receiveRequestInventory(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    long var5 = IDToAddressMap.get(var4);
      if (var5 != nullptr) {
         for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
            if (var7.getConnectedGUID() == var5) {
    ByteBufferWriter var8 = var7.startPacket();
               PacketType.RequestInventory.doPacket(var8);
               var8.putShort(var3);
               PacketType.RequestInventory.send(var7);
               break;
            }
         }
      }
   }

    static void receiveStatistic(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
         var1.statistic.parse(var0);
      } catch (Exception var4) {
         var4.printStackTrace();
      }
   }

    static void receiveStatisticRequest(ByteBuffer var0, UdpConnection var1, short var2) {
      if (var1.accessLevel != 32 && !Core.bDebug) {
         DebugLog.General.error("User " + var1.username + " has no rights to access statistics.");
      } else {
         try {
            var1.statistic.enable = var0.get();
            sendStatistic(var1);
         } catch (Exception var4) {
            var4.printStackTrace();
         }
      }
   }

    static void receiveZombieSimulation(ByteBuffer var0, UdpConnection var1, short var2) {
      NetworkZombiePacker.getInstance().receivePacket(var0, var1);
   }

    static void sendShortStatistic() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         if (var1.statistic.enable == 3) {
            sendShortStatistic(var1);
         }
      }
   }

    static void sendShortStatistic(UdpConnection var0) {
      try {
    ByteBufferWriter var1 = var0.startPacket();
         PacketType.StatisticRequest.doPacket(var1);
         MPStatistic.getInstance().write(var1);
         PacketType.StatisticRequest.send(var0);
      } catch (Exception var2) {
         var2.printStackTrace();
         var0.cancelPacket();
      }
   }

    static void sendStatistic() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         if (var1.statistic.enable == 1) {
            sendStatistic(var1);
         }
      }
   }

    static void sendStatistic(UdpConnection var0) {
    ByteBufferWriter var1 = var0.startPacket();
      PacketType.StatisticRequest.doPacket(var1);

      try {
         MPStatistic.getInstance().getStatisticTable(var1.bb);
         PacketType.StatisticRequest.send(var0);
      } catch (IOException var3) {
         var3.printStackTrace();
         var0.cancelPacket();
      }
   }

    static void getStatisticFromClients() {
      try {
         for (UdpConnection var1 : udpEngine.connections) {
    ByteBufferWriter var2 = var1.startPacket();
            PacketType.Statistic.doPacket(var2);
            var2.putLong(System.currentTimeMillis());
            PacketType.Statistic.send(var1);
         }
      } catch (Exception var3) {
         var3.printStackTrace();
      }
   }

    static void updateZombieControl(IsoZombie var0, short var1, int var2) {
      try {
         if (var0.authOwner == nullptr) {
            return;
         }

    ByteBufferWriter var3 = var0.authOwner.startPacket();
         PacketType.ZombieControl.doPacket(var3);
         var3.putShort(var0.OnlineID);
         var3.putShort(var1);
         var3.putInt(var2);
         PacketType.ZombieControl.send(var0.authOwner);
      } catch (Exception var4) {
         var4.printStackTrace();
      }
   }

    static void receivePlayerUpdate(ByteBuffer var0, UdpConnection var1, short var2) {
      if (var1.checksumState != ChecksumState.Done) {
         kick(var1, "UI_Policy_Kick", nullptr);
         var1.forceDisconnect("kick-checksum");
      } else {
    PlayerPacket var3 = l_receive.playerPacket;
         var3.parse(var0, var1);
    IsoPlayer var4 = getPlayerFromConnection(var1, var3.id);

         try {
            if (var4 == nullptr) {
               DebugLog.General.error("receivePlayerUpdate: Server received position for unknown player (id:" + var3.id + "). Server will ignore this data.");
            } else {
               if (var1.accessLevel == 1
                  && var4.networkAI.doCheckAccessLevel()
                  && (
                        var3.booleanVariables
                           & (!SystemDisabler.getAllowDebugConnections() && !SystemDisabler.getOverrideServerConnectDebugCheck() ? '\uf000' : '쀀')
                     )
                     != 0
                  && ServerOptions.instance.AntiCheatProtectionType12.getValue()
                  && PacketValidator.checkUser(var1)) {
                  PacketValidator.doKickUser(var1, var3.getClass().getSimpleName(), "Type12", nullptr);
               }

               if (!var4.networkAI.checkPosition(var1, var4, PZMath.fastfloor(var3.realx), PZMath.fastfloor(var3.realy))) {
                  return;
               }

               if (!var4.networkAI.isSetVehicleHit()) {
                  var4.networkAI.parse(var3);
               }

               var4.bleedingLevel = var3.bleedingLevel;
               if (var4.networkAI.distance.getLength() > IsoChunkMap.ChunkWidthInTiles) {
                  MPStatistic.getInstance().teleport();
               }

               var1.ReleventPos[var4.PlayerIndex].x = var3.realx;
               var1.ReleventPos[var4.PlayerIndex].y = var3.realy;
               var1.ReleventPos[var4.PlayerIndex].z = var3.realz;
               var3.id = var4.getOnlineID();
            }
         } catch (Exception var8) {
            var8.printStackTrace();
         }

         if (ServerOptions.instance.KickFastPlayers.getValue()) {
    Vector2 var5 = playerToCoordsMap.get(int.valueOf(var3.id));
            if (var5 == nullptr) {
               var5 = std::make_unique<Vector2>();
               var5.x = var3.x;
               var5.y = var3.y;
               playerToCoordsMap.put(var3.id, var5);
            } else {
               if (!var4.accessLevel == "") && !var4.isGhostMode() && (Math.abs(var3.x - var5.x) > 4.0F || Math.abs(var3.y - var5.y) > 4.0F)) {
                  if (playerMovedToFastMap.get(var3.id) == nullptr) {
                     playerMovedToFastMap.put(var3.id, 1);
                  } else {
                     playerMovedToFastMap.put(var3.id, playerMovedToFastMap.get(int.valueOf(var3.id)) + 1);
                  }

                  LoggerManager.getLogger("admin")
                     .write(var4.getDisplayName() + " go too fast (" + playerMovedToFastMap.get(int.valueOf(var3.id)) + " times)");
                  if (playerMovedToFastMap.get(var3.id) == 10) {
                     LoggerManager.getLogger("admin").write(var4.getDisplayName() + " kicked for going too fast");
                     kick(var1, "UI_Policy_Kick", nullptr);
                     var1.forceDisconnect("kick-fast-player");
                     return;
                  }
               }

               var5.x = var3.x;
               var5.y = var3.y;
            }
         }

         if (var4 != nullptr) {
            for (int var10 = 0; var10 < udpEngine.connections.size(); var10++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var10);
               if (var1.getConnectedGUID() != var6.getConnectedGUID()
                  && var6.isFullyConnected()
                  && (
                     var4.checkCanSeeClient(var6) && var6.RelevantTo(var3.x, var3.y)
                        || var2 == PacketType.PlayerUpdateReliable.getId() && (var6.accessLevel > var1.accessLevel || var1.accessLevel == 32)
                  )) {
    ByteBufferWriter var7 = var6.startPacket();
                  ((PacketType)PacketTypes.packetTypes.get(var2)).doPacket(var7);
                  var0.position(0);
                  var0.position(2);
                  var7.bb.putShort(var4.getOnlineID());
                  var7.bb.put(var0);
                  ((PacketType)PacketTypes.packetTypes.get(var2)).send(var6);
               }
            }
         }
      }
   }

    static void receivePacketCounts(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.PacketCounts.doPacket(var3);
      var3.putInt(PacketTypes.packetTypes.size());

      for (PacketType var5 : PacketTypes.packetTypes.values()) {
         var3.putShort(var5.getId());
         var3.putLong(var5.serverPacketCount);
      }

      PacketType.PacketCounts.send(var1);
   }

    static void receiveSandboxOptions(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
         SandboxOptions.instance.load(var0);
         SandboxOptions.instance.applySettings();
         SandboxOptions.instance.toLua();
         SandboxOptions.instance.saveServerLuaFile(ServerName);

         for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
    ByteBufferWriter var5 = var4.startPacket();
            PacketType.SandboxOptions.doPacket(var5);
            var0.rewind();
            var5.bb.put(var0);
            PacketType.SandboxOptions.send(var4);
         }
      } catch (Exception var6) {
         var6.printStackTrace();
      }
   }

    static void receiveChunkObjectState(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    IsoChunk var5 = ServerMap.instance.getChunk(var3, var4);
      if (var5 == nullptr) {
         var1.chunkObjectState.push_back(var3);
         var1.chunkObjectState.push_back(var4);
      } else {
    ByteBufferWriter var6 = var1.startPacket();
         PacketType.ChunkObjectState.doPacket(var6);
         var6.putShort(var3);
         var6.putShort(var4);

         try {
            if (var5.saveObjectState(var6.bb)) {
               PacketType.ChunkObjectState.send(var1);
            } else {
               var1.cancelPacket();
            }
         } catch (Throwable var8) {
            var8.printStackTrace();
            var1.cancelPacket();
            return;
         }
      }
   }

    static void receiveReadAnnotedMap(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
      StashSystem.prepareBuildingStash(var3);
   }

    static void receiveTradingUIRemoveItem(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    int var5 = var0.getInt();
    long var6 = IDToAddressMap.get(var4);
      if (var6 != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() == var6) {
    ByteBufferWriter var9 = var8.startPacket();
               PacketType.TradingUIRemoveItem.doPacket(var9);
               var9.putShort(var3);
               var9.putInt(var5);
               PacketType.TradingUIRemoveItem.send(var8);
               break;
            }
         }
      }
   }

    static void receiveTradingUIUpdateState(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    int var5 = var0.getInt();
    long var6 = IDToAddressMap.get(var4);
      if (var6 != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() == var6) {
    ByteBufferWriter var9 = var8.startPacket();
               PacketType.TradingUIUpdateState.doPacket(var9);
               var9.putShort(var3);
               var9.putInt(var5);
               PacketType.TradingUIUpdateState.send(var8);
               break;
            }
         }
      }
   }

    static void receiveTradingUIAddItem(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    InventoryItem var5 = nullptr;

      try {
         var5 = InventoryItem.loadItem(var0, 195);
      } catch (Exception var12) {
         var12.printStackTrace();
      }

      if (var5 != nullptr) {
    long var6 = IDToAddressMap.get(var4);
         if (var6 != nullptr) {
            for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
               if (var8.getConnectedGUID() == var6) {
    ByteBufferWriter var9 = var8.startPacket();
                  PacketType.TradingUIAddItem.doPacket(var9);
                  var9.putShort(var3);

                  try {
                     var5.saveWithSize(var9.bb, false);
                  } catch (IOException var11) {
                     var11.printStackTrace();
                  }

                  PacketType.TradingUIAddItem.send(var8);
                  break;
               }
            }
         }
      }
   }

    static void receiveRequestTrading(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    uint8_t var5 = var0.get();
    long var6 = IDToAddressMap.get(var3);
      if (var5 == 0) {
         var6 = IDToAddressMap.get(var4);
      }

      if (var6 != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() == var6) {
    ByteBufferWriter var9 = var8.startPacket();
               PacketType.RequestTrading.doPacket(var9);
               if (var5 == 0) {
                  var9.putShort(var3);
               } else {
                  var9.putShort(var4);
               }

               var9.putByte(var5);
               PacketType.RequestTrading.send(var8);
               break;
            }
         }
      }
   }

    static void receiveSyncFaction(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
    Faction var6 = Faction.getFaction(var3);
    bool var7 = false;
      if (var6 == nullptr) {
         var6 = std::make_shared<Faction>(var3, var4);
         var7 = true;
         Faction.getFactions().push_back(var6);
      }

      var6.getPlayers().clear();
      if (var0.get() == 1) {
         var6.setTag(GameWindow.ReadString(var0));
         var6.setTagColor(std::make_shared<ColorInfo>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
      }

      for (int var8 = 0; var8 < var5; var8++) {
    std::string var9 = GameWindow.ReadString(var0);
         var6.getPlayers().push_back(var9);
      }

      if (!var6.getOwner() == var4)) {
         var6.setOwner(var4);
      }

    bool var12 = var0.get() == 1;
      if (ChatServer.isInited()) {
         if (var7) {
            ChatServer.getInstance().createFactionChat(var3);
         }

         if (var12) {
            ChatServer.getInstance().removeFactionChat(var3);
         } else {
            ChatServer.getInstance().syncFactionChatMembers(var3, var4, var6.getPlayers());
         }
      }

      if (var12) {
         Faction.getFactions().remove(var6);
         DebugLog.log("faction: removed " + var3 + " owner=" + var6.getOwner());
      }

      for (int var13 = 0; var13 < udpEngine.connections.size(); var13++) {
    UdpConnection var10 = (UdpConnection)udpEngine.connections.get(var13);
         if (var1 == nullptr || var10.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var11 = var10.startPacket();
            PacketType.SyncFaction.doPacket(var11);
            var6.writeToBuffer(var11, var12);
            PacketType.SyncFaction.send(var10);
         }
      }
   }

    static void receiveSyncNonPvpZone(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    SyncNonPvpZonePacket var3 = std::make_shared<SyncNonPvpZonePacket>();
         var3.parse(var0, var1);
         if (var3.isConsistent()) {
            sendNonPvpZone(var3.zone, var3.doRemove, var1);
            var3.process();
            DebugLog.Multiplayer.debugln("ReceiveSyncNonPvpZone: %s", var3.getDescription());
         }
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "ReceiveSyncNonPvpZone: failed", LogSeverity.Error);
      }
   }

    static void sendNonPvpZone(NonPvpZone var0, bool var1, UdpConnection var2) {
      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         if (var2 == nullptr || var4.getConnectedGUID() != var2.getConnectedGUID()) {
    ByteBufferWriter var5 = var4.startPacket();
            PacketType.SyncNonPvpZone.doPacket(var5);
            var0.save(var5.bb);
            var5.putBoolean(var1);
            PacketType.SyncNonPvpZone.send(var4);
         }
      }
   }

    static void receiveChangeTextColor(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = getPlayerFromConnection(var1, var3);
      if (var4 != nullptr) {
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
         var4.setSpeakColourInfo(std::make_shared<ColorInfo>(var5, var6, var7, 1.0F));

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.ChangeTextColor.doPacket(var10);
               var10.putShort(var4.getOnlineID());
               var10.putFloat(var5);
               var10.putFloat(var6);
               var10.putFloat(var7);
               PacketType.ChangeTextColor.send(var9);
            }
         }
      }
   }

    static void receiveTransactionID(ByteBuffer var0, UdpConnection var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
      if (var4 != nullptr) {
         transactionIDMap.put(var4.username, var3);
         var4.setTransactionID(var3);
         ServerWorldDatabase.instance.saveTransactionID(var4.username, var3);
      }
   }

    static void receiveSyncCompost(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var6 != nullptr) {
    IsoCompost var7 = var6.getCompost();
         if (var7 == nullptr) {
            var7 = std::make_shared<IsoCompost>(var6.getCell(), var6);
            var6.AddSpecialObject(var7);
         }

    float var8 = var0.getFloat();
         var7.setCompost(var8);
         sendCompost(var7, var1);
      }
   }

    static void sendCompost(IsoCompost var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var3.RelevantTo(var0.square.x, var0.square.y) && (var1 != nullptr && var3.getConnectedGUID() != var1.getConnectedGUID() || var1 == nullptr)) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.SyncCompost.doPacket(var4);
            var4.putInt(var0.square.x);
            var4.putInt(var0.square.y);
            var4.putInt(var0.square.z);
            var4.putFloat(var0.getCompost());
            PacketType.SyncCompost.send(var3);
         }
      }
   }

    static void receiveCataplasm(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    int var5 = var0.getInt();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    float var8 = var0.getFloat();
         if (var6 > 0.0F) {
            var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5)).setPlantainFactor(var6);
         }

         if (var7 > 0.0F) {
            var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5)).setComfreyFactor(var7);
         }

         if (var8 > 0.0F) {
            var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5)).setGarlicFactor(var8);
         }

         for (int var9 = 0; var9 < udpEngine.connections.size(); var9++) {
    UdpConnection var10 = (UdpConnection)udpEngine.connections.get(var9);
            if (var10.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var11 = var10.startPacket();
               PacketType.Cataplasm.doPacket(var11);
               var11.putShort(var3);
               var11.putInt(var5);
               var11.putFloat(var6);
               var11.putFloat(var7);
               var11.putFloat(var8);
               PacketType.Cataplasm.send(var10);
            }
         }
      }
   }

    static void receiveSledgehammerDestroy(ByteBuffer var0, UdpConnection var1, short var2) {
      if (ServerOptions.instance.AllowDestructionBySledgehammer.getValue()) {
         receiveRemoveItemFromSquare(var0, var1, var2);
      }
   }

    static void AddExplosiveTrap(HandWeapon var0, IsoGridSquare var1, bool var2) {
    IsoTrap var3 = std::make_shared<IsoTrap>(var0, var1.getCell(), var1);
    int var4 = 0;
      if (var0.getExplosionRange() > 0) {
         var4 = var0.getExplosionRange();
      }

      if (var0.getFireRange() > 0) {
         var4 = var0.getFireRange();
      }

      if (var0.getSmokeRange() > 0) {
         var4 = var0.getSmokeRange();
      }

      var1.AddTileObject(var3);

      for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
    ByteBufferWriter var7 = var6.startPacket();
         PacketType.AddExplosiveTrap.doPacket(var7);
         var7.putInt(var1.x);
         var7.putInt(var1.y);
         var7.putInt(var1.z);

         try {
            var0.saveWithSize(var7.bb, false);
         } catch (IOException var9) {
            var9.printStackTrace();
         }

         var7.putInt(var4);
         var7.putBoolean(var2);
         var7.putBoolean(false);
         PacketType.AddExplosiveTrap.send(var6);
      }
   }

    static void receiveAddExplosiveTrap(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var6 != nullptr) {
    InventoryItem var7 = nullptr;

         try {
            var7 = InventoryItem.loadItem(var0, 195);
         } catch (Exception var14) {
            var14.printStackTrace();
         }

         if (var7 == nullptr) {
            return;
         }

    HandWeapon var8 = (HandWeapon)var7;
         DebugLog.log("trap: user \"" + var1.username + "\" added " + var7.getFullType() + " at " + var3 + "," + var4 + "," + var5);
         LoggerManager.getLogger("map").write(var1.idStr + " \"" + var1.username + "\" added " + var7.getFullType() + " at " + var3 + "," + var4 + "," + var5);
         if (var8.isInstantExplosion()) {
    IsoTrap var9 = std::make_shared<IsoTrap>(var8, var6.getCell(), var6);
            var6.AddTileObject(var9);
            var9.triggerExplosion(false);
         }

         for (int var15 = 0; var15 < udpEngine.connections.size(); var15++) {
    UdpConnection var10 = (UdpConnection)udpEngine.connections.get(var15);
            if (var10.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var11 = var10.startPacket();
               PacketType.AddExplosiveTrap.doPacket(var11);
               var11.putInt(var3);
               var11.putInt(var4);
               var11.putInt(var5);

               try {
                  var8.saveWithSize(var11.bb, false);
               } catch (IOException var13) {
                  var13.printStackTrace();
               }

               PacketType.AddExplosiveTrap.send(var10);
            }
         }
      }
   }

    static void sendHelicopter(float var0, float var1, bool var2) {
      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
    ByteBufferWriter var5 = var4.startPacket();
         PacketType.Helicopter.doPacket(var5);
         var5.putFloat(var0);
         var5.putFloat(var1);
         var5.putBoolean(var2);
         PacketType.Helicopter.send(var4);
      }
   }

    static void receiveRegisterZone(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    int var9 = var0.getInt();
    int var10 = var0.getInt();
    bool var11 = var0.get() == 1;
    std::vector var12 = IsoWorld.instance.getMetaGrid().getZonesAt(var5, var6, var7);
    bool var13 = false;

    for (auto& var15 : var12)         if (var4 == var15.getType())) {
            var13 = true;
            var15.setName(var3);
            var15.setLastActionTimestamp(var10);
         }
      }

      if (!var13) {
         IsoWorld.instance.getMetaGrid().registerZone(var3, var4, var5, var6, var7, var8, var9);
      }

      if (var11) {
         for (int var17 = 0; var17 < udpEngine.connections.size(); var17++) {
    UdpConnection var18 = (UdpConnection)udpEngine.connections.get(var17);
            if (var18.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var16 = var18.startPacket();
               PacketType.RegisterZone.doPacket(var16);
               var16.putUTF(var3);
               var16.putUTF(var4);
               var16.putInt(var5);
               var16.putInt(var6);
               var16.putInt(var7);
               var16.putInt(var8);
               var16.putInt(var9);
               var16.putInt(var10);
               PacketType.RegisterZone.send(var18);
            }
         }
      }
   }

    static void sendZone(Zone var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var1 == nullptr || var3.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.RegisterZone.doPacket(var4);
            var4.putUTF(var0.name);
            var4.putUTF(var0.type);
            var4.putInt(var0.x);
            var4.putInt(var0.y);
            var4.putInt(var0.z);
            var4.putInt(var0.w);
            var4.putInt(var0.h);
            var4.putInt(var0.lastActionTimestamp);
            PacketType.RegisterZone.send(var3);
         }
      }
   }

    static void receiveConstructedZone(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    Zone var6 = IsoWorld.instance.MetaGrid.getZoneAt(var3, var4, var5);
      if (var6 != nullptr) {
         var6.setHaveConstruction(true);
      }
   }

    static void addXp(IsoPlayer var0, Perk var1, int var2) {
      if (PlayerToAddressMap.containsKey(var0)) {
    long var3 = PlayerToAddressMap.get(var0);
    UdpConnection var5 = udpEngine.getActiveConnection(var3);
         if (var5 == nullptr) {
            return;
         }

    AddXp var6 = std::make_shared<AddXp>();
         var6.set(var0, var1, var2);
    ByteBufferWriter var7 = var5.startPacket();
         PacketType.AddXP.doPacket(var7);
         var6.write(var7);
         PacketType.AddXP.send(var5);
      }
   }

    static void receiveWriteLog(ByteBuffer var0, UdpConnection var1, short var2) {
   }

    static void receiveChecksum(ByteBuffer var0, UdpConnection var1, short var2) {
      NetChecksum.comparer.serverPacket(var0, var1);
   }

    static void answerPing(ByteBuffer var0, UdpConnection var1) {
    std::string var2 = GameWindow.ReadString(var0);

      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         if (var4.getConnectedGUID() == var1.getConnectedGUID()) {
    ByteBufferWriter var5 = var4.startPacket();
            PacketType.Ping.doPacket(var5);
            var5.putUTF(var2);
            var5.putInt(udpEngine.connections.size());
            var5.putInt(512);
            PacketType.Ping.send(var4);
         }
      }
   }

    static void receiveUpdateItemSprite(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    std::string var4 = GameWindow.ReadStringUTF(var0);
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, var7);
      if (var9 != nullptr && var8 < var9.getObjects().size()) {
         try {
    IsoObject var10 = (IsoObject)var9.getObjects().get(var8);
            if (var10 != nullptr) {
               var10.sprite = IsoSpriteManager.instance.getSprite(var3);
               if (var10.sprite == nullptr && !var4.empty()) {
                  var10.setSprite(var4);
               }

               var10.RemoveAttachedAnims();
    int var11 = var0.get() & 255;

               for (int var12 = 0; var12 < var11; var12++) {
    int var13 = var0.getInt();
    IsoSprite var14 = IsoSpriteManager.instance.getSprite(var13);
                  if (var14 != nullptr) {
                     var10.AttachExistingAnim(var14, 0, 0, false, 0, false, 0.0F);
                  }
               }

               var10.transmitUpdatedSpriteToClients(var1);
            }
         } catch (Exception var15) {
         }
      }
   }

    static void receiveWorldMessage(ByteBuffer var0, UdpConnection var1, short var2) {
      if (!var1.allChatMuted) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
         if (var4.length() > 256) {
            var4 = var4.substr(0, 256);
         }

         for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
    ByteBufferWriter var7 = var6.startPacket();
            PacketType.WorldMessage.doPacket(var7);
            var7.putUTF(var3);
            var7.putUTF(var4);
            PacketType.WorldMessage.send(var6);
         }

         discordBot.sendMessage(var3, var4);
         LoggerManager.getLogger("chat").write(var1.index + " \"" + var1.username + "\" A \"" + var4 + "\"");
      }
   }

    static void receiveGetModData(ByteBuffer var0, UdpConnection var1, short var2) {
      LuaEventManager.triggerEvent("SendCustomModData");
   }

    static void receiveStopFire(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
      if (var3 == 1) {
    short var12 = var0.getShort();
    IsoPlayer var14 = IDToPlayerMap.get(var12);
         if (var14 != nullptr) {
            var14.sendObjectChange("StopBurning");
         }
      } else if (var3 == 2) {
    short var11 = var0.getShort();
    IsoZombie var13 = (IsoZombie)ServerMap.instance.ZombieMap.get(var11);
         if (var13 != nullptr) {
            var13.StopBurning();
         }
      } else {
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoGridSquare var7 = ServerMap.instance.getGridSquare(var4, var5, var6);
         if (var7 != nullptr) {
            var7.stopFire();

            for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
               if (var9.RelevantTo(var4, var5) && var9.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var10 = var9.startPacket();
                  PacketType.StopFire.doPacket(var10);
                  var10.putInt(var4);
                  var10.putInt(var5);
                  var10.putInt(var6);
                  PacketType.StopFire.send(var9);
               }
            }
         }
      }
   }

    static void receiveStartFire(ByteBuffer var0, UdpConnection var1, short var2) {
    StartFire var3 = std::make_shared<StartFire>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         var3.process();

         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.StartFire.doPacket(var6);
               var3.write(var6);
               PacketType.StartFire.send(var5);
            }
         }
      }
   }

    static void startFireOnClient(IsoGridSquare var0, int var1, bool var2, int var3, bool var4) {
    StartFire var5 = std::make_shared<StartFire>();
      var5.set(var0, var2, var1, var3, var4);
      var5.process();

      for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
         if (var7.RelevantTo(var0.getX(), var0.getY())) {
    ByteBufferWriter var8 = var7.startPacket();
            PacketType.StartFire.doPacket(var8);
            var5.write(var8);
            PacketType.StartFire.send(var7);
         }
      }
   }

    static void sendOptionsToClients() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.ReloadOptions.doPacket(var2);
         var2.putInt(ServerOptions.instance.getPublicOptions().size());
    void* var3 = nullptr;

         for (std::string var5 : ServerOptions.instance.getPublicOptions()) {
            var2.putUTF(var5);
            var2.putUTF(ServerOptions.instance.getOption(var5));
         }

         PacketType.ReloadOptions.send(var1);
      }
   }

    static void sendBecomeCorpse(IsoDeadBody var0) {
    IsoGridSquare var1 = var0.getSquare();
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
            if (var3.RelevantTo(var1.x, var1.y)) {
    ByteBufferWriter var4 = var3.startPacket();
               PacketType.BecomeCorpse.doPacket(var4);

               try {
                  var4.putShort(var0.getObjectID());
                  var4.putShort(var0.getOnlineID());
                  var4.putFloat(var0.getReanimateTime());
                  if (var0.isPlayer()) {
                     var4.putByte((byte)2);
                  } else if (var0.isZombie()) {
                     var4.putByte((byte)1);
                  } else {
                     var4.putByte((byte)0);
                  }

                  var4.putInt(var1.x);
                  var4.putInt(var1.y);
                  var4.putInt(var1.z);
                  PacketType.BecomeCorpse.send(var3);
               } catch (Exception var6) {
                  var3.cancelPacket();
                  DebugLog.Multiplayer.printException(var6, "SendBecomeCorpse failed", LogSeverity.Error);
               }
            }
         }
      }
   }

    static void sendCorpse(IsoDeadBody var0) {
    IsoGridSquare var1 = var0.getSquare();
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
            if (var3.RelevantTo(var1.x, var1.y)) {
    ByteBufferWriter var4 = var3.startPacket();
               PacketType.AddCorpseToMap.doPacket(var4);
               var4.putShort(var0.getObjectID());
               var4.putShort(var0.getOnlineID());
               var4.putInt(var1.x);
               var4.putInt(var1.y);
               var4.putInt(var1.z);
               var0.writeToRemoteBuffer(var4);
               PacketType.AddCorpseToMap.send(var3);
            }
         }
      }
   }

    static void receiveAddCorpseToMap(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    IsoObject var8 = WorldItemTypes.createFromBuffer(var0);
      if (var8 != nullptr && dynamic_cast<IsoDeadBody*>(var8) != nullptr) {
         var8.loadFromRemoteBuffer(var0, false);
         ((IsoDeadBody)var8).setObjectID(var3);
    IsoGridSquare var9 = ServerMap.instance.getGridSquare(var5, var6, var7);
         if (var9 != nullptr) {
            var9.addCorpse((IsoDeadBody)var8, true);

            for (int var10 = 0; var10 < udpEngine.connections.size(); var10++) {
    UdpConnection var11 = (UdpConnection)udpEngine.connections.get(var10);
               if (var11.getConnectedGUID() != var1.getConnectedGUID() && var11.RelevantTo(var5, var6)) {
    ByteBufferWriter var12 = var11.startPacket();
                  PacketType.AddCorpseToMap.doPacket(var12);
                  var0.rewind();
                  var12.bb.put(var0);
                  PacketType.AddCorpseToMap.send(var11);
               }
            }
         }

         LoggerManager.getLogger("item").write(var1.idStr + " \"" + var1.username + "\" corpse +1 " + var5 + "," + var6 + "," + var7);
      }
   }

    static void receiveSmashWindow(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoObject var3 = IsoWorld.instance.getItemFromXYZIndexBuffer(var0);
      if (var3 != nullptr && dynamic_cast<IsoWindow*>(var3) != nullptr) {
    uint8_t var4 = var0.get();
         if (var4 == 1) {
            ((IsoWindow)var3).smashWindow(true);
            smashWindow((IsoWindow)var3, 1);
         } else if (var4 == 2) {
            ((IsoWindow)var3).setGlassRemoved(true);
            smashWindow((IsoWindow)var3, 2);
         }
      }
   }

    static void sendPlayerConnect(IsoPlayer var0, UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.PlayerConnect.doPacket(var2);
      if (var1.getConnectedGUID() != PlayerToAddressMap.get(var0)) {
         var2.putShort(var0.OnlineID);
      } else {
         var2.putShort((short)-1);
         var2.putByte((byte)var0.PlayerIndex);
         var2.putShort(var0.OnlineID);

         try {
            GameTime.getInstance().saveToPacket(var2.bb);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      }

      var2.putFloat(var0.x);
      var2.putFloat(var0.y);
      var2.putFloat(var0.z);
      var2.putUTF(var0.username);
      if (var1.getConnectedGUID() != PlayerToAddressMap.get(var0)) {
         try {
            var0.getDescriptor().save(var2.bb);
            var0.getHumanVisual().save(var2.bb);
    ItemVisuals var3 = std::make_shared<ItemVisuals>();
            var0.getItemVisuals(var3);
            var3.save(var2.bb);
         } catch (IOException var5) {
            var5.printStackTrace();
         }
      }

      if (SteamUtils.isSteamModeEnabled()) {
         var2.putLong(var0.getSteamID());
      }

      var2.putByte((byte)(var0.isGodMod() ? 1 : 0));
      var2.putByte((byte)(var0.isGhostMode() ? 1 : 0));
      var0.getSafety().save(var2.bb);
      var2.putByte(PlayerType.fromString(var0.accessLevel));
      var2.putByte((byte)(var0.isInvisible() ? 1 : 0));
      if (var1.getConnectedGUID() != PlayerToAddressMap.get(var0)) {
         try {
            var0.getXp().save(var2.bb);
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }

      var2.putUTF(var0.getTagPrefix());
      var2.putFloat(var0.getTagColor().r);
      var2.putFloat(var0.getTagColor().g);
      var2.putFloat(var0.getTagColor().b);
      var2.putDouble(var0.getHoursSurvived());
      var2.putInt(var0.getZombieKills());
      var2.putUTF(var0.getDisplayName());
      var2.putFloat(var0.getSpeakColour().r);
      var2.putFloat(var0.getSpeakColour().g);
      var2.putFloat(var0.getSpeakColour().b);
      var2.putBoolean(var0.showTag);
      var2.putBoolean(var0.factionPvp);
      var2.putInt(var0.getAttachedItems().size());

      for (int var7 = 0; var7 < var0.getAttachedItems().size(); var7++) {
         var2.putUTF(var0.getAttachedItems().get(var7).getLocation());
         var2.putUTF(var0.getAttachedItems().get(var7).getItem().getFullType());
      }

      var2.putInt(var0.remoteSneakLvl);
      var2.putInt(var0.remoteStrLvl);
      var2.putInt(var0.remoteFitLvl);
      PacketType.PlayerConnect.send(var1);
      if (var1.getConnectedGUID() != PlayerToAddressMap.get(var0)) {
         updateHandEquips(var1, var0);
      }
   }

    static void receiveRequestPlayerData(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoPlayer var3 = IDToPlayerMap.get(var0.getShort());
      if (var3 != nullptr) {
         sendPlayerConnect(var3, var1);
      }
   }

    static void receiveChatMessageFromPlayer(ByteBuffer var0, UdpConnection var1, short var2) {
      ChatServer.getInstance().processMessageFromPlayerPacket(var0);
   }

    static void loadModData(IsoGridSquare var0) {
      if (var0.getModData().rawget("id") != nullptr
         && var0.getModData().rawget("id") != nullptr
         && (var0.getModData().rawget("remove") == nullptr || ((std::string)var0.getModData().rawget("remove")) == "false"))) {
         GameTime.getInstance().getModData().rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":x", std::make_shared<double>(var0.getX()));
         GameTime.getInstance().getModData().rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":y", std::make_shared<double>(var0.getY()));
         GameTime.getInstance().getModData().rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":z", std::make_shared<double>(var0.getZ()));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":typeOfSeed", var0.getModData().rawget("typeOfSeed"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":nbOfGrow", (double)var0.getModData().rawget("nbOfGrow"));
         GameTime.getInstance().getModData().rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":id", var0.getModData().rawget("id"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":waterLvl", var0.getModData().rawget("waterLvl"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":lastWaterHour", var0.getModData().rawget("lastWaterHour"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":waterNeeded", var0.getModData().rawget("waterNeeded"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":waterNeededMax", var0.getModData().rawget("waterNeededMax"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":mildewLvl", var0.getModData().rawget("mildewLvl"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":aphidLvl", var0.getModData().rawget("aphidLvl"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":fliesLvl", var0.getModData().rawget("fliesLvl"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":fertilizer", var0.getModData().rawget("fertilizer"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":nextGrowing", var0.getModData().rawget("nextGrowing"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":hasVegetable", var0.getModData().rawget("hasVegetable"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":hasSeed", var0.getModData().rawget("hasSeed"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":health", var0.getModData().rawget("health"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":badCare", var0.getModData().rawget("badCare"));
         GameTime.getInstance()
            .getModData()
            .rawset("planting:" + ((double)var0.getModData().rawget("id")).intValue() + ":state", var0.getModData().rawget("state"));
         if (var0.getModData().rawget("hoursElapsed") != nullptr) {
            GameTime.getInstance().getModData().rawset("hoursElapsed", var0.getModData().rawget("hoursElapsed"));
         }
      }

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
         if (var2.RelevantTo(var0.getX(), var0.getY())) {
    ByteBufferWriter var3 = var2.startPacket();
            PacketType.ReceiveModData.doPacket(var3);
            var3.putInt(var0.getX());
            var3.putInt(var0.getY());
            var3.putInt(var0.getZ());

            try {
               var0.getModData().save(var3.bb);
            } catch (IOException var5) {
               var5.printStackTrace();
            }

            PacketType.ReceiveModData.send(var2);
         }
      }
   }

    static void receiveSendModData(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = ServerMap.instance.getGridSquare(var3, var4, var5);
      if (var6 != nullptr) {
         try {
            var6.getModData().load(var0, 195);
            if (var6.getModData().rawget("id") != nullptr
               && (var6.getModData().rawget("remove") == nullptr || ((std::string)var6.getModData().rawget("remove")) == "false"))) {
               GameTime.getInstance().getModData().rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":x", std::make_shared<double>(var6.getX()));
               GameTime.getInstance().getModData().rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":y", std::make_shared<double>(var6.getY()));
               GameTime.getInstance().getModData().rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":z", std::make_shared<double>(var6.getZ()));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":typeOfSeed", var6.getModData().rawget("typeOfSeed"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":nbOfGrow", (double)var6.getModData().rawget("nbOfGrow"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":id", var6.getModData().rawget("id"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":waterLvl", var6.getModData().rawget("waterLvl"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":lastWaterHour", var6.getModData().rawget("lastWaterHour"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":waterNeeded", var6.getModData().rawget("waterNeeded"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":waterNeededMax", var6.getModData().rawget("waterNeededMax"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":mildewLvl", var6.getModData().rawget("mildewLvl"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":aphidLvl", var6.getModData().rawget("aphidLvl"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":fliesLvl", var6.getModData().rawget("fliesLvl"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":fertilizer", var6.getModData().rawget("fertilizer"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":nextGrowing", var6.getModData().rawget("nextGrowing"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":hasVegetable", var6.getModData().rawget("hasVegetable"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":hasSeed", var6.getModData().rawget("hasSeed"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":health", var6.getModData().rawget("health"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":badCare", var6.getModData().rawget("badCare"));
               GameTime.getInstance()
                  .getModData()
                  .rawset("planting:" + ((double)var6.getModData().rawget("id")).intValue() + ":state", var6.getModData().rawget("state"));
               if (var6.getModData().rawget("hoursElapsed") != nullptr) {
                  GameTime.getInstance().getModData().rawset("hoursElapsed", var6.getModData().rawget("hoursElapsed"));
               }
            }

            LuaEventManager.triggerEvent("onLoadModDataFromServer", var6);

            for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
               if (var8.RelevantTo(var6.getX(), var6.getY()) && (var1 == nullptr || var8.getConnectedGUID() != var1.getConnectedGUID())) {
    ByteBufferWriter var9 = var8.startPacket();
                  PacketType.ReceiveModData.doPacket(var9);
                  var9.putInt(var3);
                  var9.putInt(var4);
                  var9.putInt(var5);

                  try {
                     var6.getModData().save(var9.bb);
                  } catch (IOException var11) {
                     var11.printStackTrace();
                  }

                  PacketType.ReceiveModData.send(var8);
               }
            }
         } catch (IOException var12) {
            var12.printStackTrace();
         }
      }
   }

    static void receiveWeaponHit(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoObject var3 = getIsoObjectRefFromByteBuffer(var0);
    short var4 = var0.getShort();
    std::string var5 = GameWindow.ReadStringUTF(var0);
    IsoPlayer var6 = getPlayerFromConnection(var1, var4);
      if (var3 != nullptr && var6 != nullptr) {
    InventoryItem var7 = nullptr;
         if (!var5.empty()) {
            var7 = InventoryItemFactory.CreateItem(var5);
            if (!(dynamic_cast<HandWeapon*>(var7) != nullptr)) {
               return;
            }
         }

         if (var7 == nullptr && !(dynamic_cast<IsoWindow*>(var3) != nullptr)) {
            return;
         }

    int var8 = (int)var3.getX();
    int var9 = (int)var3.getY();
    int var10 = (int)var3.getZ();
         if (dynamic_cast<IsoDoor*>(var3) != nullptr) {
            ((IsoDoor)var3).WeaponHit(var6, (HandWeapon)var7);
         } else if (dynamic_cast<IsoThumpable*>(var3) != nullptr) {
            ((IsoThumpable)var3).WeaponHit(var6, (HandWeapon)var7);
         } else if (dynamic_cast<IsoWindow*>(var3) != nullptr) {
            ((IsoWindow)var3).WeaponHit(var6, (HandWeapon)var7);
         } else if (dynamic_cast<IsoBarricade*>(var3) != nullptr) {
            ((IsoBarricade)var3).WeaponHit(var6, (HandWeapon)var7);
         }

         if (var3.getObjectIndex() == -1) {
            LoggerManager.getLogger("map")
               .write(
                  var1.idStr
                     + " \""
                     + var1.username
                     + "\" destroyed "
                     + (var3.getName() != nullptr ? var3.getName() : var3.getObjectName())
                     + " with "
                     + (var5.empty() ? "BareHands" : var5)
                     + " at "
                     + var8
                     + ","
                     + var9
                     + ","
                     + var10
               );
         }
      }
   }

    static void putIsoObjectRefToByteBuffer(IsoObject var0, ByteBuffer var1) {
      var1.putInt(var0.square.x);
      var1.putInt(var0.square.y);
      var1.putInt(var0.square.z);
      var1.put((byte)var0.square.getObjects().indexOf(var0));
   }

    static IsoObject getIsoObjectRefFromByteBuffer(ByteBuffer var0) {
    int var1 = var0.getInt();
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    uint8_t var4 = var0.get();
    IsoGridSquare var5 = ServerMap.instance.getGridSquare(var1, var2, var3);
      return var5 != nullptr && var4 >= 0 && var4 < var5.getObjects().size() ? (IsoObject)var5.getObjects().get(var4) : nullptr;
   }

    static void receiveDrink(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    float var4 = var0.getFloat();
    IsoPlayer var5 = getPlayerFromConnection(var1, var3);
      if (var5 != nullptr) {
         var5.getStats().thirst -= var4;
         if (var5.getStats().thirst < 0.0F) {
            var5.getStats().thirst = 0.0F;
         }
      }
   }

    static void process(ZomboidNetData var0) {
    ByteBuffer var1 = var0.buffer;
    UdpConnection var2 = udpEngine.getActiveConnection(var0.connection);

      try {
         switch (var0.type) {
            default:
               doZomboidDataInMainLoop(var0);
         }
      } catch (Exception var4) {
         DebugLog.log(DebugType.Network, "Error with packet of type: " + var0.type);
         var4.printStackTrace();
      }
   }

    static void receiveEatFood(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    float var4 = var0.getFloat();
    InventoryItem var5 = nullptr;

      try {
         var5 = InventoryItem.loadItem(var0, 195);
      } catch (Exception var7) {
         var7.printStackTrace();
      }

      if (dynamic_cast<Food*>(var5) != nullptr) {
    IsoPlayer var6 = getPlayerFromConnection(var1, var3);
         if (var6 != nullptr) {
            var6.Eat(var5, var4);
         }
      }
   }

    static void receivePingFromClient(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferWriter var3 = var1.startPacket();
    long var4 = var0.getLong();
      if (var4 == -1L) {
         DebugLog.Multiplayer.warn("Player \"%s\" toggled lua debugger", new Object[]{var1.username});
      } else {
         if (var1.accessLevel != 32) {
            return;
         }

         PacketType.PingFromClient.doPacket(var3);

         try {
            var3.putLong(var4);
            MPStatistics.write(var1, var3.bb);
            PacketType.PingFromClient.send(var1);
            MPStatistics.requested();
         } catch (Exception var7) {
            var1.cancelPacket();
         }
      }
   }

    static void receiveBandage(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    int var5 = var0.getInt();
    bool var6 = var0.get() == 1;
    float var7 = var0.getFloat();
    bool var8 = var0.get() == 1;
    std::string var9 = GameWindow.ReadStringUTF(var0);
         var4.getBodyDamage().SetBandaged(var5, var6, var7, var8, var9);

         for (int var10 = 0; var10 < udpEngine.connections.size(); var10++) {
    UdpConnection var11 = (UdpConnection)udpEngine.connections.get(var10);
            if (var11.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var12 = var11.startPacket();
               PacketType.Bandage.doPacket(var12);
               var12.putShort(var3);
               var12.putInt(var5);
               var12.putBoolean(var6);
               var12.putFloat(var7);
               var12.putBoolean(var8);
               GameWindow.WriteStringUTF(var12.bb, var9);
               PacketType.Bandage.send(var11);
            }
         }
      }
   }

    static void receiveStitch(ByteBuffer var0, UdpConnection var1, short var2) {
    Stitch var3 = std::make_shared<Stitch>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.Stitch.doPacket(var6);
               var3.write(var6);
               PacketType.Stitch.send(var5);
            }
         }
      }
   }

    static void receiveWoundInfection(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    int var5 = var0.getInt();
    bool var6 = var0.get() == 1;
         var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5)).setInfectedWound(var6);

         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var9 = var8.startPacket();
               PacketType.WoundInfection.doPacket(var9);
               var9.putShort(var3);
               var9.putInt(var5);
               var9.putBoolean(var6);
               PacketType.WoundInfection.send(var8);
            }
         }
      }
   }

    static void receiveDisinfect(ByteBuffer var0, UdpConnection var1, short var2) {
    Disinfect var3 = std::make_shared<Disinfect>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.Disinfect.doPacket(var6);
               var3.write(var6);
               PacketType.Disinfect.send(var5);
            }
         }
      }
   }

    static void receiveSplint(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    int var5 = var0.getInt();
    bool var6 = var0.get() == 1;
    std::string var7 = var6 ? GameWindow.ReadStringUTF(var0) : nullptr;
    float var8 = var6 ? var0.getFloat() : 0.0F;
    BodyPart var9 = var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5));
         var9.setSplint(var6, var8);
         var9.setSplintItem(var7);

         for (int var10 = 0; var10 < udpEngine.connections.size(); var10++) {
    UdpConnection var11 = (UdpConnection)udpEngine.connections.get(var10);
            if (var11.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var12 = var11.startPacket();
               PacketType.Splint.doPacket(var12);
               var12.putShort(var3);
               var12.putInt(var5);
               var12.putBoolean(var6);
               if (var6) {
                  var12.putUTF(var7);
                  var12.putFloat(var8);
               }

               PacketType.Splint.send(var11);
            }
         }
      }
   }

    static void receiveAdditionalPain(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
    int var5 = var0.getInt();
    float var6 = var0.getFloat();
    BodyPart var7 = var4.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5));
         var7.setAdditionalPain(var7.getAdditionalPain() + var6);

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.AdditionalPain.doPacket(var10);
               var10.putShort(var3);
               var10.putInt(var5);
               var10.putFloat(var6);
               PacketType.AdditionalPain.send(var9);
            }
         }
      }
   }

    static void receiveRemoveGlass(ByteBuffer var0, UdpConnection var1, short var2) {
    RemoveGlass var3 = std::make_shared<RemoveGlass>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         var3.process();

         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.RemoveGlass.doPacket(var6);
               var3.write(var6);
               PacketType.RemoveGlass.send(var5);
            }
         }
      }
   }

    static void receiveRemoveBullet(ByteBuffer var0, UdpConnection var1, short var2) {
    RemoveBullet var3 = std::make_shared<RemoveBullet>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         var3.process();

         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.RemoveBullet.doPacket(var6);
               var3.write(var6);
               PacketType.RemoveBullet.send(var5);
            }
         }
      }
   }

    static void receiveCleanBurn(ByteBuffer var0, UdpConnection var1, short var2) {
    CleanBurn var3 = std::make_shared<CleanBurn>();
      var3.parse(var0, var1);
      if (var3.isConsistent() && var3.validate(var1)) {
         var3.process();

         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.CleanBurn.doPacket(var6);
               var3.write(var6);
               PacketType.CleanBurn.send(var5);
            }
         }
      }
   }

    static void receiveBodyDamageUpdate(ByteBuffer var0, UdpConnection var1, short var2) {
      BodyDamageSync.instance.serverPacket(var0);
   }

    static void receiveReceiveCommand(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    void* var4 = nullptr;
      var4 = handleClientCommand(var3.substr(1), var1);
      if (var4 == nullptr) {
         var4 = handleServerCommand(var3.substr(1), var1);
      }

      if (var4 == nullptr) {
         var4 = "Unknown command " + var3;
      }

      if (!var3.substr(1).startsWith("roll") && !var3.substr(1).startsWith("card")) {
         ChatServer.getInstance().sendMessageToServerChat(var1, (std::string)var4);
      } else {
         ChatServer.getInstance().sendMessageToServerChat(var1, (std::string)var4);
      }
   }

    static std::string handleClientCommand(const std::string& var0, UdpConnection var1) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    std::vector var2 = new std::vector();
    Matcher var3 = Pattern.compile("([^\"]\\S*|\".*?\")\\s*").matcher(var0);

         while (var3.find()) {
            var2.push_back(var3.group(1).replace("\"", ""));
         }

    int var4 = var2.size();
         std::string[] var5 = var2.toArray(new std::string[var4]);
    std::string var6 = var4 > 0 ? var5[0].toLowerCase() : "";
         if (var6 == "card")) {
            PlayWorldSoundServer("ChatDrawCard", false, getAnyPlayerFromConnection(var1).getCurrentSquare(), 0.0F, 3.0F, 1.0F, false);
            return var1.username + " drew " + ServerOptions.getRandomCard();
         } else if (var6 == "roll")) {
            if (var4 != 2) {
               return (std::string)ServerOptions.clientOptionsList.get("roll");
            } else {
    int var13 = 0;

               try {
                  var13 = int.parseInt(var5[1]);
                  PlayWorldSoundServer("ChatRollDice", false, getAnyPlayerFromConnection(var1).getCurrentSquare(), 0.0F, 3.0F, 1.0F, false);
                  return var1.username + " rolls a " + var13 + "-sided dice and obtains " + Rand.Next(var13);
               } catch (Exception var10) {
                  return (std::string)ServerOptions.clientOptionsList.get("roll");
               }
            }
         } else if (var6 == "changepwd")) {
            if (var4 == 3) {
    std::string var12 = var5[1];
    std::string var8 = var5[2];

               try {
                  return ServerWorldDatabase.instance.changePwd(var1.username, var12.trim(), var8.trim());
               } catch (SQLException var11) {
                  var11.printStackTrace();
                  return "A SQL error occured";
               }
            } else {
               return (std::string)ServerOptions.clientOptionsList.get("changepwd");
            }
         } else if (var6 == "dragons")) {
            return "Sorry, you don't have the required materials.";
         } else if (var6 == "dance")) {
            return "Stop kidding me...";
         } else if (var6 == "safehouse")) {
            if (var4 != 2 || var1 == nullptr) {
               return (std::string)ServerOptions.clientOptionsList.get("safehouse");
            } else if (!ServerOptions.instance.PlayerSafehouse.getValue() && !ServerOptions.instance.AdminSafehouse.getValue()) {
               return "Safehouses are disabled on this server.";
            } else if ("release" == var5[1])) {
    SafeHouse var7 = SafeHouse.hasSafehouse(var1.username);
               if (var7 == nullptr) {
                  return "You don't own a safehouse.";
               } else if (!ServerOptions.instance.PlayerSafehouse.getValue() && !"admin" == var1.accessLevel) && !"moderator" == var1.accessLevel)) {
                  return "Only admin or moderator may release safehouses";
               } else {
                  var7.removeSafeHouse(nullptr);
                  return "Safehouse released";
               }
            } else {
               return (std::string)ServerOptions.clientOptionsList.get("safehouse");
            }
         } else {
    return nullptr;
         }
      }
   }

    static void doZomboidDataInMainLoop(ZomboidNetData var0) {
      /* synchronized - TODO: add std::mutex */ (MainLoopNetDataHighPriorityQ) {
         MainLoopNetDataHighPriorityQ.push_back(var0);
      }
   }

    static void receiveEquip(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    uint8_t var4 = var0.get();
    uint8_t var5 = var0.get();
    InventoryItem var6 = nullptr;
    IsoPlayer var7 = getPlayerFromConnection(var1, var3);
      if (var5 == 1) {
         try {
            var6 = InventoryItem.loadItem(var0, 195);
         } catch (Exception var15) {
            var15.printStackTrace();
         }

         if (var6 == nullptr) {
            LoggerManager.getLogger("user").write(var1.idStr + " equipped unknown item type");
            return;
         }
      }

      if (var7 != nullptr) {
         if (var6 != nullptr) {
            var6.setContainer(var7.getInventory());
         }

         if (var4 == 0) {
            var7.setPrimaryHandItem(var6);
         } else {
            if (var5 == 2) {
               var6 = var7.getPrimaryHandItem();
            }

            var7.setSecondaryHandItem(var6);
         }

         try {
            if (var5 == 1 && var6 != nullptr && var0.get() == 1) {
               var6.getVisual().load(var0, 195);
            }
         } catch (IOException var14) {
            var14.printStackTrace();
         }
      }

      if (var7 != nullptr) {
         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var10 = getAnyPlayerFromConnection(var9);
               if (var10 != nullptr) {
    ByteBufferWriter var11 = var9.startPacket();
                  PacketType.Equip.doPacket(var11);
                  var11.putShort(var7.OnlineID);
                  var11.putByte(var4);
                  var11.putByte(var5);
                  if (var5 == 1) {
                     try {
                        var6.saveWithSize(var11.bb, false);
                        if (var6.getVisual() != nullptr) {
                           var11.bb.put((byte)1);
                           var6.getVisual().save(var11.bb);
                        } else {
                           var11.bb.put((byte)0);
                        }
                     } catch (IOException var13) {
                        var13.printStackTrace();
                     }
                  }

                  PacketType.Equip.send(var9);
               }
            }
         }
      }
   }

    static void receivePlayerConnect(ByteBuffer var0, UdpConnection var1, short var2) {
      receivePlayerConnect(var0, var1, var1.username);
      sendInitialWorldState(var1);
   }

    static void receiveScoreboardUpdate(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.ScoreboardUpdate.doPacket(var3);
    std::vector var4 = new std::vector();
    std::vector var5 = new std::vector();
    std::vector var6 = new std::vector();

      for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
         if (var8.isFullyConnected()) {
            for (int var9 = 0; var9 < 4; var9++) {
               if (var8.usernames[var9] != nullptr) {
                  var4.push_back(var8.usernames[var9]);
    IsoPlayer var10 = getPlayerByRealUserName(var8.usernames[var9]);
                  if (var10 != nullptr) {
                     var5.push_back(var10.getDisplayName());
                  } else {
    std::string var11 = ServerWorldDatabase.instance.getDisplayName(var8.usernames[var9]);
                     var5.push_back(var11 == nullptr ? var8.usernames[var9] : var11);
                  }

                  if (SteamUtils.isSteamModeEnabled()) {
                     var6.push_back(var8.steamID);
                  }
               }
            }
         }
      }

      var3.putInt(var4.size());

      for (int var12 = 0; var12 < var4.size(); var12++) {
         var3.putUTF((std::string)var4.get(var12));
         var3.putUTF((std::string)var5.get(var12));
         if (SteamUtils.isSteamModeEnabled()) {
            var3.putLong((int64_t)var6.get(var12));
         }
      }

      PacketType.ScoreboardUpdate.send(var1);
   }

    static void receiveStopSound(ByteBuffer var0, UdpConnection var1, short var2) {
    StopSoundPacket var3 = std::make_shared<StopSoundPacket>();
      var3.parse(var0, var1);

      for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
         if (var5.getConnectedGUID() != var1.getConnectedGUID() && var5.isFullyConnected()) {
    ByteBufferWriter var6 = var5.startPacket();
            PacketType.StopSound.doPacket(var6);
            var3.write(var6);
            PacketType.StopSound.send(var5);
         }
      }
   }

    static void receivePlaySound(ByteBuffer var0, UdpConnection var1, short var2) {
    PlaySoundPacket var3 = std::make_shared<PlaySoundPacket>();
      var3.parse(var0, var1);
    IsoMovingObject var4 = var3.getMovingObject();
      if (var3.isConsistent()) {
    int var5 = 70;
    GameSound var6 = GameSounds.getSound(var3.getName());
         if (var6 != nullptr) {
            for (int var7 = 0; var7 < var6.clips.size(); var7++) {
    GameSoundClip var8 = (GameSoundClip)var6.clips.get(var7);
               if (var8.hasMaxDistance()) {
                  var5 = Math.max(var5, (int)var8.distanceMax);
               }
            }
         }

         for (int var11 = 0; var11 < udpEngine.connections.size(); var11++) {
    UdpConnection var12 = (UdpConnection)udpEngine.connections.get(var11);
            if (var12.getConnectedGUID() != var1.getConnectedGUID() && var12.isFullyConnected()) {
    IsoPlayer var9 = getAnyPlayerFromConnection(var12);
               if (var9 != nullptr && (var4 == nullptr || var12.RelevantTo(var4.getX(), var4.getY(), var5))) {
    ByteBufferWriter var10 = var12.startPacket();
                  PacketType.PlaySound.doPacket(var10);
                  var3.write(var10);
                  PacketType.PlaySound.send(var12);
               }
            }
         }
      }
   }

    static void receivePlayWorldSound(ByteBuffer var0, UdpConnection var1, short var2) {
    PlayWorldSoundPacket var3 = std::make_shared<PlayWorldSoundPacket>();
      var3.parse(var0, var1);
      if (var3.isConsistent()) {
    int var4 = 70;
    GameSound var5 = GameSounds.getSound(var3.getName());
         if (var5 != nullptr) {
            for (int var6 = 0; var6 < var5.clips.size(); var6++) {
    GameSoundClip var7 = (GameSoundClip)var5.clips.get(var6);
               if (var7.hasMaxDistance()) {
                  var4 = Math.max(var4, (int)var7.distanceMax);
               }
            }
         }

         for (int var10 = 0; var10 < udpEngine.connections.size(); var10++) {
    UdpConnection var11 = (UdpConnection)udpEngine.connections.get(var10);
            if (var11.getConnectedGUID() != var1.getConnectedGUID() && var11.isFullyConnected()) {
    IsoPlayer var8 = getAnyPlayerFromConnection(var11);
               if (var8 != nullptr && var11.RelevantTo(var3.getX(), var3.getY(), var4)) {
    ByteBufferWriter var9 = var11.startPacket();
                  PacketType.PlayWorldSound.doPacket(var9);
                  var3.write(var9);
                  PacketType.PlayWorldSound.send(var11);
               }
            }
         }
      }
   }

    static void PlayWorldSound(const std::string& var0, IsoGridSquare var1, float var2) {
      if (bServer && var1 != nullptr) {
    int var3 = var1.getX();
    int var4 = var1.getY();
    int var5 = var1.getZ();
    PlayWorldSoundPacket var6 = std::make_shared<PlayWorldSoundPacket>();
         var6.set(var0, var3, var4, (byte)var5);
         DebugLog.log(DebugType.Sound, "sending " + var6.getDescription() + " radius=" + var2);

         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
    IsoPlayer var9 = getAnyPlayerFromConnection(var8);
            if (var9 != nullptr && var8.RelevantTo(var3, var4, var2 * 2.0F)) {
    ByteBufferWriter var10 = var8.startPacket();
               PacketType.PlayWorldSound.doPacket(var10);
               var6.write(var10);
               PacketType.PlayWorldSound.send(var8);
            }
         }
      }
   }

    static void PlayWorldSoundServer(const std::string& var0, bool var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
      PlayWorldSound(var0, var2, var4);
   }

   public static void PlayWorldSoundServer(
      IsoGameCharacter var0, std::string var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7
   ) {
      if (var0 == nullptr || !var0.isInvisible() || DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue()) {
         PlayWorldSound(var1, var3, var5);
      }
   }

    static void PlayWorldSoundWavServer(const std::string& var0, bool var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
      PlayWorldSound(var0, var2, var4);
   }

    static void PlaySoundAtEveryPlayer(const std::string& var0, int var1, int var2, int var3) {
      PlaySoundAtEveryPlayer(var0, var1, var2, var3, false);
   }

    static void PlaySoundAtEveryPlayer(const std::string& var0) {
      PlaySoundAtEveryPlayer(var0, -1, -1, -1, true);
   }

    static void PlaySoundAtEveryPlayer(const std::string& var0, int var1, int var2, int var3, bool var4) {
      if (bServer) {
         if (var4) {
            DebugLog.log(DebugType.Sound, "sound: sending " + var0 + " at every player (using player location)");
         } else {
            DebugLog.log(DebugType.Sound, "sound: sending " + var0 + " at every player location x=" + var1 + " y=" + var2);
         }

         for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
    IsoPlayer var7 = getAnyPlayerFromConnection(var6);
            if (var7 != nullptr && !var7.isDeaf()) {
               if (var4) {
                  var1 = (int)var7.getX();
                  var2 = (int)var7.getY();
                  var3 = (int)var7.getZ();
               }

    ByteBufferWriter var8 = var6.startPacket();
               PacketType.PlaySoundEveryPlayer.doPacket(var8);
               var8.putUTF(var0);
               var8.putInt(var1);
               var8.putInt(var2);
               var8.putInt(var3);
               PacketType.PlaySoundEveryPlayer.send(var6);
            }
         }
      }
   }

    static void sendZombieSound(ZombieSound var0, IsoZombie var1) {
    float var2 = var0.radius();
      DebugLog.log(DebugType.Sound, "sound: sending zombie sound " + var0);

      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         if (var4.isFullyConnected() && var4.RelevantTo(var1.getX(), var1.getY(), var2)) {
    ByteBufferWriter var5 = var4.startPacket();
            PacketType.ZombieSound.doPacket(var5);
            var5.putShort(var1.OnlineID);
            var5.putByte((byte)var0.ordinal());
            PacketType.ZombieSound.send(var4);
         }
      }
   }

    static void receiveZombieHelmetFalling(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    short var4 = var0.getShort();
    std::string var5 = GameWindow.ReadString(var0);
    IsoZombie var6 = (IsoZombie)ServerMap.instance.ZombieMap.get(var4);
    IsoPlayer var7 = getPlayerFromConnection(var1, var3);
      if (var7 != nullptr && var6 != nullptr) {
         var6.serverRemoveItemFromZombie(var5);

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var10 = getAnyPlayerFromConnection(var1);
               if (var10 != nullptr) {
                  try {
    ByteBufferWriter var11 = var9.startPacket();
                     PacketType.ZombieHelmetFalling.doPacket(var11);
                     var11.putShort(var4);
                     var11.putUTF(var5);
                     PacketType.ZombieHelmetFalling.send(var9);
                  } catch (Throwable var12) {
                     var1.cancelPacket();
                     ExceptionLogger.logException(var12);
                  }
               }
            }
         }
      }
   }

    static void receivePlayerAttachedItem(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    std::string var4 = GameWindow.ReadString(var0);
    bool var5 = var0.get() == 1;
    InventoryItem var6 = nullptr;
      if (var5) {
    std::string var7 = GameWindow.ReadString(var0);
         var6 = InventoryItemFactory.CreateItem(var7);
         if (var6 == nullptr) {
            return;
         }
      }

    IsoPlayer var13 = getPlayerFromConnection(var1, var3);
      if (var13 != nullptr) {
         var13.setAttachedItem(var4, var6);

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var10 = getAnyPlayerFromConnection(var1);
               if (var10 != nullptr) {
                  try {
    ByteBufferWriter var11 = var9.startPacket();
                     PacketType.PlayerAttachedItem.doPacket(var11);
                     var11.putShort(var13.OnlineID);
                     GameWindow.WriteString(var11.bb, var4);
                     var11.putByte((byte)(var5 ? 1 : 0));
                     if (var5) {
                        GameWindow.WriteString(var11.bb, var6.getFullType());
                     }

                     PacketType.PlayerAttachedItem.send(var9);
                  } catch (Throwable var12) {
                     var1.cancelPacket();
                     ExceptionLogger.logException(var12);
                  }
               }
            }
         }
      }
   }

    static void receiveSyncClothing(ByteBuffer var0, UdpConnection var1, short var2) {
    SyncClothingPacket var3 = std::make_shared<SyncClothingPacket>();
      var3.parse(var0, var1);
      if (var3.isConsistent()) {
         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var6 = getAnyPlayerFromConnection(var1);
               if (var6 != nullptr) {
    ByteBufferWriter var7 = var5.startPacket();
                  PacketType.SyncClothing.doPacket(var7);
                  var3.write(var7);
                  PacketType.SyncClothing.send(var5);
               }
            }
         }
      }
   }

    static void receiveHumanVisual(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    IsoPlayer var4 = IDToPlayerMap.get(var3);
      if (var4 != nullptr) {
         if (!var1.havePlayer(var4)) {
            DebugLog.Network.warn("User " + var1.username + " sent HumanVisual packet for non owned player #" + var4.OnlineID);
         } else {
            try {
               var4.getHumanVisual().load(var0, 195);
            } catch (Throwable var11) {
               ExceptionLogger.logException(var11);
               return;
            }

            for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
               if (var6.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var7 = getAnyPlayerFromConnection(var6);
                  if (var7 != nullptr) {
    ByteBufferWriter var8 = var6.startPacket();
                     PacketType.HumanVisual.doPacket(var8);

                     try {
                        var8.putShort(var4.OnlineID);
                        var4.getHumanVisual().save(var8.bb);
                        PacketType.HumanVisual.send(var6);
                     } catch (Throwable var10) {
                        var6.cancelPacket();
                        ExceptionLogger.logException(var10);
                     }
                  }
               }
            }
         }
      }
   }

    static void initClientCommandFilter() {
    std::string var0 = ServerOptions.getInstance().ClientCommandFilter.getValue();
      ccFilters.clear();
      std::string[] var1 = var0.split(";");

    for (auto& var5 : var1)         if (!var5.empty() && var5.contains(".") && (var5.startsWith("+") || var5.startsWith("-"))) {
            std::string[] var6 = var5.split("\\.");
            if (var6.length == 2) {
    std::string var7 = var6[0].substr(1);
    std::string var8 = var6[1];
    CCFilter var9 = std::make_shared<CCFilter>();
               var9.command = var8;
               var9.allow = var6[0].startsWith("+");
               var9.next = ccFilters.get(var7);
               ccFilters.put(var7, var9);
            }
         }
      }
   }

    static void receiveClientCommand(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
    bool var6 = var0.get() == 1;
    KahluaTable var7 = nullptr;
      if (var6) {
         var7 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var7, var0);
         } catch (Exception var10) {
            var10.printStackTrace();
            return;
         }
      }

    IsoPlayer var8 = getPlayerFromConnection(var1, var3);
      if (var3 == -1) {
         var8 = getAnyPlayerFromConnection(var1);
      }

      if (var8 == nullptr) {
         DebugLog.log("receiveClientCommand: player is nullptr");
      } else {
    CCFilter var9 = ccFilters.get(var4);
         if (var9 == nullptr || var9.passes(var5)) {
            LoggerManager.getLogger("cmd")
               .write(
                  var1.idStr + " \"" + var8.username + "\" " + var4 + "." + var5 + " @ " + (int)var8.getX() + "," + (int)var8.getY() + "," + (int)var8.getZ()
               );
         }

         if (!"vehicle" == var4)
            || !"remove" == var5)
            || Core.bDebug
            || PlayerType.isPrivileged(var1.accessLevel)
            || var8.networkAI.isDismantleAllowed()) {
            LuaEventManager.triggerEvent("OnClientCommand", var4, var5, var8, var7);
         }
      }
   }

    static void receiveGlobalObjects(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    IsoPlayer var4 = getPlayerFromConnection(var1, var3);
      if (var3 == -1) {
         var4 = getAnyPlayerFromConnection(var1);
      }

      if (var4 == nullptr) {
         DebugLog.log("receiveGlobalObjects: player is nullptr");
      } else {
         SGlobalObjectNetwork.receive(var0, var4);
      }
   }

    static IsoPlayer getAnyPlayerFromConnection(UdpConnection var0) {
      for (int var1 = 0; var1 < 4; var1++) {
         if (var0.players[var1] != nullptr) {
            return var0.players[var1];
         }
      }

    return nullptr;
   }

    static IsoPlayer getPlayerFromConnection(UdpConnection var0, int var1) {
      return var1 >= 0 && var1 < 4 ? var0.players[var1] : nullptr;
   }

    static IsoPlayer getPlayerByRealUserName(const std::string& var0) {
      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         for (int var3 = 0; var3 < 4; var3++) {
    IsoPlayer var4 = var2.players[var3];
            if (var4 != nullptr && var4.username == var0)) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    static IsoPlayer getPlayerByUserName(const std::string& var0) {
      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         for (int var3 = 0; var3 < 4; var3++) {
    IsoPlayer var4 = var2.players[var3];
            if (var4 != nullptr && (var4.getDisplayName() == var0) || var4.getUsername() == var0))) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    static IsoPlayer getPlayerByUserNameForCommand(const std::string& var0) {
      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         for (int var3 = 0; var3 < 4; var3++) {
    IsoPlayer var4 = var2.players[var3];
            if (var4 != nullptr
               && (var4.getDisplayName().toLowerCase() == var0.toLowerCase()) || var4.getDisplayName().toLowerCase().startsWith(var0.toLowerCase()))) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    static UdpConnection getConnectionByPlayerOnlineID(short var0) {
      return udpEngine.getActiveConnection(IDToAddressMap.get(var0));
   }

    static UdpConnection getConnectionFromPlayer(IsoPlayer var0) {
    long var1 = PlayerToAddressMap.get(var0);
    return var1 = = nullptr ? nullptr : udpEngine.getActiveConnection(var1);
   }

    static void receiveRemoveBlood(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    bool var6 = var0.get() == 1;
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var7 != nullptr) {
         var7.removeBlood(false, var6);

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9 != var1 && var9.RelevantTo(var3, var4)) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.RemoveBlood.doPacket(var10);
               var10.putInt(var3);
               var10.putInt(var4);
               var10.putInt(var5);
               var10.putBoolean(var6);
               PacketType.RemoveBlood.send(var9);
            }
         }
      }
   }

    static void sendAddItemToContainer(ItemContainer var0, InventoryItem var1) {
    void* var2 = var0.getParent();
      if (var0.getContainingItem() != nullptr && var0.getContainingItem().getWorldItem() != nullptr) {
         var2 = var0.getContainingItem().getWorldItem();
      }

      if (var2 == nullptr) {
         DebugLog.General.error("container has no parent object");
      } else {
    IsoGridSquare var3 = var2.getSquare();
         if (var3 == nullptr) {
            DebugLog.General.error("container parent object has no square");
         } else {
            for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
               if (var5.RelevantTo(var3.x, var3.y)) {
    ByteBufferWriter var6 = var5.startPacket();
                  PacketType.AddInventoryItemToContainer.doPacket(var6);
                  if (dynamic_cast<IsoDeadBody*>(var2) != nullptr) {
                     var6.putShort((short)0);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putByte((byte)var2.getStaticMovingObjectIndex());
                  } else if (dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) {
                     var6.putShort((short)1);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putInt(((IsoWorldInventoryObject)var2).getItem().id);
                  } else if (dynamic_cast<BaseVehicle*>(var2) != nullptr) {
                     var6.putShort((short)3);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putShort(((BaseVehicle)var2).VehicleID);
                     var6.putByte((byte)var0.vehiclePart.getIndex());
                  } else {
                     var6.putShort((short)2);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putByte((byte)((IsoObject)var2).square.getObjects().indexOf(var2));
                     var6.putByte((byte)var2.getContainerIndex(var0));
                  }

                  try {
                     CompressIdenticalItems.save(var6.bb, var1);
                  } catch (Exception var8) {
                     var8.printStackTrace();
                  }

                  PacketType.AddInventoryItemToContainer.send(var5);
               }
            }
         }
      }
   }

    static void sendRemoveItemFromContainer(ItemContainer var0, InventoryItem var1) {
    void* var2 = var0.getParent();
      if (var0.getContainingItem() != nullptr && var0.getContainingItem().getWorldItem() != nullptr) {
         var2 = var0.getContainingItem().getWorldItem();
      }

      if (var2 == nullptr) {
         DebugLog.log("sendRemoveItemFromContainer: o is nullptr");
      } else {
    IsoGridSquare var3 = var2.getSquare();
         if (var3 == nullptr) {
            DebugLog.log("sendRemoveItemFromContainer: square is nullptr");
         } else {
            for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
               if (var5.RelevantTo(var3.x, var3.y)) {
    ByteBufferWriter var6 = var5.startPacket();
                  PacketType.RemoveInventoryItemFromContainer.doPacket(var6);
                  if (dynamic_cast<IsoDeadBody*>(var2) != nullptr) {
                     var6.putShort((short)0);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putByte((byte)var2.getStaticMovingObjectIndex());
                     var6.putInt(1);
                     var6.putInt(var1.id);
                  } else if (dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) {
                     var6.putShort((short)1);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putInt(((IsoWorldInventoryObject)var2).getItem().id);
                     var6.putInt(1);
                     var6.putInt(var1.id);
                  } else if (dynamic_cast<BaseVehicle*>(var2) != nullptr) {
                     var6.putShort((short)3);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putShort(((BaseVehicle)var2).VehicleID);
                     var6.putByte((byte)var0.vehiclePart.getIndex());
                     var6.putInt(1);
                     var6.putInt(var1.id);
                  } else {
                     var6.putShort((short)2);
                     var6.putInt(((IsoObject)var2).square.getX());
                     var6.putInt(((IsoObject)var2).square.getY());
                     var6.putInt(((IsoObject)var2).square.getZ());
                     var6.putByte((byte)((IsoObject)var2).square.getObjects().indexOf(var2));
                     var6.putByte((byte)var2.getContainerIndex(var0));
                     var6.putInt(1);
                     var6.putInt(var1.id);
                  }

                  PacketType.RemoveInventoryItemFromContainer.send(var5);
               }
            }
         }
      }
   }

    static void receiveRemoveInventoryItemFromContainer(ByteBuffer var0, UdpConnection var1, short var2) {
      alreadyRemoved.clear();
    ByteBufferReader var3 = std::make_shared<ByteBufferReader>(var0);
    short var4 = var3.getShort();
    int var5 = var3.getInt();
    int var6 = var3.getInt();
    int var7 = var3.getInt();
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, var7);
      if (var8 == nullptr) {
         var8 = ServerMap.instance.getGridSquare(var5, var6, var7);
      }

    std::unordered_set var9 = new std::unordered_set();
    bool var10 = false;
    int var11 = 0;
      if (var4 == 0) {
    uint8_t var12 = var3.getByte();
         var11 = var0.getInt();
         if (var8 != nullptr && var12 >= 0 && var12 < var8.getStaticMovingObjects().size()) {
    IsoObject var13 = (IsoObject)var8.getStaticMovingObjects().get(var12);
            if (var13 != nullptr && var13.getContainer() != nullptr) {
               for (int var14 = 0; var14 < var11; var14++) {
    int var15 = var3.getInt();
    InventoryItem var16 = var13.getContainer().getItemWithID(var15);
                  if (var16 == nullptr) {
                     alreadyRemoved.push_back(var15);
                  } else {
                     var13.getContainer().Remove(var16);
                     var10 = true;
                     var9.push_back(var16.getFullType());
                  }
               }

               var13.getContainer().setExplored(true);
               var13.getContainer().setHasBeenLooted(true);
            }
         }
      } else if (var4 == 1) {
         if (var8 != nullptr) {
    int var23 = var3.getInt();
            var11 = var0.getInt();
    ItemContainer var28 = nullptr;

            for (int var33 = 0; var33 < var8.getWorldObjects().size(); var33++) {
    IsoWorldInventoryObject var38 = (IsoWorldInventoryObject)var8.getWorldObjects().get(var33);
               if (var38 != nullptr && var38.getItem() instanceof InventoryContainer && var38.getItem().id == var23) {
                  var28 = ((InventoryContainer)var38.getItem()).getInventory();
                  break;
               }
            }

            if (var28 != nullptr) {
               for (int var34 = 0; var34 < var11; var34++) {
    int var39 = var3.getInt();
    InventoryItem var42 = var28.getItemWithID(var39);
                  if (var42 == nullptr) {
                     alreadyRemoved.push_back(var39);
                  } else {
                     var28.Remove(var42);
                     var9.push_back(var42.getFullType());
                  }
               }

               var28.setExplored(true);
               var28.setHasBeenLooted(true);
            }
         }
      } else if (var4 == 2) {
    uint8_t var24 = var3.getByte();
    uint8_t var29 = var3.getByte();
         var11 = var0.getInt();
         if (var8 != nullptr && var24 >= 0 && var24 < var8.getObjects().size()) {
    IsoObject var35 = (IsoObject)var8.getObjects().get(var24);
    ItemContainer var40 = var35 != nullptr ? var35.getContainerByIndex(var29) : nullptr;
            if (var40 != nullptr) {
               for (int var43 = 0; var43 < var11; var43++) {
    int var17 = var3.getInt();
    InventoryItem var18 = var40.getItemWithID(var17);
                  if (var18 == nullptr) {
                     alreadyRemoved.push_back(var17);
                  } else {
                     var40.Remove(var18);
                     var40.setExplored(true);
                     var40.setHasBeenLooted(true);
                     var10 = true;
                     var9.push_back(var18.getFullType());
                  }
               }

               LuaManager.updateOverlaySprite(var35);
            }
         }
      } else if (var4 == 3) {
    short var25 = var3.getShort();
    uint8_t var30 = var3.getByte();
         var11 = var0.getInt();
    BaseVehicle var36 = VehicleManager.instance.getVehicleByID(var25);
         if (var36 != nullptr) {
    VehiclePart var41 = var36 == nullptr ? nullptr : var36.getPartByIndex(var30);
    ItemContainer var44 = var41 == nullptr ? nullptr : var41.getItemContainer();
            if (var44 != nullptr) {
               for (int var45 = 0; var45 < var11; var45++) {
    int var46 = var3.getInt();
    InventoryItem var19 = var44.getItemWithID(var46);
                  if (var19 == nullptr) {
                     alreadyRemoved.push_back(var46);
                  } else {
                     var44.Remove(var19);
                     var44.setExplored(true);
                     var44.setHasBeenLooted(true);
                     var10 = true;
                     var9.push_back(var19.getFullType());
                  }
               }
            }
         }
      }

      for (int var26 = 0; var26 < udpEngine.connections.size(); var26++) {
    UdpConnection var31 = (UdpConnection)udpEngine.connections.get(var26);
         if (var31.getConnectedGUID() != var1.getConnectedGUID() && var8 != nullptr && var31.RelevantTo(var8.x, var8.y)) {
            var0.rewind();
    ByteBufferWriter var37 = var31.startPacket();
            PacketType.RemoveInventoryItemFromContainer.doPacket(var37);
            var37.bb.put(var0);
            PacketType.RemoveInventoryItemFromContainer.send(var31);
         }
      }

      if (!alreadyRemoved.empty()) {
    ByteBufferWriter var27 = var1.startPacket();
         PacketType.RemoveContestedItemsFromInventory.doPacket(var27);
         var27.putInt(alreadyRemoved.size());

         for (int var32 = 0; var32 < alreadyRemoved.size(); var32++) {
            var27.putInt(alreadyRemoved.get(var32));
         }

         PacketType.RemoveContestedItemsFromInventory.send(var1);
      }

      alreadyRemoved.clear();
      LoggerManager.getLogger("item")
         .write(var1.idStr + " \"" + var1.username + "\" container -" + var11 + " " + var5 + "," + var6 + "," + var7 + " " + var9);
   }

    static void readItemStats(ByteBuffer var0, InventoryItem var1) {
    int var2 = var0.getInt();
    float var3 = var0.getFloat();
    bool var4 = var0.get() == 1;
      var1.setUses(var2);
      if (dynamic_cast<DrainableComboItem*>(var1) != nullptr) {
         ((DrainableComboItem)var1).setDelta(var3);
         ((DrainableComboItem)var1).updateWeight();
      }

      if (var4 && dynamic_cast<Food*>(var1) != nullptr var5) {
         var5.setHungChange(var0.getFloat());
         var5.setCalories(var0.getFloat());
         var5.setCarbohydrates(var0.getFloat());
         var5.setLipids(var0.getFloat());
         var5.setProteins(var0.getFloat());
         var5.setThirstChange(var0.getFloat());
         var5.setFluReduction(var0.getInt());
         var5.setPainReduction(var0.getFloat());
         var5.setEndChange(var0.getFloat());
         var5.setReduceFoodSickness(var0.getInt());
         var5.setStressChange(var0.getFloat());
         var5.setFatigueChange(var0.getFloat());
      }
   }

    static void receiveItemStats(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
      switch (var3) {
         case 0:
    uint8_t var17 = var0.get();
    int var21 = var0.getInt();
            if (var7 != nullptr && var17 >= 0 && var17 < var7.getStaticMovingObjects().size()) {
    IsoMovingObject var25 = (IsoMovingObject)var7.getStaticMovingObjects().get(var17);
    ItemContainer var29 = var25.getContainer();
               if (var29 != nullptr) {
    InventoryItem var32 = var29.getItemWithID(var21);
                  if (var32 != nullptr) {
                     readItemStats(var0, var32);
                  }
               }
            }
            break;
         case 1:
    int var16 = var0.getInt();
            if (var7 != nullptr) {
               for (int var20 = 0; var20 < var7.getWorldObjects().size(); var20++) {
    IsoWorldInventoryObject var24 = (IsoWorldInventoryObject)var7.getWorldObjects().get(var20);
                  if (var24.getItem() != nullptr && var24.getItem().id == var16) {
                     readItemStats(var0, var24.getItem());
                     break;
                  }

                  if (var24.getItem() instanceof InventoryContainer) {
    ItemContainer var28 = ((InventoryContainer)var24.getItem()).getInventory();
    InventoryItem var31 = var28.getItemWithID(var16);
                     if (var31 != nullptr) {
                        readItemStats(var0, var31);
                        break;
                     }
                  }
               }
            }
            break;
         case 2:
    uint8_t var15 = var0.get();
    uint8_t var19 = var0.get();
    int var23 = var0.getInt();
            if (var7 != nullptr && var15 >= 0 && var15 < var7.getObjects().size()) {
    IsoObject var27 = (IsoObject)var7.getObjects().get(var15);
    ItemContainer var30 = var27.getContainerByIndex(var19);
               if (var30 != nullptr) {
    InventoryItem var33 = var30.getItemWithID(var23);
                  if (var33 != nullptr) {
                     readItemStats(var0, var33);
                  }
               }
            }
            break;
         case 3:
    short var8 = var0.getShort();
    uint8_t var9 = var0.get();
    int var10 = var0.getInt();
    BaseVehicle var11 = VehicleManager.instance.getVehicleByID(var8);
            if (var11 != nullptr) {
    VehiclePart var12 = var11.getPartByIndex(var9);
               if (var12 != nullptr) {
    ItemContainer var13 = var12.getItemContainer();
                  if (var13 != nullptr) {
    InventoryItem var14 = var13.getItemWithID(var10);
                     if (var14 != nullptr) {
                        readItemStats(var0, var14);
                     }
                  }
               }
            }
      }

      for (int var18 = 0; var18 < udpEngine.connections.size(); var18++) {
    UdpConnection var22 = (UdpConnection)udpEngine.connections.get(var18);
         if (var22 != var1 && var22.RelevantTo(var4, var5)) {
    ByteBufferWriter var26 = var22.startPacket();
            PacketType.ItemStats.doPacket(var26);
            var0.rewind();
            var26.bb.put(var0);
            PacketType.ItemStats.send(var22);
         }
      }
   }

    static void receiveRequestItemsForContainer(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferReader var3 = std::make_shared<ByteBufferReader>(var0);
    short var4 = var0.getShort();
    std::string var5 = GameWindow.ReadString(var0);
    std::string var6 = GameWindow.ReadString(var0);
    int var7 = var3.getInt();
    int var8 = var3.getInt();
    int var9 = var3.getInt();
    short var10 = var3.getShort();
    uint8_t var11 = -1;
    uint8_t var12 = -1;
    int var13 = 0;
    short var14 = 0;
    IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var7, var8, var9);
    IsoObject var16 = nullptr;
    ItemContainer var17 = nullptr;
      if (var10 == 2) {
         var11 = var3.getByte();
         var12 = var3.getByte();
         if (var15 != nullptr && var11 >= 0 && var11 < var15.getObjects().size()) {
            var16 = (IsoObject)var15.getObjects().get(var11);
            if (var16 != nullptr) {
               var17 = var16.getContainerByIndex(var12);
               if (var17 == nullptr || var17.isExplored()) {
                  return;
               }
            }
         }
      } else if (var10 == 3) {
         var14 = var3.getShort();
         var12 = var3.getByte();
    BaseVehicle var25 = VehicleManager.instance.getVehicleByID(var14);
         if (var25 != nullptr) {
    VehiclePart var18 = var25.getPartByIndex(var12);
            var17 = var18 == nullptr ? nullptr : var18.getItemContainer();
            if (var17 == nullptr || var17.isExplored()) {
               return;
            }
         }
      } else if (var10 == 1) {
         var13 = var3.getInt();

         for (int var27 = 0; var27 < var15.getWorldObjects().size(); var27++) {
    IsoWorldInventoryObject var19 = (IsoWorldInventoryObject)var15.getWorldObjects().get(var27);
            if (var19 != nullptr && var19.getItem() instanceof InventoryContainer && var19.getItem().id == var13) {
               var17 = ((InventoryContainer)var19.getItem()).getInventory();
               break;
            }
         }
      } else if (var10 == 0) {
         var11 = var3.getByte();
         if (var15 != nullptr && var11 >= 0 && var11 < var15.getStaticMovingObjects().size()) {
            var16 = (IsoObject)var15.getStaticMovingObjects().get(var11);
            if (var16 != nullptr && var16.getContainer() != nullptr) {
               if (var16.getContainer().isExplored()) {
                  return;
               }

               var17 = var16.getContainer();
            }
         }
      }

      if (var17 != nullptr && !var17.isExplored()) {
         var17.setExplored(true);
    int var28 = var17.Items.size();
         ItemPickerJava.fillContainer(var17, IDToPlayerMap.get(var4));
         if (var28 != var17.Items.size()) {
            for (int var29 = 0; var29 < udpEngine.connections.size(); var29++) {
    UdpConnection var20 = (UdpConnection)udpEngine.connections.get(var29);
               if (var20.RelevantTo(var15.x, var15.y)) {
    ByteBufferWriter var21 = var20.startPacket();
                  PacketType.AddInventoryItemToContainer.doPacket(var21);
                  var21.putShort(var10);
                  var21.putInt(var7);
                  var21.putInt(var8);
                  var21.putInt(var9);
                  if (var10 == 0) {
                     var21.putByte(var11);
                  } else if (var10 == 1) {
                     var21.putInt(var13);
                  } else if (var10 == 3) {
                     var21.putShort(var14);
                     var21.putByte(var12);
                  } else {
                     var21.putByte(var11);
                     var21.putByte(var12);
                  }

                  try {
                     CompressIdenticalItems.save(var21.bb, var17.getItems(), nullptr);
                  } catch (Exception var23) {
                     var23.printStackTrace();
                  }

                  PacketType.AddInventoryItemToContainer.send(var20);
               }
            }
         }
      }
   }

    static void sendItemsInContainer(IsoObject var0, ItemContainer var1) {
      if (udpEngine != nullptr) {
         if (var1 == nullptr) {
            DebugLog.log("sendItemsInContainer: container is nullptr");
         } else {
            if (dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr var2) {
               if (!(var2.getItem() instanceof InventoryContainer)) {
                  DebugLog.log("sendItemsInContainer: IsoWorldInventoryObject item isn't a container");
                  return;
               }

    InventoryContainer var3 = (InventoryContainer)var2.getItem();
               if (var3.getInventory() != var1) {
                  DebugLog.log("sendItemsInContainer: wrong container for IsoWorldInventoryObject");
                  return;
               }
            } else if (dynamic_cast<BaseVehicle*>(var0) != nullptr) {
               if (var1.vehiclePart == nullptr || var1.vehiclePart.getItemContainer() != var1 || var1.vehiclePart.getVehicle() != var0) {
                  DebugLog.log("sendItemsInContainer: wrong container for BaseVehicle");
                  return;
               }
            } else if (dynamic_cast<IsoDeadBody*>(var0) != nullptr) {
               if (var1 != var0.getContainer()) {
                  DebugLog.log("sendItemsInContainer: wrong container for IsoDeadBody");
                  return;
               }
            } else if (var0.getContainerIndex(var1) == -1) {
               DebugLog.log("sendItemsInContainer: wrong container for IsoObject");
               return;
            }

            if (var0 != nullptr && var1 != nullptr && !var1.getItems().empty()) {
               for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
                  if (var8.RelevantTo(var0.square.x, var0.square.y)) {
    ByteBufferWriter var4 = var8.startPacket();
                     PacketType.AddInventoryItemToContainer.doPacket(var4);
                     if (dynamic_cast<IsoDeadBody*>(var0) != nullptr) {
                        var4.putShort((short)0);
                     } else if (dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr) {
                        var4.putShort((short)1);
                     } else if (dynamic_cast<BaseVehicle*>(var0) != nullptr) {
                        var4.putShort((short)3);
                     } else {
                        var4.putShort((short)2);
                     }

                     var4.putInt(var0.getSquare().getX());
                     var4.putInt(var0.getSquare().getY());
                     var4.putInt(var0.getSquare().getZ());
                     if (dynamic_cast<IsoDeadBody*>(var0) != nullptr) {
                        var4.putByte((byte)var0.getStaticMovingObjectIndex());
                     } else if (dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr) {
                        var4.putInt(((IsoWorldInventoryObject)var0).getItem().id);
                     } else if (dynamic_cast<BaseVehicle*>(var0) != nullptr) {
                        var4.putShort(((BaseVehicle)var0).VehicleID);
                        var4.putByte((byte)var1.vehiclePart.getIndex());
                     } else {
                        var4.putByte((byte)var0.getObjectIndex());
                        var4.putByte((byte)var0.getContainerIndex(var1));
                     }

                     try {
                        CompressIdenticalItems.save(var4.bb, var1.getItems(), nullptr);
                     } catch (Exception var6) {
                        var6.printStackTrace();
                     }

                     PacketType.AddInventoryItemToContainer.send(var8);
                  }
               }
            }
         }
      }
   }

    static void logDupeItem(UdpConnection var0, const std::string& var1) {
    IsoPlayer var2 = nullptr;

      for (int var3 = 0; var3 < Players.size(); var3++) {
         if (var0.username == Players.get(var3).username)) {
            var2 = Players.get(var3);
            break;
         }
      }

    std::string var4 = "";
      if (var2 != nullptr) {
         var4 = LoggerManager.getPlayerCoords(var2);
         LoggerManager.getLogger("user").write("Error: Dupe item ID for " + var2.getDisplayName() + " " + var4);
      }

      ServerWorldDatabase.instance.addUserlog(var0.username, UserlogType.DupeItem, var1, GameServer.class.getSimpleName(), 1);
   }

    static void receiveAddInventoryItemToContainer(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferReader var3 = std::make_shared<ByteBufferReader>(var0);
    short var4 = var3.getShort();
    int var5 = var3.getInt();
    int var6 = var3.getInt();
    int var7 = var3.getInt();
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, var7);
    std::unordered_set var9 = new std::unordered_set();
    uint8_t var10 = 0;
      if (var8 == nullptr) {
         DebugLog.log("ERROR sendItemsToContainer square is nullptr");
      } else {
    ItemContainer var11 = nullptr;
    IsoObject var12 = nullptr;
         if (var4 == 0) {
    uint8_t var13 = var3.getByte();
            if (var13 < 0 || var13 >= var8.getStaticMovingObjects().size()) {
               DebugLog.log("ERROR sendItemsToContainer invalid corpse index");
               return;
            }

    IsoObject var14 = (IsoObject)var8.getStaticMovingObjects().get(var13);
            if (var14 != nullptr && var14.getContainer() != nullptr) {
               var11 = var14.getContainer();
            }
         } else if (var4 == 1) {
    int var20 = var3.getInt();

            for (int var25 = 0; var25 < var8.getWorldObjects().size(); var25++) {
    IsoWorldInventoryObject var15 = (IsoWorldInventoryObject)var8.getWorldObjects().get(var25);
               if (var15 != nullptr && var15.getItem() instanceof InventoryContainer && var15.getItem().id == var20) {
                  var11 = ((InventoryContainer)var15.getItem()).getInventory();
                  break;
               }
            }

            if (var11 == nullptr) {
               DebugLog.log("ERROR sendItemsToContainer can't find world item with id=" + var20);
               return;
            }
         } else if (var4 == 2) {
    uint8_t var21 = var3.getByte();
    uint8_t var26 = var3.getByte();
            if (var21 < 0 || var21 >= var8.getObjects().size()) {
               DebugLog.log("ERROR sendItemsToContainer invalid object index");

               for (int var29 = 0; var29 < var8.getObjects().size(); var29++) {
                  if (((IsoObject)var8.getObjects().get(var29)).getContainer() != nullptr) {
                     var21 = (byte)var29;
                     var26 = 0;
                     break;
                  }
               }

               if (var21 == -1) {
                  return;
               }
            }

            var12 = (IsoObject)var8.getObjects().get(var21);
            var11 = var12 != nullptr ? var12.getContainerByIndex(var26) : nullptr;
         } else if (var4 == 3) {
    short var22 = var3.getShort();
    uint8_t var27 = var3.getByte();
    BaseVehicle var30 = VehicleManager.instance.getVehicleByID(var22);
            if (var30 == nullptr) {
               DebugLog.log("ERROR sendItemsToContainer invalid vehicle id");
               return;
            }

    VehiclePart var16 = var30.getPartByIndex(var27);
            var11 = var16 == nullptr ? nullptr : var16.getItemContainer();
         }

         if (var11 != nullptr) {
            try {
    std::vector var23 = CompressIdenticalItems.load(var3.bb, 195, nullptr, nullptr);

               for (int var28 = 0; var28 < var23.size(); var28++) {
    InventoryItem var31 = (InventoryItem)var23.get(var28);
                  if (var31 != nullptr) {
                     if (var11.containsID(var31.id)) {
                        System.out.println("Error: Dupe item ID for " + var1.username);
                        logDupeItem(var1, var31.getDisplayName());
                     } else {
                        var11.addItem(var31);
                        var11.setExplored(true);
                        var9.push_back(var31.getFullType());
                        if (dynamic_cast<IsoMannequin*>(var12) != nullptr) {
                           ((IsoMannequin)var12).wearItem(var31, nullptr);
                        }
                     }
                  }
               }
            } catch (Exception var17) {
               var17.printStackTrace();
            }

            if (var12 != nullptr) {
               LuaManager.updateOverlaySprite(var12);
               if ("campfire" == var11.getType())) {
                  var12.sendObjectChange("container.customTemperature");
               }
            }
         }
      }

      for (int var18 = 0; var18 < udpEngine.connections.size(); var18++) {
    UdpConnection var19 = (UdpConnection)udpEngine.connections.get(var18);
         if (var19.getConnectedGUID() != var1.getConnectedGUID() && var19.RelevantTo(var8.x, var8.y)) {
            var0.rewind();
    ByteBufferWriter var24 = var19.startPacket();
            PacketType.AddInventoryItemToContainer.doPacket(var24);
            var24.bb.put(var0);
            PacketType.AddInventoryItemToContainer.send(var19);
         }
      }

      LoggerManager.getLogger("item")
         .write(var1.idStr + " \"" + var1.username + "\" container +" + var10 + " " + var5 + "," + var6 + "," + var7 + " " + var9);
   }

    static void addConnection(UdpConnection var0) {
      /* synchronized - TODO: add std::mutex */ (MainLoopNetDataHighPriorityQ) {
         MainLoopNetDataHighPriorityQ.push_back(std::make_shared<DelayedConnection>(var0, true));
      }
   }

    static void addDisconnect(UdpConnection var0) {
      /* synchronized - TODO: add std::mutex */ (MainLoopNetDataHighPriorityQ) {
         MainLoopNetDataHighPriorityQ.push_back(std::make_shared<DelayedConnection>(var0, false));
      }
   }

    static void disconnectPlayer(IsoPlayer var0, UdpConnection var1) {
      if (var0 != nullptr) {
         SafetySystemManager.storeSafety(var0);
         ChatServer.getInstance().disconnectPlayer(var0.getOnlineID());
         if (var0.getVehicle() != nullptr) {
            VehiclesDB2.instance.updateVehicleAndTrailer(var0.getVehicle());
            if (var0.getVehicle().isDriver(var0) && var0.getVehicle().isNetPlayerId(var0.getOnlineID())) {
               var0.getVehicle().setNetPlayerAuthorization(Authorization.Server, -1);
               var0.getVehicle().getController().clientForce = 0.0F;
               var0.getVehicle().jniLinearVelocity.set(0.0F, 0.0F, 0.0F);
            }

    int var2 = var0.getVehicle().getSeat(var0);
            if (var2 != -1) {
               var0.getVehicle().clearPassenger(var2);
            }
         }

         if (!var0.isDead()) {
            ServerWorldDatabase.instance.saveTransactionID(var0.username, var0.getTransactionID());
         }

         NetworkZombieManager.getInstance().clearTargetAuth(var1, var0);
         var0.removeFromWorld();
         var0.removeFromSquare();
         PlayerToAddressMap.remove(var0);
         IDToAddressMap.remove(var0.OnlineID);
         IDToPlayerMap.remove(var0.OnlineID);
         Players.remove(var0);
         SafeHouse.updateSafehousePlayersConnected();
    SafeHouse var6 = SafeHouse.hasSafehouse(var0);
         if (var6 != nullptr && var6.isOwner(var0)) {
            for (IsoPlayer var4 : IDToPlayerMap.values()) {
               var6.checkTrespass(var4);
            }
         }

         var1.usernames[var0.PlayerIndex] = nullptr;
         var1.players[var0.PlayerIndex] = nullptr;
         var1.playerIDs[var0.PlayerIndex] = -1;
         var1.ReleventPos[var0.PlayerIndex] = nullptr;
         var1.connectArea[var0.PlayerIndex] = nullptr;

         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
    ByteBufferWriter var5 = var8.startPacket();
            PacketType.PlayerTimeout.doPacket(var5);
            var5.putShort(var0.OnlineID);
            PacketType.PlayerTimeout.send(var8);
         }

         ServerLOS.instance.removePlayer(var0);
         ZombiePopulationManager.instance.updateLoadedAreas();
         DebugLog.log(DebugType.Network, "Disconnected player \"" + var0.getDisplayName() + "\" " + var1.idStr);
         LoggerManager.getLogger("user").write(var1.idStr + " \"" + var0.getUsername() + "\" disconnected player " + LoggerManager.getPlayerCoords(var0));
      }
   }

    static void heartBeat() {
      count++;
   }

    static short getFreeSlot() {
      for (short var0 = 0; var0 < udpEngine.getMaxConnections(); var0++) {
         if (SlotToConnection[var0] == nullptr) {
    return var0;
         }
      }

      return -1;
   }

    static void receiveClientConnect(UdpConnection var0, LogonResult var1) {
      ConnectionManager.log("receive-packet", "client-connect", var0);
    short var2 = getFreeSlot();
    short var3 = (short)(var2 * 4);
      if (var0.playerDownloadServer != nullptr) {
         try {
            IDToAddressMap.put(var3, var0.getConnectedGUID());
            var0.playerDownloadServer.destroy();
         } catch (Exception var9) {
            var9.printStackTrace();
         }
      }

      playerToCoordsMap.put(var3, std::make_unique<Vector2>());
      playerMovedToFastMap.put(var3, 0);
      SlotToConnection[var2] = var0;
      var0.playerIDs[0] = var3;
      IDToAddressMap.put(var3, var0.getConnectedGUID());
      var0.playerDownloadServer = std::make_shared<PlayerDownloadServer>(var0);
      DebugLog.log(DebugType.Network, "Connected new client " + var0.username + " ID # " + var3);
      var0.playerDownloadServer.startConnectionTest();
    KahluaTable var4 = SpawnPoints.instance.getSpawnRegions();

      for (int var5 = 1; var5 < var4.size() + 1; var5++) {
    ByteBufferWriter var6 = var0.startPacket();
         PacketType.SpawnRegion.doPacket(var6);
         var6.putInt(var5);

         try {
            ((KahluaTable)var4.rawget(var5)).save(var6.bb);
            PacketType.SpawnRegion.send(var0);
         } catch (IOException var8) {
            var8.printStackTrace();
         }
      }

    RequestDataPacket var10 = std::make_shared<RequestDataPacket>();
      var10.sendConnectingDetails(var0, var1);
   }

    static void receiveReplaceOnCooked(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferReader var3 = std::make_shared<ByteBufferReader>(var0);
    int var4 = var3.getInt();
    int var5 = var3.getInt();
    int var6 = var3.getInt();
    uint8_t var7 = var3.getByte();
    uint8_t var8 = var3.getByte();
    int var9 = var3.getInt();
    IsoGridSquare var10 = ServerMap.instance.getGridSquare(var4, var5, var6);
      if (var10 != nullptr) {
         if (var7 >= 0 && var7 < var10.getObjects().size()) {
    IsoObject var11 = (IsoObject)var10.getObjects().get(var7);
            if (var11 != nullptr) {
    ItemContainer var12 = var11.getContainerByIndex(var8);
               if (var12 != nullptr) {
    InventoryItem var13 = var12.getItemWithID(var9);
                  if (var13 != nullptr) {
    Food var14 = (Food)Type.tryCastTo(var13, Food.class);
                     if (var14 != nullptr) {
                        if (var14.getReplaceOnCooked() != nullptr && !var14.isRotten()) {
                           for (int var15 = 0; var15 < var14.getReplaceOnCooked().size(); var15++) {
    InventoryItem var16 = var12.AddItem((std::string)var14.getReplaceOnCooked().get(var15));
                              if (var16 != nullptr) {
                                 var16.copyConditionModData(var14);
                                 if (dynamic_cast<Food*>(var16) != nullptr && dynamic_cast<Food*>(var14) != nullptr) {
                                 }

                                 if (dynamic_cast<Food*>(var16) != nullptr && ((Food)var16).isBadInMicrowave() && var12.isMicrowave()) {
                                    var16.setUnhappyChange(5.0F);
                                    var16.setBoredomChange(5.0F);
                                    ((Food)var16).setCookedInMicrowave(true);
                                 }

                                 sendAddItemToContainer(var12, var16);
                              }
                           }

                           sendRemoveItemFromContainer(var12, var14);
                           var12.Remove(var14);
                           IsoWorld.instance.CurrentCell.addToProcessItemsRemove(var14);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void receivePlayerDataRequest(ByteBuffer var0, UdpConnection var1, short var2) {
    PlayerDataRequestPacket var3 = std::make_shared<PlayerDataRequestPacket>();
      var3.parse(var0, var1);
      if (var3.isConsistent()) {
         var3.process(var1);
      }
   }

    static void receiveRequestData(ByteBuffer var0, UdpConnection var1, short var2) {
    RequestDataPacket var3 = std::make_shared<RequestDataPacket>();
      var3.parse(var0, var1);
      var3.processServer(PacketType.RequestData, var1);
   }

    static void sendMetaGrid(int var0, int var1, int var2, UdpConnection var3) {
    IsoMetaGrid var4 = IsoWorld.instance.MetaGrid;
      if (var0 >= var4.getMinX() && var0 <= var4.getMaxX() && var1 >= var4.getMinY() && var1 <= var4.getMaxY()) {
    IsoMetaCell var5 = var4.getCellData(var0, var1);
         if (var5.info != nullptr && var2 >= 0 && var2 < var5.info.RoomList.size()) {
    ByteBufferWriter var6 = var3.startPacket();
            PacketType.MetaGrid.doPacket(var6);
            var6.putShort((short)var0);
            var6.putShort((short)var1);
            var6.putShort((short)var2);
            var6.putBoolean(var5.info.getRoom(var2).def.bLightsActive);
            PacketType.MetaGrid.send(var3);
         }
      }
   }

    static void sendMetaGrid(int var0, int var1, int var2) {
      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         sendMetaGrid(var0, var1, var2, var4);
      }
   }

    static void preventIndoorZombies(int var0, int var1, int var2) {
    RoomDef var3 = IsoWorld.instance.MetaGrid.getRoomAt(var0, var1, var2);
      if (var3 != nullptr) {
    bool var4 = isSpawnBuilding(var3.getBuilding());
         var3.getBuilding().setAllExplored(true);
         var3.getBuilding().setAlarmed(false);
    std::vector var5 = IsoWorld.instance.CurrentCell.getZombieList();

         for (int var6 = 0; var6 < var5.size(); var6++) {
    IsoZombie var7 = (IsoZombie)var5.get(var6);
            if ((var4 || var7.bIndoorZombie)
               && var7.getSquare() != nullptr
               && var7.getSquare().getRoom() != nullptr
               && var7.getSquare().getRoom().def.building == var3.getBuilding()) {
               VirtualZombieManager.instance.removeZombieFromWorld(var7);
               if (var6 >= var5.size() || var5.get(var6) != var7) {
                  var6--;
               }
            }
         }
      }
   }

    static void receivePlayerConnect(ByteBuffer var0, UdpConnection var1, const std::string& var2) {
      ConnectionManager.log("receive-packet", "player-connect", var1);
      DebugLog.General.println("User:'" + var2 + "' ip:" + var1.ip + " is trying to connect");
    uint8_t var3 = var0.get();
      if (var3 >= 0 && var3 < 4 && var1.players[var3] == nullptr) {
    uint8_t var4 = (byte)Math.min(20, var0.get());
         var1.ReleventRange = (byte)(var4 / 2 + 2);
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
         var1.ReleventPos[var3].x = var5;
         var1.ReleventPos[var3].y = var6;
         var1.ReleventPos[var3].z = var7;
         var1.connectArea[var3] = nullptr;
         var1.ChunkGridWidth = var4;
         var1.loadedCells[var3] = std::make_shared<ClientServerMap>(var3, (int)var5, (int)var6, var4);
    SurvivorDesc var8 = SurvivorFactory.CreateSurvivor();

         try {
            var8.load(var0, 195, nullptr);
         } catch (IOException var23) {
            var23.printStackTrace();
         }

    IsoPlayer var9 = std::make_shared<IsoPlayer>(nullptr, var8, (int)var5, (int)var6, (int)var7);
         var9.realx = var5;
         var9.realy = var6;
         var9.realz = (byte)var7;
         var9.PlayerIndex = var3;
         var9.OnlineChunkGridWidth = var4;
         Players.push_back(var9);
         var9.bRemote = true;

         try {
            var9.getHumanVisual().load(var0, 195);
            var9.getItemVisuals().load(var0, 195);
         } catch (IOException var22) {
            var22.printStackTrace();
         }

    short var10 = var1.playerIDs[var3];
         IDToPlayerMap.put(var10, var9);
         var1.players[var3] = var9;
         PlayerToAddressMap.put(var9, var1.getConnectedGUID());
         var9.setOnlineID(var10);

         try {
            var9.getXp().load(var0, 195);
         } catch (IOException var21) {
            var21.printStackTrace();
         }

         var9.setAllChatMuted(var0.get() == 1);
         var1.allChatMuted = var9.isAllChatMuted();
         var9.setTagPrefix(GameWindow.ReadString(var0));
         var9.setTagColor(std::make_shared<ColorInfo>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
         var9.setTransactionID(var0.getInt());
         var9.setHoursSurvived(var0.getDouble());
         var9.setZombieKills(var0.getInt());
         var9.setDisplayName(GameWindow.ReadString(var0));
         var9.setSpeakColour(std::make_shared<Color>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
         var9.showTag = var0.get() == 1;
         var9.factionPvp = var0.get() == 1;
         if (SteamUtils.isSteamModeEnabled()) {
            var9.setSteamID(var1.steamID);
    std::string var11 = GameWindow.ReadStringUTF(var0);
            SteamGameServer.BUpdateUserData(var1.steamID, var1.username, 0);
         }

    uint8_t var25 = var0.get();
    void* var12 = nullptr;
         if (var25 == 1) {
            try {
               var12 = InventoryItem.loadItem(var0, 195);
            } catch (IOException var20) {
               var20.printStackTrace();
               return;
            }

            if (var12 == nullptr) {
               LoggerManager.getLogger("user").write(var1.idStr + " equipped unknown item");
               return;
            }

            var9.setPrimaryHandItem((InventoryItem)var12);
         }

         var12 = nullptr;
    uint8_t var13 = var0.get();
         if (var13 == 2) {
            var9.setSecondaryHandItem(var9.getPrimaryHandItem());
         }

         if (var13 == 1) {
            try {
               var12 = InventoryItem.loadItem(var0, 195);
            } catch (IOException var19) {
               var19.printStackTrace();
               return;
            }

            if (var12 == nullptr) {
               LoggerManager.getLogger("user").write(var1.idStr + " equipped unknown item");
               return;
            }

            var9.setSecondaryHandItem((InventoryItem)var12);
         }

    int var14 = var0.getInt();

         for (int var15 = 0; var15 < var14; var15++) {
    std::string var16 = GameWindow.ReadString(var0);
    InventoryItem var17 = InventoryItemFactory.CreateItem(GameWindow.ReadString(var0));
            if (var17 != nullptr) {
               var9.setAttachedItem(var16, var17);
            }
         }

    int var29 = var0.getInt();
         var9.remoteSneakLvl = var29;
         var9.username = var2;
         var9.accessLevel = PlayerType.toString(var1.accessLevel);
         if (!var9.accessLevel == "") && CoopSlave.instance == nullptr) {
            var9.setGhostMode(true);
            var9.setInvisible(true);
            var9.setGodMod(true);
         }

         ChatServer.getInstance().initPlayer(var9.OnlineID);
         var1.setFullyConnected();
         sendWeather(var1);
         SafetySystemManager.restoreSafety(var9);

         for (int var30 = 0; var30 < udpEngine.connections.size(); var30++) {
    UdpConnection var32 = (UdpConnection)udpEngine.connections.get(var30);
            sendPlayerConnect(var9, var32);
         }

    SyncInjuriesPacket var31 = std::make_shared<SyncInjuriesPacket>();

         for (IsoPlayer var18 : IDToPlayerMap.values()) {
            if (var18.getOnlineID() != var9.getOnlineID() && var18.isAlive()) {
               sendPlayerConnect(var18, var1);
               var31.set(var18);
               sendPlayerInjuries(var1, var31);
            }
         }

         var1.loadedCells[var3].setLoaded();
         var1.loadedCells[var3].sendPacket(var1);
         preventIndoorZombies((int)var5, (int)var6, (int)var7);
         ServerLOS.instance.addPlayer(var9);
         LoggerManager.getLogger("user").write(var1.idStr + " \"" + var9.username + "\" fully connected " + LoggerManager.getPlayerCoords(var9));

         try {
            for (NonPvpZone var35 : NonPvpZone.getAllZones()) {
               sendNonPvpZone(var35, false, var1);
            }
         } catch (Exception var24) {
            DebugLog.Multiplayer.printException(var24, "Send non PVP zones", LogSeverity.Error);
         }
      }
   }

    static void receivePlayerSave(ByteBuffer var0, UdpConnection var1, short var2) {
      if ((Calendar.getInstance().getTimeInMillis() - previousSave) / 60000L >= 0L) {
    uint8_t var3 = var0.get();
         if (var3 >= 0 && var3 < 4) {
    short var4 = var0.getShort();
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
            ServerMap.instance.saveZoneInsidePlayerInfluence(var4);
         }
      }
   }

    static void receiveSendPlayerProfile(ByteBuffer var0, UdpConnection var1, short var2) {
      ServerPlayerDB.getInstance().serverUpdateNetworkCharacter(var0, var1);
   }

    static void receiveLoadPlayerProfile(ByteBuffer var0, UdpConnection var1, short var2) {
      ServerPlayerDB.getInstance().serverLoadNetworkCharacter(var0, var1);
   }

    static void coopAccessGranted(int var0, UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.AddCoopPlayer.doPacket(var2);
      var2.putBoolean(true);
      var2.putByte((byte)var0);
      PacketType.AddCoopPlayer.send(var1);
   }

    static void coopAccessDenied(const std::string& var0, int var1, UdpConnection var2) {
    ByteBufferWriter var3 = var2.startPacket();
      PacketType.AddCoopPlayer.doPacket(var3);
      var3.putBoolean(false);
      var3.putByte((byte)var1);
      var3.putUTF(var0);
      PacketType.AddCoopPlayer.send(var2);
   }

    static void receiveAddCoopPlayer(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    uint8_t var4 = var0.get();
      if (!ServerOptions.instance.AllowCoop.getValue() && var4 != 0) {
         coopAccessDenied("Coop players not allowed", var4, var1);
      } else if (var4 >= 0 && var4 < 4) {
         if (var1.players[var4] != nullptr && !var1.players[var4].isDead()) {
            coopAccessDenied("Coop player " + (var4 + 1) + "/4 already exists", var4, var1);
         } else if (var3 != 1) {
            if (var3 == 2) {
    std::string var10 = var1.usernames[var4];
               if (var10 == nullptr) {
                  coopAccessDenied("Coop player login wasn't received", var4, var1);
               } else {
                  DebugLog.log("coop player=" + (var4 + 1) + "/4 username=\"" + var10 + "\" player info received");
                  receivePlayerConnect(var0, var1, var10);
               }
            }
         } else {
    std::string var5 = GameWindow.ReadStringUTF(var0);
            if (var5.empty()) {
               coopAccessDenied("No username given", var4, var1);
            } else {
               for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);

                  for (int var8 = 0; var8 < 4; var8++) {
                     if ((var7 != var1 || var4 != var8) && var5 == var7.usernames[var8])) {
                        coopAccessDenied("User \"" + var5 + "\" already connected", var4, var1);
                        return;
                     }
                  }
               }

               DebugLog.log("coop player=" + (var4 + 1) + "/4 username=\"" + var5 + "\" is joining");
               if (var1.players[var4] != nullptr) {
                  DebugLog.log("coop player=" + (var4 + 1) + "/4 username=\"" + var5 + "\" is replacing dead player");
    short var12 = var1.players[var4].OnlineID;
                  disconnectPlayer(var1.players[var4], var1);
    float var15 = var0.getFloat();
    float var17 = var0.getFloat();
                  var1.usernames[var4] = var5;
                  var1.ReleventPos[var4] = std::make_shared<Vector3>(var15, var17, 0.0F);
                  var1.connectArea[var4] = std::make_shared<Vector3>(var15 / 10.0F, var17 / 10.0F, var1.ChunkGridWidth);
                  var1.playerIDs[var4] = var12;
                  IDToAddressMap.put(var12, var1.getConnectedGUID());
                  coopAccessGranted(var4, var1);
                  ZombiePopulationManager.instance.updateLoadedAreas();
                  if (ChatServer.isInited()) {
                     ChatServer.getInstance().initPlayer(var12);
                  }
               } else if (getPlayerCount() >= ServerOptions.getInstance().getMaxPlayers()) {
                  coopAccessDenied("Server is full", var4, var1);
               } else {
    short var11 = -1;

                  for (short var13 = 0; var13 < udpEngine.getMaxConnections(); var13++) {
                     if (SlotToConnection[var13] == var1) {
                        var11 = var13;
                        break;
                     }
                  }

    short var14 = (short)(var11 * 4 + var4);
                  DebugLog.log("coop player=" + (var4 + 1) + "/4 username=\"" + var5 + "\" assigned id=" + var14);
    float var16 = var0.getFloat();
    float var9 = var0.getFloat();
                  var1.usernames[var4] = var5;
                  var1.ReleventPos[var4] = std::make_shared<Vector3>(var16, var9, 0.0F);
                  var1.playerIDs[var4] = var14;
                  var1.connectArea[var4] = std::make_shared<Vector3>(var16 / 10.0F, var9 / 10.0F, var1.ChunkGridWidth);
                  IDToAddressMap.put(var14, var1.getConnectedGUID());
                  coopAccessGranted(var4, var1);
                  ZombiePopulationManager.instance.updateLoadedAreas();
               }
            }
         }
      } else {
         coopAccessDenied("Invalid coop player index", var4, var1);
      }
   }

    static void sendInitialWorldState(UdpConnection var0) {
      if (RainManager.isRaining()) {
         sendStartRain(var0);
      }

      VehicleManager.instance.serverSendInitialWorldState(var0);

      try {
         if (!ClimateManager.getInstance().isUpdated()) {
            ClimateManager.getInstance().update();
         }

         ClimateManager.getInstance().sendInitialState(var0);
      } catch (Exception var2) {
         var2.printStackTrace();
      }
   }

    static void receiveObjectModData(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    bool var7 = var0.get() == 1;
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var8 != nullptr && var6 >= 0 && var6 < var8.getObjects().size()) {
    IsoObject var9 = (IsoObject)var8.getObjects().get(var6);
         if (var7) {
    int var10 = var9.getWaterAmount();

            try {
               var9.getModData().load(var0, 195);
            } catch (IOException var12) {
               var12.printStackTrace();
            }

            if (var10 != var9.getWaterAmount()) {
               LuaEventManager.triggerEvent("OnWaterAmountChange", var9, var10);
            }
         } else if (var9.hasModData()) {
            var9.getModData().wipe();
         }

         for (int var13 = 0; var13 < udpEngine.connections.size(); var13++) {
    UdpConnection var11 = (UdpConnection)udpEngine.connections.get(var13);
            if (var11.getConnectedGUID() != var1.getConnectedGUID() && var11.RelevantTo(var3, var4)) {
               sendObjectModData(var9, var11);
            }
         }
      } else if (var8 != nullptr) {
         DebugLog.log("receiveObjectModData: index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
      } else if (bDebug) {
         DebugLog.log("receiveObjectModData: sq is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
      }
   }

    static void sendObjectModData(IsoObject var0, UdpConnection var1) {
      if (var0.getSquare() != nullptr) {
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.ObjectModData.doPacket(var2);
         var2.putInt(var0.getSquare().getX());
         var2.putInt(var0.getSquare().getY());
         var2.putInt(var0.getSquare().getZ());
         var2.putInt(var0.getSquare().getObjects().indexOf(var0));
         if (var0.getModData().empty()) {
            var2.putByte((byte)0);
         } else {
            var2.putByte((byte)1);

            try {
               var0.getModData().save(var2.bb);
            } catch (IOException var4) {
               var4.printStackTrace();
            }
         }

         PacketType.ObjectModData.send(var1);
      }
   }

    static void sendObjectModData(IsoObject var0) {
      if (!bSoftReset && !bFastForward) {
         for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
            if (var2.RelevantTo(var0.getX(), var0.getY())) {
               sendObjectModData(var0, var2);
            }
         }
      }
   }

    static void sendSlowFactor(IsoGameCharacter var0) {
      if (dynamic_cast<IsoPlayer*>(var0) != nullptr) {
         if (PlayerToAddressMap.containsKey(var0)) {
    long var1 = PlayerToAddressMap.get((IsoPlayer)var0);
    UdpConnection var3 = udpEngine.getActiveConnection(var1);
            if (var3 != nullptr) {
    ByteBufferWriter var4 = var3.startPacket();
               PacketType.SlowFactor.doPacket(var4);
               var4.putByte((byte)((IsoPlayer)var0).PlayerIndex);
               var4.putFloat(var0.getSlowTimer());
               var4.putFloat(var0.getSlowFactor());
               PacketType.SlowFactor.send(var3);
            }
         }
      }
   }

    static void sendObjectChange(IsoObject var0, const std::string& var1, KahluaTable var2, UdpConnection var3) {
      if (var0.getSquare() != nullptr) {
    ByteBufferWriter var4 = var3.startPacket();
         PacketType.ObjectChange.doPacket(var4);
         if (dynamic_cast<IsoPlayer*>(var0) != nullptr) {
            var4.putByte((byte)1);
            var4.putShort(((IsoPlayer)var0).OnlineID);
         } else if (dynamic_cast<BaseVehicle*>(var0) != nullptr) {
            var4.putByte((byte)2);
            var4.putShort(((BaseVehicle)var0).getId());
         } else if (dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr) {
            var4.putByte((byte)3);
            var4.putInt(var0.getSquare().getX());
            var4.putInt(var0.getSquare().getY());
            var4.putInt(var0.getSquare().getZ());
            var4.putInt(((IsoWorldInventoryObject)var0).getItem().getID());
         } else if (dynamic_cast<IsoDeadBody*>(var0) != nullptr) {
            var4.putByte((byte)4);
            var4.putInt(var0.getSquare().getX());
            var4.putInt(var0.getSquare().getY());
            var4.putInt(var0.getSquare().getZ());
            var4.putInt(var0.getStaticMovingObjectIndex());
         } else {
            var4.putByte((byte)0);
            var4.putInt(var0.getSquare().getX());
            var4.putInt(var0.getSquare().getY());
            var4.putInt(var0.getSquare().getZ());
            var4.putInt(var0.getSquare().getObjects().indexOf(var0));
         }

         var4.putUTF(var1);
         var0.saveChange(var1, var2, var4.bb);
         PacketType.ObjectChange.send(var3);
      }
   }

    static void sendObjectChange(IsoObject var0, const std::string& var1, KahluaTable var2) {
      if (!bSoftReset) {
         if (var0 != nullptr) {
            for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
               if (var4.RelevantTo(var0.getX(), var0.getY())) {
                  sendObjectChange(var0, var1, var2, var4);
               }
            }
         }
      }
   }

    static void sendObjectChange(IsoObject var0, const std::string& var1, Object... var2) {
      if (!bSoftReset) {
         if (var2.length == 0) {
            sendObjectChange(var0, var1, (KahluaTable)nullptr);
         } else if (var2.length % 2 == 0) {
    KahluaTable var3 = LuaManager.platform.newTable();

            for (byte var4 = 0; var4 < var2.length; var4 += 2) {
    void* var5 = var2[var4 + 1];
               if (dynamic_cast<float*>(var5) != nullptr) {
                  var3.rawset(var2[var4], ((float)var5).doubleValue());
               } else if (dynamic_cast<int*>(var5) != nullptr) {
                  var3.rawset(var2[var4], ((int)var5).doubleValue());
               } else if (dynamic_cast<int16_t*>(var5) != nullptr) {
                  var3.rawset(var2[var4], ((int16_t)var5).doubleValue());
               } else {
                  var3.rawset(var2[var4], var5);
               }
            }

            sendObjectChange(var0, var1, var3);
         }
      }
   }

    static void updateHandEquips(UdpConnection var0, IsoPlayer var1) {
    ByteBufferWriter var2 = var0.startPacket();
      PacketType.Equip.doPacket(var2);
      var2.putShort(var1.OnlineID);
      var2.putByte((byte)0);
      var2.putByte((byte)(var1.getPrimaryHandItem() != nullptr ? 1 : 0));
      if (var1.getPrimaryHandItem() != nullptr) {
         try {
            var1.getPrimaryHandItem().saveWithSize(var2.bb, false);
            if (var1.getPrimaryHandItem().getVisual() != nullptr) {
               var2.bb.put((byte)1);
               var1.getPrimaryHandItem().getVisual().save(var2.bb);
            } else {
               var2.bb.put((byte)0);
            }
         } catch (IOException var5) {
            var5.printStackTrace();
         }
      }

      PacketType.Equip.send(var0);
      var2 = var0.startPacket();
      PacketType.Equip.doPacket(var2);
      var2.putShort(var1.OnlineID);
      var2.putByte((byte)1);
      if (var1.getSecondaryHandItem() == var1.getPrimaryHandItem() && var1.getSecondaryHandItem() != nullptr) {
         var2.putByte((byte)2);
      } else {
         var2.putByte((byte)(var1.getSecondaryHandItem() != nullptr ? 1 : 0));
      }

      if (var1.getSecondaryHandItem() != nullptr) {
         try {
            var1.getSecondaryHandItem().saveWithSize(var2.bb, false);
            if (var1.getSecondaryHandItem().getVisual() != nullptr) {
               var2.bb.put((byte)1);
               var1.getSecondaryHandItem().getVisual().save(var2.bb);
            } else {
               var2.bb.put((byte)0);
            }
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }

      PacketType.Equip.send(var0);
   }

    static void receiveSyncCustomLightSettings(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    uint8_t var6 = var0.get();
    IsoGridSquare var7 = ServerMap.instance.getGridSquare(var3, var4, var5);
      if (var7 != nullptr && var6 >= 0 && var6 < var7.getObjects().size()) {
         if (var7.getObjects().get(var6) instanceof IsoLightSwitch) {
            ((IsoLightSwitch)var7.getObjects().get(var6)).receiveSyncCustomizedSettings(var0, var1);
         } else {
            DebugLog.log("Sync Lightswitch custom settings: found object not a instance of IsoLightSwitch, x,y,z=" + var3 + "," + var4 + "," + var5);
         }
      } else if (var7 != nullptr) {
         DebugLog.log("Sync Lightswitch custom settings: index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
      } else {
         DebugLog.log("Sync Lightswitch custom settings: sq is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
      }
   }

    static void sendAlarmClock_Player(short var0, int var1, bool var2, int var3, int var4, bool var5, UdpConnection var6) {
    ByteBufferWriter var7 = var6.startPacket();
      PacketType.SyncAlarmClock.doPacket(var7);
      var7.putShort(AlarmClock.PacketPlayer);
      var7.putShort(var0);
      var7.putInt(var1);
      var7.putByte((byte)(var2 ? 1 : 0));
      if (!var2) {
         var7.putInt(var3);
         var7.putInt(var4);
         var7.putByte((byte)(var5 ? 1 : 0));
      }

      PacketType.SyncAlarmClock.send(var6);
   }

    static void sendAlarmClock_World(int var0, int var1, int var2, int var3, bool var4, int var5, int var6, bool var7, UdpConnection var8) {
    ByteBufferWriter var9 = var8.startPacket();
      PacketType.SyncAlarmClock.doPacket(var9);
      var9.putShort(AlarmClock.PacketWorld);
      var9.putInt(var0);
      var9.putInt(var1);
      var9.putInt(var2);
      var9.putInt(var3);
      var9.putByte((byte)(var4 ? 1 : 0));
      if (!var4) {
         var9.putInt(var5);
         var9.putInt(var6);
         var9.putByte((byte)(var7 ? 1 : 0));
      }

      PacketType.SyncAlarmClock.send(var8);
   }

    static void receiveSyncAlarmClock(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
      if (var3 == AlarmClock.PacketPlayer) {
    short var16 = var0.getShort();
    int var17 = var0.getInt();
    bool var18 = var0.get() == 1;
    int var19 = 0;
    int var20 = 0;
    bool var21 = false;
         if (!var18) {
            var19 = var0.getInt();
            var20 = var0.getInt();
            var21 = var0.get() == 1;
         }

    IsoPlayer var22 = getPlayerFromConnection(var1, var16);
         if (var22 != nullptr) {
            for (int var23 = 0; var23 < udpEngine.connections.size(); var23++) {
    UdpConnection var24 = (UdpConnection)udpEngine.connections.get(var23);
               if (var24 != var1) {
                  sendAlarmClock_Player(var22.getOnlineID(), var17, var18, var19, var20, var21, var24);
               }
            }
         }
      } else if (var3 == AlarmClock.PacketWorld) {
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    bool var8 = var0.get() == 1;
    int var9 = 0;
    int var10 = 0;
    bool var11 = false;
         if (!var8) {
            var9 = var0.getInt();
            var10 = var0.getInt();
            var11 = var0.get() == 1;
         }

    IsoGridSquare var12 = ServerMap.instance.getGridSquare(var4, var5, var6);
         if (var12 == nullptr) {
            DebugLog.log("SyncAlarmClock: sq is nullptr x,y,z=" + var4 + "," + var5 + "," + var6);
         } else {
    AlarmClock var13 = nullptr;

            for (int var14 = 0; var14 < var12.getWorldObjects().size(); var14++) {
    IsoWorldInventoryObject var15 = (IsoWorldInventoryObject)var12.getWorldObjects().get(var14);
               if (var15 != nullptr && var15.getItem() instanceof AlarmClock && var15.getItem().id == var7) {
                  var13 = (AlarmClock)var15.getItem();
                  break;
               }
            }

            if (var13 == nullptr) {
               DebugLog.log("SyncAlarmClock: AlarmClock is nullptr x,y,z=" + var4 + "," + var5 + "," + var6);
            } else {
               if (var8) {
                  var13.stopRinging();
               } else {
                  var13.setHour(var9);
                  var13.setMinute(var10);
                  var13.setAlarmSet(var11);
               }

               for (int var25 = 0; var25 < udpEngine.connections.size(); var25++) {
    UdpConnection var26 = (UdpConnection)udpEngine.connections.get(var25);
                  if (var26 != var1) {
                     sendAlarmClock_World(var4, var5, var6, var7, var8, var9, var10, var11, var26);
                  }
               }
            }
         }
      }
   }

    static void receiveSyncIsoObject(ByteBuffer var0, UdpConnection var1, short var2) {
      if (DebugOptions.instance.Network.Server.SyncIsoObject.getValue()) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    uint8_t var6 = var0.get();
    uint8_t var7 = var0.get();
    uint8_t var8 = var0.get();
         if (var7 == 1) {
    IsoGridSquare var9 = ServerMap.instance.getGridSquare(var3, var4, var5);
            if (var9 != nullptr && var6 >= 0 && var6 < var9.getObjects().size()) {
               ((IsoObject)var9.getObjects().get(var6)).syncIsoObject(true, var8, var1, var0);
            } else if (var9 != nullptr) {
               DebugLog.log("SyncIsoObject: index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
            } else {
               DebugLog.log("SyncIsoObject: sq is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
            }
         }
      }
   }

    static void receiveSyncIsoObjectReq(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
      if (var3 <= 50 && var3 > 0) {
    ByteBufferWriter var4 = var1.startPacket();
         PacketType.SyncIsoObjectReq.doPacket(var4);
         var4.putShort(var3);

         for (int var5 = 0; var5 < var3; var5++) {
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    uint8_t var9 = var0.get();
    IsoGridSquare var10 = ServerMap.instance.getGridSquare(var6, var7, var8);
            if (var10 != nullptr && var9 >= 0 && var9 < var10.getObjects().size()) {
               ((IsoObject)var10.getObjects().get(var9)).syncIsoObjectSend(var4);
            } else if (var10 != nullptr) {
               var4.putInt(var10.getX());
               var4.putInt(var10.getY());
               var4.putInt(var10.getZ());
               var4.putByte(var9);
               var4.putByte((byte)0);
               var4.putByte((byte)0);
            } else {
               var4.putInt(var6);
               var4.putInt(var7);
               var4.putInt(var8);
               var4.putByte(var9);
               var4.putByte((byte)2);
               var4.putByte((byte)0);
            }
         }

         PacketType.SyncIsoObjectReq.send(var1);
      }
   }

    static void receiveSyncObjects(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
      if (var3 == 1) {
         SyncObjectChunkHashes(var0, var1);
      } else if (var3 == 3) {
         SyncObjectsGridSquareRequest(var0, var1);
      } else if (var3 == 5) {
         SyncObjectsRequest(var0, var1);
      }
   }

    static void SyncObjectChunkHashes(ByteBuffer var0, UdpConnection var1) {
    short var2 = var0.getShort();
      if (var2 <= 10 && var2 > 0) {
    ByteBufferWriter var3 = var1.startPacket();
         PacketType.SyncObjects.doPacket(var3);
         var3.putShort((short)2);
    int var4 = var3.bb.position();
         var3.putShort((short)0);
    int var5 = 0;

         for (int var6 = 0; var6 < var2; var6++) {
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    long var9 = var0.getLong();
    IsoChunk var11 = ServerMap.instance.getChunk(var7, var8);
            if (var11 != nullptr) {
               var5++;
               var3.putShort((short)var11.wx);
               var3.putShort((short)var11.wy);
               var3.putLong(var11.getHashCodeObjects());
    int var12 = var3.bb.position();
               var3.putShort((short)0);
    int var13 = 0;

               for (int var14 = var7 * 10; var14 < var7 * 10 + 10; var14++) {
                  for (int var15 = var8 * 10; var15 < var8 * 10 + 10; var15++) {
                     for (int var16 = 0; var16 <= 7; var16++) {
    IsoGridSquare var17 = ServerMap.instance.getGridSquare(var14, var15, var16);
                        if (var17 == nullptr) {
                           break;
                        }

                        var3.putByte((byte)(var17.getX() - var11.wx * 10));
                        var3.putByte((byte)(var17.getY() - var11.wy * 10));
                        var3.putByte((byte)var17.getZ());
                        var3.putInt((int)var17.getHashCodeObjects());
                        var13++;
                     }
                  }
               }

    int var19 = var3.bb.position();
               var3.bb.position(var12);
               var3.putShort((short)var13);
               var3.bb.position(var19);
            }
         }

    int var18 = var3.bb.position();
         var3.bb.position(var4);
         var3.putShort((short)var5);
         var3.bb.position(var18);
         PacketType.SyncObjects.send(var1);
      }
   }

    static void SyncObjectChunkHashes(IsoChunk var0, UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.SyncObjects.doPacket(var2);
      var2.putShort((short)2);
      var2.putShort((short)1);
      var2.putShort((short)var0.wx);
      var2.putShort((short)var0.wy);
      var2.putLong(var0.getHashCodeObjects());
    int var3 = var2.bb.position();
      var2.putShort((short)0);
    int var4 = 0;

      for (int var5 = var0.wx * 10; var5 < var0.wx * 10 + 10; var5++) {
         for (int var6 = var0.wy * 10; var6 < var0.wy * 10 + 10; var6++) {
            for (int var7 = 0; var7 <= 7; var7++) {
    IsoGridSquare var8 = ServerMap.instance.getGridSquare(var5, var6, var7);
               if (var8 == nullptr) {
                  break;
               }

               var2.putByte((byte)(var8.getX() - var0.wx * 10));
               var2.putByte((byte)(var8.getY() - var0.wy * 10));
               var2.putByte((byte)var8.getZ());
               var2.putInt((int)var8.getHashCodeObjects());
               var4++;
            }
         }
      }

    int var9 = var2.bb.position();
      var2.bb.position(var3);
      var2.putShort((short)var4);
      var2.bb.position(var9);
      PacketType.SyncObjects.send(var1);
   }

    static void SyncObjectsGridSquareRequest(ByteBuffer var0, UdpConnection var1) {
    short var2 = var0.getShort();
      if (var2 <= 100 && var2 > 0) {
    ByteBufferWriter var3 = var1.startPacket();
         PacketType.SyncObjects.doPacket(var3);
         var3.putShort((short)4);
    int var4 = var3.bb.position();
         var3.putShort((short)0);
    int var5 = 0;

         for (int var6 = 0; var6 < var2; var6++) {
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    uint8_t var9 = var0.get();
    IsoGridSquare var10 = ServerMap.instance.getGridSquare(var7, var8, var9);
            if (var10 != nullptr) {
               var5++;
               var3.putInt(var7);
               var3.putInt(var8);
               var3.putByte((byte)var9);
               var3.putByte((byte)var10.getObjects().size());
               var3.putInt(0);
    int var11 = var3.bb.position();

               for (int var12 = 0; var12 < var10.getObjects().size(); var12++) {
                  var3.putLong(((IsoObject)var10.getObjects().get(var12)).customHashCode());
               }

    int var14 = var3.bb.position();
               var3.bb.position(var11 - 4);
               var3.putInt(var14);
               var3.bb.position(var14);
            }
         }

    int var13 = var3.bb.position();
         var3.bb.position(var4);
         var3.putShort((short)var5);
         var3.bb.position(var13);
         PacketType.SyncObjects.send(var1);
      }
   }

    static void SyncObjectsRequest(ByteBuffer var0, UdpConnection var1) {
    short var2 = var0.getShort();
      if (var2 <= 100 && var2 > 0) {
         for (int var3 = 0; var3 < var2; var3++) {
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    uint8_t var6 = var0.get();
    long var7 = var0.getLong();
    IsoGridSquare var9 = ServerMap.instance.getGridSquare(var4, var5, var6);
            if (var9 != nullptr) {
               for (int var10 = 0; var10 < var9.getObjects().size(); var10++) {
                  if (((IsoObject)var9.getObjects().get(var10)).customHashCode() == var7) {
    ByteBufferWriter var11 = var1.startPacket();
                     PacketType.SyncObjects.doPacket(var11);
                     var11.putShort((short)6);
                     var11.putInt(var4);
                     var11.putInt(var5);
                     var11.putByte((byte)var6);
                     var11.putLong(var7);
                     var11.putByte((byte)var9.getObjects().size());

                     for (int var12 = 0; var12 < var9.getObjects().size(); var12++) {
                        var11.putLong(((IsoObject)var9.getObjects().get(var12)).customHashCode());
                     }

                     try {
                        ((IsoObject)var9.getObjects().get(var10)).writeToRemoteBuffer(var11);
                     } catch (Throwable var13) {
                        DebugLog.log("ERROR: GameServer.SyncObjectsRequest " + var13.getMessage());
                        var1.cancelPacket();
                        break;
                     }

                     PacketType.SyncObjects.send(var1);
                     break;
                  }
               }
            }
         }
      }
   }

    static void receiveSyncDoorKey(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    uint8_t var6 = var0.get();
    int var7 = var0.getInt();
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var8 != nullptr && var6 >= 0 && var6 < var8.getObjects().size()) {
    IsoObject var9 = (IsoObject)var8.getObjects().get(var6);
         if (dynamic_cast<IsoDoor*>(var9) != nullptr var10) {
            var10.keyId = var7;

            for (int var12 = 0; var12 < udpEngine.connections.size(); var12++) {
    UdpConnection var13 = (UdpConnection)udpEngine.connections.get(var12);
               if (var13.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var11 = var13.startPacket();
                  PacketType.SyncDoorKey.doPacket(var11);
                  var11.putInt(var3);
                  var11.putInt(var4);
                  var11.putInt(var5);
                  var11.putByte(var6);
                  var11.putInt(var7);
                  PacketType.SyncDoorKey.send(var13);
               }
            }
         } else {
            DebugLog.log("SyncDoorKey: expected IsoDoor index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
         }
      } else if (var8 != nullptr) {
         DebugLog.log("SyncDoorKey: index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
      } else {
         DebugLog.log("SyncDoorKey: sq is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
      }
   }

    static void receiveSyncThumpable(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    uint8_t var6 = var0.get();
    int var7 = var0.getInt();
    uint8_t var8 = var0.get();
    int var9 = var0.getInt();
    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var10 != nullptr && var6 >= 0 && var6 < var10.getObjects().size()) {
    IsoObject var11 = (IsoObject)var10.getObjects().get(var6);
         if (dynamic_cast<IsoThumpable*>(var11) != nullptr var12) {
            var12.lockedByCode = var7;
            var12.lockedByPadlock = var8 == 1;
            var12.keyId = var9;

            for (int var14 = 0; var14 < udpEngine.connections.size(); var14++) {
    UdpConnection var15 = (UdpConnection)udpEngine.connections.get(var14);
               if (var15.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var13 = var15.startPacket();
                  PacketType.SyncThumpable.doPacket(var13);
                  var13.putInt(var3);
                  var13.putInt(var4);
                  var13.putInt(var5);
                  var13.putByte(var6);
                  var13.putInt(var7);
                  var13.putByte(var8);
                  var13.putInt(var9);
                  PacketType.SyncThumpable.send(var15);
               }
            }
         } else {
            DebugLog.log("SyncThumpable: expected IsoThumpable index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
         }
      } else if (var10 != nullptr) {
         DebugLog.log("SyncThumpable: index=" + var6 + " is invalid x,y,z=" + var3 + "," + var4 + "," + var5);
      } else {
         DebugLog.log("SyncThumpable: sq is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
      }
   }

    static void receiveRemoveItemFromSquare(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var7 != nullptr && var6 >= 0 && var6 < var7.getObjects().size()) {
    IsoObject var8 = (IsoObject)var7.getObjects().get(var6);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var8) != nullptr)) {
            IsoRegions.setPreviousFlags(var7);
         }

         DebugLog.log(DebugType.Objects, "object: removing " + var8 + " index=" + var6 + " " + var3 + "," + var4 + "," + var5);
         if (dynamic_cast<IsoWorldInventoryObject*>(var8) != nullptr) {
            LoggerManager.getLogger("item")
               .write(
                  var1.idStr
                     + " \""
                     + var1.username
                     + "\" floor -1 "
                     + var3
                     + ","
                     + var4
                     + ","
                     + var5
                     + " ["
                     + ((IsoWorldInventoryObject)var8).getItem().getFullType()
                     + "]"
               );
         } else {
    std::string var9 = var8.getName() != nullptr ? var8.getName() : var8.getObjectName();
            if (var8.getSprite() != nullptr && var8.getSprite().getName() != nullptr) {
               var9 = var9 + " (" + var8.getSprite().getName() + ")";
            }

            LoggerManager.getLogger("map").write(var1.idStr + " \"" + var1.username + "\" removed " + var9 + " at " + var3 + "," + var4 + "," + var5);
         }

         if (var8.isTableSurface()) {
            for (int var12 = var6 + 1; var12 < var7.getObjects().size(); var12++) {
    IsoObject var10 = (IsoObject)var7.getObjects().get(var12);
               if (var10.isTableTopObject() || var10.isTableSurface()) {
                  var10.setRenderYOffset(var10.getRenderYOffset() - var8.getSurfaceOffset());
               }
            }
         }

         if (!(dynamic_cast<IsoWorldInventoryObject*>(var8) != nullptr)) {
            LuaEventManager.triggerEvent("OnObjectAboutToBeRemoved", var8);
         }

         if (!var7.getObjects().contains(var8)) {
            throw IllegalArgumentException("OnObjectAboutToBeRemoved not allowed to remove the object");
         }

         var8.removeFromWorld();
         var8.removeFromSquare();
         var7.RecalcAllWithNeighbours(true);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var8) != nullptr)) {
            IsoWorld.instance.CurrentCell.checkHaveRoof(var3, var4);
            MapCollisionData.instance.squareChanged(var7);
            PolygonalMap2.instance.squareChanged(var7);
            ServerMap.instance.physicsCheck(var3, var4);
            IsoRegions.squareChanged(var7, true);
            IsoGenerator.updateGenerator(var7);
         }

         for (int var13 = 0; var13 < udpEngine.connections.size(); var13++) {
    UdpConnection var14 = (UdpConnection)udpEngine.connections.get(var13);
            if (var14.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var11 = var14.startPacket();
               PacketType.RemoveItemFromSquare.doPacket(var11);
               var11.putInt(var3);
               var11.putInt(var4);
               var11.putInt(var5);
               var11.putInt(var6);
               PacketType.RemoveItemFromSquare.send(var14);
            }
         }
      }
   }

    static int RemoveItemFromMap(IsoObject var0) {
    int var1 = var0.getSquare().getX();
    int var2 = var0.getSquare().getY();
    int var3 = var0.getSquare().getZ();
    int var4 = var0.getSquare().getObjects().indexOf(var0);
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var5 != nullptr && !(dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr)) {
         IsoRegions.setPreviousFlags(var5);
      }

      LuaEventManager.triggerEvent("OnObjectAboutToBeRemoved", var0);
      if (!var0.getSquare().getObjects().contains(var0)) {
         throw IllegalArgumentException("OnObjectAboutToBeRemoved not allowed to remove the object");
      } else {
         var0.removeFromWorld();
         var0.removeFromSquare();
         if (var5 != nullptr) {
            var5.RecalcAllWithNeighbours(true);
         }

         if (!(dynamic_cast<IsoWorldInventoryObject*>(var0) != nullptr)) {
            IsoWorld.instance.CurrentCell.checkHaveRoof(var1, var2);
            MapCollisionData.instance.squareChanged(var5);
            PolygonalMap2.instance.squareChanged(var5);
            ServerMap.instance.physicsCheck(var1, var2);
            IsoRegions.squareChanged(var5, true);
            IsoGenerator.updateGenerator(var5);
         }

         for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
            if (var7.RelevantTo(var1, var2)) {
    ByteBufferWriter var8 = var7.startPacket();
               PacketType.RemoveItemFromSquare.doPacket(var8);
               var8.putInt(var1);
               var8.putInt(var2);
               var8.putInt(var3);
               var8.putInt(var4);
               PacketType.RemoveItemFromSquare.send(var7);
            }
         }

    return var4;
      }
   }

    static void sendBloodSplatter(HandWeapon var0, float var1, float var2, float var3, Vector2 var4, bool var5, bool var6) {
      for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
    ByteBufferWriter var9 = var8.startPacket();
         PacketType.BloodSplatter.doPacket(var9);
         var9.putUTF(var0 != nullptr ? var0.getType() : "");
         var9.putFloat(var1);
         var9.putFloat(var2);
         var9.putFloat(var3);
         var9.putFloat(var4.getX());
         var9.putFloat(var4.getY());
         var9.putByte((byte)(var5 ? 1 : 0));
         var9.putByte((byte)(var6 ? 1 : 0));
    uint8_t var10 = 0;
         if (var0 != nullptr) {
            var10 = (byte)Math.max(var0.getSplatNumber(), 1);
         }

         var9.putByte(var10);
         PacketType.BloodSplatter.send(var8);
      }
   }

    static void receiveAddItemToMap(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoObject var3 = WorldItemTypes.createFromBuffer(var0);
      if (dynamic_cast<IsoFire*>(var3) != nullptr && ServerOptions.instance.NoFire.getValue()) {
         DebugLog.log("user \"" + var1.username + "\" tried to start a fire");
      } else {
         var3.loadFromRemoteBuffer(var0);
         if (var3.square != nullptr) {
            DebugLog.log(
               DebugType.Objects, "object: added " + var3 + " index=" + var3.getObjectIndex() + " " + var3.getX() + "," + var3.getY() + "," + var3.getZ()
            );
            if (dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr) {
               LoggerManager.getLogger("item")
                  .write(
                     var1.idStr
                        + " \""
                        + var1.username
                        + "\" floor +1 "
                        + (int)var3.getX()
                        + ","
                        + (int)var3.getY()
                        + ","
                        + (int)var3.getZ()
                        + " ["
                        + ((IsoWorldInventoryObject)var3).getItem().getFullType()
                        + "]"
                  );
            } else {
    std::string var4 = var3.getName() != nullptr ? var3.getName() : var3.getObjectName();
               if (var3.getSprite() != nullptr && var3.getSprite().getName() != nullptr) {
                  var4 = var4 + " (" + var3.getSprite().getName() + ")";
               }

               LoggerManager.getLogger("map")
                  .write(var1.idStr + " \"" + var1.username + "\" added " + var4 + " at " + var3.getX() + "," + var3.getY() + "," + var3.getZ());
            }

            var3.addToWorld();
            var3.square.RecalcProperties();
            if (!(dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr)) {
               var3.square.restackSheetRope();
               IsoWorld.instance.CurrentCell.checkHaveRoof(var3.square.getX(), var3.square.getY());
               MapCollisionData.instance.squareChanged(var3.square);
               PolygonalMap2.instance.squareChanged(var3.square);
               ServerMap.instance.physicsCheck(var3.square.x, var3.square.y);
               IsoRegions.squareChanged(var3.square);
               IsoGenerator.updateGenerator(var3.square);
            }

            for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var7);
               if (var5.getConnectedGUID() != var1.getConnectedGUID() && var5.RelevantTo(var3.square.x, var3.square.y)) {
    ByteBufferWriter var6 = var5.startPacket();
                  PacketType.AddItemToMap.doPacket(var6);
                  var3.writeToRemoteBuffer(var6);
                  PacketType.AddItemToMap.send(var5);
               }
            }

            if (!(dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr)) {
               LuaEventManager.triggerEvent("OnObjectAdded", var3);
            } else {
               ((IsoWorldInventoryObject)var3).dropTime = GameTime.getInstance().getWorldAgeHours();
            }
         } else if (bDebug) {
            DebugLog.log("AddItemToMap: sq is nullptr");
         }
      }
   }

    static void disconnect(UdpConnection var0, const std::string& var1) {
      if (var0.playerDownloadServer != nullptr) {
         try {
            var0.playerDownloadServer.destroy();
         } catch (Exception var4) {
            var4.printStackTrace();
         }

         var0.playerDownloadServer = nullptr;
      }

      RequestDataManager.getInstance().disconnect(var0);

      for (int var2 = 0; var2 < 4; var2++) {
    IsoPlayer var3 = var0.players[var2];
         if (var3 != nullptr) {
            ChatServer.getInstance().disconnectPlayer(var0.playerIDs[var2]);
            disconnectPlayer(var3, var0);
         }

         var0.usernames[var2] = nullptr;
         var0.players[var2] = nullptr;
         var0.playerIDs[var2] = -1;
         var0.ReleventPos[var2] = nullptr;
         var0.connectArea[var2] = nullptr;
      }

      for (int var5 = 0; var5 < udpEngine.getMaxConnections(); var5++) {
         if (SlotToConnection[var5] == var0) {
            SlotToConnection[var5] = nullptr;
         }
      }

    Iterator var6 = IDToAddressMap.entrySet().iterator();

      while (var6.hasNext()) {
    Entry var7 = (Entry)var6.next();
         if ((int64_t)var7.getValue() == var0.getConnectedGUID()) {
            var6.remove();
         }
      }

      if (!SteamUtils.isSteamModeEnabled()) {
         PublicServerUtil.updatePlayers();
      }

      if (CoopSlave.instance != nullptr && var0.isCoopHost) {
         DebugLog.log("Host user disconnected, stopping the server");
         ServerMap.instance.QueueQuit();
      }

      if (bServer) {
         ConnectionManager.log("disconnect", var1, var0);
      }
   }

    static void addIncoming(short var0, ByteBuffer var1, UdpConnection var2) {
    ZomboidNetData var3 = nullptr;
      if (var1.limit() > 2048) {
         var3 = ZomboidNetDataPool.instance.getLong(var1.limit());
      } else {
         var3 = ZomboidNetDataPool.instance.get();
      }

      var3.read(var0, var1, var2);
      if (var3.type == nullptr) {
         try {
            if (ServerOptions.instance.AntiCheatProtectionType13.getValue() && PacketValidator.checkUser(var2)) {
               PacketValidator.doKickUser(var2, std::string.valueOf((int)var0), "Type13", nullptr);
            }
         } catch (Exception var5) {
            var5.printStackTrace();
         }
      } else {
         var3.time = System.currentTimeMillis();
         if (var3.type == PacketType.PlayerUpdate || var3.type == PacketType.PlayerUpdateReliable) {
            MainLoopPlayerUpdateQ.push_back(var3);
         } else if (var3.type != PacketType.VehiclesUnreliable && var3.type != PacketType.Vehicles) {
            MainLoopNetDataHighPriorityQ.push_back(var3);
         } else {
    uint8_t var4 = var3.buffer.get(0);
            if (var4 == 9) {
               MainLoopNetDataQ.push_back(var3);
            } else {
               MainLoopNetDataHighPriorityQ.push_back(var3);
            }
         }
      }
   }

    static void smashWindow(IsoWindow var0, int var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var3.RelevantTo(var0.getX(), var0.getY())) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.SmashWindow.doPacket(var4);
            var4.putInt(var0.square.getX());
            var4.putInt(var0.square.getY());
            var4.putInt(var0.square.getZ());
            var4.putByte((byte)var0.square.getObjects().indexOf(var0));
            var4.putByte((byte)var1);
            PacketType.SmashWindow.send(var3);
         }
      }
   }

    static void receiveHitCharacter(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    HitCharacterPacket var3 = HitCharacterPacket.process(var0);
         if (var3 != nullptr) {
            var3.parse(var0, var1);
            if (var3.isConsistent() && var3.validate(var1)) {
               DebugLog.Damage.trace(var3.getDescription());
               sendHitCharacter(var3, var1);
               var3.tryProcess();
            }
         }
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "ReceiveHitCharacter: failed", LogSeverity.Error);
      }
   }

    static void sendHitCharacter(HitCharacterPacket var0, UdpConnection var1) {
      DebugLog.Damage.trace(var0.getDescription());

      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var3.getConnectedGUID() != var1.getConnectedGUID() && var0.isRelevant(var3)) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.HitCharacter.doPacket(var4);
            var0.write(var4);
            PacketType.HitCharacter.send(var3);
         }
      }
   }

    static void receiveZombieDeath(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    DeadZombiePacket var3 = std::make_shared<DeadZombiePacket>();
         var3.parse(var0, var1);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("ReceiveZombieDeath: %s", var3.getDescription());
         }

         if (var3.isConsistent()) {
            if (var3.getZombie().isReanimatedPlayer()) {
               sendZombieDeath(var3.getZombie());
            } else {
               sendZombieDeath(var3);
            }

            var3.process();
         }
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "ReceiveZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void sendZombieDeath(IsoZombie var0) {
      try {
    DeadZombiePacket var1 = std::make_shared<DeadZombiePacket>();
         var1.set(var0);
         sendZombieDeath(var1);
      } catch (Exception var2) {
         DebugLog.Multiplayer.printException(var2, "SendZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void sendZombieDeath(DeadZombiePacket var0) {
      try {
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("SendZombieDeath: %s", var0.getDescription());
         }

         for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
            if (var2.RelevantTo(var0.getZombie().getX(), var0.getZombie().getY())) {
    ByteBufferWriter var3 = var2.startPacket();
               PacketType.ZombieDeath.doPacket(var3);

               try {
                  var0.write(var3);
                  PacketType.ZombieDeath.send(var2);
               } catch (Exception var5) {
                  var2.cancelPacket();
                  DebugLog.Multiplayer.printException(var5, "SendZombieDeath: failed", LogSeverity.Error);
               }
            }
         }
      } catch (Exception var6) {
         DebugLog.Multiplayer.printException(var6, "SendZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void receivePlayerDeath(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    DeadPlayerPacket var3 = std::make_shared<DeadPlayerPacket>();
         var3.parse(var0, var1);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("ReceivePlayerDeath: %s", var3.getDescription());
         }

    std::string var4 = var3.getPlayer().username;
         ChatServer.getInstance().disconnectPlayer(var3.getPlayer().getOnlineID());
         ServerWorldDatabase.instance.saveTransactionID(var4, 0);
         var3.getPlayer().setTransactionID(0);
         transactionIDMap.put(var4, 0);
         SafetySystemManager.clearSafety(var3.getPlayer());
         if (var3.getPlayer().accessLevel == "") && !ServerOptions.instance.Open.getValue() && ServerOptions.instance.DropOffWhiteListAfterDeath.getValue()
            )
          {
            try {
               ServerWorldDatabase.instance.removeUser(var4);
            } catch (SQLException var6) {
               DebugLog.Multiplayer.printException(var6, "ReceivePlayerDeath: db failed", LogSeverity.Warning);
            }
         }

         if (var3.isConsistent()) {
            var3.id = var3.getPlayer().getOnlineID();
            sendPlayerDeath(var3, var1);
            var3.process();
         }

         var3.getPlayer().setStateMachineLocked(true);
      } catch (Exception var7) {
         DebugLog.Multiplayer.printException(var7, "ReceivePlayerDeath: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerDeath(DeadPlayerPacket var0, UdpConnection var1) {
      if (Core.bDebug) {
         DebugLog.Multiplayer.debugln("SendPlayerDeath: %s", var0.getDescription());
      }

      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var1 == nullptr || var1.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.PlayerDeath.doPacket(var4);
            var0.write(var4);
            PacketType.PlayerDeath.send(var3);
         }
      }
   }

    static void receivePlayerDamage(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    short var3 = var0.getShort();
    float var4 = var0.getFloat();
    IsoPlayer var5 = getPlayerFromConnection(var1, var3);
         if (var5 != nullptr) {
            var5.getBodyDamage().load(var0, IsoWorld.getWorldVersion());
            var5.getStats().setPain(var4);
            if (Core.bDebug) {
               DebugLog.Multiplayer.debugln("ReceivePlayerDamage: \"%s\" %f", var5.getUsername(), var5.getBodyDamage().getOverallBodyHealth());
            }

            sendPlayerDamage(var5, var1);
         }
      } catch (Exception var6) {
         DebugLog.Multiplayer.printException(var6, "ReceivePlayerDamage: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerDamage(IsoPlayer var0, UdpConnection var1) {
      if (Core.bDebug) {
         DebugLog.Multiplayer.debugln("SendPlayerDamage: \"%s\" %f", var0.getUsername(), var0.getBodyDamage().getOverallBodyHealth());
      }

      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var1.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.PlayerDamage.doPacket(var4);

            try {
               var4.putShort(var0.getOnlineID());
               var4.putFloat(var0.getStats().getPain());
               var0.getBodyDamage().save(var4.bb);
               PacketType.PlayerDamage.send(var3);
            } catch (Exception var6) {
               var3.cancelPacket();
               DebugLog.Multiplayer.printException(var6, "SendPlayerDamage: failed", LogSeverity.Error);
            }
         }
      }
   }

    static void receiveSyncInjuries(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    SyncInjuriesPacket var3 = std::make_shared<SyncInjuriesPacket>();
         var3.parse(var0, var1);
         DebugLog.Damage.trace(var3.getDescription());
         if (var3.process()) {
            var3.id = var3.player.getOnlineID();
            sendPlayerInjuries(var1, var3);
         }
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "ReceivePlayerInjuries: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerInjuries(UdpConnection var0, SyncInjuriesPacket var1) {
    ByteBufferWriter var2 = var0.startPacket();
      PacketType.SyncInjuries.doPacket(var2);
      var1.write(var2);
      PacketType.SyncInjuries.send(var0);
   }

    static void receiveKeepAlive(ByteBuffer var0, UdpConnection var1, short var2) {
      MPDebugInfo.instance.serverPacket(var0, var1);
   }

    static void receiveRemoveCorpseFromMap(ByteBuffer var0, UdpConnection var1, short var2) {
    RemoveCorpseFromMap var3 = std::make_shared<RemoveCorpseFromMap>();
      var3.parse(var0, var1);
      if (var3.isConsistent()) {
         var3.process();

         for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
            if (var5.getConnectedGUID() != var1.getConnectedGUID() && var3.isRelevant(var5)) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.RemoveCorpseFromMap.doPacket(var6);
               var3.write(var6);
               PacketType.RemoveCorpseFromMap.send(var5);
            }
         }
      }
   }

    static void sendRemoveCorpseFromMap(IsoDeadBody var0) {
    RemoveCorpseFromMap var1 = std::make_shared<RemoveCorpseFromMap>();
      var1.set(var0);
      DebugLog.Death.trace(var1.getDescription());

      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
    ByteBufferWriter var4 = var3.startPacket();
         PacketType.RemoveCorpseFromMap.doPacket(var4);
         var1.write(var4);
         PacketType.RemoveCorpseFromMap.send(var3);
      }
   }

    static void receiveEventPacket(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    EventPacket var3 = std::make_shared<EventPacket>();
         var3.parse(var0, var1);

         for (UdpConnection var5 : udpEngine.connections) {
            if (var5.getConnectedGUID() != var1.getConnectedGUID() && var3.isRelevant(var5)) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.EventPacket.doPacket(var6);
               var3.write(var6);
               PacketType.EventPacket.send(var5);
            }
         }
      } catch (Exception var7) {
         DebugLog.Multiplayer.printException(var7, "ReceiveEvent: failed", LogSeverity.Error);
      }
   }

    static void receiveActionPacket(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    ActionPacket var3 = std::make_shared<ActionPacket>();
         var3.parse(var0, var1);

         for (UdpConnection var5 : udpEngine.connections) {
            if (var5.getConnectedGUID() != var1.getConnectedGUID() && var3.isRelevant(var5)) {
    ByteBufferWriter var6 = var5.startPacket();
               PacketType.ActionPacket.doPacket(var6);
               var3.write(var6);
               PacketType.ActionPacket.send(var5);
            }
         }
      } catch (Exception var7) {
         DebugLog.Multiplayer.printException(var7, "ReceiveAction: failed", LogSeverity.Error);
      }
   }

    static void receiveKillZombie(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    short var3 = var0.getShort();
    bool var4 = var0.get() != 0;
         DebugLog.Death.trace("id=%d, isFallOnFront=%b", var3, var4);
    IsoZombie var5 = (IsoZombie)ServerMap.instance.ZombieMap.get(var3);
         if (var5 != nullptr) {
            var5.setFallOnFront(var4);
            var5.becomeCorpse();
         } else {
            DebugLog.Multiplayer.error("ReceiveKillZombie: zombie not found");
         }
      } catch (Exception var6) {
         DebugLog.Multiplayer.printException(var6, "ReceiveKillZombie: failed", LogSeverity.Error);
      }
   }

    static void receiveEatBody(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "ReceiveEatBody");
         }

    short var3 = var0.getShort();
    IsoZombie var4 = (IsoZombie)ServerMap.instance.ZombieMap.get(var3);
         if (var4 == nullptr) {
            DebugLog.Multiplayer.error("ReceiveEatBody: zombie " + var3 + " not found");
            return;
         }

         for (UdpConnection var6 : udpEngine.connections) {
            if (var6.RelevantTo(var4.x, var4.y)) {
               if (Core.bDebug) {
                  DebugLog.log(DebugType.Multiplayer, "SendEatBody");
               }

    ByteBufferWriter var7 = var6.startPacket();
               PacketType.EatBody.doPacket(var7);
               var0.position(0);
               var7.bb.put(var0);
               PacketType.EatBody.send(var6);
            }
         }
      } catch (Exception var8) {
         DebugLog.Multiplayer.printException(var8, "ReceiveEatBody: failed", LogSeverity.Error);
      }
   }

    static void receiveSyncRadioData(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    bool var3 = var0.get() == 1;
    int var4 = var0.getInt();
         int[] var5 = new int[var4];

         for (int var6 = 0; var6 < var4; var6++) {
            var5[var6] = var0.getInt();
         }

         RakVoice.SetChannelsRouting(var1.getConnectedGUID(), var3, var5, (short)var4);

         for (UdpConnection var7 : udpEngine.connections) {
            if (var7 != var1 && var1.players[0] != nullptr) {
    ByteBufferWriter var8 = var7.startPacket();
               PacketType.SyncRadioData.doPacket(var8);
               var8.putShort(var1.players[0].OnlineID);
               var0.position(0);
               var8.bb.put(var0);
               PacketType.SyncRadioData.send(var7);
            }
         }
      } catch (Exception var9) {
         DebugLog.Multiplayer.printException(var9, "SyncRadioData: failed", LogSeverity.Error);
      }
   }

    static void receiveThump(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "ReceiveThump");
         }

    short var3 = var0.getShort();
    IsoZombie var4 = (IsoZombie)ServerMap.instance.ZombieMap.get(var3);
         if (var4 == nullptr) {
            DebugLog.Multiplayer.error("ReceiveThump: zombie " + var3 + " not found");
            return;
         }

         for (UdpConnection var6 : udpEngine.connections) {
            if (var6.RelevantTo(var4.x, var4.y)) {
    ByteBufferWriter var7 = var6.startPacket();
               PacketType.Thump.doPacket(var7);
               var0.position(0);
               var7.bb.put(var0);
               PacketType.Thump.send(var6);
            }
         }
      } catch (Exception var8) {
         DebugLog.Multiplayer.printException(var8, "ReceiveEatBody: failed", LogSeverity.Error);
      }
   }

    static void sendWorldSound(UdpConnection var0, WorldSound var1) {
    ByteBufferWriter var2 = var0.startPacket();
      PacketType.WorldSound.doPacket(var2);

      try {
         var2.putInt(var1.x);
         var2.putInt(var1.y);
         var2.putInt(var1.z);
         var2.putInt(var1.radius);
         var2.putInt(var1.volume);
         var2.putByte((byte)(var1.stresshumans ? 1 : 0));
         var2.putFloat(var1.zombieIgnoreDist);
         var2.putFloat(var1.stressMod);
         var2.putByte((byte)(var1.sourceIsZombie ? 1 : 0));
         PacketType.WorldSound.send(var0);
      } catch (Exception var4) {
         DebugLog.Sound.printException(var4, "SendWorldSound: failed", LogSeverity.Error);
         var0.cancelPacket();
      }
   }

    static void sendWorldSound(WorldSound var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if ((var1 == nullptr || var1.getConnectedGUID() != var3.getConnectedGUID()) && var3.isFullyConnected()) {
    IsoPlayer var4 = getAnyPlayerFromConnection(var3);
            if (var4 != nullptr && var3.RelevantTo(var0.x, var0.y, var0.radius)) {
               sendWorldSound(var3, var0);
            }
         }
      }
   }

    static void receiveWorldSound(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    bool var8 = var0.get() == 1;
    float var9 = var0.getFloat();
    float var10 = var0.getFloat();
    bool var11 = var0.get() == 1;
      DebugLog.Sound.noise("x=%d y=%d z=%d, radius=%d", var3, var4, var5, var6);
    WorldSound var12 = WorldSoundManager.instance.addSound(nullptr, var3, var4, var5, var6, var7, var8, var9, var10, var11, false, true);
      if (var12 != nullptr) {
         sendWorldSound(var12, var1);
      }
   }

    static void kick(UdpConnection var0, const std::string& var1, const std::string& var2) {
      DebugLog.General.warn("The player " + var0.username + " was kicked. The reason was " + var1 + ", " + var2);
      ConnectionManager.log("kick", var2, var0);
    ByteBufferWriter var3 = var0.startPacket();

      try {
         PacketType.Kicked.doPacket(var3);
         var3.putUTF(var1);
         var3.putUTF(var2);
         PacketType.Kicked.send(var0);
      } catch (Exception var5) {
         DebugLog.Multiplayer.printException(var5, "Kick: failed", LogSeverity.Error);
         var0.cancelPacket();
      }
   }

    static void sendStartRain(UdpConnection var0) {
    ByteBufferWriter var1 = var0.startPacket();
      PacketType.StartRain.doPacket(var1);
      var1.putInt(RainManager.randRainMin);
      var1.putInt(RainManager.randRainMax);
      var1.putFloat(RainManager.RainDesiredIntensity);
      PacketType.StartRain.send(var0);
   }

    static void startRain() {
      if (udpEngine != nullptr) {
         for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
            sendStartRain(var1);
         }
      }
   }

    static void sendStopRain(UdpConnection var0) {
    ByteBufferWriter var1 = var0.startPacket();
      PacketType.StopRain.doPacket(var1);
      PacketType.StopRain.send(var0);
   }

    static void stopRain() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         sendStopRain(var1);
      }
   }

    static void sendWeather(UdpConnection var0) {
    GameTime var1 = GameTime.getInstance();
    ByteBufferWriter var2 = var0.startPacket();
      PacketType.Weather.doPacket(var2);
      var2.putByte((byte)var1.getDawn());
      var2.putByte((byte)var1.getDusk());
      var2.putByte((byte)(var1.isThunderDay() ? 1 : 0));
      var2.putFloat(var1.Moon);
      var2.putFloat(var1.getAmbientMin());
      var2.putFloat(var1.getAmbientMax());
      var2.putFloat(var1.getViewDistMin());
      var2.putFloat(var1.getViewDistMax());
      var2.putFloat(IsoWorld.instance.getGlobalTemperature());
      var2.putUTF(IsoWorld.instance.getWeather());
      ErosionMain.getInstance().sendState(var2.bb);
      PacketType.Weather.send(var0);
   }

    static void sendWeather() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         sendWeather(var1);
      }
   }

    static bool isInSameFaction(IsoPlayer var0, IsoPlayer var1) {
    Faction var2 = Faction.getPlayerFaction(var0);
    Faction var3 = Faction.getPlayerFaction(var1);
      return var2 != nullptr && var2 == var3;
   }

    static bool isInSameSafehouse(IsoPlayer var0, IsoPlayer var1) {
    std::vector var2 = SafeHouse.getSafehouseList();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    SafeHouse var4 = (SafeHouse)var2.get(var3);
         if (var4.playerAllowed(var0.getUsername()) && var4.playerAllowed(var1.getUsername())) {
    return true;
         }
      }

    return false;
   }

    static bool isAnyPlayerInSameFaction(UdpConnection var0, IsoPlayer var1) {
      for (int var2 = 0; var2 < 4; var2++) {
    IsoPlayer var3 = var0.players[var2];
         if (var3 != nullptr && isInSameFaction(var3, var1)) {
    return true;
         }
      }

    return false;
   }

    static bool isAnyPlayerInSameSafehouse(UdpConnection var0, IsoPlayer var1) {
      for (int var2 = 0; var2 < 4; var2++) {
    IsoPlayer var3 = var0.players[var2];
         if (var3 != nullptr && isInSameSafehouse(var3, var1)) {
    return true;
         }
      }

    return false;
   }

    static bool shouldSendWorldMapPlayerPosition(UdpConnection var0, IsoPlayer var1) {
      if (var1 != nullptr && !var1.isDead()) {
    UdpConnection var2 = getConnectionFromPlayer(var1);
         if (var2 == nullptr || var2 == var0 || !var2.isFullyConnected()) {
    return false;
         } else if (var0.accessLevel > 1) {
    return true;
         } else {
    int var3 = ServerOptions.getInstance().MapRemotePlayerVisibility.getValue();
            return var3 != 2 ? true : isAnyPlayerInSameFaction(var0, var1) || isAnyPlayerInSameSafehouse(var0, var1);
         }
      } else {
    return false;
      }
   }

    static void sendWorldMapPlayerPosition(UdpConnection var0) {
      tempPlayers.clear();

      for (int var1 = 0; var1 < Players.size(); var1++) {
    IsoPlayer var2 = Players.get(var1);
         if (shouldSendWorldMapPlayerPosition(var0, var2)) {
            tempPlayers.push_back(var2);
         }
      }

      if (!tempPlayers.empty()) {
    ByteBufferWriter var5 = var0.startPacket();
         PacketType.WorldMapPlayerPosition.doPacket(var5);
         var5.putBoolean(false);
         var5.putShort((short)tempPlayers.size());

         for (int var6 = 0; var6 < tempPlayers.size(); var6++) {
    IsoPlayer var3 = tempPlayers.get(var6);
    WorldMapRemotePlayer var4 = WorldMapRemotePlayers.instance.getOrCreatePlayer(var3);
            var4.setPlayer(var3);
            var5.putShort(var4.getOnlineID());
            var5.putShort(var4.getChangeCount());
            var5.putFloat(var4.getX());
            var5.putFloat(var4.getY());
         }

         PacketType.WorldMapPlayerPosition.send(var0);
      }
   }

    static void sendWorldMapPlayerPosition() {
    int var0 = ServerOptions.getInstance().MapRemotePlayerVisibility.getValue();

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);
         if (var0 != 1 || var2.accessLevel != 1) {
            sendWorldMapPlayerPosition(var2);
         }
      }
   }

    static void receiveWorldMapPlayerPosition(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
      tempPlayers.clear();

      for (int var4 = 0; var4 < var3; var4++) {
    short var5 = var0.getShort();
    IsoPlayer var6 = IDToPlayerMap.get(var5);
         if (var6 != nullptr && shouldSendWorldMapPlayerPosition(var1, var6)) {
            tempPlayers.push_back(var6);
         }
      }

      if (!tempPlayers.empty()) {
    ByteBufferWriter var8 = var1.startPacket();
         PacketType.WorldMapPlayerPosition.doPacket(var8);
         var8.putBoolean(true);
         var8.putShort((short)tempPlayers.size());

         for (int var9 = 0; var9 < tempPlayers.size(); var9++) {
    IsoPlayer var10 = tempPlayers.get(var9);
    WorldMapRemotePlayer var7 = WorldMapRemotePlayers.instance.getOrCreatePlayer(var10);
            var7.setPlayer(var10);
            var8.putShort(var7.getOnlineID());
            var8.putShort(var7.getChangeCount());
            var8.putUTF(var7.getUsername());
            var8.putUTF(var7.getForename());
            var8.putUTF(var7.getSurname());
            var8.putUTF(var7.getAccessLevel());
            var8.putFloat(var7.getX());
            var8.putFloat(var7.getY());
            var8.putBoolean(var7.isInvisible());
         }

         PacketType.WorldMapPlayerPosition.send(var1);
      }
   }

    static void syncClock(UdpConnection var0) {
    GameTime var1 = GameTime.getInstance();
    ByteBufferWriter var2 = var0.startPacket();
      PacketType.SyncClock.doPacket(var2);
      var2.putBoolean(bFastForward);
      var2.putFloat(var1.getTimeOfDay());
      var2.putInt(var1.getNightsSurvived());
      PacketType.SyncClock.send(var0);
   }

    static void syncClock() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         syncClock(var1);
      }
   }

    static void sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2, UdpConnection var3) {
    ByteBufferWriter var4 = var3.startPacket();
      PacketType.ClientCommand.doPacket(var4);
      var4.putUTF(var0);
      var4.putUTF(var1);
      if (var2 != nullptr && !var2.empty()) {
         var4.putByte((byte)1);

         try {
    KahluaTableIterator var5 = var2.iterator();

            while (var5.advance()) {
               if (!TableNetworkUtils.canSave(var5.getKey(), var5.getValue())) {
                  DebugLog.log("ERROR: sendServerCommand: can't save key,value=" + var5.getKey() + "," + var5.getValue());
               }
            }

            TableNetworkUtils.save(var2, var4.bb);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      } else {
         var4.putByte((byte)0);
      }

      PacketType.ClientCommand.send(var3);
   }

    static void sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         sendServerCommand(var0, var1, var2, var4);
      }
   }

    static void sendServerCommandV(const std::string& var0, const std::string& var1, Object... var2) {
      if (var2.length == 0) {
         sendServerCommand(var0, var1, (KahluaTable)nullptr);
      } else if (var2.length % 2 != 0) {
         DebugLog.log("ERROR: sendServerCommand called with invalid number of arguments (" + var0 + " " + var1 + ")");
      } else {
    KahluaTable var3 = LuaManager.platform.newTable();

         for (byte var4 = 0; var4 < var2.length; var4 += 2) {
    void* var5 = var2[var4 + 1];
            if (dynamic_cast<float*>(var5) != nullptr) {
               var3.rawset(var2[var4], ((float)var5).doubleValue());
            } else if (dynamic_cast<int*>(var5) != nullptr) {
               var3.rawset(var2[var4], ((int)var5).doubleValue());
            } else if (dynamic_cast<int16_t*>(var5) != nullptr) {
               var3.rawset(var2[var4], ((int16_t)var5).doubleValue());
            } else {
               var3.rawset(var2[var4], var5);
            }
         }

         sendServerCommand(var0, var1, var3);
      }
   }

    static void sendServerCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
      if (PlayerToAddressMap.containsKey(var0)) {
    long var4 = PlayerToAddressMap.get(var0);
    UdpConnection var6 = udpEngine.getActiveConnection(var4);
         if (var6 != nullptr) {
            sendServerCommand(var1, var2, var3, var6);
         }
      }
   }

   public static std::vector<IsoPlayer> getPlayers(std::vector<IsoPlayer> var0) {
      var0.clear();

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         for (int var3 = 0; var3 < 4; var3++) {
    IsoPlayer var4 = var2.players[var3];
            if (var4 != nullptr && var4.OnlineID != -1) {
               var0.push_back(var4);
            }
         }
      }

    return var0;
   }

   public static std::vector<IsoPlayer> getPlayers() {
    std::vector var0 = new std::vector();
    return getPlayers();
   }

    static int getPlayerCount() {
    int var0 = 0;

      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         for (int var3 = 0; var3 < 4; var3++) {
            if (var2.playerIDs[var3] != -1) {
               var0++;
            }
         }
      }

    return var0;
   }

    static void sendAmbient(const std::string& var0, int var1, int var2, int var3, float var4) {
      DebugLog.log(DebugType.Sound, "ambient: sending " + var0 + " at " + var1 + "," + var2 + " radius=" + var3);

      for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
    IsoPlayer var7 = getAnyPlayerFromConnection(var6);
         if (var7 != nullptr) {
    ByteBufferWriter var8 = var6.startPacket();
            PacketType.AddAmbient.doPacket(var8);
            var8.putUTF(var0);
            var8.putInt(var1);
            var8.putInt(var2);
            var8.putInt(var3);
            var8.putFloat(var4);
            PacketType.AddAmbient.send(var6);
         }
      }
   }

    static void receiveChangeSafety(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    SafetyPacket var3 = std::make_shared<SafetyPacket>();
         var3.parse(var0, var1);
         var3.log(var1, "ReceiveChangeSafety");
         var3.process();
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "ReceiveZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void sendChangeSafety(Safety var0) {
      try {
    SafetyPacket var1 = std::make_shared<SafetyPacket>(var0);
         var1.log(nullptr, "SendChangeSafety");

         for (UdpConnection var3 : udpEngine.connections) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.ChangeSafety.doPacket(var4);
            var1.write(var4);
            PacketType.ChangeSafety.send(var3);
         }
      } catch (Exception var5) {
         DebugLog.Multiplayer.printException(var5, "SendChangeSafety: failed", LogSeverity.Error);
      }
   }

    static void receivePing(ByteBuffer var0, UdpConnection var1, short var2) {
      var1.ping = true;
      answerPing(var0, var1);
   }

    static void updateOverlayForClients(IsoObject var0, const std::string& var1, float var2, float var3, float var4, float var5, UdpConnection var6) {
      if (udpEngine != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8 != nullptr
               && var0.square != nullptr
               && var8.RelevantTo(var0.square.x, var0.square.y)
               && (var6 == nullptr || var8.getConnectedGUID() != var6.getConnectedGUID())) {
    ByteBufferWriter var9 = var8.startPacket();
               PacketType.UpdateOverlaySprite.doPacket(var9);
               GameWindow.WriteStringUTF(var9.bb, var1);
               var9.putInt(var0.getSquare().getX());
               var9.putInt(var0.getSquare().getY());
               var9.putInt(var0.getSquare().getZ());
               var9.putFloat(var2);
               var9.putFloat(var3);
               var9.putFloat(var4);
               var9.putFloat(var5);
               var9.putInt(var0.getSquare().getObjects().indexOf(var0));
               PacketType.UpdateOverlaySprite.send(var8);
            }
         }
      }
   }

    static void receiveUpdateOverlaySprite(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadStringUTF(var0);
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    float var7 = var0.getFloat();
    float var8 = var0.getFloat();
    float var9 = var0.getFloat();
    float var10 = var0.getFloat();
    int var11 = var0.getInt();
    IsoGridSquare var12 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
      if (var12 != nullptr && var11 < var12.getObjects().size()) {
         try {
    IsoObject var13 = (IsoObject)var12.getObjects().get(var11);
            if (var13 != nullptr && var13.setOverlaySprite(var3, var7, var8, var9, var10, false)) {
               updateOverlayForClients(var13, var3, var7, var8, var9, var10, var1);
            }
         } catch (Exception var14) {
         }
      }
   }

    static void sendReanimatedZombieID(IsoPlayer var0, IsoZombie var1) {
      if (PlayerToAddressMap.containsKey(var0)) {
         sendObjectChange(var0, "reanimatedID", "ID", (double)var1.OnlineID);
      }
   }

    static void receiveSyncSafehouse(ByteBuffer var0, UdpConnection var1, short var2) {
    SyncSafehousePacket var3 = std::make_shared<SyncSafehousePacket>();
      var3.parse(var0, var1);
      if (var3.validate(var1)) {
         var3.process();
         sendSafehouse(var3, var1);
         if (ChatServer.isInited()) {
            if (var3.shouldCreateChat) {
               ChatServer.getInstance().createSafehouseChat(var3.safehouse.getId());
            }

            if (var3.remove) {
               ChatServer.getInstance().removeSafehouseChat(var3.safehouse.getId());
            } else {
               ChatServer.getInstance().syncSafehouseChatMembers(var3.safehouse.getId(), var3.ownerUsername, var3.safehouse.getPlayers());
            }
         }
      }
   }

    static void receiveKickOutOfSafehouse(ByteBuffer var0, UdpConnection var1, short var2) {
      try {
    IsoPlayer var3 = IDToPlayerMap.get(var0.getShort());
         if (var3 == nullptr) {
            return;
         }

    IsoPlayer var4 = var1.players[0];
         if (var4 == nullptr) {
            return;
         }

    SafeHouse var5 = SafeHouse.hasSafehouse(var4);
         if (var5 == nullptr) {
            return;
         }

         if (!var5.isOwner(var4)) {
            return;
         }

         if (!var5.playerAllowed(var3)) {
            return;
         }

    UdpConnection var6 = getConnectionFromPlayer(var3);
         if (var6 == nullptr) {
            return;
         }

    ByteBufferWriter var7 = var6.startPacket();
         PacketType.KickOutOfSafehouse.doPacket(var7);
         var7.putByte((byte)var3.PlayerIndex);
         var7.putFloat(var5.getX() - 1);
         var7.putFloat(var5.getY() - 1);
         var7.putFloat(0.0F);
         PacketType.KickOutOfSafehouse.send(var6);
         if (var3.getNetworkCharacterAI() != nullptr) {
            var3.getNetworkCharacterAI().resetSpeedLimiter();
         }

         if (var3.isAsleep()) {
            var3.setAsleep(false);
            var3.setAsleepTime(0.0F);
            sendWakeUpPlayer(var3, nullptr);
         }
      } catch (Exception var8) {
         DebugLog.Multiplayer.printException(var8, "ReceiveKickOutOfSafehouse: failed", LogSeverity.Error);
      }
   }

    static void sendSafehouse(SyncSafehousePacket var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var1 == nullptr || var3.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.SyncSafehouse.doPacket(var4);
            var0.write(var4);
            PacketType.SyncSafehouse.send(var3);
         }
      }
   }

    static void receiveRadioServerData(ByteBuffer var0, UdpConnection var1, short var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.RadioServerData.doPacket(var3);
      ZomboidRadio.getInstance().WriteRadioServerDataPacket(var3);
      PacketType.RadioServerData.send(var1);
   }

    static void receiveRadioDeviceDataState(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
      if (var3 == 1) {
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
         if (var8 != nullptr && var7 >= 0 && var7 < var8.getObjects().size()) {
    IsoObject var9 = (IsoObject)var8.getObjects().get(var7);
            if (dynamic_cast<IsoWaveSignal*>(var9) != nullptr) {
    DeviceData var10 = ((IsoWaveSignal)var9).getDeviceData();
               if (var10 != nullptr) {
                  try {
                     var10.receiveDeviceDataStatePacket(var0, nullptr);
                  } catch (Exception var14) {
                     System.out.print(var14.getMessage());
                  }
               }
            }
         }
      } else if (var3 == 0) {
    uint8_t var15 = var0.get();
    IsoPlayer var17 = getPlayerFromConnection(var1, var15);
    uint8_t var19 = var0.get();
         if (var17 != nullptr) {
    Radio var21 = nullptr;
            if (var19 == 1 && var17.getPrimaryHandItem() instanceof Radio) {
               var21 = (Radio)var17.getPrimaryHandItem();
            }

            if (var19 == 2 && var17.getSecondaryHandItem() instanceof Radio) {
               var21 = (Radio)var17.getSecondaryHandItem();
            }

            if (var21 != nullptr && var21.getDeviceData() != nullptr) {
               try {
                  var21.getDeviceData().receiveDeviceDataStatePacket(var0, var1);
               } catch (Exception var13) {
                  System.out.print(var13.getMessage());
               }
            }
         }
      } else if (var3 == 2) {
    short var16 = var0.getShort();
    short var18 = var0.getShort();
    BaseVehicle var20 = VehicleManager.instance.getVehicleByID(var16);
         if (var20 != nullptr) {
    VehiclePart var22 = var20.getPartByIndex(var18);
            if (var22 != nullptr) {
    DeviceData var23 = var22.getDeviceData();
               if (var23 != nullptr) {
                  try {
                     var23.receiveDeviceDataStatePacket(var0, nullptr);
                  } catch (Exception var12) {
                     System.out.print(var12.getMessage());
                  }
               }
            }
         }
      }
   }

   public static void sendIsoWaveSignal(
      long var0, int var2, int var3, int var4, std::string var5, std::string var6, std::string var7, float var8, float var9, float var10, int var11, boolean var12
   ) {
    WaveSignal var13 = std::make_shared<WaveSignal>();
      var13.set(var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12);

      for (int var14 = 0; var14 < udpEngine.connections.size(); var14++) {
    UdpConnection var15 = (UdpConnection)udpEngine.connections.get(var14);
         if (var0 != var15.getConnectedGUID()) {
    ByteBufferWriter var16 = var15.startPacket();
            PacketType.WaveSignal.doPacket(var16);
            var13.write(var16);
            PacketType.WaveSignal.send(var15);
         }
      }
   }

    static void receiveWaveSignal(ByteBuffer var0, UdpConnection var1, short var2) {
    WaveSignal var3 = std::make_shared<WaveSignal>();
      var3.parse(var0, var1);
      var3.process(var1);
   }

    static void receivePlayerListensChannel(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    bool var4 = var0.get() == 1;
    bool var5 = var0.get() == 1;
      ZomboidRadio.getInstance().PlayerListensChannel(var3, var4, var5);
   }

    static void sendAlarm(int var0, int var1) {
      DebugLog.log(DebugType.Multiplayer, "SendAlarm at [ " + var0 + " , " + var1 + " ]");

      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
    IsoPlayer var4 = getAnyPlayerFromConnection(var3);
         if (var4 != nullptr) {
    ByteBufferWriter var5 = var3.startPacket();
            PacketType.AddAlarm.doPacket(var5);
            var5.putInt(var0);
            var5.putInt(var1);
            PacketType.AddAlarm.send(var3);
         }
      }
   }

    static bool isSpawnBuilding(BuildingDef var0) {
      return SpawnPoints.instance.isSpawnBuilding(var0);
   }

    static void setFastForward(bool var0) {
      if (var0 != bFastForward) {
         bFastForward = var0;
         syncClock();
      }
   }

    static void receiveSendCustomColor(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    float var7 = var0.getFloat();
    float var8 = var0.getFloat();
    float var9 = var0.getFloat();
    float var10 = var0.getFloat();
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var11 != nullptr && var6 < var11.getObjects().size()) {
    IsoObject var12 = (IsoObject)var11.getObjects().get(var6);
         if (var12 != nullptr) {
            var12.setCustomColor(var7, var8, var9, var10);
         }
      }

      for (int var15 = 0; var15 < udpEngine.connections.size(); var15++) {
    UdpConnection var13 = (UdpConnection)udpEngine.connections.get(var15);
         if (var13.RelevantTo(var3, var4) && (var1 != nullptr && var13.getConnectedGUID() != var1.getConnectedGUID() || var1 == nullptr)) {
    ByteBufferWriter var14 = var13.startPacket();
            PacketType.SendCustomColor.doPacket(var14);
            var14.putInt(var3);
            var14.putInt(var4);
            var14.putInt(var5);
            var14.putInt(var6);
            var14.putFloat(var7);
            var14.putFloat(var8);
            var14.putFloat(var9);
            var14.putFloat(var10);
            PacketType.SendCustomColor.send(var13);
         }
      }
   }

    static void receiveSyncFurnace(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var6 == nullptr) {
         DebugLog.log("receiveFurnaceChange: square is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
      } else {
    BSFurnace var7 = nullptr;

         for (int var8 = 0; var8 < var6.getObjects().size(); var8++) {
            if (var6.getObjects().get(var8) instanceof BSFurnace) {
               var7 = (BSFurnace)var6.getObjects().get(var8);
               break;
            }
         }

         if (var7 == nullptr) {
            DebugLog.log("receiveFurnaceChange: furnace is nullptr x,y,z=" + var3 + "," + var4 + "," + var5);
         } else {
            var7.fireStarted = var0.get() == 1;
            var7.fuelAmount = var0.getFloat();
            var7.fuelDecrease = var0.getFloat();
            var7.heat = var0.getFloat();
            var7.sSprite = GameWindow.ReadString(var0);
            var7.sLitSprite = GameWindow.ReadString(var0);
            sendFuranceChange(var7, var1);
         }
      }
   }

    static void receiveVehicles(ByteBuffer var0, UdpConnection var1, short var2) {
      VehicleManager.instance.serverPacket(var0, var1, var2);
   }

    static void receiveTimeSync(ByteBuffer var0, UdpConnection var1, short var2) {
      GameTime.receiveTimeSync(var0, var1);
   }

    static void sendFuranceChange(BSFurnace var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var3.RelevantTo(var0.square.x, var0.square.y) && (var1 != nullptr && var3.getConnectedGUID() != var1.getConnectedGUID() || var1 == nullptr)) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.SyncFurnace.doPacket(var4);
            var4.putInt(var0.square.x);
            var4.putInt(var0.square.y);
            var4.putInt(var0.square.z);
            var4.putByte((byte)(var0.isFireStarted() ? 1 : 0));
            var4.putFloat(var0.getFuelAmount());
            var4.putFloat(var0.getFuelDecrease());
            var4.putFloat(var0.getHeat());
            GameWindow.WriteString(var4.bb, var0.sSprite);
            GameWindow.WriteString(var4.bb, var0.sLitSprite);
            PacketType.SyncFurnace.send(var3);
         }
      }
   }

    static void receiveUserlog(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::vector var4 = ServerWorldDatabase.instance.getUserlog(var3);

      for (int var5 = 0; var5 < udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)udpEngine.connections.get(var5);
         if (var6.getConnectedGUID() == var1.getConnectedGUID()) {
    ByteBufferWriter var7 = var6.startPacket();
            PacketType.Userlog.doPacket(var7);
            var7.putInt(var4.size());
            var7.putUTF(var3);

            for (int var8 = 0; var8 < var4.size(); var8++) {
    Userlog var9 = (Userlog)var4.get(var8);
               var7.putInt(UserlogType.FromString(var9.getType()).index());
               var7.putUTF(var9.getText());
               var7.putUTF(var9.getIssuedBy());
               var7.putInt(var9.getAmount());
               var7.putUTF(var9.getLastUpdate());
            }

            PacketType.Userlog.send(var6);
         }
      }
   }

    static void receiveAddUserlog(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
      ServerWorldDatabase.instance.addUserlog(var3, UserlogType.FromString(var4), var5, var1.username, 1);
      LoggerManager.getLogger("admin").write(var1.username + " added log on user " + var3 + ", log: " + var5);
   }

    static void receiveRemoveUserlog(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
      ServerWorldDatabase.instance.removeUserLog(var3, var4, var5);
      LoggerManager.getLogger("admin").write(var1.username + " removed log on user " + var3 + ", type:" + var4 + ", log: " + var5);
   }

    static void receiveAddWarningPoint(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
      ServerWorldDatabase.instance.addWarningPoint(var3, var4, var5, var1.username);
      LoggerManager.getLogger("admin").write(var1.username + " added " + var5 + " warning point(s) on " + var3 + ", reason:" + var4);

      for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
         if (var7.username == var3)) {
    ByteBufferWriter var8 = var7.startPacket();
            PacketType.WorldMessage.doPacket(var8);
            var8.putUTF(var1.username);
            var8.putUTF(" gave you " + var5 + " warning point(s), reason: " + var4 + " ");
            PacketType.WorldMessage.send(var7);
         }
      }
   }

    static void sendAdminMessage(const std::string& var0, int var1, int var2, int var3) {
      for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
         if (canSeePlayerStats(var5)) {
    ByteBufferWriter var6 = var5.startPacket();
            PacketType.MessageForAdmin.doPacket(var6);
            var6.putUTF(var0);
            var6.putInt(var1);
            var6.putInt(var2);
            var6.putInt(var3);
            PacketType.MessageForAdmin.send(var5);
         }
      }
   }

    static void receiveWakeUpPlayer(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoPlayer var3 = getPlayerFromConnection(var1, var0.getShort());
      if (var3 != nullptr) {
         var3.setAsleep(false);
         var3.setAsleepTime(0.0F);
         sendWakeUpPlayer(var3, var1);
      }
   }

    static void sendWakeUpPlayer(IsoPlayer var0, UdpConnection var1) {
      for (int var2 = 0; var2 < udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)udpEngine.connections.get(var2);
         if (var1 == nullptr || var3.getConnectedGUID() != var1.getConnectedGUID()) {
    ByteBufferWriter var4 = var3.startPacket();
            PacketType.WakeUpPlayer.doPacket(var4);
            var4.putShort(var0.getOnlineID());
            PacketType.WakeUpPlayer.send(var3);
         }
      }
   }

    static void receiveGetDBSchema(ByteBuffer var0, UdpConnection var1, short var2) {
    DBSchema var3 = ServerWorldDatabase.instance.getDBSchema();

      for (int var4 = 0; var4 < udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)udpEngine.connections.get(var4);
         if (var1 != nullptr && var5.getConnectedGUID() == var1.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
            PacketType.GetDBSchema.doPacket(var6);
    std::unordered_map var7 = var3.getSchema();
            var6.putInt(var7.size());

            for (std::string var9 : var7.keySet()) {
    std::unordered_map var10 = (std::unordered_map)var7.get(var9);
               var6.putUTF(var9);
               var6.putInt(var10.size());

               for (std::string var12 : var10.keySet()) {
                  var6.putUTF(var12);
                  var6.putUTF((std::string)var10.get(var12));
               }
            }

            PacketType.GetDBSchema.send(var5);
         }
      }
   }

    static void receiveGetTableResult(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
    std::string var4 = GameWindow.ReadString(var0);
    std::vector var5 = ServerWorldDatabase.instance.getTableResult(var4);

      for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
         if (var1 != nullptr && var7.getConnectedGUID() == var1.getConnectedGUID()) {
            doTableResult(var7, var4, var5, 0, var3);
         }
      }
   }

    static void doTableResult(UdpConnection var0, const std::string& var1, std::vector<DBResult> var2, int var3, int var4) {
    int var5 = 0;
    bool var6 = true;
    ByteBufferWriter var7 = var0.startPacket();
      PacketType.GetTableResult.doPacket(var7);
      var7.putInt(var3);
      var7.putUTF(var1);
      if (var2.size() < var4) {
         var7.putInt(var2.size());
      } else if (var2.size() - var3 < var4) {
         var7.putInt(var2.size() - var3);
      } else {
         var7.putInt(var4);
      }

      for (int var8 = var3; var8 < var2.size(); var8++) {
    DBResult var9 = nullptr;

         try {
            var9 = (DBResult)var2.get(var8);
            var7.putInt(var9.getColumns().size());
         } catch (Exception var12) {
            var12.printStackTrace();
         }

         for (std::string var11 : var9.getColumns()) {
            var7.putUTF(var11);
            var7.putUTF((std::string)var9.getValues().get(var11));
         }

         if (++var5 >= var4) {
            var6 = false;
            PacketType.GetTableResult.send(var0);
            doTableResult(var0, var1, var2, var3 + var5, var4);
            break;
         }
      }

      if (var6) {
         PacketType.GetTableResult.send(var0);
      }
   }

    static void receiveExecuteQuery(ByteBuffer var0, UdpConnection var1, short var2) {
      if (var1.accessLevel == 32) {
         try {
    std::string var3 = GameWindow.ReadString(var0);
    KahluaTable var4 = LuaManager.platform.newTable();
            var4.load(var0, 195);
            ServerWorldDatabase.instance.executeQuery(var3, var4);
         } catch (Throwable var5) {
            var5.printStackTrace();
         }
      }
   }

    static void receiveSendFactionInvite(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
    IsoPlayer var6 = getPlayerByUserName(var5);
      if (var6 != nullptr) {
    long var7 = IDToAddressMap.get(var6.getOnlineID());

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() == var7) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.SendFactionInvite.doPacket(var10);
               var10.putUTF(var3);
               var10.putUTF(var4);
               PacketType.SendFactionInvite.send(var9);
               break;
            }
         }
      }
   }

    static void receiveAcceptedFactionInvite(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    IsoPlayer var5 = getPlayerByUserName(var4);
    long var6 = IDToAddressMap.get(var5.getOnlineID());

      for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
         if (var8.getConnectedGUID() == var6) {
    Faction var9 = Faction.getPlayerFaction(var8.username);
            if (var9 != nullptr && var9.getName() == var3)) {
    ByteBufferWriter var10 = var8.startPacket();
               PacketType.AcceptedFactionInvite.doPacket(var10);
               var10.putUTF(var3);
               var10.putUTF(var4);
               PacketType.AcceptedFactionInvite.send(var8);
            }
         }
      }
   }

    static void receiveViewTickets(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
      if ("" == var3)) {
         var3 = nullptr;
      }

      sendTickets(var3, var1);
   }

    static void sendTickets(const std::string& var0, UdpConnection var1) {
    std::vector var2 = ServerWorldDatabase.instance.getTickets(var0);

      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         if (var4.getConnectedGUID() == var1.getConnectedGUID()) {
    ByteBufferWriter var5 = var4.startPacket();
            PacketType.ViewTickets.doPacket(var5);
            var5.putInt(var2.size());

            for (int var6 = 0; var6 < var2.size(); var6++) {
    DBTicket var7 = (DBTicket)var2.get(var6);
               var5.putUTF(var7.getAuthor());
               var5.putUTF(var7.getMessage());
               var5.putInt(var7.getTicketID());
               if (var7.getAnswer() != nullptr) {
                  var5.putByte((byte)1);
                  var5.putUTF(var7.getAnswer().getAuthor());
                  var5.putUTF(var7.getAnswer().getMessage());
                  var5.putInt(var7.getAnswer().getTicketID());
               } else {
                  var5.putByte((byte)0);
               }
            }

            PacketType.ViewTickets.send(var4);
            break;
         }
      }
   }

    static void receiveAddTicket(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
      if (var5 == -1) {
         sendAdminMessage("user " + var3 + " added a ticket <LINE> <LINE> " + var4, -1, -1, -1);
      }

      ServerWorldDatabase.instance.addTicket(var3, var4, var5);
      sendTickets(var3, var1);
   }

    static void receiveRemoveTicket(ByteBuffer var0, UdpConnection var1, short var2) {
    int var3 = var0.getInt();
      ServerWorldDatabase.instance.removeTicket(var3);
      sendTickets(nullptr, var1);
   }

    static bool sendItemListNet(UdpConnection var0, IsoPlayer var1, std::vector<InventoryItem> var2, IsoPlayer var3, const std::string& var4, const std::string& var5) {
      for (int var6 = 0; var6 < udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)udpEngine.connections.get(var6);
         if (var0 == nullptr || var7 != var0) {
            if (var3 != nullptr) {
    bool var8 = false;

               for (int var9 = 0; var9 < var7.players.length; var9++) {
    IsoPlayer var10 = var7.players[var9];
                  if (var10 != nullptr && var10 == var3) {
                     var8 = true;
                     break;
                  }
               }

               if (!var8) {
                  continue;
               }
            }

    ByteBufferWriter var12 = var7.startPacket();
            PacketType.SendItemListNet.doPacket(var12);
            var12.putByte((byte)(var3 != nullptr ? 1 : 0));
            if (var3 != nullptr) {
               var12.putShort(var3.getOnlineID());
            }

            var12.putByte((byte)(var1 != nullptr ? 1 : 0));
            if (var1 != nullptr) {
               var12.putShort(var1.getOnlineID());
            }

            GameWindow.WriteString(var12.bb, var4);
            var12.putByte((byte)(var5 != nullptr ? 1 : 0));
            if (var5 != nullptr) {
               GameWindow.WriteString(var12.bb, var5);
            }

            try {
               CompressIdenticalItems.save(var12.bb, var2, nullptr);
            } catch (Exception var11) {
               var11.printStackTrace();
               var7.cancelPacket();
    return false;
            }

            PacketType.SendItemListNet.send(var7);
         }
      }

    return true;
   }

    static void receiveSendItemListNet(ByteBuffer var0, UdpConnection var1, short var2) {
    IsoPlayer var3 = nullptr;
      if (var0.get() == 1) {
         var3 = IDToPlayerMap.get(var0.getShort());
      }

    IsoPlayer var4 = nullptr;
      if (var0.get() == 1) {
         var4 = IDToPlayerMap.get(var0.getShort());
      }

    std::string var5 = GameWindow.ReadString(var0);
    std::string var6 = nullptr;
      if (var0.get() == 1) {
         var6 = GameWindow.ReadString(var0);
      }

    std::vector var7 = new std::vector();

      try {
         CompressIdenticalItems.load(var0, 195, var7, nullptr);
      } catch (Exception var9) {
         var9.printStackTrace();
      }

      if (var3 == nullptr) {
         LuaEventManager.triggerEvent("OnReceiveItemListNet", var4, var7, var3, var5, var6);
      } else {
         sendItemListNet(var1, var4, var7, var3, var5, var6);
      }
   }

    static void sendPlayerDamagedByCarCrash(IsoPlayer var0, float var1) {
    UdpConnection var2 = getConnectionFromPlayer(var0);
      if (var2 != nullptr) {
    ByteBufferWriter var3 = var2.startPacket();
         PacketType.PlayerDamageFromCarCrash.doPacket(var3);
         var3.putFloat(var1);
         PacketType.PlayerDamageFromCarCrash.send(var2);
      }
   }

    static void receiveClimateManagerPacket(ByteBuffer var0, UdpConnection var1, short var2) {
    ClimateManager var3 = ClimateManager.getInstance();
      if (var3 != nullptr) {
         try {
            var3.receiveClimatePacket(var0, var1);
         } catch (Exception var5) {
            var5.printStackTrace();
         }
      }
   }

    static void receivePassengerMap(ByteBuffer var0, UdpConnection var1, short var2) {
      PassengerMap.serverReceivePacket(var0, var1);
   }

    static void receiveIsoRegionClientRequestFullUpdate(ByteBuffer var0, UdpConnection var1, short var2) {
      IsoRegions.receiveClientRequestFullDataChunks(var0, var1);
   }

    static std::string isWorldVersionUnsupported() {
      File var0 = std::make_shared<File>(
         ZomboidFileSystem.instance.getSaveDir() + File.separator + "Multiplayer" + File.separator + ServerName + File.separator + "map_t.bin"
      );
      if (var0.exists()) {
         DebugLog.log("checking server WorldVersion in map_t.bin");

         try {
    std::string var7;
            try (
    FileInputStream var1 = std::make_shared<FileInputStream>(var0);
    DataInputStream var2 = std::make_shared<DataInputStream>(var1);
            ) {
    uint8_t var3 = var2.readByte();
    uint8_t var4 = var2.readByte();
    uint8_t var5 = var2.readByte();
    uint8_t var6 = var2.readByte();
               if (var3 == 71 && var4 == 77 && var5 == 84 && var6 == 77) {
    int var14 = var2.readInt();
                  if (var14 > 195) {
                     return "The server savefile appears to be from a newer version of the game and cannot be loaded.";
                  }

                  if (var14 > 143) {
    return nullptr;
                  }

                  return "The server savefile appears to be from a pre-animations version of the game and cannot be loaded.\nDue to the extent of changes required to implement animations, saves from earlier versions are not compatible.";
               }

               var7 = "The server savefile appears to be from an old version of the game and cannot be loaded.";
            }

    return var7;
         } catch (Exception var13) {
            var13.printStackTrace();
         }
      } else {
         DebugLog.log("map_t.bin does not exist, cannot determine the server's WorldVersion.  This is ok the first time a server is started.");
      }

    return nullptr;
   }

    std::string getPoisonousBerry() {
      return this.poisonousBerry;
   }

    void setPoisonousBerry(const std::string& var1) {
      this.poisonousBerry = var1;
   }

    std::string getPoisonousMushroom() {
      return this.poisonousMushroom;
   }

    void setPoisonousMushroom(const std::string& var1) {
      this.poisonousMushroom = var1;
   }

    std::string getDifficulty() {
      return this.difficulty;
   }

    void setDifficulty(const std::string& var1) {
      this.difficulty = var1;
   }

    static void transmitBrokenGlass(IsoGridSquare var0) {
      for (int var1 = 0; var1 < udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)udpEngine.connections.get(var1);

         try {
            if (var2.RelevantTo(var0.getX(), var0.getY())) {
    ByteBufferWriter var3 = var2.startPacket();
               PacketType.AddBrokenGlass.doPacket(var3);
               var3.putInt((short)var0.getX());
               var3.putInt((short)var0.getY());
               var3.putInt((short)var0.getZ());
               PacketType.AddBrokenGlass.send(var2);
            }
         } catch (Throwable var4) {
            var2.cancelPacket();
            ExceptionLogger.logException(var4);
         }
      }
   }

    static bool isServerDropPackets() {
      return droppedPackets > 0;
   }

    static void receiveSyncPerks(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoPlayer var7 = getPlayerFromConnection(var1, var3);
      if (var7 != nullptr) {
         var7.remoteSneakLvl = var4;
         var7.remoteStrLvl = var5;
         var7.remoteFitLvl = var6;

         for (int var8 = 0; var8 < udpEngine.connections.size(); var8++) {
    UdpConnection var9 = (UdpConnection)udpEngine.connections.get(var8);
            if (var9.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var10 = getAnyPlayerFromConnection(var1);
               if (var10 != nullptr) {
                  try {
    ByteBufferWriter var11 = var9.startPacket();
                     PacketType.SyncPerks.doPacket(var11);
                     var11.putShort(var7.OnlineID);
                     var11.putInt(var4);
                     var11.putInt(var5);
                     var11.putInt(var6);
                     PacketType.SyncPerks.send(var9);
                  } catch (Throwable var12) {
                     var1.cancelPacket();
                     ExceptionLogger.logException(var12);
                  }
               }
            }
         }
      }
   }

    static void receiveSyncWeight(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    double var4 = var0.getDouble();
    IsoPlayer var6 = getPlayerFromConnection(var1, var3);
      if (var6 != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var9 = getAnyPlayerFromConnection(var1);
               if (var9 != nullptr) {
                  try {
    ByteBufferWriter var10 = var8.startPacket();
                     PacketType.SyncWeight.doPacket(var10);
                     var10.putShort(var6.OnlineID);
                     var10.putDouble(var4);
                     PacketType.SyncWeight.send(var8);
                  } catch (Throwable var11) {
                     var1.cancelPacket();
                     ExceptionLogger.logException(var11);
                  }
               }
            }
         }
      }
   }

    static void receiveSyncEquippedRadioFreq(ByteBuffer var0, UdpConnection var1, short var2) {
    uint8_t var3 = var0.get();
    int var4 = var0.getInt();
    std::vector var5 = new std::vector();

      for (int var6 = 0; var6 < var4; var6++) {
         var5.push_back(var0.getInt());
      }

    IsoPlayer var13 = getPlayerFromConnection(var1, var3);
      if (var13 != nullptr) {
         for (int var7 = 0; var7 < udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)udpEngine.connections.get(var7);
            if (var8.getConnectedGUID() != var1.getConnectedGUID()) {
    IsoPlayer var9 = getAnyPlayerFromConnection(var1);
               if (var9 != nullptr) {
                  try {
    ByteBufferWriter var10 = var8.startPacket();
                     PacketType.SyncEquippedRadioFreq.doPacket(var10);
                     var10.putShort(var13.OnlineID);
                     var10.putInt(var4);

                     for (int var11 = 0; var11 < var5.size(); var11++) {
                        var10.putInt((int)var5.get(var11));
                     }

                     PacketType.SyncEquippedRadioFreq.send(var8);
                  } catch (Throwable var12) {
                     var1.cancelPacket();
                     ExceptionLogger.logException(var12);
                  }
               }
            }
         }
      }
   }

    static void receiveGlobalModData(ByteBuffer var0, UdpConnection var1, short var2) {
      GlobalModData.instance.receive(var0);
   }

    static void receiveGlobalModDataRequest(ByteBuffer var0, UdpConnection var1, short var2) {
      GlobalModData.instance.receiveRequest(var0, var1);
   }

    static void receiveSendSafehouseInvite(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
    IsoPlayer var6 = getPlayerByUserName(var5);
    long var7 = IDToAddressMap.get(var6.getOnlineID());
    int var8 = var0.getInt();
    int var9 = var0.getInt();
    int var10 = var0.getInt();
    int var11 = var0.getInt();

      for (int var12 = 0; var12 < udpEngine.connections.size(); var12++) {
    UdpConnection var13 = (UdpConnection)udpEngine.connections.get(var12);
         if (var13.getConnectedGUID() == var7) {
    ByteBufferWriter var14 = var13.startPacket();
            PacketType.SendSafehouseInvite.doPacket(var14);
            var14.putUTF(var3);
            var14.putUTF(var4);
            var14.putInt(var8);
            var14.putInt(var9);
            var14.putInt(var10);
            var14.putInt(var11);
            PacketType.SendSafehouseInvite.send(var13);
            break;
         }
      }
   }

    static void receiveAcceptedSafehouseInvite(ByteBuffer var0, UdpConnection var1, short var2) {
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = GameWindow.ReadString(var0);
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    int var9 = var0.getInt();
    SafeHouse var10 = SafeHouse.getSafeHouse(var6, var7, var8, var9);
      if (var10 != nullptr) {
         var10.addPlayer(var5);
      } else {
         DebugLog.log(
            "WARN: player '" + var5 + "' accepted the invitation, but the safehouse not found for x=" + var6 + " y=" + var7 + " w=" + var8 + " h=" + var9
         );
      }

      for (int var11 = 0; var11 < udpEngine.connections.size(); var11++) {
    UdpConnection var12 = (UdpConnection)udpEngine.connections.get(var11);
    ByteBufferWriter var13 = var12.startPacket();
         PacketType.AcceptedSafehouseInvite.doPacket(var13);
         var13.putUTF(var3);
         var13.putUTF(var4);
         var13.putUTF(var5);
         var13.putInt(var6);
         var13.putInt(var7);
         var13.putInt(var8);
         var13.putInt(var9);
         PacketType.AcceptedSafehouseInvite.send(var12);
      }
   }

    static void sendRadioPostSilence() {
      for (int var0 = 0; var0 < udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)udpEngine.connections.get(var0);
         if (var1.statistic.enable == 3) {
            sendShortStatistic(var1);
         }
      }
   }

    static void sendRadioPostSilence(UdpConnection var0) {
      try {
    ByteBufferWriter var1 = var0.startPacket();
         PacketType.RadioPostSilenceEvent.doPacket(var1);
         var1.putByte((byte)(ZomboidRadio.POST_RADIO_SILENCE ? 1 : 0));
         PacketType.RadioPostSilenceEvent.send(var0);
      } catch (Exception var2) {
         var2.printStackTrace();
         var0.cancelPacket();
      }
   }

    static void receiveSneezeCough(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    uint8_t var4 = var0.get();
    IsoPlayer var5 = IDToPlayerMap.get(var3);
      if (var5 != nullptr) {
    float var6 = var5.x;
    float var7 = var5.y;
    int var8 = 0;

         for (int var9 = udpEngine.connections.size(); var8 < var9; var8++) {
    UdpConnection var10 = (UdpConnection)udpEngine.connections.get(var8);
            if (var1.getConnectedGUID() != var10.getConnectedGUID() && var10.RelevantTo(var6, var7)) {
    ByteBufferWriter var11 = var10.startPacket();
               PacketType.SneezeCough.doPacket(var11);
               var11.putShort(var3);
               var11.putByte(var4);
               PacketType.SneezeCough.send(var10);
            }
         }
      }
   }

    static void receiveBurnCorpse(ByteBuffer var0, UdpConnection var1, short var2) {
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    IsoPlayer var5 = IDToPlayerMap.get(var3);
      if (var5 == nullptr) {
         DebugLog.Network.warn("Player not found by id " + var3);
      } else {
    IsoDeadBody var6 = IsoDeadBody.getDeadBody(var4);
         if (var6 == nullptr) {
            DebugLog.Network.warn("Corpse not found by id " + var4);
         } else {
    float var7 = IsoUtils.DistanceTo(var5.x, var5.y, var6.x, var6.y);
            if (var7 <= 1.8F) {
               IsoFireManager.StartFire(var6.getCell(), var6.getSquare(), true, 100);
            } else {
               DebugLog.Network.warn("Distance between player and corpse too big: " + var7);
            }
         }
      }
   }

    static void sendValidatePacket(UdpConnection var0, bool var1, bool var2, bool var3) {
    ByteBufferWriter var4 = var0.startPacket();

      try {
    ValidatePacket var5 = std::make_shared<ValidatePacket>();
         var5.setSalt(var0.validator.getSalt(), var1, var2, var3);
         PacketType.Validate.doPacket(var4);
         var5.write(var4);
         PacketType.Validate.send(var0);
         var5.log(GameClient.connection, "send-packet");
      } catch (Exception var6) {
         var0.cancelPacket();
         DebugLog.Multiplayer.printException(var6, "SendValidatePacket: failed", LogSeverity.Error);
      }
   }

    static void receiveValidatePacket(ByteBuffer var0, UdpConnection var1, short var2) {
    ValidatePacket var3 = std::make_shared<ValidatePacket>();
      var3.parse(var0, var1);
      var3.log(GameClient.connection, "receive-packet");
      if (var3.isConsistent()) {
         var3.process(var1);
      }
   }
}
} // namespace network
} // namespace zombie
