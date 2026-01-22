#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/javafmod.h"
#if __has_include(<absl/container/flat_hash_map.h>)
#  include <absl/container/flat_hash_map.h>
#  define SHORT_HASH_MAP absl::flat_hash_map
#elif __has_include(<boost/unordered_map.hpp>)
#  include <boost/unordered_map.hpp>
#  define SHORT_HASH_MAP boost::unordered_map
#else
#  include <unordered_map>
#  define SHORT_HASH_MAP std::unordered_map
#endif
#include <vector>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/SharedDescriptors/Descriptor.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/WorldSoundManager/WorldSound.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/IsoZombie/ZombieSound.h"
#include "zombie/characters/NetworkTeleport.h"
#include "zombie/characters/NetworkZombieVariables.h"
#include "zombie/characters/Safety.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/commands/serverCommands/LogCommand.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferReader.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/UdpEngine.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/raknet/VoiceManagerData.h"
#include "zombie/core/raknet/VoiceManagerData/RadioData.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/core/znet/SteamUser.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/ZNet.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/erosion/ErosionConfig.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/globalObjects/CGlobalObjectNetwork.h"
#include "zombie/inventory/CompressIdenticalItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridOcclusionData.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectSyncRequests.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/ObjectsSyncRequests.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/BSFurnace.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient/1.h"
#include "zombie/network/GameClient/RequestState.h"
#include "zombie/network/NetworkVariables/ThumpType.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/Userlog/UserlogType.h"
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
#include "zombie/network/packets/PlayerPacket/l_send.h"
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
#include "zombie/network/packets/VehicleAuthorizationPacket.h"
#include "zombie/network/packets/WaveSignal.h"
#include "zombie/network/packets/hit/HitCharacterPacket.h"
#include "zombie/network/packets/hit/PlayerHitPlayerPacket.h"
#include "zombie/network/packets/hit/PlayerHitSquarePacket.h"
#include "zombie/network/packets/hit/PlayerHitVehiclePacket.h"
#include "zombie/network/packets/hit/PlayerHitZombiePacket.h"
#include "zombie/network/packets/hit/VehicleHitPlayerPacket.h"
#include "zombie/network/packets/hit/VehicleHitZombiePacket.h"
#include "zombie/network/packets/hit/ZombieHitPlayerPacket.h"
#include "zombie/popman/MPDebugInfo.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/popman/ZombieCountOptimiser.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/util/AddCoopPlayer.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
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


class GameClient {
public:
    static const GameClient instance = std::make_shared<GameClient>();
    static const int DEFAULT_PORT = 16361;
    static bool bClient = false;
    static UdpConnection connection;
    static int count = 0;
    static std::string ip = "localhost";
    static std::string ServerName = "";
    static std::string localIP = "";
    static std::string password = "testpass";
    static bool allChatMuted = false;
    static std::string username = "lemmy101";
    static std::string serverPassword = "";
    static bool useSteamRelay = false;
    UdpEngine udpEngine;
    uint8_t ID = -1;
    float timeSinceKeepAlive = 0.0F;
    UpdateLimit itemSendFrequency = std::make_shared<UpdateLimit>(3000L);
    static int port = GameServer.DEFAULT_PORT;
    bool bPlayerConnectSent = false;
    bool bClientStarted = false;
    int ResetID = 0;
    bool bConnectionLost = false;
    static std::string checksum = "";
    static bool checksumValid = false;
   public static List<int64_t> pingsList = std::make_unique<std::vector<>>();
    static std::string GameMap;
    static bool bFastForward;
   public static const ClientServerMap[] loadedCells = new ClientServerMap[4];
    int DEBUG_PING = 5;
    IsoObjectSyncRequests objectSyncReq = std::make_shared<IsoObjectSyncRequests>();
    ObjectsSyncRequests worldObjectsSyncReq = std::make_shared<ObjectsSyncRequests>(true);
    static bool bCoopInvite;
   private std::vector<IsoPlayer> connectedPlayers = std::make_unique<std::vector<>>();
    static bool isPaused = false;
   private const std::vector<IsoPlayer> players = std::make_unique<std::vector<>>();
    bool idMapDirty = true;
    static const int sendZombieWithoutNeighbor = 4000;
    static const int sendZombieWithNeighbor = 200;
    const UpdateLimit sendZombieTimer = std::make_shared<UpdateLimit>(4000L);
    const UpdateLimit sendZombieRequestsTimer = std::make_shared<UpdateLimit>(200L);
    const UpdateLimit UpdateChannelsRoamingLimit = std::make_shared<UpdateLimit>(3010L);
    long disconnectTime = System.currentTimeMillis();
    static const long disconnectTimeLimit = 10000L;
    static long steamID = 0L;
   public static const Map<int16_t, Vector2> positions = new std::unordered_map<>(ServerOptions.getInstance().getMaxPlayers());
    int safehouseUpdateTimer = 0;
    bool delayPacket = false;
   private const std::vector<int> delayedDisconnect = std::make_unique<std::vector<>>();
    static TShortArrayList tempShortList = std::make_shared<TShortArrayList>();
   private volatile RequestState request;
    KahluaTable ServerSpawnRegions = nullptr;
   static const ConcurrentLinkedQueue<ZomboidNetData> MainLoopNetDataQ = std::make_unique<ConcurrentLinkedQueue<>>();
   static const std::vector<ZomboidNetData> MainLoopNetData = std::make_unique<std::vector<>>();
   static const std::vector<ZomboidNetData> LoadingMainLoopNetData = std::make_unique<std::vector<>>();
   static const std::vector<ZomboidNetData> DelayedCoopNetData = std::make_unique<std::vector<>>();
    bool bConnected = false;
    UpdateLimit PlayerUpdateReliableLimit = std::make_shared<UpdateLimit>(2000L);
    int TimeSinceLastUpdate = 0;
    ByteBuffer staticTest = ByteBuffer.allocate(20000);
    ByteBufferWriter wr = std::make_shared<ByteBufferWriter>(this.staticTest);
    long StartHeartMilli = 0L;
    long EndHeartMilli = 0L;
    int ping = 0;
    static float ServerPredictedAhead = 0.0F;
   public static const std::unordered_map<int16_t, IsoPlayer> IDToPlayerMap = std::make_unique<std::unordered_map<>>();
   public static const TShortObjectHashMap<IsoZombie> IDToZombieMap = std::make_unique<TShortObjectHashMap>();
    static bool bIngame;
    static bool askPing = false;
   public const std::vector<std::string> ServerMods = std::make_unique<std::vector<>>();
    ErosionConfig erosionConfig;
    static Calendar startAuth = nullptr;
    static std::string poisonousBerry = nullptr;
    static std::string poisonousMushroom = nullptr;
   const std::vector<ZomboidNetData> incomingNetData = std::make_unique<std::vector<>>();
   private const std::unordered_map<ItemContainer, std::vector<InventoryItem>> itemsToSend = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<ItemContainer, std::vector<InventoryItem>> itemsToSendRemove = std::make_unique<std::unordered_map<>>();
    KahluaTable dbSchema;

    IsoPlayer getPlayerByOnlineID(short var1) {
      return IDToPlayerMap.get(var1);
   }

    void init() {
      LoadingMainLoopNetData.clear();
      MainLoopNetDataQ.clear();
      MainLoopNetData.clear();
      DelayedCoopNetData.clear();
      bIngame = false;
      IDToPlayerMap.clear();
      IDToZombieMap.clear();
      pingsList.clear();
      this.itemsToSend.clear();
      this.itemsToSendRemove.clear();
      IDToZombieMap.setAutoCompactionFactor(0.0F);
      this.bPlayerConnectSent = false;
      this.bConnectionLost = false;
      this.delayedDisconnect.clear();
      GameWindow.bServerDisconnected = false;
      this.ServerSpawnRegions = nullptr;
      this.startClient();
   }

    void startClient() {
      if (this.bClientStarted) {
         this.udpEngine.Connect(ip, port, serverPassword, useSteamRelay);
      } else {
         try {
            this.udpEngine = std::make_shared<UdpEngine>(Rand.Next(10000) + 12345, 0, 1, nullptr, false);
            if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
               this.udpEngine.Connect("127.0.0.1", CoopMaster.instance.getServerPort(), serverPassword, false);
            } else {
               this.udpEngine.Connect(ip, port, serverPassword, useSteamRelay);
            }

            this.bClientStarted = true;
         } catch (Exception var2) {
            DebugLog.Network.printException(var2, "Exception thrown during GameClient.startClient.", LogSeverity.Error);
         }
      }
   }

    static void receiveStatistic(ByteBuffer var0, short var1) {
      try {
    long var2 = var0.getLong();
    ByteBufferWriter var4 = connection.startPacket();
         PacketType.Statistic.doPacket(var4);
         var4.putLong(var2);
         MPStatisticClient.getInstance().send(var4);
         PacketType.Statistic.send(connection);
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

    static void receiveStatisticRequest(ByteBuffer var0, short var1) {
      try {
         MPStatistic.getInstance().setStatisticTable(var0);
      } catch (IOException var3) {
         var3.printStackTrace();
      }

      LuaEventManager.triggerEvent("OnServerStatisticReceived");
   }

    static void receivePlayerUpdate(ByteBuffer var0, short var1) {
    PlayerPacket var2 = l_receive.playerPacket;
      var2.parse(var0, connection);

      try {
    IsoPlayer var3 = IDToPlayerMap.get(var2.id);
         if (var3 == nullptr) {
    PlayerDataRequestPacket var4 = std::make_shared<PlayerDataRequestPacket>();
            var4.set(var2.id);
    ByteBufferWriter var5 = connection.startPacket();
            PacketType.PlayerDataRequest.doPacket(var5);
            var4.write(var5);
            PacketType.PlayerDataRequest.send(connection);
         } else {
            var3.lastRemoteUpdate = System.currentTimeMillis();
            rememberPlayerPosition(var3, var2.realx, var2.realy);
            if (!var3.networkAI.isSetVehicleHit()) {
               var3.networkAI.parse(var2);
            }

            var3.bleedingLevel = var2.bleedingLevel;
            if (var3.getVehicle() == nullptr
               && !var2.usePathFinder
               && (
                  var3.networkAI.distance.getLength() > 7.0F
                     || IsoUtils.DistanceTo(var2.x, var2.y, var2.z, var3.x, var3.y, var3.z) > 1.0F && (int)var3.z != var2.z
               )) {
               NetworkTeleport.update(var3, var2);
               NetworkTeleport.teleport(var3, var2, 1.0F);
            }

    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var2.x, var2.y, var2.z);
            if (var7 != nullptr) {
               if (var3.isAlive() && !IsoWorld.instance.CurrentCell.getObjectList().contains(var3)) {
                  IsoWorld.instance.CurrentCell.getObjectList().push_back(var3);
                  var3.setCurrent(var7);
               }
            } else if (IsoWorld.instance.CurrentCell.getObjectList().contains(var3)) {
               var3.removeFromWorld();
               var3.removeFromSquare();
            }
         }
      } catch (Exception var6) {
         var6.printStackTrace();
      }
   }

    static void receiveZombieSimulation(ByteBuffer var0, short var1) {
      NetworkZombieSimulator.getInstance().clear();
    bool var2 = var0.get() == 1;
      if (var2) {
         instance.sendZombieTimer.setUpdatePeriod(200L);
      } else {
         instance.sendZombieTimer.setUpdatePeriod(4000L);
      }

    short var3 = var0.getShort();

      for (short var4 = 0; var4 < var3; var4++) {
    short var5 = var0.getShort();
    IsoZombie var6 = (IsoZombie)IDToZombieMap.get(var5);
         if (var6 != nullptr) {
            VirtualZombieManager.instance.removeZombieFromWorld(var6);
         }
      }

    short var7 = var0.getShort();

      for (short var8 = 0; var8 < var7; var8++) {
    short var9 = var0.getShort();
         NetworkZombieSimulator.getInstance().push_back(var9);
      }

      NetworkZombieSimulator.getInstance().added();
      NetworkZombieSimulator.getInstance().receivePacket(var0, connection);
   }

    static void receiveZombieControl(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    short var3 = var0.getShort();
    int var4 = var0.getInt();
    IsoZombie var5 = (IsoZombie)IDToZombieMap.get(var2);
      if (var5 != nullptr) {
         NetworkZombieVariables.setInt(var5, var3, var4);
      }
   }

    void Shutdown() {
      if (this.bClientStarted) {
         this.udpEngine.Shutdown();
         this.bClientStarted = false;
      }
   }

    void update() {
      ZombieCountOptimiser.startCount();
      if (this.safehouseUpdateTimer == 0 && ServerOptions.instance.DisableSafehouseWhenPlayerConnected.getValue()) {
         this.safehouseUpdateTimer = 3000;
         SafeHouse.updateSafehousePlayersConnected();
      }

      if (this.safehouseUpdateTimer > 0) {
         this.safehouseUpdateTimer--;
      }

      for (ZomboidNetData var1 = MainLoopNetDataQ.poll(); var1 != nullptr; var1 = MainLoopNetDataQ.poll()) {
         MainLoopNetData.push_back(var1);
      }

      /* synchronized - TODO: add std::mutex */ (this.delayedDisconnect) {
         while (!this.delayedDisconnect.empty()) {
    int var2 = this.delayedDisconnect.remove(0);
            switch (var2) {
               case 17:
                  if (!SteamUtils.isSteamModeEnabled()) {
                     LuaEventManager.triggerEvent("OnConnectFailed", nullptr);
                  }
                  break;
               case 18:
                  LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_AlreadyConnected"));
               case 19:
               case 20:
               case 22:
               case 25:
               case 26:
               case 27:
               case 28:
               case 29:
               case 30:
               case 31:
               default:
                  break;
               case 21:
                  LuaEventManager.triggerEvent("OnDisconnect");
                  break;
               case 23:
                  LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_Banned"));
                  break;
               case 24:
                  LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_InvalidServerPassword"));
                  break;
               case 32:
                  LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_ConnectionLost"));
            }
         }
      }

      if (!this.bConnectionLost) {
         if (!this.bPlayerConnectSent) {
            for (int var12 = 0; var12 < MainLoopNetData.size(); var12++) {
    ZomboidNetData var15 = MainLoopNetData.get(var12);
               if (!this.gameLoadingDealWithNetData(var15)) {
                  LoadingMainLoopNetData.push_back(var15);
               }
            }

            MainLoopNetData.clear();
            WorldStreamer.instance.updateMain();
         } else {
            if (!LoadingMainLoopNetData.empty()) {
               DebugLog.log(DebugType.Network, "Processing delayed packets...");
               MainLoopNetData.addAll(0, LoadingMainLoopNetData);
               LoadingMainLoopNetData.clear();
            }

            if (!DelayedCoopNetData.empty() && IsoWorld.instance.AddCoopPlayers.empty()) {
               DebugLog.log(DebugType.Network, "Processing delayed coop packets...");
               MainLoopNetData.addAll(0, DelayedCoopNetData);
               DelayedCoopNetData.clear();
            }

    long var11 = System.currentTimeMillis();

            for (int var16 = 0; var16 < MainLoopNetData.size(); var16++) {
    ZomboidNetData var18 = MainLoopNetData.get(var16);
               if (var18.time + this.DEBUG_PING <= var11) {
                  this.mainLoopDealWithNetData(var18);
                  MainLoopNetData.remove(var16--);
               }
            }

            for (int var17 = 0; var17 < IsoWorld.instance.CurrentCell.getObjectList().size(); var17++) {
    IsoMovingObject var19 = (IsoMovingObject)IsoWorld.instance.CurrentCell.getObjectList().get(var17);
               if (dynamic_cast<IsoPlayer*>(var19) != nullptr && !((IsoPlayer)var19).isLocalPlayer() && !this.getPlayers().contains(var19)) {
                  if (Core.bDebug) {
                     DebugLog.log("Disconnected/Distant player " + ((IsoPlayer)var19).username + " in CurrentCell.getObjectList() removed");
                  }

                  IsoWorld.instance.CurrentCell.getObjectList().remove(var17--);
               }
            }

            try {
               this.sendAddedRemovedItems(false);
            } catch (Exception var6) {
               var6.printStackTrace();
               ExceptionLogger.logException(var6);
            }

            try {
               VehicleManager.instance.clientUpdate();
            } catch (Exception var5) {
               var5.printStackTrace();
            }

            if (this.UpdateChannelsRoamingLimit.Check()) {
               VoiceManager.getInstance().UpdateChannelsRoaming(connection);
            }

            this.objectSyncReq.sendRequests(connection);
            this.worldObjectsSyncReq.sendRequests(connection);
            WorldStreamer.instance.updateMain();
            MPStatisticClient.getInstance().update();
            this.timeSinceKeepAlive = this.timeSinceKeepAlive + GameTime.getInstance().getMultiplier();
            ChatManager.UpdateClient();
         }
      } else {
         if (!this.bPlayerConnectSent) {
            for (int var9 = 0; var9 < MainLoopNetData.size(); var9++) {
    ZomboidNetData var13 = MainLoopNetData.get(var9);
               this.gameLoadingDealWithNetData(var13);
            }

            MainLoopNetData.clear();
         } else {
            for (int var10 = 0; var10 < MainLoopNetData.size(); var10++) {
    ZomboidNetData var14 = MainLoopNetData.get(var10);
               if (var14.type == PacketType.Kicked) {
    std::string var3 = Translator.getText(GameWindow.ReadString(var14.buffer));
    std::string var4 = Translator.getText(GameWindow.ReadString(var14.buffer));
                  GameWindow.kickReason = var3 + " " + var4;
                  DebugLog.Multiplayer.warn("ReceiveKickedDisconnect: " + var4);
               }
            }

            MainLoopNetData.clear();
         }

         GameWindow.bServerDisconnected = true;
      }
   }

    void smashWindow(IsoWindow var1, int var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SmashWindow.doPacket(var3);
      var3.putInt(var1.square.getX());
      var3.putInt(var1.square.getY());
      var3.putInt(var1.square.getZ());
      var3.putByte((byte)var1.square.getObjects().indexOf(var1));
      var3.putByte((byte)var2);
      PacketType.SmashWindow.send(connection);
   }

    static void getCustomModData() {
    ByteBufferWriter var0 = connection.startPacket();
      PacketType.getModData.doPacket(var0);
      PacketType.getModData.send(connection);
   }

    static void receiveStitch(ByteBuffer var0, short var1) {
    Stitch var2 = std::make_shared<Stitch>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveBandage(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    int var4 = var0.getInt();
    bool var5 = var0.get() == 1;
    float var6 = var0.getFloat();
    bool var7 = var0.get() == 1;
    std::string var8 = GameWindow.ReadStringUTF(var0);
         var3.getBodyDamage().SetBandaged(var4, var5, var6, var7, var8);
      }
   }

    static void receivePingFromClient(ByteBuffer var0, short var1) {
      MPStatistics.parse(var0);
   }

    static void receiveWoundInfection(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    int var4 = var0.getInt();
    bool var5 = var0.get() == 1;
         var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4)).setInfectedWound(var5);
      }
   }

    static void receiveDisinfect(ByteBuffer var0, short var1) {
    Disinfect var2 = std::make_shared<Disinfect>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveSplint(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    int var4 = var0.getInt();
    bool var5 = var0.get() == 1;
    std::string var6 = var5 ? GameWindow.ReadStringUTF(var0) : nullptr;
    float var7 = var5 ? var0.getFloat() : 0.0F;
    BodyPart var8 = var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4));
         var8.setSplint(var5, var7);
         var8.setSplintItem(var6);
      }
   }

    static void receiveRemoveGlass(ByteBuffer var0, short var1) {
    RemoveGlass var2 = std::make_shared<RemoveGlass>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveRemoveBullet(ByteBuffer var0, short var1) {
    RemoveBullet var2 = std::make_shared<RemoveBullet>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveCleanBurn(ByteBuffer var0, short var1) {
    CleanBurn var2 = std::make_shared<CleanBurn>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveAdditionalPain(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    int var4 = var0.getInt();
    float var5 = var0.getFloat();
    BodyPart var6 = var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4));
         var6.setAdditionalPain(var6.getAdditionalPain() + var5);
      }
   }

    void delayPacket(int var1, int var2, int var3) {
      if (IsoWorld.instance != nullptr) {
         for (int var4 = 0; var4 < IsoWorld.instance.AddCoopPlayers.size(); var4++) {
    AddCoopPlayer var5 = (AddCoopPlayer)IsoWorld.instance.AddCoopPlayers.get(var4);
            if (var5.isLoadingThisSquare(var1, var2)) {
               this.delayPacket = true;
               return;
            }
         }
      }
   }

    void mainLoopDealWithNetData(ZomboidNetData var1) {
    ByteBuffer var2 = var1.buffer;
    int var3 = var2.position();
      this.delayPacket = false;
      if (var1.type == nullptr) {
         ZomboidNetDataPool.instance.discard(var1);
      } else {
         var1.type.clientPacketCount++;

         try {
            this.mainLoopHandlePacketInternal(var1, var2);
            if (this.delayPacket) {
               var2.position(var3);
               DelayedCoopNetData.push_back(var1);
               return;
            }
         } catch (Exception var5) {
            DebugLog.Network.printException(var5, "Error with packet of type: " + var1.type, LogSeverity.Error);
         }

         ZomboidNetDataPool.instance.discard(var1);
      }
   }

    void mainLoopHandlePacketInternal(ZomboidNetData var1, ByteBuffer var2) {
      if (DebugOptions.instance.Network.Client.MainLoop.getValue()) {
         var1.type.onMainLoopHandlePacketInternal(var2);
      }
   }

    static void receiveAddBrokenGlass(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 != nullptr) {
         var5.addBrokenGlass();
      }
   }

    static void receivePlayerDamageFromCarCrash(ByteBuffer var0, short var1) {
    float var2 = var0.getFloat();
      if (IsoPlayer.getInstance().getVehicle() == nullptr) {
         DebugLog.Multiplayer.error("Receive damage from car crash, can't find vehicle");
      } else {
         IsoPlayer.getInstance().getVehicle().addRandomDamageFromCrash(IsoPlayer.getInstance(), var2);
         LuaEventManager.triggerEvent("OnPlayerGetDamage", IsoPlayer.getInstance(), "CARCRASHDAMAGE", var2);
      }
   }

    static void receivePacketCounts(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
    short var4 = var0.getShort();
    long var5 = var0.getLong();
    PacketType var7 = (PacketType)PacketTypes.packetTypes.get(var4);
         if (var7 != nullptr) {
            var7.serverPacketCount = var5;
         }
      }
   }

    void requestPacketCounts() {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.PacketCounts.doPacket(var1);
      PacketType.PacketCounts.send(connection);
   }

    static bool IsClientPaused() {
    return isPaused;
   }

    static void receiveStartPause(ByteBuffer var0, short var1) {
      isPaused = true;
      LuaEventManager.triggerEvent("OnServerStartSaving");
   }

    static void receiveStopPause(ByteBuffer var0, short var1) {
      isPaused = false;
      LuaEventManager.triggerEvent("OnServerFinishSaving");
   }

    static void receiveChatMessageToPlayer(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processChatMessagePacket(var0);
   }

    static void receivePlayerConnectedToChat(ByteBuffer var0, short var1) {
      ChatManager.getInstance().setFullyConnected();
   }

    static void receivePlayerJoinChat(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processJoinChatPacket(var0);
   }

    static void receiveInvMngRemoveItem(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    InventoryItem var3 = IsoPlayer.getInstance().getInventory().getItemWithIDRecursiv(var2);
      if (var3 == nullptr) {
         DebugLog.log("ERROR: invMngRemoveItem can not find " + var2 + " item.");
      } else {
         IsoPlayer.getInstance().removeWornItem(var3);
         if (var3.getCategory() == "Clothing")) {
            LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
         }

         if (var3 == IsoPlayer.getInstance().getPrimaryHandItem()) {
            IsoPlayer.getInstance().setPrimaryHandItem(nullptr);
            LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
         } else if (var3 == IsoPlayer.getInstance().getSecondaryHandItem()) {
            IsoPlayer.getInstance().setSecondaryHandItem(nullptr);
            LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
         }

    bool var4 = IsoPlayer.getInstance().getInventory().removeItemWithIDRecurse(var2);
         if (!var4) {
            DebugLog.log("ERROR: GameClient.invMngRemoveItem can not remove item " + var2);
         }
      }
   }

    static void receiveInvMngGetItem(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    InventoryItem var3 = nullptr;

      try {
         var3 = InventoryItem.loadItem(var0, 195);
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      if (var3 != nullptr) {
         IsoPlayer.getInstance().getInventory().addItem(var3);
      }
   }

    static void receiveInvMngReqItem(ByteBuffer var0, short var1) {
    int var2 = 0;
    std::string var3 = nullptr;
      if (var0.get() == 1) {
         var3 = GameWindow.ReadString(var0);
      } else {
         var2 = var0.getInt();
      }

    short var4 = var0.getShort();
    InventoryItem var5 = nullptr;
      if (var3 == nullptr) {
         var5 = IsoPlayer.getInstance().getInventory().getItemWithIDRecursiv(var2);
         if (var5 == nullptr) {
            DebugLog.log("ERROR: invMngRemoveItem can not find " + var2 + " item.");
            return;
         }
      } else {
         var5 = InventoryItemFactory.CreateItem(var3);
      }

      if (var5 != nullptr) {
         if (var3 == nullptr) {
            IsoPlayer.getInstance().removeWornItem(var5);
            if (var5.getCategory() == "Clothing")) {
               LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
            }

            if (var5 == IsoPlayer.getInstance().getPrimaryHandItem()) {
               IsoPlayer.getInstance().setPrimaryHandItem(nullptr);
               LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
            } else if (var5 == IsoPlayer.getInstance().getSecondaryHandItem()) {
               IsoPlayer.getInstance().setSecondaryHandItem(nullptr);
               LuaEventManager.triggerEvent("OnClothingUpdated", IsoPlayer.getInstance());
            }

            IsoPlayer.getInstance().getInventory().removeItemWithIDRecurse(var5.getID());
         } else {
            IsoPlayer.getInstance().getInventory().RemoveOneOf(var3.split("\\.")[1]);
         }

    ByteBufferWriter var6 = connection.startPacket();
         PacketType.InvMngGetItem.doPacket(var6);
         var6.putShort(var4);
         var5.saveWithSize(var6.bb, false);
         PacketType.InvMngGetItem.send(connection);
      }
   }

    static void invMngRequestItem(int var0, const std::string& var1, IsoPlayer var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.InvMngReqItem.doPacket(var3);
      if (var1 != nullptr) {
         var3.putByte((byte)1);
         var3.putUTF(var1);
      } else {
         var3.putByte((byte)0);
         var3.putInt(var0);
      }

      var3.putShort(IsoPlayer.getInstance().getOnlineID());
      var3.putShort(var2.getOnlineID());
      PacketType.InvMngReqItem.send(connection);
   }

    static void invMngRequestRemoveItem(int var0, IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.InvMngRemoveItem.doPacket(var2);
      var2.putInt(var0);
      var2.putShort(var1.getOnlineID());
      PacketType.InvMngRemoveItem.send(connection);
   }

    static void receiveSyncFaction(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    int var4 = var0.getInt();
    Faction var5 = Faction.getFaction(var2);
      if (var5 == nullptr) {
         var5 = std::make_shared<Faction>(var2, var3);
         Faction.getFactions().push_back(var5);
      }

      var5.getPlayers().clear();
      if (var0.get() == 1) {
         var5.setTag(GameWindow.ReadString(var0));
         var5.setTagColor(std::make_shared<ColorInfo>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
      }

      for (int var6 = 0; var6 < var4; var6++) {
         var5.getPlayers().push_back(GameWindow.ReadString(var0));
      }

      var5.setOwner(var3);
    bool var7 = var0.get() == 1;
      if (var7) {
         Faction.getFactions().remove(var5);
         DebugLog.log("faction: removed " + var2 + " owner=" + var5.getOwner());
      }

      LuaEventManager.triggerEvent("SyncFaction", var2);
   }

    static void receiveSyncNonPvpZone(ByteBuffer var0, short var1) {
      try {
    SyncNonPvpZonePacket var2 = std::make_shared<SyncNonPvpZonePacket>();
         var2.parse(var0, connection);
         if (var2.isConsistent()) {
            var2.process();
            if (Core.bDebug) {
               DebugLog.Multiplayer.debugln("ReceiveSyncNonPvpZone: %s", var2.getDescription());
            }
         }
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveSyncNonPvpZone: failed", LogSeverity.Error);
      }
   }

    static void receiveChangeTextColor(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    float var4 = var0.getFloat();
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
         var3.setSpeakColourInfo(std::make_shared<ColorInfo>(var4, var5, var6, 1.0F));
      }
   }

    static void receivePlaySoundEveryPlayer(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
      DebugLog.log(DebugType.Sound, "sound: received " + var2 + " at " + var3 + "," + var4 + "," + var5);
      if (!Core.SoundDisabled) {
    FMOD_STUDIO_EVENT_DESCRIPTION var6 = FMODManager.instance.getEventDescription(var2);
         if (var6 == nullptr) {
            return;
         }

    long var7 = javafmod.FMOD_Studio_System_CreateEventInstance(var6.address);
         if (var7 <= 0L) {
            return;
         }

         javafmod.FMOD_Studio_EventInstance_SetVolume(var7, Core.getInstance().getOptionAmbientVolume() / 20.0F);
         javafmod.FMOD_Studio_EventInstance3D(var7, var3, var4, var5);
         javafmod.FMOD_Studio_StartEvent(var7);
         javafmod.FMOD_Studio_ReleaseEventInstance(var7);
      }
   }

    static void receiveCataplasm(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    int var4 = var0.getInt();
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
         if (var5 > 0.0F) {
            var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4)).setPlantainFactor(var5);
         }

         if (var6 > 0.0F) {
            var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4)).setComfreyFactor(var6);
         }

         if (var7 > 0.0F) {
            var3.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4)).setGarlicFactor(var7);
         }
      }
   }

    static void receiveStopFire(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 != nullptr) {
         var5.stopFire();
      }
   }

    static void receiveAddAlarm(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
      DebugLog.log(DebugType.Multiplayer, "ReceiveAlarm at [ " + var2 + " , " + var3 + " ]");
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, 0);
      if (var4 != nullptr && var4.getBuilding() != nullptr && var4.getBuilding().getDef() != nullptr) {
         var4.getBuilding().getDef().bAlarmed = true;
         AmbientStreamManager.instance.doAlarm(var4.room.def);
      }
   }

    static void receiveAddExplosiveTrap(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 != nullptr) {
    InventoryItem var6 = nullptr;

         try {
            var6 = InventoryItem.loadItem(var0, 195);
         } catch (Exception var9) {
            var9.printStackTrace();
         }

    HandWeapon var7 = var6 != nullptr ? (HandWeapon)var6 : nullptr;
    IsoTrap var8 = std::make_shared<IsoTrap>(var7, var5.getCell(), var5);
         var5.AddTileObject(var8);
         var8.triggerExplosion(var7.getSensorRange() > 0);
      }
   }

    static void receiveTeleport(ByteBuffer var0, short var1) {
    uint8_t var2 = var0.get();
    IsoPlayer var3 = IsoPlayer.players[var2];
      if (var3 != nullptr && !var3.isDead()) {
         if (var3.getVehicle() != nullptr) {
            var3.getVehicle().exit(var3);
            LuaEventManager.triggerEvent("OnExitVehicle", var3);
         }

         var3.setX(var0.getFloat());
         var3.setY(var0.getFloat());
         var3.setZ(var0.getFloat());
         var3.setLx(var3.getX());
         var3.setLy(var3.getY());
         var3.setLz(var3.getZ());
      }
   }

    static void receiveRemoveBlood(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    bool var5 = var0.get() == 1;
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 != nullptr) {
         var6.removeBlood(true, var5);
      }
   }

    static void receiveSyncThumpable(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    uint8_t var5 = var0.get();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         if (var5 >= 0 && var5 < var6.getObjects().size()) {
    IsoObject var7 = (IsoObject)var6.getObjects().get(var5);
            if (dynamic_cast<IsoThumpable*>(var7) != nullptr var8) {
               var8.lockedByCode = var0.getInt();
               var8.lockedByPadlock = var0.get() == 1;
               var8.keyId = var0.getInt();
            } else {
               DebugLog.log("syncThumpable: expected IsoThumpable index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
            }
         } else {
            DebugLog.log("syncThumpable: index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
         }
      }
   }

    static void receiveSyncDoorKey(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    uint8_t var5 = var0.get();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         if (var5 >= 0 && var5 < var6.getObjects().size()) {
    IsoObject var7 = (IsoObject)var6.getObjects().get(var5);
            if (dynamic_cast<IsoDoor*>(var7) != nullptr var8) {
               var8.keyId = var0.getInt();
            } else {
               DebugLog.log("SyncDoorKey: expected IsoDoor index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
            }
         } else {
            DebugLog.log("SyncDoorKey: index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
         }
      }
   }

    static void receiveConstructedZone(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    Zone var5 = IsoWorld.instance.MetaGrid.getZoneAt(var2, var3, var4);
      if (var5 != nullptr) {
         var5.setHaveConstruction(true);
      }
   }

    static void receiveAddCoopPlayer(ByteBuffer var0, short var1) {
    bool var2 = var0.get() == 1;
    uint8_t var3 = var0.get();
      if (var2) {
         for (int var4 = 0; var4 < IsoWorld.instance.AddCoopPlayers.size(); var4++) {
            ((AddCoopPlayer)IsoWorld.instance.AddCoopPlayers.get(var4)).accessGranted(var3);
         }
      } else {
    std::string var6 = GameWindow.ReadStringUTF(var0);

         for (int var5 = 0; var5 < IsoWorld.instance.AddCoopPlayers.size(); var5++) {
            ((AddCoopPlayer)IsoWorld.instance.AddCoopPlayers.get(var5)).accessDenied(var3, var6);
         }
      }
   }

    static void receiveZombieDescriptors(ByteBuffer var0, short var1) {
      try {
    Descriptor var2 = std::make_shared<Descriptor>();
         var2.load(var0, 195);
         SharedDescriptors.registerPlayerZombieDescriptor(var2);
      } catch (Exception var3) {
         var3.printStackTrace();
      }
   }

    static void checksumServer() {
    ByteBufferWriter var0 = connection.startPacket();
      PacketType.Checksum.doPacket(var0);
      var0.putUTF(checksum + ScriptManager.instance.getChecksum());
      PacketType.Checksum.send(connection);
   }

    static void receiveRegisterZone(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    int var9 = var0.getInt();
    std::vector var10 = IsoWorld.instance.getMetaGrid().getZonesAt(var4, var5, var6);
    bool var11 = false;

    for (auto& var13 : var10)         if (var3 == var13.getType())) {
            var11 = true;
            var13.setName(var2);
            var13.setLastActionTimestamp(var9);
         }
      }

      if (!var11) {
         IsoWorld.instance.getMetaGrid().registerZone(var2, var3, var4, var5, var6, var7, var8);
      }
   }

    static void receiveAddXpCommand(ByteBuffer var0, short var1) {
    IsoPlayer var2 = IDToPlayerMap.get(var0.getShort());
    Perk var3 = Perks.fromIndex(var0.getInt());
      if (var2 != nullptr && !var2.isDead()) {
         var2.getXp().AddXP(var3, var0.getInt());
      }
   }

    void sendAddXp(IsoPlayer var1, Perk var2, int var3) {
    AddXp var4 = std::make_shared<AddXp>();
      var4.set(var1, var2, var3);
    ByteBufferWriter var5 = connection.startPacket();
      PacketType.AddXP.doPacket(var5);
      var4.write(var5);
      PacketType.AddXP.send(connection);
   }

    static void receiveSyncXP(ByteBuffer var0, short var1) {
    IsoPlayer var2 = IDToPlayerMap.get(var0.getShort());
      if (var2 != nullptr && !var2.isDead()) {
         try {
            var2.getXp().load(var0, 195);
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }
   }

    void sendSyncXp(IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SyncXP.doPacket(var2);
      var2.putShort(var1.getOnlineID());

      try {
         var1.getXp().save(var2.bb);
      } catch (IOException var4) {
         var4.printStackTrace();
      }

      PacketType.SyncXP.send(connection);
   }

    void sendTransactionID(IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SendTransactionID.doPacket(var2);
      var2.putShort(var1.getOnlineID());
      var2.putInt(var1.getTransactionID());
      PacketType.SendTransactionID.send(connection);
   }

    static void receiveUserlog(ByteBuffer var0, short var1) {
    std::vector var2 = new std::vector();
    int var3 = var0.getInt();
    std::string var4 = GameWindow.ReadString(var0);

      for (int var5 = 0; var5 < var3; var5++) {
         var2.push_back(
            std::make_shared<Userlog>(
               var4,
               UserlogType.fromIndex(var0.getInt()),
               GameWindow.ReadString(var0),
               GameWindow.ReadString(var0),
               var0.getInt(),
               GameWindow.ReadString(var0)
            )
         );
      }

      LuaEventManager.triggerEvent("OnReceiveUserlog", var4, var2);
   }

    static void receiveAddXp(ByteBuffer var0, short var1) {
    AddXp var2 = std::make_shared<AddXp>();
      var2.parse(var0, connection);
      if (var2.isConsistent()) {
         var2.process();
      }
   }

    static void receivePing(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = var0.getInt() - 1 + "/" + var0.getInt();
      LuaEventManager.triggerEvent("ServerPinged", var2, var3);
      connection.forceDisconnect("receive-ping");
      askPing = false;
   }

    static void receiveChecksumLoading(ByteBuffer var0, short var1) {
      NetChecksum.comparer.clientPacket(var0);
   }

    static void receiveServerMapLoading(ByteBuffer var0, short var1) {
      ClientServerMap.receivePacket(var0);
   }

    static void receiveChangeSafety(ByteBuffer var0, short var1) {
      try {
    SafetyPacket var2 = std::make_shared<SafetyPacket>();
         var2.parse(var0, connection);
         var2.log(nullptr, "ReceiveChangeSafety");
         var2.process();
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveChangeSafety: failed", LogSeverity.Error);
      }
   }

    static void sendChangeSafety(Safety var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ChangeSafety.doPacket(var1);

      try {
    SafetyPacket var2 = std::make_shared<SafetyPacket>(var0);
         var2.write(var1);
         PacketType.ChangeSafety.send(connection);
         var2.log(nullptr, "SendChangeSafety");
      } catch (Exception var3) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var3, "SendChangeSafety: failed", LogSeverity.Error);
      }
   }

    static void receiveAddItemInInventory(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    std::string var3 = GameWindow.ReadString(var0);
    int var4 = var0.getInt();
    IsoPlayer var5 = IDToPlayerMap.get(var2);
      if (var5 != nullptr && !var5.isDead()) {
         var5.getInventory().AddItems(var3, var4);
      }
   }

    static void receiveKicked(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
      ConnectionManager.log("kick", var3, connection);
    std::string var4 = Translator.getText(var2);
      if (!StringUtils.isNullOrEmpty(var3)) {
         var4 = var4 + " " + Translator.getText("UI_ValidationFailed_" + var3);
      }

      if (GameWindow.states.current == IngameState.instance) {
         if (!StringUtils.isNullOrEmpty(var4)) {
            ChatManager.getInstance().showServerChatMessage(var4);
         }
      } else {
         LuaEventManager.triggerEvent("OnConnectFailed", var4);
      }

      connection.username = nullptr;
      GameWindow.kickReason = var4;
      GameWindow.bServerDisconnected = true;
      connection.forceDisconnect("receive-kick");
      DebugLog.Multiplayer.warn("ReceiveKicked: " + var3);
   }

    void addDisconnectPacket(int var1) {
      /* synchronized - TODO: add std::mutex */ (this.delayedDisconnect) {
         this.delayedDisconnect.push_back(var1);
      }

      ConnectionManager.log("disconnect", std::string.valueOf(var1), nullptr);
   }

    void connectionLost() {
      this.bConnectionLost = true;
      positions.clear();
      WorldMapRemotePlayers.instance.Reset();
   }

    static void SendCommandToServer(const std::string& var0) {
      if (ServerOptions.clientOptionsList == nullptr) {
         ServerOptions.initClientCommandsHelp();
      }

      if (var0.startsWith("/roll")) {
         try {
    int var1 = int.parseInt(var0.split(" ")[1]);
            if (var1 > 100) {
               ChatManager.getInstance().showServerChatMessage((std::string)ServerOptions.clientOptionsList.get("roll"));
               return;
            }
         } catch (Exception var5) {
            ChatManager.getInstance().showServerChatMessage((std::string)ServerOptions.clientOptionsList.get("roll"));
            return;
         }

         if (!IsoPlayer.getInstance().getInventory().contains("Dice") && connection.accessLevel == 1) {
            ChatManager.getInstance().showServerChatMessage((std::string)ServerOptions.clientOptionsList.get("roll"));
            return;
         }
      }

      if (var0.startsWith("/card") && !IsoPlayer.getInstance().getInventory().contains("CardDeck") && connection.accessLevel == 1) {
         ChatManager.getInstance().showServerChatMessage((std::string)ServerOptions.clientOptionsList.get("card"));
      } else if (!var0.startsWith("/log ")) {
    ByteBufferWriter var7 = connection.startPacket();
         PacketType.ReceiveCommand.doPacket(var7);
         var7.putUTF(var0);
         PacketType.ReceiveCommand.send(connection);
      } else {
    std::string var6 = ChatManager.getInstance().getFocusTab().getTitleID();
         if ("UI_chat_admin_tab_title_id" == var6)) {
    ByteBufferWriter var2 = connection.startPacket();
            PacketType.ReceiveCommand.doPacket(var2);
            var2.putUTF(var0);
            PacketType.ReceiveCommand.send(connection);
         } else if ("UI_chat_main_tab_title_id" == var6)) {
            std::string[] var8 = var0.split(" ");
            if (var8.length == 3) {
    DebugType var3 = LogCommand.getDebugType(var8[1]);
    LogSeverity var4 = LogCommand.getLogSeverity(var8[2]);
               if (var3 != nullptr && var4 != nullptr) {
                  DebugLog.enableLog(var3, var4);
                  ChatManager.getInstance()
                     .showServerChatMessage(std::string.format("Client \"%s\" log level is \"%s\"", var3.name().toLowerCase(), var4.name().toLowerCase()));
                  if (DebugType.Network == var3)) {
                     ZNet.SetLogLevel(DebugLog.getLogLevel(DebugType.Network));
                  }
               } else {
                  ChatManager.getInstance()
                     .showServerChatMessage(
                        Translator.getText(
                           "UI_ServerOptionDesc_SetLogLevel",
                           var3 == nullptr ? "\"type\"" : var3.name().toLowerCase(),
                           var4 == nullptr ? "\"severity\"" : var4.name().toLowerCase()
                        )
                     );
               }
            }
         }
      }
   }

    static void sendServerPing(long var0) {
      if (connection != nullptr) {
    ByteBufferWriter var2 = connection.startPacket();
         PacketType.PingFromClient.doPacket(var2);
         var2.putLong(var0);
         PacketType.PingFromClient.send(connection);
         if (var0 == -1L) {
            DebugLog.Multiplayer.debugln("Player \"%s\" toggled lua debugger", connection.username);
         }
      }
   }

    bool gameLoadingDealWithNetData(ZomboidNetData var1) {
    ByteBuffer var2 = var1.buffer;

      try {
         return var1.type.onGameLoadingDealWithNetData(var2);
      } catch (Exception var4) {
         DebugLog.log(DebugType.Network, "Error with packet of type: " + var1.type);
         var4.printStackTrace();
         ZomboidNetDataPool.instance.discard(var1);
    return true;
      }
   }

    static void receiveWorldMessage(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadStringUTF(var0);
    std::string var3 = GameWindow.ReadString(var0);
      var3 = var3.replaceAll("<", "&lt;");
      var3 = var3.replaceAll(">", "&gt;");
      ChatManager.getInstance().addMessage(var2, var3);
   }

    static void receiveReloadOptions(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
         ServerOptions.instance.putOption(GameWindow.ReadString(var0), GameWindow.ReadString(var0));
      }
   }

    static void receiveStartRain(ByteBuffer var0, short var1) {
      RainManager.setRandRainMin(var0.getInt());
      RainManager.setRandRainMax(var0.getInt());
      RainManager.startRaining();
      RainManager.RainDesiredIntensity = var0.getFloat();
   }

    static void receiveStopRain(ByteBuffer var0, short var1) {
      RainManager.stopRaining();
   }

    static void receiveWeather(ByteBuffer var0, short var1) {
    GameTime var2 = GameTime.getInstance();
      var2.setDawn(var0.get() & 255);
      var2.setDusk(var0.get() & 255);
      var2.setThunderDay(var0.get() == 1);
      var2.setMoon(var0.getFloat());
      var2.setAmbientMin(var0.getFloat());
      var2.setAmbientMax(var0.getFloat());
      var2.setViewDistMin(var0.getFloat());
      var2.setViewDistMax(var0.getFloat());
      IsoWorld.instance.setGlobalTemperature(var0.getFloat());
      IsoWorld.instance.setWeather(GameWindow.ReadStringUTF(var0));
      ErosionMain.getInstance().receiveState(var0);
   }

    static void receiveWorldMapPlayerPosition(ByteBuffer var0, short var1) {
      tempShortList.clear();
    bool var2 = var0.get() == 1;
    short var3 = var0.getShort();

      for (int var4 = 0; var4 < var3; var4++) {
    short var5 = var0.getShort();
    WorldMapRemotePlayer var6 = WorldMapRemotePlayers.instance.getOrCreatePlayerByID(var5);
         if (var2) {
    short var7 = var0.getShort();
    std::string var8 = GameWindow.ReadStringUTF(var0);
    std::string var9 = GameWindow.ReadStringUTF(var0);
    std::string var10 = GameWindow.ReadStringUTF(var0);
    std::string var11 = GameWindow.ReadStringUTF(var0);
    float var12 = var0.getFloat();
    float var13 = var0.getFloat();
    bool var14 = var0.get() == 1;
            var6.setFullData(var7, var8, var9, var10, var11, var12, var13, var14);
            if (positions.containsKey(var5)) {
               positions.get(var5).set(var12, var13);
            } else {
               positions.put(var5, std::make_shared<Vector2>(var12, var13));
            }
         } else {
    short var17 = var0.getShort();
    float var18 = var0.getFloat();
    float var19 = var0.getFloat();
            if (var6.getChangeCount() != var17) {
               tempShortList.push_back(var5);
            } else {
               var6.setPosition(var18, var19);
               if (positions.containsKey(var5)) {
                  positions.get(var5).set(var18, var19);
               } else {
                  positions.put(var5, std::make_shared<Vector2>(var18, var19));
               }
            }
         }
      }

      if (!tempShortList.empty()) {
    ByteBufferWriter var15 = connection.startPacket();
         PacketType.WorldMapPlayerPosition.doPacket(var15);
         var15.putShort((short)tempShortList.size());

         for (int var16 = 0; var16 < tempShortList.size(); var16++) {
            var15.putShort(tempShortList.get(var16));
         }

         PacketType.WorldMapPlayerPosition.send(connection);
      }
   }

    static void receiveSyncClock(ByteBuffer var0, short var1) {
    GameTime var2 = GameTime.getInstance();
    bool var3 = bFastForward;
      bFastForward = var0.get() == 1;
    float var4 = var0.getFloat();
    int var5 = var0.getInt();
    float var6 = var2.getTimeOfDay() - var2.getLastTimeOfDay();
      var2.setTimeOfDay(var4);
      var2.setLastTimeOfDay(var4 - var6);
      if (var2.getLastTimeOfDay() < 0.0F) {
         var2.setLastTimeOfDay(var4 - var6 + 24.0F);
      }

      var2.ServerLastTimeOfDay = var2.ServerTimeOfDay;
      var2.ServerTimeOfDay = var4;
      var2.setNightsSurvived(var5);
      if (var2.ServerLastTimeOfDay > var2.ServerTimeOfDay) {
         var2.ServerNewDays++;
      }
   }

    static void receiveClientCommand(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    bool var4 = var0.get() == 1;
    KahluaTable var5 = nullptr;
      if (var4) {
         var5 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var5, var0);
         } catch (Exception var7) {
            var7.printStackTrace();
            return;
         }
      }

      LuaEventManager.triggerEvent("OnServerCommand", var2, var3, var5);
   }

    static void receiveGlobalObjects(ByteBuffer var0, short var1) {
      CGlobalObjectNetwork.receive(var0);
   }

    void setRequest(RequestState var1) {
      this.request = var1;
   }

    static void receiveRequestData(ByteBuffer var0, short var1) {
    RequestDataPacket var2 = std::make_shared<RequestDataPacket>();
      var2.parse(var0, connection);
      if (var2.isConsistent()) {
         var2.process(connection);
      }
   }

    void GameLoadingRequestData() {
    RequestDataPacket var2 = std::make_shared<RequestDataPacket>();
      this.request = RequestState.Start;

      while (this.request != RequestState.Complete) {
         if (this.request == RequestState.Start) {
            var2.setRequest();
    ByteBufferWriter var1 = connection.startPacket();
            PacketType.RequestData.doPacket(var1);
            var2.write(var1);
            PacketType.RequestData.send(connection);
            this.request = RequestState.Loading;
         }

         try {
            Thread.sleep(30L);
         } catch (InterruptedException var4) {
            DebugLog.Multiplayer.printException(var4, "GameLoadingRequestData sleep error", LogSeverity.Error);
         }
      }
   }

    static void receiveMetaGrid(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    short var3 = var0.getShort();
    short var4 = var0.getShort();
    IsoMetaGrid var5 = IsoWorld.instance.MetaGrid;
      if (var2 >= var5.getMinX() && var2 <= var5.getMaxX() && var3 >= var5.getMinY() && var3 <= var5.getMaxY()) {
    IsoMetaCell var6 = var5.getCellData(var2, var3);
         if (var6.info != nullptr && var4 >= 0 && var4 < var6.info.RoomList.size()) {
            var6.info.getRoom(var4).def.bLightsActive = var0.get() == 1;
         }
      }
   }

    static void receiveSendCustomColor(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         if (var6 != nullptr && var5 < var6.getObjects().size()) {
    IsoObject var7 = (IsoObject)var6.getObjects().get(var5);
            if (var7 != nullptr) {
               var7.setCustomColor(std::make_shared<ColorInfo>(var0.getFloat(), var0.getFloat(), var0.getFloat(), var0.getFloat()));
            }
         }
      }
   }

    static void receiveUpdateItemSprite(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    std::string var3 = GameWindow.ReadStringUTF(var0);
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
      if (var8 == nullptr) {
         instance.delayPacket(var4, var5, var6);
      } else {
         if (var8 != nullptr && var7 < var8.getObjects().size()) {
            try {
    IsoObject var9 = (IsoObject)var8.getObjects().get(var7);
               if (var9 != nullptr) {
                  boolean var10 = var9.sprite != nullptr
                     && var9.sprite.getProperties().Is("HitByCar")
                     && var9.sprite.getProperties().Val("DamagedSprite") != nullptr
                     && !var9.sprite.getProperties().Val("DamagedSprite").empty();
                  var9.sprite = IsoSpriteManager.instance.getSprite(var2);
                  if (var9.sprite == nullptr && !var3.empty()) {
                     var9.setSprite(var3);
                  }

                  var9.RemoveAttachedAnims();
    int var11 = var0.get() & 255;

                  for (int var12 = 0; var12 < var11; var12++) {
    int var13 = var0.getInt();
    IsoSprite var14 = IsoSpriteManager.instance.getSprite(var13);
                     if (var14 != nullptr) {
                        var9.AttachExistingAnim(var14, 0, 0, false, 0, false, 0.0F);
                     }
                  }

                  if (dynamic_cast<IsoThumpable*>(var9) != nullptr && var10 && (var9.sprite == nullptr || !var9.sprite.getProperties().Is("HitByCar"))) {
                     ((IsoThumpable)var9).setBlockAllTheSquare(false);
                  }

                  var8.RecalcAllWithNeighbours(true);
               }
            } catch (Exception var15) {
            }
         }
      }
   }

    static void receiveUpdateOverlaySprite(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadStringUTF(var0);
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    float var8 = var0.getFloat();
    float var9 = var0.getFloat();
    int var10 = var0.getInt();
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var11 == nullptr) {
         instance.delayPacket(var3, var4, var5);
      } else {
         if (var11 != nullptr && var10 < var11.getObjects().size()) {
            try {
    IsoObject var12 = (IsoObject)var11.getObjects().get(var10);
               if (var12 != nullptr) {
                  var12.setOverlaySprite(var2, var6, var7, var8, var9, false);
               }
            } catch (Exception var13) {
            }
         }
      }
   }

    KahluaTable copyTable(KahluaTable var1) {
    KahluaTable var2 = LuaManager.platform.newTable();
    KahluaTableIterator var3 = var1.iterator();

      while (var3.advance()) {
    void* var4 = var3.getKey();
    void* var5 = var3.getValue();
         if (dynamic_cast<KahluaTable*>(var5) != nullptr) {
            var2.rawset(var4, this.copyTable((KahluaTable)var5));
         } else {
            var2.rawset(var4, var5);
         }
      }

    return var2;
   }

    KahluaTable getServerSpawnRegions() {
      return this.copyTable(this.ServerSpawnRegions);
   }

    static void receiveStartFire(ByteBuffer var0, short var1) {
    StartFire var2 = std::make_shared<StartFire>();
      var2.parse(var0, connection);
      if (var2.isConsistent() && var2.validate(connection)) {
         var2.process();
      }
   }

    static void receiveBecomeCorpse(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    short var3 = var0.getShort();
    float var4 = var0.getFloat();
    uint8_t var5 = var0.get();
    IsoGameCharacter var6 = nullptr;
      if (var5 == 1) {
         var6 = (IsoGameCharacter)IDToZombieMap.get(var3);
      } else if (var5 == 2) {
         var6 = (IsoGameCharacter)IDToPlayerMap.get(var3);
      }

      if (var6 != nullptr) {
    IsoDeadBody var7 = std::make_shared<IsoDeadBody>(var6);
         var7.setObjectID(var2);
         var7.setOnlineID(var3);
         var7.setReanimateTime(var4);
         IsoDeadBody.addDeadBodyID(var2, var7);
      }
   }

    static void receiveAddCorpseToMap(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    short var3 = var0.getShort();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoObject var7 = WorldItemTypes.createFromBuffer(var0);
      var7.loadFromRemoteBuffer(var0, false);
      ((IsoDeadBody)var7).setObjectID(var2);
      ((IsoDeadBody)var7).setOnlineID(var3);
      IsoDeadBody.addDeadBodyID(var2, (IsoDeadBody)var7);
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
      if (var8 == nullptr) {
         instance.delayPacket(var4, var5, var6);
      } else {
         var8.addCorpse((IsoDeadBody)var7, true);
      }
   }

    static void receiveReceiveModData(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 == nullptr && IsoWorld.instance.isValidSquare(var2, var3, var4) && IsoWorld.instance.CurrentCell.getChunkForGridSquare(var2, var3, var4) != nullptr) {
         var5 = IsoGridSquare.getNew(IsoWorld.instance.getCell(), nullptr, var2, var3, var4);
      }

      if (var5 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         try {
            var5.getModData().load(var0, 195);
         } catch (IOException var7) {
            var7.printStackTrace();
         }

         LuaEventManager.triggerEvent("onLoadModDataFromServer", var5);
      }
   }

    static void receiveObjectModData(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    bool var6 = var0.get() == 1;
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var7 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         if (var7 != nullptr && var5 >= 0 && var5 < var7.getObjects().size()) {
    IsoObject var8 = (IsoObject)var7.getObjects().get(var5);
            if (var6) {
               try {
                  var8.getModData().load(var0, 195);
               } catch (IOException var10) {
                  var10.printStackTrace();
               }
            } else {
               var8.getModData().wipe();
            }
         } else if (var7 != nullptr) {
            DebugLog.log("receiveObjectModData: index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectModData: sq is nullptr x,y,z=" + var2 + "," + var3 + "," + var4);
         }
      }
   }

    static void receiveObjectChange(ByteBuffer var0, short var1) {
    uint8_t var2 = var0.get();
      if (var2 == 1) {
    short var3 = var0.getShort();
    std::string var4 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var4);
         }

    IsoPlayer var5 = IDToPlayerMap.get(var3);
         if (var5 != nullptr) {
            var5.loadChange(var4, var0);
         }
      } else if (var2 == 2) {
    short var11 = var0.getShort();
    std::string var15 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var15);
         }

    BaseVehicle var19 = VehicleManager.instance.getVehicleByID(var11);
         if (var19 != nullptr) {
            var19.loadChange(var15, var0);
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: unknown vehicle id=" + var11);
         }
      } else if (var2 == 3) {
    int var12 = var0.getInt();
    int var16 = var0.getInt();
    int var20 = var0.getInt();
    int var6 = var0.getInt();
    std::string var7 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var7);
         }

    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var12, var16, var20);
         if (var8 == nullptr) {
            instance.delayPacket(var12, var16, var20);
            return;
         }

         for (int var9 = 0; var9 < var8.getWorldObjects().size(); var9++) {
    IsoWorldInventoryObject var10 = (IsoWorldInventoryObject)var8.getWorldObjects().get(var9);
            if (var10.getItem() != nullptr && var10.getItem().getID() == var6) {
               var10.loadChange(var7, var0);
               return;
            }
         }

         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: itemID=" + var6 + " is invalid x,y,z=" + var12 + "," + var16 + "," + var20);
         }
      } else if (var2 == 4) {
    int var13 = var0.getInt();
    int var17 = var0.getInt();
    int var21 = var0.getInt();
    int var23 = var0.getInt();
    std::string var25 = GameWindow.ReadString(var0);
    IsoGridSquare var27 = IsoWorld.instance.CurrentCell.getGridSquare(var13, var17, var21);
         if (var27 == nullptr) {
            instance.delayPacket(var13, var17, var21);
            return;
         }

         if (var23 >= 0 && var23 < var27.getStaticMovingObjects().size()) {
    IsoObject var29 = (IsoObject)var27.getStaticMovingObjects().get(var23);
            var29.loadChange(var25, var0);
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: index=" + var23 + " is invalid x,y,z=" + var13 + "," + var17 + "," + var21);
         }
      } else {
    int var14 = var0.getInt();
    int var18 = var0.getInt();
    int var22 = var0.getInt();
    int var24 = var0.getInt();
    std::string var26 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var26);
         }

    IsoGridSquare var28 = IsoWorld.instance.CurrentCell.getGridSquare(var14, var18, var22);
         if (var28 == nullptr) {
            instance.delayPacket(var14, var18, var22);
            return;
         }

         if (var28 != nullptr && var24 >= 0 && var24 < var28.getObjects().size()) {
    IsoObject var30 = (IsoObject)var28.getObjects().get(var24);
            var30.loadChange(var26, var0);
         } else if (var28 != nullptr) {
            if (Core.bDebug) {
               DebugLog.log("receiveObjectChange: index=" + var24 + " is invalid x,y,z=" + var14 + "," + var18 + "," + var22);
            }
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: sq is nullptr x,y,z=" + var14 + "," + var18 + "," + var22);
         }
      }
   }

    static void receiveKeepAlive(ByteBuffer var0, short var1) {
      MPDebugInfo.instance.clientPacket(var0);
   }

    static void receiveSmashWindow(ByteBuffer var0, short var1) {
    IsoObject var2 = instance.getIsoObjectRefFromByteBuffer(var0);
      if (dynamic_cast<IsoWindow*>(var2) != nullptr) {
    uint8_t var3 = var0.get();
         if (var3 == 1) {
            ((IsoWindow)var2).smashWindow(true);
         } else if (var3 == 2) {
            ((IsoWindow)var2).setGlassRemoved(true);
         }
      } else if (Core.bDebug) {
         DebugLog.log("SmashWindow not a window!");
      }
   }

    static void receiveRemoveContestedItemsFromInventory(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
    int var4 = var0.getInt();

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
            if (var6 != nullptr && !var6.isDead()) {
               var6.getInventory().removeItemWithIDRecurse(var4);
            }
         }
      }
   }

    static void receiveServerQuit(ByteBuffer var0, short var1) {
      GameWindow.kickReason = "Server shut down safely. Players and map data saved.";
      GameWindow.bServerDisconnected = true;
      ConnectionManager.log("receive-packet", "server-quit", nullptr);
   }

    static void receiveHitCharacter(ByteBuffer var0, short var1) {
      try {
    HitCharacterPacket var2 = HitCharacterPacket.process(var0);
         if (var2 != nullptr) {
            var2.parse(var0, connection);
            if (var2.isConsistent()) {
               DebugLog.Damage.trace(var2.getDescription());
               var2.tryProcess();
            }
         }
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveHitCharacter: failed", LogSeverity.Error);
      }
   }

   public static boolean sendHitCharacter(
      IsoGameCharacter var0, IsoMovingObject var1, HandWeapon var2, float var3, boolean var4, float var5, boolean var6, boolean var7, boolean var8
   ) {
    bool var9 = false;
    ByteBufferWriter var10 = connection.startPacket();
      PacketType.HitCharacter.doPacket(var10);

      try {
    void* var11 = nullptr;
         if (dynamic_cast<IsoZombie*>(var0) != nullptr) {
            if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
    bool var19 = ((IsoPlayer)var1).isLocalPlayer();
    bool var13 = !((IsoZombie)var0).isRemoteZombie();
               if (var13 && var19) {
    ZombieHitPlayerPacket var14 = std::make_shared<ZombieHitPlayerPacket>();
                  var14.set((IsoZombie)var0, (IsoPlayer)var1);
                  var11 = var14;
               } else {
                  DebugLog.Multiplayer.warn(std::string.format("SendHitCharacter: Wielder or target is not local (wielder=%b, target=%b)", var13, var19));
               }
            } else {
               DebugLog.Multiplayer
                  .warn(std::string.format("SendHitCharacter: unknown target type (wielder=%s, target=%s)", var0.getClass().getName(), var1.getClass().getName()));
            }
         } else if (dynamic_cast<IsoPlayer*>(var0) != nullptr) {
            if (var1 == nullptr) {
    PlayerHitSquarePacket var12 = std::make_shared<PlayerHitSquarePacket>();
               var12.set((IsoPlayer)var0, var2, var6);
               var11 = var12;
            } else if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
    PlayerHitPlayerPacket var16 = std::make_shared<PlayerHitPlayerPacket>();
               var16.set((IsoPlayer)var0, (IsoPlayer)var1, var2, var3, var4, var5, var6, var8);
               var11 = var16;
            } else if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    PlayerHitZombiePacket var17 = std::make_shared<PlayerHitZombiePacket>();
               var17.set((IsoPlayer)var0, (IsoZombie)var1, var2, var3, var4, var5, var6, var7, var8);
               var11 = var17;
            } else if (dynamic_cast<BaseVehicle*>(var1) != nullptr) {
    PlayerHitVehiclePacket var18 = std::make_shared<PlayerHitVehiclePacket>();
               var18.set((IsoPlayer)var0, (BaseVehicle)var1, var2, var6);
               var11 = var18;
            } else {
               DebugLog.Multiplayer
                  .warn(std::string.format("SendHitCharacter: unknown target type (wielder=%s, target=%s)", var0.getClass().getName(), var1.getClass().getName()));
            }
         } else {
            DebugLog.Multiplayer
               .warn(std::string.format("SendHitCharacter: unknown wielder type (wielder=%s, target=%s)", var0.getClass().getName(), var1.getClass().getName()));
         }

         if (var11 != nullptr) {
            var11.write(var10);
            PacketType.HitCharacter.send(connection);
            DebugLog.Damage.trace(var11.getDescription());
            var9 = true;
         }
      } catch (Exception var15) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var15, "SendHitCharacter: failed", LogSeverity.Error);
      }

    return var9;
   }

    static void sendHitVehicle(IsoPlayer var0, IsoGameCharacter var1, BaseVehicle var2, float var3, bool var4, int var5, float var6, bool var7) {
    ByteBufferWriter var8 = connection.startPacket();
      PacketType.HitCharacter.doPacket(var8);

      try {
    void* var9 = nullptr;
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
    VehicleHitPlayerPacket var10 = std::make_shared<VehicleHitPlayerPacket>();
            var10.set(var0, (IsoPlayer)var1, var2, var3, var4, var5, var6, var7);
            var9 = var10;
         } else if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    VehicleHitZombiePacket var12 = std::make_shared<VehicleHitZombiePacket>();
            var12.set(var0, (IsoZombie)var1, var2, var3, var4, var5, var6, var7);
            var9 = var12;
         } else {
            DebugLog.Multiplayer
               .warn(std::string.format("SendHitVehicle: unknown target type (wielder=%s, target=%s)", var0.getClass().getName(), var1.getClass().getName()));
         }

         if (var9 != nullptr) {
            var9.write(var8);
            PacketType.HitCharacter.send(connection);
            DebugLog.Damage.trace(var9.getDescription());
         }
      } catch (Exception var11) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var11, "SendHitVehicle: failed", LogSeverity.Error);
      }
   }

    static void receiveZombieDeath(ByteBuffer var0, short var1) {
      try {
    DeadZombiePacket var2 = std::make_shared<DeadZombiePacket>();
         var2.parse(var0, connection);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("ReceiveZombieDeath: %s", var2.getDescription());
         }
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void sendZombieDeath(IsoZombie var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ZombieDeath.doPacket(var1);

      try {
    DeadZombiePacket var2 = std::make_shared<DeadZombiePacket>();
         var2.set(var0);
         var2.write(var1);
         PacketType.ZombieDeath.send(connection);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("SendZombieDeath: %s", var2.getDescription());
         }
      } catch (Exception var3) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var3, "SendZombieDeath: failed", LogSeverity.Error);
      }
   }

    static void receivePlayerDeath(ByteBuffer var0, short var1) {
      try {
    DeadPlayerPacket var2 = std::make_shared<DeadPlayerPacket>();
         var2.parse(var0, connection);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("ReceivePlayerDeath: %s", var2.getDeathDescription());
         }
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceivePlayerDeath: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerDeath(IsoPlayer var0) {
      var0.setTransactionID(0);
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.PlayerDeath.doPacket(var1);

      try {
    DeadPlayerPacket var2 = std::make_shared<DeadPlayerPacket>();
         var2.set(var0);
         var2.write(var1);
         PacketType.PlayerDeath.send(connection);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("SendPlayerDeath: %s", var2.getDeathDescription());
         }
      } catch (Exception var3) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var3, "SendPlayerDeath: failed", LogSeverity.Error);
      }
   }

    static void receivePlayerDamage(ByteBuffer var0, short var1) {
      try {
    short var2 = var0.getShort();
    float var3 = var0.getFloat();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
         if (var4 != nullptr) {
            var4.getBodyDamage().load(var0, IsoWorld.getWorldVersion());
            var4.getStats().setPain(var3);
            if (Core.bDebug) {
               DebugLog.Multiplayer.debugln("ReceivePlayerDamage: \"%s\" %f", var4.getUsername(), var4.getBodyDamage().getOverallBodyHealth());
            }
         }
      } catch (Exception var5) {
         DebugLog.Multiplayer.printException(var5, "ReceivePlayerDamage: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerDamage(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.PlayerDamage.doPacket(var1);

      try {
         var1.putShort((short)var0.getPlayerNum());
         var1.putFloat(var0.getStats().getPain());
         var0.getBodyDamage().save(var1.bb);
         PacketType.PlayerDamage.send(connection);
         if (Core.bDebug) {
            DebugLog.Multiplayer.debugln("SendPlayerDamage: \"%s\" %f", var0.getUsername(), var0.getBodyDamage().getOverallBodyHealth());
         }
      } catch (Exception var3) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var3, "SendPlayerDamage: failed", LogSeverity.Error);
      }
   }

    static void receiveSyncInjuries(ByteBuffer var0, short var1) {
      try {
    SyncInjuriesPacket var2 = std::make_shared<SyncInjuriesPacket>();
         var2.parse(var0, connection);
         DebugLog.Damage.trace(var2.getDescription());
         var2.process();
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceivePlayerInjuries: failed", LogSeverity.Error);
      }
   }

    static void sendPlayerInjuries(IsoPlayer var0) {
    SyncInjuriesPacket var1 = std::make_shared<SyncInjuriesPacket>();
      var1.set(var0);
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SyncInjuries.doPacket(var2);

      try {
         var1.write(var2);
         PacketType.SyncInjuries.send(connection);
         DebugLog.Damage.trace(var1.getDescription());
      } catch (Exception var4) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var4, "SendPlayerInjuries: failed", LogSeverity.Error);
      }
   }

    static void receiveRemoveCorpseFromMap(ByteBuffer var0, short var1) {
    RemoveCorpseFromMap var2 = std::make_shared<RemoveCorpseFromMap>();
      var2.parse(var0, connection);
      if (var2.isConsistent()) {
         var2.process();
      }
   }

    static void sendRemoveCorpseFromMap(IsoDeadBody var0) {
    RemoveCorpseFromMap var1 = std::make_shared<RemoveCorpseFromMap>();
      var1.set(var0);
      DebugLog.Death.trace(var1.getDescription());
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.RemoveCorpseFromMap.doPacket(var2);
      var1.write(var2);
      PacketType.RemoveCorpseFromMap.send(connection);
   }

    static void sendEvent(IsoPlayer var0, const std::string& var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.EventPacket.doPacket(var2);

      try {
    EventPacket var3 = std::make_shared<EventPacket>();
         if (var3.set(var0, var1)) {
            var3.write(var2);
            PacketType.EventPacket.send(connection);
         } else {
            connection.cancelPacket();
         }
      } catch (Exception var4) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var4, "SendEvent: failed", LogSeverity.Error);
      }
   }

    static void receiveEventPacket(ByteBuffer var0, short var1) {
      try {
    EventPacket var2 = std::make_shared<EventPacket>();
         var2.parse(var0, connection);
         var2.tryProcess();
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveEvent: failed", LogSeverity.Error);
      }
   }

    static void sendAction(BaseAction var0, bool var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.ActionPacket.doPacket(var2);

      try {
    ActionPacket var3 = std::make_shared<ActionPacket>();
         var3.set(var1, var0);
         var3.write(var2);
         PacketType.ActionPacket.send(connection);
      } catch (Exception var4) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var4, "SendAction: failed", LogSeverity.Error);
      }
   }

    static void receiveActionPacket(ByteBuffer var0, short var1) {
      try {
    ActionPacket var2 = std::make_shared<ActionPacket>();
         var2.parse(var0, connection);
         var2.process();
      } catch (Exception var3) {
         DebugLog.Multiplayer.printException(var3, "ReceiveAction: failed", LogSeverity.Error);
      }
   }

    static void sendEatBody(IsoZombie var0, IsoMovingObject var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.EatBody.doPacket(var2);

      try {
         var2.putShort(var0.getOnlineID());
         if (dynamic_cast<IsoDeadBody*>(var1) != nullptr var3) {
            var2.putByte((byte)1);
            var2.putBoolean(var0.getVariableBoolean("onknees"));
            var2.putFloat(var0.getEatSpeed());
            var2.putFloat(var0.getStateEventDelayTimer());
            var2.putInt(var3.getStaticMovingObjectIndex());
            var2.putFloat(var3.getSquare().getX());
            var2.putFloat(var3.getSquare().getY());
            var2.putFloat(var3.getSquare().getZ());
         } else if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            var2.putByte((byte)2);
            var2.putBoolean(var0.getVariableBoolean("onknees"));
            var2.putFloat(var0.getEatSpeed());
            var2.putFloat(var0.getStateEventDelayTimer());
            var2.putShort(((IsoPlayer)var1).getOnlineID());
         } else {
            var2.putByte((byte)0);
         }

         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, "SendEatBody");
         }

         PacketType.EatBody.send(connection);
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "SendEatBody: failed", LogSeverity.Error);
         connection.cancelPacket();
      }
   }

    static void receiveEatBody(ByteBuffer var0, short var1) {
      try {
    short var2 = var0.getShort();
    uint8_t var3 = var0.get();
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, std::string.format("ReceiveEatBody: zombie=%d type=%d", var2, var3));
         }

    IsoZombie var4 = (IsoZombie)IDToZombieMap.get(var2);
         if (var4 == nullptr) {
            DebugLog.Multiplayer.error("ReceiveEatBody: zombie " + var2 + " not found");
            return;
         }

         if (var3 == 1) {
    bool var5 = var0.get() != 0;
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    int var8 = var0.getInt();
    float var9 = var0.getFloat();
    float var10 = var0.getFloat();
    float var11 = var0.getFloat();
    IsoGridSquare var12 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var10, var11);
            if (var12 == nullptr) {
               DebugLog.Multiplayer.error("ReceiveEatBody: incorrect square");
               return;
            }

            if (var8 >= 0 && var8 < var12.getStaticMovingObjects().size()) {
    IsoDeadBody var13 = (IsoDeadBody)var12.getStaticMovingObjects().get(var8);
               if (var13 != nullptr) {
                  var4.setTarget(nullptr);
                  var4.setEatBodyTarget(var13, true, var6);
                  var4.setVariable("onknees", var5);
                  var4.setStateEventDelayTimer(var7);
               } else {
                  DebugLog.Multiplayer.error("ReceiveEatBody: no corpse with index " + var8 + " on square");
               }
            } else {
               DebugLog.Multiplayer.error("ReceiveEatBody: no corpse on square");
            }
         } else if (var3 == 2) {
    bool var15 = var0.get() != 0;
    float var16 = var0.getFloat();
    float var17 = var0.getFloat();
    short var18 = var0.getShort();
    IsoPlayer var19 = IDToPlayerMap.get(var18);
            if (var19 == nullptr) {
               DebugLog.Multiplayer.error("ReceiveEatBody: player " + var18 + " not found");
               return;
            }

            var4.setTarget(nullptr);
            var4.setEatBodyTarget(var19, true, var16);
            var4.setVariable("onknees", var15);
            var4.setStateEventDelayTimer(var17);
         } else {
            var4.setEatBodyTarget(nullptr, false);
         }
      } catch (Exception var14) {
         DebugLog.Multiplayer.printException(var14, "ReceiveEatBody: failed", LogSeverity.Error);
      }
   }

    static void sendThump(IsoGameCharacter var0, Thumpable var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.Thump.doPacket(var2);

      try {
    short var3 = var0.getOnlineID();
    std::string var4 = var0.getVariableString("ThumpType");
         var2.putShort(var3);
         var2.putByte((byte)ThumpType.fromString(var4).ordinal());
         if (dynamic_cast<IsoObject*>(var1) != nullptr var5) {
            var2.putInt(var5.getObjectIndex());
            var2.putFloat(var5.getSquare().getX());
            var2.putFloat(var5.getSquare().getY());
            var2.putFloat(var5.getSquare().getZ());
         } else {
            var2.putInt(-1);
         }

         if (Core.bDebug) {
            DebugLog.log(
               DebugType.Multiplayer,
               std::string.format("SendThump: zombie=%d type=%s target=%s", var3, var4, var1 == nullptr ? "nullptr" : var1.getClass().getSimpleName())
            );
         }

         PacketType.Thump.send(connection);
      } catch (Exception var6) {
         DebugLog.Multiplayer.printException(var6, "SendThump: failed", LogSeverity.Error);
         connection.cancelPacket();
      }
   }

    static void receiveSyncRadioData(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    VoiceManagerData var3 = VoiceManagerData.get(var2);
      /* synchronized - TODO: add std::mutex */ (var3.radioData) {
         var3.isCanHearAll = var0.get() == 1;
    short var5 = (short)var0.getInt();
         var3.radioData.clear();

         for (int var6 = 0; var6 < var5 / 4; var6++) {
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    int var9 = var0.getInt();
    int var10 = var0.getInt();
            var3.radioData.push_back(std::make_shared<RadioData>(var7, var8, var9, var10));
         }
      }
   }

    static void receiveThump(ByteBuffer var0, short var1) {
      try {
    short var2 = var0.getShort();
    std::string var3 = ThumpType.fromByte(var0.get());
         if (Core.bDebug) {
            DebugLog.log(DebugType.Multiplayer, std::string.format("ReceiveThump: zombie=%d type=%s", var2, var3));
         }

    IsoZombie var4 = (IsoZombie)IDToZombieMap.get(var2);
         if (var4 == nullptr) {
            DebugLog.Multiplayer.error("ReceiveThump: zombie " + var2 + " not found");
            return;
         }

         var4.setVariable("ThumpType", var3);
    int var5 = var0.getInt();
         if (var5 == -1) {
            var4.setThumpTarget(nullptr);
            return;
         }

    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    float var8 = var0.getFloat();
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var8);
         if (var9 == nullptr) {
            DebugLog.Multiplayer.error("ReceiveThump: incorrect square");
            return;
         }

    IsoObject var10 = (IsoObject)var9.getObjects().get(var5);
         if (dynamic_cast<Thumpable*>(var10) != nullptr) {
            var4.setThumpTarget(var10);
         } else {
            DebugLog.Multiplayer.error("ReceiveThump: no thumpable with index " + var5 + " on square");
         }
      } catch (Exception var11) {
         DebugLog.Multiplayer.printException(var11, "ReceiveThump: failed", LogSeverity.Error);
      }
   }

    void sendWorldSound(WorldSound var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.WorldSound.doPacket(var2);
      var2.putInt(var1.x);
      var2.putInt(var1.y);
      var2.putInt(var1.z);
      var2.putInt(var1.radius);
      var2.putInt(var1.volume);
      var2.putByte((byte)(var1.stresshumans ? 1 : 0));
      var2.putFloat(var1.zombieIgnoreDist);
      var2.putFloat(var1.stressMod);
      var2.putByte((byte)(var1.sourceIsZombie ? 1 : 0));
      PacketType.WorldSound.send(connection);
   }

    static void receiveRemoveItemFromSquare(ByteBuffer var0, short var1) {
      if (IsoWorld.instance.CurrentCell != nullptr) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
         if (var6 == nullptr) {
            instance.delayPacket(var2, var3, var4);
         } else {
            if (var6 != nullptr && var5 >= 0 && var5 < var6.getObjects().size()) {
    IsoObject var7 = (IsoObject)var6.getObjects().get(var5);
               var6.RemoveTileObject(var7);
               if (dynamic_cast<IsoWorldInventoryObject*>(var7) != nullptr || var7.getContainer() != nullptr) {
                  LuaEventManager.triggerEvent("OnContainerUpdate", var7);
               }
            } else if (Core.bDebug) {
               DebugLog.log("RemoveItemFromMap: sq is nullptr or index is invalid");
            }
         }
      }
   }

    static void receiveLoadPlayerProfile(ByteBuffer var0, short var1) {
      ClientPlayerDB.getInstance().clientLoadNetworkCharacter(var0, connection);
   }

    void sendLoginQueueRequest2() {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.LoginQueueRequest2.doPacket(var1);
      PacketType.LoginQueueRequest2.send(connection);
      ConnectionManager.log("send-packet", "login-queue-request", connection);
   }

    void sendLoginQueueDone2(long var1) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.LoginQueueDone2.doPacket(var3);
      var3.putLong(var1);
      PacketType.LoginQueueDone2.send(connection);
      ConnectionManager.log("send-packet", "login-queue-done", connection);
   }

    static void receiveRemoveInventoryItemFromContainer(ByteBuffer var0, short var1) {
      if (IsoWorld.instance.CurrentCell != nullptr) {
    ByteBufferReader var2 = std::make_shared<ByteBufferReader>(var0);
    short var3 = var0.getShort();
    int var4 = var2.getInt();
    int var5 = var2.getInt();
    int var6 = var2.getInt();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
         if (var7 != nullptr) {
            if (var3 == 0) {
    uint8_t var8 = var2.getByte();
    int var9 = var0.getInt();
               if (var8 < 0 || var8 >= var7.getStaticMovingObjects().size()) {
                  DebugLog.log("ERROR: removeItemFromContainer: invalid corpse index");
                  return;
               }

    IsoObject var10 = (IsoObject)var7.getStaticMovingObjects().get(var8);
               if (var10 != nullptr && var10.getContainer() != nullptr) {
                  for (int var11 = 0; var11 < var9; var11++) {
    int var12 = var2.getInt();
                     var10.getContainer().removeItemWithID(var12);
                     var10.getContainer().setExplored(true);
                  }
               }
            } else if (var3 == 1) {
    int var16 = var2.getInt();
    int var19 = var0.getInt();
    ItemContainer var22 = nullptr;

               for (int var25 = 0; var25 < var7.getWorldObjects().size(); var25++) {
    IsoWorldInventoryObject var29 = (IsoWorldInventoryObject)var7.getWorldObjects().get(var25);
                  if (var29 != nullptr && var29.getItem() instanceof InventoryContainer && var29.getItem().id == var16) {
                     var22 = ((InventoryContainer)var29.getItem()).getInventory();
                     break;
                  }
               }

               if (var22 == nullptr) {
                  DebugLog.log("ERROR removeItemFromContainer can't find world item with id=" + var16);
                  return;
               }

               for (int var26 = 0; var26 < var19; var26++) {
    int var30 = var2.getInt();
                  var22.removeItemWithID(var30);
                  var22.setExplored(true);
               }
            } else if (var3 == 2) {
    uint8_t var17 = var2.getByte();
    uint8_t var20 = var2.getByte();
    int var23 = var0.getInt();
               if (var17 < 0 || var17 >= var7.getObjects().size()) {
                  DebugLog.log("ERROR: removeItemFromContainer: invalid object index");
                  return;
               }

    IsoObject var27 = (IsoObject)var7.getObjects().get(var17);
    ItemContainer var31 = var27 != nullptr ? var27.getContainerByIndex(var20) : nullptr;
               if (var31 != nullptr) {
                  for (int var13 = 0; var13 < var23; var13++) {
    int var14 = var2.getInt();
                     var31.removeItemWithID(var14);
                     var31.setExplored(true);
                  }
               }
            } else if (var3 == 3) {
    short var18 = var2.getShort();
    uint8_t var21 = var2.getByte();
    int var24 = var0.getInt();
    BaseVehicle var28 = VehicleManager.instance.getVehicleByID(var18);
               if (var28 == nullptr) {
                  DebugLog.log("ERROR: removeItemFromContainer: invalid vehicle id");
                  return;
               }

    VehiclePart var32 = var28.getPartByIndex(var21);
               if (var32 == nullptr) {
                  DebugLog.log("ERROR: removeItemFromContainer: invalid part index");
                  return;
               }

    ItemContainer var33 = var32.getItemContainer();
               if (var33 == nullptr) {
                  DebugLog.log("ERROR: removeItemFromContainer: part " + var32.getId() + " has no container");
                  return;
               }

               if (var33 != nullptr) {
                  for (int var34 = 0; var34 < var24; var34++) {
    int var15 = var2.getInt();
                     var33.removeItemWithID(var15);
                     var33.setExplored(true);
                  }

                  var32.setContainerContentAmount(var33.getCapacityWeight());
               }
            } else {
               DebugLog.log("ERROR: removeItemFromContainer: invalid object index");
            }
         } else {
            instance.delayPacket(var4, var5, var6);
         }
      }
   }

    static void receiveAddInventoryItemToContainer(ByteBuffer var0, short var1) {
      if (IsoWorld.instance.CurrentCell != nullptr) {
    ByteBufferReader var2 = std::make_shared<ByteBufferReader>(var0);
    short var3 = var0.getShort();
    int var4 = var2.getInt();
    int var5 = var2.getInt();
    int var6 = var2.getInt();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var6);
         if (var7 == nullptr) {
            instance.delayPacket(var4, var5, var6);
         } else {
    ItemContainer var8 = nullptr;
    VehiclePart var9 = nullptr;
            if (var3 == 0) {
    uint8_t var10 = var2.getByte();
               if (var10 < 0 || var10 >= var7.getStaticMovingObjects().size()) {
                  DebugLog.log("ERROR: sendItemsToContainer: invalid corpse index");
                  return;
               }

    IsoObject var11 = (IsoObject)var7.getStaticMovingObjects().get(var10);
               if (var11 != nullptr && var11.getContainer() != nullptr) {
                  var8 = var11.getContainer();
               }
            } else if (var3 == 1) {
    int var14 = var2.getInt();

               for (int var18 = 0; var18 < var7.getWorldObjects().size(); var18++) {
    IsoWorldInventoryObject var12 = (IsoWorldInventoryObject)var7.getWorldObjects().get(var18);
                  if (var12 != nullptr && var12.getItem() instanceof InventoryContainer && var12.getItem().id == var14) {
                     var8 = ((InventoryContainer)var12.getItem()).getInventory();
                     break;
                  }
               }

               if (var8 == nullptr) {
                  DebugLog.log("ERROR: sendItemsToContainer: can't find world item with id=" + var14);
                  return;
               }
            } else if (var3 == 2) {
    uint8_t var15 = var2.getByte();
    uint8_t var19 = var2.getByte();
               if (var15 < 0 || var15 >= var7.getObjects().size()) {
                  DebugLog.log("ERROR: sendItemsToContainer: invalid object index");
                  return;
               }

    IsoObject var22 = (IsoObject)var7.getObjects().get(var15);
               var8 = var22 != nullptr ? var22.getContainerByIndex(var19) : nullptr;
            } else if (var3 == 3) {
    short var16 = var2.getShort();
    uint8_t var20 = var2.getByte();
    BaseVehicle var23 = VehicleManager.instance.getVehicleByID(var16);
               if (var23 == nullptr) {
                  DebugLog.log("ERROR: sendItemsToContainer: invalid vehicle id");
                  return;
               }

               var9 = var23.getPartByIndex(var20);
               if (var9 == nullptr) {
                  DebugLog.log("ERROR: sendItemsToContainer: invalid part index");
                  return;
               }

               var8 = var9.getItemContainer();
               if (var8 == nullptr) {
                  DebugLog.log("ERROR: sendItemsToContainer: part " + var9.getId() + " has no container");
                  return;
               }
            } else {
               DebugLog.log("ERROR: sendItemsToContainer: unknown container type");
            }

            if (var8 != nullptr) {
               try {
    std::vector var17 = CompressIdenticalItems.load(var2.bb, 195, nullptr, nullptr);

                  for (int var21 = 0; var21 < var17.size(); var21++) {
    InventoryItem var24 = (InventoryItem)var17.get(var21);
                     if (var24 != nullptr) {
                        if (var8.containsID(var24.id)) {
                           if (var3 != 0) {
                              System.out.println("Error: Dupe item ID. id = " + var24.id);
                           }
                        } else {
                           var8.addItem(var24);
                           var8.setExplored(true);
                           if (var8.getParent() instanceof IsoMannequin) {
                              ((IsoMannequin)var8.getParent()).wearItem(var24, nullptr);
                           }
                        }
                     }
                  }
               } catch (Exception var13) {
                  var13.printStackTrace();
               }

               if (var9 != nullptr) {
                  var9.setContainerContentAmount(var8.getCapacityWeight());
               }
            }
         }
      }
   }

    void readItemStats(ByteBuffer var1, InventoryItem var2) {
    int var3 = var1.getInt();
    float var4 = var1.getFloat();
    bool var5 = var1.get() == 1;
      var2.setUses(var3);
      if (dynamic_cast<DrainableComboItem*>(var2) != nullptr) {
         ((DrainableComboItem)var2).setDelta(var4);
         ((DrainableComboItem)var2).updateWeight();
      }

      if (var5 && dynamic_cast<Food*>(var2) != nullptr var6) {
         var6.setHungChange(var1.getFloat());
         var6.setCalories(var1.getFloat());
         var6.setCarbohydrates(var1.getFloat());
         var6.setLipids(var1.getFloat());
         var6.setProteins(var1.getFloat());
         var6.setThirstChange(var1.getFloat());
         var6.setFluReduction(var1.getInt());
         var6.setPainReduction(var1.getFloat());
         var6.setEndChange(var1.getFloat());
         var6.setReduceFoodSickness(var1.getInt());
         var6.setStressChange(var1.getFloat());
         var6.setFatigueChange(var1.getFloat());
      }
   }

    static void receiveItemStats(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      switch (var2) {
         case 0:
    uint8_t var16 = var0.get();
    int var19 = var0.getInt();
            if (var6 != nullptr && var16 >= 0 && var16 < var6.getStaticMovingObjects().size()) {
    IsoMovingObject var22 = (IsoMovingObject)var6.getStaticMovingObjects().get(var16);
    ItemContainer var25 = var22.getContainer();
               if (var25 != nullptr) {
    InventoryItem var28 = var25.getItemWithID(var19);
                  if (var28 != nullptr) {
                     instance.readItemStats(var0, var28);
                  }
               }
            }
            break;
         case 1:
    int var15 = var0.getInt();
            if (var6 != nullptr) {
               for (int var18 = 0; var18 < var6.getWorldObjects().size(); var18++) {
    IsoWorldInventoryObject var21 = (IsoWorldInventoryObject)var6.getWorldObjects().get(var18);
                  if (var21.getItem() != nullptr && var21.getItem().id == var15) {
                     instance.readItemStats(var0, var21.getItem());
                     break;
                  }

                  if (var21.getItem() instanceof InventoryContainer) {
    ItemContainer var24 = ((InventoryContainer)var21.getItem()).getInventory();
    InventoryItem var27 = var24.getItemWithID(var15);
                     if (var27 != nullptr) {
                        instance.readItemStats(var0, var27);
                        break;
                     }
                  }
               }
            }
            break;
         case 2:
    uint8_t var14 = var0.get();
    uint8_t var17 = var0.get();
    int var20 = var0.getInt();
            if (var6 != nullptr && var14 >= 0 && var14 < var6.getObjects().size()) {
    IsoObject var23 = (IsoObject)var6.getObjects().get(var14);
    ItemContainer var26 = var23.getContainerByIndex(var17);
               if (var26 != nullptr) {
    InventoryItem var29 = var26.getItemWithID(var20);
                  if (var29 != nullptr) {
                     instance.readItemStats(var0, var29);
                  }
               }
            }
            break;
         case 3:
    short var7 = var0.getShort();
    uint8_t var8 = var0.get();
    int var9 = var0.getInt();
    BaseVehicle var10 = VehicleManager.instance.getVehicleByID(var7);
            if (var10 != nullptr) {
    VehiclePart var11 = var10.getPartByIndex(var8);
               if (var11 != nullptr) {
    ItemContainer var12 = var11.getItemContainer();
                  if (var12 != nullptr) {
    InventoryItem var13 = var12.getItemWithID(var9);
                     if (var13 != nullptr) {
                        instance.readItemStats(var0, var13);
                     }
                  }
               }
            }
      }
   }

    static bool canSeePlayerStats() {
      return connection.accessLevel != 1;
   }

    static bool canModifyPlayerStats() {
      return (connection.accessLevel & 56) != 0;
   }

    void sendPersonalColor(IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.ChangeTextColor.doPacket(var2);
      var2.putShort((short)var1.getPlayerNum());
      var2.putFloat(Core.getInstance().getMpTextColor().r);
      var2.putFloat(Core.getInstance().getMpTextColor().g);
      var2.putFloat(Core.getInstance().getMpTextColor().b);
      PacketType.ChangeTextColor.send(connection);
   }

    void sendChangedPlayerStats(IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.ChangePlayerStats.doPacket(var2);
      var1.createPlayerStats(var2, username);
      PacketType.ChangePlayerStats.send(connection);
   }

    static void receiveChangePlayerStats(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr) {
    std::string var4 = GameWindow.ReadString(var0);
         var3.setPlayerStats(var0, var4);
         allChatMuted = var3.isAllChatMuted();
      }
   }

    void writePlayerConnectData(ByteBufferWriter var1, IsoPlayer var2) {
      var1.putByte((byte)var2.PlayerIndex);
      var1.putByte((byte)IsoChunkMap.ChunkGridWidth);
      var1.putFloat(var2.x);
      var1.putFloat(var2.y);
      var1.putFloat(var2.z);

      try {
         var2.getDescriptor().save(var1.bb);
         var2.getHumanVisual().save(var1.bb);
    ItemVisuals var3 = std::make_shared<ItemVisuals>();
         var2.getItemVisuals(var3);
         var3.save(var1.bb);
         var2.getXp().save(var1.bb);
      } catch (IOException var8) {
         var8.printStackTrace();
      }

      var1.putBoolean(var2.isAllChatMuted());
      var1.putUTF(var2.getTagPrefix());
      var1.putFloat(var2.getTagColor().r);
      var1.putFloat(var2.getTagColor().g);
      var1.putFloat(var2.getTagColor().b);
      var1.putInt(var2.getTransactionID());
      var1.putDouble(var2.getHoursSurvived());
      var1.putInt(var2.getZombieKills());
      var1.putUTF(var2.getDisplayName());
      var1.putFloat(var2.getSpeakColour().r);
      var1.putFloat(var2.getSpeakColour().g);
      var1.putFloat(var2.getSpeakColour().b);
      var1.putBoolean(var2.showTag);
      var1.putBoolean(var2.factionPvp);
      if (SteamUtils.isSteamModeEnabled()) {
         var1.putUTF(SteamFriends.GetFriendPersonaName(SteamUser.GetSteamID()));
      }

    InventoryItem var9 = var2.getPrimaryHandItem();
      if (var9 == nullptr) {
         var1.putByte((byte)0);
      } else {
         var1.putByte((byte)1);

         try {
            var9.saveWithSize(var1.bb, false);
         } catch (IOException var7) {
            var7.printStackTrace();
         }
      }

    InventoryItem var4 = var2.getSecondaryHandItem();
      if (var4 == nullptr) {
         var1.putByte((byte)0);
      } else if (var4 == var9) {
         var1.putByte((byte)2);
      } else {
         var1.putByte((byte)1);

         try {
            var4.saveWithSize(var1.bb, false);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      }

      var1.putInt(var2.getAttachedItems().size());

      for (int var5 = 0; var5 < var2.getAttachedItems().size(); var5++) {
         var1.putUTF(var2.getAttachedItems().get(var5).getLocation());
         var1.putUTF(var2.getAttachedItems().get(var5).getItem().getFullType());
      }

      var1.putInt(var2.getPerkLevel(Perks.Sneak));
      connection.username = var2.username;
   }

    void sendPlayerConnect(IsoPlayer var1) {
      var1.setOnlineID((short)-1);
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.PlayerConnect.doPacket(var2);
      this.writePlayerConnectData(var2, var1);
      PacketType.PlayerConnect.send(connection);
      allChatMuted = var1.isAllChatMuted();
      sendPerks(var1);
      var1.updateEquippedRadioFreq();
      this.bPlayerConnectSent = true;
      ConnectionManager.log("send-packet", "player-connect", connection);
   }

    void sendPlayerSave(IsoPlayer var1) {
      if (connection != nullptr) {
    ByteBufferWriter var2 = connection.startPacket();
         PacketType.PlayerSave.doPacket(var2);
         var2.putByte((byte)var1.PlayerIndex);
         var2.putShort(var1.OnlineID);
         var2.putFloat(var1.x);
         var2.putFloat(var1.y);
         var2.putFloat(var1.z);
         PacketType.PlayerSave.send(connection);
      }
   }

    void sendPlayer2(IsoPlayer var1) {
      if (bClient && var1.isLocalPlayer() && var1.networkAI.isNeedToUpdate()) {
         if (l_send.playerPacket.set(var1)) {
    ByteBufferWriter var2 = connection.startPacket();
    PacketType var3;
            if (this.PlayerUpdateReliableLimit.Check()) {
               var3 = PacketType.PlayerUpdateReliable;
            } else {
               var3 = PacketType.PlayerUpdate;
            }

            var3.doPacket(var2);
            l_send.playerPacket.write(var2);
            var3.send(connection);
         }
      }
   }

    void sendPlayer(IsoPlayer var1) {
      var1.networkAI.needToUpdate();
   }

    void heartBeat() {
      count++;
   }

    static IsoZombie getZombie(short var0) {
      return (IsoZombie)IDToZombieMap.get(var0);
   }

    static void sendPlayerExtraInfo(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ExtraInfo.doPacket(var1);
      var1.putShort((short)var0.getPlayerNum());
      var1.putByte((byte)(var0.isGodMod() ? 1 : 0));
      var1.putByte((byte)(var0.isGhostMode() ? 1 : 0));
      var1.putByte((byte)(var0.isInvisible() ? 1 : 0));
      var1.putByte((byte)(var0.isNoClip() ? 1 : 0));
      var1.putByte((byte)(var0.isShowAdminTag() ? 1 : 0));
      var1.putByte((byte)(var0.isCanHearAll() ? 1 : 0));
      PacketType.ExtraInfo.send(connection);
   }

    static void receiveExtraInfo(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    std::string var3 = GameWindow.ReadString(var0);
    bool var4 = var0.get() == 1;
    bool var5 = var0.get() == 1;
    bool var6 = var0.get() == 1;
    bool var7 = var0.get() == 1;
    bool var8 = var0.get() == 1;
    IsoPlayer var9 = IDToPlayerMap.get(var2);
      if (var9 != nullptr) {
         var9.accessLevel = var3;
         var9.setGodMod(var4);
         var9.setInvisible(var6);
         var9.setGhostMode(var5);
         var9.setNoClip(var7);
         var9.setShowAdminTag(var8);
         if (!var9.bRemote) {
            connection.accessLevel = PlayerType.fromString(var3);
         }
      }
   }

    void setResetID(int var1) {
      this.ResetID = 0;
      this.loadResetID();
      if (this.ResetID != var1) {
    std::vector var2 = new std::vector();
         var2.push_back("map_symbols.bin");
         var2.push_back("map_visited.bin");
         var2.push_back("recorded_media.bin");

         for (int var3 = 0; var3 < var2.size(); var3++) {
            try {
    File var4 = ZomboidFileSystem.instance.getFileInCurrentSave((std::string)var2.get(var3));
               if (var4.exists()) {
    File var5 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + (std::string)var2.get(var3));
                  if (var5.exists()) {
                     var5.delete();
                  }

                  var4.renameTo(var5);
               }
            } catch (Exception var7) {
               ExceptionLogger.logException(var7);
            }
         }

         DebugLog.log("server was reset, deleting " + Core.GameMode + File.separator + Core.GameSaveWorld);
         GlobalObject.deleteSave(Core.GameMode + File.separator + Core.GameSaveWorld);
         GlobalObject.createWorld(Core.GameSaveWorld);

         for (int var8 = 0; var8 < var2.size(); var8++) {
            try {
    File var9 = ZomboidFileSystem.instance.getFileInCurrentSave((std::string)var2.get(var8));
    File var10 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + (std::string)var2.get(var8));
               if (var10.exists()) {
                  var10.renameTo(var9);
               }
            } catch (Exception var6) {
               ExceptionLogger.logException(var6);
            }
         }
      }

      this.ResetID = var1;
      this.saveResetID();
   }

    void loadResetID() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("serverid.dat");
      if (var1.exists()) {
    FileInputStream var2 = nullptr;

         try {
            var2 = std::make_shared<FileInputStream>(var1);
         } catch (FileNotFoundException var7) {
            var7.printStackTrace();
         }

    DataInputStream var3 = std::make_shared<DataInputStream>(var2);

         try {
            this.ResetID = var3.readInt();
         } catch (IOException var6) {
            var6.printStackTrace();
         }

         try {
            var2.close();
         } catch (IOException var5) {
            var5.printStackTrace();
         }
      }
   }

    void saveResetID() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("serverid.dat");
    FileOutputStream var2 = nullptr;

      try {
         var2 = std::make_shared<FileOutputStream>(var1);
      } catch (FileNotFoundException var7) {
         var7.printStackTrace();
      }

    DataOutputStream var3 = std::make_shared<DataOutputStream>(var2);

      try {
         var3.writeInt(this.ResetID);
      } catch (IOException var6) {
         var6.printStackTrace();
      }

      try {
         var2.close();
      } catch (IOException var5) {
         var5.printStackTrace();
      }
   }

    static void receivePlayerConnect(ByteBuffer var0, short var1) {
    bool var2 = false;
    short var3 = var0.getShort();
    uint8_t var4 = -1;
      if (var3 == -1) {
         var2 = true;
         var4 = var0.get();
         var3 = var0.getShort();

         try {
            GameTime.getInstance().load(var0);
            GameTime.getInstance().ServerTimeOfDay = GameTime.getInstance().getTimeOfDay();
            GameTime.getInstance().ServerNewDays = 0;
            GameTime.getInstance().setMinutesPerDay(SandboxOptions.instance.getDayLengthMinutes());
            LuaEventManager.triggerEvent("OnGameTimeLoaded");
         } catch (IOException var18) {
            var18.printStackTrace();
         }
      } else if (IDToPlayerMap.containsKey(var3)) {
         return;
      }

    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    IsoPlayer var8 = nullptr;
      if (var2) {
    std::string var9 = GameWindow.ReadString(var0);

         for (int var10 = 0; var10 < IsoWorld.instance.AddCoopPlayers.size(); var10++) {
            ((AddCoopPlayer)IsoWorld.instance.AddCoopPlayers.get(var10)).receivePlayerConnect(var4);
         }

         var8 = IsoPlayer.players[var4];
         var8.username = var9;
         var8.setOnlineID(var3);
      } else {
    std::string var19 = GameWindow.ReadString(var0);
    SurvivorDesc var21 = SurvivorFactory.CreateSurvivor();

         try {
            var21.load(var0, 195, nullptr);
         } catch (IOException var17) {
            var17.printStackTrace();
         }

         try {
            var8 = std::make_shared<IsoPlayer>(IsoWorld.instance.CurrentCell, var21, (int)var5, (int)var6, (int)var7);
            var8.bRemote = true;
            var8.lastRemoteUpdate = System.currentTimeMillis();
            var8.getHumanVisual().load(var0, 195);
            var8.getItemVisuals().load(var0, 195);
            var8.username = var19;
            var8.updateUsername();
            var8.setSceneCulled(false);
         } catch (Exception var16) {
            var16.printStackTrace();
         }

         var8.setX(var5);
         var8.setY(var6);
         var8.setZ(var7);
         var8.networkAI.targetX = var5;
         var8.networkAI.targetY = var6;
         var8.networkAI.targetZ = (int)var7;
      }

      var8.setOnlineID(var3);
      if (SteamUtils.isSteamModeEnabled()) {
         var8.setSteamID(var0.getLong());
      }

      var8.setGodMod(var0.get() == 1);
      var8.setGhostMode(var0.get() == 1);
      var8.getSafety().load(var0, IsoWorld.getWorldVersion());
    uint8_t var20 = var0.get();
      if (var2) {
         connection.accessLevel = var20;
         DebugLog.General
            .warn(
               "ReceivePlayerConnect: guid=%d mtu=%d connection-type=%s",
               new Object[]{connection.getConnectedGUID(), connection.getMTUSize(), connection.getConnectionType().name()}
            );
      }

      var8.accessLevel = PlayerType.toString(var20);
      var8.setInvisible(var0.get() == 1);
      if (!var2) {
         try {
            var8.getXp().load(var0, 195);
         } catch (IOException var15) {
            var15.printStackTrace();
         }
      }

      var8.setTagPrefix(GameWindow.ReadString(var0));
      var8.setTagColor(std::make_shared<ColorInfo>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
      var8.setHoursSurvived(var0.getDouble());
      var8.setZombieKills(var0.getInt());
      var8.setDisplayName(GameWindow.ReadString(var0));
      var8.setSpeakColour(std::make_shared<Color>(var0.getFloat(), var0.getFloat(), var0.getFloat(), 1.0F));
      var8.showTag = var0.get() == 1;
      var8.factionPvp = var0.get() == 1;
    int var22 = var0.getInt();

      for (int var11 = 0; var11 < var22; var11++) {
    std::string var12 = GameWindow.ReadString(var0);
    InventoryItem var13 = InventoryItemFactory.CreateItem(GameWindow.ReadString(var0));
         if (var13 != nullptr) {
            var8.setAttachedItem(var12, var13);
         }
      }

    int var23 = var0.getInt();
    int var24 = var0.getInt();
    int var25 = var0.getInt();
      var8.remoteSneakLvl = var23;
      var8.remoteStrLvl = var24;
      var8.remoteFitLvl = var25;
      if (Core.bDebug) {
         DebugLog.log(DebugType.Network, "Player Connect received for player " + username + " id " + var3 + (var2 ? " (local)" : " (remote)"));
      }

      if (!var2) {
         rememberPlayerPosition(var8, var5, var6);
      }

      IDToPlayerMap.put(var3, var8);
      instance.idMapDirty = true;
      LuaEventManager.triggerEvent("OnMiniScoreboardUpdate");
      if (var2) {
         getCustomModData();
      }

      if (!var2 && ServerOptions.instance.DisableSafehouseWhenPlayerConnected.getValue()) {
    SafeHouse var14 = SafeHouse.hasSafehouse(var8);
         if (var14 != nullptr) {
            var14.setPlayerConnected(var14.getPlayerConnected() + 1);
         }
      }

      if (var2) {
    std::string var26 = ServerOptions.getInstance().getOption("ServerWelcomeMessage");
         if (var26 != nullptr && !var26 == "")) {
            ChatManager.getInstance().showServerChatMessage(var26);
         }

         VoiceManager.getInstance().UpdateChannelsRoaming(connection);
      }
   }

    static void receiveScoreboardUpdate(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
      instance.connectedPlayers = std::make_unique<std::vector<>>();
    std::vector var3 = new std::vector();
    std::vector var4 = new std::vector();
    std::vector var5 = new std::vector();

      for (int var6 = 0; var6 < var2; var6++) {
    std::string var7 = GameWindow.ReadString(var0);
    std::string var8 = GameWindow.ReadString(var0);
         var3.push_back(var7);
         var4.push_back(var8);
         instance.connectedPlayers.push_back(instance.getPlayerFromUsername(var7));
         if (SteamUtils.isSteamModeEnabled()) {
    std::string var9 = SteamUtils.convertSteamIDToString(var0.getLong());
            var5.push_back(var9);
         }
      }

      LuaEventManager.triggerEvent("OnScoreboardUpdate", var3, var4, var5);
   }

    bool receivePlayerConnectWhileLoading(ByteBuffer var1) {
    bool var2 = false;
    short var3 = var1.getShort();
    uint8_t var4 = -1;
      if (var3 != -1) {
    return false;
      } else {
         if (var3 == -1) {
            var2 = true;
            var4 = var1.get();
            var3 = var1.getShort();

            try {
               GameTime.getInstance().load(var1);
               LuaEventManager.triggerEvent("OnGameTimeLoaded");
            } catch (IOException var14) {
               var14.printStackTrace();
            }
         }

    float var5 = var1.getFloat();
    float var6 = var1.getFloat();
    float var7 = var1.getFloat();
    IsoPlayer var8 = nullptr;
         if (var2) {
    std::string var9 = GameWindow.ReadString(var1);
            var8 = IsoPlayer.players[var4];
            var8.username = var9;
            var8.setOnlineID(var3);
         } else {
    std::string var15 = GameWindow.ReadString(var1);
    SurvivorDesc var10 = SurvivorFactory.CreateSurvivor();

            try {
               var10.load(var1, 195, nullptr);
            } catch (IOException var13) {
               var13.printStackTrace();
            }

            try {
               var8 = std::make_shared<IsoPlayer>(IsoWorld.instance.CurrentCell, var10, (int)var5, (int)var6, (int)var7);
               var8.getHumanVisual().load(var1, 195);
               var8.getItemVisuals().load(var1, 195);
               var8.username = var15;
               var8.updateUsername();
               var8.setSceneCulled(false);
            } catch (Exception var12) {
               var12.printStackTrace();
            }

            var8.bRemote = true;
            var8.setX(var5);
            var8.setY(var6);
            var8.setZ(var7);
         }

         var8.setOnlineID(var3);
         if (Core.bDebug) {
            DebugLog.log(DebugType.Network, "Player Connect received for player " + username + " id " + var3 + (var2 ? " (me)" : " (not me)"));
         }

    int var16 = var1.getInt();

         for (int var17 = 0; var17 < var16; var17++) {
            ServerOptions.instance.putOption(GameWindow.ReadString(var1), GameWindow.ReadString(var1));
         }

         var8.setGodMod(var1.get() == 1);
         var8.setGhostMode(var1.get() == 1);
         var8.getSafety().load(var1, IsoWorld.getWorldVersion());
         var8.accessLevel = GameWindow.ReadString(var1);
         var8.setInvisible(var1.get() == 1);
         IDToPlayerMap.put(var3, var8);
         this.idMapDirty = true;
         getCustomModData();
    std::string var18 = ServerOptions.getInstance().getOption("ServerWelcomeMessage");
         if (var2 && var18 != nullptr && !var18 == "")) {
            ChatManager.getInstance().showServerChatMessage(var18);
         }

    return true;
      }
   }

   public std::vector<IsoPlayer> getPlayers() {
      if (!this.idMapDirty) {
         return this.players;
      } else {
         this.players.clear();
         this.players.addAll(IDToPlayerMap.values());
         this.idMapDirty = false;
         return this.players;
      }
   }

    IsoObject getIsoObjectRefFromByteBuffer(ByteBuffer var1) {
    int var2 = var1.getInt();
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    uint8_t var5 = var1.get();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 == nullptr) {
         this.delayPacket(var2, var3, var4);
    return nullptr;
      } else {
         return var5 >= 0 && var5 < var6.getObjects().size() ? (IsoObject)var6.getObjects().get(var5) : nullptr;
      }
   }

    void sendWeaponHit(IsoPlayer var1, HandWeapon var2, IsoObject var3) {
      if (var1 != nullptr && var3 != nullptr && var1.isLocalPlayer()) {
    ByteBufferWriter var4 = connection.startPacket();
         PacketType.WeaponHit.doPacket(var4);
         var4.putInt(var3.square.x);
         var4.putInt(var3.square.y);
         var4.putInt(var3.square.z);
         var4.putByte((byte)var3.getObjectIndex());
         var4.putShort((short)var1.getPlayerNum());
         var4.putUTF(var2 != nullptr ? var2.getFullType() : "");
         PacketType.WeaponHit.send(connection);
      }
   }

    static void receiveSyncCustomLightSettings(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    uint8_t var5 = var0.get();
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var6 != nullptr && var5 >= 0 && var5 < var6.getObjects().size()) {
         if (var6.getObjects().get(var5) instanceof IsoLightSwitch) {
            ((IsoLightSwitch)var6.getObjects().get(var5)).receiveSyncCustomizedSettings(var0, nullptr);
         } else {
            DebugLog.log("Sync Lightswitch custom settings: found object not a instance of IsoLightSwitch, x,y,z=" + var2 + "," + var3 + "," + var4);
         }
      } else if (var6 != nullptr) {
         DebugLog.log("Sync Lightswitch custom settings: index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
      } else if (Core.bDebug) {
         DebugLog.log("Sync Lightswitch custom settings: sq is nullptr x,y,z=" + var2 + "," + var3 + "," + var4);
      }
   }

    static void receiveSyncIsoObjectReq(ByteBuffer var0, short var1) {
      if (SystemDisabler.doObjectStateSyncEnable) {
    short var2 = var0.getShort();

         for (int var3 = 0; var3 < var2; var3++) {
            receiveSyncIsoObject(var0, var1);
         }
      }
   }

    static void receiveSyncWorldObjectsReq(ByteBuffer var0, short var1) {
      DebugLog.log("SyncWorldObjectsReq client : ");
    short var2 = var0.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
    int var4 = var0.getInt();
    int var5 = var0.getInt();
         instance.worldObjectsSyncReq.receiveSyncIsoChunk(var4, var5);
    short var6 = var0.getShort();
         DebugLog.log("[" + var4 + "," + var5 + "]:" + var6 + " ");
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4 * 10, var5 * 10, 0);
         if (var7 == nullptr) {
            return;
         }

    IsoChunk var8 = var7.getChunk();
         var8.ObjectsSyncCount++;
         var8.recalcHashCodeObjects();
      }

      DebugLog.log(";\n");
   }

    static void receiveSyncObjects(ByteBuffer var0, short var1) {
      if (SystemDisabler.doWorldSyncEnable) {
    short var2 = var0.getShort();
         if (var2 == 2) {
            instance.worldObjectsSyncReq.receiveGridSquareHashes(var0);
         }

         if (var2 == 4) {
            instance.worldObjectsSyncReq.receiveGridSquareObjectHashes(var0);
         }

         if (var2 == 6) {
            instance.worldObjectsSyncReq.receiveObject(var0);
         }
      }
   }

    static void receiveSyncIsoObject(ByteBuffer var0, short var1) {
      if (DebugOptions.instance.Network.Client.SyncIsoObject.getValue()) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    uint8_t var5 = var0.get();
    uint8_t var6 = var0.get();
    uint8_t var7 = var0.get();
         if (var6 != 2) {
            instance.objectSyncReq.receiveIsoSync(var2, var3, var4, var5);
         }

         if (var6 == 1) {
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
            if (var8 == nullptr) {
               return;
            }

            if (var5 >= 0 && var5 < var8.getObjects().size()) {
               ((IsoObject)var8.getObjects().get(var5)).syncIsoObject(true, var7, nullptr, var0);
            } else {
               DebugLog.Network.warn("SyncIsoObject: index=" + var5 + " is invalid x,y,z=" + var2 + "," + var3 + "," + var4);
            }
         }
      }
   }

    static void receiveSyncAlarmClock(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
      if (var2 == AlarmClock.PacketPlayer) {
    short var15 = var0.getShort();
    int var16 = var0.getInt();
    bool var17 = var0.get() == 1;
    int var18 = var17 ? 0 : var0.getInt();
    int var19 = var17 ? 0 : var0.getInt();
    uint8_t var20 = var17 ? 0 : var0.get();
    IsoPlayer var21 = IDToPlayerMap.get(var15);
         if (var21 != nullptr) {
            for (int var22 = 0; var22 < var21.getInventory().getItems().size(); var22++) {
    InventoryItem var23 = (InventoryItem)var21.getInventory().getItems().get(var22);
               if (dynamic_cast<AlarmClock*>(var23) != nullptr && var23.getID() == var16) {
                  if (var17) {
                     ((AlarmClock)var23).stopRinging();
                  } else {
                     ((AlarmClock)var23).setAlarmSet(var20 == 1);
                     ((AlarmClock)var23).setHour(var18);
                     ((AlarmClock)var23).setMinute(var19);
                  }
                  break;
               }
            }
         }
      } else if (var2 == AlarmClock.PacketWorld) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    bool var7 = var0.get() == 1;
    int var8 = var7 ? 0 : var0.getInt();
    int var9 = var7 ? 0 : var0.getInt();
    uint8_t var10 = var7 ? 0 : var0.get();
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
         if (var11 != nullptr) {
            for (int var12 = 0; var12 < var11.getWorldObjects().size(); var12++) {
    IsoWorldInventoryObject var13 = (IsoWorldInventoryObject)var11.getWorldObjects().get(var12);
               if (var13 != nullptr && var13.getItem() instanceof AlarmClock && var13.getItem().id == var6) {
    AlarmClock var14 = (AlarmClock)var13.getItem();
                  if (var7) {
                     var14.stopRinging();
                  } else {
                     var14.setAlarmSet(var10 == 1);
                     var14.setHour(var8);
                     var14.setMinute(var9);
                  }
                  break;
               }
            }
         }
      }
   }

    static void receiveAddItemToMap(ByteBuffer var0, short var1) {
      if (IsoWorld.instance.CurrentCell != nullptr) {
    IsoObject var2 = WorldItemTypes.createFromBuffer(var0);
         var2.loadFromRemoteBuffer(var0);
         if (var2.square != nullptr) {
            if (dynamic_cast<IsoLightSwitch*>(var2) != nullptr) {
               ((IsoLightSwitch)var2).addLightSourceFromSprite();
            }

            var2.addToWorld();
            IsoWorld.instance.CurrentCell.checkHaveRoof(var2.square.getX(), var2.square.getY());
            if (!(dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr)) {
               for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
                  LosUtil.cachecleared[var3] = true;
               }

               IsoGridSquare.setRecalcLightTime(-1);
               GameTime.instance.lightSourceUpdate = 100.0F;
               MapCollisionData.instance.squareChanged(var2.square);
               PolygonalMap2.instance.squareChanged(var2.square);
               if (var2 == var2.square.getPlayerBuiltFloor()) {
                  IsoGridOcclusionData.SquareChanged();
               }

               IsoGenerator.updateGenerator(var2.getSquare());
            }

            if (dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr || var2.getContainer() != nullptr) {
               LuaEventManager.triggerEvent("OnContainerUpdate", var2);
            }
         }
      }
   }

    static void skipPacket(ByteBuffer var0, short var1) {
   }

    static void receiveAccessDenied(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
      std::string[] var3 = var2.split("##");
      std::string var4 = var3.length > 0
         ? Translator.getText(
            "UI_OnConnectFailed_" + var3[0], var3.length > 1 ? var3[1] : nullptr, var3.length > 2 ? var3[2] : nullptr, var3.length > 3 ? var3[3] : nullptr
         )
         : nullptr;
      LuaEventManager.triggerEvent("OnConnectFailed", var4);
      DebugLog.Multiplayer.warn("ReceiveAccessDenied: " + var4);
   }

    static void receivePlayerTimeout(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
      receivePlayerTimeout(var2);
   }

    static void receivePlayerTimeout(short var0) {
      WorldMapRemotePlayers.instance.removePlayerByID(var0);
      positions.remove(var0);
    IsoPlayer var1 = IDToPlayerMap.get(var0);
      if (var1 != nullptr) {
         DebugLog.log("Received timeout for player " + var1.username + " id " + var1.OnlineID);
         NetworkZombieSimulator.getInstance().clearTargetAuth(var1);
         if (var1.getVehicle() != nullptr) {
    int var2 = var1.getVehicle().getSeat(var1);
            if (var2 != -1) {
               var1.getVehicle().clearPassenger(var2);
            }

            VehicleManager.instance.sendRequestGetPosition(var1.getVehicle().VehicleID, PacketType.Vehicles);
         }

         var1.removeFromWorld();
         var1.removeFromSquare();
         IDToPlayerMap.remove(var1.OnlineID);
         instance.idMapDirty = true;
         LuaEventManager.triggerEvent("OnMiniScoreboardUpdate");
      }
   }

    void disconnect() {
      this.resetDisconnectTimer();
      this.bConnected = false;
      if (IsoPlayer.getInstance() != nullptr) {
         IsoPlayer.getInstance().setOnlineID((short)-1);
      }
   }

    void resetDisconnectTimer() {
      this.disconnectTime = System.currentTimeMillis();
   }

    std::string getReconnectCountdownTimer() {
      return std::string.valueOf((int)Math.ceil((10000L - System.currentTimeMillis() + this.disconnectTime) / 1000L));
   }

    bool canConnect() {
      return System.currentTimeMillis() - this.disconnectTime > 10000L;
   }

    void addIncoming(short var1, ByteBuffer var2) {
      if (connection != nullptr) {
         if (var1 == PacketType.SentChunk.getId()) {
            WorldStreamer.instance.receiveChunkPart(var2);
         } else if (var1 == PacketType.NotRequiredInZip.getId()) {
            WorldStreamer.instance.receiveNotRequired(var2);
         } else if (var1 == PacketType.LoadPlayerProfile.getId()) {
            ClientPlayerDB.getInstance().clientLoadNetworkCharacter(var2, connection);
         } else {
    ZomboidNetData var3 = nullptr;
            if (var2.remaining() > 2048) {
               var3 = ZomboidNetDataPool.instance.getLong(var2.remaining());
            } else {
               var3 = ZomboidNetDataPool.instance.get();
            }

            var3.read(var1, var2, connection);
            var3.time = System.currentTimeMillis();
            MainLoopNetDataQ.push_back(var3);
         }
      }
   }

    void doDisconnect(const std::string& var1) {
      if (connection != nullptr) {
         connection.forceDisconnect(var1);
         this.bConnected = false;
         connection = nullptr;
         bClient = false;
      } else {
         instance.Shutdown();
      }
   }

    void removeZombieFromCache(IsoZombie var1) {
      if (IDToZombieMap.containsKey(var1.OnlineID)) {
         IDToZombieMap.remove(var1.OnlineID);
      }
   }

    static void receiveEquip(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    uint8_t var3 = var0.get();
    uint8_t var4 = var0.get();
    IsoPlayer var5 = IDToPlayerMap.get(var2);
      if (var5 != IsoPlayer.getInstance()) {
    InventoryItem var6 = nullptr;
         if (var4 == 1) {
            try {
               var6 = InventoryItem.loadItem(var0, 195);
            } catch (Exception var9) {
               var9.printStackTrace();
            }
         }

         if (var5 != nullptr && var3 == 1 && var4 == 2) {
            var6 = var5.getPrimaryHandItem();
         }

         if (var5 != nullptr) {
            if (var3 == 0) {
               var5.setPrimaryHandItem(var6);
            } else {
               var5.setSecondaryHandItem(var6);
            }

            try {
               if (var6 != nullptr) {
                  var6.setContainer(var5.getInventory());
                  if (var4 == 1 && var0.get() == 1) {
                     var6.getVisual().load(var0, 195);
                  }
               }
            } catch (IOException var8) {
               var8.printStackTrace();
            }
         }
      }
   }

    void equip(IsoPlayer var1, int var2) {
    InventoryItem var3 = nullptr;
      if (var2 == 0) {
         var3 = var1.getPrimaryHandItem();
      } else {
         var3 = var1.getSecondaryHandItem();
      }

    ByteBufferWriter var4 = connection.startPacket();
      PacketType.Equip.doPacket(var4);
      var4.putByte((byte)var1.PlayerIndex);
      var4.putByte((byte)var2);
      if (var3 == nullptr) {
         var4.putByte((byte)0);
      } else if (var2 == 1 && var1.getPrimaryHandItem() == var1.getSecondaryHandItem()) {
         var4.putByte((byte)2);
      } else {
         var4.putByte((byte)1);

         try {
            var3.saveWithSize(var4.bb, false);
            if (var3.getVisual() != nullptr) {
               var4.bb.put((byte)1);
               var3.getVisual().save(var4.bb);
            } else {
               var4.bb.put((byte)0);
            }
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      }

      PacketType.Equip.send(connection);
   }

    void sendWorldMessage(const std::string& var1) {
      ChatManager.getInstance().showInfoMessage(var1);
   }

    void convertGameSaveWorldDirectory(const std::string& var1, const std::string& var2) {
    File var3 = std::make_shared<File>(var1);
      if (var3.isDirectory()) {
    File var4 = std::make_shared<File>(var2);
    bool var5 = var3.renameTo(var4);
         if (var5) {
            DebugLog.log("CONVERT: The GameSaveWorld directory was renamed from " + var1 + " to " + var2);
         } else {
            DebugLog.log("ERROR: The GameSaveWorld directory cannot rename from " + var1 + " to " + var2);
         }
      }
   }

    void doConnect(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, const std::string& var6, const std::string& var7, bool var8) {
      username = var1.trim();
      password = var2.trim();
      ip = var3.trim();
      localIP = var4.trim();
      port = int.parseInt(var5.trim());
      serverPassword = var6.trim();
      ServerName = var7.trim();
      useSteamRelay = var8;
      instance.init();
      Core.GameSaveWorld = ip + "_" + port + "_" + ServerWorldDatabase.encrypt(var1);
      this.convertGameSaveWorldDirectory(
         ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + ip + "_" + port + "_" + var1, ZomboidFileSystem.instance.getCurrentSaveDir()
      );
      if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
         Core.GameSaveWorld = CoopMaster.instance.getPlayerSaveFolder(CoopMaster.instance.getServerName());
      }
   }

    void doConnectCoop(const std::string& var1) {
      username = SteamFriends.GetPersonaName();
      password = "";
      ip = var1;
      localIP = "";
      port = 0;
      serverPassword = "";
      this.init();
      if (CoopMaster.instance != nullptr && CoopMaster.instance.isRunning()) {
         Core.GameSaveWorld = CoopMaster.instance.getPlayerSaveFolder(CoopMaster.instance.getServerName());
      }
   }

    void scoreboardUpdate() {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ScoreboardUpdate.doPacket(var1);
      PacketType.ScoreboardUpdate.send(connection);
   }

    void sendWorldSound(void* var1, int var2, int var3, int var4, int var5, int var6, bool var7, float var8, float var9) {
    ByteBufferWriter var10 = connection.startPacket();
      PacketType.WorldSound.doPacket(var10);
      var10.putInt(var2);
      var10.putInt(var3);
      var10.putInt(var4);
      var10.putInt(var5);
      var10.putInt(var6);
      var10.putByte((byte)(var7 ? 1 : 0));
      var10.putFloat(var8);
      var10.putFloat(var9);
      var10.putByte((byte)(dynamic_cast<IsoZombie*>(var1) != nullptr ? 1 : 0));
      PacketType.WorldSound.send(connection);
   }

    static void receivePlayWorldSound(ByteBuffer var0, short var1) {
    PlayWorldSoundPacket var2 = std::make_shared<PlayWorldSoundPacket>();
      var2.parse(var0, connection);
      var2.process();
      DebugLog.log(DebugType.Sound, var2.getDescription());
   }

    static void receivePlaySound(ByteBuffer var0, short var1) {
    PlaySoundPacket var2 = std::make_shared<PlaySoundPacket>();
      var2.parse(var0, connection);
      var2.process();
      DebugLog.log(DebugType.Sound, var2.getDescription());
   }

    static void receiveStopSound(ByteBuffer var0, short var1) {
    StopSoundPacket var2 = std::make_shared<StopSoundPacket>();
      var2.parse(var0, connection);
      var2.process();
      DebugLog.log(DebugType.Sound, var2.getDescription());
   }

    static void receiveWorldSound(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    bool var7 = var0.get() == 1;
    float var8 = var0.getFloat();
    float var9 = var0.getFloat();
    bool var10 = var0.get() == 1;
      WorldSoundManager.instance.addSound(nullptr, var2, var3, var4, var5, var6, var7, var8, var9, var10, false, true);
   }

    static void receiveAddAmbient(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    float var6 = var0.getFloat();
      DebugLog.log(DebugType.Sound, "ambient: received " + var2 + " at " + var3 + "," + var4 + " radius=" + var5);
      AmbientStreamManager.instance.addAmbient(var2, var3, var4, var5, var6);
   }

    void sendClientCommand(IsoPlayer var1, const std::string& var2, const std::string& var3, KahluaTable var4) {
    ByteBufferWriter var5 = connection.startPacket();
      PacketType.ClientCommand.doPacket(var5);
      var5.putByte((byte)(var1 != nullptr ? var1.PlayerIndex : -1));
      var5.putUTF(var2);
      var5.putUTF(var3);
      if (var4 != nullptr && !var4.empty()) {
         var5.putByte((byte)1);

         try {
    KahluaTableIterator var6 = var4.iterator();

            while (var6.advance()) {
               if (!TableNetworkUtils.canSave(var6.getKey(), var6.getValue())) {
                  DebugLog.log("ERROR: sendClientCommand: can't save key,value=" + var6.getKey() + "," + var6.getValue());
               }
            }

            TableNetworkUtils.save(var4, var5.bb);
         } catch (IOException var7) {
            var7.printStackTrace();
         }
      } else {
         var5.putByte((byte)0);
      }

      PacketType.ClientCommand.send(connection);
   }

    void sendClientCommandV(IsoPlayer var1, const std::string& var2, const std::string& var3, Object... var4) {
      if (var4.length == 0) {
         this.sendClientCommand(var1, var2, var3, (KahluaTable)nullptr);
      } else if (var4.length % 2 != 0) {
         DebugLog.log("ERROR: sendClientCommand called with wrong number of arguments (" + var2 + " " + var3 + ")");
      } else {
    KahluaTable var5 = LuaManager.platform.newTable();

         for (byte var6 = 0; var6 < var4.length; var6 += 2) {
    void* var7 = var4[var6 + 1];
            if (dynamic_cast<float*>(var7) != nullptr) {
               var5.rawset(var4[var6], ((float)var7).doubleValue());
            } else if (dynamic_cast<int*>(var7) != nullptr) {
               var5.rawset(var4[var6], ((int)var7).doubleValue());
            } else if (dynamic_cast<int16_t*>(var7) != nullptr) {
               var5.rawset(var4[var6], ((int16_t)var7).doubleValue());
            } else {
               var5.rawset(var4[var6], var7);
            }
         }

         this.sendClientCommand(var1, var2, var3, var5);
      }
   }

    void sendClothing(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
      if (var1 != nullptr && var1.OnlineID != -1) {
    SyncClothingPacket var4 = std::make_shared<SyncClothingPacket>();
         var4.set(var1, var2, var3);
    ByteBufferWriter var5 = connection.startPacket();
         PacketType.SyncClothing.doPacket(var5);
         var4.write(var5);
         PacketType.SyncClothing.send(connection);
      }
   }

    static void receiveSyncClothing(ByteBuffer var0, short var1) {
    SyncClothingPacket var2 = std::make_shared<SyncClothingPacket>();
      var2.parse(var0, connection);
   }

    void sendAttachedItem(IsoPlayer var1, const std::string& var2, InventoryItem var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.PlayerAttachedItem.doPacket(var4);

      try {
         var4.putByte((byte)var1.PlayerIndex);
         GameWindow.WriteString(var4.bb, var2);
         if (var3 != nullptr) {
            var4.putByte((byte)1);
            GameWindow.WriteString(var4.bb, var3.getFullType());
         } else {
            var4.putByte((byte)0);
         }

         PacketType.PlayerAttachedItem.send(connection);
      } catch (Throwable var6) {
         connection.cancelPacket();
         ExceptionLogger.logException(var6);
      }
   }

    static void receivePlayerAttachedItem(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr && !var3.isLocalPlayer()) {
    std::string var4 = GameWindow.ReadString(var0);
    bool var5 = var0.get() == 1;
         if (var5) {
    std::string var6 = GameWindow.ReadString(var0);
    InventoryItem var7 = InventoryItemFactory.CreateItem(var6);
            if (var7 == nullptr) {
               return;
            }

            var3.setAttachedItem(var4, var7);
         } else {
            var3.setAttachedItem(var4, nullptr);
         }
      }
   }

    void sendVisual(IsoPlayer var1) {
      if (var1 != nullptr && var1.OnlineID != -1) {
    ByteBufferWriter var2 = connection.startPacket();
         PacketType.HumanVisual.doPacket(var2);

         try {
            var2.putShort(var1.OnlineID);
            var1.getHumanVisual().save(var2.bb);
            PacketType.HumanVisual.send(connection);
         } catch (Throwable var4) {
            connection.cancelPacket();
            ExceptionLogger.logException(var4);
         }
      }
   }

    static void receiveHumanVisual(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoPlayer var3 = IDToPlayerMap.get(var2);
      if (var3 != nullptr && !var3.isLocalPlayer()) {
         try {
            var3.getHumanVisual().load(var0, 195);
            var3.resetModelNextFrame();
         } catch (Throwable var5) {
            ExceptionLogger.logException(var5);
         }
      }
   }

    static void receiveBloodSplatter(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    float var3 = var0.getFloat();
    float var4 = var0.getFloat();
    float var5 = var0.getFloat();
    float var6 = var0.getFloat();
    float var7 = var0.getFloat();
    bool var8 = var0.get() == 1;
    bool var9 = var0.get() == 1;
    uint8_t var10 = var0.get();
    IsoCell var11 = IsoWorld.instance.CurrentCell;
    IsoGridSquare var12 = var11.getGridSquare(var3, var4, var5);
      if (var12 == nullptr) {
         instance.delayPacket((int)var3, (int)var4, (int)var5);
      } else if (var9 && SandboxOptions.instance.BloodLevel.getValue() > 1) {
         for (int var18 = -1; var18 <= 1; var18++) {
            for (int var19 = -1; var19 <= 1; var19++) {
               if (var18 != 0 || var19 != 0) {
    std::make_shared<IsoZombieGiblets>(var18 *);
               }
            }
         }

    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
      } else {
         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
            for (int var13 = 0; var13 < var10; var13++) {
               var12.splatBlood(3, 0.3F);
            }

            var12.getChunk().addBloodSplat(var3, var4, (int)var5, Rand.Next(20));
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
         }

    uint8_t var17 = 3;
    uint8_t var14 = 0;
    uint8_t var15 = 1;
         switch (SandboxOptions.instance.BloodLevel.getValue()) {
            case 1:
               var15 = 0;
               break;
            case 2:
               var15 = 1;
               var17 = 5;
               var14 = 2;
            case 3:
            default:
               break;
            case 4:
               var15 = 3;
               var17 = 2;
               break;
            case 5:
               var15 = 10;
               var17 = 0;
         }

         for (int var16 = 0; var16 < var15; var16++) {
            if (Rand.Next(var8 ? 8 : var17) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 8 : var17) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 8 : var17) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 8 : var17) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 4 : var14) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }

            if (Rand.Next(var8 ? 9 : 6) == 0) {
    std::make_shared<IsoZombieGiblets>(var6 *, var7 *);
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void receiveZombieSound(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    uint8_t var3 = var0.get();
    ZombieSound var4 = ZombieSound.fromIndex(var3);
      DebugLog.log(DebugType.Sound, "sound: received " + var3 + " for zombie " + var2);
    IsoZombie var5 = (IsoZombie)IDToZombieMap.get(var2);
      if (var5 != nullptr && var5.getCurrentSquare() != nullptr) {
    float var6 = var4.radius();
         switch (1.$SwitchMap$zombie$characters$IsoZombie$ZombieSound[var4.ordinal()]) {
            case 1:
    std::string var11 = var5.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
               var5.getEmitter().playVocals(var11);
               break;
            case 2:
               var5.getEmitter().playSoundImpl("HeadStab", nullptr);
    std::string var10 = var5.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
               var5.getEmitter().playVocals(var10);
               var5.getEmitter().tick();
               break;
            case 3:
               var5.getEmitter().playSoundImpl("HeadSmash", nullptr);
    std::string var9 = var5.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
               var5.getEmitter().playVocals(var9);
               var5.getEmitter().tick();
               break;
            case 4:
               var5.playHurtSound();
               break;
            case 5:
    std::string var8 = var5.isFemale() ? "FemaleZombieIdle" : "MaleZombieIdle";
               var5.getEmitter().playVocals(var8);
               break;
            case 6:
    std::string var7 = var5.isFemale() ? "FemaleZombieAttack" : "MaleZombieAttack";
               var5.getEmitter().playVocals(var7);
               break;
            default:
               DebugLog.log("unhandled zombie sound " + var4);
         }
      }
   }

    static void receiveSlowFactor(ByteBuffer var0, short var1) {
    uint8_t var2 = var0.get();
    float var3 = var0.getFloat();
    float var4 = var0.getFloat();
    IsoPlayer var5 = IsoPlayer.players[var2];
      if (var5 != nullptr && !var5.isDead()) {
         var5.setSlowTimer(var3);
         var5.setSlowFactor(var4);
         DebugLog.log(DebugType.Combat, "slowTimer=" + var3 + " slowFactor=" + var4);
      }
   }

    void sendCustomColor(IsoObject var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SendCustomColor.doPacket(var2);
      var2.putInt(var1.getSquare().getX());
      var2.putInt(var1.getSquare().getY());
      var2.putInt(var1.getSquare().getZ());
      var2.putInt(var1.getSquare().getObjects().indexOf(var1));
      var2.putFloat(var1.getCustomColor().r);
      var2.putFloat(var1.getCustomColor().g);
      var2.putFloat(var1.getCustomColor().b);
      var2.putFloat(var1.getCustomColor().a);
      PacketType.SendCustomColor.send(connection);
   }

    void sendBandage(int var1, int var2, bool var3, float var4, bool var5, const std::string& var6) {
    ByteBufferWriter var7 = connection.startPacket();
      PacketType.Bandage.doPacket(var7);
      var7.putShort((short)var1);
      var7.putInt(var2);
      var7.putBoolean(var3);
      var7.putFloat(var4);
      var7.putBoolean(var5);
      GameWindow.WriteStringUTF(var7.bb, var6);
      PacketType.Bandage.send(connection);
   }

    void sendStitch(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4, bool var5) {
    Stitch var6 = std::make_shared<Stitch>();
      var6.set(var1, var2, var3, var4, var5);
    ByteBufferWriter var7 = connection.startPacket();
      PacketType.Stitch.doPacket(var7);
      var6.write(var7);
      PacketType.Stitch.send(connection);
   }

    void sendWoundInfection(int var1, int var2, bool var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.WoundInfection.doPacket(var4);
      var4.putShort((short)var1);
      var4.putInt(var2);
      var4.putBoolean(var3);
      PacketType.WoundInfection.send(connection);
   }

    void sendDisinfect(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4) {
    Disinfect var5 = std::make_shared<Disinfect>();
      var5.set(var1, var2, var3, var4);
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.Disinfect.doPacket(var6);
      var5.write(var6);
      PacketType.Disinfect.send(connection);
   }

    void sendSplint(int var1, int var2, bool var3, float var4, const std::string& var5) {
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.Splint.doPacket(var6);
      var6.putShort((short)var1);
      var6.putInt(var2);
      var6.putBoolean(var3);
      if (var3) {
         if (var5 == nullptr) {
            var5 = "";
         }

         var6.putUTF(var5);
         var6.putFloat(var4);
      }

      PacketType.Splint.send(connection);
   }

    void sendAdditionalPain(int var1, int var2, float var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.AdditionalPain.doPacket(var4);
      var4.putShort((short)var1);
      var4.putInt(var2);
      var4.putFloat(var3);
      PacketType.AdditionalPain.send(connection);
   }

    void sendRemoveGlass(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, bool var4) {
    RemoveGlass var5 = std::make_shared<RemoveGlass>();
      var5.set(var1, var2, var3, var4);
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.RemoveGlass.doPacket(var6);
      var5.write(var6);
      PacketType.RemoveGlass.send(connection);
   }

    void sendRemoveBullet(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3) {
    RemoveBullet var4 = std::make_shared<RemoveBullet>();
      var4.set(var1, var2, var3);
    ByteBufferWriter var5 = connection.startPacket();
      PacketType.RemoveBullet.doPacket(var5);
      var4.write(var5);
      PacketType.RemoveBullet.send(connection);
   }

    void sendCleanBurn(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4) {
    CleanBurn var5 = std::make_shared<CleanBurn>();
      var5.set(var1, var2, var3, var4);
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.CleanBurn.doPacket(var6);
      var5.write(var6);
      PacketType.CleanBurn.send(connection);
   }

    void eatFood(IsoPlayer var1, Food var2, float var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.EatFood.doPacket(var4);

      try {
         var4.putByte((byte)var1.PlayerIndex);
         var4.putFloat(var3);
         var2.saveWithSize(var4.bb, false);
      } catch (IOException var6) {
         var6.printStackTrace();
      }

      PacketType.EatFood.send(connection);
   }

    void drink(IsoPlayer var1, float var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.Drink.doPacket(var3);
      var3.putByte((byte)var1.PlayerIndex);
      var3.putFloat(var2);
      PacketType.Drink.send(connection);
   }

    void addToItemSendBuffer(IsoObject var1, ItemContainer var2, InventoryItem var3) {
      if (dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr) {
    InventoryItem var4 = ((IsoWorldInventoryObject)var1).getItem();
         if (var3 == nullptr || var4 == nullptr || !(dynamic_cast<InventoryContainer*>(var4) != nullptr) || var2 != ((InventoryContainer)var4).getInventory()) {
            DebugLog.log("ERROR: addToItemSendBuffer parent=" + var1 + " item=" + var3);
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            } else {
               return;
            }
         }
      } else if (dynamic_cast<BaseVehicle*>(var1) != nullptr) {
         if (var2.vehiclePart == nullptr || var2.vehiclePart.getItemContainer() != var2 || var2.vehiclePart.getVehicle() != var1) {
            DebugLog.log("ERROR: addToItemSendBuffer parent=" + var1 + " item=" + var3);
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            }

            return;
         }
      } else if (var1 == nullptr || var3 == nullptr || var1.getContainerIndex(var2) == -1) {
         DebugLog.log("ERROR: addToItemSendBuffer parent=" + var1 + " item=" + var3);
         if (Core.bDebug) {
            throw std::make_unique<IllegalStateException>();
         }

         return;
      }

      if (this.itemsToSendRemove.containsKey(var2)) {
    std::vector var5 = this.itemsToSendRemove.get(var2);
         if (var5.remove(var3)) {
            if (var5.empty()) {
               this.itemsToSendRemove.remove(var2);
            }

            return;
         }
      }

      if (this.itemsToSend.containsKey(var2)) {
         this.itemsToSend.get(var2).push_back(var3);
      } else {
    std::vector var6 = new std::vector();
         this.itemsToSend.put(var2, var6);
         var6.push_back(var3);
      }
   }

    void addToItemRemoveSendBuffer(IsoObject var1, ItemContainer var2, InventoryItem var3) {
      if (dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr) {
    InventoryItem var4 = ((IsoWorldInventoryObject)var1).getItem();
         if (var3 == nullptr || var4 == nullptr || !(dynamic_cast<InventoryContainer*>(var4) != nullptr) || var2 != ((InventoryContainer)var4).getInventory()) {
            DebugLog.log("ERROR: addToItemRemoveSendBuffer parent=" + var1 + " item=" + var3);
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            } else {
               return;
            }
         }
      } else if (dynamic_cast<BaseVehicle*>(var1) != nullptr) {
         if (var2.vehiclePart == nullptr || var2.vehiclePart.getItemContainer() != var2 || var2.vehiclePart.getVehicle() != var1) {
            DebugLog.log("ERROR: addToItemRemoveSendBuffer parent=" + var1 + " item=" + var3);
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            }

            return;
         }
      } else if (dynamic_cast<IsoDeadBody*>(var1) != nullptr) {
         if (var3 == nullptr || var2 != var1.getContainer()) {
            DebugLog.log("ERROR: addToItemRemoveSendBuffer parent=" + var1 + " item=" + var3);
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            }

            return;
         }
      } else if (var1 == nullptr || var3 == nullptr || var1.getContainerIndex(var2) == -1) {
         DebugLog.log("ERROR: addToItemRemoveSendBuffer parent=" + var1 + " item=" + var3);
         if (Core.bDebug) {
            throw std::make_unique<IllegalStateException>();
         }

         return;
      }

      if (!SystemDisabler.doWorldSyncEnable) {
         if (this.itemsToSend.containsKey(var2)) {
    std::vector var8 = this.itemsToSend.get(var2);
            if (var8.remove(var3)) {
               if (var8.empty()) {
                  this.itemsToSend.remove(var2);
               }

               return;
            }
         }

         if (this.itemsToSendRemove.containsKey(var2)) {
            this.itemsToSendRemove.get(var2).push_back(var3);
         } else {
    std::vector var9 = new std::vector();
            var9.push_back(var3);
            this.itemsToSendRemove.put(var2, var9);
         }
      } else {
    void* var7 = var2.getParent();
         if (var2.getContainingItem() != nullptr && var2.getContainingItem().getWorldItem() != nullptr) {
            var7 = var2.getContainingItem().getWorldItem();
         }

    UdpConnection var5 = connection;
    ByteBufferWriter var6 = var5.startPacket();
         PacketType.RemoveInventoryItemFromContainer.doPacket(var6);
         if (dynamic_cast<IsoDeadBody*>(var7) != nullptr) {
            var6.putShort((short)0);
            var6.putInt(((IsoObject)var7).square.getX());
            var6.putInt(((IsoObject)var7).square.getY());
            var6.putInt(((IsoObject)var7).square.getZ());
            var6.putByte((byte)var7.getStaticMovingObjectIndex());
            var6.putInt(1);
            var6.putInt(var3.id);
         } else if (dynamic_cast<IsoWorldInventoryObject*>(var7) != nullptr) {
            var6.putShort((short)1);
            var6.putInt(((IsoObject)var7).square.getX());
            var6.putInt(((IsoObject)var7).square.getY());
            var6.putInt(((IsoObject)var7).square.getZ());
            var6.putInt(((IsoWorldInventoryObject)var7).getItem().id);
            var6.putInt(1);
            var6.putInt(var3.id);
         } else if (dynamic_cast<BaseVehicle*>(var7) != nullptr) {
            var6.putShort((short)3);
            var6.putInt(((IsoObject)var7).square.getX());
            var6.putInt(((IsoObject)var7).square.getY());
            var6.putInt(((IsoObject)var7).square.getZ());
            var6.putShort(((BaseVehicle)var7).VehicleID);
            var6.putByte((byte)var2.vehiclePart.getIndex());
            var6.putInt(1);
            var6.putInt(var3.id);
         } else {
            var6.putShort((short)2);
            var6.putInt(((IsoObject)var7).square.getX());
            var6.putInt(((IsoObject)var7).square.getY());
            var6.putInt(((IsoObject)var7).square.getZ());
            var6.putByte((byte)((IsoObject)var7).square.getObjects().indexOf(var7));
            var6.putByte((byte)var7.getContainerIndex(var2));
            var6.putInt(1);
            var6.putInt(var3.id);
         }

         PacketType.RemoveInventoryItemFromContainer.send(var5);
      }
   }

    void sendAddedRemovedItems(bool var1) {
    bool var2 = var1 || this.itemSendFrequency.Check();
      if (!SystemDisabler.doWorldSyncEnable && !this.itemsToSendRemove.empty() && var2) {
         for (Entry var4 : this.itemsToSendRemove.entrySet()) {
    ItemContainer var5 = (ItemContainer)var4.getKey();
    std::vector var6 = (std::vector)var4.getValue();
    void* var7 = var5.getParent();
            if (var5.getContainingItem() != nullptr && var5.getContainingItem().getWorldItem() != nullptr) {
               var7 = var5.getContainingItem().getWorldItem();
            }

            if (var7 != nullptr && ((IsoObject)var7).square != nullptr) {
               try {
    ByteBufferWriter var8 = connection.startPacket();
                  PacketType.RemoveInventoryItemFromContainer.doPacket(var8);
                  if (dynamic_cast<IsoDeadBody*>(var7) != nullptr) {
                     var8.putShort((short)0);
                     var8.putInt(((IsoObject)var7).square.getX());
                     var8.putInt(((IsoObject)var7).square.getY());
                     var8.putInt(((IsoObject)var7).square.getZ());
                     var8.putByte((byte)var7.getStaticMovingObjectIndex());
                  } else if (dynamic_cast<IsoWorldInventoryObject*>(var7) != nullptr) {
                     var8.putShort((short)1);
                     var8.putInt(((IsoObject)var7).square.getX());
                     var8.putInt(((IsoObject)var7).square.getY());
                     var8.putInt(((IsoObject)var7).square.getZ());
                     var8.putInt(((IsoWorldInventoryObject)var7).getItem().id);
                  } else if (dynamic_cast<BaseVehicle*>(var7) != nullptr) {
                     var8.putShort((short)3);
                     var8.putInt(((IsoObject)var7).square.getX());
                     var8.putInt(((IsoObject)var7).square.getY());
                     var8.putInt(((IsoObject)var7).square.getZ());
                     var8.putShort(((BaseVehicle)var7).VehicleID);
                     var8.putByte((byte)var5.vehiclePart.getIndex());
                  } else {
                     var8.putShort((short)2);
                     var8.putInt(((IsoObject)var7).square.getX());
                     var8.putInt(((IsoObject)var7).square.getY());
                     var8.putInt(((IsoObject)var7).square.getZ());
                     var8.putByte((byte)((IsoObject)var7).square.getObjects().indexOf(var7));
                     var8.putByte((byte)var7.getContainerIndex(var5));
                  }

                  var8.putInt(var6.size());

                  for (int var23 = 0; var23 < var6.size(); var23++) {
    InventoryItem var10 = (InventoryItem)var6.get(var23);
                     var8.putInt(var10.id);
                  }

                  PacketType.RemoveInventoryItemFromContainer.send(connection);
               } catch (Exception var16) {
                  DebugLog.log("sendAddedRemovedItems: itemsToSendRemove container:" + var5 + "." + var7 + " items:" + var6);
                  if (var6 != nullptr) {
                     for (int var9 = 0; var9 < var6.size(); var9++) {
                        if (var6.get(var9) == nullptr) {
                           DebugLog.log("item:nullptr");
                        } else {
                           DebugLog.log("item:" + ((InventoryItem)var6.get(var9)).getName());
                        }
                     }

                     DebugLog.log("itemSize:" + var6.size());
                  }

                  var16.printStackTrace();
                  connection.cancelPacket();
               }
            }
         }

         this.itemsToSendRemove.clear();
      }

      if (!this.itemsToSend.empty() && var2) {
         for (Entry var18 : this.itemsToSend.entrySet()) {
    ItemContainer var19 = (ItemContainer)var18.getKey();
    std::vector var20 = (std::vector)var18.getValue();
    void* var21 = var19.getParent();
            if (var19.getContainingItem() != nullptr && var19.getContainingItem().getWorldItem() != nullptr) {
               var21 = var19.getContainingItem().getWorldItem();
            }

            if (var21 != nullptr && ((IsoObject)var21).square != nullptr) {
               try {
    ByteBufferWriter var22 = connection.startPacket();
                  PacketType.AddInventoryItemToContainer.doPacket(var22);
                  if (dynamic_cast<IsoDeadBody*>(var21) != nullptr) {
                     var22.putShort((short)0);
                     var22.putInt(((IsoObject)var21).square.getX());
                     var22.putInt(((IsoObject)var21).square.getY());
                     var22.putInt(((IsoObject)var21).square.getZ());
                     var22.putByte((byte)var21.getStaticMovingObjectIndex());

                     try {
                        CompressIdenticalItems.save(var22.bb, var20, nullptr);
                     } catch (Exception var14) {
                        var14.printStackTrace();
                     }
                  } else if (dynamic_cast<IsoWorldInventoryObject*>(var21) != nullptr) {
                     var22.putShort((short)1);
                     var22.putInt(((IsoObject)var21).square.getX());
                     var22.putInt(((IsoObject)var21).square.getY());
                     var22.putInt(((IsoObject)var21).square.getZ());
                     var22.putInt(((IsoWorldInventoryObject)var21).getItem().id);

                     try {
                        CompressIdenticalItems.save(var22.bb, var20, nullptr);
                     } catch (Exception var13) {
                        var13.printStackTrace();
                     }
                  } else if (dynamic_cast<BaseVehicle*>(var21) != nullptr) {
                     var22.putShort((short)3);
                     var22.putInt(((IsoObject)var21).square.getX());
                     var22.putInt(((IsoObject)var21).square.getY());
                     var22.putInt(((IsoObject)var21).square.getZ());
                     var22.putShort(((BaseVehicle)var21).VehicleID);
                     var22.putByte((byte)var19.vehiclePart.getIndex());

                     try {
                        CompressIdenticalItems.save(var22.bb, var20, nullptr);
                     } catch (Exception var12) {
                        var12.printStackTrace();
                     }
                  } else {
                     var22.putShort((short)2);
                     var22.putInt(((IsoObject)var21).square.getX());
                     var22.putInt(((IsoObject)var21).square.getY());
                     var22.putInt(((IsoObject)var21).square.getZ());
                     var22.putByte((byte)((IsoObject)var21).square.getObjects().indexOf(var21));
                     var22.putByte((byte)var21.getContainerIndex(var19));

                     try {
                        CompressIdenticalItems.save(var22.bb, var20, nullptr);
                     } catch (Exception var11) {
                        var11.printStackTrace();
                     }
                  }

                  PacketType.AddInventoryItemToContainer.send(connection);
               } catch (Exception var15) {
                  DebugLog.log("sendAddedRemovedItems: itemsToSend container:" + var19 + "." + var21 + " items:" + var20);
                  if (var20 != nullptr) {
                     for (int var24 = 0; var24 < var20.size(); var24++) {
                        if (var20.get(var24) == nullptr) {
                           DebugLog.log("item:nullptr");
                        } else {
                           DebugLog.log("item:" + ((InventoryItem)var20.get(var24)).getName());
                        }
                     }

                     DebugLog.log("itemSize:" + var20.size());
                  }

                  var15.printStackTrace();
                  connection.cancelPacket();
               }
            }
         }

         this.itemsToSend.clear();
      }
   }

    void checkAddedRemovedItems(IsoObject var1) {
      if (var1 != nullptr) {
         if (!this.itemsToSend.empty() || !this.itemsToSendRemove.empty()) {
            if (dynamic_cast<IsoDeadBody*>(var1) != nullptr) {
               if (this.itemsToSend.containsKey(var1.getContainer()) || this.itemsToSendRemove.containsKey(var1.getContainer())) {
                  this.sendAddedRemovedItems(true);
               }
            } else if (dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr) {
    InventoryItem var4 = ((IsoWorldInventoryObject)var1).getItem();
               if (dynamic_cast<InventoryContainer*>(var4) != nullptr) {
    ItemContainer var5 = ((InventoryContainer)var4).getInventory();
                  if (this.itemsToSend.containsKey(var5) || this.itemsToSendRemove.containsKey(var5)) {
                     this.sendAddedRemovedItems(true);
                  }
               }
            } else if (!(dynamic_cast<BaseVehicle*>(var1) != nullptr)) {
               for (int var2 = 0; var2 < var1.getContainerCount(); var2++) {
    ItemContainer var3 = var1.getContainerByIndex(var2);
                  if (this.itemsToSend.containsKey(var3) || this.itemsToSendRemove.containsKey(var3)) {
                     this.sendAddedRemovedItems(true);
                     return;
                  }
               }
            }
         }
      }
   }

    void sendReplaceOnCooked(InventoryItem var1) {
    IsoObject var2 = var1.getOutermostContainer().getParent();
      if (var2 != nullptr) {
         this.checkAddedRemovedItems(var2);
    ByteBufferWriter var3 = connection.startPacket();
         PacketType.ReplaceOnCooked.doPacket(var3);
         var3.putInt(var2.square.getX());
         var3.putInt(var2.square.getY());
         var3.putInt(var2.square.getZ());
         var3.putByte((byte)var2.square.getObjects().indexOf(var2));
         var3.putByte((byte)var2.getContainerIndex(var1.getContainer()));
         var3.putInt(var1.getID());
         PacketType.ReplaceOnCooked.send(connection);
      }
   }

    void writeItemStats(ByteBufferWriter var1, InventoryItem var2) {
      var1.putInt(var2.id);
      var1.putInt(var2.getUses());
      var1.putFloat(dynamic_cast<DrainableComboItem*>(var2) != nullptr ? ((DrainableComboItem)var2).getUsedDelta() : 0.0F);
      if (dynamic_cast<Food*>(var2) != nullptr var3) {
         var1.putBoolean(true);
         var1.putFloat(var3.getHungChange());
         var1.putFloat(var3.getCalories());
         var1.putFloat(var3.getCarbohydrates());
         var1.putFloat(var3.getLipids());
         var1.putFloat(var3.getProteins());
         var1.putFloat(var3.getThirstChange());
         var1.putInt(var3.getFluReduction());
         var1.putFloat(var3.getPainReduction());
         var1.putFloat(var3.getEndChange());
         var1.putInt(var3.getReduceFoodSickness());
         var1.putFloat(var3.getStressChange());
         var1.putFloat(var3.getFatigueChange());
      } else {
         var1.putBoolean(false);
      }
   }

    void sendItemStats(InventoryItem var1) {
      if (var1 != nullptr) {
         if (var1.getWorldItem() != nullptr && var1.getWorldItem().getWorldObjectIndex() != -1) {
    IsoWorldInventoryObject var6 = var1.getWorldItem();
    ByteBufferWriter var7 = connection.startPacket();
            PacketType.ItemStats.doPacket(var7);
            var7.putShort((short)1);
            var7.putInt(var6.square.getX());
            var7.putInt(var6.square.getY());
            var7.putInt(var6.square.getZ());
            this.writeItemStats(var7, var1);
            PacketType.ItemStats.send(connection);
         } else if (var1.getContainer() == nullptr) {
            DebugLog.log("ERROR: sendItemStats(): item is neither in a container nor on the ground");
            if (Core.bDebug) {
               throw std::make_unique<IllegalStateException>();
            }
         } else {
    ItemContainer var2 = var1.getContainer();
    void* var3 = var2.getParent();
            if (var2.getContainingItem() != nullptr && var2.getContainingItem().getWorldItem() != nullptr) {
               var3 = var2.getContainingItem().getWorldItem();
            }

            if (dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr) {
    InventoryItem var5 = ((IsoWorldInventoryObject)var3).getItem();
               if (!(dynamic_cast<InventoryContainer*>(var5) != nullptr) || var2 != ((InventoryContainer)var5).getInventory()) {
                  DebugLog.log("ERROR: sendItemStats() parent=" + var3 + " item=" + var1);
                  if (Core.bDebug) {
                     throw std::make_unique<IllegalStateException>();
                  } else {
                     return;
                  }
               }
            } else if (dynamic_cast<BaseVehicle*>(var3) != nullptr) {
               if (var2.vehiclePart == nullptr || var2.vehiclePart.getItemContainer() != var2 || var2.vehiclePart.getVehicle() != var3) {
                  DebugLog.log("ERROR: sendItemStats() parent=" + var3 + " item=" + var1);
                  if (Core.bDebug) {
                     throw std::make_unique<IllegalStateException>();
                  }

                  return;
               }
            } else if (dynamic_cast<IsoDeadBody*>(var3) != nullptr) {
               if (var2 != var3.getContainer()) {
                  DebugLog.log("ERROR: sendItemStats() parent=" + var3 + " item=" + var1);
                  if (Core.bDebug) {
                     throw std::make_unique<IllegalStateException>();
                  }

                  return;
               }
            } else if (var3 == nullptr || var3.getContainerIndex(var2) == -1) {
               DebugLog.log("ERROR: sendItemStats() parent=" + var3 + " item=" + var1);
               if (Core.bDebug) {
                  throw std::make_unique<IllegalStateException>();
               }

               return;
            }

    ByteBufferWriter var8 = connection.startPacket();
            PacketType.ItemStats.doPacket(var8);
            if (dynamic_cast<IsoDeadBody*>(var3) != nullptr) {
               var8.putShort((short)0);
               var8.putInt(((IsoObject)var3).square.getX());
               var8.putInt(((IsoObject)var3).square.getY());
               var8.putInt(((IsoObject)var3).square.getZ());
               var8.putByte((byte)var3.getStaticMovingObjectIndex());
            } else if (dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr) {
               var8.putShort((short)1);
               var8.putInt(((IsoObject)var3).square.getX());
               var8.putInt(((IsoObject)var3).square.getY());
               var8.putInt(((IsoObject)var3).square.getZ());
            } else if (dynamic_cast<BaseVehicle*>(var3) != nullptr) {
               var8.putShort((short)3);
               var8.putInt(((IsoObject)var3).square.getX());
               var8.putInt(((IsoObject)var3).square.getY());
               var8.putInt(((IsoObject)var3).square.getZ());
               var8.putShort(((BaseVehicle)var3).VehicleID);
               var8.putByte((byte)var2.vehiclePart.getIndex());
            } else {
               var8.putShort((short)2);
               var8.putInt(((IsoObject)var3).square.getX());
               var8.putInt(((IsoObject)var3).square.getY());
               var8.putInt(((IsoObject)var3).square.getZ());
               var8.putByte((byte)var3.getObjectIndex());
               var8.putByte((byte)var3.getContainerIndex(var2));
            }

            this.writeItemStats(var8, var1);
            PacketType.ItemStats.send(connection);
         }
      }
   }

    void PlayWorldSound(const std::string& var1, int var2, int var3, uint8_t var4) {
    PlayWorldSoundPacket var5 = std::make_shared<PlayWorldSoundPacket>();
      var5.set(var1, var2, var3, var4);
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.PlayWorldSound.doPacket(var6);
      var5.write(var6);
      PacketType.PlayWorldSound.send(connection);
   }

    void PlaySound(const std::string& var1, bool var2, IsoMovingObject var3) {
    PlaySoundPacket var4 = std::make_shared<PlaySoundPacket>();
      var4.set(var1, var2, var3);
    ByteBufferWriter var5 = connection.startPacket();
      PacketType.PlaySound.doPacket(var5);
      var4.write(var5);
      PacketType.PlaySound.send(connection);
   }

    void StopSound(IsoMovingObject var1, const std::string& var2, bool var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.StopSound.doPacket(var4);
    StopSoundPacket var5 = std::make_shared<StopSoundPacket>();
      var5.set(var1, var2, var3);
      var5.write(var4);
      PacketType.StopSound.send(connection);
   }

    void startLocalServer() {
      bClient = true;
      ip = "127.0.0.1";
      Thread var1 = std::make_shared<Thread>(
         ThreadGroups.Workers,
         () -> {
    std::string var0 = System.getProperty("file.separator");
    std::string var1x = System.getProperty("java.class.path");
    std::string var2 = System.getProperty("java.home") + var0 + "bin" + var0 + "java";
            ProcessBuilder var3 = std::make_shared<ProcessBuilder>(
               var2,
               "-Xms2048m",
               "-Xmx2048m",
               "-Djava.library.path=../natives/",
               "-cp",
               "lwjgl.jar;lwjgl_util.jar;sqlitejdbc-v056.jar;../bin/",
               "zombie.network.GameServer"
            );
            var3.redirectErrorStream(true);
    Process var4 = nullptr;

            try {
               var4 = var3.start();
            } catch (IOException var10) {
               var10.printStackTrace();
            }

    InputStreamReader var5 = std::make_shared<InputStreamReader>(var4.getInputStream());
    bool var6 = false;

            try {
               while (!var5.ready()) {
    int var7;
                  try {
                     while ((var7 = var5.read()) != -1) {
                        System.out.print((char)var7);
                     }
                  } catch (IOException var11) {
                     var11.printStackTrace();
                  }

                  try {
                     var5.close();
                  } catch (IOException var9) {
                     var9.printStackTrace();
                  }
               }
            } catch (IOException var12) {
               var12.printStackTrace();
            }
         }
      );
      var1.setUncaughtExceptionHandler(GameWindow::uncaughtException);
      var1.start();
   }

    static void sendPing() {
      if (bClient) {
    ByteBufferWriter var0 = connection.startPingPacket();
         PacketTypes.doPingPacket(var0);
         var0.putLong(System.currentTimeMillis());
         var0.putLong(0L);
         connection.endPingPacket();
      }
   }

    static void registerZone(Zone var0, bool var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.RegisterZone.doPacket(var2);
      var2.putUTF(var0.name);
      var2.putUTF(var0.type);
      var2.putInt(var0.x);
      var2.putInt(var0.y);
      var2.putInt(var0.z);
      var2.putInt(var0.w);
      var2.putInt(var0.h);
      var2.putInt(var0.getLastActionTimestamp());
      var2.putBoolean(var1);
      PacketType.RegisterZone.send(connection);
   }

    static void receiveHelicopter(ByteBuffer var0, short var1) {
    float var2 = var0.getFloat();
    float var3 = var0.getFloat();
    bool var4 = var0.get() == 1;
      if (IsoWorld.instance != nullptr && IsoWorld.instance.helicopter != nullptr) {
         IsoWorld.instance.helicopter.clientSync(var2, var3, var4);
      }
   }

    static void receiveVehicles(ByteBuffer var0, short var1) {
      VehicleManager.instance.clientPacket(var0);
   }

    static void receiveVehicleAuthorization(ByteBuffer var0, short var1) {
    VehicleAuthorizationPacket var2 = std::make_shared<VehicleAuthorizationPacket>();
      var2.parse(var0, connection);
      if (var2.isConsistent()) {
         var2.process();
      }
   }

    static void receiveTimeSync(ByteBuffer var0, short var1) {
      GameTime.receiveTimeSync(var0, connection);
   }

    static void sendSafehouse(SafeHouse var0, bool var1) {
    SyncSafehousePacket var2 = std::make_shared<SyncSafehousePacket>();
      var2.set(var0, var1);
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SyncSafehouse.doPacket(var3);
      var2.write(var3);
      PacketType.SyncSafehouse.send(connection);
   }

    static void receiveSyncSafehouse(ByteBuffer var0, short var1) {
    SyncSafehousePacket var2 = std::make_shared<SyncSafehousePacket>();
      var2.parse(var0, connection);
      var2.process();
      LuaEventManager.triggerEvent("OnSafehousesChanged");
   }

    static void sendKickOutOfSafehouse(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.KickOutOfSafehouse.doPacket(var1);
      var1.putShort(var0.getOnlineID());
      PacketType.KickOutOfSafehouse.send(connection);
   }

    IsoPlayer getPlayerFromUsername(const std::string& var1) {
    std::vector var2 = this.getPlayers();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoPlayer var4 = (IsoPlayer)var2.get(var3);
         if (var4.getUsername() == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    static void destroy(IsoObject var0) {
      if (ServerOptions.instance.AllowDestructionBySledgehammer.getValue()) {
    ByteBufferWriter var1 = connection.startPacket();
         PacketType.SledgehammerDestroy.doPacket(var1);
    IsoGridSquare var2 = var0.getSquare();
         var1.putInt(var2.getX());
         var1.putInt(var2.getY());
         var1.putInt(var2.getZ());
         var1.putInt(var2.getObjects().indexOf(var0));
         PacketType.SledgehammerDestroy.send(connection);
         var2.RemoveTileObject(var0);
      }
   }

    static void sendTeleport(IsoPlayer var0, float var1, float var2, float var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.Teleport.doPacket(var4);
      GameWindow.WriteString(var4.bb, var0.getUsername());
      var4.putFloat(var1);
      var4.putFloat(var2);
      var4.putFloat(var3);
      PacketType.Teleport.send(connection);
   }

    static void sendStopFire(IsoGridSquare var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.StopFire.doPacket(var1);
      var1.putByte((byte)0);
      var1.putInt(var0.getX());
      var1.putInt(var0.getY());
      var1.putInt(var0.getZ());
      PacketType.StopFire.send(connection);
   }

    static void sendStopFire(IsoGameCharacter var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.StopFire.doPacket(var1);
      if (dynamic_cast<IsoPlayer*>(var0) != nullptr) {
         var1.putByte((byte)1);
         var1.putShort(var0.getOnlineID());
      }

      if (dynamic_cast<IsoZombie*>(var0) != nullptr) {
         var1.putByte((byte)2);
         var1.putShort(((IsoZombie)var0).OnlineID);
      }

      PacketType.StopFire.send(connection);
   }

    void sendCataplasm(int var1, int var2, float var3, float var4, float var5) {
    ByteBufferWriter var6 = connection.startPacket();
      PacketType.Cataplasm.doPacket(var6);
      var6.putShort((short)var1);
      var6.putInt(var2);
      var6.putFloat(var3);
      var6.putFloat(var4);
      var6.putFloat(var5);
      PacketType.Cataplasm.send(connection);
   }

    static void receiveBodyDamageUpdate(ByteBuffer var0, short var1) {
      BodyDamageSync.instance.clientPacket(var0);
   }

    static void receiveRadioDeviceDataState(ByteBuffer var0, short var1) {
    uint8_t var2 = var0.get();
      if (var2 == 1) {
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
         if (var7 != nullptr && var6 >= 0 && var6 < var7.getObjects().size()) {
    IsoObject var8 = (IsoObject)var7.getObjects().get(var6);
            if (dynamic_cast<IsoWaveSignal*>(var8) != nullptr) {
    DeviceData var9 = ((IsoWaveSignal)var8).getDeviceData();
               if (var9 != nullptr) {
                  try {
                     var9.receiveDeviceDataStatePacket(var0, nullptr);
                  } catch (Exception var13) {
                     System.out.print(var13.getMessage());
                  }
               }
            }
         }
      } else if (var2 == 0) {
    short var14 = var0.getShort();
    IsoPlayer var16 = IDToPlayerMap.get(var14);
    uint8_t var18 = var0.get();
         if (var16 != nullptr) {
    Radio var20 = nullptr;
            if (var18 == 1 && var16.getPrimaryHandItem() instanceof Radio) {
               var20 = (Radio)var16.getPrimaryHandItem();
            }

            if (var18 == 2 && var16.getSecondaryHandItem() instanceof Radio) {
               var20 = (Radio)var16.getSecondaryHandItem();
            }

            if (var20 != nullptr && var20.getDeviceData() != nullptr) {
               try {
                  var20.getDeviceData().receiveDeviceDataStatePacket(var0, connection);
               } catch (Exception var12) {
                  System.out.print(var12.getMessage());
               }
            }
         }
      } else if (var2 == 2) {
    short var15 = var0.getShort();
    short var17 = var0.getShort();
    BaseVehicle var19 = VehicleManager.instance.getVehicleByID(var15);
         if (var19 != nullptr) {
    VehiclePart var21 = var19.getPartByIndex(var17);
            if (var21 != nullptr) {
    DeviceData var22 = var21.getDeviceData();
               if (var22 != nullptr) {
                  try {
                     var22.receiveDeviceDataStatePacket(var0, nullptr);
                  } catch (Exception var11) {
                     System.out.print(var11.getMessage());
                  }
               }
            }
         }
      }
   }

    static void sendRadioServerDataRequest() {
    ByteBufferWriter var0 = connection.startPacket();
      PacketType.RadioServerData.doPacket(var0);
      PacketType.RadioServerData.send(connection);
   }

    static void receiveRadioServerData(ByteBuffer var0, short var1) {
    ZomboidRadio var2 = ZomboidRadio.getInstance();
    int var3 = var0.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
    std::string var5 = GameWindow.ReadString(var0);
    int var6 = var0.getInt();

         for (int var7 = 0; var7 < var6; var7++) {
    int var8 = var0.getInt();
    std::string var9 = GameWindow.ReadString(var0);
            var2.addChannelName(var9, var8, var5);
         }
      }

      var2.setHasRecievedServerData(true);
      ZomboidRadio.POST_RADIO_SILENCE = var0.get() == 1;
   }

    static void receiveRadioPostSilence(ByteBuffer var0, short var1) {
      ZomboidRadio.POST_RADIO_SILENCE = var0.get() == 1;
   }

   public static void sendIsoWaveSignal(
      int var0, int var1, int var2, std::string var3, std::string var4, std::string var5, float var6, float var7, float var8, int var9, boolean var10
   ) {
    ByteBufferWriter var11 = connection.startPacket();
      PacketType.WaveSignal.doPacket(var11);

      try {
    WaveSignal var12 = std::make_shared<WaveSignal>();
         var12.set(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
         var12.write(var11);
         PacketType.WaveSignal.send(connection);
      } catch (Exception var13) {
         connection.cancelPacket();
         DebugLog.Multiplayer.printException(var13, "SendIsoWaveSignal: failed", LogSeverity.Error);
      }
   }

    static void receiveWaveSignal(ByteBuffer var0, short var1) {
      if (ChatManager.getInstance().isWorking()) {
    WaveSignal var2 = std::make_shared<WaveSignal>();
         var2.parse(var0, connection);
         var2.process(connection);
      }
   }

    static void sendPlayerListensChannel(int var0, bool var1, bool var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.PlayerListensChannel.doPacket(var3);
      var3.putInt(var0);
      var3.putByte((byte)(var1 ? 1 : 0));
      var3.putByte((byte)(var2 ? 1 : 0));
      PacketType.PlayerListensChannel.send(connection);
   }

    static void receiveSyncFurnace(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 == nullptr) {
         instance.delayPacket(var2, var3, var4);
      } else {
         if (var5 != nullptr) {
    BSFurnace var6 = nullptr;

            for (int var7 = 0; var7 < var5.getObjects().size(); var7++) {
               if (var5.getObjects().get(var7) instanceof BSFurnace) {
                  var6 = (BSFurnace)var5.getObjects().get(var7);
                  break;
               }
            }

            if (var6 == nullptr) {
               DebugLog.log("receiveFurnaceChange: furnace is nullptr x,y,z=" + var2 + "," + var3 + "," + var4);
               return;
            }

            var6.fireStarted = var0.get() == 1;
            var6.fuelAmount = var0.getFloat();
            var6.fuelDecrease = var0.getFloat();
            var6.heat = var0.getFloat();
            var6.sSprite = GameWindow.ReadString(var0);
            var6.sLitSprite = GameWindow.ReadString(var0);
            var6.updateLight();
         }
      }
   }

    static void sendFurnaceChange(BSFurnace var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.SyncFurnace.doPacket(var1);
      var1.putInt(var0.getSquare().getX());
      var1.putInt(var0.getSquare().getY());
      var1.putInt(var0.getSquare().getZ());
      var1.putByte((byte)(var0.isFireStarted() ? 1 : 0));
      var1.putFloat(var0.getFuelAmount());
      var1.putFloat(var0.getFuelDecrease());
      var1.putFloat(var0.getHeat());
      GameWindow.WriteString(var1.bb, var0.sSprite);
      GameWindow.WriteString(var1.bb, var0.sLitSprite);
      PacketType.SyncFurnace.send(connection);
   }

    static void sendCompost(IsoCompost var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.SyncCompost.doPacket(var1);
      var1.putInt(var0.getSquare().getX());
      var1.putInt(var0.getSquare().getY());
      var1.putInt(var0.getSquare().getZ());
      var1.putFloat(var0.getCompost());
      PacketType.SyncCompost.send(connection);
   }

    static void receiveSyncCompost(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 != nullptr) {
    IsoCompost var6 = var5.getCompost();
         if (var6 == nullptr) {
            var6 = std::make_shared<IsoCompost>(var5.getCell(), var5);
            var5.AddSpecialObject(var6);
         }

         var6.setCompost(var0.getFloat());
         var6.updateSprite();
      }
   }

    void requestUserlog(const std::string& var1) {
      if (canSeePlayerStats()) {
    ByteBufferWriter var2 = connection.startPacket();
         PacketType.Userlog.doPacket(var2);
         GameWindow.WriteString(var2.bb, var1);
         PacketType.Userlog.send(connection);
      }
   }

    void addUserlog(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (canSeePlayerStats()) {
    ByteBufferWriter var4 = connection.startPacket();
         PacketType.AddUserlog.doPacket(var4);
         GameWindow.WriteString(var4.bb, var1);
         GameWindow.WriteString(var4.bb, var2);
         GameWindow.WriteString(var4.bb, var3);
         PacketType.AddUserlog.send(connection);
      }
   }

    void removeUserlog(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (canModifyPlayerStats()) {
    ByteBufferWriter var4 = connection.startPacket();
         PacketType.RemoveUserlog.doPacket(var4);
         GameWindow.WriteString(var4.bb, var1);
         GameWindow.WriteString(var4.bb, var2);
         GameWindow.WriteString(var4.bb, var3);
         PacketType.RemoveUserlog.send(connection);
      }
   }

    void addWarningPoint(const std::string& var1, const std::string& var2, int var3) {
      if (canModifyPlayerStats()) {
    ByteBufferWriter var4 = connection.startPacket();
         PacketType.AddWarningPoint.doPacket(var4);
         GameWindow.WriteString(var4.bb, var1);
         GameWindow.WriteString(var4.bb, var2);
         var4.putInt(var3);
         PacketType.AddWarningPoint.send(connection);
      }
   }

    static void receiveMessageForAdmin(ByteBuffer var0, short var1) {
      if (canSeePlayerStats()) {
    std::string var2 = GameWindow.ReadString(var0);
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
         LuaEventManager.triggerEvent("OnAdminMessage", var2, var3, var4, var5);
      }
   }

    void wakeUpPlayer(IsoPlayer var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.WakeUpPlayer.doPacket(var2);
      var2.putShort((short)var1.getPlayerNum());
      PacketType.WakeUpPlayer.send(connection);
   }

    static void receiveWakeUpPlayer(ByteBuffer var0, short var1) {
    IsoPlayer var2 = IDToPlayerMap.get(var0.getShort());
      if (var2 != nullptr) {
         SleepingEvent.instance.wakeUp(var2, true);
      }
   }

    void getDBSchema() {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.GetDBSchema.doPacket(var1);
      PacketType.GetDBSchema.send(connection);
   }

    static void receiveGetDBSchema(ByteBuffer var0, short var1) {
      if ((connection.accessLevel & 3) <= 0) {
         instance.dbSchema = LuaManager.platform.newTable();
    int var2 = var0.getInt();

         for (int var3 = 0; var3 < var2; var3++) {
    KahluaTable var4 = LuaManager.platform.newTable();
    std::string var5 = GameWindow.ReadString(var0);
    int var6 = var0.getInt();

            for (int var7 = 0; var7 < var6; var7++) {
    KahluaTable var8 = LuaManager.platform.newTable();
    std::string var9 = GameWindow.ReadString(var0);
    std::string var10 = GameWindow.ReadString(var0);
               var8.rawset("name", var9);
               var8.rawset("type", var10);
               var4.rawset(var7, var8);
            }

            instance.dbSchema.rawset(var5, var4);
         }

         LuaEventManager.triggerEvent("OnGetDBSchema", instance.dbSchema);
      }
   }

    void getTableResult(const std::string& var1, int var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.GetTableResult.doPacket(var3);
      var3.putInt(var2);
      var3.putUTF(var1);
      PacketType.GetTableResult.send(connection);
   }

    static void receiveGetTableResult(ByteBuffer var0, short var1) {
    std::vector var2 = new std::vector();
    int var3 = var0.getInt();
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
    std::vector var6 = new std::vector();

      for (int var7 = 0; var7 < var5; var7++) {
    DBResult var8 = std::make_shared<DBResult>();
         var8.setTableName(var4);
    int var9 = var0.getInt();

         for (int var10 = 0; var10 < var9; var10++) {
    std::string var11 = GameWindow.ReadString(var0);
    std::string var12 = GameWindow.ReadString(var0);
            var8.getValues().put(var11, var12);
            if (var7 == 0) {
               var6.push_back(var11);
            }
         }

         var8.setColumns(var6);
         var2.push_back(var8);
      }

      LuaEventManager.triggerEvent("OnGetTableResult", var2, var3, var4);
   }

    void executeQuery(const std::string& var1, KahluaTable var2) {
      if (connection.accessLevel == 32) {
    ByteBufferWriter var3 = connection.startPacket();
         PacketType.ExecuteQuery.doPacket(var3);

         try {
            var3.putUTF(var1);
            var2.save(var3.bb);
         } catch (Throwable var8) {
            ExceptionLogger.logException(var8);
         } finally {
            PacketType.ExecuteQuery.send(connection);
         }
      }
   }

   public std::vector<IsoPlayer> getConnectedPlayers() {
      return this.connectedPlayers;
   }

    static void sendNonPvpZone(NonPvpZone var0, bool var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SyncNonPvpZone.doPacket(var2);
      var0.save(var2.bb);
      var2.putBoolean(var1);
      PacketType.SyncNonPvpZone.send(connection);
   }

    static void sendFaction(Faction var0, bool var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SyncFaction.doPacket(var2);
      var0.writeToBuffer(var2, var1);
      PacketType.SyncFaction.send(connection);
   }

    static void sendFactionInvite(Faction var0, IsoPlayer var1, const std::string& var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SendFactionInvite.doPacket(var3);
      var3.putUTF(var0.getName());
      var3.putUTF(var1.getUsername());
      var3.putUTF(var2);
      PacketType.SendFactionInvite.send(connection);
   }

    static void receiveSendFactionInvite(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
      LuaEventManager.triggerEvent("ReceiveFactionInvite", var2, var3);
   }

    static void acceptFactionInvite(Faction var0, const std::string& var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.AcceptedFactionInvite.doPacket(var2);
      var2.putUTF(var0.getName());
      var2.putUTF(var1);
      PacketType.AcceptedFactionInvite.send(connection);
   }

    static void receiveAcceptedFactionInvite(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    Faction var4 = Faction.getFaction(var2);
      if (var4 != nullptr) {
         var4.addPlayer(var3);
      }

      LuaEventManager.triggerEvent("AcceptedFactionInvite", var2, var3);
   }

    static void addTicket(const std::string& var0, const std::string& var1, int var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.AddTicket.doPacket(var3);
      var3.putUTF(var0);
      var3.putUTF(var1);
      var3.putInt(var2);
      PacketType.AddTicket.send(connection);
   }

    static void getTickets(const std::string& var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ViewTickets.doPacket(var1);
      var1.putUTF(var0);
      PacketType.ViewTickets.send(connection);
   }

    static void receiveViewTickets(ByteBuffer var0, short var1) {
    std::vector var2 = new std::vector();
    int var3 = var0.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
    DBTicket var5 = std::make_shared<DBTicket>(GameWindow.ReadString(var0), GameWindow.ReadString(var0), var0.getInt());
         var2.push_back(var5);
         if (var0.get() == 1) {
    DBTicket var6 = std::make_shared<DBTicket>(GameWindow.ReadString(var0), GameWindow.ReadString(var0), var0.getInt());
            var6.setIsAnswer(true);
            var5.setAnswer(var6);
         }
      }

      LuaEventManager.triggerEvent("ViewTickets", var2);
   }

    static void receiveChecksum(ByteBuffer var0, short var1) {
      NetChecksum.comparer.clientPacket(var0);
   }

    static void removeTicket(int var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.RemoveTicket.doPacket(var1);
      var1.putInt(var0);
      PacketType.RemoveTicket.send(connection);
   }

    static bool sendItemListNet(IsoPlayer var0, std::vector<InventoryItem> var1, IsoPlayer var2, const std::string& var3, const std::string& var4) {
    ByteBufferWriter var5 = connection.startPacket();
      PacketType.SendItemListNet.doPacket(var5);
      var5.putByte((byte)(var2 != nullptr ? 1 : 0));
      if (var2 != nullptr) {
         var5.putShort(var2.getOnlineID());
      }

      var5.putByte((byte)(var0 != nullptr ? 1 : 0));
      if (var0 != nullptr) {
         var5.putShort(var0.getOnlineID());
      }

      GameWindow.WriteString(var5.bb, var3);
      var5.putByte((byte)(var4 != nullptr ? 1 : 0));
      if (var4 != nullptr) {
         GameWindow.WriteString(var5.bb, var4);
      }

      try {
         CompressIdenticalItems.save(var5.bb, var1, nullptr);
      } catch (Exception var7) {
         var7.printStackTrace();
         connection.cancelPacket();
    return false;
      }

      PacketType.SendItemListNet.send(connection);
    return true;
   }

    static void receiveSendItemListNet(ByteBuffer var0, short var1) {
    IsoPlayer var2 = nullptr;
      if (var0.get() != 1) {
         var2 = IDToPlayerMap.get(var0.getShort());
      }

    IsoPlayer var3 = nullptr;
      if (var0.get() == 1) {
         var3 = IDToPlayerMap.get(var0.getShort());
      }

    std::string var4 = GameWindow.ReadString(var0);
    std::string var5 = nullptr;
      if (var0.get() == 1) {
         var5 = GameWindow.ReadString(var0);
      }

    short var6 = var0.getShort();
    std::vector var7 = new std::vector(var6);

      try {
         for (int var8 = 0; var8 < var6; var8++) {
    InventoryItem var9 = InventoryItem.loadItem(var0, 195);
            if (var9 != nullptr) {
               var7.push_back(var9);
            }
         }
      } catch (IOException var10) {
         var10.printStackTrace();
      }

      LuaEventManager.triggerEvent("OnReceiveItemListNet", var3, var7, var2, var4, var5);
   }

    void requestTrading(IsoPlayer var1, IsoPlayer var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.RequestTrading.doPacket(var3);
      var3.putShort(var1.OnlineID);
      var3.putShort(var2.OnlineID);
      var3.putByte((byte)0);
      PacketType.RequestTrading.send(connection);
   }

    void acceptTrading(IsoPlayer var1, IsoPlayer var2, bool var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.RequestTrading.doPacket(var4);
      var4.putShort(var2.OnlineID);
      var4.putShort(var1.OnlineID);
      var4.putByte((byte)(var3 ? 1 : 2));
      PacketType.RequestTrading.send(connection);
   }

    static void receiveRequestTrading(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    uint8_t var3 = var0.get();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
      if (var4 != nullptr) {
         if (var3 == 0) {
            LuaEventManager.triggerEvent("RequestTrade", var4);
         } else {
            LuaEventManager.triggerEvent("AcceptedTrade", var3 == 1);
         }
      }
   }

    void tradingUISendAddItem(IsoPlayer var1, IsoPlayer var2, InventoryItem var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.TradingUIAddItem.doPacket(var4);
      var4.putShort(var1.OnlineID);
      var4.putShort(var2.OnlineID);

      try {
         var3.saveWithSize(var4.bb, false);
      } catch (IOException var6) {
         var6.printStackTrace();
      }

      PacketType.TradingUIAddItem.send(connection);
   }

    static void receiveTradingUIAddItem(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    void* var3 = nullptr;

      try {
         var3 = InventoryItem.loadItem(var0, 195);
      } catch (Exception var5) {
         var5.printStackTrace();
         return;
      }

      if (var3 != nullptr) {
    IsoPlayer var4 = IDToPlayerMap.get(var2);
         if (var4 != nullptr) {
            LuaEventManager.triggerEvent("TradingUIAddItem", var4, var3);
         }
      }
   }

    void tradingUISendRemoveItem(IsoPlayer var1, IsoPlayer var2, int var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.TradingUIRemoveItem.doPacket(var4);
      var4.putShort(var1.OnlineID);
      var4.putShort(var2.OnlineID);
      var4.putInt(var3);
      PacketType.TradingUIRemoveItem.send(connection);
   }

    static void receiveTradingUIRemoveItem(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
      if (var4 != nullptr) {
         LuaEventManager.triggerEvent("TradingUIRemoveItem", var4, var3);
      }
   }

    void tradingUISendUpdateState(IsoPlayer var1, IsoPlayer var2, int var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.TradingUIUpdateState.doPacket(var4);
      var4.putShort(var1.OnlineID);
      var4.putShort(var2.OnlineID);
      var4.putInt(var3);
      PacketType.TradingUIUpdateState.send(connection);
   }

    static void receiveTradingUIUpdateState(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
      if (var4 != nullptr) {
         LuaEventManager.triggerEvent("TradingUIUpdateState", var4, var3);
      }
   }

    static void sendBuildingStashToDo(const std::string& var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.ReadAnnotedMap.doPacket(var1);
      var1.putUTF(var0);
      PacketType.ReadAnnotedMap.send(connection);
   }

    static void setServerStatisticEnable(bool var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.StatisticRequest.doPacket(var1);
      var1.putBoolean(var0);
      PacketType.StatisticRequest.send(connection);
      MPStatistic.clientStatisticEnable = var0;
   }

    static bool getServerStatisticEnable() {
      return MPStatistic.clientStatisticEnable;
   }

    static void sendRequestInventory(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.RequestInventory.doPacket(var1);
      var1.putShort(IsoPlayer.getInstance().getOnlineID());
      var1.putShort(var0.getOnlineID());
      PacketType.RequestInventory.send(connection);
   }

    int sendInventoryPutItems(ByteBufferWriter var1, InventoryItem> var2, long var3) {
    int var5 = var2.size();
    Iterator var6 = var2.keySet().iterator();

      while (var6.hasNext()) {
    InventoryItem var7 = (InventoryItem)var2.get(var6.next());
         var1.putUTF(var7.getModule());
         var1.putUTF(var7.getType());
         var1.putLong(var7.getID());
         var1.putLong(var3);
         var1.putBoolean(IsoPlayer.getInstance().isEquipped(var7));
         if (dynamic_cast<DrainableComboItem*>(var7) != nullptr) {
            var1.putFloat(((DrainableComboItem)var7).getUsedDelta());
         } else {
            var1.putFloat(var7.getCondition());
         }

         var1.putInt(var7.getCount());
         if (dynamic_cast<DrainableComboItem*>(var7) != nullptr) {
            var1.putUTF(Translator.getText("IGUI_ItemCat_Drainable"));
         } else {
            var1.putUTF(var7.getCategory());
         }

         var1.putUTF(var7.getContainer().getType());
         var1.putBoolean(var7.getWorker() != nullptr && var7.getWorker() == "inInv"));
         if (dynamic_cast<InventoryContainer*>(var7) != nullptr
            && ((InventoryContainer)var7).getItemContainer() != nullptr
            && !((InventoryContainer)var7).getItemContainer().getItems().empty()) {
    LinkedHashMap var8 = ((InventoryContainer)var7).getItemContainer().getItems4Admin();
            var5 += var8.size();
            this.sendInventoryPutItems(var1, var8, var7.getID());
         }
      }

    return var5;
   }

    static void receiveRequestInventory(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SendInventory.doPacket(var3);
      var3.putShort(var2);
    int var4 = var3.bb.position();
      var3.putInt(0);
      var3.putFloat(IsoPlayer.getInstance().getInventory().getCapacityWeight());
      var3.putFloat(IsoPlayer.getInstance().getMaxWeight());
    LinkedHashMap var5 = IsoPlayer.getInstance().getInventory().getItems4Admin();
    int var6 = instance.sendInventoryPutItems(var3, var5, -1L);
    int var7 = var3.bb.position();
      var3.bb.position(var4);
      var3.putInt(var6);
      var3.bb.position(var7);
      PacketType.SendInventory.send(connection);
   }

    static void receiveSendInventory(ByteBuffer var0, short var1) {
    int var2 = var0.getInt();
    float var3 = var0.getFloat();
    float var4 = var0.getFloat();
    KahluaTable var5 = LuaManager.platform.newTable();
      var5.rawset("capacityWeight", (double)var3);
      var5.rawset("maxWeight", (double)var4);

      for (int var6 = 0; var6 < var2; var6++) {
    KahluaTable var7 = LuaManager.platform.newTable();
    std::string var8 = GameWindow.ReadStringUTF(var0) + "." + GameWindow.ReadStringUTF(var0);
    long var9 = var0.getLong();
    long var11 = var0.getLong();
    bool var13 = var0.get() == 1;
    float var14 = var0.getFloat();
    int var15 = var0.getInt();
    std::string var16 = GameWindow.ReadStringUTF(var0);
    std::string var17 = GameWindow.ReadStringUTF(var0);
    bool var18 = var0.get() == 1;
         var7.rawset("fullType", var8);
         var7.rawset("itemId", var9);
         var7.rawset("isEquip", var13);
         var7.rawset("var", Math.round(var14 * 100.0) / 100.0);
         var7.rawset("count", var15 + "");
         var7.rawset("cat", var16);
         var7.rawset("parrentId", var11);
         var7.rawset("hasParrent", var11 != -1L);
         var7.rawset("container", var17);
         var7.rawset("inInv", var18);
         var5.rawset(var5.size() + 1, var7);
      }

      LuaEventManager.triggerEvent("MngInvReceiveItems", var5);
   }

    static void sendGetItemInvMng(long var0) {
   }

    static void receiveSpawnRegion(ByteBuffer var0, short var1) {
      if (instance.ServerSpawnRegions == nullptr) {
         instance.ServerSpawnRegions = LuaManager.platform.newTable();
      }

    int var2 = var0.getInt();
    KahluaTable var3 = LuaManager.platform.newTable();

      try {
         var3.load(var0, 195);
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      instance.ServerSpawnRegions.rawset(var2, var3);
   }

    static void receivePlayerConnectLoading(ByteBuffer var0) {
    int var1 = var0.position();
      if (!instance.receivePlayerConnectWhileLoading(var0)) {
         var0.position(var1);
         throw std::make_unique<IOException>();
      }
   }

    static void receiveClimateManagerPacket(ByteBuffer var0, short var1) {
    ClimateManager var2 = ClimateManager.getInstance();
      if (var2 != nullptr) {
         try {
            var2.receiveClimatePacket(var0, nullptr);
         } catch (Exception var4) {
            var4.printStackTrace();
         }
      }
   }

    static void receiveServerMap(ByteBuffer var0, short var1) {
      ClientServerMap.receivePacket(var0);
   }

    static void receivePassengerMap(ByteBuffer var0, short var1) {
      PassengerMap.clientReceivePacket(var0);
   }

    static void receiveIsoRegionServerPacket(ByteBuffer var0, short var1) {
      IsoRegions.receiveServerUpdatePacket(var0);
   }

    static void sendIsoRegionDataRequest() {
    ByteBufferWriter var0 = connection.startPacket();
      PacketType.IsoRegionClientRequestFullUpdate.doPacket(var0);
      PacketType.IsoRegionClientRequestFullUpdate.send(connection);
   }

    void sendSandboxOptionsToServer(SandboxOptions var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.SandboxOptions.doPacket(var2);

      try {
         var1.save(var2.bb);
      } catch (IOException var7) {
         ExceptionLogger.logException(var7);
      } finally {
         PacketType.SandboxOptions.send(connection);
      }
   }

    static void receiveSandboxOptions(ByteBuffer var0, short var1) {
      try {
         SandboxOptions.instance.load(var0);
         SandboxOptions.instance.applySettings();
         SandboxOptions.instance.toLua();
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

    static void receiveChunkObjectState(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    short var3 = var0.getShort();
    IsoChunk var4 = IsoWorld.instance.CurrentCell.getChunk(var2, var3);
      if (var4 != nullptr) {
         try {
            var4.loadObjectState(var0);
         } catch (Throwable var6) {
            ExceptionLogger.logException(var6);
         }
      }
   }

    static void receivePlayerLeaveChat(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processLeaveChatPacket(var0);
   }

    static void receiveInitPlayerChat(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processInitPlayerChatPacket(var0);
   }

    static void receiveAddChatTab(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processAddTabPacket(var0);
   }

    static void receiveRemoveChatTab(ByteBuffer var0, short var1) {
      ChatManager.getInstance().processRemoveTabPacket(var0);
   }

    static void receivePlayerNotFound(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadStringUTF(var0);
      ChatManager.getInstance().processPlayerNotFound(var2);
   }

    static void sendZombieHelmetFall(IsoPlayer var0, IsoGameCharacter var1, InventoryItem var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.ZombieHelmetFalling.doPacket(var3);
      var3.putByte((byte)var0.PlayerIndex);
      var3.putShort(var1.getOnlineID());
      var3.putUTF(var2.getType());
      PacketType.ZombieHelmetFalling.send(connection);
   }

    static void receiveZombieHelmetFalling(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    IsoZombie var3 = (IsoZombie)IDToZombieMap.get(var2);
    std::string var4 = GameWindow.ReadString(var0);
      if (var3 != nullptr && !StringUtils.isNullOrEmpty(var4)) {
         var3.helmetFall(true, var4);
      }
   }

    static void sendPerks(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.SyncPerks.doPacket(var1);
      var1.putByte((byte)var0.PlayerIndex);
      var1.putInt(var0.getPerkLevel(Perks.Sneak));
      var1.putInt(var0.getPerkLevel(Perks.Strength));
      var1.putInt(var0.getPerkLevel(Perks.Fitness));
      PacketType.SyncPerks.send(connection);
   }

    static void receiveSyncPerks(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    IsoPlayer var6 = IDToPlayerMap.get(var2);
      if (var6 != nullptr && !var6.isLocalPlayer()) {
         var6.remoteSneakLvl = var3;
         var6.remoteStrLvl = var4;
         var6.remoteFitLvl = var5;
      }
   }

    static void sendWeight(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.SyncWeight.doPacket(var1);
      var1.putByte((byte)var0.PlayerIndex);
      var1.putDouble(var0.getNutrition().getWeight());
      PacketType.SyncWeight.send(connection);
   }

    static void receiveSyncWeight(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    double var3 = var0.getDouble();
    IsoPlayer var5 = IDToPlayerMap.get(var2);
      if (var5 != nullptr && !var5.isLocalPlayer()) {
         var5.getNutrition().setWeight(var3);
      }
   }

    static void receiveGlobalModData(ByteBuffer var0, short var1) {
      GlobalModData.instance.receive(var0);
   }

    static void sendSafehouseInvite(SafeHouse var0, IsoPlayer var1, const std::string& var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SendSafehouseInvite.doPacket(var3);
      var3.putUTF(var0.getTitle());
      var3.putUTF(var1.getUsername());
      var3.putUTF(var2);
      var3.putInt(var0.getX());
      var3.putInt(var0.getY());
      var3.putInt(var0.getW());
      var3.putInt(var0.getH());
      PacketType.SendSafehouseInvite.send(connection);
   }

    static void receiveSendSafehouseInvite(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    int var4 = var0.getInt();
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    SafeHouse var8 = SafeHouse.getSafeHouse(var4, var5, var6, var7);
      LuaEventManager.triggerEvent("ReceiveSafehouseInvite", var8, var3);
   }

    static void acceptSafehouseInvite(SafeHouse var0, const std::string& var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.AcceptedSafehouseInvite.doPacket(var2);
      var2.putUTF(var0.getTitle());
      var2.putUTF(var1);
      var2.putUTF(username);
      var2.putInt(var0.getX());
      var2.putInt(var0.getY());
      var2.putInt(var0.getW());
      var2.putInt(var0.getH());
      PacketType.AcceptedSafehouseInvite.send(connection);
   }

    static void receiveAcceptedSafehouseInvite(ByteBuffer var0, short var1) {
    std::string var2 = GameWindow.ReadString(var0);
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    int var5 = var0.getInt();
    int var6 = var0.getInt();
    int var7 = var0.getInt();
    int var8 = var0.getInt();
    SafeHouse var9 = SafeHouse.getSafeHouse(var5, var6, var7, var8);
      if (var9 != nullptr) {
         var9.addPlayer(var4);
      }

      LuaEventManager.triggerEvent("AcceptedSafehouseInvite", var9.getTitle(), var3);
   }

    static void sendEquippedRadioFreq(IsoPlayer var0) {
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.SyncEquippedRadioFreq.doPacket(var1);
      var1.putByte((byte)var0.PlayerIndex);
      var1.putInt(var0.invRadioFreq.size());

      for (int var2 = 0; var2 < var0.invRadioFreq.size(); var2++) {
         var1.putInt((int)var0.invRadioFreq.get(var2));
      }

      PacketType.SyncEquippedRadioFreq.send(connection);
   }

    static void receiveSyncEquippedRadioFreq(ByteBuffer var0, short var1) {
    short var2 = var0.getShort();
    int var3 = var0.getInt();
    IsoPlayer var4 = IDToPlayerMap.get(var2);
      if (var4 != nullptr) {
         var4.invRadioFreq.clear();

         for (int var5 = 0; var5 < var3; var5++) {
            var4.invRadioFreq.push_back(var0.getInt());
         }

         for (int var6 = 0; var6 < var4.invRadioFreq.size(); var6++) {
            System.out.println(var4.invRadioFreq.get(var6));
         }
      }
   }

    static void sendSneezingCoughing(short var0, int var1, uint8_t var2) {
    ByteBufferWriter var3 = connection.startPacket();
      PacketType.SneezeCough.doPacket(var3);
      var3.putShort(var0);
    uint8_t var4 = 0;
      if (var1 % 2 == 0) {
         var4 = (byte)(var4 | 1);
      }

      if (var1 > 2) {
         var4 = (byte)(var4 | 2);
      }

      if (var2 > 1) {
         var4 = (byte)(var4 | 4);
      }

      var3.putByte(var4);
      PacketType.SneezeCough.send(connection);
   }

    static void receiveSneezeCough(ByteBuffer var0, short var1) {
    IsoPlayer var2 = IDToPlayerMap.get(var0.getShort());
      if (var2 != nullptr) {
    uint8_t var3 = var0.get();
    bool var4 = (var3 & 1) == 0;
    bool var5 = (var3 & 2) != 0;
    int var6 = (var3 & 4) == 0 ? 1 : 2;
         var2.setVariable("Ext", var4 ? "Sneeze" + var6 : "Cough");
         var2.Say(Translator.getText("IGUI_PlayerText_" + (var4 ? "Sneeze" : "Cough") + (var5 ? "Muffled" : "")));
         var2.reportEvent("EventDoExt");
      }
   }

    static void sendBurnCorpse(short var0, short var1) {
    ByteBufferWriter var2 = connection.startPacket();
      PacketType.BurnCorpse.doPacket(var2);
      var2.putShort(var0);
      var2.putShort(var1);
      PacketType.SneezeCough.send(connection);
   }

    static void rememberPlayerPosition(IsoPlayer var0, float var1, float var2) {
      if (var0 != nullptr && !var0.isLocalPlayer()) {
         if (positions.containsKey(var0.getOnlineID())) {
            positions.get(var0.getOnlineID()).set(var1, var2);
         } else {
            positions.put(var0.getOnlineID(), std::make_shared<Vector2>(var1, var2));
         }

    WorldMapRemotePlayer var3 = WorldMapRemotePlayers.instance.getPlayerByID(var0.getOnlineID());
         if (var3 != nullptr) {
            var3.setPosition(var1, var2);
         }
      }
   }

    static void receiveValidatePacket(ByteBuffer var0, short var1) {
    ValidatePacket var2 = std::make_shared<ValidatePacket>();
      var2.parse(var0, connection);
      var2.log(connection, "receive-packet");
      if (var2.isConsistent()) {
         var2.process(connection);
      }
   }

    static void sendValidatePacket(ValidatePacket var0) {
      var0.log(connection, "send-packet");
    ByteBufferWriter var1 = connection.startPacket();
      PacketType.Validate.doPacket(var1);
      var0.write(var1);
      PacketType.Validate.send(connection);
   }
}
} // namespace network
} // namespace zombie
