#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ICoopServerMessageListener {
public:
 virtual ~ICoopServerMessageListener() = default;
 void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& var3);
}
} // namespace network
} // namespace zombie
