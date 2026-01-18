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

class SteamUser {
public:
 static long GetSteamID() {
 return SteamUtils.isSteamModeEnabled() ? n_GetSteamID() : 0L;
 }

 static std::string GetSteamIDString() {
 if (SteamUtils.isSteamModeEnabled()) {
 long long0 = n_GetSteamID();
 return SteamUtils.convertSteamIDToString(long0);
 } else {
 return nullptr;
 }
 }

 private static long n_GetSteamID();
}
} // namespace znet
} // namespace core
} // namespace zombie
