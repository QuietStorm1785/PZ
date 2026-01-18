#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace commands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class PlayerType {
public:
 static const uint8_t deprecated = 0;
 static const uint8_t fromServerOnly = 0;
 static const uint8_t player = 1;
 static const uint8_t observer = 2;
 static const uint8_t gm = 4;
 static const uint8_t overseer = 8;
 static const uint8_t moderator = 16;
 static const uint8_t admin = 32;
 static const uint8_t all = 63;
 static const uint8_t allExceptPlayer = 62;

 private PlayerType() {
 }

 static std::string toString(uint8_t byte0) {
 switch (byte0) {
 case 0:
 return "from-server-only";
 case 1:
 return "";
 case 2:
 return "observer";
 case 4:
 return "gm";
 case 8:
 return "overseer";
 case 16:
 return "moderator";
 case 32:
 return "admin";
 default:
 return "";
 }
 }

 static uint8_t fromString(const std::string& string) {
 string = string.trim().toLowerCase();
 if ("" == string) || "player" == string) || "none" == string) {
 return 1;
 } else if ("observer" == string) {
 return 2;
 } else if ("gm" == string) {
 return 4;
 } else if ("overseer" == string) {
 return 8;
 } else if ("moderator" == string) {
 return 16;
 } else {
 return (byte)("admin" == string) ? 32 : 0);
 }
 }

 static bool isPrivileged(uint8_t byte0) {
 return (byte0 & 62) != 0;
 }
}
} // namespace commands
} // namespace zombie
