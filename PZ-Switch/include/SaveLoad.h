#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace zombie {
namespace saveload {

struct Vec3 {
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

struct GameSaveData {
    int gameVersion;
    uint64_t timestamp;
    std::string playerName;
    Vec3 playerPosition;
    float playerHealth;
    int playedMinutes;
};

struct WorldSaveData {
    std::vector<uint8_t> cellData;
    std::vector<uint8_t> zombieData;
    std::vector<uint8_t> itemData;
    std::vector<uint8_t> buildingData;
};

class SaveFileWriter {
public:
    SaveFileWriter(const std::string& filename);
    ~SaveFileWriter();
    
    bool writeGameData(const GameSaveData& data);
    bool writeWorldData(const WorldSaveData& data);
    bool flush();
    
private:
    std::string filename;
    std::vector<uint8_t> buffer;
};

class SaveFileReader {
public:
    SaveFileReader(const std::string& filename);
    ~SaveFileReader();
    
    bool readGameData(GameSaveData& outData);
    bool readWorldData(WorldSaveData& outData);
    
private:
    std::string filename;
    std::vector<uint8_t> buffer;
    size_t readPos;
};

class SaveGameManager {
public:
    static SaveGameManager& getInstance() {
        static SaveGameManager instance;
        return instance;
    }
    
    bool saveGame(const std::string& saveName, const GameSaveData& gameData, const WorldSaveData& worldData);
    bool loadGame(const std::string& saveName, GameSaveData& outGameData, WorldSaveData& outWorldData);
    
    std::vector<std::string> listSaves() const;
    bool deleteSave(const std::string& saveName);
    
    std::string getSavePath() const;
    
private:
    SaveGameManager() = default;
    ~SaveGameManager() = default;
    
    const std::string saveDirPath = "./saves/";
};

} // namespace saveload
} // namespace zombie
