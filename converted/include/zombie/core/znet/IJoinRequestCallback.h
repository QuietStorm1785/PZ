#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IJoinRequestCallback {
public:
 virtual ~IJoinRequestCallback() = default;
 void onJoinRequest(long var1, const std::string& var3);
}
} // namespace znet
} // namespace core
} // namespace zombie
