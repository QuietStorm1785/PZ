#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>


namespace zombie {
namespace audio {


class DummySoundBank : public BaseSoundBank {
public:
    virtual ~DummySoundBank() = default;

    void addVoice(const std::string&, const std::string&, float) override {}
    void addFootstep(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&) override {}
    void* getVoice(const std::string&) override { return nullptr; }
    void* getFootstep(const std::string&) override { return nullptr; }
};
} // namespace audio
} // namespace zombie
