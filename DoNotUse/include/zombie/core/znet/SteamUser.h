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

class SteamUser {
public:
    static long GetSteamID() {
      return SteamUtils.isSteamModeEnabled() ? n_GetSteamID() : 0L;
   }

    static std::string GetSteamIDString() {
      if (SteamUtils.isSteamModeEnabled()) {
    long var0 = n_GetSteamID();
         return SteamUtils.convertSteamIDToString(var0);
      } else {
    return nullptr;
      }
   }

   private static native long n_GetSteamID();
}
} // namespace znet
} // namespace core
} // namespace zombie
