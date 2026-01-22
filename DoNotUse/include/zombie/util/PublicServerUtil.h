#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/InetAddress.h"
#include "java/net/NetworkInterface.h"
#include "java/net/SocketTimeoutException.h"
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {


class PublicServerUtil {
public:
    static std::string webSite = "https://www.projectzomboid.com/server_browser/";
    static long timestampForUpdate = 0L;
    static long timestampForPlayerUpdate = 0L;
    static long updateTick = 600000L;
    static long updatePlayerTick = 300000L;
    static int sentPlayerCount = 0;
    static bool isEnabled = false;

    static void init() {
      isEnabled = false;
      if (DebugOptions.instance.Network.PublicServerUtil.Enabled.getValue()) {
         try {
            if (GameServer.bServer) {
               ServerOptions.instance.changeOption("PublicName", checkHacking(ServerOptions.instance.getOption("PublicName")));
               ServerOptions.instance.changeOption("PublicDescription", checkHacking(ServerOptions.instance.getOption("PublicDescription")));
            }

            if (GameServer.bServer && !isPublic()) {
               return;
            }

            DebugLog.log("connecting to public server list");
    URL var0 = std::make_shared<URL>(webSite + "serverVar.php");
    URLConnection var1 = var0.openConnection();
            var1.setConnectTimeout(3000);
            var1.connect();
    InputStreamReader var2 = std::make_shared<InputStreamReader>(var1.getInputStream());
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
    void* var4 = nullptr;
    std::stringstream var5 = new std::stringstream();

            while ((var4 = var3.readLine()) != nullptr) {
               var5.append((std::string)var4).append('\n');
            }

            var3.close();
            std::string[] var6 = var5.split("<br>");

    for (auto& var10 : var6)               if (var10.contains("allowed") && var10.contains("true")) {
                  isEnabled = true;
               }

               if (var10.contains("updateTick")) {
                  updateTick = int64_t.parseLong(var10.split("=")[1].trim());
               }

               if (var10.contains("updatePlayerTick")) {
                  updatePlayerTick = int64_t.parseLong(var10.split("=")[1].trim());
               }

               if (var10.contains("ip")) {
                  GameServer.ip = var10.split("=")[1].trim();
                  if (GameServer.ip.contains(":")) {
                     DebugLog.log(
                        "The IP address ("
                           + GameServer.ip
                           + ") looks like the IPv6 address. Please make sure IPv4 server address is set to the "
                           + ServerOptions.getInstance().server_browser_announced_ip.getName()
                           + " server option."
                     );
                  }
               }
            }
         } catch (SocketTimeoutException var11) {
            isEnabled = false;
            DebugLog.log("timeout trying to connect to public server list");
         } catch (Exception var12) {
            isEnabled = false;
            var12.printStackTrace();
         }
      }
   }

    static std::string checkHacking(const std::string& var0) {
      return var0 == nullptr
         ? ""
         : var0.replaceAll("--", "")
            .replaceAll("->", "")
            .replaceAll("(?i)select union", "")
            .replaceAll("(?i)select join", "")
            .replaceAll("1=1", "")
            .replaceAll("(?i)delete from", "");
   }

    static void insertOrUpdate() {
      if (isEnabled) {
         if (isPublic()) {
            try {
               insertDatas();
            } catch (Exception var1) {
               System.out.println("Can't reach PZ.com");
            }
         }
      }
   }

    static bool isPublic() {
    std::string var0 = checkHacking(ServerOptions.instance.PublicName.getValue());
      return ServerOptions.instance.Public.getValue() && !var0.empty();
   }

    static void update() {
      if (System.currentTimeMillis() - timestampForUpdate > updateTick) {
         timestampForUpdate = System.currentTimeMillis();
         init();
         if (!isEnabled) {
            return;
         }

         if (isPublic()) {
            try {
               insertDatas();
            } catch (Exception var1) {
               System.out.println("Can't reach PZ.com");
            }
         }
      }
   }

    static void insertDatas() {
      if (isEnabled) {
    std::string var0 = "";
         if (!ServerOptions.instance.PublicDescription.getValue().empty()) {
            var0 = "&desc=" + ServerOptions.instance.PublicDescription.getValue().replaceAll(" ", "%20");
         }

    std::string var1 = "";

         for (std::string var3 : GameServer.ServerMods) {
            var1 = var1 + var3 + ",";
         }

         if (!"" == var1)) {
            var1 = var1.substr(0, var1.length() - 1);
            var1 = "&mods=" + var1.replaceAll(" ", "%20");
         }

    std::string var5 = GameServer.ip;
         if (!ServerOptions.instance.server_browser_announced_ip.getValue().empty()) {
            var5 = ServerOptions.instance.server_browser_announced_ip.getValue();
         }

         timestampForUpdate = System.currentTimeMillis();
    int var6 = GameServer.getPlayerCount();
         callUrl(
            webSite
               + "write.php?name="
               + ServerOptions.instance.PublicName.getValue().replaceAll(" ", "%20")
               + var0
               + "&port="
               + ServerOptions.instance.DefaultPort.getValue()
               + "&UDPPort="
               + ServerOptions.instance.UDPPort.getValue()
               + "&players="
               + var6
               + "&ip="
               + var5
               + "&open="
               + (ServerOptions.instance.Open.getValue() ? "1" : "0")
               + "&password="
               + ("" == ServerOptions.instance.Password.getValue()) ? "0" : "1")
               + "&maxPlayers="
               + ServerOptions.getInstance().getMaxPlayers()
               + "&version="
               + Core.getInstance().getVersion().replaceAll(" ", "%20")
               + var1
               + "&mac="
               + getMacAddress()
         );
         sentPlayerCount = var6;
      }
   }

    static void updatePlayers() {
      if (System.currentTimeMillis() - timestampForPlayerUpdate > updatePlayerTick) {
         timestampForPlayerUpdate = System.currentTimeMillis();
         if (!isEnabled) {
            return;
         }

         try {
    std::string var0 = GameServer.ip;
            if (!ServerOptions.instance.server_browser_announced_ip.getValue().empty()) {
               var0 = ServerOptions.instance.server_browser_announced_ip.getValue();
            }

    int var1 = GameServer.getPlayerCount();
            callUrl(webSite + "updatePlayers.php?port=" + ServerOptions.instance.DefaultPort.getValue() + "&players=" + var1 + "&ip=" + var0);
            sentPlayerCount = GameServer.getPlayerCount();
         } catch (Exception var2) {
            System.out.println("Can't reach PZ.com");
         }
      }
   }

    static void updatePlayerCountIfChanged() {
      if (isEnabled && sentPlayerCount != GameServer.getPlayerCount()) {
         updatePlayers();
      }
   }

    static bool isEnabled() {
    return isEnabled;
   }

    static std::string getMacAddress() {
      try {
    InetAddress var0 = InetAddress.getLocalHost();
    NetworkInterface var1 = NetworkInterface.getByInetAddress(var0);
         if (var1 != nullptr) {
            byte[] var2 = var1.getHardwareAddress();
    std::stringstream var3 = new std::stringstream();

            for (int var4 = 0; var4 < var2.length; var4++) {
               var3.append(std::string.format("%02X%s", var2[var4], var4 < var2.length - 1 ? "-" : ""));
            }

            return var3;
         }
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      return "";
   }

    static void callUrl(const std::string& var0) {
      std::make_shared<Thread>(ThreadGroups.Workers, Lambda.invoker(var0, var0x -> {
         try {
    URL var1 = std::make_shared<URL>(var0x);
    URLConnection var2 = var1.openConnection();
            var2.getInputStream();
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }), "openUrl").start();
   }
}
} // namespace util
} // namespace zombie
