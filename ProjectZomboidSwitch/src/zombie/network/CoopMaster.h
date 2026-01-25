// Registers CoopMaster Lua functions in the given Lua state
extern "C" void CoopMaster_registerLua(lua_State* L);
private:
    void launchServerInternal(const std::string& name, const std::string& admin, int mem, bool softreset);

#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: CoopMaster and all inner classes


class CoopMaster {
public:
    CoopMaster();
    ~CoopMaster();

    // Fields ported from Java
    void* serverProcess = nullptr;
    void* serverThread = nullptr;
    void* serverCommandStream = nullptr;
    std::vector<std::string> incomingMessages;
    void* serverMessageParser = nullptr;
    void* serverTerminationReason = nullptr;
    void* timeoutWatchThread = nullptr;
    bool serverResponded = false;
    static CoopMaster* instance;
    std::string adminUsername;
    std::string adminPassword;
    std::string serverName;
    void* serverSteamID = nullptr;
    std::string serverIP;
    int serverPort = 0;
    int autoCookie = 0;
    static constexpr int autoCookieOffset = 1000000;
    static constexpr int maxAutoCookie = 1000000;
    struct ListenerOptions;
    struct Pair;
    struct TerminationReason;
    std::vector<Pair> listeners;

    // Methods ported from Java
    int getServerPort() const;
    void launchServer(const std::string& name, const std::string& admin, int mem);
    void softreset(const std::string& name, const std::string& admin, int mem);
    bool isRunning() const;
    std::string getServerName() const;
    std::string getServerSaveFolder(const std::string& worldName) const;
    std::string getPlayerSaveFolder(const std::string& worldName) const;
    // ...other methods to be ported...

    // Inner classes from Java (CoopMaster$1, $2, ... $12, ListenerOptions, Pair, TerminationReason)
    struct ListenerOptions {
        std::string tag;
        std::string cookie;
        bool autoRemove = false;
        ListenerOptions() = default;
        ListenerOptions(const std::string& tag, const std::string& cookie, bool autoRemove)
            : tag(tag), cookie(cookie), autoRemove(autoRemove) {}
    };
    struct Pair {
        void* first = nullptr; // ICoopServerMessageListener*
        ListenerOptions second;
        Pair() = default;
        Pair(void* first, const ListenerOptions& second) : first(first), second(second) {}
    };
    enum class TerminationReason {
        NormalTermination,
        Timeout
    };

    // Stubs for Java inner classes (CoopMaster$1 ... $12)
    struct Inner1 { Inner1() = default; };
    struct Inner2 { Inner2() = default; };
    struct Inner3 { Inner3() = default; };
    struct Inner4 { Inner4() = default; };
    struct Inner5 { Inner5() = default; };
    struct Inner6 { Inner6() = default; };
    struct Inner7 { Inner7() = default; };
    struct Inner8 { Inner8() = default; };
    struct Inner9 { Inner9() = default; };
    struct Inner10 { Inner10() = default; };
    struct Inner11 { Inner11() = default; };
    struct Inner12 { Inner12() = default; };

private:
    void launchServerInternal(const std::string& name, const std::string& admin, int mem, bool softreset);

    // Inner classes from Java (CoopMaster$1, $2, ... $12, ListenerOptions, Pair, TerminationReason)
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // TODO: Port fields and methods from Java CoopMaster$1
    };
    class Inner2 {
    public:
        Inner2();
        ~Inner2();
        // TODO: Port fields and methods from Java CoopMaster$2
    };
    class Inner3 {
    public:
        Inner3();
        ~Inner3();
        // TODO: Port fields and methods from Java CoopMaster$3
    };
    class Inner4 {
    public:
        Inner4();
        ~Inner4();
        // TODO: Port fields and methods from Java CoopMaster$4
    };
    class Inner5 {
    public:
        Inner5();
        ~Inner5();
        // TODO: Port fields and methods from Java CoopMaster$5
    };
    class Inner6 {
    public:
        Inner6();
        ~Inner6();
        // TODO: Port fields and methods from Java CoopMaster$6
    };
    class Inner7 {
    public:
        Inner7();
        ~Inner7();
        // TODO: Port fields and methods from Java CoopMaster$7
    };
    class Inner8 {
    public:
        Inner8();
        ~Inner8();
        // TODO: Port fields and methods from Java CoopMaster$8
    };
    class Inner9 {
    public:
        Inner9();
        ~Inner9();
        // TODO: Port fields and methods from Java CoopMaster$9
    };
    class Inner10 {
    public:
        Inner10();
        ~Inner10();
        // TODO: Port fields and methods from Java CoopMaster$10
    };
    class Inner11 {
    public:
        Inner11();
        ~Inner11();
        // TODO: Port fields and methods from Java CoopMaster$11
    };
    class Inner12 {
    public:
        Inner12();
        ~Inner12();
        // TODO: Port fields and methods from Java CoopMaster$12
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
