#include "zombie/audio/DummySoundBank.h"

namespace zombie {
namespace audio {

void DummySoundBank::addVoice(const std::string &alias,
                              const std::string &sound, float priority) {
  // TODO: Implement addVoice
}

void DummySoundBank::addFootstep(const std::string &alias,
                                 const std::string &grass,
                                 const std::string &wood,
                                 const std::string &concrete,
                                 const std::string &upstairs) {
  // TODO: Implement addFootstep
}

FMODVoice DummySoundBank::getVoice(const std::string &alias) {
  // TODO: Implement getVoice
  return nullptr;
}

FMODFootstep DummySoundBank::getFootstep(const std::string &alias) {
  // TODO: Implement getFootstep
  return nullptr;
}

} // namespace audio
} // namespace zombie
