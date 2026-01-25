

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

#include "CoopSlave.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <filesystem>

CoopSlave* CoopSlave::instance = nullptr;
std::ostream* CoopSlave::stdoutStream = &std::cout;
std::ostream* CoopSlave::stderrStream = &std::cerr;

void CoopSlave::init() {
    if (!instance) instance = new CoopSlave();
}

void CoopSlave::initStreams() {
    std::string path = "coop-console.txt"; // TODO: Use ZomboidFileSystem for cache dir
    static std::ofstream fileStream(path);
    stdoutStream = &fileStream;
    stderrStream = &fileStream;
    std::cout.rdbuf(fileStream.rdbuf());
    std::cerr.rdbuf(fileStream.rdbuf());
}

CoopSlave::CoopSlave() : serverMessagePattern("^([\\-\\w]+)(\\[(\\d+)\\])?@(.*)$") {
    notify("coop mode enabled");
    // TODO: Use system property for hostUser if available
}

CoopSlave::~CoopSlave() {
    // Cleanup if needed
}

void CoopSlave::notify(const std::string& msg) {
    sendMessage("info", "", msg);
}

void CoopSlave::sendStatus(const std::string& msg) {
    sendMessage("status", "", msg);
}

void CoopSlave::status(const std::string& msg) {
    if (instance) instance->sendStatus(msg);
}

void CoopSlave::sendMessage(const std::string& msg) {
    sendMessage("message", "", msg);
}

void CoopSlave::sendMessage(const std::string& type, const std::string& tag, const std::string& payload) {
    if (!tag.empty()) {
        (*stdoutStream) << type << "[" << tag << "]@" << payload << std::endl;
    } else {
        (*stdoutStream) << type << "@" << payload << std::endl;
    }
}

void CoopSlave::sendExternalIPAddress(const std::string& tag) {
    // TODO: PortMapper::getExternalAddress equivalent
    sendMessage("get-parameter", tag, "external-ip");
}

void CoopSlave::sendSteamID(const std::string& tag) {
    // TODO: SteamUtils/SteamGameServer integration
    if (serverSteamID == 0 /* && SteamUtils::isSteamModeEnabled() */) {
        // serverSteamID = SteamGameServer::GetSteamID();
        serverSteamID = 123456789; // placeholder
    }
    sendMessage("get-parameter", tag, std::to_string(serverSteamID));
}

bool CoopSlave::handleCommand(const std::string& cmd) {
    std::regex re(serverMessagePattern);
    std::smatch match;
    if (std::regex_match(cmd, match, re)) {
        std::string var3 = match[1];
        std::string var4 = match[3];
        std::string var5 = match[4];
        if (var3 == "set-host-user") {
            (*stdoutStream) << "Set host user:" << var5 << std::endl;
            hostUser = var5;
        }
        if (var3 == "set-host-steamid") {
            // TODO: SteamUtils::convertStringToSteamID
            hostSteamID = std::stoll(var5);
        }
        if (var3 == "invite-add") {
            int64_t id = std::stoll(var5);
            if (id != -1) invites.insert(id);
        }
        if (var3 == "invite-remove") {
            int64_t id = std::stoll(var5);
            if (id != -1) invites.erase(id);
        }
        if (var3 == "get-parameter") {
            // DebugLog::log("Got get-parameter command: tag = " + var3 + " payload = " + var5);
            if (var5 == "external-ip") {
                sendExternalIPAddress(var4);
            } else if (var5 == "steam-id") {
                sendSteamID(var4);
            }
        }
        if (var3 == "ping") {
            lastPong = static_cast<int64_t>(std::chrono::system_clock::now().time_since_epoch().count());
        }
        if (var3 == "process-status" && var5 == "eof") {
            // DebugLog::log("Master connection lost: EOF");
            masterLostFlag = true;
        }
        return true;
    } else {
        // DebugLog::log("Got malformed command: " + cmd);
        return false;
    }
}

std::string CoopSlave::getHostUser() const {
    return hostUser;
}

void CoopSlave::update() {
    int64_t now = static_cast<int64_t>(std::chrono::system_clock::now().time_since_epoch().count());
    if (now >= nextPing) {
        sendMessage("ping", "", "ping");
        nextPing = now + 5000;
    }
    int64_t timeout = 60000;
    if (lastPong == -1) lastPong = now;
    masterLostFlag = masterLostFlag || (now - lastPong > timeout);
}

bool CoopSlave::masterLost() const {
    return masterLostFlag;
}

bool CoopSlave::isHost(int64_t steamID) const {
    return steamID == hostSteamID;
}

bool CoopSlave::isInvited(int64_t steamID) const {
    return invites.find(steamID) != invites.end();
}

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
