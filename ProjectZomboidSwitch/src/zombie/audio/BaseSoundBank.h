#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>


namespace zombie {
namespace audio {


class BaseSoundBank {
public:
    virtual ~BaseSoundBank() = default;

    static BaseSoundBank& instance();

    virtual void addVoice(const std::string& name, const std::string& file, float volume) = 0;
    virtual void addFootstep(const std::string& type, const std::string& material, const std::string& left, const std::string& right, const std::string& surface) = 0;
    // Replace FMODVoice and FMODFootstep with OpenAL or stub types as needed
    virtual void* getVoice(const std::string& name) = 0;
    virtual void* getFootstep(const std::string& type) = 0;
};
} // namespace audio
} // namespace zombie
