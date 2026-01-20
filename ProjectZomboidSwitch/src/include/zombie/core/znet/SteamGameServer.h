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

class SteamGameServer {
public:
    static int STEAM_SERVERS_DISCONNECTED = 0;
    static int STEAM_SERVERS_CONNECTED = 1;
    static int STEAM_SERVERS_CONNECTFAILURE = 2;

   public static native boolean Init(std::string var0, int var1, int var2, int var3, std::string var4);

   public static native void SetProduct(std::string var0);

   public static native void SetGameDescription(std::string var0);

   public static native void SetModDir(std::string var0);

   public static native void SetDedicatedServer(boolean var0);

   public static native void LogOnAnonymous();

   public static native void EnableHeartBeats(boolean var0);

   public static native void SetMaxPlayerCount(int var0);

   public static native void SetServerName(std::string var0);

   public static native void SetMapName(std::string var0);

   public static native void SetKeyValue(std::string var0, std::string var1);

   public static native void SetGameTags(std::string var0);

   public static native void SetRegion(std::string var0);

   public static native boolean BUpdateUserData(long var0, std::string var2, int var3);

   public static native int GetSteamServersConnectState();

   public static native long GetSteamID();
}
} // namespace znet
} // namespace core
} // namespace zombie
