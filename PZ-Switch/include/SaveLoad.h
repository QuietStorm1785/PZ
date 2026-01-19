#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <cstdint>

namespace zombie { namespace world { class TileMap; } }

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
 SaveFileWriter(std::string_view filename);
 ~SaveFileWriter();
 
 // Legacy flat writes (deprecated)
 bool writeGameData(const GameSaveData& data);
 bool writeWorldData(const WorldSaveData& data);
 bool flush();

 // SVI archive packing (header .svh + payload .dat)
 struct SVHeaderMeta {
 std::string title;
 std::string saveName;
 std::string profileId;
 uint32_t gameVersion;
 uint64_t timestamp;
 };

 static std::vector<uint8_t> makeSVHText(const SVHeaderMeta& meta);
 struct SVIArchiveEntry {
 std::string name; // e.g., "map_1_1.bin" or "server/server.ini"
 std::vector<uint8_t> bytes; // file content
 };

 static bool writeSVIArchive(std::string_view outFile,
 const SVHeaderMeta& meta,
 const std::vector<SVIArchiveEntry>& entries);
 
private:
 std::string filename;
 std::vector<uint8_t> buffer;
};

class SaveFileReader {
public:
 SaveFileReader(std::string_view filename);
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
 
 bool saveGame(std::string_view saveName, const GameSaveData& gameData, const WorldSaveData& worldData);
 bool saveGameSVI(std::string_view saveName, const GameSaveData& gameData, const WorldSaveData& worldData);
 bool loadGame(std::string_view saveName, GameSaveData& outGameData, WorldSaveData& outWorldData);
 bool loadGameSVI(std::string_view saveName, GameSaveData& outGameData, WorldSaveData& outWorldData);
 bool loadLatestGameSVI(GameSaveData& outGameData, WorldSaveData& outWorldData);
 std::string getLatestSVIPath() const;
 
 std::vector<std::string> listSaves() const;
 bool deleteSave(std::string_view saveName);
 
 std::string getSavePath() const;
 
 // TileMap serialization helpers
 static std::vector<uint8_t> serializeTileMap(const zombie::world::TileMap& map);
 static bool deserializeTileMap(const std::vector<uint8_t>& data, zombie::world::TileMap& map);
 
private:
 SaveGameManager() = default;
 ~SaveGameManager() = default;
 
 const std::string saveDirPath = "./saves/"; // dev default; platform can override
 std::string getPlatformSaveRoot() const;
 std::string getActiveProfileId() const;
};

} // namespace saveload
} // namespace zombie
