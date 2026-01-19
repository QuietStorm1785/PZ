#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Server {
public:
 std::string name = "My Server";
 std::string ip = "127.0.0.1";
 std::string localIP = "";
 std::string port = "16262";
 std::string serverpwd = "";
 std::string description = "";
 std::string userName = "";
 std::string pwd = "";
 bool useSteamRelay = false;
 int lastUpdate = 0;
 std::string players = nullptr;
 std::string maxPlayers = nullptr;
 bool open = false;
 bool bPublic = true;
 std::string version = nullptr;
 std::string mods = nullptr;
 bool passwordProtected;
 std::string steamId = nullptr;
 std::string ping = nullptr;
 bool hosted = false;

 std::string getPort() { return this->port; }

 void setPort(std::string_view _port) { this->port = _port; }

 std::string getIp() { return this->ip; }

 void setIp(std::string_view _ip) { this->ip = _ip; }

 std::string getLocalIP() { return this->localIP; }

 void setLocalIP(std::string_view _ip) { this->localIP = _ip; }

 std::string getServerPassword() { return this->serverpwd; }

 void setServerPassword(std::string_view _pwd) {
 this->serverpwd = _pwd.empty() ? "" : _pwd;
 }

 std::string getDescription() { return this->description; }

 void setDescription(std::string_view _description) {
 this->description = _description;
 }

 std::string getUserName() { return this->userName; }

 void setUserName(std::string_view _userName) { this->userName = _userName; }

 std::string getPwd() { return this->pwd; }

 void setPwd(std::string_view _pwd) { this->pwd = _pwd; }

 bool getUseSteamRelay() { return this->useSteamRelay; }

 void setUseSteamRelay(bool boolean0) { this->useSteamRelay = boolean0; }

 int getLastUpdate() { return this->lastUpdate; }

 void setLastUpdate(int _lastUpdate) { this->lastUpdate = _lastUpdate; }

 std::string getPlayers() { return this->players; }

 void setPlayers(std::string_view _players) { this->players = _players; }

 bool isOpen() { return this->open; }

 void setOpen(bool _open) { this->open = _open; }

 bool isPublic() { return this->bPublic; }

 void setPublic(bool _bPublic) { this->bPublic = _bPublic; }

 std::string getVersion() { return this->version; }

 void setVersion(std::string_view _version) { this->version = _version; }

 std::string getMaxPlayers() { return this->maxPlayers; }

 void setMaxPlayers(std::string_view _maxPlayers) {
 this->maxPlayers = _maxPlayers;
 }

 std::string getMods() { return this->mods; }

 void setMods(std::string_view _mods) { this->mods = _mods; }

 std::string getName() { return this->name; }

 void setName(std::string_view _name) { this->name = _name; }

 std::string getPing() { return this->ping; }

 void setPing(std::string_view _ping) { this->ping = _ping; }

 bool isPasswordProtected() { return this->passwordProtected; }

 void setPasswordProtected(bool pp) { this->passwordProtected = pp; }

 std::string getSteamId() { return this->steamId; }

 void setSteamId(std::string_view _steamId) { this->steamId = _steamId; }

 bool isHosted() { return this->hosted; }

 void setHosted(bool _hosted) { this->hosted = _hosted; }
}
} // namespace network
} // namespace zombie
