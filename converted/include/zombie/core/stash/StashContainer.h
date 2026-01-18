#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace stash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class StashContainer {
public:
 std::string room;
 std::string containerSprite;
 std::string containerType;
 int contX = -1;
 int contY = -1;
 int contZ = -1;
 std::string containerItem;

 public StashContainer(const std::string& string0, const std::string& string1, const std::string& string2) {
 if (string0.empty()) {
 this->room = "all";
 } else {
 this->room = string0;
 }

 this->containerSprite = string1;
 this->containerType = string2;
 }
}
} // namespace stash
} // namespace core
} // namespace zombie
