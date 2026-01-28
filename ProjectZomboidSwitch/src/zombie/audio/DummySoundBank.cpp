
#include <string>
#include "zombie/audio/DummySoundBank.h"

namespace zombie {
namespace audio {

void DummySoundBank::addVoice(const std::string&, const std::string&, float) {
    // OpenAL stub: no-op
}

void DummySoundBank::addFootstep(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&) {
    // OpenAL stub: no-op
}

void* DummySoundBank::getVoice(const std::string&) {
    // OpenAL stub: always return nullptr
    return nullptr;
}

void* DummySoundBank::getFootstep(const std::string&) {
    // OpenAL stub: always return nullptr
    return nullptr;
}

} // namespace audio
} // namespace zombie
