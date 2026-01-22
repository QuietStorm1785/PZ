#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/network/MPStatistic/MainThreadStatistic.h"
#include "zombie/network/MPStatistic/ProbeStatistic.h"
#include "zombie/network/MPStatistic/SaveTasksStatistic.h"
#include "zombie/network/MPStatistic/ServerCellStatistic.h"
#include "zombie/network/MPStatistic/TasksStatistic.h"
#include "zombie/network/MPStatistic/ThreadStatistic.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class MPStatistic {
public:
    static MPStatistic instance;
    static bool doPrintStatistic = false;
    static bool doCSVStatistic = false;
    static int Period = 0;
    TasksStatistic LoaderThreadTasks = std::make_shared<TasksStatistic>();
    TasksStatistic RecalcThreadTasks = std::make_shared<TasksStatistic>();
    SaveTasksStatistic SaveTasks = std::make_shared<SaveTasksStatistic>();
    ServerCellStatistic ServerMapToLoad = std::make_shared<ServerCellStatistic>();
    ServerCellStatistic ServerMapLoadedCells = std::make_shared<ServerCellStatistic>();
    ServerCellStatistic ServerMapLoaded2 = std::make_shared<ServerCellStatistic>();
    int countServerChunkThreadSaveNow = 0;
    MainThreadStatistic Main = std::make_shared<MainThreadStatistic>(this);
    ThreadStatistic ServerLOS = std::make_shared<ThreadStatistic>();
    ThreadStatistic LoaderThread = std::make_shared<ThreadStatistic>();
    ThreadStatistic RecalcAllThread = std::make_shared<ThreadStatistic>();
    ThreadStatistic SaveThread = std::make_shared<ThreadStatistic>();
    ThreadStatistic PolyPathThread = std::make_shared<ThreadStatistic>();
    ThreadStatistic WorldReuser = std::make_shared<ThreadStatistic>();
    ThreadStatistic PlayerDownloadServer = std::make_shared<ThreadStatistic>();
    ThreadStatistic MapCollisionThread = std::make_shared<ThreadStatistic>();
    ProbeStatistic ChunkChecksum = std::make_shared<ProbeStatistic>();
    ProbeStatistic Bullet = std::make_shared<ProbeStatistic>();
    ProbeStatistic AnimationPlayerUpdate = std::make_shared<ProbeStatistic>();
    ProbeStatistic ServerMapPreupdate = std::make_shared<ProbeStatistic>();
    ProbeStatistic ServerMapPostupdate = std::make_shared<ProbeStatistic>();
    ProbeStatistic IngameStateUpdate = std::make_shared<ProbeStatistic>();
    long packetLength = 0L;
    int countIncomePackets = 0;
    int countOutcomePackets = 0;
    int countIncomeBytes = 0;
    int countOutcomeBytes = 0;
    int maxIncomeBytesPerSecond = 0;
    int maxOutcomeBytesPerSecond = 0;
    int currentIncomeBytesPerSecond = 0;
    int currentOutcomeBytesPerSecond = 0;
    long lastCalculateBPS = 0L;
    long lastReport = 0L;
    long minUpdatePeriod = 9999L;
    long maxUpdatePeriod = 0L;
    long avgUpdatePeriod = 0L;
    long currentAvgUpdatePeriod = 0L;
    long teleports = 0L;
    long counter1 = 0L;
    long counter2 = 0L;
    long counter3 = 0L;
    long updatePeriods = 0L;
    int loadCellFromDisk = 0;
    int saveCellToDisk = 0;
    static bool clientStatisticEnable = false;
    PrintStream csvStatisticFile = nullptr;
    PrintStream csvIncomePacketsFile = nullptr;
    PrintStream csvIncomeBytesFile = nullptr;
    PrintStream csvOutcomePacketsFile = nullptr;
    PrintStream csvOutcomeBytesFile = nullptr;
    PrintStream csvConnectionsFile = nullptr;
   private const std::vector<int> csvConnections = std::make_unique<std::vector<>>();
    KahluaTable table = nullptr;

    static MPStatistic getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<MPStatistic>();
      }

    return instance;
   }

    void IncrementServerChunkThreadSaveNow() {
      this.countServerChunkThreadSaveNow++;
   }

    void teleport() {
      this.teleports++;
   }

    void count1(long var1) {
      this.counter1 += var1;
   }

    void count2(long var1) {
      this.counter2 += var1;
   }

    void count3(long var1) {
      this.counter3 += var1;
   }

    void write(ByteBufferWriter var1) {
      var1.putLong(this.minUpdatePeriod);
      var1.putLong(this.maxUpdatePeriod);
      var1.putLong(this.currentAvgUpdatePeriod / this.updatePeriods);
      var1.putLong(this.updatePeriods / Period);
      var1.putLong(this.teleports);
      var1.putLong(GameServer.udpEngine.connections.size());
      var1.putLong(this.counter1 / this.updatePeriods);
      var1.putLong(this.counter2 / this.updatePeriods);
      var1.putLong(this.counter3 / this.updatePeriods);
   }

    void setPacketsLength(long var1) {
      this.packetLength = var1;
   }

    void addIncomePacket(PacketType var1, int var2) {
      if (var1 != nullptr) {
         var1.incomePackets++;
         this.countIncomePackets++;
         var1.incomeBytes += var2;
         this.countIncomeBytes += var2;
         this.currentIncomeBytesPerSecond += var2;
         this.calculateMaxBPS();
      }
   }

    void addOutcomePacket(short var1, int var2) {
    PacketType var3 = (PacketType)PacketTypes.packetTypes.get(var1);
      if (var3 != nullptr) {
         var3.outcomePackets++;
         this.countOutcomePackets++;
         var3.outcomeBytes += var2;
         this.countOutcomeBytes += var2;
         this.currentOutcomeBytesPerSecond += var2;
         this.calculateMaxBPS();
      }
   }

    void calculateMaxBPS() {
      if (System.currentTimeMillis() - this.lastCalculateBPS > 1000L) {
         this.lastCalculateBPS = System.currentTimeMillis();
         if (this.currentIncomeBytesPerSecond > this.maxIncomeBytesPerSecond) {
            this.maxIncomeBytesPerSecond = this.currentIncomeBytesPerSecond;
         }

         if (this.currentOutcomeBytesPerSecond > this.maxOutcomeBytesPerSecond) {
            this.maxOutcomeBytesPerSecond = this.currentOutcomeBytesPerSecond;
         }

         this.currentIncomeBytesPerSecond = 0;
         this.currentOutcomeBytesPerSecond = 0;
      }
   }

    void IncrementLoadCellFromDisk() {
      this.loadCellFromDisk++;
   }

    void IncrementSaveCellToDisk() {
      this.saveCellToDisk++;
   }

    void process(long var1) {
      if (var1 > this.maxUpdatePeriod) {
         this.maxUpdatePeriod = var1;
      }

      if (var1 < this.minUpdatePeriod) {
         this.minUpdatePeriod = var1;
      }

      this.avgUpdatePeriod = (long)((float)this.avgUpdatePeriod + (float)(var1 - this.avgUpdatePeriod) * 0.05F);
      this.currentAvgUpdatePeriod += var1;
      this.updatePeriods++;
      if (Period != 0 && System.currentTimeMillis() - this.lastReport >= Period * 1000L) {
         this.lastReport = System.currentTimeMillis();
         this.printStatistic();
         this.printCSVStatistic();
         GameServer.sendShortStatistic();
         this.table = LuaManager.platform.newTable();
         this.table.rawset("lastReport", (double)this.lastReport);
         this.table.rawset("period", (double)Period);
         this.table.rawset("minUpdatePeriod", (double)this.minUpdatePeriod);
         this.table.rawset("maxUpdatePeriod", (double)this.maxUpdatePeriod);
         this.table.rawset("avgUpdatePeriod", (double)this.avgUpdatePeriod);
         this.maxUpdatePeriod = 0L;
         this.minUpdatePeriod = 9999L;
         this.currentAvgUpdatePeriod = 0L;
         this.updatePeriods = 0L;
         this.teleports = 0L;
         this.counter1 = 0L;
         this.counter2 = 0L;
         this.counter3 = 0L;
         this.table.rawset("loadCellFromDisk", (double)this.loadCellFromDisk);
         this.table.rawset("saveCellToDisk", (double)this.saveCellToDisk);
         this.loadCellFromDisk = 0;
         this.saveCellToDisk = 0;
         this.table.rawset("usedMemory", (double)(Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory()));
         this.table.rawset("totalMemory", (double)Runtime.getRuntime().totalMemory());
         this.table.rawset("freeMemory", (double)Runtime.getRuntime().freeMemory());
         this.table.rawset("countConnections", (double)GameServer.udpEngine.connections.size());
    KahluaTable var3 = LuaManager.platform.newTable();

         for (int var4 = 0; var4 < GameServer.udpEngine.connections.size(); var4++) {
    KahluaTable var5 = LuaManager.platform.newTable();
    UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var4);
            var5.rawset("ip", var6.ip);
            var5.rawset("username", var6.username);
            var5.rawset("accessLevel", var6.accessLevel);
    KahluaTable var7 = LuaManager.platform.newTable();

            for (int var8 = 0; var8 < var6.players.length; var8++) {
               if (var6.players[var8] != nullptr) {
    KahluaTable var9 = LuaManager.platform.newTable();
                  var9.rawset("username", var6.players[var8].username);
                  var9.rawset("x", (double)var6.players[var8].x);
                  var9.rawset("y", (double)var6.players[var8].y);
                  var9.rawset("z", (double)var6.players[var8].z);
                  var7.rawset(var8, var9);
               }
            }

            var5.rawset("users", var7);
            var5.rawset("diff", (double)var6.statistic.diff);
            var5.rawset("pingAVG", (double)var6.statistic.pingAVG);
            var5.rawset("remotePlayersCount", (double)var6.statistic.remotePlayersCount);
            var5.rawset("remotePlayersDesyncAVG", (double)var6.statistic.remotePlayersDesyncAVG);
            var5.rawset("remotePlayersDesyncMax", (double)var6.statistic.remotePlayersDesyncMax);
            var5.rawset("remotePlayersTeleports", (double)var6.statistic.remotePlayersTeleports);
            var5.rawset("zombiesCount", (double)var6.statistic.zombiesCount);
            var5.rawset("zombiesLocalOwnership", (double)var6.statistic.zombiesLocalOwnership);
            var5.rawset("zombiesDesyncAVG", (double)var6.statistic.zombiesDesyncAVG);
            var5.rawset("zombiesDesyncMax", (double)var6.statistic.zombiesDesyncMax);
            var5.rawset("zombiesTeleports", (double)var6.statistic.zombiesTeleports);
            var5.rawset("FPS", (double)var6.statistic.FPS);
            var5.rawset("FPSMin", (double)var6.statistic.FPSMin);
            var5.rawset("FPSAvg", (double)var6.statistic.FPSAvg);
            var5.rawset("FPSMax", (double)var6.statistic.FPSMax);
    KahluaTable var18 = LuaManager.platform.newTable();
    short var21 = 0;

            for (int var10 = 0; var10 < 32; var10++) {
               var18.rawset(var10, (double)var6.statistic.FPSHistogramm[var10]);
               if (var21 < var6.statistic.FPSHistogramm[var10]) {
                  var21 = var6.statistic.FPSHistogramm[var10];
               }
            }

            var5.rawset("FPSHistogram", var18);
            var5.rawset("FPSHistogramMax", (double)var21);
            var3.rawset(var4, var5);
         }

         this.table.rawset("connections", var3);
         this.table.rawset("packetLength", (double)this.packetLength);
         this.table.rawset("countIncomePackets", (double)this.countIncomePackets);
         this.table.rawset("countIncomeBytes", (double)this.countIncomeBytes);
         this.table.rawset("maxIncomeBytesPerSecound", (double)this.maxIncomeBytesPerSecond);
    KahluaTable var11 = LuaManager.platform.newTable();
    int var12 = -1;

         for (PacketType var16 : PacketTypes.packetTypes.values()) {
            if (var16.incomePackets > 0) {
    KahluaTable var19 = LuaManager.platform.newTable();
               var19.rawset("name", var16.name());
               var19.rawset("count", (double)var16.incomePackets);
               var19.rawset("bytes", (double)var16.incomeBytes);
               var11.rawset(var12, var19);
            }

            var16.incomePackets = 0;
            var16.incomeBytes = 0;
         }

         this.table.rawset("incomePacketsTable", var11);
         this.countIncomePackets = 0;
         this.countIncomeBytes = 0;
         this.maxIncomeBytesPerSecond = 0;
         this.table.rawset("countOutcomePackets", (double)this.countOutcomePackets);
         this.table.rawset("countOutcomeBytes", (double)this.countOutcomeBytes);
         this.table.rawset("maxOutcomeBytesPerSecound", (double)this.maxOutcomeBytesPerSecond);
    KahluaTable var15 = LuaManager.platform.newTable();
         var12 = -1;

         for (PacketType var20 : PacketTypes.packetTypes.values()) {
            if (var20.outcomePackets > 0) {
    KahluaTable var22 = LuaManager.platform.newTable();
               var22.rawset("name", var20.name());
               var22.rawset("count", (double)var20.outcomePackets);
               var22.rawset("bytes", (double)var20.outcomeBytes);
               var15.rawset(var12++, var22);
            }

            var20.outcomePackets = 0;
            var20.outcomeBytes = 0;
         }

         this.table.rawset("outcomePacketsTable", var15);
         this.countOutcomePackets = 0;
         this.countOutcomeBytes = 0;
         this.maxOutcomeBytesPerSecond = 0;
         this.LoaderThreadTasks.Clear();
         this.RecalcThreadTasks.Clear();
         this.SaveTasks.Clear();
         this.ServerMapToLoad.Clear();
         this.ServerMapLoadedCells.Clear();
         this.ServerMapLoaded2.Clear();
         this.countServerChunkThreadSaveNow = 0;
         this.Main.Clear();
         this.ServerLOS.Clear();
         this.LoaderThread.Clear();
         this.RecalcAllThread.Clear();
         this.SaveThread.Clear();
         this.PolyPathThread.Clear();
         this.WorldReuser.Clear();
         this.PlayerDownloadServer.Clear();
         this.MapCollisionThread.Clear();
         this.ChunkChecksum.Clear();
         this.Bullet.Clear();
         this.AnimationPlayerUpdate.Clear();
         this.ServerMapPreupdate.Clear();
         this.ServerMapPostupdate.Clear();
         this.IngameStateUpdate.Clear();
         GameServer.getStatisticFromClients();
         GameServer.sendStatistic();
      }
   }

    void printStatistic() {
      if (doPrintStatistic) {
         DebugLog.Statistic.println("=== STATISTICS ===");
         DebugLog.Statistic.println("UpdatePeriod (mils) min:" + this.minUpdatePeriod + " max:" + this.maxUpdatePeriod + " avg:" + this.avgUpdatePeriod);
         DebugLog.Statistic.println("Server cell disk operations load:" + this.loadCellFromDisk + " save:" + this.saveCellToDisk);
         DebugLog.Statistic
            .println("Memory (bytes):" + (Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory()) + " of " + Runtime.getRuntime().totalMemory());
         DebugLog.Statistic.println("== Connections:" + GameServer.udpEngine.connections.size() + " ==");

         for (int var1 = 0; var1 < GameServer.udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)GameServer.udpEngine.connections.get(var1);
            DebugLog.Statistic.println("Connection " + var1 + " " + var2.ip + " " + var2.username + " " + var2.accessLevel);

            for (int var3 = 0; var3 < var2.players.length; var3++) {
               if (var2.players[var3] != nullptr) {
                  DebugLog.Statistic
                     .println(
                        "  User " + var2.players[var3].username + " (" + var2.players[var3].x + ", " + var2.players[var3].y + ", " + var2.players[var3].z + ")"
                     );
               }
            }

            DebugLog.Statistic.println("  Ping:" + var2.statistic.diff / 2 + " AVG:" + var2.statistic.pingAVG);
            DebugLog.Statistic
               .println(
                  "  Players count:"
                     + var2.statistic.remotePlayersCount
                     + " desyncAVG:"
                     + var2.statistic.remotePlayersDesyncAVG
                     + " desyncMAX:"
                     + var2.statistic.remotePlayersDesyncMax
                     + " teleports:"
                     + var2.statistic.remotePlayersTeleports
               );
            DebugLog.Statistic
               .println(
                  "  Zombies count:"
                     + var2.statistic.zombiesCount
                     + " LocalOwnership:"
                     + var2.statistic.zombiesLocalOwnership
                     + " desyncAVG:"
                     + var2.statistic.zombiesDesyncAVG
                     + " desyncMAX:"
                     + var2.statistic.zombiesDesyncMax
                     + " teleports:"
                     + var2.statistic.zombiesTeleports
               );
            DebugLog.Statistic
               .println("  FPS:" + var2.statistic.FPS + " Min:" + var2.statistic.FPSMin + " Avg:" + var2.statistic.FPSAvg + " Max:" + var2.statistic.FPSMax);
         }

         DebugLog.Statistic.println("== Income Packets ==");
         DebugLog.Statistic.println("length of packet queue:" + this.packetLength);
         DebugLog.Statistic.println("count packets:" + this.countIncomePackets);
         DebugLog.Statistic.println("count bytes:" + this.countIncomeBytes);
         DebugLog.Statistic.println("max bps:" + this.maxIncomeBytesPerSecond);

         for (PacketType var6 : PacketTypes.packetTypes.values()) {
            if (var6.incomePackets > 0) {
               DebugLog.Statistic.println(var6.name() + "(" + var6.getId() + ") count:" + var6.incomePackets + " bytes:" + var6.incomeBytes);
            }
         }

         DebugLog.Statistic.println("== Outcome Packets ==");
         DebugLog.Statistic.println("count packets:" + this.countOutcomePackets);
         DebugLog.Statistic.println("count bytes:" + this.countOutcomeBytes);
         DebugLog.Statistic.println("max bps:" + this.maxOutcomeBytesPerSecond);

         for (PacketType var7 : PacketTypes.packetTypes.values()) {
            if (var7.outcomePackets > 0) {
               DebugLog.Statistic.println(var7.name() + "(" + var7.getId() + ") count:" + var7.outcomePackets + " bytes:" + var7.outcomeBytes);
            }
         }

         DebugLog.Statistic.println("=== END STATISTICS ===");
      }
   }

    static std::string getStatisticDir() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDirSub("Statistic");
      ZomboidFileSystem.ensureFolderExists(var0);
    File var1 = std::make_shared<File>(var0);
      return var1.getAbsolutePath();
   }

    void removeCSVStatistics() {
    std::string var1 = getStatisticDir();

      try {
    File var2 = std::make_shared<File>(var1 + File.separator + "Statistic.csv");
         var2.delete();
      } catch (Exception var8) {
         DebugLog.Statistic.printException(var8, "Delete file failed: Statistic.csv", LogSeverity.Error);
      }

      try {
    File var9 = std::make_shared<File>(var1 + File.separator + "Connections.csv");
         var9.delete();
      } catch (Exception var7) {
         DebugLog.Statistic.printException(var7, "Delete file failed: Connections.csv", LogSeverity.Error);
      }

      try {
    File var10 = std::make_shared<File>(var1 + File.separator + "IncomePackets.csv");
         var10.delete();
      } catch (Exception var6) {
         DebugLog.Statistic.printException(var6, "Delete file failed: IncomePackets.csv", LogSeverity.Error);
      }

      try {
    File var11 = std::make_shared<File>(var1 + File.separator + "IncomeBytes.csv");
         var11.delete();
      } catch (Exception var5) {
         DebugLog.Statistic.printException(var5, "Delete file failed: IncomeBytes.csv", LogSeverity.Error);
      }

      try {
    File var12 = std::make_shared<File>(var1 + File.separator + "OutcomePackets.csv");
         var12.delete();
      } catch (Exception var4) {
         DebugLog.Statistic.printException(var4, "Delete file failed: OutcomePackets.csv", LogSeverity.Error);
      }

      try {
    File var13 = std::make_shared<File>(var1 + File.separator + "OutcomeBytes.csv");
         var13.delete();
      } catch (Exception var3) {
         DebugLog.Statistic.printException(var3, "Delete file failed: OutcomeBytes.csv", LogSeverity.Error);
      }
   }

    void closeCSVStatistics() {
      if (this.csvStatisticFile != nullptr) {
         this.csvStatisticFile.close();
      }

      this.csvStatisticFile = nullptr;
      if (this.csvConnectionsFile != nullptr) {
         this.csvConnectionsFile.close();
      }

      this.csvConnectionsFile = nullptr;
      if (this.csvIncomePacketsFile != nullptr) {
         this.csvIncomePacketsFile.close();
      }

      this.csvIncomePacketsFile = nullptr;
      if (this.csvIncomeBytesFile != nullptr) {
         this.csvIncomeBytesFile.close();
      }

      this.csvIncomeBytesFile = nullptr;
      if (this.csvOutcomePacketsFile != nullptr) {
         this.csvOutcomePacketsFile.close();
      }

      this.csvOutcomePacketsFile = nullptr;
      if (this.csvOutcomeBytesFile != nullptr) {
         this.csvOutcomeBytesFile.close();
      }

      this.csvOutcomeBytesFile = nullptr;
   }

    void openCSVStatistic() {
      if (doCSVStatistic) {
    std::string var1 = getStatisticDir();

         try {
    File var2 = std::make_shared<File>(var1 + File.separator + "Statistic.csv");
            if (var2.exists()) {
               this.csvStatisticFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var2, true));
            } else {
               this.csvStatisticFile = std::make_shared<PrintStream>(var2);
               this.csvStatisticFile
                  .println(
                     "lastReport; minUpdatePeriod; maxUpdatePeriod; avgUpdatePeriod; loadCellFromDisk; saveCellToDisk; countLoaderThreadTasksAdded; countLoaderThreadTasksProcessed; countRecalcThreadTasksAdded; countRecalcThreadTasksProcessed; countSaveUnloadedTasksAdded; countSaveLoadedTasksAdded; countSaveGameTimeTasksAdded; countQuitThreadTasksAdded; countSaveThreadTasksProcessed; countServerMapToLoadAdded; countServerMapToLoadCanceled; countServerMapLoadedCellsAdded; countServerMapLoadedCellsCanceled; countServerMapLoaded2Added; countServerMapLoaded2Canceled; countServerChunkThreadSaveNow; "
                        + this.Main.PrintTitle("MainThread")
                        + this.ServerLOS.PrintTitle("ServerLOS")
                        + this.LoaderThread.PrintTitle("LoaderThread")
                        + this.RecalcAllThread.PrintTitle("RecalcAllThread")
                        + this.SaveThread.PrintTitle("SaveThread")
                        + this.PolyPathThread.PrintTitle("PolyPathThread")
                        + this.WorldReuser.PrintTitle("WorldReuser")
                        + this.PlayerDownloadServer.PrintTitle("WorldReuser")
                        + this.MapCollisionThread.PrintTitle("MapCollisionThread")
                        + this.ChunkChecksum.PrintTitle("ChunkChecksum")
                        + this.Bullet.PrintTitle("Bullet")
                        + this.AnimationPlayerUpdate.PrintTitle("AnimationPlayerUpdate")
                        + this.ServerMapPreupdate.PrintTitle("ServerMapPreupdate")
                        + this.ServerMapPostupdate.PrintTitle("ServerMapPostupdate")
                        + this.IngameStateUpdate.PrintTitle("IngameStateUpdate")
                        + "totalMemory; freeMemory; countConnections; packetLength; countIncomePackets; countIncomeBytes; maxIncomeBytesPerSecound; countOutcomePackets; countOutcomeBytes; maxOutcomeBytesPerSecound"
                  );
            }
         } catch (FileNotFoundException var10) {
            DebugLog.Statistic.printException(var10, "Open file failed: Statistic.csv", LogSeverity.Error);
            if (this.csvStatisticFile != nullptr) {
               this.csvStatisticFile.close();
            }

            this.csvStatisticFile = nullptr;
         }

         try {
    File var11 = std::make_shared<File>(var1 + File.separator + "Connections.csv");
            if (var11.exists()) {
               this.csvConnectionsFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var11, true));
            } else {
               this.csvConnectionsFile = std::make_shared<PrintStream>(var11);
               this.csvConnectionsFile.print("ip; ");
               this.csvConnectionsFile.print("username; ");
               this.csvConnectionsFile.print("accessLevel; ");
               this.csvConnectionsFile.print("players.length; ");
               this.csvConnectionsFile.print("ping; ");
               this.csvConnectionsFile.print("pingAVG; ");
               this.csvConnectionsFile.print("remotePlayersCount; ");
               this.csvConnectionsFile.print("remotePlayersDesyncAVG; ");
               this.csvConnectionsFile.print("remotePlayersDesyncMax; ");
               this.csvConnectionsFile.print("remotePlayersTeleports; ");
               this.csvConnectionsFile.print("zombiesCount; ");
               this.csvConnectionsFile.print("zombiesLocalOwnership; ");
               this.csvConnectionsFile.print("zombiesDesyncAVG; ");
               this.csvConnectionsFile.print("zombiesDesyncMax; ");
               this.csvConnectionsFile.print("zombiesTeleports; ");
               this.csvConnectionsFile.print("FPS; ");
               this.csvConnectionsFile.print("FPSMin; ");
               this.csvConnectionsFile.print("FPSAvg; ");
               this.csvConnectionsFile.print("FPSMax; ");

               for (int var3 = 0; var3 < 32; var3++) {
                  this.csvConnectionsFile.print("FPSHistogramm[" + var3 + "]; ");
               }

               this.csvConnectionsFile.println();
            }
         } catch (FileNotFoundException var9) {
            DebugLog.Statistic.printException(var9, "Open file failed: Connections.csv", LogSeverity.Error);
            if (this.csvConnectionsFile != nullptr) {
               this.csvConnectionsFile.close();
            }

            this.csvConnectionsFile = nullptr;
         }

         try {
    File var12 = std::make_shared<File>(var1 + File.separator + "IncomePackets.csv");
            if (var12.exists()) {
               this.csvIncomePacketsFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var12, true));
            } else {
               this.csvIncomePacketsFile = std::make_shared<PrintStream>(var12);

               for (PacketType var4 : PacketTypes.packetTypes.values()) {
                  this.csvIncomePacketsFile.print(var4.name() + "(" + var4.getId() + "); ");
               }

               this.csvIncomePacketsFile.println();
            }
         } catch (FileNotFoundException var8) {
            DebugLog.Statistic.printException(var8, "Open file failed: IncomePackets.csv", LogSeverity.Error);
            if (this.csvIncomePacketsFile != nullptr) {
               this.csvIncomePacketsFile.close();
            }

            this.csvIncomePacketsFile = nullptr;
         }

         try {
    File var13 = std::make_shared<File>(var1 + File.separator + "IncomeBytes.csv");
            if (var13.exists()) {
               this.csvIncomeBytesFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var13, true));
            } else {
               this.csvIncomeBytesFile = std::make_shared<PrintStream>(var13);

               for (PacketType var20 : PacketTypes.packetTypes.values()) {
                  this.csvIncomeBytesFile.print(var20.name() + "(" + var20.getId() + "); ");
               }

               this.csvIncomeBytesFile.println();
            }
         } catch (FileNotFoundException var7) {
            DebugLog.Statistic.printException(var7, "Open file failed: IncomeBytes.csv", LogSeverity.Error);
            if (this.csvIncomeBytesFile != nullptr) {
               this.csvIncomeBytesFile.close();
            }

            this.csvIncomeBytesFile = nullptr;
         }

         try {
    File var14 = std::make_shared<File>(var1 + File.separator + "OutcomePackets.csv");
            if (var14.exists()) {
               this.csvOutcomePacketsFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var14, true));
            } else {
               this.csvOutcomePacketsFile = std::make_shared<PrintStream>(var14);

               for (PacketType var21 : PacketTypes.packetTypes.values()) {
                  this.csvOutcomePacketsFile.print(var21.name() + "(" + var21.getId() + "); ");
               }

               this.csvOutcomePacketsFile.println();
            }
         } catch (FileNotFoundException var6) {
            DebugLog.Statistic.printException(var6, "Open file failed: OutcomePackets.csv", LogSeverity.Error);
            if (this.csvOutcomePacketsFile != nullptr) {
               this.csvOutcomePacketsFile.close();
            }

            this.csvOutcomePacketsFile = nullptr;
         }

         try {
    File var15 = std::make_shared<File>(var1 + File.separator + "OutcomeBytes.csv");
            if (var15.exists()) {
               this.csvOutcomeBytesFile = std::make_shared<PrintStream>(std::make_shared<FileOutputStream>(var15, true));
            } else {
               this.csvOutcomeBytesFile = std::make_shared<PrintStream>(var15);

               for (PacketType var22 : PacketTypes.packetTypes.values()) {
                  this.csvOutcomeBytesFile.print(var22.name() + "(" + var22.getId() + "); ");
               }

               this.csvOutcomeBytesFile.println();
            }
         } catch (FileNotFoundException var5) {
            DebugLog.Statistic.printException(var5, "Open file failed: OutcomeBytes.csv", LogSeverity.Error);
            if (this.csvOutcomeBytesFile != nullptr) {
               this.csvOutcomeBytesFile.close();
            }

            this.csvOutcomeBytesFile = nullptr;
         }
      }
   }

    void printCSVStatistic() {
      if (doCSVStatistic) {
         try {
            try {
               this.openCSVStatistic();
               if (this.csvStatisticFile != nullptr) {
                  this.csvStatisticFile.print(System.currentTimeMillis() + ";");
                  this.csvStatisticFile.print(this.minUpdatePeriod + ";");
                  this.csvStatisticFile.print(this.maxUpdatePeriod + ";");
                  this.csvStatisticFile.print(this.avgUpdatePeriod + ";");
                  this.csvStatisticFile.print(this.loadCellFromDisk + ";");
                  this.csvStatisticFile.print(this.saveCellToDisk + ";");
                  this.csvStatisticFile.print(this.LoaderThreadTasks.Print());
                  this.csvStatisticFile.print(this.RecalcThreadTasks.Print());
                  this.csvStatisticFile.print(this.SaveTasks.Print());
                  this.csvStatisticFile.print(this.ServerMapToLoad.Print());
                  this.csvStatisticFile.print(this.ServerMapLoadedCells.Print());
                  this.csvStatisticFile.print(this.ServerMapLoaded2.Print());
                  this.csvStatisticFile.print(this.countServerChunkThreadSaveNow + ";");
                  this.csvStatisticFile.print(this.Main.Print());
                  this.csvStatisticFile.print(this.ServerLOS.Print());
                  this.csvStatisticFile.print(this.LoaderThread.Print());
                  this.csvStatisticFile.print(this.RecalcAllThread.Print());
                  this.csvStatisticFile.print(this.SaveThread.Print());
                  this.csvStatisticFile.print(this.PolyPathThread.Print());
                  this.csvStatisticFile.print(this.WorldReuser.Print());
                  this.csvStatisticFile.print(this.PlayerDownloadServer.Print());
                  this.csvStatisticFile.print(this.MapCollisionThread.Print());
                  this.csvStatisticFile.print(this.ChunkChecksum.Print());
                  this.csvStatisticFile.print(this.Bullet.Print());
                  this.csvStatisticFile.print(this.AnimationPlayerUpdate.Print());
                  this.csvStatisticFile.print(this.ServerMapPreupdate.Print());
                  this.csvStatisticFile.print(this.ServerMapPostupdate.Print());
                  this.csvStatisticFile.print(this.IngameStateUpdate.Print());
                  this.csvStatisticFile.print(Runtime.getRuntime().totalMemory() + ";");
                  this.csvStatisticFile.print(Runtime.getRuntime().freeMemory() + ";");
                  this.csvStatisticFile.print(GameServer.udpEngine.connections.size() + ";");
                  this.csvStatisticFile.print(this.packetLength + ";");
                  this.csvStatisticFile.print(this.countIncomePackets + ";");
                  this.csvStatisticFile.print(this.countIncomeBytes + ";");
                  this.csvStatisticFile.print(this.maxIncomeBytesPerSecond + ";");
                  this.csvStatisticFile.print(this.countOutcomePackets + ";");
                  this.csvStatisticFile.print(this.countOutcomeBytes + ";");
                  this.csvStatisticFile.println(this.maxOutcomeBytesPerSecond + ";");
                  this.csvStatisticFile.flush();
               }

               if (this.csvConnectionsFile != nullptr) {
                  for (int var1 = 0; var1 < GameServer.udpEngine.connections.size(); var1++) {
    UdpConnection var2 = (UdpConnection)GameServer.udpEngine.connections.get(var1);

                     try {
                        if (var2 != nullptr && var2.username != nullptr && !this.csvConnections.contains(var2.username.hashCode())) {
                           this.csvConnections.push_back(var2.username.hashCode());
                        }
                     } catch (NullPointerException var9) {
                        var9.printStackTrace();
                        return;
                     }
                  }

                  for (int var12 = 0; var12 < this.csvConnections.size(); var12++) {
    UdpConnection var14 = nullptr;

                     for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
                        if (var4 != nullptr && var4.username != nullptr && var4.username.hashCode() == this.csvConnections.get(var12)) {
                           var14 = var4;
                        }
                     }

                     if (var14 == nullptr) {
                        for (int var17 = 0; var17 < 51; var17++) {
                           this.csvConnectionsFile.print("; ");
                        }
                     } else {
                        this.csvConnectionsFile.print(var14.ip + "; ");
                        this.csvConnectionsFile.print(var14.username + "; ");
                        this.csvConnectionsFile.print(var14.accessLevel + "; ");
                        this.csvConnectionsFile.print(var14.players.length + "; ");
                        this.csvConnectionsFile.print(var14.statistic.diff / 2 + "; ");
                        this.csvConnectionsFile.print(var14.statistic.pingAVG + "; ");
                        this.csvConnectionsFile.print(var14.statistic.remotePlayersCount + "; ");
                        this.csvConnectionsFile.print(var14.statistic.remotePlayersDesyncAVG + "; ");
                        this.csvConnectionsFile.print(var14.statistic.remotePlayersDesyncMax + "; ");
                        this.csvConnectionsFile.print(var14.statistic.remotePlayersTeleports + "; ");
                        this.csvConnectionsFile.print(var14.statistic.zombiesCount + "; ");
                        this.csvConnectionsFile.print(var14.statistic.zombiesLocalOwnership + "; ");
                        this.csvConnectionsFile.print(var14.statistic.zombiesDesyncAVG + "; ");
                        this.csvConnectionsFile.print(var14.statistic.zombiesDesyncMax + "; ");
                        this.csvConnectionsFile.print(var14.statistic.zombiesTeleports + "; ");
                        this.csvConnectionsFile.print(var14.statistic.FPS + "; ");
                        this.csvConnectionsFile.print(var14.statistic.FPSMin + "; ");
                        this.csvConnectionsFile.print(var14.statistic.FPSAvg + "; ");
                        this.csvConnectionsFile.print(var14.statistic.FPSMax + "; ");

                        for (int var16 = 0; var16 < 32; var16++) {
                           this.csvConnectionsFile.print(var14.statistic.FPSHistogramm[var16] + "; ");
                        }
                     }

                     this.csvConnectionsFile.println();
                  }

                  this.csvConnectionsFile.flush();
               }

               if (this.csvIncomePacketsFile != nullptr
                  && this.csvOutcomePacketsFile != nullptr
                  && this.csvIncomeBytesFile != nullptr
                  && this.csvOutcomeBytesFile != nullptr) {
                  for (PacketType var15 : PacketTypes.packetTypes.values()) {
                     this.csvIncomePacketsFile.print(var15.incomePackets + ";");
                     this.csvIncomeBytesFile.print(var15.incomeBytes + ";");
                     this.csvOutcomePacketsFile.print(var15.outcomePackets + ";");
                     this.csvOutcomeBytesFile.print(var15.outcomeBytes + ";");
                  }

                  this.csvIncomePacketsFile.println();
                  this.csvIncomeBytesFile.println();
                  this.csvOutcomePacketsFile.println();
                  this.csvOutcomeBytesFile.println();
                  this.csvIncomePacketsFile.flush();
                  this.csvIncomeBytesFile.flush();
                  this.csvOutcomePacketsFile.flush();
                  this.csvOutcomeBytesFile.flush();
                  return;
               }
            } catch (NullPointerException var10) {
               var10.printStackTrace();
            }
         } finally {
            this.closeCSVStatistics();
         }
      }
   }

    void getStatisticTable(ByteBuffer var1) {
      if (this.table != nullptr) {
         this.table.save(var1);
      }
   }

    void setStatisticTable(ByteBuffer var1) {
      if (var1.remaining() != 0) {
         this.table = LuaManager.platform.newTable();

         try {
            this.table.load(var1, 195);
            this.table.rawset("lastReportTime", (double)System.currentTimeMillis());
         } catch (Exception var3) {
            this.table = nullptr;
            ExceptionLogger.logException(var3);
         }
      }
   }

    KahluaTable getStatisticTableForLua() {
      return this.table;
   }

    void printEnabled(bool var1) {
      doPrintStatistic = var1;
   }

    void writeEnabled(bool var1) {
      doCSVStatistic = var1;
      if (var1) {
         this.removeCSVStatistics();
      }
   }

    void setPeriod(int var1) {
      Period = Math.max(var1, 0);
      if (this.table != nullptr) {
         this.table.rawset("period", (double)Period);
      }
   }
}
} // namespace network
} // namespace zombie
