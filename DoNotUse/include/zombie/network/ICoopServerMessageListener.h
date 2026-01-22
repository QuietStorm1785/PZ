#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class ICoopServerMessageListener {
public:
    virtual ~ICoopServerMessageListener() = default;
    void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& var3);
}
} // namespace network
} // namespace zombie
