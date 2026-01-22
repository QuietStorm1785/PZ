#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigInteger.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/CoopSlave.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/ServerWorldDatabase/LogonResult.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace znet {


class SteamUtils {
public:
    static bool m_steamEnabled;
    static bool m_netEnabled;
    static bool m_floatingGamepadTextInputVisible = false;
    static const BigInteger TWO_64 = BigInteger.ONE.shiftLeft(64);
    static const BigInteger MAX_ULONG = std::make_shared<BigInteger>("FFFFFFFFFFFFFFFF", 16);
   private static List<IJoinRequestCallback> m_joinRequestCallbacks;
    static const int k_EGamepadTextInputModeNormal = 0;
    static const int k_EGamepadTextInputModePassword = 1;
    static const int k_EGamepadTextInputLineModeSingleLine = 0;
    static const int k_EGamepadTextInputLineModeMultipleLines = 1;
    static const int k_EFloatingGamepadTextInputModeSingleLine = 0;
    static const int k_EFloatingGamepadTextInputModeMultipleLines = 1;
    static const int k_EFloatingGamepadTextInputModeEmail = 2;
    static const int k_EFloatingGamepadTextInputModeNumeric = 3;

    static void loadLibrary(const std::string& var0) {
      DebugLog.log("Loading " + var0 + "...");
      System.loadLibrary(var0);
   }

    static void init() {
      m_steamEnabled = System.getProperty("zomboid.steam") != nullptr && System.getProperty("zomboid.steam") == "1");
      DebugLog.log("Loading networking libraries...");
    std::string var0 = "";
      if ("1" == System.getProperty("zomboid.debuglibs.znet"))) {
         DebugLog.log("***** Loading debug versions of libraries");
         var0 = "d";
      }

      try {
         if (System.getProperty("os.name").contains("OS X")) {
            if (m_steamEnabled) {
               loadLibrary("steam_api");
               loadLibrary("RakNet");
               loadLibrary("ZNetJNI");
            } else {
               loadLibrary("RakNet");
               loadLibrary("ZNetNoSteam");
            }
         } else if (System.getProperty("os.name").startsWith("Win")) {
            if (System.getProperty("sun.arch.data.model") == "64")) {
               if (m_steamEnabled) {
                  loadLibrary("steam_api64");
                  loadLibrary("RakNet64" + var0);
                  loadLibrary("ZNetJNI64" + var0);
               } else {
                  loadLibrary("RakNet64" + var0);
                  loadLibrary("ZNetNoSteam64" + var0);
               }
            } else if (m_steamEnabled) {
               loadLibrary("steam_api");
               loadLibrary("RakNet32" + var0);
               loadLibrary("ZNetJNI32" + var0);
            } else {
               loadLibrary("RakNet32" + var0);
               loadLibrary("ZNetNoSteam32" + var0);
            }
         } else if (System.getProperty("sun.arch.data.model") == "64")) {
            if (m_steamEnabled) {
               loadLibrary("steam_api");
               loadLibrary("RakNet64");
               loadLibrary("ZNetJNI64");
            } else {
               loadLibrary("RakNet64");
               loadLibrary("ZNetNoSteam64");
            }
         } else if (m_steamEnabled) {
            loadLibrary("steam_api");
            loadLibrary("RakNet32");
            loadLibrary("ZNetJNI32");
         } else {
            loadLibrary("RakNet32");
            loadLibrary("ZNetNoSteam32");
         }

         m_netEnabled = true;
      } catch (UnsatisfiedLinkError var6) {
         m_steamEnabled = false;
         m_netEnabled = false;
         ExceptionLogger.logException(var6);
         if (System.getProperty("os.name").startsWith("Win")) {
            DebugLog.log("One of the game's DLLs could not be loaded.");
            DebugLog.log("  Your system may be missing a DLL needed by the game's DLL.");
            DebugLog.log("  You may need to install the Microsoft Visual C++ Redistributable 2013.");
    File var2 = std::make_shared<File>("../_CommonRedist/vcredist/");
            if (var2.exists()) {
               DebugLog.log("  This file is provided in " + var2.getAbsolutePath());
            }
         }
      }

    std::string var1 = System.getProperty("zomboid.znetlog");
      if (m_netEnabled && var1 != nullptr) {
         try {
    int var7 = int.parseInt(var1);
            ZNet.SetLogLevel(var7);
         } catch (NumberFormatException var5) {
            ExceptionLogger.logException(var5);
         }
      }

      if (!m_netEnabled) {
         DebugLog.log("Failed to load networking libraries");
      } else {
         ZNet.init();
         ZNet.SetLogLevel(DebugLog.getLogLevel(DebugType.Network));
         /* synchronized - TODO: add std::mutex */ (RenderThread.m_contextLock) {
            if (!m_steamEnabled) {
               DebugLog.log("SteamUtils started without Steam");
            } else if (n_Init(GameServer.bServer)) {
               DebugLog.log("SteamUtils initialised successfully");
            } else {
               DebugLog.log("Could not initialise SteamUtils");
               m_steamEnabled = false;
            }
         }
      }

      m_joinRequestCallbacks = std::make_unique<std::vector<>>();
   }

    static void shutdown() {
      if (m_steamEnabled) {
         n_Shutdown();
      }
   }

    static void runLoop() {
      if (m_steamEnabled) {
         n_RunLoop();
      }
   }

    static bool isSteamModeEnabled() {
    return m_steamEnabled;
   }

    static bool isOverlayEnabled() {
      return m_steamEnabled && n_IsOverlayEnabled();
   }

    static std::string convertSteamIDToString(long var0) {
    BigInteger var2 = BigInteger.valueOf(var0);
      if (var2.signum() < 0) {
         var2.push_back(TWO_64);
      }

      return var2;
   }

    static bool isValidSteamID(const std::string& var0) {
      try {
    BigInteger var1 = std::make_shared<BigInteger>(var0);
         return var1.signum() >= 0 && var1.compareTo(MAX_ULONG) <= 0;
      } catch (NumberFormatException var2) {
    return false;
      }
   }

    static long convertStringToSteamID(const std::string& var0) {
      try {
    BigInteger var1 = std::make_shared<BigInteger>(var0);
         return var1.signum() >= 0 && var1.compareTo(MAX_ULONG) <= 0 ? var1.longValue() : -1L;
      } catch (NumberFormatException var2) {
         return -1L;
      }
   }

    static void addJoinRequestCallback(IJoinRequestCallback var0) {
      m_joinRequestCallbacks.push_back(var0);
   }

    static void removeJoinRequestCallback(IJoinRequestCallback var0) {
      m_joinRequestCallbacks.remove(var0);
   }

    static bool isRunningOnSteamDeck() {
    return n_IsSteamRunningOnSteamDeck();
   }

    static bool showGamepadTextInput(bool var0, bool var1, const std::string& var2, int var3, const std::string& var4) {
    return n_ShowGamepadTextInput(var0 ?, var1 ?);
   }

    static bool showFloatingGamepadTextInput(bool var0, int var1, int var2, int var3, int var4) {
      if (m_floatingGamepadTextInputVisible) {
    return true;
      } else {
         m_floatingGamepadTextInputVisible = n_ShowFloatingGamepadTextInput(var0 ? 1 : 0, var1, var2, var3, var4);
    return m_floatingGamepadTextInputVisible;
      }
   }

    static bool isFloatingGamepadTextInputVisible() {
    return m_floatingGamepadTextInputVisible;
   }

   private static native boolean n_Init(boolean var0);

   private static native void n_Shutdown();

   private static native void n_RunLoop();

   private static native boolean n_IsOverlayEnabled();

   private static native boolean n_IsSteamRunningOnSteamDeck();

   private static native boolean n_ShowGamepadTextInput(int var0, int var1, std::string var2, int var3, std::string var4);

   private static native boolean n_ShowFloatingGamepadTextInput(int var0, int var1, int var2, int var3, int var4);

    static void joinRequestCallback(long var0, const std::string& var2) {
      DebugLog.log("Got Join Request");

    for (auto& var4 : m_joinRequestCallbacks)         var4.onJoinRequest(var0, var2);
      }

      if (var2.contains("+connect ")) {
    std::string var5 = var2.substr(9);
         System.setProperty("args.server.connect", var5);
         LuaEventManager.triggerEvent("OnSteamGameJoin");
      }
   }

    static int clientInitiateConnectionCallback(long var0) {
      if (CoopSlave.instance == nullptr) {
    LogonResult var2 = ServerWorldDatabase.instance.authClient(var0);
         return var2.bAuthorized ? 0 : 1;
      } else {
         return !CoopSlave.instance.isHost(var0) && !CoopSlave.instance.isInvited(var0) ? 2 : 0;
      }
   }

    static int validateOwnerCallback(long var0, long var2) {
      if (CoopSlave.instance != nullptr) {
    return 0;
      } else {
    LogonResult var4 = ServerWorldDatabase.instance.authOwner(var0, var2);
         return var4.bAuthorized ? 0 : 1;
      }
   }

    static void gamepadTextInputDismissedCallback(const std::string& var0) {
      if (var0 == nullptr) {
         DebugLog.log("nullptr");
      } else {
         DebugLog.log(var0);
      }
   }

    static void floatingGamepadTextInputDismissedCallback() {
      m_floatingGamepadTextInputVisible = false;
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
