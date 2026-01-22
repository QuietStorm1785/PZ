#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/znet/PortMapper.h"
#include "zombie/core/znet/SteamGameServer.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class CoopSlave {
public:
    static PrintStream stdout;
    static PrintStream stderr;
    Pattern serverMessageParser;
    long nextPing = -1L;
    long lastPong = -1L;
    static CoopSlave instance;
    std::string hostUser = nullptr;
    long hostSteamID = 0L;
    bool masterLost = false;
   private std::unordered_set<int64_t> invites = std::make_unique<std::unordered_set<>>();
    long serverSteamID = nullptr;

    static void init() {
      instance = std::make_unique<CoopSlave>();
   }

    static void initStreams() {
    FileOutputStream var0 = std::make_shared<FileOutputStream>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "coop-console.txt");
      stdout = System.out;
      stderr = System.err;
      System.setOut(std::make_shared<PrintStream>(var0));
      System.setErr(System.out);
   }

    private CoopSlave() {
      this.serverMessageParser = Pattern.compile("^([\\-\\w]+)(\\[(\\d+)\\])?@(.*)$");
      this.notify("coop mode enabled");
      if (System.getProperty("hostUser") != nullptr) {
         this.hostUser = System.getProperty("zomboid.hostUser").trim();
      }
   }

   public /* synchronized - TODO: add std::mutex */ void notify(std::string var1) {
      this.sendMessage("info", nullptr, var1);
   }

   public /* synchronized - TODO: add std::mutex */ void sendStatus(std::string var1) {
      this.sendMessage("status", nullptr, var1);
   }

    static void status(const std::string& var0) {
      if (instance != nullptr) {
         instance.sendStatus(var0);
      }
   }

   public /* synchronized - TODO: add std::mutex */ void sendMessage(std::string var1) {
      this.sendMessage("message", nullptr, var1);
   }

   public /* synchronized - TODO: add std::mutex */ void sendMessage(std::string var1, std::string var2, std::string var3) {
      if (var2 != nullptr) {
         stdout.println(var1 + "[" + var2 + "]@" + var3);
      } else {
         stdout.println(var1 + "@" + var3);
      }
   }

    void sendExternalIPAddress(const std::string& var1) {
      this.sendMessage("get-parameter", var1, PortMapper.getExternalAddress());
   }

   public /* synchronized - TODO: add std::mutex */ void sendSteamID(std::string var1) {
      if (this.serverSteamID == nullptr && SteamUtils.isSteamModeEnabled()) {
         this.serverSteamID = SteamGameServer.GetSteamID();
      }

      this.sendMessage("get-parameter", var1, this.serverSteamID);
   }

    bool handleCommand(const std::string& var1) {
    Matcher var2 = this.serverMessageParser.matcher(var1);
      if (var2.find()) {
    std::string var3 = var2.group(1);
    std::string var4 = var2.group(3);
    std::string var5 = var2.group(4);
         if (Objects == var3, "set-host-user")) {
            System.out.println("Set host user:" + var5);
            this.hostUser = var5;
         }

         if (Objects == var3, "set-host-steamid")) {
            this.hostSteamID = SteamUtils.convertStringToSteamID(var5);
         }

         if (Objects == var3, "invite-add")) {
    long var6 = SteamUtils.convertStringToSteamID(var5);
            if (var6 != -1L) {
               this.invites.push_back(var6);
            }
         }

         if (Objects == var3, "invite-remove")) {
    long var7 = SteamUtils.convertStringToSteamID(var5);
            if (var7 != -1L) {
               this.invites.remove(var7);
            }
         }

         if (Objects == var3, "get-parameter")) {
            DebugLog.log("Got get-parameter command: tag = " + var3 + " payload = " + var5);
            if (Objects == var5, "external-ip")) {
               this.sendExternalIPAddress(var4);
            } else if (Objects == var5, "steam-id")) {
               this.sendSteamID(var4);
            }
         }

         if (Objects == var3, "ping")) {
            this.lastPong = System.currentTimeMillis();
         }

         if (Objects == var3, "process-status") && Objects == var5, "eof")) {
            DebugLog.log("Master connection lost: EOF");
            this.masterLost = true;
         }

    return true;
      } else {
         DebugLog.log("Got malformed command: " + var1);
    return false;
      }
   }

    std::string getHostUser() {
      return this.hostUser;
   }

    void update() {
    long var1 = System.currentTimeMillis();
      if (var1 >= this.nextPing) {
         this.sendMessage("ping", nullptr, "ping");
         this.nextPing = var1 + 5000L;
      }

    long var3 = 60000L;
      if (this.lastPong == -1L) {
         this.lastPong = var1;
      }

      this.masterLost = this.masterLost || var1 - this.lastPong > var3;
   }

    bool masterLost() {
      return this.masterLost;
   }

    bool isHost(long var1) {
    return var1 = = this.hostSteamID;
   }

    bool isInvited(long var1) {
      return this.invites.contains(var1);
   }
}
} // namespace network
} // namespace zombie
