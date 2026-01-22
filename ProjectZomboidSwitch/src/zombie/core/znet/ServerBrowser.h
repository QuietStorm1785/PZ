#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/network/Server.h"

namespace zombie {
namespace core {
namespace znet {


class ServerBrowser {
public:
    static IServerBrowserCallback m_callbackInterface = nullptr;

    static bool init() {
    bool var0 = false;
      if (SteamUtils.isSteamModeEnabled()) {
         var0 = n_Init();
      }

    return var0;
   }

    static void shutdown() {
      if (SteamUtils.isSteamModeEnabled()) {
         n_Shutdown();
      }
   }

    static void RefreshInternetServers() {
      if (SteamUtils.isSteamModeEnabled()) {
         n_RefreshInternetServers();
      }
   }

    static int GetServerCount() {
    int var0 = 0;
      if (SteamUtils.isSteamModeEnabled()) {
         var0 = n_GetServerCount();
      }

    return var0;
   }

    static GameServerDetails GetServerDetails(int var0) {
    GameServerDetails var1 = nullptr;
      if (SteamUtils.isSteamModeEnabled()) {
         var1 = n_GetServerDetails(var0);
      }

    return var1;
   }

    static void Release() {
      if (SteamUtils.isSteamModeEnabled()) {
         n_Release();
      }
   }

    static bool IsRefreshing() {
    bool var0 = false;
      if (SteamUtils.isSteamModeEnabled()) {
         var0 = n_IsRefreshing();
      }

    return var0;
   }

    static bool QueryServer(const std::string& var0, int var1) {
    bool var2 = false;
      if (SteamUtils.isSteamModeEnabled()) {
         var2 = n_QueryServer(var0, var1);
      }

    return var2;
   }

    static GameServerDetails GetServerDetails(const std::string& var0, int var1) {
    GameServerDetails var2 = nullptr;
      if (SteamUtils.isSteamModeEnabled()) {
         var2 = n_GetServerDetails(var0, var1);
      }

    return var2;
   }

    static void ReleaseServerQuery(const std::string& var0, int var1) {
      if (SteamUtils.isSteamModeEnabled()) {
         n_ReleaseServerQuery(var0, var1);
      }
   }

   public static List<GameServerDetails> GetServerList() {
    std::vector var0 = new std::vector();
      if (SteamUtils.isSteamModeEnabled()) {
         try {
            while (IsRefreshing()) {
               Thread.sleep(100L);
               SteamUtils.runLoop();
            }
         } catch (InterruptedException var3) {
            var3.printStackTrace();
         }

         for (int var1 = 0; var1 < GetServerCount(); var1++) {
    GameServerDetails var2 = GetServerDetails(var1);
            if (var2.steamId != 0L) {
               var0.push_back(var2);
            }
         }
      }

    return var0;
   }

    static GameServerDetails GetServerDetailsSync(const std::string& var0, int var1) {
    GameServerDetails var2 = nullptr;
      if (SteamUtils.isSteamModeEnabled()) {
         var2 = GetServerDetails(var0, var1);
         if (var2 == nullptr) {
            QueryServer(var0, var1);

            try {
               while (var2 == nullptr) {
                  Thread.sleep(100L);
                  SteamUtils.runLoop();
                  var2 = GetServerDetails(var0, var1);
               }
            } catch (InterruptedException var4) {
               var4.printStackTrace();
            }
         }
      }

    return var2;
   }

    static bool RequestServerRules(const std::string& var0, int var1) {
    return n_RequestServerRules();
   }

    static void setCallbackInterface(IServerBrowserCallback var0) {
      m_callbackInterface = var0;
   }

   private static native boolean n_Init();

   private static native void n_Shutdown();

   private static native void n_RefreshInternetServers();

   private static native int n_GetServerCount();

   private static native GameServerDetails n_GetServerDetails(int var0);

   private static native void n_Release();

   private static native boolean n_IsRefreshing();

   private static native boolean n_QueryServer(std::string var0, int var1);

   private static native GameServerDetails n_GetServerDetails(std::string var0, int var1);

   private static native void n_ReleaseServerQuery(std::string var0, int var1);

   private static native boolean n_RequestServerRules(std::string var0, int var1);

    static void onServerRespondedCallback(int var0) {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnServerResponded(var0);
      }

      LuaEventManager.triggerEvent("OnSteamServerResponded", var0);
   }

    static void onServerFailedToRespondCallback(int var0) {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnServerFailedToRespond(var0);
      }
   }

    static void onRefreshCompleteCallback() {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnRefreshComplete();
      }

      LuaEventManager.triggerEvent("OnSteamRefreshInternetServers");
   }

    static void onServerRespondedCallback(const std::string& var0, int var1) {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnServerResponded(var0, var1);
      }

    GameServerDetails var2 = GetServerDetails(var0, var1);
      if (var2 != nullptr) {
    Server var3 = std::make_shared<Server>();
         var3.setName(var2.name);
         var3.setDescription("");
         var3.setSteamId(int64_t.toString(var2.steamId));
         var3.setPing(int.toString(var2.ping));
         var3.setPlayers(int.toString(var2.numPlayers));
         var3.setMaxPlayers(int.toString(var2.maxPlayers));
         var3.setOpen(true);
         if (var2.tags.contains("hidden")) {
            var3.setOpen(false);
         }

         var3.setIp(var2.address);
         var3.setPort(int.toString(var2.port));
         var3.setMods("");
         if (!var2.tags.replace("hidden", "").replace("hosted", "").replace(";", "").empty()) {
            var3.setMods(var2.tags.replace(";hosted", "").replace("hidden", ""));
         }

         var3.setHosted(var2.tags.endsWith(";hosted"));
         var3.setVersion("");
         var3.setLastUpdate(1);
         var3.setPasswordProtected(var2.passwordProtected);
         ReleaseServerQuery(var0, var1);
         LuaEventManager.triggerEvent("OnSteamServerResponded2", var0, (double)var1, var3);
      }
   }

    static void onServerFailedToRespondCallback(const std::string& var0, int var1) {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnServerFailedToRespond(var0, var1);
      }

      LuaEventManager.triggerEvent("OnSteamServerFailedToRespond2", var0, (double)var1);
   }

    static void onRulesRefreshComplete(const std::string& var0, int var1, std::string[] var2) {
      if (m_callbackInterface != nullptr) {
         m_callbackInterface.OnSteamRulesRefreshComplete(var0, var1);
      }

    KahluaTable var3 = LuaManager.platform.newTable();

      for (byte var4 = 0; var4 < var2.length; var4 += 2) {
         var3.rawset(var2[var4], var2[var4 + 1]);
      }

      LuaEventManager.triggerEvent("OnSteamRulesRefreshComplete", var0, (double)var1, var3);
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
