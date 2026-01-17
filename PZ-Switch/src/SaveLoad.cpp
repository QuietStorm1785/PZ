#include "SaveLoad.h"
#include <fstream>
#include <filesystem>
#include <ctime>

namespace zombie {
namespace saveload {

SaveFileWriter::SaveFileWriter(const std::string& filename)
    : filename(filename) {
}

SaveFileWriter::~SaveFileWriter() {
}

bool SaveFileWriter::writeGameData(const GameSaveData& data) {
    buffer.clear();
    
    // Serialize game data (simplified)
    uint32_t version = data.gameVersion;
    buffer.insert(buffer.end(), (uint8_t*)&version, (uint8_t*)&version + sizeof(uint32_t));
    
    uint64_t timestamp = data.timestamp;
    buffer.insert(buffer.end(), (uint8_t*)&timestamp, (uint8_t*)&timestamp + sizeof(uint64_t));
    
    return true;
}

bool SaveFileWriter::writeWorldData(const WorldSaveData& data) {
    buffer.insert(buffer.end(), data.cellData.begin(), data.cellData.end());
    return true;
}

bool SaveFileWriter::flush() {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    file.write((char*)buffer.data(), buffer.size());
    file.close();
    return true;
}

SaveFileReader::SaveFileReader(const std::string& filename)
    : filename(filename), readPos(0) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        buffer.resize(size);
        file.seekg(0);
        file.read((char*)buffer.data(), size);
        file.close();
    }
}

SaveFileReader::~SaveFileReader() {
}

bool SaveFileReader::readGameData(GameSaveData& outData) {
    if (buffer.size() < sizeof(uint32_t) + sizeof(uint64_t)) return false;
    
    outData.gameVersion = *(uint32_t*)buffer.data();
    outData.timestamp = *(uint64_t*)(buffer.data() + sizeof(uint32_t));
    
    return true;
}

bool SaveFileReader::readWorldData(WorldSaveData& outData) {
    outData.cellData = buffer;
    return true;
}

bool SaveGameManager::saveGame(const std::string& saveName, const GameSaveData& gameData, const WorldSaveData& worldData) {
    std::filesystem::create_directories(saveDirPath);
    
    std::string filename = saveDirPath + saveName + ".sav";
    SaveFileWriter writer(filename);
    
    if (!writer.writeGameData(gameData)) return false;
    if (!writer.writeWorldData(worldData)) return false;
    
    return writer.flush();
}

bool SaveGameManager::loadGame(const std::string& saveName, GameSaveData& outGameData, WorldSaveData& outWorldData) {
    std::string filename = saveDirPath + saveName + ".sav";
    SaveFileReader reader(filename);
    
    if (!reader.readGameData(outGameData)) return false;
    if (!reader.readWorldData(outWorldData)) return false;
    
    return true;
}

std::vector<std::string> SaveGameManager::listSaves() const {
    std::vector<std::string> saves;
    if (std::filesystem::exists(saveDirPath)) {
        for (const auto& entry : std::filesystem::directory_iterator(saveDirPath)) {
            if (entry.path().extension() == ".sav") {
                saves.push_back(entry.path().stem().string());
            }
        }
    }
    return saves;
}

bool SaveGameManager::deleteSave(const std::string& saveName) {
    std::string filename = saveDirPath + saveName + ".sav";
    return std::filesystem::remove(filename) > 0;
}

std::string SaveGameManager::getSavePath() const {
    return saveDirPath;
}

} // namespace saveload
} // namespace zombie
