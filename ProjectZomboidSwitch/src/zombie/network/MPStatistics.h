#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/management/OperatingSystemMXBean.h"
#include "java/text/NumberFormat.h"
#include "javax/management/NotificationEmitter.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MovingObjectUpdateScheduler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/RakVoice.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManagerData/VoiceDataSource.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/ZNetStatistics.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/popman/NetworkZombieManager.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class MPStatistics {
public:
    static const float MEM_USAGE_THRESHOLD = 0.95F;
    static const long REQUEST_TIMEOUT = 10000L;
    static const long STATISTICS_INTERVAL = 2000L;
    static const long PING_INTERVAL = 1000L;
    static const long PING_PERIOD = 10000L;
    static const long PING_LIMIT_PERIOD = 60000L;
    static const long PING_INTERVAL_COUNT = 60L;
    static const long PING_LIMIT_COUNT = 20L;
    static const long PING_LOG_COUNT = 120L;
    static const long MAX_PING_TO_SUM = 1000L;
    static const KahluaTable statsTable = LuaManager.platform.newTable();
    static const KahluaTable statusTable = LuaManager.platform.newTable();
    static const UpdateLimit ulRequestTimeout = std::make_shared<UpdateLimit>(10000L);
    static const UpdateLimit ulStatistics = std::make_shared<UpdateLimit>(2000L);
    static const UpdateLimit ulPing = std::make_shared<UpdateLimit>(1000L);
    static bool serverStatisticsEnabled = false;
    static int serverPlayers = 0;
    static int clientPlayers = 0;
    static int clientLastPing = -1;
    static int clientAvgPing = -1;
    static int clientMinPing = -1;
    static std::string clientVOIPSource = "";
    static std::string clientVOIPFreq = "";
    static long clientVOIPRX = 0L;
    static long clientVOIPTX = 0L;
    static long serverVOIPRX = 0L;
    static long serverVOIPTX = 0L;
    static int serverWaitingRequests = 0;
    static int clientSentRequests = 0;
    static int requested1 = 0;
    static int requested2 = 0;
    static int pending1 = 0;
    static int pending2 = 0;
    static long serverCPUCores = 0L;
    static long serverCPULoad = 0L;
    static long serverMemMax = 0L;
    static long serverMemFree = 0L;
    static long serverMemTotal = 0L;
    static long serverMemUsed = 0L;
    static long serverRX = 0L;
    static long serverTX = 0L;
    static long serverResent = 0L;
    static double serverLoss = 0.0;
    static float serverFPS = 0.0F;
    static long serverNetworkingUpdates = 0L;
    static long serverNetworkingFPS = 0L;
    static std::string serverRevision = "";
    static long clientCPUCores = 0L;
    static long clientCPULoad = 0L;
    static long clientMemMax = 0L;
    static long clientMemFree = 0L;
    static long clientMemTotal = 0L;
    static long clientMemUsed = 0L;
    static long clientRX = 0L;
    static long clientTX = 0L;
    static long clientResent = 0L;
    static double clientLoss = 0.0;
    static float clientFPS = 0.0F;
    static int serverStoredChunks = 0;
    static int serverRelevantChunks = 0;
    static int serverZombiesTotal = 0;
    static int serverZombiesLoaded = 0;
    static int serverZombiesSimulated = 0;
    static int serverZombiesCulled = 0;
    static int serverZombiesAuthorized = 0;
    static int serverZombiesUnauthorized = 0;
    static int serverZombiesReusable = 0;
    static int serverZombiesUpdated = 0;
    static int clientStoredChunks = 0;
    static int clientRelevantChunks = 0;
    static int clientZombiesTotal = 0;
    static int clientZombiesLoaded = 0;
    static int clientZombiesSimulated = 0;
    static int clientZombiesCulled = 0;
    static int clientZombiesAuthorized = 0;
    static int clientZombiesUnauthorized = 0;
    static int clientZombiesReusable = 0;
    static int clientZombiesUpdated = 0;
    static long zombieUpdates = 0L;
    static long serverMinPing = 0L;
    static long serverMaxPing = 0L;
    static long serverAvgPing = 0L;
    static long serverLastPing = 0L;
    static long serverLossPing = 0L;
    static long serverHandledPingPeriodStart = 0L;
    static int serverHandledPingPacketIndex = 0;
   private static const std::vector<int64_t> serverHandledPingHistory = std::make_unique<std::vector<>>();
   private static const std::unordered_set<int64_t> serverHandledLossPingHistory = std::make_unique<std::unordered_set<>>();
    static long pingIntervalCount = 60L;
    static long pingLimitCount = 20L;
    static long maxPingToSum = 1000L;

    static bool isClientStatisticsEnabled() {
    bool var0 = false;

      for (IsoPlayer var4 : IsoPlayer.players) {
         if (var4 != nullptr && var4.isShowMPInfos()) {
            var0 = true;
            break;
         }
      }

    return var0;
   }

    static void getClientZombieStatistics() {
    int var0 = (int)Math.max(MovingObjectUpdateScheduler.instance.getFrameCounter() - zombieUpdates, 1L);
      clientZombiesTotal = GameClient.IDToZombieMap.values().length;
      clientZombiesLoaded = IsoWorld.instance.getCell().getZombieList().size();
      clientZombiesSimulated = clientZombiesUpdated / var0;
      clientZombiesAuthorized = NetworkZombieSimulator.getInstance().getAuthorizedZombieCount();
      clientZombiesUnauthorized = NetworkZombieSimulator.getInstance().getUnauthorizedZombieCount();
      clientZombiesReusable = VirtualZombieManager.instance.reusableZombiesSize();
      clientZombiesCulled = 0;
      clientZombiesUpdated = 0;
      zombieUpdates = MovingObjectUpdateScheduler.instance.getFrameCounter();
      serverZombiesCulled = 0;
   }

    static void getServerZombieStatistics() {
    int var0 = (int)Math.max(MovingObjectUpdateScheduler.instance.getFrameCounter() - zombieUpdates, 1L);
      serverZombiesTotal = ServerMap.instance.ZombieMap.size();
      serverZombiesLoaded = IsoWorld.instance.getCell().getZombieList().size();
      serverZombiesSimulated = serverZombiesUpdated / var0;
      serverZombiesAuthorized = 0;
      serverZombiesUnauthorized = NetworkZombieManager.getInstance().getUnauthorizedZombieCount();
      serverZombiesReusable = VirtualZombieManager.instance.reusableZombiesSize();
      serverZombiesCulled = 0;
      serverZombiesUpdated = 0;
      zombieUpdates = MovingObjectUpdateScheduler.instance.getFrameCounter();
   }

    static void getClientChunkStatistics() {
      try {
         WorldStreamer.instance.getStatistics();
      } catch (Exception var1) {
         DebugLog.Multiplayer.printException(var1, "Error getting chunk statistics", LogSeverity.Error);
      }
   }

    static void countChunkRequests(int var0, int var1, int var2, int var3, int var4) {
      clientSentRequests = var0;
      requested1 = var1;
      requested2 = var2;
      pending1 = var3;
      pending2 = var4;
   }

    static void resetStatistic() {
      if (GameClient.bClient) {
         GameClient.connection.netStatistics = nullptr;
      } else if (GameServer.bServer) {
         for (UdpConnection var1 : GameServer.udpEngine.connections) {
            var1.netStatistics = nullptr;
         }
      }

      serverPlayers = 0;
      clientPlayers = 0;
      clientVOIPSource = "";
      clientVOIPFreq = "";
      clientVOIPRX = 0L;
      clientVOIPTX = 0L;
      serverVOIPRX = 0L;
      serverVOIPTX = 0L;
      serverCPUCores = 0L;
      serverCPULoad = 0L;
      serverRX = 0L;
      serverTX = 0L;
      serverResent = 0L;
      serverLoss = 0.0;
      serverFPS = 0.0F;
      serverNetworkingFPS = 0L;
      serverMemMax = 0L;
      serverMemFree = 0L;
      serverMemTotal = 0L;
      serverMemUsed = 0L;
      clientCPUCores = 0L;
      clientCPULoad = 0L;
      clientRX = 0L;
      clientTX = 0L;
      clientResent = 0L;
      clientLoss = 0.0;
      clientFPS = 0.0F;
      clientMemMax = 0L;
      clientMemFree = 0L;
      clientMemTotal = 0L;
      clientMemUsed = 0L;
      serverZombiesTotal = 0;
      serverZombiesLoaded = 0;
      serverZombiesSimulated = 0;
      serverZombiesCulled = 0;
      serverZombiesAuthorized = 0;
      serverZombiesUnauthorized = 0;
      serverZombiesReusable = 0;
      serverZombiesUpdated = 0;
      clientZombiesTotal = 0;
      clientZombiesLoaded = 0;
      clientZombiesSimulated = 0;
      clientZombiesCulled = 0;
      clientZombiesAuthorized = 0;
      clientZombiesUnauthorized = 0;
      clientZombiesReusable = 0;
      clientZombiesUpdated = 0;
      serverWaitingRequests = 0;
      clientSentRequests = 0;
      requested1 = 0;
      requested2 = 0;
      pending1 = 0;
      pending2 = 0;
   }

    static void getClientStatistics() {
      try {
         clientVOIPRX = 0L;
         clientVOIPTX = 0L;
         clientRX = 0L;
         clientTX = 0L;
         clientResent = 0L;
         clientLoss = 0.0;
    ZNetStatistics var0 = GameClient.connection.getStatistics();
         if (var0 != nullptr) {
            clientRX = var0.lastActualBytesReceived / 1000L;
            clientTX = var0.lastActualBytesSent / 1000L;
            clientResent = var0.lastUserMessageBytesResent / 1000L;
            clientLoss = var0.packetlossLastSecond / 1000.0;
         }

         long[] var1 = new long[]{-1L, -1L};
         if (RakVoice.GetChannelStatistics(GameClient.connection.getConnectedGUID(), var1)) {
            clientVOIPRX = var1[0] / 2000L;
            clientVOIPTX = var1[1] / 2000L;
         }

         clientFPS = 60.0F / GameTime.instance.FPSMultiplier;
         clientCPUCores = ManagementFactory.getOperatingSystemMXBean().getAvailableProcessors();
         clientCPULoad = (long)(((OperatingSystemMXBean)ManagementFactory.getOperatingSystemMXBean()).getProcessCpuLoad() * 100.0);
         clientMemMax = Runtime.getRuntime().maxMemory() / 1000L / 1000L;
         clientMemFree = Runtime.getRuntime().freeMemory() / 1000L / 1000L;
         clientMemTotal = Runtime.getRuntime().totalMemory() / 1000L / 1000L;
         clientMemUsed = clientMemTotal - clientMemFree;
         clientPlayers = 0;

         for (IsoPlayer var5 : IsoPlayer.players) {
            if (var5 != nullptr) {
               clientPlayers++;
            }
         }
      } catch (Exception var6) {
      }
   }

    static void getServerStatistics() {
      try {
         serverVOIPRX = 0L;
         serverVOIPTX = 0L;
         serverRX = 0L;
         serverTX = 0L;
         serverResent = 0L;
         serverLoss = 0.0;
         long[] var0 = new long[]{-1L, -1L};

         for (UdpConnection var2 : GameServer.udpEngine.connections) {
    ZNetStatistics var3 = var2.getStatistics();
            if (var3 != nullptr) {
               serverRX = serverRX + var2.netStatistics.lastActualBytesReceived;
               serverTX = serverTX + var2.netStatistics.lastActualBytesSent;
               serverResent = serverResent + var2.netStatistics.lastUserMessageBytesResent;
               serverLoss = serverLoss + var2.netStatistics.packetlossLastSecond;
            }

            if (RakVoice.GetChannelStatistics(var2.getConnectedGUID(), var0)) {
               serverVOIPRX = serverVOIPRX + var0[0];
               serverVOIPTX = serverVOIPTX + var0[1];
            }
         }

         serverRX /= 1000L;
         serverTX /= 1000L;
         serverResent /= 1000L;
         serverLoss /= 1000.0;
         serverVOIPRX /= 2000L;
         serverVOIPTX /= 2000L;
         serverFPS = 60.0F / GameTime.instance.FPSMultiplier;
         serverCPUCores = ManagementFactory.getOperatingSystemMXBean().getAvailableProcessors();
         serverCPULoad = (long)(((OperatingSystemMXBean)ManagementFactory.getOperatingSystemMXBean()).getProcessCpuLoad() * 100.0);
         serverNetworkingFPS = 1000L * serverNetworkingUpdates / 2000L;
         serverNetworkingUpdates = 0L;
         serverMemMax = Runtime.getRuntime().maxMemory() / 1000L / 1000L;
         serverMemFree = Runtime.getRuntime().freeMemory() / 1000L / 1000L;
         serverMemTotal = Runtime.getRuntime().totalMemory() / 1000L / 1000L;
         serverMemUsed = serverMemTotal - serverMemFree;
         serverPlayers = GameServer.IDToPlayerMap.size();
      } catch (Exception var4) {
      }
   }

    static void resetPingCounters() {
      clientLastPing = -1;
      clientAvgPing = -1;
      clientMinPing = -1;
   }

    static void getPing(UdpConnection var0) {
      try {
         if (var0 != nullptr) {
            clientLastPing = var0.getLastPing();
            clientAvgPing = var0.getAveragePing();
            clientMinPing = var0.getLowestPing();
         }
      } catch (Exception var2) {
      }
   }

    static long checkLatest(UdpConnection var0, long var1) {
      if (var0.pingHistory.size() >= pingIntervalCount) {
    long var3 = var0.pingHistory.stream().limit(pingIntervalCount).filter(var2 -> var2 > var1).count();
         if (var3 >= pingLimitCount) {
            return (long)Math.ceil(
               (float)var0.pingHistory.stream().limit(pingIntervalCount).mapToLong(var0x -> Math.min(maxPingToSum, var0x)).sum() / (float)pingIntervalCount
            );
         }
      }

    return 0L;
   }

    static void limitPing() {
    int var0 = ServerOptions.instance.PingLimit.getValue();

      for (UdpConnection var2 : GameServer.udpEngine.connections) {
         serverAvgPing = var2.getAveragePing();
         serverLastPing = var2.getLastPing();
         var2.pingHistory.addFirst(serverLastPing);
    long var3 = checkLatest(var2, var0);
         if (doKick(var2, var3)) {
            GameServer.kick(var2, "UI_Policy_Kick", "UI_OnConnectFailed_Ping");
            var2.forceDisconnect("kick-ping-limit");
            GameServer.addDisconnect(var2);
            DebugLog.Multiplayer.warn("Kick: player=\"%s\" type=\"%s\"", new Object[]{var2.username, "UI_OnConnectFailed_Ping"});
            DebugLog.Multiplayer.debugln("Ping: limit=%d/%d average-%d=%d", var0, pingLimitCount, pingIntervalCount, var3);
            DebugLog.Multiplayer.debugln("Ping: last-%d: %s", 120L, var2.pingHistory.stream().map(Object::toString).collect(Collectors.joining(", ")));
         }

         if (var2.pingHistory.size() > 120L) {
            var2.pingHistory.removeLast();
         }
      }
   }

    static bool doKickWhileLoading(UdpConnection var0, long var1) {
    int var3 = ServerOptions.instance.PingLimit.getValue();
      return var3 > ServerOptions.instance.PingLimit.getMin() && var1 > var3 && !var0.preferredInQueue && !PlayerType.isPrivileged(var0.accessLevel);
   }

    static bool doKick(UdpConnection var0, long var1) {
    return doKickWhileLoading();
   }

    static void resetServerHandledPingCounters() {
      serverMinPing = 0L;
      serverMaxPing = 0L;
      serverAvgPing = 0L;
      serverLastPing = 0L;
      serverLossPing = 0L;
      serverHandledPingPeriodStart = 0L;
      serverHandledPingPacketIndex = 0;
      serverHandledPingHistory.clear();
      serverHandledLossPingHistory.clear();
   }

    static void getServerHandledPing() {
    long var0 = System.currentTimeMillis();
      if (serverHandledPingPacketIndex == 10L) {
         serverMinPing = serverHandledPingHistory.stream().mapToLong(var0x -> var0x).min().orElse(0L);
         serverMaxPing = serverHandledPingHistory.stream().mapToLong(var0x -> var0x).max().orElse(0L);
         serverAvgPing = (long)serverHandledPingHistory.stream().mapToLong(var0x -> var0x).average().orElse(0.0);
         serverHandledPingHistory.clear();
         serverHandledPingPacketIndex = 0;
    int var2 = serverHandledLossPingHistory.size();
         serverHandledLossPingHistory.removeIf(var2x -> var0 > var2x + 10000L);
         serverLossPing = serverLossPing + (var2 - serverHandledLossPingHistory.size());
         serverHandledPingPeriodStart = var0;
      }

      GameClient.sendServerPing(var0);
      if (serverHandledLossPingHistory.size() > 1000) {
         serverHandledLossPingHistory.clear();
      }

      serverHandledLossPingHistory.push_back(var0);
      serverHandledPingPacketIndex++;
   }

    static void setVOIPSource(VoiceDataSource var0, int var1) {
      clientVOIPSource = VoiceDataSource.Unknown == var0) ? "" : var0.name();
      clientVOIPFreq = var1 == 0 ? "" : std::string.valueOf(var1 / 1000.0F);
   }

    static void countServerNetworkingFPS() {
      serverNetworkingUpdates++;
   }

    static void increaseStoredChunk() {
      if (GameClient.bClient) {
         clientStoredChunks++;
      } else if (GameServer.bServer) {
         serverStoredChunks++;
      }

      decreaseRelevantChunk();
   }

    static void decreaseStoredChunk() {
      if (GameClient.bClient) {
         clientStoredChunks--;
      } else if (GameServer.bServer) {
         serverStoredChunks--;
      }

      increaseRelevantChunk();
   }

    static void increaseRelevantChunk() {
      if (GameClient.bClient) {
         clientRelevantChunks++;
      } else if (GameServer.bServer) {
         serverRelevantChunks++;
      }
   }

    static void decreaseRelevantChunk() {
      if (GameClient.bClient) {
         clientRelevantChunks--;
      } else if (GameServer.bServer) {
         serverRelevantChunks--;
      }
   }

    static void Init() {
      if (GameServer.bServer || GameClient.bClient) {
         try {
            for (MemoryPoolMXBean var1 : ManagementFactory.getMemoryPoolMXBeans()) {
               if (MemoryType.HEAP == var1.getType()) && var1.isUsageThresholdSupported()) {
    long var2 = var1.getCollectionUsageThreshold();
    std::string var4 = System.getProperty("zomboid.thresholdm");
                  if (!StringUtils.isNullOrEmpty(var4)) {
                     var2 = int64_t.parseLong(var4) * 1000000L;
                  }

                  if (var2 == 0L) {
                     var2 = (long)((float)Runtime.getRuntime().maxMemory() * 0.95F);
                     var1.setUsageThreshold(var2);
                  }

                  if (var2 > 0L) {
                     ((NotificationEmitter)ManagementFactory.getMemoryMXBean())
                        .addNotificationListener(
                           (var1x, var2x) -> DebugLog.Multiplayer
                              .warn(
                                 "[%s] %s (%d) free=%s",
                                 new Object[]{
                                    MPStatistics.class.getSimpleName(),
                                    "java.management.memory.threshold.exceeded",
                                    var1.getUsageThresholdCount(),
                                    NumberFormat.getNumberInstance().format(Runtime.getRuntime().freeMemory())
                                 }
                              ),
                           var0x -> "java.management.memory.threshold.exceeded" == var0x.getType()),
                           nullptr
                        );
                  }

                  DebugLog.log(
                     DebugType.Multiplayer,
                     std::string.format(
                        "[%s] mem usage notification threshold=%s", MPStatistics.class.getSimpleName(), NumberFormat.getNumberInstance().format(var2)
                     )
                  );
                  break;
               }
            }
         } catch (Exception var5) {
            DebugLog.Multiplayer.printException(var5, std::string.format("[%s] init error", MPStatistics.class.getSimpleName()), LogSeverity.Error);
         }

         Reset();
      }
   }

    static void Reset() {
      resetPingCounters();
      resetServerHandledPingCounters();
      resetStatistic();
   }

    static void Update() {
      if (GameClient.bClient) {
         if (ulPing.Check()) {
            if (!isClientStatisticsEnabled() && !NetworkAIParams.isShowPingInfo()) {
               resetPingCounters();
               resetServerHandledPingCounters();
            } else {
               getPing(GameClient.connection);
               if (isClientStatisticsEnabled()) {
                  getServerHandledPing();
               } else {
                  resetServerHandledPingCounters();
               }
            }
         }

         if (isClientStatisticsEnabled()) {
            if (ulStatistics.Check()) {
               getClientStatistics();
               getClientZombieStatistics();
               getClientChunkStatistics();
            }
         } else {
            resetStatistic();
         }
      } else if (GameServer.bServer) {
         if (ulPing.Check()) {
            limitPing();
         }

         if (ulRequestTimeout.Check()) {
            serverStatisticsEnabled = false;
         }

         if (serverStatisticsEnabled) {
            if (ulStatistics.Check()) {
               getServerStatistics();
               getServerZombieStatistics();
            }
         } else {
            resetStatistic();
         }
      }
   }

    static void requested() {
      serverStatisticsEnabled = true;
      ulRequestTimeout.Reset(10000L);
   }

    static void clientZombieCulled() {
      clientZombiesCulled++;
   }

    static void serverZombieCulled() {
      serverZombiesCulled++;
   }

    static void clientZombieUpdated() {
      clientZombiesUpdated++;
   }

    static void serverZombieUpdated() {
      serverZombiesUpdated++;
   }

    static void write(UdpConnection var0, ByteBuffer var1) {
      var1.putLong(serverMemMax);
      var1.putLong(serverMemFree);
      var1.putLong(serverMemTotal);
      var1.putLong(serverMemUsed);
      var1.putLong(serverCPUCores);
      var1.putLong(serverCPULoad);
      var1.putLong(serverVOIPRX);
      var1.putLong(serverVOIPTX);
      var1.putLong(serverRX);
      var1.putLong(serverTX);
      var1.putLong(serverResent);
      var1.putDouble(serverLoss);
      var1.putFloat(serverFPS);
      var1.putLong(serverNetworkingFPS);
      var1.putInt(serverStoredChunks);
      var1.putInt(serverRelevantChunks);
      var1.putInt(serverZombiesTotal);
      var1.putInt(serverZombiesLoaded);
      var1.putInt(serverZombiesSimulated);
      var1.putInt(serverZombiesCulled);
      var1.putInt(NetworkZombieManager.getInstance().getAuthorizedZombieCount(var0));
      var1.putInt(serverZombiesUnauthorized);
      var1.putInt(serverZombiesReusable);
      var1.putInt(var0.playerDownloadServer.getWaitingRequests());
      var1.putInt(serverPlayers);
      GameWindow.WriteString(var1, "");
   }

    static void parse(ByteBuffer var0) {
    long var1 = System.currentTimeMillis();
    long var3 = var0.getLong();
      serverMemMax = var0.getLong();
      serverMemFree = var0.getLong();
      serverMemTotal = var0.getLong();
      serverMemUsed = var0.getLong();
      serverCPUCores = var0.getLong();
      serverCPULoad = var0.getLong();
      serverVOIPRX = var0.getLong();
      serverVOIPTX = var0.getLong();
      serverRX = var0.getLong();
      serverTX = var0.getLong();
      serverResent = var0.getLong();
      serverLoss = var0.getDouble();
      serverFPS = var0.getFloat();
      serverNetworkingFPS = var0.getLong();
      serverStoredChunks = var0.getInt();
      serverRelevantChunks = var0.getInt();
      serverZombiesTotal = var0.getInt();
      serverZombiesLoaded = var0.getInt();
      serverZombiesSimulated = var0.getInt();
      serverZombiesCulled = serverZombiesCulled + var0.getInt();
      serverZombiesAuthorized = var0.getInt();
      serverZombiesUnauthorized = var0.getInt();
      serverZombiesReusable = var0.getInt();
      serverWaitingRequests = var0.getInt();
      serverPlayers = var0.getInt();
      serverRevision = GameWindow.ReadString(var0);
      serverHandledLossPingHistory.remove(var3);
      if (var3 >= serverHandledPingPeriodStart) {
         serverLastPing = var1 - var3;
         serverHandledPingHistory.push_back(serverLastPing);
      }
   }

    static KahluaTable getLuaStatus() {
      statusTable.wipe();
      if (GameClient.bClient) {
         statusTable.rawset("serverTime", NumberFormat.getNumberInstance().format(TimeUnit.NANOSECONDS.toSeconds(GameTime.getServerTime())));
         statusTable.rawset("svnRevision", "");
         statusTable.rawset("buildDate", "");
         statusTable.rawset("buildTime", "");
         statusTable.rawset("version", Core.getInstance().getVersion());
         statusTable.rawset("lastPing", std::string.valueOf(clientLastPing));
         statusTable.rawset("avgPing", std::string.valueOf(clientAvgPing));
         statusTable.rawset("minPing", std::string.valueOf(clientMinPing));
      }

    return statusTable;
   }

    static KahluaTable getLuaStatistics() {
      statsTable.wipe();
      if (GameClient.bClient) {
         statsTable.rawset("clientTime", std::string.valueOf(TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis())));
         statsTable.rawset("serverTime", NumberFormat.getNumberInstance().format(TimeUnit.NANOSECONDS.toSeconds(GameTime.getServerTime())));
         statsTable.rawset("clientRevision", std::string.valueOf(""));
         statsTable.rawset("serverRevision", std::string.valueOf(serverRevision));
         statsTable.rawset("clientPlayers", std::string.valueOf(clientPlayers));
         statsTable.rawset("serverPlayers", std::string.valueOf(serverPlayers));
         statsTable.rawset("clientVOIPSource", std::string.valueOf(clientVOIPSource));
         statsTable.rawset("clientVOIPFreq", std::string.valueOf(clientVOIPFreq));
         statsTable.rawset("clientVOIPRX", std::string.valueOf(clientVOIPRX));
         statsTable.rawset("clientVOIPTX", std::string.valueOf(clientVOIPTX));
         statsTable.rawset("clientRX", std::string.valueOf(clientRX));
         statsTable.rawset("clientTX", std::string.valueOf(clientTX));
         statsTable.rawset("clientResent", std::string.valueOf(clientResent));
         statsTable.rawset("clientLoss", std::string.valueOf((int)clientLoss));
         statsTable.rawset("serverVOIPRX", std::string.valueOf(serverVOIPRX));
         statsTable.rawset("serverVOIPTX", std::string.valueOf(serverVOIPTX));
         statsTable.rawset("serverRX", std::string.valueOf(serverRX));
         statsTable.rawset("serverTX", std::string.valueOf(serverTX));
         statsTable.rawset("serverResent", std::string.valueOf(serverResent));
         statsTable.rawset("serverLoss", std::string.valueOf((int)serverLoss));
         statsTable.rawset("clientLastPing", std::string.valueOf(clientLastPing));
         statsTable.rawset("clientAvgPing", std::string.valueOf(clientAvgPing));
         statsTable.rawset("clientMinPing", std::string.valueOf(clientMinPing));
         statsTable.rawset("serverPingLast", std::string.valueOf(serverLastPing));
         statsTable.rawset("serverPingMin", std::string.valueOf(serverMinPing));
         statsTable.rawset("serverPingAvg", std::string.valueOf(serverAvgPing));
         statsTable.rawset("serverPingMax", std::string.valueOf(serverMaxPing));
         statsTable.rawset("serverPingLoss", std::string.valueOf(serverLossPing));
         statsTable.rawset("clientCPUCores", std::string.valueOf(clientCPUCores));
         statsTable.rawset("clientCPULoad", std::string.valueOf(clientCPULoad));
         statsTable.rawset("clientMemMax", std::string.valueOf(clientMemMax));
         statsTable.rawset("clientMemFree", std::string.valueOf(clientMemFree));
         statsTable.rawset("clientMemTotal", std::string.valueOf(clientMemTotal));
         statsTable.rawset("clientMemUsed", std::string.valueOf(clientMemUsed));
         statsTable.rawset("serverCPUCores", std::string.valueOf(serverCPUCores));
         statsTable.rawset("serverCPULoad", std::string.valueOf(serverCPULoad));
         statsTable.rawset("serverMemMax", std::string.valueOf(serverMemMax));
         statsTable.rawset("serverMemFree", std::string.valueOf(serverMemFree));
         statsTable.rawset("serverMemTotal", std::string.valueOf(serverMemTotal));
         statsTable.rawset("serverMemUsed", std::string.valueOf(serverMemUsed));
         statsTable.rawset("serverNetworkingFPS", std::string.valueOf((int)serverNetworkingFPS));
         statsTable.rawset("serverFPS", std::string.valueOf((int)serverFPS));
         statsTable.rawset("clientFPS", std::string.valueOf((int)clientFPS));
         statsTable.rawset("serverStoredChunks", std::string.valueOf(serverStoredChunks));
         statsTable.rawset("serverRelevantChunks", std::string.valueOf(serverRelevantChunks));
         statsTable.rawset("serverZombiesTotal", std::string.valueOf(serverZombiesTotal));
         statsTable.rawset("serverZombiesLoaded", std::string.valueOf(serverZombiesLoaded));
         statsTable.rawset("serverZombiesSimulated", std::string.valueOf(serverZombiesSimulated));
         statsTable.rawset("serverZombiesCulled", std::string.valueOf(serverZombiesCulled));
         statsTable.rawset("serverZombiesAuthorized", std::string.valueOf(serverZombiesAuthorized));
         statsTable.rawset("serverZombiesUnauthorized", std::string.valueOf(serverZombiesUnauthorized));
         statsTable.rawset("serverZombiesReusable", std::string.valueOf(serverZombiesReusable));
         statsTable.rawset("clientStoredChunks", std::string.valueOf(clientStoredChunks));
         statsTable.rawset("clientRelevantChunks", std::string.valueOf(clientRelevantChunks));
         statsTable.rawset("clientZombiesTotal", std::string.valueOf(clientZombiesTotal));
         statsTable.rawset("clientZombiesLoaded", std::string.valueOf(clientZombiesLoaded));
         statsTable.rawset("clientZombiesSimulated", std::string.valueOf(clientZombiesSimulated));
         statsTable.rawset("clientZombiesCulled", std::string.valueOf(clientZombiesCulled));
         statsTable.rawset("clientZombiesAuthorized", std::string.valueOf(clientZombiesAuthorized));
         statsTable.rawset("clientZombiesUnauthorized", std::string.valueOf(clientZombiesUnauthorized));
         statsTable.rawset("clientZombiesReusable", std::string.valueOf(clientZombiesReusable));
         statsTable.rawset("serverWaitingRequests", std::string.valueOf(serverWaitingRequests));
         statsTable.rawset("clientSentRequests", std::string.valueOf(clientSentRequests));
         statsTable.rawset("requested1", std::string.valueOf(requested1));
         statsTable.rawset("requested2", std::string.valueOf(requested2));
         statsTable.rawset("pending1", std::string.valueOf(pending1));
         statsTable.rawset("pending2", std::string.valueOf(pending2));
      }

    return statsTable;
   }
}
} // namespace network
} // namespace zombie
