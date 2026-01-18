#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class SteamGameServer {
public:
 static int STEAM_SERVERS_DISCONNECTED = 0;
 static int STEAM_SERVERS_CONNECTED = 1;
 static int STEAM_SERVERS_CONNECTFAILURE = 2;

 public static boolean Init(String var0, int var1, int var2, int var3, String var4);

 public static void SetProduct(String var0);

 public static void SetGameDescription(String var0);

 public static void SetModDir(String var0);

 public static void SetDedicatedServer(boolean var0);

 public static void LogOnAnonymous();

 public static void EnableHeartBeats(boolean var0);

 public static void SetMaxPlayerCount(int var0);

 public static void SetServerName(String var0);

 public static void SetMapName(String var0);

 public static void SetKeyValue(String var0, String var1);

 public static void SetGameTags(String var0);

 public static void SetRegion(String var0);

 public static boolean BUpdateUserData(long var0, String var2, int var3);

 public static int GetSteamServersConnectState();

 public static long GetSteamID();
}
} // namespace znet
} // namespace core
} // namespace zombie
