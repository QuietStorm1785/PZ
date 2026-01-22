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
