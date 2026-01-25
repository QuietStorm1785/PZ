#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODVoice.h"

namespace zombie {
namespace audio {


class DummySoundBank : public BaseSoundBank {
public:
    virtual ~DummySoundBank() = default;

    void addVoice(const std::string&, const std::string&, float) override {}
    void addFootstep(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&) override {}
    FMODVoice getVoice(const std::string&) override { return FMODVoice(); }
    FMODFootstep getFootstep(const std::string&) override { return FMODFootstep(); }
};
} // namespace audio
} // namespace zombie
