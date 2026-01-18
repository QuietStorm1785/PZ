#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GUID {
public:
 static std::string generateGUID() {
 UUID uuid = UUID.randomUUID();
 return uuid.toString();
 }
}
} // namespace core
} // namespace zombie
