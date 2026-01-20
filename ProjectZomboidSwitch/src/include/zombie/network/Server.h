#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

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

    std::string getPort() {
      return this.port;
   }

    void setPort(const std::string& var1) {
      this.port = var1;
   }

    std::string getIp() {
      return this.ip;
   }

    void setIp(const std::string& var1) {
      this.ip = var1;
   }

    std::string getLocalIP() {
      return this.localIP;
   }

    void setLocalIP(const std::string& var1) {
      this.localIP = var1;
   }

    std::string getServerPassword() {
      return this.serverpwd;
   }

    void setServerPassword(const std::string& var1) {
      this.serverpwd = var1 == nullptr ? "" : var1;
   }

    std::string getDescription() {
      return this.description;
   }

    void setDescription(const std::string& var1) {
      this.description = var1;
   }

    std::string getUserName() {
      return this.userName;
   }

    void setUserName(const std::string& var1) {
      this.userName = var1;
   }

    std::string getPwd() {
      return this.pwd;
   }

    void setPwd(const std::string& var1) {
      this.pwd = var1;
   }

    bool getUseSteamRelay() {
      return this.useSteamRelay;
   }

    void setUseSteamRelay(bool var1) {
      this.useSteamRelay = var1;
   }

    int getLastUpdate() {
      return this.lastUpdate;
   }

    void setLastUpdate(int var1) {
      this.lastUpdate = var1;
   }

    std::string getPlayers() {
      return this.players;
   }

    void setPlayers(const std::string& var1) {
      this.players = var1;
   }

    bool isOpen() {
      return this.open;
   }

    void setOpen(bool var1) {
      this.open = var1;
   }

    bool isPublic() {
      return this.bPublic;
   }

    void setPublic(bool var1) {
      this.bPublic = var1;
   }

    std::string getVersion() {
      return this.version;
   }

    void setVersion(const std::string& var1) {
      this.version = var1;
   }

    std::string getMaxPlayers() {
      return this.maxPlayers;
   }

    void setMaxPlayers(const std::string& var1) {
      this.maxPlayers = var1;
   }

    std::string getMods() {
      return this.mods;
   }

    void setMods(const std::string& var1) {
      this.mods = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getPing() {
      return this.ping;
   }

    void setPing(const std::string& var1) {
      this.ping = var1;
   }

    bool isPasswordProtected() {
      return this.passwordProtected;
   }

    void setPasswordProtected(bool var1) {
      this.passwordProtected = var1;
   }

    std::string getSteamId() {
      return this.steamId;
   }

    void setSteamId(const std::string& var1) {
      this.steamId = var1;
   }

    bool isHosted() {
      return this.hosted;
   }

    void setHosted(bool var1) {
      this.hosted = var1;
   }
}
} // namespace network
} // namespace zombie
