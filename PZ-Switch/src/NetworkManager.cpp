#include "NetworkManager.h"
#include <cstring>
#include <iostream>

namespace zombie {
namespace network {

// ============================================================================
// Packet Implementation
// ============================================================================

Packet::Packet() : type(PacketType::CUSTOM), readPos(0) {}

Packet::Packet(PacketType t) : type(t), readPos(0) {}

Packet::~Packet() {}

void Packet::writeUint8(uint8_t value) {
 data.push_back(value);
}

void Packet::writeUint16(uint16_t value) {
 data.push_back(static_cast<uint8_t>(value >> 8));
 data.push_back(static_cast<uint8_t>(value & 0xFF));
}

void Packet::writeUint32(uint32_t value) {
 data.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
 data.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
 data.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
 data.push_back(static_cast<uint8_t>(value & 0xFF));
}

void Packet::writeInt8(int8_t value) {
 writeUint8(static_cast<uint8_t>(value));
}

void Packet::writeInt16(int16_t value) {
 writeUint16(static_cast<uint16_t>(value));
}

void Packet::writeInt32(int32_t value) {
 writeUint32(static_cast<uint32_t>(value));
}

void Packet::writeFloat(float value) {
 uint32_t asInt;
 std::memcpy(&asInt, &value, sizeof(float));
 writeUint32(asInt);
}

void Packet::writeString(const std::string& str) {
 writeUint16(static_cast<uint16_t>(str.length()));
 for (char c : str) {
 writeUint8(static_cast<uint8_t>(c));
 }
}

void Packet::writeBytes(const uint8_t* bytes, size_t length) {
 for (size_t i = 0; i < length; i++) {
 data.push_back(bytes[i]);
 }
}

uint8_t Packet::readUint8() {
 if (readPos >= data.size()) return 0;
 return data[readPos++];
}

uint16_t Packet::readUint16() {
 uint16_t value = 0;
 value |= static_cast<uint16_t>(readUint8()) << 8;
 value |= static_cast<uint16_t>(readUint8());
 return value;
}

uint32_t Packet::readUint32() {
 uint32_t value = 0;
 value |= static_cast<uint32_t>(readUint8()) << 24;
 value |= static_cast<uint32_t>(readUint8()) << 16;
 value |= static_cast<uint32_t>(readUint8()) << 8;
 value |= static_cast<uint32_t>(readUint8());
 return value;
}

int8_t Packet::readInt8() {
 return static_cast<int8_t>(readUint8());
}

int16_t Packet::readInt16() {
 return static_cast<int16_t>(readUint16());
}

int32_t Packet::readInt32() {
 return static_cast<int32_t>(readUint32());
}

float Packet::readFloat() {
 uint32_t asInt = readUint32();
 float value;
 std::memcpy(&value, &asInt, sizeof(float));
 return value;
}

std::string Packet::readString() {
 uint16_t length = readUint16();
 std::string str;
 str.reserve(length);
 for (uint16_t i = 0; i < length && readPos < data.size(); i++) {
 str += static_cast<char>(readUint8());
 }
 return str;
}

void Packet::readBytes(uint8_t* buffer, size_t length) {
 for (size_t i = 0; i < length && readPos < data.size(); i++) {
 buffer[i] = readUint8();
 }
}

std::vector<uint8_t> Packet::serialize() const {
 std::vector<uint8_t> buffer;
 
 // Packet format: [type:1][size:4][data:N]
 buffer.push_back(static_cast<uint8_t>(type));
 
 uint32_t size = static_cast<uint32_t>(data.size());
 buffer.push_back(static_cast<uint8_t>((size >> 24) & 0xFF));
 buffer.push_back(static_cast<uint8_t>((size >> 16) & 0xFF));
 buffer.push_back(static_cast<uint8_t>((size >> 8) & 0xFF));
 buffer.push_back(static_cast<uint8_t>(size & 0xFF));
 
 buffer.insert(buffer.end(), data.begin(), data.end());
 
 return buffer;
}

std::unique_ptr<Packet> Packet::deserialize(const uint8_t* buffer, size_t length) {
 if (length < 5) return nullptr; // Need at least type + size
 
 auto packet = std::make_unique<Packet>();
 
 packet->type = static_cast<PacketType>(buffer[0]);
 
 uint32_t size = 0;
 size |= static_cast<uint32_t>(buffer[1]) << 24;
 size |= static_cast<uint32_t>(buffer[2]) << 16;
 size |= static_cast<uint32_t>(buffer[3]) << 8;
 size |= static_cast<uint32_t>(buffer[4]);
 
 if (length < 5 + size) return nullptr; // Incomplete packet
 
 packet->data.assign(buffer + 5, buffer + 5 + size);
 packet->readPos = 0;
 
 return packet;
}

// ============================================================================
// NetworkManager Implementation
// ============================================================================

NetworkManager::NetworkManager()
 : initialized(false)
 , bytesSent(0)
 , bytesReceived(0)
 , packetsSent(0)
 , packetsReceived(0) {
}

NetworkManager::~NetworkManager() {
 if (initialized) {
 shutdown();
 }
}

bool NetworkManager::init() {
 if (SDLNet_Init() < 0) {
 std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
 return false;
 }
 
 initialized = true;
 return true;
}

void NetworkManager::shutdown() {
 if (initialized) {
 packetHandlers.clear();
 SDLNet_Quit();
 initialized = false;
 }
}

void NetworkManager::update(float deltaTime) {
 // Override in derived classes
}

void NetworkManager::registerPacketHandler(PacketType type, PacketHandler handler) {
 packetHandlers[type] = handler;
}

void NetworkManager::unregisterPacketHandler(PacketType type) {
 packetHandlers.erase(type);
}

void NetworkManager::handlePacket(const Packet& packet, NetworkPeer* peer) {
 auto it = packetHandlers.find(packet.getType());
 if (it != packetHandlers.end()) {
 it->second(packet, peer);
 }
}

bool NetworkManager::sendPacketToPeer(const Packet& packet, NetworkPeer* peer) {
 if (!peer || !peer->socket || !peer->connected) return false;
 
 auto buffer = packet.serialize();
 int result = SDLNet_TCP_Send(peer->socket, buffer.data(), static_cast<int>(buffer.size()));
 
 if (result < static_cast<int>(buffer.size())) {
 std::cerr << "SDLNet_TCP_Send failed: " << SDLNet_GetError() << std::endl;
 peer->connected = false;
 return false;
 }
 
 bytesSent += buffer.size();
 packetsSent++;
 return true;
}

std::unique_ptr<Packet> NetworkManager::receivePacketFromPeer(NetworkPeer* peer) {
 if (!peer || !peer->socket || !peer->connected) return nullptr;
 
 // Read header (type + size = 5 bytes)
 uint8_t header[5];
 int result = SDLNet_TCP_Recv(peer->socket, header, 5);
 
 if (result <= 0) {
 if (result < 0) {
 peer->connected = false;
 }
 return nullptr;
 }
 
 if (result < 5) return nullptr; // Incomplete header
 
 uint32_t dataSize = 0;
 dataSize |= static_cast<uint32_t>(header[1]) << 24;
 dataSize |= static_cast<uint32_t>(header[2]) << 16;
 dataSize |= static_cast<uint32_t>(header[3]) << 8;
 dataSize |= static_cast<uint32_t>(header[4]);
 
 if (dataSize > 1024 * 1024) { // 1MB max packet size
 std::cerr << "Packet too large: " << dataSize << " bytes" << std::endl;
 peer->connected = false;
 return nullptr;
 }
 
 // Read data
 std::vector<uint8_t> buffer(5 + dataSize);
 std::memcpy(buffer.data(), header, 5);
 
 if (dataSize > 0) {
 result = SDLNet_TCP_Recv(peer->socket, buffer.data() + 5, dataSize);
 if (result < static_cast<int>(dataSize)) {
 peer->connected = false;
 return nullptr;
 }
 }
 
 bytesReceived += buffer.size();
 packetsReceived++;
 
 return Packet::deserialize(buffer.data(), buffer.size());
}

// ============================================================================
// NetworkServer Implementation
// ============================================================================

NetworkServer::NetworkServer()
 : NetworkManager()
 , running(false)
 , port(0)
 , maxClients(32)
 , serverSocket(nullptr)
 , socketSet(nullptr)
 , nextClientId(1)
 , heartbeatTimer(0.0f) {
}

NetworkServer::~NetworkServer() {
 if (running) {
 stop();
 }
}

bool NetworkServer::start(uint16_t serverPort, int max) {
 if (running) return false;
 if (!initialized && !init()) return false;
 
 port = serverPort;
 maxClients = max;
 
 // Create server socket
 IPaddress ip;
 if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
 std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
 return false;
 }
 
 serverSocket = SDLNet_TCP_Open(&ip);
 if (!serverSocket) {
 std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
 return false;
 }
 
 // Create socket set
 socketSet = SDLNet_AllocSocketSet(maxClients + 1);
 if (!socketSet) {
 std::cerr << "SDLNet_AllocSocketSet failed: " << SDLNet_GetError() << std::endl;
 SDLNet_TCP_Close(serverSocket);
 return false;
 }
 
 SDLNet_TCP_AddSocket(socketSet, serverSocket);
 
 running = true;
 std::cout << "Server started on port " << port << std::endl;
 return true;
}

void NetworkServer::stop() {
 if (!running) return;
 
 // Disconnect all clients
 for (auto& client : clients) {
 if (client->connected) {
 Packet disconnectPacket(PacketType::DISCONNECT);
 sendPacketToPeer(disconnectPacket, client.get());
 SDLNet_TCP_Close(client->socket);
 }
 }
 clients.clear();
 
 // Clean up server socket
 if (socketSet) {
 SDLNet_FreeSocketSet(socketSet);
 socketSet = nullptr;
 }
 
 if (serverSocket) {
 SDLNet_TCP_Close(serverSocket);
 serverSocket = nullptr;
 }
 
 running = false;
 std::cout << "Server stopped" << std::endl;
}

void NetworkServer::update(float deltaTime) {
 if (!running) return;
 
 acceptNewClients();
 updateClients(deltaTime);
 
 // Send heartbeats
 heartbeatTimer += deltaTime;
 if (heartbeatTimer >= HEARTBEAT_INTERVAL) {
 sendHeartbeats();
 heartbeatTimer = 0.0f;
 }
}

void NetworkServer::acceptNewClients() {
 // Check for new connections
 int activity = SDLNet_CheckSockets(socketSet, 0);
 if (activity <= 0) return;
 
 if (SDLNet_SocketReady(serverSocket)) {
 TCPsocket newSocket = SDLNet_TCP_Accept(serverSocket);
 if (newSocket) {
 if (static_cast<int>(clients.size()) < maxClients) {
 auto client = std::make_unique<NetworkPeer>();
 client->id = nextClientId++;
 client->socket = newSocket;
 client->connected = true;
 client->lastHeartbeat = SDL_GetTicks();
 client->address = *SDLNet_TCP_GetPeerAddress(newSocket);
 
 SDLNet_TCP_AddSocket(socketSet, newSocket);
 
 std::cout << "Client " << client->id << " connected" << std::endl;
 
 // Send connection response
 Packet response(PacketType::CONNECT_RESPONSE);
 response.writeUint32(client->id);
 sendPacketToPeer(response, client.get());
 
 clients.push_back(std::move(client));
 } else {
 std::cout << "Server full, rejecting connection" << std::endl;
 SDLNet_TCP_Close(newSocket);
 }
 }
 }
}

void NetworkServer::updateClients(float deltaTime) {
 uint32_t currentTime = SDL_GetTicks();
 
 for (auto it = clients.begin(); it != clients.end();) {
 auto& client = *it;
 
 // Check timeout
 if (currentTime - client->lastHeartbeat > CLIENT_TIMEOUT * 1000) {
 std::cout << "Client " << client->id << " timed out" << std::endl;
 disconnectClient(client.get());
 it = clients.erase(it);
 continue;
 }
 
 // Receive packets
 if (SDLNet_SocketReady(client->socket)) {
 auto packet = receivePacketFromPeer(client.get());
 if (packet) {
 client->lastHeartbeat = currentTime;
 
 // Handle heartbeat
 if (packet->getType() == PacketType::HEARTBEAT) {
 // Just update last heartbeat time
 } else {
 handlePacket(*packet, client.get());
 }
 } else if (!client->connected) {
 // Disconnected
 std::cout << "Client " << client->id << " disconnected" << std::endl;
 disconnectClient(client.get());
 it = clients.erase(it);
 continue;
 }
 }
 
 ++it;
 }
}

void NetworkServer::disconnectClient(NetworkPeer* client) {
 if (client->socket) {
 SDLNet_TCP_DelSocket(socketSet, client->socket);
 SDLNet_TCP_Close(client->socket);
 client->socket = nullptr;
 }
 client->connected = false;
}

void NetworkServer::sendHeartbeats() {
 Packet heartbeat(PacketType::HEARTBEAT);
 for (auto& client : clients) {
 if (client->connected) {
 sendPacketToPeer(heartbeat, client.get());
 }
 }
}

void NetworkServer::broadcastPacket(const Packet& packet, NetworkPeer* exclude) {
 for (auto& client : clients) {
 if (client->connected && client.get() != exclude) {
 sendPacketToPeer(packet, client.get());
 }
 }
}

void NetworkServer::sendPacketToClient(const Packet& packet, uint32_t clientId) {
 for (auto& client : clients) {
 if (client->id == clientId && client->connected) {
 sendPacketToPeer(packet, client.get());
 break;
 }
 }
}

NetworkPeer* NetworkServer::getClient(uint32_t clientId) {
 for (auto& client : clients) {
 if (client->id == clientId) {
 return client.get();
 }
 }
 return nullptr;
}

// ============================================================================
// NetworkClient Implementation
// ============================================================================

NetworkClient::NetworkClient()
 : NetworkManager()
 , connected(false)
 , clientId(0)
 , socket(nullptr)
 , heartbeatTimer(0.0f) {
}

NetworkClient::~NetworkClient() {
 if (connected) {
 disconnect();
 }
}

bool NetworkClient::connect(const std::string& hostname, uint16_t port, const std::string& name) {
 if (connected) return false;
 if (!initialized && !init()) return false;
 
 playerName = name;
 
 // Resolve host
 if (SDLNet_ResolveHost(&serverAddress, hostname.c_str(), port) < 0) {
 std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
 return false;
 }
 
 // Connect to server
 socket = SDLNet_TCP_Open(&serverAddress);
 if (!socket) {
 std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
 return false;
 }
 
 serverPeer.socket = socket;
 serverPeer.address = serverAddress;
 serverPeer.connected = true;
 
 // Send connect request
 Packet connectPacket(PacketType::CONNECT_REQUEST);
 connectPacket.writeString(playerName);
 sendPacketToPeer(connectPacket, &serverPeer);
 
 // Wait for response (with timeout)
 SDL_Delay(100);
 auto response = receivePacketFromPeer(&serverPeer);
 if (response && response->getType() == PacketType::CONNECT_RESPONSE) {
 clientId = response->readUint32();
 connected = true;
 std::cout << "Connected to server as client " << clientId << std::endl;
 return true;
 }
 
 SDLNet_TCP_Close(socket);
 socket = nullptr;
 return false;
}

void NetworkClient::disconnect() {
 if (!connected) return;
 
 // Send disconnect packet
 Packet disconnectPacket(PacketType::DISCONNECT);
 sendPacketToPeer(disconnectPacket, &serverPeer);
 
 if (socket) {
 SDLNet_TCP_Close(socket);
 socket = nullptr;
 }
 
 connected = false;
 std::cout << "Disconnected from server" << std::endl;
}

void NetworkClient::update(float deltaTime) {
 if (!connected) return;
 
 receivePackets();
 
 // Send heartbeat
 heartbeatTimer += deltaTime;
 if (heartbeatTimer >= HEARTBEAT_INTERVAL) {
 sendHeartbeat();
 heartbeatTimer = 0.0f;
 }
}

void NetworkClient::sendHeartbeat() {
 Packet heartbeat(PacketType::HEARTBEAT);
 sendPacketToPeer(heartbeat, &serverPeer);
}

void NetworkClient::receivePackets() {
 // Non-blocking receive
 SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);
 if (!set) return;
 
 SDLNet_TCP_AddSocket(set, socket);
 int activity = SDLNet_CheckSockets(set, 0);
 
 if (activity > 0 && SDLNet_SocketReady(socket)) {
 auto packet = receivePacketFromPeer(&serverPeer);
 if (packet) {
 if (packet->getType() != PacketType::HEARTBEAT) {
 handlePacket(*packet, &serverPeer);
 }
 } else if (!serverPeer.connected) {
 connected = false;
 std::cout << "Lost connection to server" << std::endl;
 }
 }
 
 SDLNet_FreeSocketSet(set);
}

void NetworkClient::sendPacket(const Packet& packet) {
 sendPacketToPeer(packet, &serverPeer);
}

// ============================================================================
// NetworkProtocol Implementation
// ============================================================================

std::unique_ptr<Packet> NetworkProtocol::createPlayerPositionPacket(
 uint32_t playerId, float x, float y, float z, float rotation) {
 auto packet = std::make_unique<Packet>(PacketType::PLAYER_POSITION);
 packet->writeUint32(playerId);
 packet->writeFloat(x);
 packet->writeFloat(y);
 packet->writeFloat(z);
 packet->writeFloat(rotation);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createPlayerHealthPacket(
 uint32_t playerId, float health, float maxHealth) {
 auto packet = std::make_unique<Packet>(PacketType::PLAYER_HEALTH);
 packet->writeUint32(playerId);
 packet->writeFloat(health);
 packet->writeFloat(maxHealth);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createPlayerJoinPacket(
 uint32_t playerId, const std::string& name) {
 auto packet = std::make_unique<Packet>(PacketType::PLAYER_JOIN);
 packet->writeUint32(playerId);
 packet->writeString(name);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createPlayerLeavePacket(uint32_t playerId) {
 auto packet = std::make_unique<Packet>(PacketType::PLAYER_LEAVE);
 packet->writeUint32(playerId);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createZombieSpawnPacket(
 uint32_t zombieId, float x, float y, float z) {
 auto packet = std::make_unique<Packet>(PacketType::ZOMBIE_SPAWN);
 packet->writeUint32(zombieId);
 packet->writeFloat(x);
 packet->writeFloat(y);
 packet->writeFloat(z);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createZombiePositionPacket(
 uint32_t zombieId, float x, float y, float z) {
 auto packet = std::make_unique<Packet>(PacketType::ZOMBIE_POSITION);
 packet->writeUint32(zombieId);
 packet->writeFloat(x);
 packet->writeFloat(y);
 packet->writeFloat(z);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createZombieDestroyPacket(uint32_t zombieId) {
 auto packet = std::make_unique<Packet>(PacketType::ZOMBIE_DESTROY);
 packet->writeUint32(zombieId);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createChatMessagePacket(
 uint32_t playerId, const std::string& message) {
 auto packet = std::make_unique<Packet>(PacketType::CHAT_MESSAGE);
 packet->writeUint32(playerId);
 packet->writeString(message);
 return packet;
}

std::unique_ptr<Packet> NetworkProtocol::createWorldStatePacket(
 uint32_t worldSeed, float worldTime) {
 auto packet = std::make_unique<Packet>(PacketType::WORLD_STATE);
 packet->writeUint32(worldSeed);
 packet->writeFloat(worldTime);
 return packet;
}

void NetworkProtocol::parsePlayerPosition(const Packet& packet,
 uint32_t& playerId, float& x, float& y, float& z, float& rotation) {
 Packet& p = const_cast<Packet&>(packet);
 p.resetRead();
 playerId = p.readUint32();
 x = p.readFloat();
 y = p.readFloat();
 z = p.readFloat();
 rotation = p.readFloat();
}

void NetworkProtocol::parsePlayerHealth(const Packet& packet,
 uint32_t& playerId, float& health, float& maxHealth) {
 Packet& p = const_cast<Packet&>(packet);
 p.resetRead();
 playerId = p.readUint32();
 health = p.readFloat();
 maxHealth = p.readFloat();
}

void NetworkProtocol::parseZombieSpawn(const Packet& packet,
 uint32_t& zombieId, float& x, float& y, float& z) {
 Packet& p = const_cast<Packet&>(packet);
 p.resetRead();
 zombieId = p.readUint32();
 x = p.readFloat();
 y = p.readFloat();
 z = p.readFloat();
}

} // namespace network
} // namespace zombie
