

#pragma once
#include <string>
#include <unordered_map>
#include <vector>

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: GameServer and all inner classes


class GameServer {
public:
    // --- Static fields (from Java) ---
    static const int MAX_PLAYERS = 512;
    static const int TimeLimitForProcessPackets = 70;
    static const int PacketsUpdateRate = 200;
    static const int FPS = 10;
    // Collections and maps (use void* or comments for now)
    static void* ccFilters; // std::unordered_map<std::string, CCFilter> // TODO: implement/port type
    static int test;
    static int DEFAULT_PORT;
    static int UDPPort;
    static int UDPPortCommandline;
    static std::string IPCommandline;
    static int PortCommandline;
    static bool SteamVACCommandline;
    static bool GUICommandline;
    static bool bServer;
    static bool bCoop;
    static bool bDebug;
    static bool bSoftReset;
    static void* udpEngine; // UdpEngine* // TODO: implement/port type
    static void* IDToAddressMap; // std::unordered_map<int16_t, int64_t> // TODO: implement/port type
    static void* IDToPlayerMap; // std::unordered_map<int16_t, IsoPlayer> // TODO: implement/port type
    static void* Players; // std::vector<IsoPlayer> // TODO: implement/port type
    static float timeSinceKeepAlive;
    static int MaxTicksSinceKeepAliveBeforeStall;
    static void* DebugPlayer; // std::unordered_set<UdpConnection> // TODO: implement/port type
    static int ResetID;
    static void* ServerMods; // std::vector<std::string> // TODO: implement/port type
    static void* WorkshopItems; // std::vector<int64_t> // TODO: implement/port type
    static void* WorkshopInstallFolders; // std::vector<std::string> // TODO: implement/port type
    static void* WorkshopTimeStamps; // std::vector<long> // TODO: implement/port type
    static std::string ServerName;
    static void* discordBot; // DiscordBot* // TODO: implement/port type
    static std::string checksum;
    static std::string GameMap;
    static bool bFastForward;
    static void* transactionIDMap; // std::unordered_map<std::string, int> // TODO: implement/port type
    static void* worldObjectsServerSyncReq; // ObjectsSyncRequests* // TODO: implement/port type
    static std::string ip;
    static int count;
    static void* SlotToConnection; // UdpConnection*[512] // TODO: implement/port type
    static void* PlayerToAddressMap; // std::unordered_map<IsoPlayer, int64_t> // TODO: implement/port type
    static void* alreadyRemoved; // std::vector<int> // TODO: implement/port type
    static bool bDone;
    static bool launched;
    static void* consoleCommands; // std::vector<std::string> // TODO: implement/port type
    static void* MainLoopPlayerUpdate; // std::unordered_map<int64_t, IZomboidPacket> // TODO: implement/port type
    static void* MainLoopPlayerUpdateQ; // ConcurrentLinkedQueue<IZomboidPacket> // TODO: implement/port type
    static void* MainLoopNetDataHighPriorityQ; // ConcurrentLinkedQueue<IZomboidPacket> // TODO: implement/port type
    static void* MainLoopNetDataQ; // ConcurrentLinkedQueue<IZomboidPacket> // TODO: implement/port type
    static void* MainLoopNetData2; // std::vector<IZomboidPacket> // TODO: implement/port type
    static void* playerToCoordsMap; // std::unordered_map<int16_t, Vector2> // TODO: implement/port type
    static void* playerMovedToFastMap; // std::unordered_map<int16_t, int> // TODO: implement/port type
    static void* large_file_bb; // ByteBuffer* // TODO: implement/port type
    static long previousSave;
    static std::string poisonousBerry;
    static std::string poisonousMushroom;
    static std::string difficulty;
    static int droppedPackets;
    static int countOfDroppedPackets;
    static int countOfDroppedConnections;
    static void* removeZombiesConnection; // UdpConnection* // TODO: implement/port type
    static void* calcCountPlayersInRelevantPositionLimiter; // UpdateLimit* // TODO: implement/port type
    static void* sendWorldMapPlayerPositionLimiter; // UpdateLimit* // TODO: implement/port type
    static void* loginQueue; // LoginQueue* // TODO: implement/port type
    static int mainCycleExceptionLogCount;
    static void* MainThread; // Thread* // TODO: implement/port type
    static void* tempPlayers; // std::vector<IsoPlayer> // TODO: implement/port type
    // ... add more static fields as needed ...

    GameServer();
    ~GameServer();

    // --- Inner classes ---
    class CCFilter {
    public:
        std::string command;
        bool allow = false;
        CCFilter* next = nullptr;

        CCFilter() = default;
        CCFilter(const std::string& cmd, bool allowVal, CCFilter* nextPtr = nullptr)
            : command(cmd), allow(allowVal), next(nextPtr) {}
        ~CCFilter() = default;

        bool matches(const std::string& var1) const {
            return command == var1 || command == "*";
        }

        bool passes(const std::string& var1) const {
            if (matches(var1)) {
                return allow;
            } else {
                return next == nullptr ? true : next->passes(var1);
            }
        }
    };

    class DelayedConnection {
    public:
        // Ported fields from Java
        void* connection; // Placeholder for UdpConnection*
        bool connect;
        std::string hostString;

        DelayedConnection(void* conn, bool connectFlag)
            : connection(conn), connect(connectFlag) {
            if (connect) {
                // hostString should be set from conn if available
                // (left as a placeholder)
                hostString = "";
            }
        }
        bool isConnect() const { return connect; }
        bool isDisconnect() const { return !connect; }
    };

    class s_performance {
    public:
        // Static probe placeholders
        static inline const char* frameStep = "GameServer.frameStep";
        static inline const char* mainLoopDealWithNetData = "GameServer.mainLoopDealWithNetData";
        static inline const char* RCONServerUpdate = "RCONServer.update";
        s_performance() = default;
        ~s_performance() = default;
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
