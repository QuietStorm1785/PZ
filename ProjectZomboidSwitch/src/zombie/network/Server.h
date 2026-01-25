#pragma once
#include <string>
#include <vector>
#include <memory>
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: Server

class Server {
public:
    Server();
    ~Server();

    // Getters and setters for all fields
    std::string getPort() const;
    void setPort(const std::string& val);
    std::string getIp() const;
    void setIp(const std::string& val);
    std::string getLocalIP() const;
    void setLocalIP(const std::string& val);
    std::string getServerPassword() const;
    void setServerPassword(const std::string& val);
    std::string getDescription() const;
    void setDescription(const std::string& val);
    std::string getUserName() const;
    void setUserName(const std::string& val);
    std::string getPwd() const;
    void setPwd(const std::string& val);
    bool getUseSteamRelay() const;
    void setUseSteamRelay(bool val);
    int getLastUpdate() const;
    void setLastUpdate(int val);
    std::string getPlayers() const;
    void setPlayers(const std::string& val);
    bool isOpen() const;
    void setOpen(bool val);
    bool isPublic() const;
    void setPublic(bool val);
    std::string getVersion() const;
    void setVersion(const std::string& val);
    std::string getMaxPlayers() const;
    void setMaxPlayers(const std::string& val);
    std::string getMods() const;
    void setMods(const std::string& val);
    std::string getName() const;
    void setName(const std::string& val);
    std::string getPing() const;
    void setPing(const std::string& val);
    bool isPasswordProtected() const;
    void setPasswordProtected(bool val);
    std::string getSteamId() const;
    void setSteamId(const std::string& val);
    bool isHosted() const;
    void setHosted(bool val);

private:
    std::string name = "My Server";
    std::string ip = "127.0.0.1";
    std::string localIP;
    std::string port = "16262";
    std::string serverpwd;
    std::string description;
    std::string userName;
    std::string pwd;
    bool useSteamRelay = false;
    int lastUpdate = 0;
    std::string players;
    std::string maxPlayers;
    bool open = false;
    bool bPublic = true;
    std::string version;
    std::string mods;
    bool passwordProtected = false;
    std::string steamId;
    std::string ping;
    bool hosted = false;
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
