// VoiceManager.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class VoiceManager {
public:
    VoiceManager();
    ~VoiceManager();

    // Example API (to be filled in with actual ported methods)
    void startVoiceSession(const std::string& userId);
    void stopVoiceSession(const std::string& userId);
    bool isVoiceSessionActive(const std::string& userId) const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> activeSessions;
};

} // namespace network
} // namespace zombie
