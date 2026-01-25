#include <string>
#include "zombie/audio/DummySoundBank.h"

namespace zombie {
namespace audio {

void DummySoundBank::addVoice(const std::string& var1, const std::string& var2, float var3) {
    // Store the voice data in the internal map
    m_voices[var1] = FMODVoice{var2, var3};
}

void DummySoundBank::addFootstep(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    // Store the footstep data in the internal map
    m_footsteps[var1] = FMODFootstep{var2, var3, var4, var5};
}

FMODVoice DummySoundBank::getVoice(const std::string& var1) {
    // Retrieve the voice from the internal map
    auto it = m_voices.find(var1);
    if (it != m_voices.end()) {
        return it->second;
    }
    return FMODVoice{};
}

FMODFootstep DummySoundBank::getFootstep(const std::string& var1) {
    // Retrieve the footstep from the internal map
    auto it = m_footsteps.find(var1);
    if (it != m_footsteps.end()) {
        return it->second;
    }
    return FMODFootstep{};
}

} // namespace audio
} // namespace zombie
