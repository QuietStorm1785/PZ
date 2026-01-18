#include "SaveLoad.h"
#include <fstream>
#include <filesystem>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "Config.h"
#include "TileMap.h"

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

std::vector<uint8_t> SaveFileWriter::makeSVHText(const SVHeaderMeta& meta) {
    std::ostringstream oss;
    oss << "SVI-HEADER\n";
    oss << "Title=" << meta.title << "\n";
    oss << "SaveName=" << meta.saveName << "\n";
    oss << "ProfileId=" << meta.profileId << "\n";
    oss << "GameVersion=" << meta.gameVersion << "\n";
    oss << "Timestamp=" << meta.timestamp << "\n";
    const std::string txt = oss.str();
    return std::vector<uint8_t>(txt.begin(), txt.end());
}

// Simple custom archive format:
// [MAGIC 'SVI1'] [uint32 entryCount]
// For each entry: [uint32 nameLen][bytes name][uint64 dataLen][bytes data]
static void writeU32(std::vector<uint8_t>& out, uint32_t v) {
    for (int i = 0; i < 4; ++i) out.push_back(static_cast<uint8_t>((v >> (i * 8)) & 0xFF));
}
static void writeU64(std::vector<uint8_t>& out, uint64_t v) {
    for (int i = 0; i < 8; ++i) out.push_back(static_cast<uint8_t>((v >> (i * 8)) & 0xFF));
}

bool SaveFileWriter::writeSVIArchive(const std::string& outFile,
                                     const SVHeaderMeta& meta,
                                     const std::vector<SVIArchiveEntry>& entries) {
    std::vector<uint8_t> out;
    // Magic
    out.push_back('S'); out.push_back('V'); out.push_back('I'); out.push_back('1');
    // entries + header.svh
    writeU32(out, static_cast<uint32_t>(entries.size() + 1));

    // Entry 1: header.svh
    const std::string name1 = "header.svh";
    writeU32(out, static_cast<uint32_t>(name1.size()));
    out.insert(out.end(), name1.begin(), name1.end());
    const auto headerBytes = makeSVHText(meta);
    writeU64(out, static_cast<uint64_t>(headerBytes.size()));
    out.insert(out.end(), headerBytes.begin(), headerBytes.end());

    // Additional entries
    for (const auto& e : entries) {
        writeU32(out, static_cast<uint32_t>(e.name.size()));
        out.insert(out.end(), e.name.begin(), e.name.end());
        writeU64(out, static_cast<uint64_t>(e.bytes.size()));
        out.insert(out.end(), e.bytes.begin(), e.bytes.end());
    }

    std::ofstream file(outFile, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) return false;
    file.write(reinterpret_cast<const char*>(out.data()), static_cast<std::streamsize>(out.size()));
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
    std::string root = getPlatformSaveRoot();
    std::filesystem::create_directories(root);
    std::string filename = root + saveName + ".sav";
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

// Parse SVI archive bytes into game/world data
static bool parseSVIArchiveBytes(const std::vector<uint8_t>& bytes,
                                 GameSaveData& outGameData,
                                 WorldSaveData& outWorldData) {
    auto readU32 = [&](size_t& pos) -> uint32_t {
        uint32_t v = 0; for (int i=0;i<4;++i) v |= static_cast<uint32_t>(bytes[pos++]) << (i*8); return v; };
    auto readU64 = [&](size_t& pos) -> uint64_t {
        uint64_t v = 0; for (int i=0;i<8;++i) v |= static_cast<uint64_t>(bytes[pos++]) << (i*8); return v; };

    size_t pos = 0;
    if (bytes.size() < 4) return false;
    if (!(bytes[0]=='S' && bytes[1]=='V' && bytes[2]=='I' && bytes[3]=='1')) return false;
    pos = 4;
    const uint32_t count = readU32(pos);
    std::vector<uint8_t> payload;
    std::vector<std::string> playerDbTexts;
    std::vector<std::vector<uint8_t>> mapParts;

    for (uint32_t i = 0; i < count && pos < bytes.size(); ++i) {
        const uint32_t nameLen = readU32(pos);
        if (pos + nameLen > bytes.size()) return false;
        std::string name(reinterpret_cast<const char*>(bytes.data() + pos), nameLen);
        pos += nameLen;
        const uint64_t dataLen = readU64(pos);
        if (pos + dataLen > bytes.size()) return false;
        if (name == std::string("save.dat")) {
            payload.assign(bytes.begin() + pos, bytes.begin() + pos + static_cast<size_t>(dataLen));
        } else if (name.rfind("player_", 0) == 0) {
            std::string txt(reinterpret_cast<const char*>(bytes.data() + pos), static_cast<size_t>(dataLen));
            playerDbTexts.push_back(std::move(txt));
        } else if (name.rfind("map_", 0) == 0) {
            mapParts.emplace_back(bytes.begin() + pos, bytes.begin() + pos + static_cast<size_t>(dataLen));
        }
        pos += static_cast<size_t>(dataLen);
    }

    if (payload.empty()) return false;

    size_t p = 0;
    auto readF32 = [&](float& out){ if (p+4>payload.size()) return false; std::memcpy(&out, payload.data()+p, 4); p+=4; return true; };
    auto readPU32 = [&](){ uint32_t v=0; for(int i=0;i<4;++i) v |= static_cast<uint32_t>(payload[p++]) << (i*8); return v; };
    auto readPU64 = [&](){ uint64_t v=0; for(int i=0;i<8;++i) v |= static_cast<uint64_t>(payload[p++]) << (i*8); return v; };

    outGameData.gameVersion = static_cast<int>(readPU32());
    outGameData.timestamp = readPU64();
    float x=0,y=0,z=0,h=0; readF32(x); readF32(y); readF32(z); readF32(h);
    outGameData.playerPosition = {x,y,z};
    outGameData.playerHealth = h;
    outGameData.playedMinutes = static_cast<int>(readPU32());

    if (p < payload.size()) {
        outWorldData.cellData.assign(payload.begin()+p, payload.end());
    } else {
        outWorldData.cellData.clear();
    }

    for (const auto& txt : playerDbTexts) {
        std::istringstream ss(txt);
        std::string line;
        while (std::getline(ss, line)) {
            if (line.empty() || line[0] == '[') continue;
            auto eq = line.find('=');
            if (eq == std::string::npos) continue;
            auto key = line.substr(0, eq);
            auto val = line.substr(eq + 1);
            if (key == "Name" || key == "playerName") outGameData.playerName = val;
            else if (key == "Health" || key == "health") outGameData.playerHealth = std::stof(val);
            else if (key == "PosX" || key == "x") outGameData.playerPosition.x = std::stof(val);
            else if (key == "PosY" || key == "y") outGameData.playerPosition.y = std::stof(val);
            else if (key == "PosZ" || key == "z") outGameData.playerPosition.z = std::stof(val);
            else if (key == "PlayedMinutes" || key == "playedMinutes") outGameData.playedMinutes = std::stoi(val);
        }
    }

    if (!mapParts.empty()) {
        std::vector<uint8_t> combined;
        for (auto& part : mapParts) combined.insert(combined.end(), part.begin(), part.end());
        outWorldData.cellData = std::move(combined);
    }
    outWorldData.zombieData.clear();
    outWorldData.itemData.clear();
    outWorldData.buildingData.clear();

    return true;
}

bool SaveGameManager::loadGameSVI(const std::string& saveName, GameSaveData& outGameData, WorldSaveData& outWorldData) {
    const std::string filename = getPlatformSaveRoot() + saveName + ".svi";
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    file.seekg(0, std::ios::end);
    const size_t size = static_cast<size_t>(file.tellg());
    file.seekg(0);
    std::vector<uint8_t> bytes(size);
    file.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(size));
    file.close();

    return parseSVIArchiveBytes(bytes, outGameData, outWorldData);
}

bool SaveGameManager::loadLatestGameSVI(GameSaveData& outGameData, WorldSaveData& outWorldData) {
    auto path = getLatestSVIPath();
    if (path.empty()) return false;

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;
    file.seekg(0, std::ios::end);
    const size_t size = static_cast<size_t>(file.tellg());
    file.seekg(0);
    std::vector<uint8_t> bytes(size);
    file.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(size));
    file.close();

    return parseSVIArchiveBytes(bytes, outGameData, outWorldData);
}

std::vector<std::string> SaveGameManager::listSaves() const {
    std::vector<std::string> saves;
    std::string root = getPlatformSaveRoot();
    if (std::filesystem::exists(root)) {
        for (const auto& entry : std::filesystem::directory_iterator(root)) {
            if (entry.path().extension() == ".sav") {
                saves.push_back(entry.path().stem().string());
            }
        }
    }
    return saves;
}

std::string SaveGameManager::getLatestSVIPath() const {
    namespace fs = std::filesystem;
    fs::path root(getPlatformSaveRoot());
    if (!fs::exists(root)) return std::string();

    fs::path newest;
    fs::file_time_type newestTime{};
    bool found = false;
    for (const auto& entry : fs::directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;
        if (entry.path().extension() != ".svi") continue;
        auto t = entry.last_write_time();
        if (!found || t > newestTime) {
            newest = entry.path();
            newestTime = t;
            found = true;
        }
    }
    return found ? newest.string() : std::string();
}

bool SaveGameManager::deleteSave(const std::string& saveName) {
    std::string filename = getPlatformSaveRoot() + saveName + ".sav";
    return std::filesystem::remove(filename) > 0;
}

std::string SaveGameManager::getSavePath() const {
    return getPlatformSaveRoot();
}

bool SaveGameManager::saveGameSVI(const std::string& saveName, const GameSaveData& gameData, const WorldSaveData& worldData) {
    std::string root = getPlatformSaveRoot();
    std::filesystem::create_directories(root);
    const std::string outFile = root + saveName + ".svi";

    SaveFileWriter::SVHeaderMeta meta;
    meta.title = "Project Zomboid";
    meta.saveName = saveName;
    meta.profileId = getActiveProfileId();
    meta.gameVersion = static_cast<uint32_t>(gameData.gameVersion);
    meta.timestamp = gameData.timestamp;

    // Build archive entries
    std::vector<SaveFileWriter::SVIArchiveEntry> entries;

    // 1) save.dat (for compatibility with loader)
    {
        std::vector<uint8_t> payload;
        auto appendU32 = [&](uint32_t v){ for (int i=0;i<4;++i) payload.push_back((v >> (i*8)) & 0xFF); };
        auto appendU64 = [&](uint64_t v){ for (int i=0;i<8;++i) payload.push_back((v >> (i*8)) & 0xFF); };
        auto appendF32 = [&](float f){ const uint8_t* p = reinterpret_cast<const uint8_t*>(&f); payload.insert(payload.end(), p, p+4); };

        appendU32(static_cast<uint32_t>(gameData.gameVersion));
        appendU64(gameData.timestamp);
        appendF32(gameData.playerPosition.x);
        appendF32(gameData.playerPosition.y);
        appendF32(gameData.playerPosition.z);
        appendF32(gameData.playerHealth);
        appendU32(static_cast<uint32_t>(gameData.playedMinutes));
        payload.insert(payload.end(), worldData.cellData.begin(), worldData.cellData.end());

        entries.push_back({"save.dat", std::move(payload)});
    }

    // 2) player_*.db (text placeholder for stats/inventory)
    {
        std::string playerName = gameData.playerName.empty() ? std::string("Player") : gameData.playerName;
        // sanitize name
        for (auto& c : playerName) { if (!(std::isalnum(static_cast<unsigned char>(c)) || c=='_' || c=='-')) c = '_'; }
        std::ostringstream oss;
        oss << "[Player]\n";
        oss << "Name=" << playerName << "\n";
        oss << "Health=" << gameData.playerHealth << "\n";
        oss << "PlayedMinutes=" << gameData.playedMinutes << "\n";
        oss << "PosX=" << gameData.playerPosition.x << "\n";
        oss << "PosY=" << gameData.playerPosition.y << "\n";
        oss << "PosZ=" << gameData.playerPosition.z << "\n";
        const std::string txt = oss.str();
        entries.push_back({std::string("player_") + playerName + ".db", std::vector<uint8_t>(txt.begin(), txt.end())});
    }

    // 3) world.ini (basic config snapshot from runtime options)
    {
        const auto& cfg = zombie::config::gOptionsConfig;
        std::ostringstream oss;
        oss << "[World]\n";
        oss << "Brightness=" << cfg.brightness << "\n";
        oss << "VSync=" << (cfg.vsync ? 1 : 0) << "\n";
        oss << "IsoCursorVisibility=" << (cfg.isoCursorVisibility ? 1 : 0) << "\n";
        oss << "ShowCursorWhileAiming=" << (cfg.showCursorWhileAiming ? 1 : 0) << "\n";
        oss << "AimOutlineMode=" << cfg.aimOutlineMode << "\n";
        oss << "LockCursorToWindow=" << (cfg.lockCursorToWindow ? 1 : 0) << "\n";
        oss << "UiOffscreenRendering=" << (cfg.uiOffscreenRendering ? 1 : 0) << "\n";
        oss << "UiRenderingFps=" << cfg.uiRenderingFps << "\n";
        oss << "InventoryButtonSize=" << cfg.inventoryButtonSize << "\n";
        oss << "ShowModInfoTooltip=" << (cfg.showModInfoTooltip ? 1 : 0) << "\n";
        oss << "ShowSurvivalGuide=" << (cfg.showSurvivalGuide ? 1 : 0) << "\n";
        oss << "AutosaveEnabled=" << (cfg.autosaveEnabled ? 1 : 0) << "\n";
        auto s = oss.str();
        entries.push_back({"world.ini", std::vector<uint8_t>(s.begin(), s.end())});
    }

    // 4) server/server.ini (multiplayer related files)
    {
        std::string s = "[Server]\nEnabled=false\nPort=16261\n";
        entries.push_back({"server/server.ini", std::vector<uint8_t>(s.begin(), s.end())});
    }

    // 5) map_* chunk bins (split worldData.cellData into fixed-size chunks)
    {
        const size_t chunkSize = 2048;
        const auto& buf = worldData.cellData;
        if (buf.empty()) {
            std::vector<uint8_t> empty{'E','M','P','T','Y'};
            entries.push_back({"map_1_1.bin", std::move(empty)});
        } else {
            size_t offset = 0; int ix = 1; int iy = 1;
            while (offset < buf.size()) {
                size_t take = std::min(chunkSize, buf.size() - offset);
                std::vector<uint8_t> chunk(buf.begin() + offset, buf.begin() + offset + take);
                std::string name = std::string("map_") + std::to_string(ix) + "_" + std::to_string(iy) + ".bin";
                entries.push_back({name, std::move(chunk)});
                offset += take;
                // simple progression
                if (++ix > 3) { ix = 1; ++iy; }
            }
        }
    }

    // 6) chunks/list.txt (index of map files)
    {
        std::ostringstream oss;
        for (const auto& e : entries) {
            if (e.name.rfind("map_", 0) == 0) {
                oss << e.name << "\n";
            }
        }
        const std::string txt = oss.str();
        entries.push_back({"chunks/list.txt", std::vector<uint8_t>(txt.begin(), txt.end())});
    }

    // 7) world.tiles (placeholder tiles data)
    {
        std::string tiles = "TILES\n# Placeholder tile data";
        entries.push_back({"world.tiles", std::vector<uint8_t>(tiles.begin(), tiles.end())});
    }

    return SaveFileWriter::writeSVIArchive(outFile, meta, entries);
}

std::string SaveGameManager::getPlatformSaveRoot() const {
#if defined(__SWITCH__)
    // Placeholder for internal NAND/system save path; to be replaced with FS API hooks.
    // Requirement: store to internal memory tied to user profile.
    return std::string("nand:/saves/") + getActiveProfileId() + "/";
#else
    // Dev environment fallback
    return std::string("./nand_saves/") + getActiveProfileId() + "/";
#endif
}

std::string SaveGameManager::getActiveProfileId() const {
#if defined(__SWITCH__)
    // TODO: query active user via account service; temporary env fallback
    const char* env = std::getenv("SWITCH_USER_ID");
    if (env && *env) return std::string(env);
    return "default";
#else
    const char* env = std::getenv("SWITCH_USER_ID");
    if (env && *env) return std::string(env);
    return "dev";
#endif
}

// --- TileMap serialization helpers ---
std::vector<uint8_t> SaveGameManager::serializeTileMap(const zombie::world::TileMap& map) {
    std::vector<uint8_t> out;
    auto writeU32 = [&](uint32_t v){ for(int i=0;i<4;++i) out.push_back((v >> (i*8)) & 0xFF); };
    auto writeU16 = [&](uint16_t v){ out.push_back(v & 0xFF); out.push_back((v >> 8) & 0xFF); };
    // Header: 'MAP1'
    writeU32(0x314D4150);
    writeU32(static_cast<uint32_t>(map.getWidth()));
    writeU32(static_cast<uint32_t>(map.getHeight()));
    writeU32(static_cast<uint32_t>(map.getLayerCount()));
    writeU32(static_cast<uint32_t>(map.getTileSize()));
    writeU32(0); // reserved
    for (int l = 0; l < map.getLayerCount(); ++l) {
        for (int y = 0; y < map.getHeight(); ++y) {
            for (int x = 0; x < map.getWidth(); ++x) {
                uint16_t id = static_cast<uint16_t>(map.getTile(x,y,l));
                writeU16(id);
            }
        }
    }
    return out;
}

bool SaveGameManager::deserializeTileMap(const std::vector<uint8_t>& data, zombie::world::TileMap& map) {
    if (data.size() < 24) return false;
    auto readU32 = [&](size_t& p){ uint32_t v=0; for(int i=0;i<4;++i) v |= static_cast<uint32_t>(data[p++]) << (i*8); return v; };
    size_t p = 0;
    uint32_t magic = readU32(p);
    if (magic != 0x314D4150) return false;
    uint32_t w = readU32(p);
    uint32_t h = readU32(p);
    uint32_t layers = readU32(p);
    uint32_t tileSize = readU32(p);
    (void)readU32(p); // reserved
    size_t expected = static_cast<size_t>(w) * static_cast<size_t>(h) * static_cast<size_t>(layers) * 2;
    if (data.size() - p < expected) return false;
    map.setSize(static_cast<int>(w), static_cast<int>(h), static_cast<int>(layers));
    map.setTileSize(static_cast<int>(tileSize));
    for (uint32_t l = 0; l < layers; ++l) {
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                uint16_t id = static_cast<uint16_t>(data[p] | (data[p+1] << 8));
                p += 2;
                map.setTile(static_cast<int>(x), static_cast<int>(y), static_cast<int>(l), static_cast<int>(id));
            }
        }
    }
    return true;
}

} // namespace saveload
} // namespace zombie
