
#pragma once

// NAMESPACE WRAP BEGIN
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/spnetwork/ZomboidNetData.h"
#include <glm/vec2.hpp>
namespace zombie {
namespace network {

// Ported from Java: GameClient and all inner classes


class GameClient {
public:
    GameClient();
    ~GameClient();

    // --- Static fields (from Java) ---
    static GameClient* instance;
    static constexpr int DEFAULT_PORT = 16361;
    static bool bClient;
    static int count;
    static std::string ip;
    static std::string ServerName;
    static std::string localIP;
    static std::string password;
    static bool allChatMuted;
    static std::string username;
    static std::string serverPassword;
    static bool useSteamRelay;
    static int port;
    static std::string checksum;
    static bool checksumValid;
    static std::vector<long> pingsList;
    static std::string GameMap;
    static bool bFastForward;
    // Ported static collections from Java source
    static std::unordered_set<int> loadedCells;
    static std::unordered_map<int, org::joml::Vector2*> positions;
    static std::unordered_map<short, zombie::characters::IsoPlayer*> IDToPlayerMap;
    static std::unordered_map<short, void*> IDToZombieMap; // TODO: Replace void* with IsoZombie* when available
    // Ported collections for items to send/remove
    static std::vector<void*> itemsToSend;
    static std::vector<void*> itemsToSendRemove;
    static bool bCoopInvite;
    static bool isPaused;
    static long steamID;
    static bool bIngame;
    static bool askPing;

    // --- Enum for RequestState (inner class in Java) ---
    enum class RequestState {
        Start,
        Loading,
        Complete
    };


    // --- Instance fields (from Java) ---
    // Instance fields
    core::raknet::UdpEngine* udpEngine = nullptr;
    uint8_t ID = static_cast<uint8_t>(-1);
    float timeSinceKeepAlive = 0.0f;
    core::utils::UpdateLimit itemSendFrequency{0};
    bool bPlayerConnectSent = false;
    bool bClientStarted = false;
    int ResetID = 0;
    bool bConnectionLost = false;
    std::vector<zombie::characters::IsoPlayer*> connectedPlayers;
    std::vector<zombie::characters::IsoPlayer*> players;
    bool idMapDirty = true;
    int safehouseUpdateTimer = 0;
    bool delayPacket = false;
    std::vector<int> delayedDisconnect;
    // Major collections and queues
    std::queue<zombie::spnetwork::ZomboidNetData*> MainLoopNetDataQ;
    std::vector<zombie::spnetwork::ZomboidNetData*> MainLoopNetData;
    std::vector<zombie::spnetwork::ZomboidNetData*> LoadingMainLoopNetData;
    std::vector<zombie::spnetwork::ZomboidNetData*> DelayedCoopNetData;
    std::vector<long> tempShortList;
    RequestState request = RequestState::Start;
    void* ServerSpawnRegions = nullptr; // KahluaTable*
    bool bConnected = false;
    core::utils::UpdateLimit PlayerUpdateReliableLimit{0};
    int TimeSinceLastUpdate = 0;
    core::ByteBuffer staticTest{1024}; // Default to 1024 bytes, adjust as needed
    core::network::ByteBufferWriter wr{staticTest};
    long StartHeartMilli = 0L;
    long EndHeartMilli = 0L;
    int ping = 0;
    // Hash maps and ID maps
    std::unordered_map<short, zombie::characters::IsoPlayer*> IDToPlayerMap;
    std::unordered_map<short, void*> IDToZombieMap; // TODO: Replace void* with IsoZombie* when available
    std::unordered_map<short, org::joml::Vector2*> positions;


    // --- Method stubs (to be implemented) ---
    void init();
    void startClient();
    void update();
    void Shutdown();

    // --- Static/utility methods (ported from Java) ---
    static void* getZombie(short id); // Returns IsoZombie* (void* placeholder)
    static void* getPlayerByOnlineID(short id); // Returns IsoPlayer* (void* placeholder)
    static bool IsClientPaused();
    static void sendPlayer(void* player); // Use IsoPlayer* when ported
    static void sendPlayer2(void* player); // Use IsoPlayer* when ported
    static void sendPlayerConnect(void* player); // Use IsoPlayer* when ported
    // ... Add more as porting continues ...

    // Inner1: Synthetic switch map for ZombieSound (Java $1)
    class Inner1 {
    public:
        Inner1();
        ~Inner1();
        // TODO: Port fields and methods from Java GameClient$1
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
