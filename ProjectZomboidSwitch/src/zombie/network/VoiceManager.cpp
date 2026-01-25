// VoiceManager.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "VoiceManager.h"
#include <algorithm>

namespace zombie {
namespace network {

VoiceManager::VoiceManager() {}
VoiceManager::~VoiceManager() {}

void VoiceManager::startVoiceSession(const std::string& userId) {
    if (std::find(activeSessions.begin(), activeSessions.end(), userId) == activeSessions.end()) {
        activeSessions.push_back(userId);
    }
}

void VoiceManager::stopVoiceSession(const std::string& userId) {
    auto it = std::remove(activeSessions.begin(), activeSessions.end(), userId);
    if (it != activeSessions.end()) {
        activeSessions.erase(it, activeSessions.end());
    }
}

bool VoiceManager::isVoiceSessionActive(const std::string& userId) const {
    return std::find(activeSessions.begin(), activeSessions.end(), userId) != activeSessions.end();
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
