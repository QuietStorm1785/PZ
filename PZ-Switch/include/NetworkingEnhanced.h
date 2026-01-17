#pragma once
#include "NetworkManager.h"
#include <unordered_map>
#include <queue>

namespace zombie {
namespace networking {

enum class WorldEventType {
    ENTITY_SPAWNED,
    ENTITY_DESPAWNED,
    ENTITY_DIED,
    ITEM_DROPPED,
    ITEM_PICKED_UP,
    STRUCTURE_BUILT,
    STRUCTURE_DESTROYED,
    WEATHER_CHANGED,
    TIME_CHANGED,
    ZOMBIE_HORDE,
    PLAYER_JOINED,
    PLAYER_LEFT
};

struct WorldEvent {
    WorldEventType eventType;
    float timestamp;
    std::string data;
};

class WorldStateManager {
public:
    static WorldStateManager& getInstance() {
        static WorldStateManager instance;
        return instance;
    }
    
    void broadcastWorldEvent(WorldEventType eventType, const std::string& data);
    void queueWorldEvent(const WorldEvent& event);
    
    const std::queue<WorldEvent>& getPendingEvents() const { return eventQueue; }
    WorldEvent popEvent();
    
    int getPendingEventCount() const { return eventQueue.size(); }
    
private:
    WorldStateManager() = default;
    ~WorldStateManager() = default;
    
    std::queue<WorldEvent> eventQueue;
};

class ReplicationManager {
public:
    static ReplicationManager& getInstance() {
        static ReplicationManager instance;
        return instance;
    }
    
    void replicateEntityState(int entityId, const std::string& stateData);
    void replicateWorldChunk(int chunkX, int chunkY, const std::string& chunkData);
    
    void requestEntityState(int entityId);
    void requestWorldChunk(int chunkX, int chunkY);
    
private:
    ReplicationManager() = default;
    ~ReplicationManager() = default;
    
    std::unordered_map<int, std::string> entityStates;
    std::unordered_map<int, std::string> chunkStates;
};

class LobbyManager {
public:
    static LobbyManager& getInstance() {
        static LobbyManager instance;
        return instance;
    }
    
    void createLobby(const std::string& lobbyName, int maxPlayers);
    void joinLobby(const std::string& lobbyId);
    void leaveLobby();
    
    const std::string& getCurrentLobbyId() const { return currentLobbyId; }
    int getPlayerCount() const { return playerCount; }
    
private:
    LobbyManager() = default;
    ~LobbyManager() = default;
    
    std::string currentLobbyId;
    int playerCount;
    int maxPlayers;
};

} // namespace networking
} // namespace zombie
