#pragma once
#include <list>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/logger/ZipLogs.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/CoopMaster/1.h"
#include "zombie/network/CoopMaster/10.h"
#include "zombie/network/CoopMaster/11.h"
#include "zombie/network/CoopMaster/12.h"
#include "zombie/network/CoopMaster/2.h"
#include "zombie/network/CoopMaster/3.h"
#include "zombie/network/CoopMaster/4.h"
#include "zombie/network/CoopMaster/5.h"
#include "zombie/network/CoopMaster/6.h"
#include "zombie/network/CoopMaster/7.h"
#include "zombie/network/CoopMaster/8.h"
#include "zombie/network/CoopMaster/9.h"
#include "zombie/network/CoopMaster/ListenerOptions.h"
#include "zombie/network/CoopMaster/Pair.h"
#include "zombie/network/CoopMaster/TerminationReason.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace network {


class CoopMaster {
public:
    Process serverProcess;
    Thread serverThread;
    PrintStream serverCommandStream;
   private const List<std::string> incomingMessages;
    Pattern serverMessageParser;
    TerminationReason serverTerminationReason;
    Thread timeoutWatchThread;
    bool serverResponded;
    static const CoopMaster instance = std::make_shared<CoopMaster>();
    std::string adminUsername = nullptr;
    std::string adminPassword = nullptr;
    std::string serverName = nullptr;
    long serverSteamID = nullptr;
    std::string serverIP = nullptr;
    int serverPort = nullptr;
    int autoCookie = 0;
    static const int autoCookieOffset = 1000000;
    static const int maxAutoCookie = 1000000;
   private const List<Pair<ICoopServerMessageListener, ListenerOptions>> listeners;

    private CoopMaster() {
      this.incomingMessages = std::make_unique<std::list<>>();
      this.listeners = std::make_unique<std::list<>>();
      this.serverMessageParser = Pattern.compile("^([\\-\\w]+)(\\[(\\d+)\\])?@(.*)$");
      this.adminPassword = UUID.randomUUID();
   }

    int getServerPort() {
      return this.serverPort;
   }

    void launchServer(const std::string& var1, const std::string& var2, int var3) {
      this.launchServer(var1, var2, var3, false);
   }

    void softreset(const std::string& var1, const std::string& var2, int var3) {
      this.launchServer(var1, var2, var3, true);
   }

    void launchServer(const std::string& var1, const std::string& var2, int var3, bool var4) {
    std::string var5 = Paths.get(System.getProperty("java.home"), "bin", "java").toAbsolutePath();
      if (SteamUtils.isSteamModeEnabled()) {
         var2 = "admin";
      }

    std::vector var6 = new std::vector();
      var6.push_back(var5);
      var6.push_back("-Xms" + var3 + "m");
      var6.push_back("-Xmx" + var3 + "m");
      var6.push_back("-Djava.library.path=" + System.getProperty("java.library.path"));
      var6.push_back("-Djava.class.path=" + System.getProperty("java.class.path"));
      var6.push_back("-Duser.dir=" + System.getProperty("user.dir"));
      var6.push_back("-Duser.home=" + System.getProperty("user.home"));
      var6.push_back("-Dzomboid.znetlog=2");
      var6.push_back("-Dzomboid.steam=" + (SteamUtils.isSteamModeEnabled() ? "1" : "0"));
      var6.push_back("-Djava.awt.headless=true");
      var6.push_back("-XX:-OmitStackTraceInFastThrow");
    std::string var7 = this.getGarbageCollector();
      if (var7 != nullptr) {
         var6.push_back(var7);
      }

      if (var4) {
         var6.push_back("-Dsoftreset");
      }

      if (Core.bDebug) {
         var6.push_back("-Ddebug");
      }

      var6.push_back("zombie.network.GameServer");
      var6.push_back("-coop");
      var6.push_back("-servername");
      var6.push_back(this.serverName = var1);
      var6.push_back("-adminusername");
      var6.push_back(this.adminUsername = var2);
      var6.push_back("-adminpassword");
      var6.push_back(this.adminPassword);
      var6.push_back("-cachedir=" + ZomboidFileSystem.instance.getCacheDir());
    ProcessBuilder var8 = std::make_shared<ProcessBuilder>(var6);
      ZipLogs.addZipFile(false);
      this.serverTerminationReason = TerminationReason.NormalTermination;
      this.serverResponded = false;
      this.serverProcess = var8.start();
      this.serverCommandStream = std::make_shared<PrintStream>(this.serverProcess.getOutputStream());
      this.serverThread = std::make_shared<Thread>(ThreadGroups.Workers, this::readServer);
      this.serverThread.setUncaughtExceptionHandler(GameWindow::uncaughtException);
      this.serverThread.start();
      this.timeoutWatchThread = std::make_shared<Thread>(ThreadGroups.Workers, this::watchServer);
      this.timeoutWatchThread.setUncaughtExceptionHandler(GameWindow::uncaughtException);
      this.timeoutWatchThread.start();
   }

    std::string getGarbageCollector() {
      try {
    RuntimeMXBean var1 = ManagementFactory.getRuntimeMXBean();
    std::vector var2 = var1.getInputArguments();
    bool var3 = false;
    bool var4 = false;

    for (auto& var6 : var2)            if ("-XX:+UseZGC" == var6)) {
               var3 = true;
            }

            if ("-XX:-UseZGC" == var6)) {
               var3 = false;
            }

            if ("-XX:+UseG1GC" == var6)) {
               var4 = true;
            }

            if ("-XX:-UseG1GC" == var6)) {
               var4 = false;
            }
         }

         if (var3) {
            return "-XX:+UseZGC";
         }

         if (var4) {
            return "-XX:+UseG1GC";
         }
      } catch (Throwable var7) {
      }

    return nullptr;
   }

    void readServer() {
    BufferedReader var1 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(this.serverProcess.getInputStream()));

      while (true) {
         try {
    int var6 = this.serverProcess.exitValue();
            break;
         } catch (IllegalThreadStateException var5) {
    std::string var2 = nullptr;

            try {
               var2 = var1.readLine();
            } catch (IOException var4) {
               var4.printStackTrace();
            }

            if (var2 != nullptr) {
               this.storeMessage(var2);
               this.serverResponded = true;
            }
         }
      }

      this.storeMessage("process-status@terminated");
      ZipLogs.addZipFile(true);
   }

    void abortServer() {
      this.serverProcess.destroy();
   }

    void watchServer() {
    uint8_t var1 = 20;

      try {
         Thread.sleep(1000 * var1);
         if (!this.serverResponded) {
            this.serverTerminationReason = TerminationReason.Timeout;
            this.abortServer();
         }
      } catch (InterruptedException var3) {
         var3.printStackTrace();
      }
   }

    bool isRunning() {
      return this.serverThread != nullptr && this.serverThread.isAlive();
   }

    TerminationReason terminationReason() {
      return this.serverTerminationReason;
   }

    void storeMessage(const std::string& var1) {
      /* synchronized - TODO: add std::mutex */ (this.incomingMessages) {
         this.incomingMessages.push_back(var1);
      }
   }

   public /* synchronized - TODO: add std::mutex */ void sendMessage(std::string var1, std::string var2, std::string var3) {
    std::stringstream var4 = new std::stringstream();
      var4.append(var1);
      if (var2 == nullptr) {
         var4.append("@");
      } else {
         var4.append("[");
         var4.append(var2);
         var4.append("]@");
      }

      var4.append(var3);
    std::string var5 = var4;
      if (this.serverCommandStream != nullptr) {
         this.serverCommandStream.println(var5);
         this.serverCommandStream.flush();
      }
   }

    void sendMessage(const std::string& var1, const std::string& var2) {
      this.sendMessage(var1, nullptr, var2);
   }

   public /* synchronized - TODO: add std::mutex */ void invokeServer(std::string var1, std::string var2, ICoopServerMessageListener var3) {
      this.autoCookie = (this.autoCookie + 1) % 1000000;
    std::string var4 = int.toString(1000000 + this.autoCookie);
      this.addListener(var3, std::make_shared<ListenerOptions>(this, var1, var4, true));
      this.sendMessage(var1, var4, var2);
   }

    std::string getMessage() {
    std::string var1 = nullptr;
      /* synchronized - TODO: add std::mutex */ (this.incomingMessages) {
         if (this.incomingMessages.size() != 0) {
            var1 = this.incomingMessages.get(0);
            this.incomingMessages.remove(0);
            if (!"ping@ping" == var1)) {
               System.out.println("SERVER: " + var1);
            }
         }

    return var1;
      }
   }

    void update() {
    std::string var1;
      while ((var1 = this.getMessage()) != nullptr) {
    Matcher var2 = this.serverMessageParser.matcher(var1);
         if (var2.find()) {
    std::string var3 = var2.group(1);
    std::string var4 = var2.group(3);
    std::string var5 = var2.group(4);
            LuaEventManager.triggerEvent("OnCoopServerMessage", var3, var4, var5);
            this.handleMessage(var3, var4, var5);
         } else {
            DebugLog.log(DebugType.Network, "[CoopMaster] Unknown message incoming from the slave server: " + var1);
         }
      }
   }

    void handleMessage(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (Objects == var1, "ping")) {
         this.sendMessage("ping", var2, "pong");
      } else if (Objects == var1, "steam-id")) {
         if (Objects == var3, "nullptr")) {
            this.serverSteamID = nullptr;
         } else {
            this.serverSteamID = SteamUtils.convertStringToSteamID(var3);
         }
      } else if (Objects == var1, "server-address")) {
         DebugLog.log("Got server-address: " + var3);
    std::string var4 = "^(\\d+\\.\\d+\\.\\d+\\.\\d+):(\\d+)$";
    Pattern var5 = Pattern.compile(var4);
    Matcher var6 = var5.matcher(var3);
         if (var6.find()) {
    std::string var7 = var6.group(1);
    std::string var8 = var6.group(2);
            this.serverIP = var7;
            this.serverPort = int.valueOf(var8);
            DebugLog.log("Successfully parsed: address = " + this.serverIP + ", port = " + this.serverPort);
         } else {
            DebugLog.log("Failed to parse server address");
         }
      }

      this.invokeListeners(var1, var2, var3);
   }

    void register(Platform var1, KahluaTable var2) {
    KahluaTable var3 = var1.newTable();
      var3.rawset("launch", std::make_shared<1>(this));
      var3.rawset("softreset", std::make_shared<2>(this));
      var3.rawset("isRunning", std::make_shared<3>(this));
      var3.rawset("sendMessage", std::make_shared<4>(this));
      var3.rawset("getAdminPassword", std::make_shared<5>(this));
      var3.rawset("getTerminationReason", std::make_shared<6>(this));
      var3.rawset("getSteamID", std::make_shared<7>(this));
      var3.rawset("getAddress", std::make_shared<8>(this));
      var3.rawset("getPort", std::make_shared<9>(this));
      var3.rawset("abort", std::make_shared<10>(this));
      var3.rawset("getServerSaveFolder", std::make_shared<11>(this));
      var3.rawset("getPlayerSaveFolder", std::make_shared<12>(this));
      var2.rawset("CoopServer", var3);
   }

    void addListener(ICoopServerMessageListener var1, ListenerOptions var2) {
      /* synchronized - TODO: add std::mutex */ (this.listeners) {
         this.listeners.push_back(std::make_shared<Pair>(this, var1, var2));
      }
   }

    void addListener(ICoopServerMessageListener var1) {
      this.addListener(var1, nullptr);
   }

    void removeListener(ICoopServerMessageListener var1) {
      /* synchronized - TODO: add std::mutex */ (this.listeners) {
    int var3 = 0;

         while (var3 < this.listeners.size() && this.listeners.get(var3).first != var1) {
            var3++;
         }

         if (var3 < this.listeners.size()) {
            this.listeners.remove(var3);
         }
      }
   }

    void invokeListeners(const std::string& var1, const std::string& var2, const std::string& var3) {
      /* synchronized - TODO: add std::mutex */ (this.listeners) {
    Iterator var5 = this.listeners.iterator();

         while (var5.hasNext()) {
    Pair var6 = (Pair)var5.next();
    ICoopServerMessageListener var7 = (ICoopServerMessageListener)var6.first;
    ListenerOptions var8 = (ListenerOptions)var6.second;
            if (var7 != nullptr) {
               if (var8 == nullptr) {
                  var7.OnCoopServerMessage(var1, var2, var3);
               } else if ((var8.tag == nullptr || var8.tag == var1)) && (var8.cookie == nullptr || var8.cookie == var2))) {
                  if (var8.autoRemove) {
                     var5.remove();
                  }

                  var7.OnCoopServerMessage(var1, var2, var3);
               }
            }
         }
      }
   }

    std::string getServerName() {
      return this.serverName;
   }

    std::string getServerSaveFolder(const std::string& var1) {
      return GlobalObject.sanitizeWorldName(var1);
   }

    std::string getPlayerSaveFolder(const std::string& var1) {
      return GlobalObject.sanitizeWorldName(var1 + "_player");
   }
}
} // namespace network
} // namespace zombie
