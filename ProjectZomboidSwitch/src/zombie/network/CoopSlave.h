
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: CoopSlave


class CoopSlave {
public:
    static CoopSlave* instance;
    static void init();
    static void initStreams();
    CoopSlave();
    ~CoopSlave();

    void notify(const std::string& msg);
    void sendStatus(const std::string& msg);
    static void status(const std::string& msg);
    void sendMessage(const std::string& msg);
    void sendMessage(const std::string& type, const std::string& tag, const std::string& payload);
    void sendExternalIPAddress(const std::string& tag);
    void sendSteamID(const std::string& tag);
    bool handleCommand(const std::string& cmd);
    std::string getHostUser() const;
    void update();
    bool masterLost() const;
    bool isHost(int64_t steamID) const;
    bool isInvited(int64_t steamID) const;

    std::string hostUser;
    int64_t hostSteamID = 0;

private:
    // Simulate PrintStream with std::ostream*
    static std::ostream* stdoutStream;
    static std::ostream* stderrStream;
    // Regex for server message parsing
    std::string serverMessagePattern;
    int64_t nextPing = -1;
    int64_t lastPong = -1;
    bool masterLostFlag = false;
    std::unordered_set<int64_t> invites;
    int64_t serverSteamID = 0;
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
