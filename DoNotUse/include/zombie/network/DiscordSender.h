#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class DiscordSender {
public:
    virtual ~DiscordSender() = default;
    void sendMessageFromDiscord(const std::string& var1, const std::string& var2);
}
} // namespace network
} // namespace zombie
