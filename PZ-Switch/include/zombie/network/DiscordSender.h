#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DiscordSender {
public:
 virtual ~DiscordSender() = default;
 void sendMessageFromDiscord(std::string_view var1, std::string_view var2);
}
} // namespace network
} // namespace zombie
