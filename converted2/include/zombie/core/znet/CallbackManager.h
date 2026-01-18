#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include <cstdint>
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

class CallbackManager {
public:
public
  CallbackManager() { SteamUtils.addJoinRequestCallback(this); }

  void onJoinRequest(long var1, const std::string &string) {
    LuaEventManager.triggerEvent("OnAcceptInvite", string);
  }
}
} // namespace znet
} // namespace core
} // namespace zombie
