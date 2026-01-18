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

class IServerBrowserCallback {
public:
 virtual ~IServerBrowserCallback() = default;
 void OnServerResponded(int var1);

 void OnServerFailedToRespond(int var1);

 void OnRefreshComplete();

 void OnServerResponded(const std::string& var1, int var2);

 void OnServerFailedToRespond(const std::string& var1, int var2);

 void OnSteamRulesRefreshComplete(const std::string& var1, int var2);
}
} // namespace znet
} // namespace core
} // namespace zombie
