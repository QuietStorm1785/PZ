#include "Server.h"

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {


Server::Server() = default;
Server::~Server() = default;

std::string Server::getPort() const { return port; }
void Server::setPort(const std::string& val) { port = val; }
std::string Server::getIp() const { return ip; }
void Server::setIp(const std::string& val) { ip = val; }
std::string Server::getLocalIP() const { return localIP; }
void Server::setLocalIP(const std::string& val) { localIP = val; }
std::string Server::getServerPassword() const { return serverpwd; }
void Server::setServerPassword(const std::string& val) { serverpwd = val.empty() ? "" : val; }
std::string Server::getDescription() const { return description; }
void Server::setDescription(const std::string& val) { description = val; }
std::string Server::getUserName() const { return userName; }
void Server::setUserName(const std::string& val) { userName = val; }
std::string Server::getPwd() const { return pwd; }
void Server::setPwd(const std::string& val) { pwd = val; }
bool Server::getUseSteamRelay() const { return useSteamRelay; }
void Server::setUseSteamRelay(bool val) { useSteamRelay = val; }
int Server::getLastUpdate() const { return lastUpdate; }
void Server::setLastUpdate(int val) { lastUpdate = val; }
std::string Server::getPlayers() const { return players; }
void Server::setPlayers(const std::string& val) { players = val; }
bool Server::isOpen() const { return open; }
void Server::setOpen(bool val) { open = val; }
bool Server::isPublic() const { return bPublic; }
void Server::setPublic(bool val) { bPublic = val; }
std::string Server::getVersion() const { return version; }
void Server::setVersion(const std::string& val) { version = val; }
std::string Server::getMaxPlayers() const { return maxPlayers; }
void Server::setMaxPlayers(const std::string& val) { maxPlayers = val; }
std::string Server::getMods() const { return mods; }
void Server::setMods(const std::string& val) { mods = val; }
std::string Server::getName() const { return name; }
void Server::setName(const std::string& val) { name = val; }
std::string Server::getPing() const { return ping; }
void Server::setPing(const std::string& val) { ping = val; }
bool Server::isPasswordProtected() const { return passwordProtected; }
void Server::setPasswordProtected(bool val) { passwordProtected = val; }
std::string Server::getSteamId() const { return steamId; }
void Server::setSteamId(const std::string& val) { steamId = val; }
bool Server::isHosted() const { return hosted; }
void Server::setHosted(bool val) { hosted = val; }
bool Server::getUseSteamRelay() const { return useSteamRelay; }
void Server::setUseSteamRelay(bool val) { useSteamRelay = val; }
int Server::getLastUpdate() const { return lastUpdate; }
void Server::setLastUpdate(int val) { lastUpdate = val; }
std::string Server::getPlayers() const { return players; }
void Server::setPlayers(const std::string& val) { players = val; }
bool Server::isOpen() const { return open; }
void Server::setOpen(bool val) { open = val; }
bool Server::isPublic() const { return bPublic; }
void Server::setPublic(bool val) { bPublic = val; }
std::string Server::getVersion() const { return version; }
void Server::setVersion(const std::string& val) { version = val; }
std::string Server::getMaxPlayers() const { return maxPlayers; }
void Server::setMaxPlayers(const std::string& val) { maxPlayers = val; }
std::string Server::getMods() const { return mods; }
void Server::setMods(const std::string& val) { mods = val; }
std::string Server::getName() const { return name; }
void Server::setName(const std::string& val) { name = val; }
std::string Server::getPing() const { return ping; }
void Server::setPing(const std::string& val) { ping = val; }
bool Server::isPasswordProtected() const { return passwordProtected; }
void Server::setPasswordProtected(bool val) { passwordProtected = val; }
std::string Server::getSteamId() const { return steamId; }
void Server::setSteamId(const std::string& val) { steamId = val; }
bool Server::isHosted() const { return hosted; }
void Server::setHosted(bool val) { hosted = val; }

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
