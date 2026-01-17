#pragma once
#include <SDL2/SDL_net.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <unordered_map>

namespace zombie {
namespace network {

// Forward declarations
class Packet;
class NetworkClient;
class NetworkServer;

/**
 * PacketType - Defines all network packet types
 */
enum class PacketType : uint8_t {
    // Connection packets
    CONNECT_REQUEST = 0x01,
    CONNECT_RESPONSE = 0x02,
    DISCONNECT = 0x03,
    HEARTBEAT = 0x04,
    
    // Player sync packets
    PLAYER_JOIN = 0x10,
    PLAYER_LEAVE = 0x11,
    PLAYER_POSITION = 0x12,
    PLAYER_ACTION = 0x13,
    PLAYER_HEALTH = 0x14,
    PLAYER_INVENTORY = 0x15,
    
    // World sync packets
    WORLD_STATE = 0x20,
    CHUNK_DATA = 0x21,
    OBJECT_SPAWN = 0x22,
    OBJECT_DESTROY = 0x23,
    OBJECT_UPDATE = 0x24,
    
    // Zombie sync packets
    ZOMBIE_SPAWN = 0x30,
    ZOMBIE_DESTROY = 0x31,
    ZOMBIE_POSITION = 0x32,
    ZOMBIE_STATE = 0x33,
    
    // Chat packets
    CHAT_MESSAGE = 0x40,
    SERVER_MESSAGE = 0x41,
    
    // Game state packets
    TIME_SYNC = 0x50,
    WEATHER_SYNC = 0x51,
    
    // Custom/extension
    CUSTOM = 0xFF
};

/**
 * Packet - Network packet with serialization support
 */
class Packet {
public:
    Packet();
    Packet(PacketType type);
    ~Packet();
    
    // Packet info
    PacketType getType() const { return type; }
    void setType(PacketType t) { type = t; }
    
    uint32_t getSize() const { return static_cast<uint32_t>(data.size()); }
    const uint8_t* getData() const { return data.data(); }
    
    // Write operations
    void writeUint8(uint8_t value);
    void writeUint16(uint16_t value);
    void writeUint32(uint32_t value);
    void writeInt8(int8_t value);
    void writeInt16(int16_t value);
    void writeInt32(int32_t value);
    void writeFloat(float value);
    void writeString(const std::string& str);
    void writeBytes(const uint8_t* bytes, size_t length);
    
    // Read operations
    uint8_t readUint8();
    uint16_t readUint16();
    uint32_t readUint32();
    int8_t readInt8();
    int16_t readInt16();
    int32_t readInt32();
    float readFloat();
    std::string readString();
    void readBytes(uint8_t* buffer, size_t length);
    
    // Reset read position
    void resetRead() { readPos = 0; }
    bool hasMore() const { return readPos < data.size(); }
    
    // Serialize to/from buffer
    std::vector<uint8_t> serialize() const;
    static std::unique_ptr<Packet> deserialize(const uint8_t* buffer, size_t length);
    
private:
    PacketType type;
    std::vector<uint8_t> data;
    size_t readPos;
};

/**
 * NetworkPeer - Represents a connected peer (client or server)
 */
struct NetworkPeer {
    uint32_t id;
    IPaddress address;
    TCPsocket socket;
    uint32_t lastHeartbeat;
    bool connected;
    std::string playerName;
    
    NetworkPeer() : id(0), socket(nullptr), lastHeartbeat(0), connected(false) {}
};

/**
 * PacketHandler - Callback for handling received packets
 */
using PacketHandler = std::function<void(const Packet&, NetworkPeer*)>;

/**
 * NetworkManager - Base class for network functionality
 */
class NetworkManager {
public:
    NetworkManager();
    virtual ~NetworkManager();
    
    // Initialization
    virtual bool init();
    virtual void shutdown();
    
    // Update (call each frame)
    virtual void update(float deltaTime);
    
    // Packet handling
    void registerPacketHandler(PacketType type, PacketHandler handler);
    void unregisterPacketHandler(PacketType type);
    
    // Statistics
    uint32_t getBytesSent() const { return bytesSent; }
    uint32_t getBytesReceived() const { return bytesReceived; }
    uint32_t getPacketsSent() const { return packetsSent; }
    uint32_t getPacketsReceived() const { return packetsReceived; }
    
protected:
    bool initialized;
    uint32_t bytesSent;
    uint32_t bytesReceived;
    uint32_t packetsSent;
    uint32_t packetsReceived;
    
    std::unordered_map<PacketType, PacketHandler> packetHandlers;
    
    void handlePacket(const Packet& packet, NetworkPeer* peer);
    bool sendPacketToPeer(const Packet& packet, NetworkPeer* peer);
    std::unique_ptr<Packet> receivePacketFromPeer(NetworkPeer* peer);
};

/**
 * NetworkServer - Server implementation
 */
class NetworkServer : public NetworkManager {
public:
    NetworkServer();
    ~NetworkServer();
    
    // Server control
    bool start(uint16_t port, int maxClients = 32);
    void stop();
    
    bool isRunning() const { return running; }
    int getClientCount() const { return static_cast<int>(clients.size()); }
    
    // Update
    void update(float deltaTime) override;
    
    // Broadcasting
    void broadcastPacket(const Packet& packet, NetworkPeer* exclude = nullptr);
    void sendPacketToClient(const Packet& packet, uint32_t clientId);
    
    // Client management
    NetworkPeer* getClient(uint32_t clientId);
    const std::vector<std::unique_ptr<NetworkPeer>>& getClients() const { return clients; }
    
private:
    bool running;
    uint16_t port;
    int maxClients;
    TCPsocket serverSocket;
    SDLNet_SocketSet socketSet;
    std::vector<std::unique_ptr<NetworkPeer>> clients;
    uint32_t nextClientId;
    
    void acceptNewClients();
    void updateClients(float deltaTime);
    void disconnectClient(NetworkPeer* client);
    void sendHeartbeats();
    
    float heartbeatTimer;
    static constexpr float HEARTBEAT_INTERVAL = 5.0f;
    static constexpr float CLIENT_TIMEOUT = 15.0f;
};

/**
 * NetworkClient - Client implementation
 */
class NetworkClient : public NetworkManager {
public:
    NetworkClient();
    ~NetworkClient();
    
    // Connection
    bool connect(const std::string& hostname, uint16_t port, const std::string& playerName);
    void disconnect();
    
    bool isConnected() const { return connected; }
    uint32_t getClientId() const { return clientId; }
    const std::string& getPlayerName() const { return playerName; }
    
    // Update
    void update(float deltaTime) override;
    
    // Send to server
    void sendPacket(const Packet& packet);
    
private:
    bool connected;
    uint32_t clientId;
    std::string playerName;
    TCPsocket socket;
    IPaddress serverAddress;
    NetworkPeer serverPeer;
    
    void sendHeartbeat();
    void receivePackets();
    
    float heartbeatTimer;
    static constexpr float HEARTBEAT_INTERVAL = 5.0f;
};

/**
 * NetworkProtocol - Helper functions for common packet operations
 */
class NetworkProtocol {
public:
    // Player packets
    static std::unique_ptr<Packet> createPlayerPositionPacket(
        uint32_t playerId, float x, float y, float z, float rotation);
    
    static std::unique_ptr<Packet> createPlayerHealthPacket(
        uint32_t playerId, float health, float maxHealth);
    
    static std::unique_ptr<Packet> createPlayerJoinPacket(
        uint32_t playerId, const std::string& name);
    
    static std::unique_ptr<Packet> createPlayerLeavePacket(uint32_t playerId);
    
    // Zombie packets
    static std::unique_ptr<Packet> createZombieSpawnPacket(
        uint32_t zombieId, float x, float y, float z);
    
    static std::unique_ptr<Packet> createZombiePositionPacket(
        uint32_t zombieId, float x, float y, float z);
    
    static std::unique_ptr<Packet> createZombieDestroyPacket(uint32_t zombieId);
    
    // Chat packets
    static std::unique_ptr<Packet> createChatMessagePacket(
        uint32_t playerId, const std::string& message);
    
    // World packets
    static std::unique_ptr<Packet> createWorldStatePacket(
        uint32_t worldSeed, float worldTime);
    
    // Parsing helpers
    static void parsePlayerPosition(const Packet& packet,
        uint32_t& playerId, float& x, float& y, float& z, float& rotation);
    
    static void parsePlayerHealth(const Packet& packet,
        uint32_t& playerId, float& health, float& maxHealth);
    
    static void parseZombieSpawn(const Packet& packet,
        uint32_t& zombieId, float& x, float& y, float& z);
};

} // namespace network
} // namespace zombie
