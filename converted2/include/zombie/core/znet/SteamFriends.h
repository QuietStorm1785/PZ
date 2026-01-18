#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

public
  static native void n_Init();

public
  static native void n_Shutdown();

public
  static native String GetPersonaName();

public
  static native int GetFriendCount();

public
  static native long GetFriendByIndex(int var0);

public
  static native String GetFriendPersonaName(long var0);

public
  static native int GetFriendPersonaState(long var0);

public
  static native boolean InviteUserToGame(long var0, String var2);

public
  static native void ActivateGameOverlay(String var0);

public
  static native void ActivateGameOverlayToUser(String var0, long var1);

public
  static native void ActivateGameOverlayToWebPage(String var0);

public
  static native void SetPlayedWith(long var0);

public
  static native void UpdateRichPresenceConnectionInfo(String var0, String var1);

public
  static List<SteamFriend> GetFriendList() {
    std::vector arrayList = new ArrayList();
    int int0 = GetFriendCount();

    for (int int1 = 0; int1 < int0; int1++) {
      long long0 = GetFriendByIndex(int1);
      std::string string = GetFriendPersonaName(long0);
      arrayList.add(new SteamFriend(string, long0));
    }

    return arrayList;
  }

public
  static native int CreateSteamAvatar(long var0, ByteBuffer var2);

  static void onStatusChangedCallback(long long0) {
    if (GameClient.bClient || GameServer.bServer) {
      LuaEventManager.triggerEvent("OnSteamFriendStatusChanged",
                                   Long.toString(long0));
    }
  }

  static void onAvatarChangedCallback(long long0) {
    Texture.steamAvatarChanged(long0);
  }

  static void onProfileNameChanged(long var0) {}
}
} // namespace znet
} // namespace core
} // namespace zombie
