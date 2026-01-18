#include "zombie/core/znet/ServerBrowser.h"

namespace zombie {
namespace core {
namespace znet {

bool ServerBrowser::init() {
 // TODO: Implement init
 return false;
}

void ServerBrowser::shutdown() {
 // TODO: Implement shutdown
}

void ServerBrowser::RefreshInternetServers() {
 // TODO: Implement RefreshInternetServers
}

int ServerBrowser::GetServerCount() {
 // TODO: Implement GetServerCount
 return 0;
}

GameServerDetails ServerBrowser::GetServerDetails(int int0) {
 // TODO: Implement GetServerDetails
 return nullptr;
}

void ServerBrowser::Release() {
 // TODO: Implement Release
}

bool ServerBrowser::IsRefreshing() {
 // TODO: Implement IsRefreshing
 return false;
}

bool ServerBrowser::QueryServer(const std::string& string, int int0) {
 // TODO: Implement QueryServer
 return false;
}

GameServerDetails ServerBrowser::GetServerDetails(const std::string& string, int int0) {
 // TODO: Implement GetServerDetails
 return nullptr;
}

void ServerBrowser::ReleaseServerQuery(const std::string& string, int int0) {
 // TODO: Implement ReleaseServerQuery
}

GameServerDetails ServerBrowser::GetServerDetailsSync(const std::string& string, int int0) {
 // TODO: Implement GetServerDetailsSync
 return nullptr;
}

bool ServerBrowser::RequestServerRules(const std::string& string, int int0) {
 // TODO: Implement RequestServerRules
 return false;
}

return ServerBrowser::n_RequestServerRules() {
 // TODO: Implement n_RequestServerRules
 return nullptr;
}

void ServerBrowser::setCallbackInterface(IServerBrowserCallback iServerBrowserCallback) {
 // TODO: Implement setCallbackInterface
}

void ServerBrowser::onServerRespondedCallback(int int0) {
 // TODO: Implement onServerRespondedCallback
}

void ServerBrowser::onServerFailedToRespondCallback(int int0) {
 // TODO: Implement onServerFailedToRespondCallback
}

void ServerBrowser::onRefreshCompleteCallback() {
 // TODO: Implement onRefreshCompleteCallback
}

void ServerBrowser::onServerRespondedCallback(const std::string& string, int int0) {
 // TODO: Implement onServerRespondedCallback
}

void ServerBrowser::onServerFailedToRespondCallback(const std::string& string, int int0) {
 // TODO: Implement onServerFailedToRespondCallback
}

void ServerBrowser::onRulesRefreshComplete(const std::string& string, int int0, String[] strings) {
 // TODO: Implement onRulesRefreshComplete
}

} // namespace znet
} // namespace core
} // namespace zombie
