#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class Talker {
public:
    virtual ~Talker() = default;
    bool IsSpeaking();

    void Say(const std::string& var1);

    std::string getSayLine();

    std::string getTalkerType();
}
} // namespace characters
} // namespace zombie
