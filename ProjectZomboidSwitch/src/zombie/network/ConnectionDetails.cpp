#include "ConnectionDetails.h"

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

ConnectionDetails::ConnectionDetails() {}
ConnectionDetails::~ConnectionDetails() {}

// --- Static methods ported from Java ---

// Write all connection details to the buffer
void ConnectionDetails::write(UdpConnection* conn, LogonResult* logon, ByteBuffer* buffer) {
    // Ported from Java: write all connection details to the buffer
    // try {
    writeServerDetails(buffer, conn, logon);
    writeGameMap(buffer);
    // if (SteamUtils::isSteamModeEnabled()) {
    //     writeWorkshopItems(buffer);
    // }
    writeMods(buffer);
    writeStartLocation(buffer);
    writeServerOptions(buffer);
    writeSandboxOptions(buffer);
    writeGameTime(buffer);
    writeErosionMain(buffer);
    writeGlobalObjects(buffer);
    writeResetID(buffer);
    writeBerries(buffer);
    writeWorldDictionary(buffer);
    // } catch (const std::exception& ex) {
    //     // TODO: Exception handling/logging
    // }
}

void ConnectionDetails::parse(ByteBuffer* buffer) {
    // Ported from Java: ConnectionDetails.parse
    ConnectionManager::log("receive-packet", "connection-details", nullptr);
    auto now = std::chrono::system_clock::now();
    auto connectState = std::make_shared<ConnectToServerState>(buffer);
    connectState->enter();
    MainScreenState::getInstance()->setConnectToServerState(connectState);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - GameClient::startAuth).count();
    DebugLog::General::println("LOGGED INTO : %lld millisecond", ms);
}

void ConnectionDetails::writeServerDetails(ByteBuffer* buffer, UdpConnection* conn, LogonResult* logon) {
    buffer->put(static_cast<uint8_t>(conn->isCoopHost ? 1 : 0));
    buffer->putInt(ServerOptions::getInstance()->getMaxPlayers());
    if (SteamUtils::isSteamModeEnabled() && CoopSlave::instance && !conn->isCoopHost) {
        buffer->put(static_cast<uint8_t>(1));
        buffer->putLong(CoopSlave::instance->hostSteamID);
        GameWindow::WriteString(buffer, GameServer::ServerName);
    } else {
        buffer->put(static_cast<uint8_t>(0));
    }
    int var3 = conn->playerIDs[0] / 4;
    buffer->put(static_cast<uint8_t>(var3));
    GameWindow::WriteString(buffer, logon->accessLevel);
}

void ConnectionDetails::writeGameMap(ByteBuffer* buffer) {
    GameWindow::WriteString(buffer, GameServer::GameMap);
}

void ConnectionDetails::writeWorkshopItems(ByteBuffer* buffer) {
    buffer->putShort(static_cast<short>(GameServer::WorkshopItems.size()));
    for (size_t i = 0; i < GameServer::WorkshopItems.size(); ++i) {
        buffer->putLong(static_cast<int64_t>(GameServer::WorkshopItems[i]));
        buffer->putLong(GameServer::WorkshopTimeStamps[i]);
    }
}

void ConnectionDetails::writeMods(ByteBuffer* buffer) {
    std::vector<std::shared_ptr<Mod>> mods;
    for (const std::string& modName : GameServer::ServerMods) {
        std::string modDir = ZomboidFileSystem::instance->getModDir(modName);
        std::shared_ptr<Mod> mod;
        if (!modDir.empty()) {
            try {
                mod = ChooseGameInfo::readModInfo(modDir);
            } catch (...) {
                // ExceptionLogger::logException(...);
                mod = std::make_shared<Mod>(modName);
                mod->setId(modName);
                mod->setName(modName);
            }
        } else {
            mod = std::make_shared<Mod>(modName);
            mod->setId(modName);
            mod->setName(modName);
        }
        mods.push_back(mod);
    }
    buffer->putInt(static_cast<int>(mods.size()));
    for (const auto& mod : mods) {
        GameWindow::WriteString(buffer, mod->getId());
        GameWindow::WriteString(buffer, mod->getUrl());
        GameWindow::WriteString(buffer, mod->getName());
    }
}

void ConnectionDetails::writeStartLocation(ByteBuffer* buffer) {
    Vector3 loc = ServerMap::instance->getStartLocation(nullptr);
    buffer->putInt(static_cast<int>(loc.x));
    buffer->putInt(static_cast<int>(loc.y));
    buffer->putInt(static_cast<int>(loc.z));
}

void ConnectionDetails::writeServerOptions(ByteBuffer* buffer) {
    buffer->putInt(static_cast<int>(ServerOptions::instance->getPublicOptions().size()));
    for (const std::string& opt : ServerOptions::instance->getPublicOptions()) {
        GameWindow::WriteString(buffer, opt);
        GameWindow::WriteString(buffer, ServerOptions::instance->getOption(opt));
    }
}

void ConnectionDetails::writeSandboxOptions(ByteBuffer* buffer) {
    SandboxOptions::instance->save(buffer);
}

void ConnectionDetails::writeGameTime(ByteBuffer* buffer) {
    GameTime::getInstance()->saveToPacket(buffer);
}

void ConnectionDetails::writeErosionMain(ByteBuffer* buffer) {
    ErosionMain::getInstance()->getConfig()->save(buffer);
}

void ConnectionDetails::writeGlobalObjects(ByteBuffer* buffer) {
    SGlobalObjects::saveInitialStateForClient(buffer);
}

void ConnectionDetails::writeResetID(ByteBuffer* buffer) {
    buffer->putInt(GameServer::ResetID);
}

void ConnectionDetails::writeBerries(ByteBuffer* buffer) {
    GameWindow::WriteString(buffer, Core::getInstance()->getPoisonousBerry());
    GameWindow::WriteString(buffer, Core::getInstance()->getPoisonousMushroom());
}

void ConnectionDetails::writeWorldDictionary(ByteBuffer* buffer) {
    WorldDictionary::saveDataForClient(buffer);
}

// NAMESPACE WRAP END
} // namespace network
} // namespace zombie
