#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IServerBrowserCallback {
public:
 virtual ~IServerBrowserCallback() = default;
 void OnServerResponded(int var1);

 void OnServerFailedToRespond(int var1);

 void OnRefreshComplete();

 void OnServerResponded(std::string_view var1, int var2);

 void OnServerFailedToRespond(std::string_view var1, int var2);

 void OnSteamRulesRefreshComplete(std::string_view var1, int var2);
}
} // namespace znet
} // namespace core
} // namespace zombie
