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
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SteamUtils {
public:
 static bool m_steamEnabled;
 static bool m_netEnabled;
 static bool m_floatingGamepadTextInputVisible = false;
 static const BigInteger TWO_64 = BigInteger.ONE.shiftLeft(64);
 static const BigInteger MAX_ULONG = new BigInteger("FFFFFFFFFFFFFFFF", 16);
 private static List<IJoinRequestCallback> m_joinRequestCallbacks;
 static const int k_EGamepadTextInputModeNormal = 0;
 static const int k_EGamepadTextInputModePassword = 1;
 static const int k_EGamepadTextInputLineModeSingleLine = 0;
 static const int k_EGamepadTextInputLineModeMultipleLines = 1;
 static const int k_EFloatingGamepadTextInputModeSingleLine = 0;
 static const int k_EFloatingGamepadTextInputModeMultipleLines = 1;
 static const int k_EFloatingGamepadTextInputModeEmail = 2;
 static const int k_EFloatingGamepadTextInputModeNumeric = 3;

 static void loadLibrary(const std::string& string) {
 DebugLog.log("Loading " + string + "...");
 System.loadLibrary(string);
 }

 static void init() {
 m_steamEnabled = System.getProperty("zomboid.steam") != nullptr && System.getProperty("zomboid.steam") == "1");
 DebugLog.log("Loading networking libraries...");
 std::string string0 = "";
 if ("1" == System.getProperty("zomboid.debuglibs.znet"))) {
 DebugLog.log("***** Loading debug versions of libraries");
 string0 = "d";
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
 loadLibrary("RakNet64" + string0);
 loadLibrary("ZNetJNI64" + string0);
 } else {
 loadLibrary("RakNet64" + string0);
 loadLibrary("ZNetNoSteam64" + string0);
 }
 } else if (m_steamEnabled) {
 loadLibrary("steam_api");
 loadLibrary("RakNet32" + string0);
 loadLibrary("ZNetJNI32" + string0);
 } else {
 loadLibrary("RakNet32" + string0);
 loadLibrary("ZNetNoSteam32" + string0);
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
 } catch (UnsatisfiedLinkError unsatisfiedLinkError) {
 m_steamEnabled = false;
 m_netEnabled = false;
 ExceptionLogger.logException(unsatisfiedLinkError);
 if (System.getProperty("os.name").startsWith("Win")) {
 DebugLog.log("One of the game's DLLs could not be loaded.");
 DebugLog.log(" Your system may be missing a DLL needed by the game's DLL.");
 DebugLog.log(" You may need to install the Microsoft Visual C++ Redistributable 2013.");
 File file = new File("../_CommonRedist/vcredist/");
 if (file.exists()) {
 DebugLog.log(" This file is provided in " + file.getAbsolutePath());
 }
 }
 }

 std::string string1 = System.getProperty("zomboid.znetlog");
 if (m_netEnabled && string1 != nullptr) {
 try {
 int int0 = Integer.parseInt(string1);
 ZNet.SetLogLevel(int0);
 } catch (NumberFormatException numberFormatException) {
 ExceptionLogger.logException(numberFormatException);
 }
 }

 if (!m_netEnabled) {
 DebugLog.log("Failed to load networking libraries");
 } else {
 ZNet.init();
 ZNet.SetLogLevel(DebugLog.getLogLevel(DebugType.Network);
 synchronized (RenderThread.m_contextLock) {
 if (!m_steamEnabled) {
 DebugLog.log("SteamUtils started without Steam");
 } else if (n_Init(GameServer.bServer) {
 DebugLog.log("SteamUtils initialised successfully");
 } else {
 DebugLog.log("Could not initialise SteamUtils");
 m_steamEnabled = false;
 }
 }
 }

 m_joinRequestCallbacks = std::make_unique<ArrayList<>>();
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

 static std::string convertSteamIDToString(long long0) {
 BigInteger bigInteger = BigInteger.valueOf(long0);
 if (bigInteger.signum() < 0) {
 bigInteger.add(TWO_64);
 }

 return bigInteger.toString();
 }

 static bool isValidSteamID(const std::string& string) {
 try {
 BigInteger bigInteger = new BigInteger(string);
 return bigInteger.signum() >= 0 && bigInteger.compareTo(MAX_ULONG) <= 0;
 } catch (NumberFormatException numberFormatException) {
 return false;
 }
 }

 static long convertStringToSteamID(const std::string& string) {
 try {
 BigInteger bigInteger = new BigInteger(string);
 return bigInteger.signum() >= 0 && bigInteger.compareTo(MAX_ULONG) <= 0 ? bigInteger.longValue() : -1L;
 } catch (NumberFormatException numberFormatException) {
 return -1L;
 }
 }

 static void addJoinRequestCallback(IJoinRequestCallback iJoinRequestCallback) {
 m_joinRequestCallbacks.add(iJoinRequestCallback);
 }

 static void removeJoinRequestCallback(IJoinRequestCallback iJoinRequestCallback) {
 m_joinRequestCallbacks.remove(iJoinRequestCallback);
 }

 static bool isRunningOnSteamDeck() {
 return n_IsSteamRunningOnSteamDeck();
 }

 static bool showGamepadTextInput(bool boolean1, bool boolean0, const std::string& string0, int int0, const std::string& string1) {
 return n_ShowGamepadTextInput(boolean1 ?, boolean0 ?);
 }

 static bool showFloatingGamepadTextInput(bool boolean0, int int0, int int1, int int2, int int3) {
 if (m_floatingGamepadTextInputVisible) {
 return true;
 } else {
 m_floatingGamepadTextInputVisible = n_ShowFloatingGamepadTextInput(boolean0 ? 1 : 0, int0, int1, int2, int3);
 return m_floatingGamepadTextInputVisible;
 }
 }

 static bool isFloatingGamepadTextInputVisible() {
 return m_floatingGamepadTextInputVisible;
 }

 private static boolean n_Init(boolean var0);

 private static void n_Shutdown();

 private static void n_RunLoop();

 private static boolean n_IsOverlayEnabled();

 private static boolean n_IsSteamRunningOnSteamDeck();

 private static boolean n_ShowGamepadTextInput(int var0, int var1, String var2, int var3, String var4);

 private static boolean n_ShowFloatingGamepadTextInput(int var0, int var1, int var2, int var3, int var4);

 static void joinRequestCallback(long long0, const std::string& string0) {
 DebugLog.log("Got Join Request");

 for (auto& iJoinRequestCallback : m_joinRequestCallbacks) iJoinRequestCallback.onJoinRequest(long0, string0);
 }

 if (string0.contains("+connect ")) {
 std::string string1 = string0.substring(9);
 System.setProperty("args.server.connect", string1);
 LuaEventManager.triggerEvent("OnSteamGameJoin");
 }
 }

 static int clientInitiateConnectionCallback(long long0) {
 if (CoopSlave.instance == nullptr) {
 ServerWorldDatabase.LogonResult logonResult = ServerWorldDatabase.instance.authClient(long0);
 return logonResult.bAuthorized ? 0 : 1;
 } else {
 return !CoopSlave.instance.isHost(long0) && !CoopSlave.instance.isInvited(long0) ? 2 : 0;
 }
 }

 static int validateOwnerCallback(long long0, long long1) {
 if (CoopSlave.instance != nullptr) {
 return 0;
 } else {
 ServerWorldDatabase.LogonResult logonResult = ServerWorldDatabase.instance.authOwner(long0, long1);
 return logonResult.bAuthorized ? 0 : 1;
 }
 }

 static void gamepadTextInputDismissedCallback(const std::string& string) {
 if (string == nullptr) {
 DebugLog.log("nullptr");
 } else {
 DebugLog.log(string);
 }
 }

 static void floatingGamepadTextInputDismissedCallback() {
 m_floatingGamepadTextInputVisible = false;
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
