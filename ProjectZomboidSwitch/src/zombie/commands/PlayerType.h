#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace commands {

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

    static std::string toString(uint8_t var0) {
      switch (var0) {
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

    static uint8_t fromString(const std::string& var0) {
      var0 = var0.trim().toLowerCase();
      if ("" == var0) || "player" == var0) || "none" == var0)) {
    return 1;
      } else if ("observer" == var0)) {
    return 2;
      } else if ("gm" == var0)) {
    return 4;
      } else if ("overseer" == var0)) {
    return 8;
      } else if ("moderator" == var0)) {
    return 16;
      } else {
         return (byte)("admin" == var0) ? 32 : 0);
      }
   }

    static bool isPrivileged(uint8_t var0) {
      return (var0 & 62) != 0;
   }
}
} // namespace commands
} // namespace zombie
