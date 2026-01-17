#include "zombie/core/znet/IServerBrowserCallback.h"

namespace zombie {
namespace core {
namespace znet {

void IServerBrowserCallback::OnServerResponded(int var1) {
  // TODO: Implement OnServerResponded
}

void IServerBrowserCallback::OnServerFailedToRespond(int var1) {
  // TODO: Implement OnServerFailedToRespond
}

void IServerBrowserCallback::OnRefreshComplete() {
  // TODO: Implement OnRefreshComplete
}

void IServerBrowserCallback::OnServerResponded(const std::string &var1,
                                               int var2) {
  // TODO: Implement OnServerResponded
}

void IServerBrowserCallback::OnServerFailedToRespond(const std::string &var1,
                                                     int var2) {
  // TODO: Implement OnServerFailedToRespond
}

void IServerBrowserCallback::OnSteamRulesRefreshComplete(
    const std::string &var1, int var2) {
  // TODO: Implement OnSteamRulesRefreshComplete
}

} // namespace znet
} // namespace core
} // namespace zombie
