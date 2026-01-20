#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace znet {


class SteamFriends {
public:
    static const int k_EPersonaStateOffline = 0;
    static const int k_EPersonaStateOnline = 1;
    static const int k_EPersonaStateBusy = 2;
    static const int k_EPersonaStateAway = 3;
    static const int k_EPersonaStateSnooze = 4;
    static const int k_EPersonaStateLookingToTrade = 5;
    static const int k_EPersonaStateLookingToPlay = 6;

    static void init() {
      if (SteamUtils.isSteamModeEnabled()) {
         n_Init();
      }
   }

    static void shutdown() {
      if (SteamUtils.isSteamModeEnabled()) {
         n_Shutdown();
      }
   }

   public static native void n_Init();

   public static native void n_Shutdown();

   public static native std::string GetPersonaName();

   public static native int GetFriendCount();

   public static native long GetFriendByIndex(int var0);

   public static native std::string GetFriendPersonaName(long var0);

   public static native int GetFriendPersonaState(long var0);

   public static native boolean InviteUserToGame(long var0, std::string var2);

   public static native void ActivateGameOverlay(std::string var0);

   public static native void ActivateGameOverlayToUser(std::string var0, long var1);

   public static native void ActivateGameOverlayToWebPage(std::string var0);

   public static native void SetPlayedWith(long var0);

   public static native void UpdateRichPresenceConnectionInfo(std::string var0, std::string var1);

   public static List<SteamFriend> GetFriendList() {
    std::vector var0 = new std::vector();
    int var1 = GetFriendCount();

      for (int var2 = 0; var2 < var1; var2++) {
    long var3 = GetFriendByIndex(var2);
    std::string var5 = GetFriendPersonaName(var3);
         var0.push_back(std::make_shared<SteamFriend>(var5, var3));
      }

    return var0;
   }

   public static native int CreateSteamAvatar(long var0, ByteBuffer var2);

    static void onStatusChangedCallback(long var0) {
      if (GameClient.bClient || GameServer.bServer) {
         LuaEventManager.triggerEvent("OnSteamFriendStatusChanged", int64_t.toString(var0));
      }
   }

    static void onAvatarChangedCallback(long var0) {
      Texture.steamAvatarChanged(var0);
   }

    static void onProfileNameChanged(long var0) {
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
